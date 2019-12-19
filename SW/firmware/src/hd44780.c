/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file hd44780.c
 * 
 * \brief Fichier source de la gestion de l'afficheur.
 * 
 * \details Ce fichier fournit les fonctions et les définitions utilisés par le
 * programme pour  gérer l'afficheur.
 *  
 ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdio.h>
#include <stdbool.h>
#include <GenericTypeDefs.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "hd44780.h"
#include "peripheral/gpio/plib_gpio.h"
#include "globaldef.h"
#include "timers.h"
#include "delay_us.h"
#include "mainboard2.h"

/* ************************************************************************** */

/**
 * \addtogroup afficheur
 * @{
 */

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/**
 * \brief Nom de la tâche de l'afficheur.
 */
#define LCD_TASK_NAME "LCD"

/**
 * \brief Nom du timer du TO.
 */
#define LCD_TO_TIMER_NAME "TO LCD"
/**
 * \brief Profondeur du tas de la tâche de l'afficheur.
 */
#define LCD_TASK_STACK 512

/**
 * \brief Priorité de la tâche de l'afficheur.
 */
#define LCD_TASK_PRIORITY 3

/**
 * \brief Nombre d'éléments dans la queue utilisée pour l'affichage.
 */
#define LCD_QUEUE_LEN 40

/**
 * \brief Position du caractère ? dans la ram graphique.
 */
#define EURO 7

/**
 * \brief Time out de la vérification de l'occupation du contrôleur.
 * \details Si l'afficheur est toujours occupé après ce délai, le programme 
 * cessera la vérification et tentera d'effectuer la commande.
 */
#define LCD_TO (2 * MILLISEC)

/**
 * \brief Dplacement des caractères
 */
#define LCD_SHIFT                       0b00000001

/**
 * \brief Incrémente le compteur d'adresse.
 */
#define LCD_INCREMENT                   0b00000010

/**
 * \brief curseur clignotant
 */
#define LCD_CURSOR_BLINK                0b00000001

/**
 * \brief curseur sur l'afficheur actif.
 */
#define LCD_CURSOR_ON                   0b00000010

/**
 * \brief afficheur actif.
 */
#define LCD_DISPLAY_ON                          0b00000100

/**
 * \brief Indique si le déplacement doit s'effectuer à gauche ou à droite.
 */
#define LCD_R_L                         0b00000100

/**
 * \brief déplace l'affichage
 */
#define LCD_SC                          0b00001000

/**
 * \brief Fonte utilisée par l'afficheur.
 */
#define LCD_FONT                        0b00000100    

/**
 * \brief Définie le nombre de ligne de l'afficheur.
 */
#define LCD_N_LIGNE                     0b00001000

/**
 * \brief Interface 8 bits
 */
#define LCD_8_BITS                      0b00010000

/**
 * \brief Flag d'occupation du contrôleur.
 * \details 0 libre, 1 occupé.
 * les bit 0 à 6 contiennent l'adresse du compteur d'adresse.
 */
#define  LCD_BUSY_FLAG                  0b10000000

/**
 * \brief Bus de données de l'afficheur.
 */
#define LCD_DATA ((1 << 4) | (1 << 5) | (1 << 6) | (1 <<7 ))

/**
 * \brief Port des données de l'afficheur.
 */
#define LCD_PORT_DATA GPIO_PORT_A

/**
 * \brief Positionne le bus de data en entrée.
 */
#define LCD_DATA_IN() GPIO_PortInputEnable (LCD_PORT_DATA, LCD_DATA)

/**
 * \brief Positionne le bus de data en sortie.
 */
#define LCD_DATA_OUT() GPIO_PortOutputEnable(LCD_PORT_DATA, LCD_DATA)

/**
 * \brief Positionne à zéro le port de données.
 */
#define LCD_CLEAR_DATA() GPIO_PortClear(LCD_PORT_DATA, LCD_DATA)

/**
 * \brief Caractères de niveau sur l'afficheur
 */
const uint8_t barr[] [8] =
        // <editor-fold desc="barr">
{
    {
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00010000,
     0b00000000,
    },
    {
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00001000,
     0b00011000,
     0b00000000,
    },
    {
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000100,
     0b00001100,
     0b00011100,
     0b00000000,
    },
    {
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000010,
     0b00000110,
     0b00001110,
     0b00011110,
     0b00000000,
    },
    {
     0b00000000,
     0b00000000,
     0b00000001,
     0b00000011,
     0b00000111,
     0b00001111,
     0b00011111,
     0b00000000,
    }
};
// </editor-fold>

/**
 * \brief Caractère euro
 */
const uint8_t euro[] =
        // <editor-fold desc="Euro">
{
 0b00000111,
 0b00001000,
 0b00011110,
 0b00001000,
 0b00011110,
 0b00001000,
 0b00000111,
 0b00000000,
};
// </editor-fold>

/**
 * \brief Structure contenant les informations à envoyer au contrôler HD44780.
 */
typedef struct
{
    bool isNotCmd;
    uint8_t byToLCD;
} FOR_LCD;

/**
 * \brief Variable structure contenant les variables utilisées par le module LCD.
 */
static struct
{
    TaskHandle_t hTaskLCD; /*!<HHandle de la tâche d'écriture.*/
    QueueHandle_t hQueueLCD; /*!Handle de la liste utilisée pour stocker les
                              * commandes et les caractères destinés au LCD.*/
    TimerHandle_t hTO_LCD; /*!<Timer de contrôle du TO.*/
    SemaphoreHandle_t semaphoreLCD; /*!<Handle du sémaphore protégeant la liste print.*/
    FOR_LCD forlcd; /*!<Structure contenant une information à envoyer à 
                     * l'afficheur.*/
    uint8_t cursor_Address; /*!<Adresse de la position qui sera utilisée pour 
                             * le prochain afficheur.*/
    bool isTOLCD; /*!<Flag indiquant si le TO est atteint.*/
    bool isLCDInitialized; /*!Flag indiquant si l'afficheur est initializé.*/

} lcd;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         static void vTO_LCD(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Positionne le flag de time out de l'afficheur à true
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vTO_LCD(TimerHandle_t timerHandle)
{
    lcd.isTOLCD = true;
}

/*********************************************************************
 * Function:        
 *         static void vLCD_Enable(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Valide les données présentent sur le bus de données de l'afficheur.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vLCD_Enable(void)
{
    LCD_EN_Set();
    Delay10us(1);
    LCD_EN_Clear();
}

/*********************************************************************
 * Function:        
 *        static uint8_t byGetLCDAddressCounter(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Return l'adresse en cours
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         L'adresse de l'afficheur en cours.
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static uint8_t byGetLCDAddressCounter(void)
{

    uint8_t byResult;

    LCD_DATA_IN();
    LCD_RS_Clear();
    LCD_RW_Set();
    Delay10us(1);
    LCD_EN_Set();
    Delay10us(1);
    byResult = (uint8_t) GPIO_PortRead(LCD_PORT_DATA) & LCD_DATA;
    LCD_EN_Clear();
    Delay10us(1);
    LCD_EN_Set();
    Delay10us(1);
    byResult += (uint8_t) (GPIO_PortRead(LCD_PORT_DATA) & LCD_DATA) >> 4;
    LCD_EN_Clear();
    Delay10us(1);
    LCD_RW_Clear();
    LCD_DATA_OUT();
    return byResult;
}

/*********************************************************************
 * Function:        
 *         static BOOL isLCDBusy()
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Vérifie si l'afficheur est disponible pour une nouvelle commande.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static BOOL isLCDBusy()
{
    return(lcd.cursor_Address = byGetLCDAddressCounter()) & LCD_BUSY_FLAG;
}

/*********************************************************************
 * Function:        static void LCDSetValue(const uint8_t byValue)
 *
 * Version:         
 *                  1.0
 * 
 * Date:            
 *                  yyyy.MM.dd
 * 
 * Author:          
 *                  Rachid AKKOUCHE  
 * 
 * Summary:         
 *                  Cette fonction 
 *
 * PreCondition:    
 *                  None                 
 *
 * Input:           
 *                  None                 
 *                  
 * Output:          
 *                  None                 
 * 
 * Returns          
 *                  None                 
 *
 * Side Effects:    
 *                  None                 
 *
 * Note:            
 *                  None                 
 * 
 * Example:
 *                  <code>
 *                  code            
 *                  </code>
 * 
 ********************************************************************/
static void vLCDSetValue(const uint8_t byValue, const bool isData)
{
    lcd.isTOLCD = false;
    xTimerStart(lcd.hTO_LCD, 1000);
    while(isLCDBusy() && !lcd.isTOLCD);
    xTimerStop(lcd.hTO_LCD, 1000);
    isData ? LCD_RS_Set() : LCD_RS_Clear();
    GPIO_PortWrite(LCD_PORT_DATA, LCD_DATA, (byValue & 0XF0));
    Delay10us(1);
    vLCD_Enable();
    Delay10us(1);
    GPIO_PortWrite(LCD_PORT_DATA, LCD_DATA, ((byValue << 4) & 0XF0));
    Delay10us(1);
    vLCD_Enable();
}
//******************************************************************************

/*********************************************************************
 * Function:        
 *         static void vTaskSendToDisplay(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Traite les caractères ou les commandes destinés à l'afficheur.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vTaskSendToDisplay(void *vParameter)
{
    while(1)
    {
        xQueueReceive(lcd.hQueueLCD, &lcd.forlcd, portMAX_DELAY);
        vLCDSetValue(lcd.forlcd.byToLCD, lcd.forlcd.isNotCmd);
    }
}

/*********************************************************************
 * Function:        
 *         static void vLCD_Set_Interface(const bool is8Bits)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vLCD_Set_Interface(const bool is8Bits)
{
    GPIO_PortWrite(LCD_PORT_DATA, LCD_DATA, LCD_FUNCTION_SET | (is8Bits ? LCD_8_BITS : 0));
    vLCD_Enable();
}

/*********************************************************************
 * Function:        
 *         static void vLCD_Command(const uint8_t byCmd)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/08
 *
 * Summary:
 *         Insère une commande dans la liste de l'afficheur.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vLCD_Command(const uint8_t byCmd)
{
    lcd.forlcd.isNotCmd = false;
    lcd.forlcd.byToLCD = byCmd;
    xQueueSendToBack(lcd.hQueueLCD, &lcd.forlcd, 1 * SECONDE);
}
/********************************************************************/

/*********************************************************************
 * Function:        
 *         static void vSetCGRamAddr(const uint8_t addr)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Enregistre le caractère en RAM.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vSetCGRamAddr(const uint8_t addr)
{
    lcd.forlcd.isNotCmd = false;
    lcd.forlcd.byToLCD = LCD_SET_CGRAM_ADRESS | addr;
    xQueueSendToBack(lcd.hQueueLCD, &lcd.forlcd, 1 * SECONDE);
}

/*********************************************************************
 * Function:        
 *         static void vCreateChar(const uint8_t Code, const uint8_t *pBuffer)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Crée un caractère en RAM graphique.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vCreateChar(const uint8_t Code, const uint8_t *pBuffer)
{
    uint8_t byIndex;
    vSetCGRamAddr(Code * 8);
    for(byIndex = 8; byIndex; byIndex--)
    {
        lcd.forlcd.isNotCmd = true;
        lcd.forlcd.byToLCD = *pBuffer++;
        xQueueSendToBack(lcd.hQueueLCD, &lcd.forlcd, 1 * SECONDE);
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         bool isLCDInitialized(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
bool isLCDInitialized(void)
{
    return lcd.isLCDInitialized;
}

/*********************************************************************
 * Function:        
 *         void _mon_putc(const char data)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Ajoute un caractère dans la queue
 * 
 * Description:
 *         Par défaut le compilateur envoie les caractères de vDisplayLCD sur le port 
 * série. La redéclaration de _mon_putc permet une redirection
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         Le code du caractère à afficher.
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void _mon_putc(const char data)
{
    lcd.forlcd.isNotCmd = true;
    lcd.forlcd.byToLCD = data;
    xQueueSendToBack(lcd.hQueueLCD, &lcd.forlcd, 1 * SECONDE);
}

/*********************************************************************
 * Function:        void vDisplayLCD(char *format, ...)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vDisplayLCD(char *format, ...)
{
    va_list args;

    xSemaphoreTake(lcd.semaphoreLCD, 10000);
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    xSemaphoreGive(lcd.semaphoreLCD);
}

/*********************************************************************
 * Function:        
 *         bool getIsLCDIntialiazed(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
bool getIsLCDIntialiazed(void)
{
    return lcd.isLCDInitialized;
}

/*********************************************************************
 * Function:        
 *         void vLCD_HOME()
 * 
 * Version :
 *          1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Positionne le curseur sur le premier caractère de la première ligne.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCD_HOME()
{
    vLCD_Command(LCD_HOME);
    delayMs(1);
}

/*********************************************************************
 * Function:        
 *         void vLCD_CLEAR()
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Efface l'écran.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCD_CLEAR()
{
    vLCD_Command(LCD_CLEAR);
    delayMs(1);
}

/*********************************************************************
 * Function:        
 *         void vLCDGotoXY(uint8_t X, uint8_t Y)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Positionne le curseur à la ligne Y en position X
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         X position sur la ligne.
 *          Y Ligne
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         La ligne et la position commence à 1
 * 
 *         
 ********************************************************************/
void vLCDGotoXY(uint8_t X, uint8_t Y)
{
    vLCD_Command(LCD_SET_DDRAM_ADDRESS | (--X + (--Y * 0X40)));
}

/*********************************************************************
 * Function:        
 *         void vLCDClearLine(const uint8_t byLine)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Efface une ligne
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         byLine Numéro de la ligne à effacer
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCDClearLine(const uint8_t byLine)
{
    vLCDGotoXY(1, byLine);
    vDisplayLCD("%s", "                    ");
    vLCDGotoXY(1, byLine);
}

/*********************************************************************
 * Function:        
 *         void vLCD_EntryMode(const eID inc, const eShift shift)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/1/10
 *
 * Summary:
 *         Choisi le mode d'entrée de l'afficheur.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         inc Type d'incrémentation.
 *          shift Déplacement à gaughe ou à droite.
 * 
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCD_EntryMode(const eID inc, const eShift shift)
{
    vLCD_Command(LCD_ENTRY_SET | (inc == increment ? LCD_INCREMENT : 0) | (shift == shifted ? LCD_SHIFT : 0));
}

/*********************************************************************
 * Function:        
 *         void vLCD_Display_control(LCD_ON_OFF d_on, Cursor_ON_OFF c_on, Blink_ON_OFF b_on)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Contrôle de l'afficheur
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         d_on Afficheur actif ou non
 *          c_on Curseur affiché ou non 
 *          b_on Curseur clignotant ou non
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCD_Display_control(const LCD_ON_OFF d_on, const Cursor_ON_OFF c_on, const Blink_ON_OFF b_on)
{
    vLCD_Command(LCD_DISPLAY_CONTROL | (d_on == LCD_On ? LCD_DISPLAY_ON : 0) |
                 (c_on == Cursor_On ? LCD_CURSOR_ON : 0) | (b_on == Blink_On ? LCD_CURSOR_BLINK : 0));
}

/*********************************************************************
 * Function:        
 *         void vLCD_Shift(const CursorDisplayShift beShifted, const eDirection direction)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         Déplace le curseur ou l'affichage
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         beShifted Indique si le glissement s'effectue ou non
 *          direction Direction du glissement le cas échéant.
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCD_Shift(const CursorDisplayShift beShifted, const eDirection direction)
{
    vLCD_Command(LCD_SHIFT_DISPLAY_CURSOR | (beShifted == D_shift ? LCD_SC : 0) |
                 (direction == right ? LCD_R_L : 0));
}

/*********************************************************************
 * Function:        
 *         void vLCD_Function(const eInterface interface, const eLines lines,
 *                            const eFont font)     
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Défini le bus, le nombre de lignes et la fonte utilisés.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         inteface 4 ou 8 bits
 *          eLines 1 ou 2 lignes
 *          font 5x8 ou 5x10
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         La fonte 5x10 ne peut être utlisée que par les afficheurs à 1 ligne.
 *         
 ********************************************************************/
void vLCD_Function(const eInterface interface, const eLines lines,
                   const eFont font)
{
    vLCD_Command(LCD_FUNCTION_SET | (interface == bits8 ? LCD_8_BITS : 0) |
                 (lines == more ? LCD_N_LIGNE : 0) | (font == hi ? LCD_FONT : 0));
}

/*********************************************************************
 * Function:        
 *         bool getLCDInitialized(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/10
 *
 * Summary:
 *         Renvoi le flag d'initialization.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         isInitialized
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
bool getLCDInitialized(void)
{
    return lcd.isLCDInitialized;
}

/*********************************************************************
 * Function:        
 *         void vHD44780Init(void)
 * 
 * Version: 1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Initialise le contrôleur HD44780 ou équivalent.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vHD44780Init(void)
{
    uint8_t byIndex;

    delayMs(MILLISEC * 100);
    vLCD_Set_Interface(true);
    delayMs(8);
    vLCD_Set_Interface(true);
    delayMs(1);
    vLCD_Set_Interface(true);
    delayMs(1);
    vLCD_Set_Interface(false);
    delayMs(1);
    vLCD_Function(bits4, more, lo);
    vLCD_Display_control(LCD_Off, Cursor_Off, Blink_Off);
    vLCD_EntryMode(increment, noShifted);
    vLCD_Display_control(LCD_On, Blink_Off, Cursor_Off);
    vCreateChar(EURO, euro);
    for(byIndex = 0; byIndex < 5; byIndex++)
    {
        vCreateChar(byIndex + 1, barr[byIndex]);
    }
    vLCD_CLEAR();
}

/*********************************************************************
 * Function:        
 *         void vLCDInit(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/09
 *
 * Summary:
 *         Initialise le module de gestion de l'afficheur.
 * 
 * Description:
 *         Positionne toutes les lignes à létat bas,
 *         Crée la tâche d'envoi des commandes ou des caractères
 *         Crée la liste qui contiendra les commandes ou caractères.  
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vLCDInit(void)
{
    LCD_RS_Clear();
    LCD_RW_Clear();
    LCD_EN_Clear();
    LCD_CLEAR_DATA();
    lcd.isLCDInitialized = false;

    if(!lcd.semaphoreLCD)
    {
        xSemaphoreGive(lcd.semaphoreLCD = xSemaphoreCreateBinary());
    }
    if(!lcd.hQueueLCD)
    {
        lcd.hQueueLCD = xQueueCreate(40, sizeof(FOR_LCD));
    }
    if(!lcd.hTO_LCD)
    {
        lcd.hTO_LCD = xTimerCreate(LCD_TO_TIMER_NAME, LCD_TO, false, NULL,
                                   vTO_LCD);
    }
    if(!lcd.hTaskLCD)
    {
        xTaskCreate(vTaskSendToDisplay, LCD_TASK_NAME, LCD_TASK_STACK, NULL,
                    LCD_TASK_PRIORITY, &lcd.hTaskLCD);
    }
}
/**
 * @}
 */
/* *****************************************************************************
End of File
 */

/** *************************************************************************
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file audits.c
 * 
 * \brief Fichier gestion des audits.
 * 
 * \details Gestion des audits
 *  
 ***************************************************************************/
/* ************************************************************************** */

#include <string.h>
#include <machine/types.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "globaldef.h"
#include "config/../configuration.h"
#include "driver/at24/drv_at24.h"
#include "peripheral/gpio/plib_gpio.h"
#include "audits.h"
#include "hd44780.h"
#include "peripheral/uart/plib_uart3.h"
#include "MDB/mdb_bv.h"
#include "MDB/mdb_cg.h"

/**
 * \addtogroup audits
 * @{
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/**
 * \brief Valeur indiquant que l'eeprom a �t� initialis'.
 */
#define AUDITS_USED_FLAG 0XA5A5A5A5

/**
 * \brief Nom de la t�che d'audits.
 */
#define AUDITS_TASK_NAME "Audits"

/**
 * \brief Profondeur du tas de la t�che d'audits.
 */
#define AUDITS_TASK_STACK 512

/**
 * \brief Priorit� de la t�che d'audits.
 */
#define AUDITS_TASK_PRIORITY 2

/**
 * \brief Nombre d'�l�ments dans la queue utilis�e dans la t�che d'audits
 */
#define AUDITS_QUEUE_LEN 8

/**
 * \brief Delay de la t�che
 */
#define AUDITS_DELAY (1000 * MILLISEC)

/**
 * \brief Adresse du flag d'initialisation dans l'eeprom
 */
#define ADDRESS_FLAG (DRV_AT24_EEPROM_FLASH_SIZE - sizeof(uint32_t))


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/**
 * \brief Structure contenant les donn�es d'un enregistrement � sauvegarder dans 
 * l'eeprom.
 */
typedef struct
{
    uint32_t dwAddress; /*!<Adresse � laquelle sera enregistr�e la valeur.*/
    uint32_t dwValue; /*<Valeur de la donn�e � sauvegarder.*/
} RECORDWORD;

/**
 * \brief Structure des datas d'audits
 */
typedef struct
{
    uint32_t dwCG_in[NUMBERCHANNELSCG]; /*!<Tableau du nombre de pi�ces par canal 
                                        * accept�es par le rendeur.*/
    uint32_t dwCG_OUT[NUMBERCHANNELSCG]; /*!<<Tableau du nombre de pi�ces par 
                                         * canal retourn�es par le rendeur.*/
    uint32_t dwBV_in[NUMBERCHANNELSBV]; /*!<Tableau du nombre de billets par 
                                        * canal accept�s par le lecteur de 
                                        * billets.*/
    uint32_t dwProductsOut[PRODUCT_NUMBER]; /*!<Tableau du nombre de produits 
                                             * distribu�s.*/
    uint32_t dwInCash; /*!<Montant en caisse.*/
    uint32_t dwCashLess; /*!<Montant pay� en cash less.*/
    uint32_t dwOverPay; /*!<Montant du trop per�u en cts.*/

} SAUDITS;

/**
 * \brief Union contenant les audits.
 */
typedef union
{
    uint8_t buffer[sizeof(SAUDITS) / DRV_AT24_EEPROM_PAGE_SIZE * DRV_AT24_EEPROM_PAGE_SIZE + DRV_AT24_EEPROM_PAGE_SIZE]; /*!<Tableau contenant les donn�es audits.*/
    SAUDITS saudit; /*<Structure contenant les donn�es audits.*/
} UAUDITS;

/**
 * \brief Variables contenant les donn�es de la gestion des audits.
 */
static struct
{
    AUDITS_STATES state; /*!<Etat de la t�che.*/
    DRV_HANDLE hDrvAT24; /*!<Handle du driver de la m�moire eeprom*/
    QueueHandle_t hAuditQueue; /*!<Handle de la queue utilis�e comme liste des 
                                * informations � enregistrer.*/
    TaskHandle_t hAuditHandle; /*!<Handle de la t�che de la machine d'�tat 
                                * utilis�e par le module.*/
    UAUDITS dataBuffer; /*!<Buffer contenant les donne�es d'audits.*/
    RECORDWORD record; /*!<Variable temporaire utilis�e pour enregistrer les 
                        * informations dans l'eeprom.*/
    bool isAuditReseted; /*!<Flag indiquant si un reset � �t� effectu� sur les
                          * audits*/
} audits;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         static void vTaskAudit(void *vParameters)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/08
 *
 * Summary:
 *         T�che du module de gestion des audits.
 * 
 * Description:
 *         Cette t�che freertos effectue en permanence la v�rification de l'�tat
 * de la machine d'�tat du module et effectue les op�rations correspondant � 
 * l'�tat en cours.
 *
 * PreCondition:    
 *         La t�che doit avoir �t� cr�e par la fonction vAuditsInit et le 
 * scheduler FreeRtos actif.
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
static void vTaskAudit(void *vParameters)
{
    int index;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        switch(audits.state)
        {
            case AUDITS_STATE_INIT:
                // <editor-fold desc="AUDIT_INIT"> 
            {
                if((DRV_AT24_Status(DRV_AT24_INDEX) == SYS_STATUS_READY) &&
                   ((audits.hDrvAT24 = DRV_AT24_Open(DRV_AT24_INDEX, DRV_IO_INTENT_READWRITE)) !=
                    DRV_HANDLE_INVALID))
                {
                    audits.state = CLR_Get() ? AUDITS_STATE_READ : AUDITS_STATE_CLEAR;
                    if(!audits.hAuditQueue)
                    {
                        audits.hAuditQueue = xQueueCreate(AUDITS_QUEUE_LEN, sizeof( RECORDWORD));
                    }
                }
                break;
            }// </editor-fold>
            case AUDITS_STATE_READ:
                // <editor-fold desc="AUDITS_READ"> 
            {
                audits.state = AUDITS_STATE_IDLE;
                DRV_AT24_Read(audits.hDrvAT24, &audits.record.dwValue,
                              sizeof(audits.record.dwValue), ADDRESS_FLAG);
                while(DRV_AT24_TransferStatusGet(audits.hDrvAT24) == DRV_AT24_TRANSFER_STATUS_BUSY);
                if(audits.record.dwValue != AUDITS_USED_FLAG)
                {
                    memset(&audits.dataBuffer, 0, sizeof(UAUDITS));
                    for(index = 0; index < (sizeof(UAUDITS) / DRV_AT24_EEPROM_PAGE_SIZE); index++)
                    {
                        DRV_AT24_PageWrite(audits.hDrvAT24, &audits.dataBuffer, index * DRV_AT24_EEPROM_PAGE_SIZE);
                        while(DRV_AT24_TransferStatusGet(audits.hDrvAT24) == DRV_AT24_TRANSFER_STATUS_BUSY);
                    }
                    audits.record.dwAddress = ADDRESS_FLAG;
                    audits.record.dwValue = AUDITS_USED_FLAG;
                    xQueueSendToBack(audits.hAuditQueue, &audits.record, 1000);
                }
                else
                {
                    DRV_AT24_Read(audits.hDrvAT24, audits.dataBuffer.buffer, sizeof(UAUDITS), 0);
                    while(DRV_AT24_TransferStatusGet(audits.hDrvAT24) == DRV_AT24_TRANSFER_STATUS_BUSY);
                }
                break;
            }// </editor-fold>
            case AUDITS_STATE_IDLE:
                // <editor-fold desc="AUDIT_IDLE"> 
            {
                if(xQueueReceive(audits.hAuditQueue, &audits.record, 10))
                {
                    DRV_AT24_Write(audits.hDrvAT24, &audits.record.dwValue,
                                   sizeof(audits.record.dwValue),
                                   audits.record.dwAddress);
                    while(DRV_AT24_TransferStatusGet(audits.hDrvAT24) == DRV_AT24_TRANSFER_STATUS_BUSY);
                    if(audits.record.dwAddress == ADDRESS_FLAG)
                    {
                        if(audits.record.dwValue == UINT32_MAX)
                        {
                            audits.state = AUDITS_STATE_READ;
                        }
                        if(audits.record.dwValue == AUDITS_USED_FLAG)
                        {
                            if(!CLR_Get())
                            {
                                vLCD_CLEAR();
                                vLCDGotoXY(1, 1);
                                vDisplayLCD("%s", "  RAZ termine");
                                vLCDGotoXY(1, 2);
                                vDisplayLCD("%s", " Retirez jumper");
                                while(!CLR_Get())
                                {
                                    LED_SYS_Toggle();
                                    vTaskDelay(FLASH_PERIOD);
                                }
                                LED_SYS_Clear();
                            }
                            setIsRAZAudit(true);
                        }
                    }
                }
                break;
            }// </editor-fold>
            case AUDITS_STATE_CLEAR:
                // <editor-fold desc="AUDITS_STATE_CLEAR"> 
            {
                audits.state = AUDITS_STATE_IDLE;
                audits.record.dwAddress = ADDRESS_FLAG;
                audits.record.dwValue = UINT32_MAX;
                xQueueSendToBack(audits.hAuditQueue, &audits.record, 1000);
                break;
            }// </editor-fold>
            case AUDITS_STATE_SEND_TO_PC:
                // <editor-fold desc="AUDITS_SEND_TO_PC"> 
            {
                audits.state = AUDITS_STATE_IDLE;
                uint32_t dwDataSize = sizeof(SAUDITS);
                UART3_Write(&dwDataSize, sizeof(dwDataSize));
                while(!UART3_TransmitComplete());
                UART3_Write(&audits.dataBuffer.saudit, sizeof(SAUDITS));
                while(!UART3_TransmitComplete());
                break;
            }// </editor-fold>
            default:
            {
                break;
            }
        }
        vTaskDelayUntil(&xLastWakeTime, AUDITS_DELAY);
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         uint32_t getAuditValue(uint32_t Address)
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
uint32_t getAuditValue(uint32_t Address)
{
    uint32_t result;
    memmove(&result, &audits.dataBuffer.buffer[Address], sizeof(uint32_t));
    return result;
}

/*********************************************************************
 * Function:        
 *         void setAuditValue(const uint32_t Address, const uint32_t value)
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
void setAuditValue(uint32_t Address, uint32_t value)
{
    audits.record.dwAddress = Address;
    audits.record.dwValue = value;
    xQueueSendToBack(audits.hAuditQueue, &audits.record, 1000);
}

/*********************************************************************
 * Function:        
 *         void setAuditState(AUDITS_STATES state)
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
void setAuditState(AUDITS_STATES state)
{
    while(audits.state != AUDITS_STATE_IDLE);
    audits.state = state;
}

/*********************************************************************
 * Function:        
 *         bool getIsRAZAudit()
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
 *         Retourne le flag indiquant que l'audit est remise � z�ro.
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
 *         Le flag de remise � z�ro des audits
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
bool getIsRAZAudit()
{
    return audits.isAuditReseted;
}

/*********************************************************************
 * Function:        
 *         void setIsRAZAudit(bool isRAZ)
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
 *         Fixe l'�tat du flag de RAZ.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         isRAZ Flag indiquant si le RAZ vient d\ �tre effectu�.
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
void setIsRAZAudit(bool isRAZ)
{
    audits.isAuditReseted = isRAZ;
}

/*********************************************************************
 * Function:        
 *         void vAuditsInit(void)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/01
 *
 * Summary:
 *         Initialisation du module
 * 
 * Description:
 *         Position l'�tat de la machine d'�tat sur AUDIT_STATE_INIT pour
 * permettre la cr�ation du handle de la m�moire I2C. Puis cr�e la t�che pour
 * FreeRtos du module.
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
void vAuditsInit(void)
{
    if(!audits.hAuditHandle)
    {
        audits.state = AUDITS_STATE_INIT;
        setIsRAZAudit(false);
        xTaskCreate(vTaskAudit, AUDITS_TASK_NAME, AUDITS_TASK_STACK, NULL,
                    AUDITS_TASK_PRIORITY, &audits.hAuditHandle);
    }
}
/**
 * @}
 */
/* *****************************************************************************
End of File
 */

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
 * \brief Valeur indiquant que l'eeprom a été initialis'.
 */
#define AUDITS_USED_FLAG 0XA5A5A5A5

/**
 * \brief Nom de la tâche d'audits.
 */
#define AUDITS_TASK_NAME "Audits"

/**
 * \brief Profondeur du tas de la tâche d'audits.
 */
#define AUDITS_TASK_STACK 512

/**
 * \brief Priorité de la tâche d'audits.
 */
#define AUDITS_TASK_PRIORITY 2

/**
 * \brief Nombre d'éléments dans la queue utilisée dans la tâche d'audits
 */
#define AUDITS_QUEUE_LEN 8

/**
 * \brief Delay de la tâche
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
 * \brief Structure contenant les données d'un enregistrement à sauvegarder dans 
 * l'eeprom.
 */
typedef struct
{
    uint32_t dwAddress; /*!<Adresse à laquelle sera enregistrée la valeur.*/
    uint32_t dwValue; /*<Valeur de la donnée à sauvegarder.*/
} RECORDWORD;

/**
 * \brief Structure des datas d'audits
 */
typedef struct
{
    uint32_t dwCG_in[NUMBERCHANNELSCG]; /*!<Tableau du nombre de pièces par canal 
                                        * acceptées par le rendeur.*/
    uint32_t dwCG_OUT[NUMBERCHANNELSCG]; /*!<<Tableau du nombre de pièces par 
                                         * canal retournées par le rendeur.*/
    uint32_t dwBV_in[NUMBERCHANNELSBV]; /*!<Tableau du nombre de billets par 
                                        * canal acceptés par le lecteur de 
                                        * billets.*/
    uint32_t dwProductsOut[PRODUCT_NUMBER]; /*!<Tableau du nombre de produits 
                                             * distribués.*/
    uint32_t dwInCash; /*!<Montant en caisse.*/
    uint32_t dwCashLess; /*!<Montant payé en cash less.*/
    uint32_t dwOverPay; /*!<Montant du trop perçu en cts.*/

} SAUDITS;

/**
 * \brief Union contenant les audits.
 */
typedef union
{
    uint8_t buffer[sizeof(SAUDITS) / DRV_AT24_EEPROM_PAGE_SIZE * DRV_AT24_EEPROM_PAGE_SIZE + DRV_AT24_EEPROM_PAGE_SIZE]; /*!<Tableau contenant les données audits.*/
    SAUDITS saudit; /*<Structure contenant les données audits.*/
} UAUDITS;

/**
 * \brief Variables contenant les données de la gestion des audits.
 */
static struct
{
    AUDITS_STATES state; /*!<Etat de la tâche.*/
    DRV_HANDLE hDrvAT24; /*!<Handle du driver de la mémoire eeprom*/
    QueueHandle_t hAuditQueue; /*!<Handle de la queue utilisée comme liste des 
                                * informations à enregistrer.*/
    TaskHandle_t hAuditHandle; /*!<Handle de la tâche de la machine d'état 
                                * utilisée par le module.*/
    UAUDITS dataBuffer; /*!<Buffer contenant les donneées d'audits.*/
    RECORDWORD record; /*!<Variable temporaire utilisée pour enregistrer les 
                        * informations dans l'eeprom.*/
    bool isAuditReseted; /*!<Flag indiquant si un reset à été effectué sur les
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
 *         Tâche du module de gestion des audits.
 * 
 * Description:
 *         Cette tâche freertos effectue en permanence la vérification de l'état
 * de la machine d'état du module et effectue les opérations correspondant à 
 * l'état en cours.
 *
 * PreCondition:    
 *         La tâche doit avoir été crée par la fonction vAuditsInit et le 
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
 *         Retourne le flag indiquant que l'audit est remise à zéro.
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
 *         Le flag de remise à zéro des audits
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
 *         Fixe l'état du flag de RAZ.
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         isRAZ Flag indiquant si le RAZ vient d\ être effectué.
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
 *         Position l'état de la machine d'état sur AUDIT_STATE_INIT pour
 * permettre la création du handle de la mémoire I2C. Puis crée la tâche pour
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

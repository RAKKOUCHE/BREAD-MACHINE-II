/* ************************************************************************** */
/** Descriptive File Name
 * 
 * Company
 *      RASoftware  
 * \file dataCommun.c
 * 
 * \brief Fichier superviseur des données
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc-pic32m.h>

#include "dataCommun.h"
#include "timers.h"

/**
 * \addtogroup dataRecord
 * @{
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* ************************************************************************** */

/**
 * \brief Nom en clair de la tâche
 */
#define PCCOM_TASK_NAME "PC com"

/**
 * \brief Nom en clair du timer de TO.
 */
#define PCCOM_TASK_TIMER_NAME "PC_TIMER"

/**
 * \brief Taille du tas de la tâche.
 */
#define PCCOM_TASK_STACK 512

/**
 * \brief Priorité de la tâche.
 */
#define PCCOM_TASK_PRIORITY 2

/**
 * \brief Delai maximum accordé pour une communication.
 */
#define PCCOM_TIMER_TO (5 * SECONDE)

/**
 * \brief Enumération des commandes venant du PC.
 */
enum
{
    PCCOM_AUDITS_REQUEST = 0XAA, /*!<Envoi des audits au PC.*/
    PCCOM_AUDITS_CLEAR = 0X55, /*!<Requête, par le PC, de la remise à zéro des audits.*/
    PCCOM_PARAM_REQUEST = 0X5A, /*!<Envoi des paramètres au PC.*/
    PCC0M_PARAM_SET = 0XA5, /*!<Enregistre les paramètres venant du PC.*/
    PCCOM_CHECK = 0XAF, /*!<Ack vers le PC.*/
};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         static void vTOPC(TimerHandle_t *timer)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/22
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
static void vTOPC(TimerHandle_t timerHandle)
{
    pcCom.isTOReached = true;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         void vTaskPcComm(void *vParameters)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/14
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
void vTaskPcComm(void *vParameters)
{
    int toto;
    uint8_t byCheckAnswer = 0XFA;
    while(1)
    {
        switch(pcCom.state)
        {
            case STATE_PCCOMM_INIT:
                // <editor-fold desc="STATE_PCCOMM_INIT"> 
            {
                pcCom.hTimerTO_PC = xTimerCreate(PCCOM_TASK_TIMER_NAME,
                                                 PCCOM_TIMER_TO, false, 
                                                 NULL, vTOPC);
                pcCom.state = STATE_PCCOM_IDLE;
                break;
            }// </editor-fold>

            case STATE_PCCOM_IDLE:
                // <editor-fold desc="STATE_PCCOM_IDLE"> 
            {
                if(UART3_ReceiverIsReady())
                {
                    switch(UART3_ReadByte())
                    {
                        case PCCOM_AUDITS_REQUEST:
                            // <editor-fold desc="PCCOM_AUDITS_REQUEST"> 
                        {
                            setAuditState(AUDITS_STATE_SEND_TO_PC);
                            break;
                        }// </editor-fold>
                        case PCCOM_AUDITS_CLEAR:
                            // <editor-fold desc="PCCOM_AUDITS_CLEAR"> 
                        {
                            setAuditState(AUDITS_STATE_CLEAR);
                            while(!getIsRAZAudit());
//                            setAuditState(AUDITS_STATE_SEND_TO_PC);
                            break;
                        }// </editor-fold>
                        case PCCOM_PARAM_REQUEST:
                            // <editor-fold desc="PCCOM_PARAM_REQUEST"> 
                        {
                            vParamSendToPC();
                            break;
                        }// </editor-fold>
                        case PCC0M_PARAM_SET:
                            // <editor-fold desc="PCC0M_PARAM_SET:"> 
                        {
                            vParametersGetFromPC();
                            break;
                        }// </editor-fold>
                        case PCCOM_CHECK:
                        {
                            UART3_Write(&byCheckAnswer, 1);
                            while(UART3_TransmitComplete());
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
                break;
            }// </editor-fold>
            default:
            {

                break;
            }
        }
        delayMs(100);
    }
}

/*********************************************************************
 * Function:        
 *         void vDataInit(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/14
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         Initialise des fonctions communes aux données
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
void vDataInit(void)
{
    if(pcCom.handlePcCom == NULL)
    {
        xTaskCreate(vTaskPcComm, PCCOM_TASK_NAME, PCCOM_TASK_STACK, NULL,
                    PCCOM_TASK_PRIORITY, &pcCom.handlePcCom);
    }
}
/**
 * @}
 */
/* *****************************************************************************
End of File
 */

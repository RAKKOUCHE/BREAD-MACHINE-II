
/**
 * \addtogroup dataRecord
 * @{
 */
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

#include "dataCommun.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/usart/processor/usart_p32mx575f512l.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* ************************************************************************** */

/**
 * \brief Nom en clair de la tâche
 */
#define PCCOM_TASK_NAME "TSK PC_COM"

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
    SYS_RESET_SoftwareReset();
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

    //    uint8_t byCheckAnswer = 0XFA;

    while(1)
    {
        switch(pcCom.state)
        {
            case STATE_PCCOMM_INIT:
                // <editor-fold desc="STATE_PCCOMM_INIT">
            {
                PLIB_USART_LineControlModeSelect(USART_ID_2, USART_8N1);
                PLIB_USART_BaudRateSet(USART_ID_2, SYS_CLK_BUS_PERIPHERAL_1, 19200);

                PLIB_USART_OperationModeSelect(USART_ID_2, USART_ENABLE_TX_RX_USED);

                PLIB_USART_TransmitterEnable(USART_ID_2);

                PLIB_USART_ReceiverEnable(USART_ID_2);

                PLIB_USART_Enable(USART_ID_2);

                pcCom.hTimerTO_PC = xTimerCreate(PCCOM_TASK_TIMER_NAME,
                                                 PCCOM_TIMER_TO, false,
                                                 NULL, vTOPC);
                pcCom.state = STATE_PCCOM_IDLE;
                break;
            }// </editor-fold>

            case STATE_PCCOM_IDLE:
                // <editor-fold desc="STATE_PCCOM_IDLE">
            {
                if(PLIB_USART_ReceiverDataIsAvailable(USART_ID_2))
                {
                    switch((uint8_t)PLIB_USART_ReceiverByteReceive(USART_ID_2))
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
                            setIsRAZAudit(false);
                            RAZAudits();
                            while(!getIsRAZAudit());
                            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
                            PLIB_USART_TransmitterByteSend(USART_ID_2, 0Xff);

                            //                            setAuditState(AUDITS_STATE_CLEAR);
                            //                            while(!getIsRAZAudit());
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
                            // <editor-fold desc="PCCOM_CHECK">
                        {
                            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
                            PLIB_USART_TransmitterByteSend(USART_ID_2, 0xFA);
                            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
                            break;
                        }// </editor-fold>
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
        delayMs(20);
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
        xTaskCreate((TaskFunction_t)vTaskPcComm, PCCOM_TASK_NAME, PCCOM_TASK_STACK, NULL,
                    PCCOM_TASK_PRIORITY, &pcCom.handlePcCom);
    }
}
/**
 * @}
 */
/* *****************************************************************************
End of File
 */

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
#define PCCOOM_TASK_NAME "PC com"

/**
 * \brief Taille du tas de la tâche.
 */
#define PCCOM_TASK_STACK 512

/**
 * \brief Priorité de la tâche.
 */
#define PCCOM_TASK_PRIORITY 2

/**
 * \brief Enumération des commandes venant du PC.
 */
enum
{   
    PCCOM_AUDITS_REQUEST = 0XAA,
    PCCOM_AUDITS_CLEAR = 0X55,
    PCCOM_PARAM_REQUEST = 0X5A,
    PCC0M_PARAM_SET = 0XA5,
    PCCOM_CHECK = 0XAF,
};

/**
 * \brief Enumération des états de la machine d'état de la communication.
 */
typedef enum
{
    STATE_PCCOMM_INIT,
    STATE_PCCOM_IDLE,
} PCCOMM_STATE;

/**
 * \brief Varialbe structure contenant les variables utilisées par le module.
 */
static struct
{
    PCCOMM_STATE state;
    TaskHandle_t handlePcCom;
} pcCom;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

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
    uint8_t byCheckAnswer = 0XFA;
    while(1)
    {
        switch(pcCom.state)
        {
            case STATE_PCCOMM_INIT:
                // <editor-fold desc="STATE_PCCOMM_INIT"> 
            {
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
                            setAuditState(AUDITS_STATE_SEND_TO_PC);
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
        xTaskCreate(vTaskPcComm, PCCOOM_TASK_NAME, PCCOM_TASK_STACK, NULL,
                    PCCOM_TASK_PRIORITY, &pcCom.handlePcCom);
    }
}
/**
 * @}
 */
/* *****************************************************************************
End of File
 */

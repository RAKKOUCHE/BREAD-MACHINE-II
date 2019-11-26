/** ***************************************************************************
 * \date 2019 11 08
 * 
 * \file mainboard2.c
 * 
 * \brief Ce fichier contient le code source pour le module principale de 
 * l'applicatin.
 * 
 * \details Ce fichier contient le code source du module principale de 
 * l'application. Il implémente la logique de la machine d'état de l'application 
 * et peut appeler les routines API des modules MPLAB Harmony du système, 
 * tels que les pilotes,  services système et middleware.  Toutefois, il
 *  n'appelle aucune des interfaces système (telles que les fonctions 
 * "Initialiser" et "Tâches") des modules du système ou  faire des suppositions 
 * sur le moment où ces fonctions sont exécutées s'appellent.  C'est de la 
 * responsabilité du système spécifique à la configuration fichiers.
 * 
 ******************************************************************************/

/*******************************************************************************
 *   MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    mainboard2.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "mainboard2.h"
/**
 * \addtogroup main
 * @{
 */
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the MAINBOARD2_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

static MAINBOARD2_DATA mainboard2Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Functions
// *****************************************************************************
// *****************************************************************************

/*********************************************************************
 * Function:        void vTO_OverPay(const TimerHandle_t HandleTimer)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    le handle mainBoardData.hTimerOverpayTO ou 
 *                  mainBoardData.hTimerCumul doit avoir été créé.
 *
 * Input:           HandleTimer non utilsée. Nécessaire pour le prototype du
 *                  callback.

 * Output:          None
 * 
 * Side Effects:    None
 *
 * Overview:        Si un montant a été inséré mais pas utilisé, il sera 
 *                  enregistré dans les trop perçus.
 *
 * Note:            None
 ********************************************************************/
void vTO_OverPay(const TimerHandle_t HandleTimer)
{
    setAuditValue(ADDRESSOVERPAY, getAmountDispo());
    setAmountDispo(0);
    setAmountRequested(0);
    setMainBoardTaskState(MAINBOARD2_STATE_DISPLAY_CHOICE);
}

/******************************************************************************/

/*********************************************************************
 * Function:        
 *         void vTO_Cumul(const TimerHandle_t handleTimer)
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/07/19
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

void vTO_Cumul(const TimerHandle_t handleTimer)
{
    setMainBoardTaskState(MAINBOARD2_STATE_CHANGE);
}

/*********************************************************************
 * Function:        
 *         MAINBOARD2_STATES getMainBoardTaskState(void)
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
MAINBOARD2_STATES getMainBoardTaskState(void)
{
    return mainboard2Data.state;
}

/*********************************************************************
 * Function:        
 *         void setMainBoardTaskState(MAINBOARD2_STATES state)
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
void setMainBoardTaskState(MAINBOARD2_STATES state)
{
    mainboard2Data.state = state;
}

/*********************************************************************
 * Function:        
 *         uint32_t GetAmountDispo(void)
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
int32_t getAmountDispo(void)
{
    return mainboard2Data.lAmountDispo;
}

/*********************************************************************
 * Function:        
 *         void setAmountRequested(uint32_t amount)
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
void setAmountRequested(uint32_t amount)
{
    mainboard2Data.lAmountRequested = amount;
}
// *****************************************************************************

/*********************************************************************
 * Function:        
 *         uint32_t GetAmountRequestedvoid)
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
int32_t getAmountRequested(void)
{
    return mainboard2Data.lAmountRequested;
}

/*********************************************************************
 * Function:        
 *         void setAmountDispo(uint32_t amount)
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
void setAmountDispo(uint32_t amount)
{
    mainboard2Data.lAmountDispo = amount;
}
// *****************************************************************************

/*********************************************************************
 * Function:        
 *         bool getMDBChecked(void)
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
bool getMDBChecked(void)
{
    return mainboard2Data.isMDBChecked;
}

/*********************************************************************
 * Function:        
 *         void setMDBChecked(bool isChecked)
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
void setMDBChecked(bool isChecked)
{
    mainboard2Data.isMDBChecked = isChecked;
}



// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void MAINBOARD2_Initialize ( void )

  Remarks:
    See prototype in mainboard2.h.
 */

void MAINBOARD2_Initialize(void)
{
    /* Place the App state machine in its initial state. */
    setMainBoardTaskState(MAINBOARD2_STATE_INIT);
    vParametersRead();
    vLCDInit();
    vAuditsInit();
    vDataInit();
    vMDBInit();


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void MAINBOARD2_Tasks ( void )

  Remarks:
    See prototype in mainboard2.h.
 */

void MAINBOARD2_Tasks(void)
{

    /* Check the application's current state. */
    switch(mainboard2Data.state)
    {
            /* Application's initial state. */
        case MAINBOARD2_STATE_INIT:
        {
            vHD44780Init();
            setMainBoardTaskState(MAINBOARD2_STATE_SERVICE_TASKS);
            vLCD_CLEAR();
            vDisplayLCD("%s", "MT DISTRIBUTION");
            vLCDGotoXY(1, 2);
            vDisplayLCD(" %s %s", "Version ", VERSION);
            delayMs(1 * SECONDE);
            vTaskResume(mdb.hTaskMdb);
            hTimerCumul = xTimerCreate("TO CUMUL", getTOCumul() * SECONDE, false, NULL, vTO_Cumul);
            break;
        }
        case MAINBOARD2_STATE_SERVICE_TASKS:
        {
            LED_SYS_Toggle();
            if(getIsRAZAudit())
            {
                setIsRAZAudit(false);
                //                mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_CHOICE;
            }
            break;
        }

        case MAINBOARD2_STATE_DISPLAY_CHOICE:
            // <editor-fold desc="MAINBOARD2_STATE_DISPLAY_CHOICE"> 
        {
            mainboard2Data.state = MAINBOARD2_STATE_SERVICE_TASKS;
            vLCD_CLEAR();
            vDisplayLCD("%s", "   Choisissez");
            vLCDGotoXY(1, 2);
            vDisplayLCD("%s", " votre produit");
            break;
        }// </editor-fold>
            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/**
 * @}
 */

/*******************************************************************************
 End of File
 */

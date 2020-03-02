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
 * "Initialiser" et "Tâches") des modules du système ou  faire des suppositions cumul
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
#include "contacts.h"
#include "MDB/mdb_bv.h"
#include "globaldef.h"
#include "moteurs.h"
#include "trap_security.h"

/**
 * \addtogroup main
 * @{
 */

/**
 * \brief Nom du timer de choix.
 */
#define CHOICE_TIMER_NAME "Choice tmr"

/**
 * \brief Temps d'affichage de la selection.
 */
#define CHOICE_TIMER_DELAY (20 * SECONDE)


const char STR_MANUFACTURER[] = "MT DISTRIBUTION ";
const char STR_VERSION[] = " VERSION";
const char STR_SELECT[] = "   Choisissez   ";
const char STR_YOUR_PRODUCT[] = "un produit  ";
const char STR_CREDIT[] = "Credit: ";
const char STR_DISPENSE[] = "  Distribution";
const char STR_IN_PROGRESS[] = "   en cours...";
const char STR_TO_PAY[] = "A payer:";
const char STR_TAKE[] = "     Prenez";
const char STR_YOUR_CHOICE[] = "   votre choix";
const char STR_RETURN_IN_PROGRESS[] = "Rendu en cours...";
const char STR_MACHINE[] = "    MACHINE     ";
const char STR_HS[] = "      VIDE      ";
const char STR_CHOICE[] = "Choix : ";
const char STR_PRICE[] = "Prix ";
const char STR_VERIFGSM[] = "Verification GSM";
const char STR_PATIENCE[] = "  Un instant...";

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
    setAuditValue(ADDRESSOVERPAY, getAmountDispo() + getAuditValue(ADDRESSOVERPAY));
    setAmountDispo(0);
    setAmountRequested(0);
    //setMainBoardTaskState(MAINBOARD2_STATE_DISPLAY_CHOICE);
}

/******************************************************************************/

/*********************************************************************
 * Function:        
 *         static void vTO_DisplaySelection(const TimerHandle_t handleTimer)
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
static void vTO_DisplaySelection(const TimerHandle_t handleTimer)
{
    clrSelection();
    mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_SELECT;
}

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
    vLEDsKeybInit();
    vKeyboardInit();
    vDS18B20Init();
    vMotorsInit();
    vADCInit();

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
    uint8_t byIndex;
    static uint32_t oldAmount = 0;
    static uint8_t oldChoice = 0;
    /* Check the application's current state. */
    switch(mainboard2Data.state)
    {
            /* Application's initial state. */
        case MAINBOARD2_STATE_INIT:
            // <editor-fold desc="MAINBOARD2_STATE_INIT"> 
        {
            oldAmount = 0;
            setAmountDispo(0);
            setMainBoardTaskState(MAINBOARD2_STATE_SERVICE_TASKS);
            vHD44780Init();
            vLCD_CLEAR();
            vDisplayLCD("%s", STR_MANUFACTURER);
            vLCDGotoXY(1, 2);
            vDisplayLCD(" %s %s", STR_VERSION, VERSION);
            delayMs(1 * SECONDE);
#ifndef __DEBUG
            delayMs(15 * SECONDE);
#endif 
            vTaskResume(getHandleMDB());
            if(hTimerOverPay == NULL)
            {
                hTimerOverPay = xTimerCreate("TO OVERPAY", getDelayOverpay() ?
                                             getDelayOverpay() * SECONDE :
                                             portMAX_DELAY,
                                             false, NULL, vTO_OverPay);
            }
            if(hTOCumul == NULL)
            {
                hTOCumul = xTimerCreate("TO CUMUL", getTOCumul() ?
                                        getTOCumul() * SECONDE :
                                        portMAX_DELAY,
                                        false, NULL, vTO_Cumul);
            }
            if(hTimerDisplaySelection == NULL)
            {
                hTimerDisplaySelection = xTimerCreate(CHOICE_TIMER_NAME,
                                                      CHOICE_TIMER_DELAY,
                                                      false, NULL,
                                                      vTO_DisplaySelection);
            }
            break;
        }// </editor-fold>
        case MAINBOARD2_STATE_SERVICE_TASKS:
            // <editor-fold desc="MAINBOARD2_STATE_SERVICE_TASKS">         
        {
            LED_SYS_Toggle();
            if(getIsRAZAudit())
            {
                setIsRAZAudit(false);
            }
            if(getIsMDBChecked() && !getAmountDispo() && (getTemp() > 0.0))
            {
                vLCDGotoXY(12, 2);
                vDisplayLCD("%.1f²", getTemp());
            }
            if(oldAmount != getAmountDispo())
            {
                mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_AMOUNT;
                if((oldAmount = getAmountDispo()) == 0)
                {
                    xTimerStop(hTimerOverPay, 1000);
                    xTimerStop(hTOCumul, 1000);
                }
            }
            if((getSelection() != oldChoice))
            {
                oldChoice = getSelection();
                if(!oldChoice)
                {
                    for(byIndex = 0; byIndex < 6; byIndex++)
                    {
                        if(getIsMotorInUse(byIndex))
                        {
                            setMotorState(byIndex, MOTORS_BREAK);
                            delayMs(200);
                            setMotorState(byIndex, MOTORS_OFF);
                        }
                    }
                }
                if(oldChoice && (oldChoice < 4))
                {
                    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
                    {
                        setLedState(byIndex, LED_OFF);
                    }
                    setLedState(oldChoice - 1, LED_ON);
                }
                if(oldChoice == 4)
                {
                    //Check du git du 5/1/2020
                    setShiftState(!getShiftState());
                }
#ifdef __DEBUG
                if(oldChoice > 4)
#else
                if(oldChoice > 4 && DOOR_Get())
#endif
                {
                    if(getShiftState())
                    {
                        setShiftState(true);
                        setMotorState(oldChoice - 2,
                                      (getLastDir(oldChoice - 2) == REVERSE) ?
                                      MOTORS_FORWARD :
                                      MOTORS_REVERSE);
                    }
                    else
                    {
                        setMotorState(oldChoice - 5, MOTORS_FORWARD);
                    }
                }
                if(getAmountDispo())
                {
                    mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_AMOUNT;
                }
                else
                {
                    if(oldChoice && (oldChoice < 4))
                    {
                        vLCD_CLEAR();
                        vDisplayLCD("%s%u", STR_CHOICE, oldChoice);
                        vLCDGotoXY(1, 2);
                        vDisplayLCD("%s %.*f\7", STR_PRICE, getMDBDecimalPos(),
                                    (double) getProductPrice(getSelection() - 1) / getMDBCurrencyDivider());
                        xTimerStart(hTimerDisplaySelection, 1000);
                    }
                }
            }
            if(getIsDoorMoved())
            {//La porte vient d'être fermée.
                clrIsDoorMoved();
                if(!DOOR_Get())
                {
                    //TODO test des trappes.
                    for(byIndex = 3; byIndex < 3 + PRODUCT_NUMBER; byIndex++)
                    {
                        setMotorState(byIndex, MOTORS_REVERSE);
                        while(getDoorSwitchState(byIndex - 2) != KEY_USED)
                        {
                            Nop();
                        }
                        setMotorState(byIndex, MOTORS_OFF);
                        delayMs(500 * MILLISEC);
                        setMotorState(byIndex, MOTORS_FORWARD);
                        while(getDoorSwitchState(byIndex + 1) != KEY_USED)
                        {
                            
                            //toto control de la consomation si la valeur est à zéro
                        }
                        setMotorState(byIndex, MOTORS_OFF);
                        //                        while(true)
                        //                        {
                        //
                        //                        }

                    }

                    //TODO vérication de la présence des produits
                }
                else
                {
                    //TODO Envoyer un sms.
                }
            }

            break;
        }// </editor-fold>
        case MAINBOARD2_STATE_DISPLAY_SELECT:
            // <editor-fold desc="MAINBOARD2_STATE_DISPLAY_CHOICE"> 
        {
            oldChoice = 0;
            mainboard2Data.state = MAINBOARD2_STATE_SERVICE_TASKS;
            vLCD_CLEAR();
            vDisplayLCD("%s", STR_SELECT);
            vLCDGotoXY(1, 2);
            vDisplayLCD("%s", STR_YOUR_PRODUCT);
            setLedChase(true);
            break;
        }// </editor-fold>
        case MAINBOARD2_STATE_DISPLAY_AMOUNT:
            // <editor-fold desc="MAINBOARD2_STATE_DISPLAY_AMOUNT"> 
        {
            mainboard2Data.state = getAmountDispo() ?
                    MAINBOARD2_STATE_SERVICE_TASKS :
                    MAINBOARD2_STATE_DISPLAY_SELECT;
            vLCD_CLEAR();
            vDisplayLCD("%s %.*f\7", STR_CREDIT, getMDBDecimalPos(),
                        (double) getAmountDispo() / getMDBCurrencyDivider());
            if(getSelection())
            {
                xTimerStop(hTimerDisplaySelection, 1000);
                vLCDGotoXY(1, 2);
                if(getAmountDispo() < getProductPrice((getSelection() - 1)))
                {
                    vDisplayLCD("%s %.*f\7", STR_TO_PAY, getMDBDecimalPos(),
                                (double) (getProductPrice(getSelection() - 1) -
                                          getAmountDispo()) / getMDBCurrencyDivider());
                }
            }
            break;
        }// </editor-fold>
        case MAINBOARD2_STATE_CHANGE:
            // <editor-fold desc="MAINBOARD2_STATE_CHANGE"> 
        {
            vLCD_CLEAR();

            vDisplayLCD("%s", STR_RETURN_IN_PROGRESS);


            setIsChangeFinished(false);
            xTaskNotifyGive(getChangeTaskHandle());
            while(!getIsChangeFinished());
            delayMs(1000); //Permet de visualiser la somme rendu.

            mainboard2Data.state = getAmountDispo() ?
                    MAINBOARD2_STATE_DISPLAY_AMOUNT :
                    MAINBOARD2_STATE_DISPLAY_SELECT;

            if(!BOT_1_Get() && !BOT_2_Get() && !BOT_3_Get())
            {
                setChangeGiverTaskState(CG_COIN_TYPE);
                setBV_State(BV_BILL_TYPE);
            }
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

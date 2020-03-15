/** ***************************************************************************
 * \date 2019 11 08
 *
 * \file MAINBOARD.c
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
    MAINBOARD.c

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

#include "mainboard.h"

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

/**
 * \brief
 */
#define DISPENSE_PRIORITY 1

/**
 * \brief
 */
#define DISPENSE_TASK_STACK 512


const char STR_MANUFACTURER[] = "MT DISTRIBUTION ";
const char STR_VERSION[] = " VERSION";
const char STR_SELECT[] = "   Choisissez   ";
const char STR_YOUR_PRODUCT[] = "un produit  ";
const char STR_CREDIT[] = "Credit : ";
const char STR_DISPENSE[] = "  Distribution";
const char STR_IN_PROGRESS[] = "   en cours...";
const char STR_TO_PAY[] = "A payer :";
const char STR_TAKE[] = "     Prenez";
const char STR_YOUR_CHOICE[] = "   votre choix";
const char STR_RETURN_IN_PROGRESS[] = "Rendu en cours...";
const char STR_MACHINE[] = "    MACHINE     ";
const char STR_HS[] = "      VIDE      ";
const char STR_CHOICE[] = "Choix : ";
const char STR_PRICE[] = "Prix";
const char STR_VERIFGSM[] = "Verification GSM";
const char STR_PATIENCE[] = "  Un instant...";


uint8_t doorSwitchTable[] = {2, 3, 4, 12, 13, 14, 15};

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
    This structure should be initialized by the MAINBOARD_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

static MAINBOARD_DATA MAINBOARDData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Functions
// *****************************************************************************
// *****************************************************************************

/*********************************************************************
 * Function:        static void setProductSelect(const uint8_t num)
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
static void setProductSelect(const uint8_t num)
{
    MAINBOARDData.byProductSelected = num;
}

/*********************************************************************
 * Function:        static uint8_t getProductSelect(void)
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
static uint8_t getProductSelect(void)
{
    return MAINBOARDData.byProductSelected;
}

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
static void vTO_OverPay(const TimerHandle_t HandleTimer)
{
    setAuditValue(ADDRESSOVERPAY, getAmountDispo() + getAuditValue(ADDRESSOVERPAY));
    setAmountDispo(0);
    setAmountRequested(0);
    //setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_CHOICE);
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
    setProductSelect(0);
    if(getAmountDispo() > 0)
    {
        setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
    }
    else
    {
        setAmountRequested(0);
        setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_SELECT);
    }
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
static void vTO_Cumul(const TimerHandle_t handleTimer)
{
    setMainBoardTaskState(MAINBOARD_STATE_CHANGE);
}

/*********************************************************************
 * Function:
 *         MAINBOARD_STATES getMainBoardTaskState(void)
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
static MAINBOARD_STATES getMainBoardTaskState(void)
{

    return MAINBOARDData.state;
}

/*********************************************************************
 * Function:        static void DispenseTask(void)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    La tâche doit avoir été créée par xTaskCreate
 *
 * Input:           la notification de la tâche
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Indique sur l'afficheur l'opération de distribution du pain.
 *                  Active le moteur de la trappe correspondant au choix pour
 *                  permettre la prise de la baguette.
 *                  Si la trappe est en fin de course, un message indique que
 *                  la prise du produit doit être effectuée.
 *                  Lorsque la baguette n'est plus détectée, la trappe redescend.
 *                  Autorise le retour de la monnaie si nécessaire.
 * 
 * Note:            None
 ********************************************************************/
static void vDispenseTask(void)
{
    char buffer[19];

    COIN_TYPE coinType;
    BILL_TYPE billType;
    while(1)
    {
        ulTaskNotifyTake(true, portMAX_DELAY);
        //Invalidation des moyens de paiement.
        coinType = getCoinType();
        billType = getBillType();
        isSetCoinEnable(false, &coinType);
        isSetBillEnable(false, &billType);
        vLCD_CLEAR();
        printf("%s", STR_DISPENSE);
        vLCDGotoXY(1, 2);
        printf("%s", STR_IN_PROGRESS);
        setMotorState(getProductSelect() + 2, MOTORS_REVERSE);
        xTimerStop(hTOCumul, 1 * SECONDE);
        vLCD_CLEAR();
        printf("%s", STR_TAKE);
        vLCDGotoXY(1, 2);
        printf("%s", STR_YOUR_CHOICE);
        while(getDoorSwitchState((getProductSelect() / 2) + 1) != KEY_USED);
        setMotorState(getProductSelect() + 2, MOTORS_BREAK);
        while((getOptoState((getProductSelect() - 1)* 2) != KEY_HI) || (getOptoState(((getProductSelect() - 1)* 2) + 1) != KEY_HI));
        setAmountDispo(getAmountDispo() - getAmountRequested());
        setMotorState(getProductSelect() + 2, MOTORS_FORWARD);
        while(getDoorSwitchState((getProductSelect() / 2) + 4) != KEY_USED);

        switch(getProductSelect())
        {
            default:
            {
                break;
            }
        }

        //        switch(
        //        {
        //            case 1:
        //            case 2:
        //            {
        //                vMotorStart(TRAP_1, FWD);
        //                do
        //                {
        //                    while(!clavier.isTaked[0] && SYS_PORTS_PinRead(TOP_1)); //Verifie si le pain a été pris ou si la trappe est arrivée en haut.
        //                    DelayMs(100); //100 ms pour l'anti-rebond.
        //                }while(!clavier.isTaked[0] && SYS_PORTS_PinRead(TOP_1)); //S'il s'agit d'un parasite on repete l'opération de vérification         
        //                vMotorBreak(TRAP_1); //Sinon on arrete le moteur.
        //                if(!SYS_PORTS_PinRead(TOP_1))//Si la trappe est complétement ouverte
        //                {
        //                    xTaskNotifyGive(mainBoardData.hDisplayTakeSelection); // on change le message pour demander au client de prendre son pain.
        //                }
        //                do
        //                {
        //                    clavier.isDelayBeforeCloseReached = false;
        //                    xTimerStart(clavier.hDelayBeforeClose, 1000);
        //                    while(!clavier.isDelayBeforeCloseReached);
        //
        //                }while(!clavier.isTaked[0]);
        //
        //                vMotorStart(TRAP_1, REW);
        //                while(SYS_PORTS_PinRead(BOTTOM_1));
        //                vMotorBreak(TRAP_1);
        //
        //                mainBoardData.isNotAutorized = false;
        //                xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
        //                vMotorStart(CONVOYEUR_1, FWD);
        //                while(clavier.isTaked[0] && !mainBoardData.isNotAutorized);
        //                vMotorBreak(CONVOYEUR_1);
        //                mainBoardData.isChoiceAuthorized[0] = mainBoardData.isChoiceAuthorized[1] = !mainBoardData.isNotAutorized;
        //                if(mainBoardData.isNotAutorized)
        //                {
        //                    sprintf(buffer, ConvoyerEmpty, 1);
        //                    vSendSMS(buffer);
        //                }
        //                break;
        //            }
        //            case 3:
        //            case 4:
        //            {
        //                vMotorStart(TRAP_2, FWD); //Démarrage de l'ouverture de la trap.
        //                do
        //                {
        //                    while(!clavier.isTaked[1] && SYS_PORTS_PinRead(TOP_2)); //Verifie si le pain a été pris ou si la trappe est arrivée en haut.
        //                    DelayMs(100); //100 ms pour l'anti-rebond.
        //                }while(!clavier.isTaked[1] && SYS_PORTS_PinRead(TOP_2)); //S'il s'agit d'un parasite on repete l'opération de vérification         
        //                vMotorBreak(TRAP_2); //Sinon on arrete le moteur.
        //                if(!SYS_PORTS_PinRead(TOP_2))//Si la trappe est complétement ouverte
        //                {
        //                    xTaskNotifyGive(mainBoardData.hDisplayTakeSelection); // on change le message pour demander au client de prendre son pain.
        //                }
        //                do
        //                {
        //                    clavier.isDelayBeforeCloseReached = false;
        //                    xTimerStart(clavier.hDelayBeforeClose, 1000);
        //                    while(!clavier.isDelayBeforeCloseReached);
        //
        //                }while(!clavier.isTaked[1]);
        //
        //                vMotorStart(TRAP_2, REW);
        //                while(SYS_PORTS_PinRead(BOTTOM_2));
        //                vMotorBreak(TRAP_2);
        //
        //                mainBoardData.isNotAutorized = false;
        //                xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
        //                vMotorStart(CONVOYEUR_2, FWD);
        //                while(clavier.isTaked[1] && !mainBoardData.isNotAutorized);
        //                vMotorBreak(CONVOYEUR_2);
        //                mainBoardData.isChoiceAuthorized[2] = mainBoardData.isChoiceAuthorized[3] = !mainBoardData.isNotAutorized;
        //                if(mainBoardData.isNotAutorized)
        //                {
        //                    sprintf(buffer, ConvoyerEmpty, 2);
        //                    vSendSMS(buffer);
        //                }
        //                xTimerStop(mainBoardData.hTimerCheckAutorized, 1000);
        //                break;
        //            }
        //            case 5:
        //            case 6:
        //            {
        //                vMotorStart(TRAP_3, FWD);
        //                do
        //                {
        //                    while(!clavier.isTaked[2] && SYS_PORTS_PinRead(TOP_3)); //Verifie si le pain a été pris ou si la trappe est arrivée en haut.
        //                    DelayMs(100); //100 ms pour l'anti-rebond.
        //                }while(!clavier.isTaked[2] && SYS_PORTS_PinRead(TOP_3)); //S'il s'agit d'un parasite on repete l'opération de vérification         
        //                vMotorBreak(TRAP_3); //Sinon on arrete le moteur.
        //                if(!SYS_PORTS_PinRead(TOP_3))//Si la trappe est complétement ouverte
        //                {
        //                    xTaskNotifyGive(mainBoardData.hDisplayTakeSelection); // on change le message pour demander au client de prendre son pain.
        //                }
        //                do
        //                {
        //                    clavier.isDelayBeforeCloseReached = false;
        //                    xTimerStart(clavier.hDelayBeforeClose, 1000);
        //                    while(!clavier.isDelayBeforeCloseReached);
        //
        //                }while(!clavier.isTaked[2]);
        //
        //                vMotorStart(TRAP_3, REW);
        //                while(SYS_PORTS_PinRead(BOTTOM_3));
        //                vMotorBreak(TRAP_3);
        //
        //                mainBoardData.isNotAutorized = false;
        //                xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
        //                vMotorStart(CONVOYEUR_3, FWD);
        //                while(clavier.isTaked[2] && !mainBoardData.isNotAutorized);
        //                vMotorBreak(CONVOYEUR_3);
        //                mainBoardData.isChoiceAuthorized[4] = mainBoardData.isChoiceAuthorized[5] = !mainBoardData.isNotAutorized;
        //                if(mainBoardData.isNotAutorized)
        //                {
        //                    sprintf(buffer, ConvoyerEmpty, 3);
        //                    vSendSMS(buffer);
        //                }
        //                xTimerStop(mainBoardData.hTimerCheckAutorized, 1000);
        //                break;
        //            }
        //            default:
        //            {
        //                break;
        //            }
        //        }
        //        ++audits.saudit.dwProduit[--clavier.keyInUse];
        //        EEpromWriteData(ADDRESS_PRODUIT + (clavier.keyInUse *
        //                                           sizeof(audits.saudit.dwProduit[clavier.keyInUse])),
        //                        &audits.saudit.dwProduit[clavier.keyInUse],
        //                        sizeof(audits.saudit.dwProduit[clavier.keyInUse]));
        //        clavier.keyInUse = 0XFF;
        //        leds.isMainBoardIdle = true;
        //        mainBoardData.state = (mainBoardData.lAmountCashDispo -= mainBoardData.lAmountRequested) ?
        //            MAINBOARD_STATE_CHANGE : MAINBOARD_STATE_DISPLAY_SELECT;
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:        static  uint8_t getProductSelected(void)
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

/*********************************************************************
 * Function:
 *         void setMainBoardTaskState(MAINBOARD_STATES state)
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
void setMainBoardTaskState(MAINBOARD_STATES state)
{

    MAINBOARDData.state = state;
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

    return MAINBOARDData.lAmountDispo;
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

    MAINBOARDData.lAmountRequested = amount;
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

    return MAINBOARDData.lAmountRequested;
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

    MAINBOARDData.lAmountDispo = amount;
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
void MAINBOARD_Initialize ( void )

Remarks:
See prototype in MAINBOARD.h.
 */

void MAINBOARD_Initialize(void)
{

    /* Place the App state machine in its initial state. */
    setMainBoardTaskState(MAINBOARD_STATE_INIT);
    vParametersRead();
    vLCDInit();
    vEEpromInit();
    vAuditsInit();
    vDataInit();
    vMDBInit();
    vLEDsKeybInit();
    vKeyboardInit();
    vDS18B20Init();
    vMotorsInit();
    //TODO à vérifier
    vADCInit();

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
Function:
void MAINBOARD_Tasks ( void )

Remarks:
See prototype in MAINBOARD.h.
 */

void MAINBOARD_Tasks(void)
{
    uint8_t byIndex;
    static uint32_t oldAmount = 0;
    static uint8_t oldChoice = 0;

    /* Check the application's current state. */
    switch(getMainBoardTaskState())
    {
            /* Application's initial state. */
        case MAINBOARD_STATE_INIT:
            // <editor-fold desc="MAINBOARD_STATE_INIT">
        {
            setMainBoardTaskState(MAINBOARD_STATE_SERVICE_TASKS);
            oldAmount = 0;
            setAmountDispo(0);


            vHD44780Init();
            vDisplayLCD("%s", STR_MANUFACTURER);
            vLCDGotoXY(1, 2);
            vDisplayLCD(" %s %s", STR_VERSION, VERSION);
            delayMs(1 * SECONDE);
#ifndef __DEBUG
            delayMs(15 * SECONDE);
#endif
            vTaskResume(getHandleMDB());
            xTaskCreate((TaskFunction_t) vDispenseTask, "TSK DISPENSE",
                        DISPENSE_TASK_STACK, NULL, DISPENSE_PRIORITY,
                        &MAINBOARDData.hDispenseTask);

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
        case MAINBOARD_STATE_SERVICE_TASKS:
            // <editor-fold desc="MAINBOARD_STATE_SERVICE_TASKS">
        {
            if(getIsTaskKeyChecked() && getIsMotorChecked())
            {
                setIsTaskKeyChecked(false);
                setIsMotorChecked(false);
                LED_SYS_Toggle();
            }

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
                setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
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
                        }
                    }
                }
                if(oldChoice && (oldChoice < 4))
                {
                    setMainBoardTaskState(MAINBOARD_STATE_CHECK_DISPENSE);
                    setProductSelect(oldChoice);
                    setSelectedLed(oldChoice);
                    setAmountRequested(getProductPrice(getProductSelect() - 1));
                }
                if(oldChoice == 4)
                {
                    shiftStateToggle();
                }
                if(oldChoice > 4)
                {
                    if(getShiftState())
                    {
                        setShiftState(true);
                        if(!(PORTC & (1 << doorSwitchTable[oldChoice - 4])))
                        {
                            setLastDir(oldChoice - 2, REVERSE);
                        }
                        else
                        {
                            if(!(PORTC & (1 << doorSwitchTable[oldChoice - 1])))
                            {
                                setLastDir(oldChoice - 2, FORWARD);
                            }
                        }
                        setMotorState(oldChoice - 2,
                                      (getLastDir(oldChoice - 2) == FORWARD) ?
                                      MOTORS_REVERSE : MOTORS_FORWARD);
                    }
                    else
                    {
                        setMotorState(oldChoice - 5, MOTORS_FORWARD);
                    }
                }
                if(getAmountDispo())
                {
                    setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
                }
                else
                {
                    if(oldChoice && (oldChoice < 4))
                    {
                        vLCD_CLEAR();
                        vDisplayLCD("%s%u", STR_CHOICE, oldChoice);
                        vLCDGotoXY(1, 2);
                        vDisplayLCD("%s %.*f\7", STR_PRICE, getMDBDecimalPos(),
                                    (double) getProductPrice(oldChoice - 1) / getMDBCurrencyDivider());
                        xTimerStart(hTimerDisplaySelection, 1000);
                    }
                }
            }
            break;
        }// </editor-fold>
        case MAINBOARD_STATE_DISPLAY_SELECT:
            // <editor-fold desc="MAINBOARD_STATE_DISPLAY_CHOICE">
        {
            oldChoice = 0;
            setMainBoardTaskState(MAINBOARD_STATE_SERVICE_TASKS);
            vLCD_CLEAR();
            vDisplayLCD("%s", STR_SELECT);
            vLCDGotoXY(1, 2);
            vDisplayLCD("%s", STR_YOUR_PRODUCT);
            setLedChase(true);
            break;
        }// </editor-fold>
        case MAINBOARD_STATE_DISPLAY_AMOUNT:
            // <editor-fold desc="MAINBOARD_STATE_DISPLAY_AMOUNT">
        {
            //            setMainBoardTaskState( getAmountDispo() ?
            //                    MAINBOARD_STATE_SERVICE_TASKS :
            setMainBoardTaskState(MAINBOARD_STATE_CHECK_DISPENSE);
            //                    MAINBOARD_STATE_DISPLAY_SELECT;
            vLCD_CLEAR();
            vDisplayLCD("%s %.*f\7", STR_CREDIT, getMDBDecimalPos(),
                        (double) getAmountDispo() / getMDBCurrencyDivider());
            if(getProductSelect())
            {
                xTimerStop(hTimerDisplaySelection, 1000);
                vLCDGotoXY(1, 2);
                if(getAmountDispo() < getProductPrice(getProductSelect() - 1))
                {
                    vDisplayLCD("%s %.*f\7", STR_TO_PAY, getMDBDecimalPos(),
                                (double) (getProductPrice(getProductSelect() - 1) -
                                          getAmountDispo()) / getMDBCurrencyDivider());
                }
            }
            break;
        }// </editor-fold>
        case MAINBOARD_STATE_CHECK_DISPENSE:
            // <editor-fold desc="MAINBOARD_STATE_CHECK_DISPENSE"> 
        {
            if(getAmountRequested() && (getAmountDispo() >= getAmountRequested()))
            {
                xTaskNotifyGive(MAINBOARDData.hDispenseTask);
            }
            setMainBoardTaskState(MAINBOARD_STATE_SERVICE_TASKS);
            break;
        }// </editor-fold>
        case MAINBOARD_STATE_CHANGE:
            // <editor-fold desc="MAINBOARD_STATE_CHANGE">
        {
            vLCD_CLEAR();
            vDisplayLCD("%s", STR_RETURN_IN_PROGRESS);
            setIsChangeFinished(false);
            xTaskNotifyGive(getChangeTaskHandle());
            while(!getIsChangeFinished());
            delayMs(1000); //Permet de visualiser la somme rendu.
            setMainBoardTaskState(getAmountDispo() ?
                                  MAINBOARD_STATE_DISPLAY_AMOUNT :
                                  MAINBOARD_STATE_DISPLAY_SELECT);

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

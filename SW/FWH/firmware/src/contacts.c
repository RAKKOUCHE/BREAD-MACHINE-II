/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 08
 *
 * \file clavier.c
 *
 * \brief Fichier source de la gestion des touches.
 *
 * \details Ce fichier fournit les fonctions et les définitions utilisés par le
 *  programme pour gérer les les touches.
 *
 ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "contacts.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/**
 * \brief
 */
#define CHK_TASK_NAME "TSK CHK DISPENSE"

/**
 * \brief
 */
#define CHK_TASK_PRIORITY 3

/**
 * \brief
 */
#define CHK_TASK_STACK 512

/**
 * \brief
 */
#define DOOR_CLOSE_TIME_NAME "TMR CLOSE DOOR"

/**
 * \brief
 */
#define DOOR_TRAP_DELAY (10 * SECONDE)

/**
 * \brief
 */
#define DETECT_PRODUCT_DELAY (15 * SECONDE)

/**
 * \brief Nom en clair de la gestion des touches du clavier.
 */
#define CLAVIER_TASK_NAME "TSK KBD"

/**
 * \brief Priority de la tâche dy clavier.
 */
#define CLAVIER_TASK_PRIORITY 4

/**
 * \brief Profondeur de la pile
 */
#define CLAVIER_TASK_STACK 512

/**
 * \brief Delay de la tâche des touches.
 */
#define CLAVIER_TASK_DELAY (30 * MILLISEC)

/**
 * \brief
 */
#define SHIFT_TIMER_NAME "Shift TO"

/**
 * \brief
 */
#define SHIFT_TIMER_DELAY (10 * SECONDE)

/**
 * \brief structure contenant les variables d'une  touche.
 */
typedef struct
{
    KEY_STATES state;
} KEY;

/**
 * \brief Structure contenant les variables du clavierss
 */
struct
{
    bool isDoorOpen; /*!<Indique si la porte est ouverte.*/
    bool isTaskKeyChecked; /*!<Indique si le tâche de vérification des  touches est effectuée.*/
    bool isKeyShifted; /*!<Indique si les touches alternatives sont activées.*/
    bool isDoorTOReached; /*!<Indique si un time out pour la porte est atteint.*/
    uint8_t selection; /*!<Numéro du choix en cours.*/
    KEY keys[7]; /*!<Etat des touches du claviers.*/
    KEY door_switches[7]; /*!<Etat des contacts de la porte.*/
    KEY opto[6]; /*!<Etat des opto coupleurs*/
    TaskHandle_t hSwitchTask; /*!<Tâche de la gestion des touches.*/
    TaskHandle_t hCheckProductDispo; /*!<Tâche de la gestion de la fermeture de la porte.*/
    TimerHandle_t hShiftTO; /*!<*!Delais de maintient de la touche shift.*/
    TimerHandle_t hTimerPresenceProduct;
} switchs;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/**
 * \brief
 */
uint8_t trapSwitchsTable[] = {2, 3, 4, 12, 13, 14, 15};

/**
 * \brief
 */
uint8_t optosTable[] = {10, 11, 12, 13, 2, 3};

/*********************************************************************
 * Function:        static void vTOProductPresent(TimerHandle_t xTimer)
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
static void vTOProductPresent(TimerHandle_t xTimer)
{
    switchs.isDoorTOReached = true;
}

/*********************************************************************
 * Function:        void DoorClosed(void)
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
static void vTaskCheckProductDispo(void)
{
    uint8_t byIndex;

    while(true)
    {
        ulTaskNotifyTake(true, portMAX_DELAY);
        for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
        {
            if(getIsProductSelectable(byIndex))
            {
                switchs.isDoorTOReached = false;
                if(getDoorSwitchState(byIndex + 4) != KEY_USED)
                {
                    vLCD_CLEAR();
                    vLCD_CLEAR();
                    printf("%s%u", "FERMETURE TRAP ", byIndex + 1);
                    delayMs(100);
                    xTimerChangePeriod(switchs.hTimerPresenceProduct,
                                       DOOR_TRAP_DELAY, 1 * SECONDE);
                    setMotorState(byIndex + 3, MOTORS_FORWARD);
                    do
                    {
                        while((getDoorSwitchState(byIndex + 4) != KEY_USED) &&
                              !switchs.isDoorTOReached);
                        delayMs(10);
                    }while((getDoorSwitchState(byIndex + 4) != KEY_USED) &&
                           !switchs.isDoorTOReached);
                }
                xTimerStop(switchs.hTimerPresenceProduct, 1 * SECONDE);
                setMotorState(byIndex + 3, MOTORS_BREAK);
                while(getMotorState(byIndex + 3) != MOTORS_IDLE);

                if((getOptoState(byIndex * 2) == KEY_HI) &&
                   (getOptoState((byIndex * 2) + 1) == KEY_HI))
                {
                    xTimerChangePeriod(switchs.hTimerPresenceProduct,
                                       DETECT_PRODUCT_DELAY, 1 * SECONDE);
                    setMotorState(byIndex, MOTORS_FORWARD);
                    while((getOptoState(byIndex * 2) == KEY_HI) &&
                          (getOptoState((byIndex * 2) + 1) == KEY_HI) &&
                          !switchs.isDoorTOReached);
                }
                setMotorState(byIndex, MOTORS_BREAK);
                while(getMotorState(byIndex) != MOTORS_IDLE);
                xTimerStop(switchs.hTimerPresenceProduct, 1 * SECONDE);
                setIsProductSelectable(byIndex, !switchs.isDoorTOReached);
            }
        }
        setAmountRequested(0);
        setMainBoardTaskState(getAmountDispo() ? MAINBOARD_STATE_DISPLAY_AMOUNT :
                              MAINBOARD_STATE_DISPLAY_SELECT);
    }

    //    EMOTOR pxIndex;
    //
    //    BYTE byIndex;
    //    char buffer[19] = {0};
    //
    //    for(byIndex = 0; byIndex < 3; byIndex++)
    //    {
    //        clavier.isTaked[byIndex] = (BYTE)SYS_PORTS_PinRead(OPTOPORT, PORTS_BIT_POS_13 + byIndex);
    //    }
    //
    //    for(pxIndex = CONVOYEUR_1; pxIndex < NUMMOTORS; pxIndex++)
    //    {
    //        moteurs.moteur[pxIndex].state = MTR_CHECK;
    //    };
    //
    //    xSemaphoreTake(moteurs.semaphoreHatchChecked, 60 * SECONDE);
    //    DelayMs(100); //Pour laisser le temps à l'affichage.
    //    LCD_Clear();
    //    printf("%s", POSITIONNEMENT);
    //    LCDGotoXY(1, 2);
    //    printf("   %s ", CONVOYEUR);
    //
    //    if(!SYS_PORTS_PinRead(BOTTOM_1))
    //    {
    //        printf("%s", "1");
    //        mainBoardData.isNotAutorized = false;
    //        xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
    //        vMotorStart(CONVOYEUR_1, FWD);
    //        while(clavier.isTaked[0] && !mainBoardData.isNotAutorized);
    //        vMotorBreak(CONVOYEUR_1);
    //        mainBoardData.isChoiceAuthorized[0] = mainBoardData.isChoiceAuthorized[1] = !mainBoardData.isNotAutorized;
    //        if(mainBoardData.isNotAutorized)
    //        {
    //            sprintf(buffer, ConvoyerEmpty, 1);
    //            vSendSMS(buffer);
    //            DelayMs(1000);
    //        }
    //        xTimerStop(mainBoardData.hTimerCheckAutorized, 1000);
    //    }
    //    else
    //    {
    //        mainBoardData.isChoiceAuthorized[0] = mainBoardData.isChoiceAuthorized[1] = false;
    //    }
    //
    //    if(!SYS_PORTS_PinRead(BOTTOM_2))
    //    {
    //        LCDGotoXY(14, 2);
    //        printf("%s", "2");
    //        mainBoardData.isNotAutorized = false;
    //        xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
    //        vMotorStart(CONVOYEUR_2, FWD);
    //        while(clavier.isTaked[1] && !mainBoardData.isNotAutorized);
    //        vMotorBreak(CONVOYEUR_2);
    //        mainBoardData.isChoiceAuthorized[2] = mainBoardData.isChoiceAuthorized[3] = !mainBoardData.isNotAutorized;
    //        if(mainBoardData.isNotAutorized)
    //        {
    //            sprintf(buffer, ConvoyerEmpty, 2);
    //            vSendSMS(buffer);
    //            DelayMs(1000);
    //        }
    //        xTimerStop(mainBoardData.hTimerCheckAutorized, 1000);
    //    }
    //    else
    //    {
    //        mainBoardData.isChoiceAuthorized[2] = mainBoardData.isChoiceAuthorized[3] = false;
    //    }
    //
    //    if(!SYS_PORTS_PinRead(BOTTOM_3))
    //    {
    //        LCDGotoXY(14, 2);
    //        printf("%s", "3");
    //        mainBoardData.isNotAutorized = false;
    //        xTimerStart(mainBoardData.hTimerCheckAutorized, 1000);
    //        vMotorStart(CONVOYEUR_3, FWD);
    //        while(clavier.isTaked[2] && !mainBoardData.isNotAutorized);
    //        vMotorBreak(CONVOYEUR_3);
    //        mainBoardData.isChoiceAuthorized[4] = mainBoardData.isChoiceAuthorized[5] = !mainBoardData.isNotAutorized;
    //        if(mainBoardData.isNotAutorized)
    //        {
    //            sprintf(buffer, ConvoyerEmpty, 3);
    //            vSendSMS(buffer);
    //            DelayMs(1000);
    //        }
    //        xTimerStop(mainBoardData.hTimerCheckAutorized, 1000);
    //    }
    //    else
    //    {
    //        mainBoardData.isChoiceAuthorized[4] = mainBoardData.isChoiceAuthorized[5] = false;
    //    }
    //    clavier.isDOORClosed = true;
}

/******************************************************************************/

/*********************************************************************
 * Function:
 *         static void vShift_TO(const TimerHandle_t HandleTimer)
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
static void vShift_TO(const TimerHandle_t HandleTimer)
{
    switchs.isKeyShifted = false;
}

/*********************************************************************
 * Function:
 *         static void setKeyState(const uint8_t numKey, const KEY_STATES state)
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
static void setKeyState(const uint8_t numKey, const KEY_STATES state)
{
    switchs.keys[numKey].state = state;
}

/*********************************************************************
 * Function:
 *         void setDoorSwitchState( const uint8_t byIndex, const KEY_STATES state)
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
static void setDoorSwitchState(const uint8_t byIndex, const KEY_STATES state)
{
    switchs.door_switches[byIndex].state = state;
}

/*********************************************************************
 * Function:        static void setOptoState(const uint8_t byIndex, const KEY_STATE state)
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
static void setOptoState(const uint8_t byIndex, const KEY_STATES state)
{
    switchs.opto[byIndex].state = state;
}

/*********************************************************************
 * Function:
 *         KEYSTATES getKeyState(const uint8_t numKey)
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
static KEY_STATES getKeyState(const uint8_t numKey)
{
    return switchs.keys[numKey].state;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */

/*********************************************************************
 * Function:
 *         static void vTaskKeyboard(void *vParameter)
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
static void vTaskKeyboard(void *vParameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8_t byIndex, byIndex2;
    KEY_STATES lkState;
    KEY_STATES lSWState;
    KEY_STATES lOptoState;

    if(!DOOR_Get())
    {
        setDoorSwitchState(0, KEY_USED); //Pour éviter une opération de test quand le courant est coupé et la porte fermée.
    }
    while(1)
    {
        if(getIsMDBChecked())
        {
            setIsTaskKeyChecked(true);

            for(byIndex = 0; byIndex < 7; byIndex++)
            {
                if(byIndex < 3)
                {
                    //Clavier
                    lkState = (KEY_STATES)((PORTD >> (7 + byIndex) & 1));
                }
                else
                {

                    lkState = (KEY_STATES)((PORTE >> byIndex) & 1);
                }
                lSWState = (KEY_STATES)((PORTC >> trapSwitchsTable[byIndex]) & 1);

                // <editor-fold defaultstate="collapsed" desc="OPTOCOUPLEURS">
                if(byIndex < 6)
                {
                    lOptoState = (KEY_STATES)((PORTD >> optosTable[byIndex]) & 1);

                    switch(getOptoState(byIndex))
                    {
                        case KEY_HI:
                            // <editor-fold desc="KEY_HI">
                        {
                            setOptoState(byIndex, lOptoState);
                            break;
                        }// </editor-fold>
                        case KEY_LO:
                            // <editor-fold desc="KEY_LO">
                        {
                            setOptoState(byIndex, lOptoState == KEY_LO ? KEY_CHECKED : KEY_HI);
                            break;
                        }// </editor-fold>
                        case KEY_CHECKED:
                            // <editor-fold desc="KEY_CHECKED">
                        {
                            setMotorState(byIndex / 2, MOTORS_BREAK);
                            setOptoState(byIndex, (lOptoState == KEY_LO) ? KEY_USED : KEY_HI);
                            break;
                        }// </editor-fold>
                        case KEY_USED:
                            // <editor-fold desc="KEY_USED">
                        {
                            if(lOptoState == KEY_HI)
                            {
                                setOptoState(byIndex, KEY_HI);
                            }
                            break;
                        }// </editor-fold>
                        default:
                        {
                            break;
                        }
                    }
                }// </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="FIN DE COURSE DES TRAPPES ET CONTACT DE PORTE">
                switch(getDoorSwitchState(byIndex))
                {
                    case KEY_HI:
                        // <editor-fold desc="KEY_HI">
                    {
                        setDoorSwitchState(byIndex, lSWState);
                        if(!byIndex)
                        {
                            setIsDoorOpen(true);
                        }
                        break;
                    }// </editor-fold>
                    case KEY_LO:
                        // <editor-fold desc="KEY_LO">
                    {
                        setDoorSwitchState(byIndex, lSWState == KEY_LO ? KEY_CHECKED : KEY_HI);
                        break;
                    }// </editor-fold>
                    case KEY_CHECKED:
                        // <editor-fold desc="KEY_CHECKED">
                    {
                        if(byIndex)
                        {
                            setMotorState((byIndex + 2) - ((uint8_t)(byIndex > 3) * 3), MOTORS_BREAK);
                            switchs.selection = 0;
                        }
                        setDoorSwitchState(byIndex, (lSWState == KEY_LO) ? KEY_USED : KEY_HI);
                        if(!byIndex)
                        {
                            setMainBoardTaskState((MAINBOARD_STATE_IDLE));
                            vLCD_CLEAR();
                            printf("%s", "FERMETURE PORTE");
                            for(byIndex2 = 0; byIndex2 < PRODUCT_NUMBER; byIndex2++)
                            {
                                setIsProductSelectable(byIndex2, true);
                            }

                            setIsDoorOpen(false);
                            delayMs(50);
                            xTaskNotifyGive(switchs.hCheckProductDispo);
                        }
                        break;
                    }// </editor-fold>
                    case KEY_USED:
                        // <editor-fold desc="KEY_USED">
                    {
                        if(lSWState == KEY_HI)
                        {
                            setDoorSwitchState(byIndex, KEY_HI);
                            if(!byIndex)
                            {
                                vLCD_CLEAR();
                                delayMs(50);
                                printf(" PORTE OUVERTE");
                                //delayMs(50);
                            }
                        }
                        break;
                    }// </editor-fold>
                    default:
                    {
                        break;
                    }
                }// </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="CLAVIER ET COMMANDES MOTEUR ONBOARD">
                if(((byIndex < 3) && getIsProductSelectable(byIndex)) || getIsDoorOpen())
                {
                    switch(getKeyState(byIndex))
                    {
                        case KEY_HI:
                            // <editor-fold desc="KEY_HI">
                        {
                            setKeyState(byIndex, lkState);
                            break;
                        }// </editor-fold>
                        case KEY_LO:
                            // <editor-fold desc="KEY_LO">
                        {
                            setKeyState(byIndex, lkState == KEY_LO ? KEY_CHECKED : KEY_HI);
                            break;
                        }// </editor-fold>
                        case KEY_CHECKED:
                            // <editor-fold desc="KEY_CHECKED">
                        {
                            if(lkState == KEY_LO)
                            {
                                switchs.selection = byIndex + 1;
                                setKeyState(byIndex, KEY_USED);
                            }
                            else
                            {
                                setKeyState(byIndex, KEY_HI);
                            }
                            break;
                        }// </editor-fold>
                        case KEY_USED:
                            // <editor-fold desc="KEY_USED">
                        {
                            if(lkState == KEY_HI)
                            {
                                setKeyState(byIndex, KEY_HI);
                                switchs.selection = 0;
                            }
                            break;
                        }// </editor-fold>
                        default:
                        {

                            break;
                        }
                    }
                }// </editor-fold>
            }
        }
        vTaskDelayUntil(&xLastWakeTime, CLAVIER_TASK_DELAY);
    }
}

/*********************************************************************
 * Function:        TaskHandle_t getHandleProductDispo(void)
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
TaskHandle_t getHandleProductDispo(void)
{
    return switchs.hCheckProductDispo;
}

/*********************************************************************
 * Function:        bool getIsDoorOpen()
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
BOOL getIsDoorOpen()
{
    return switchs.isDoorOpen;
}

/*********************************************************************
 * Function:        void setIsDoorOpen(bool status)
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
void setIsDoorOpen(const BOOL status)
{
    switchs.isDoorOpen = status;
}

/*********************************************************************
 * Function:        BOOL getIsTaskKeyChecked(void)
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
BOOL getIsTaskKeyChecked(void)
{
    return switchs.isTaskKeyChecked;
}

/*********************************************************************
 * Function:        void setIsTaskKeyChecked(BOOL status)
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
void setIsTaskKeyChecked(BOOL status)
{
    switchs.isTaskKeyChecked = status;
}

/*********************************************************************
 * Function:
 *         KEY_STATES getDoorSwitchState (const uint8_t byIndex)
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
KEY_STATES getDoorSwitchState(const uint8_t byIndex)
{
    return switchs.door_switches[byIndex].state;
}

/*********************************************************************
 * Function:        KEY_STATES getOptoState(const uint8_t byIndex)
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
KEY_STATES getOptoState(const uint8_t byIndex)
{
    return switchs.opto[byIndex].state;
}

/*********************************************************************
 * Function:
 *         void setShiftState(bool state)
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
void setShiftState(const bool state)
{
    (switchs.isKeyShifted = state) ?
            xTimerStart(switchs.hShiftTO, 1000) :
            xTimerStop(switchs.hShiftTO, 1000);
}

/*********************************************************************
 * Function:
 *         bool getShiftState(void)
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
bool getShiftState(void)
{
    return switchs.isKeyShifted;
}

/*********************************************************************
 * Function:        void shiftStateToggle(void
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
void shiftStateToggle(void)
{
    switchs.isKeyShifted = !switchs.isKeyShifted;
}

/*********************************************************************
 * Function:
 *         uint8_t getSelection()
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
uint8_t getSelection()
{
    return switchs.selection;
}

/*********************************************************************
 * Function:
 *         void vKeyboardInit()
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
void vKeyboardInit(void)
{
    uint8_t byIndex;
    switchs.selection = 0;
    switchs.isKeyShifted = false;
    setIsDoorOpen(DOOR_Get());
    switchs.isTaskKeyChecked = false;
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        setKeyState(byIndex, (KEY_STATES)(PORTD >> (7 + byIndex) & 1));
        setIsProductSelectable(byIndex, true);
    }
    for(; byIndex < 7; byIndex++)
    {
        setKeyState(byIndex, (KEY_STATES)(PORTE >> byIndex) & 1);
    }
    for(byIndex = 0; byIndex < 7; byIndex++)
    {
        setDoorSwitchState(byIndex, (KEY_STATES)(PORTC >> (trapSwitchsTable[byIndex]) & 1));
    }
    if(switchs.hSwitchTask == NULL)
    {
        xTaskCreate((TaskFunction_t)vTaskKeyboard, CLAVIER_TASK_NAME, CLAVIER_TASK_STACK, NULL, CLAVIER_TASK_PRIORITY, &switchs.hSwitchTask);
    }
    if(switchs.hCheckProductDispo == NULL)
    {
        xTaskCreate((TaskFunction_t)vTaskCheckProductDispo, CHK_TASK_NAME,
                    CHK_TASK_STACK, NULL, CHK_TASK_PRIORITY,
                    &switchs.hCheckProductDispo);
    }
    if(switchs.hShiftTO == NULL)
    {
        switchs.hShiftTO = xTimerCreate(SHIFT_TIMER_NAME, 10 * SECONDE, pdFALSE, NULL, vShift_TO);
    }
    if(switchs.hTimerPresenceProduct == NULL)
    {
        switchs.hTimerPresenceProduct = xTimerCreate(DOOR_CLOSE_TIME_NAME,
                                                     DOOR_TRAP_DELAY, pdFALSE,
                                                     NULL, vTOProductPresent);
    }
}

/******************************************************************************
End of File
 */

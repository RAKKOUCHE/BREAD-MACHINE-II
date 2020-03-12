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
#define CLAVIER_TASK_STACK 1024

/**
 * \brief Delay de la tâche des touches.
 */
#define CLAVIER_TASK_DELAY (10 * MILLISEC)

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
    bool isDoorMoved; /*!<Indique si la porter vient d'être ouverte ou fermée.*/
    bool isKeyShifted; /*!<Indique si les touches alternatives sont activées.*/
    uint8_t selection; /*!<Numéro du choix en cours.*/
    KEY keys[7]; /*!<Etat des touches du claviers.*/
    KEY door_switches[7]; /*!<Etat des contacts de la porte.*/
    KEY opto[6]; /*!<Etat des opto coupleurs*/
    TaskHandle_t hSwitchTask; /*!<Tâche de la gestion des touches.*/
    TimerHandle_t hShiftTO; /*!<*!Delais de maintient de la touche shift.*/
} switchs;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
uint8_t trapSwitchsTable[] = {2, 3, 4, 12, 13, 14, 15};
//
/**
 * \brief
 */
uint8_t optosTable[] = {10, 11, 12, 13, 2, 3};

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
    uint8_t byIndex;
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
                    lkState = (KEY_STATES) ((PORTD >> (7 + byIndex) & 1));
                }
                else
                {
                    lkState = (KEY_STATES) ((PORTE >> byIndex) & 1);
                }
                lSWState = (KEY_STATES) ((PORTC >> trapSwitchsTable[byIndex]) & 1);


                // <editor-fold defaultstate="collapsed" desc="OPTOCOUPLEURS">
                if((byIndex < 6) && getIsDoorOpen())
                {
                    lOptoState = (KEY_STATES) ((PORTD >> optosTable[byIndex]) & 1);

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
                            setMotorState((byIndex + 2) - ((uint8_t) (byIndex > 3) * 3), MOTORS_BREAK);
                            clrSelection();
                        }
                        setDoorSwitchState(byIndex, (lSWState == KEY_LO) ? KEY_USED : KEY_HI);
                        if(!byIndex)
                        {
                            setIsDoorOpen(false);
                            switchs.isDoorMoved = true;
                        }
                        break;
                    }// </editor-fold>
                    case KEY_USED:
                        // <editor-fold desc="KEY_USED">
                    {
                        if(lSWState == KEY_HI)
                        {
                            if(!byIndex)
                            {
                                switchs.isDoorMoved = true;
                            }
                            setDoorSwitchState(byIndex, KEY_HI);
                        }
                        break;
                    }// </editor-fold>
                    default:
                    {
                        break;
                    }
                }

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
            }
        }
        vTaskDelayUntil(&xLastWakeTime, CLAVIER_TASK_DELAY);
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */

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
 *         void clrSelection()
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
void clrSelection()
{
    switchs.selection = 0;
}

/*********************************************************************
 * Function:
 *         void clrIsDoorMoved(void)
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
void clrIsDoorMoved(void)
{
    switchs.isDoorMoved = false;
}

/*********************************************************************
 * Function:
 *         bool getIsDoorMoved(void)
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
bool getIsDoorMoved(void)
{
    return switchs.isDoorMoved;
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
    switchs.isDoorMoved = false;
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        setKeyState(byIndex, (KEY_STATES) (PORTD >> (7 + byIndex) & 1));
    }
    for(; byIndex < 7; byIndex++)
    {
        setKeyState(byIndex, (KEY_STATES) (PORTE >> byIndex) & 1);
    }

    for(byIndex = 0; byIndex < 7; byIndex++)
    {
        setDoorSwitchState(byIndex, (KEY_STATES) (PORTC >> (trapSwitchsTable[byIndex]) & 1));
    }

    if(switchs.hSwitchTask == NULL)
    {
        xTaskCreate(vTaskKeyboard, CLAVIER_TASK_NAME, CLAVIER_TASK_STACK, NULL, CLAVIER_TASK_PRIORITY, &switchs.hSwitchTask);
    }
    if(switchs.hShiftTO == NULL)
    {
        switchs.hShiftTO = xTimerCreate(SHIFT_TIMER_NAME, 10 * SECONDE, pdFALSE, NULL, vShift_TO);
    }
}

/******************************************************************************
 End of File
 */

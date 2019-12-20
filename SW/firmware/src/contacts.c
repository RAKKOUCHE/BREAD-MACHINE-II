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
#define CLAVIER_TASK_PRIORITY 3

/**
 * \brief Profondeur de la pile
 */
#define CLAVIER_TASK_STACK 512

/**
 * \brief Delay de la tâche des touches.
 */
#define CLAVIER_TASK_DELAY (50 * MILLISEC)

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
    bool isKeyShifted;
    uint8_t selection;
    KEY keys[7];
    TaskHandle_t hSwitchTask;
    TimerHandle_t hShiftTO;
} switchs;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */

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
    switchs.hShiftTO = false;
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
    while(1)
    {
        if(getIsMDBChecked())
        {
            for(byIndex = 0; byIndex < 7; byIndex++)
            {
                if(byIndex < 3)
                {
                    lkState = (KEY_STATES)((PORTD >> (7 + byIndex) & 1));
                }
                else
                {
                    lkState = (KEY_STATES)((PORTE >> byIndex) & 1);
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
    switchs.isKeyShifted = state;
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
 * Function:        
 *         void setKeyState(const uint8_t numKey, KEY_STATES state)
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
void setKeyState(const uint8_t numKey, KEY_STATES state)
{
    switchs.keys[numKey].state = state;
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
KEY_STATES getKeyState(const uint8_t numKey)
{
    return switchs.keys[numKey].state;
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
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        setKeyState(byIndex, (KEY_STATES) (PORTD >> (7 + byIndex) & 1));
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

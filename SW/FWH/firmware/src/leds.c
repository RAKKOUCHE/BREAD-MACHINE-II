/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file leds.c
 * 
 * \brief Fichier source de la gestion des leds du clavier
 * 
 * \details Ce fichier fournit les fonctions et les définitions utilisés par le
 *  programme pour  gérer les leds du clavier
 *  
 ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "leds.h"

/* TODO:  Include other files here if needed. */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/**
 * \brief Priorité de la tâche de gestion des leds.
 */
#define LED_TASK_PRIORITY 1

/**
 * \brief Mom en clair de la tâche
 */
#define LED_TASK_NAME "Led task"

/**
 * \brief Dimension de la pile de la  tâche
 */
#define LED_TASK_STACK 512

/**
 * \brief Délai pour la tâche.
 */
#define TASK_LED_DELAY (130 * MILLISEC)

/**
 * \Structure contenant les variables d'une led.
 */
typedef struct
{
    LED_STATE ledState;
    LED_ENABLE enableState;
} LED;

/* ************************************************************************** */
struct
{
    uint8_t listEnable[PRODUCT_NUMBER];
    uint8_t numEnable;
    LED led[PRODUCT_NUMBER];
    BOOL isChase;
    TaskHandle_t taskLed;
} leds;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
static void vTaskLed(void *vParameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    static uint8_t byIndex = 0;
    while(1)
    {
        if(getIsMDBChecked())
        {
            if(leds.isChase)
            {
                if((PORTD >> leds.listEnable[byIndex]) & 1)
                {
                    LATDCLR = (1 << leds.listEnable[byIndex]);
                }
                if(++byIndex >= leds.numEnable)
                {
                    byIndex = 0;
                }
                LATDSET = (1 << leds.listEnable[byIndex]);
            }
            else
            {
                for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
                {
                    if(leds.led[byIndex].enableState == enable)
                    {
                        switch(leds.led[byIndex].ledState)
                        {
                            case LED_OFF:
                                // <editor-fold desc="LED_OFF"> 
                            {
                                LATDCLR = (1 << (4 + byIndex));
                                leds.led[byIndex].ledState = LED_IDLE;
                                break;
                            }// </editor-fold>
                            case LED_ON:
                                // <editor-fold desc="LED_ON"> 
                            {
                                LATDSET = (1 << (4 + byIndex));
                                leds.led[byIndex].ledState = LED_IDLE;
                                break;
                            }// </editor-fold>
                            case LED_BLINK:
                                // <editor-fold desc="LED_BLINK"> 
                            {
                                LATDINV = (1 << (4 + byIndex));
                                break;
                            }// </editor-fold>
                            case LED_IDLE:
                                // <editor-fold desc="LED_IDLE"> 
                            {

                                break;
                            }// </editor-fold>
                            default:
                            {

                                break;
                            }
                        }
                    }
                }
            }
        }
        vTaskDelayUntil(&xLastWakeTime, TASK_LED_DELAY);
    }
}
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
banner.
 */

/*********************************************************************
 * Function:        
 *         static void setLedState(const uint8_t ledNum, const LED_STATE state )
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
static void setLedState(const uint8_t ledNum, const LED_STATE state)
{
    leds.isChase = FALSE;
    leds.led[ledNum].ledState = state;
}

/*********************************************************************
 * Function:        
 *         static void setLedEnable(const uint8_t ledNum, const LED_ENABLE en)
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
static void setLedEnable(const uint8_t ledNum, const LED_ENABLE en)
{
    leds.led[ledNum].enableState = en;
}

/*********************************************************************
 * Function:        
 *         void setLedChase(BOOL isOn)
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
void setLedChase(const BOOL isOn)
{
    uint8_t byIndex;
    if((leds.isChase = isOn))
    {
        LED_BTN_1_Clear();
        LED_BTN_2_Clear();
        LED_BTN_3_Clear();

        for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
        {
            leds.listEnable[leds.numEnable] = 0;
            if(leds.led[byIndex].enableState == enable)
            {
                leds.listEnable[leds.numEnable++] = (4 + byIndex);
            }
        }
        if(leds.numEnable)
        {
            LATDSET = 1 << leds.listEnable[0];
        }
    }
}

// *****************************************************************************

/*********************************************************************
 * Function:        void setSelectedLed(uint8_t ledNum)
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
void setSelectedLed(uint8_t ledNum)
{
    uint8_t byIndex;
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        setLedState(byIndex, LED_OFF);
    }
    setLedState(ledNum - 1, LED_ON);
}

/*********************************************************************
 * Function:        void vLEDsKeybInit(void)
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
void vLEDsKeybInit(void)     
{
    uint8_t byIndex;
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        setLedEnable(byIndex, enable);
        setLedState(byIndex, LED_OFF);
    }
    if(leds.taskLed == NULL)
    {
        xTaskCreate(vTaskLed, LED_TASK_NAME, LED_TASK_STACK, NULL, LED_TASK_PRIORITY, &leds.taskLed);
    }
}

/* *****************************************************************************
End of File
 */

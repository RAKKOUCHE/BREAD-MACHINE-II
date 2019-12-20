/* ************************************************************************** */

/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "moteurs.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/**
 * \brief
 */
#define MOTOR_DELAY (100 * MILLISEC)

/**
 * \brief
 */
#define MOTOR_TASK_NAME "Moteur tsk"

/**\brief
 */
#define MOTOR_TASK_STACK 512

/**
 * \brief
 */
#define MOTOR_TASK_PRIORITY 3

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

typedef enum
{
    MOTORS_INIT,
    MOTORS_OFF,
    MOTORS_ON,
    MOTORS_BREAK,
    MOTORS_IDLE,
} MOTORS_SATE;

struct
{
    MOTORS_SATE state;
    TaskHandle_t hMotorHandle;
} motors;

/*********************************************************************
 * Function:        
 *         static void setPower(void)
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
static void powerMotor(void)
{
    BRK_Set();
    PWR_Set();
}

/*********************************************************************
 * Function:        
 *         static void breakMotor(void)
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
static void breakMotor(void)
{
    BRK_Clear();
    PWR_Clear();
}

/*********************************************************************
 * Function:        
 *         static void freeMotor(void)
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
static void freeMotor(void)
{
    BRK_Set();
    PWR_Clear();
}

/*********************************************************************
 * Function:        
 *         static void vTaskMoteur(void *vParameter)
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
static void vTaskMoteur(void *vParameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        switch(motors.state)
        {
            case MOTORS_INIT:
                // <editor-fold desc="MOTORS_INIT"> 
            {
                motors.state = MOTORS_IDLE;
                breakMotor();
                freeMotor();
                break;
            }// </editor-fold>
            case MOTORS_IDLE:
                // <editor-fold desc="MOTORS_IDLE"> 
            {

                break;
            }// </editor-fold>
            default:
            {
                break;
            }
        }
        vTaskDelayUntil(&xLastWakeTime, MOTOR_DELAY);
    }
}
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
 *         void vMotorsInit(void)
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
void vMotorsInit(void)
{
    motors.state = MOTORS_INIT;
    if(motors.hMotorHandle == NULL)
    {
        xTaskCreate(vTaskMoteur, MOTOR_TASK_NAME, MOTOR_TASK_STACK, NULL, MOTOR_TASK_PRIORITY, &motors.hMotorHandle);
    }
}
/* *****************************************************************************
 End of File
 */

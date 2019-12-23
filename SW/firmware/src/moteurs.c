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

/**
 * \brief Nombre de moteurs dans le distributeur.
 * \details 3 convoyeurs, 3 trappes.
 */
#define MOTEURS_NUMBER (PRODUCT_NUMBER * 2) 
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
    MOTORS_BREAK,
    MOTORS_FORWARD,
    MOTORS_REVERSE,
    MOTORS_IDLE,
} MOTORS_SATE;

typedef struct
{
    MOTORS_SATE state;
} MOTOR;

struct
{
    MOTOR motor[MOTEURS_NUMBER];
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
static void powerMotors(void)
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
static void actvateBreakMotors(void)
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
static void freeMotors(void)
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
        uint8_t byIndex;
        for(byIndex = 0; byIndex < MOTEURS_NUMBER; byIndex++)
        {
            switch(motors.motor[byIndex].state)
            {
                case MOTORS_INIT:
                    // <editor-fold desc="MOTORS_INIT"> 
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    actvateBreakMotors();
                    freeMotors();
                    break;
                }// </editor-fold>
                case MOTORS_OFF:
                    // <editor-fold desc="MOTORS_OFF">
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    switch(byIndex / 3)
                    {
                        case 0:
                            // <editor-fold desc="Caroussels">
                        {
                            freeMotors();
                            LATBSET = 1 < (byIndex + 10);
                            break;
                        }// </editor-fold>
                        case 1:
                            // <editor-fold desc="Trappes">
                        {
                            LATBCLR = 3 < ((byIndex * 2) + 2);
                            break;
                        }// </editor-fold>
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }// </editor-fold>
                case MOTORS_BREAK:
                    // <editor-fold desc="MOTORS_BREAK">
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    switch(byIndex / 3)
                    {
                        case 0:
                            // <editor-fold desc="Caroussels">
                        {
                            actvateBreakMotors();
                            LATBCLR = (1 < (byIndex + 10));
                            break;
                        }// </editor-fold>
                        default:
                        {
                            break;
                        }
                    }

                    break;
                }// </editor-fold>
                case MOTORS_FORWARD:
                    // <editor-fold desc="MOTORS_FORWARD">
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    switch(byIndex/3)
                    {
                        case 0:
                            // <editor-fold desc="0">
                        {
                            powerMotors();
                            LATBCLR =  (1 < (byIndex + 10));
                            break;
                        }// </editor-fold>
                        case 1:
                            // <editor-fold desc="1">
                        {
                            LATBSET = (1 < ((byIndex * 2) + 2));
                            LATBCLR = (1 < ((byIndex * 2) + 3));
                            break;
                        }// </editor-fold>
                        default:
                        {
                            break;
                        }
                    }

                    break;
                }// </editor-fold>
                case MOTORS_REVERSE:
                    // <editor-fold desc="MOTORS_REVERSE">
                {
                    switch(byIndex / 3)
                    {
                        case 1:
                            // <editor-fold desc="1">
                        {
                            LATBCLR = (1 < ((byIndex * 2) + 2));
                            LATBSET = (1 < ((byIndex * 2) + 3));
                            break;
                        }// </editor-fold>
                        default:
                        {
                            break;
                        }
                    }

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
    uint8_t byIndex;
    for(byIndex = 0; byIndex < MOTEURS_NUMBER; byIndex++)
    {
        motors.motor[byIndex].state = MOTORS_INIT;
    }
    if(motors.hMotorHandle == NULL)
    {
        xTaskCreate(vTaskMoteur, MOTOR_TASK_NAME, MOTOR_TASK_STACK, NULL, MOTOR_TASK_PRIORITY, &motors.hMotorHandle);
    }
}
/* *****************************************************************************
 End of File
 */

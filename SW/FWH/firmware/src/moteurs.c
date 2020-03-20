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

/**
 * \brief
 */
typedef struct
{
    DIRECTION lastdir;
    MOTORS_SATE state;
} MOTOR;

/**
 * \brief
 */
struct
{
    MOTOR motor[MOTEURS_NUMBER];
    TaskHandle_t hMotorHandle;
    BOOL isMotorChecked;
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
static void powerCarrouselMotors(void)
{
    BRK_Set();
    Delay10us(1);
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
void actvateBreakMotors(void)
{
    PWR_Clear();
    delayMs(1);
    BRK_Clear();
}

/*********************************************************************
 * Function:        BOOL getIsMotorChecked()
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
BOOL getIsMotorChecked()
{
    return motors.isMotorChecked;
}

/*********************************************************************
 * Function:        void setIsMotorChecked(const BOOL status)
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
void setIsMotorChecked(const BOOL status)
{
    motors.isMotorChecked = status;
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
    PWR_Clear();
    Delay10us(1);
    BRK_Set();
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
    uint8_t byIndex;
    while(1)
    {
        setIsMotorChecked(TRUE);
        for(byIndex = 0; byIndex < MOTEURS_NUMBER; byIndex++)
        {
            switch(motors.motor[byIndex].state)
            {
                case MOTORS_INIT:
                    // <editor-fold desc="MOTORS_INIT">
                {
                    motors.motor[byIndex].state = MOTORS_OFF;
                    actvateBreakMotors();
                    freeMotors();
                    break;
                }// </editor-fold>
                case MOTORS_OFF:
                    // <editor-fold desc="MOTORS_OFF">
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    switch(byIndex)
                    {
                        case 0:
                        case 1:
                        case 2:
                            // <editor-fold desc="Carrousels">
                        {
                            freeMotors();
                            LATBSET = (1 << (byIndex + 10));
                            break;
                        }// </editor-fold>
                        case 3:
                            // <editor-fold desc="Trappe 1">
                        {
                            CMD_TRAP_P11_Clear();
                            CMD_TRAP_P12_Clear();
                            CMD_TRAP_N11_Set();
                            CMD_TRAP_N12_Set();
                            break;
                        }// </editor-fold>
                        case 4:
                            // <editor-fold desc="Trappe 2">
                        {
                            CMD_TRAP_P21_Clear();
                            CMD_TRAP_P22_Clear();
                            CMD_TRAP_N21_Set();
                            CMD_TRAP_N22_Set();
                            break;
                        } // </editor-fold>
                        case 5:
                            // <editor-fold desc="Trappe 3">
                        {
                            CMD_TRAP_P31_Clear();
                            CMD_TRAP_P32_Clear();
                            CMD_TRAP_N31_Set();
                            CMD_TRAP_N32_Set();
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
                    motors.motor[byIndex].state = MOTORS_OFF;
                    switch(byIndex)
                    {
                        case 0:
                        case 1:
                        case 2:
                            // <editor-fold desc="Carrousels">
                        {
                            actvateBreakMotors();
                            LATBCLR = (1 << (byIndex + 10));
                            break;
                        }// </editor-fold>
                        case 3:
                            // <editor-fold desc="Trappe 1">
                        {
                            CMD_TRAP_P11_Clear();
                            CMD_TRAP_P12_Clear();
                            CMD_TRAP_N11_Clear();
                            CMD_TRAP_N12_Clear();
                            break;
                        }// </editor-fold>
                        case 4:
                            // <editor-fold desc="Trappe 2">
                        {
                            CMD_TRAP_P21_Clear();
                            CMD_TRAP_P22_Clear();
                            CMD_TRAP_N21_Clear();
                            CMD_TRAP_N22_Clear();
                            break;
                        }// </editor-fold>
                        case 5:
                            // <editor-fold desc="Trappe 3">
                        {
                            CMD_TRAP_P31_Clear();
                            CMD_TRAP_P32_Clear();
                            CMD_TRAP_N31_Clear();
                            CMD_TRAP_N32_Clear();
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
                    if(byIndex > 2)
                    {
                        setLastDir(byIndex, FORWARD);
                    }
                    switch(byIndex)
                    {
                        case 0:
                        case 1:
                        case 2:
                            // <editor-fold desc="Carrousels">
                        {
                            powerCarrouselMotors();
                            LATBCLR = (1 << (byIndex + 10));
                            break;
                        }// </editor-fold>
                        case 3:
                            // <editor-fold desc="Trappe 1">
                        {
                            CMD_TRAP_P12_Clear();
                            CMD_TRAP_N11_Set();
                            CMD_TRAP_N12_Clear();
                            CMD_TRAP_P11_Set();
                            break;
                        }// </editor-fold>
                        case 4:
                            // <editor-fold desc="Trappe 2">
                        {
                            CMD_TRAP_P22_Clear();
                            CMD_TRAP_N21_Set();
                            CMD_TRAP_N22_Clear();
                            CMD_TRAP_P21_Set();
                            break;
                        }// </editor-fold>
                        case 5:
                            // <editor-fold desc="Trappe 3">
                        {
                            CMD_TRAP_P32_Clear();
                            CMD_TRAP_N31_Set();
                            CMD_TRAP_N32_Clear();
                            CMD_TRAP_P31_Set();
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
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    if(byIndex > 2)
                    {
                        setLastDir(byIndex, REVERSE);
                    }
                    switch(byIndex)
                    {
                        case 0:
                        case 1:
                        case 2:
                            // <editor-fold desc="Trappes">
                        {
                            //Pas d'inversion des moteurs des carrousels.
                            break;
                        }// </editor-fold>
                        case 3:
                            // <editor-fold desc="Trappe 1">
                        {
                            CMD_TRAP_P11_Clear();
                            CMD_TRAP_N12_Set();
                            CMD_TRAP_N11_Clear();
                            CMD_TRAP_P12_Set();
                            break;
                        }// </editor-fold>
                        case 4:
                            // <editor-fold desc="Trappe 2">
                        {
                            CMD_TRAP_P21_Clear();
                            CMD_TRAP_N22_Set();
                            CMD_TRAP_N21_Clear();
                            CMD_TRAP_P22_Set();
                            break;
                        }// </editor-fold>
                        case 5:
                            // <editor-fold desc="Trappe 3">
                        {
                            CMD_TRAP_P31_Clear();
                            CMD_TRAP_N32_Set();
                            CMD_TRAP_N31_Clear();
                            CMD_TRAP_P32_Set();
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

DIRECTION getLastDir(uint8_t num)
{
    return motors.motor[num].lastdir;
}

/*********************************************************************
 * Function:
 *         void setLastDir(uint8_t num, DIRECTION direction)
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
void setLastDir(uint8_t num, DIRECTION direction)
{
    motors.motor[num].lastdir = direction;
}

/*********************************************************************
 * Function:
 *         void setMotorState(const uint8_t num, const MOTORS_SATE state)
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
void setMotorState(const uint8_t num, const MOTORS_SATE state)
{
    motors.motor[num].state = state;
}

/*********************************************************************
 * Function:
 *         MOTORS_SATE getMotorState(const uint8_t num)
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
MOTORS_SATE getMotorState(const uint8_t num)
{
    return motors.motor[num].state;
}

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

    //L'initialisation de l'état des moteurs est effectuée tout au début du programme
    //pour éviter un conflit entre les transistors.
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

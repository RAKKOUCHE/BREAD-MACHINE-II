/**
 * \addtogroup moteurs
 * @{
 */

/** *************************************************************************
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 08
 *
 * \file moteurs.c
 *
 * \brief Fichier sources de la gestion des moteur.
 *
 ***************************************************************************/

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
 * \brief Nom du timer utilisé pour éliminer le pic de courant.
 */
#define MOTOR_PEAK_TIMER_NAME "PEAK TIMER"

/**
 * \brief Délai utilisé pour éviter le peak de courant.
 */
#define MOTOR_PEAK_DELAY (500 * MILLISEC)

/**
 * \brief Sensibilité de la sécurité des trappes.
 * \details Plus la valeur est faible, plus la détection sera sensible.
 */
#define DELTA 75

/**
 * \brief Délai de la tâche des moteurs.
 */
#define MOTOR_DELAY (20 * MILLISEC)

/**
 * \brief Nom de la tâche moteur
 */
#define MOTOR_TASK_NAME "TSK MOTEUR"

/**
 * \brief Dimension du tas affecté à la tâche des moteurs.
 */
#define MOTOR_TASK_STACK 512

/**
 * \brief Priorité de la tâche des moteurs.
 */
#define MOTOR_TASK_PRIORITY 3

/**
 * \brief Délai pendant lequel le moteur sera inversé pour la sécurité de la trappe.
 */
#define MOTOR_REVERSE_DELAY (1000 * MILLISEC)

/**
 * \brief Nombre de moteurs dans le distributeur.
 * \details 6 : 3 convoyeurs, 3 trappes.
 */
#define MOTEURS_NUMBER (PRODUCT_NUMBER * 2)

/**
 * \brief Nom du timer du TO de la vérification de la sécurité.
 */
#define MOTORS_NAME_TIMEOUT_CHECK "TO motors check"

/**
 * \brief Délai maximum pendant lequel un moteur sera activé.
 */

#define CHECK_MOTOR_TO (20UL *SECONDE)


/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/**
 * \brief Structure contenant les informations d'un moteur
 */
typedef struct
{
    DIRECTION lastdir; /*!<La dernière direction utilisé par le moteur.*/
    MOTORS_SATE state; /*!<Dernier état de la tâche pour ce moteur.*/
    bool isToBeReversed; /*!<Flag indiquant si la direction du moteur doit être inversée.*/
    bool isSecurityActivated; /*!<La sécurité est activée.*/
} MOTOR;

/**
 * \brief Variable contenant les informations sur les moteurs.
 */
struct
{
    MOTOR motor[MOTEURS_NUMBER]; /*!<Tableau contenant les informations spécifiques des moteurs.*/
    TaskHandle_t hMotorHandle; /*!<Handle de la tâche gérant les moteurs.*/
    TimerHandle_t hTimerMotorCheck; /*!<Handle du timer gérant le TO de la vérification des moteurs.*/
    TimerHandle_t hTimerPeakMoteur; /*!<Handle du timer utilisé pour éliminer le peak de courant du démarrage du moteur.*/
    bool isMotorChecked; /*!<Flag indiquant si le programme a effectué la tâche du moteur.*/
    bool isMotorsCheckTO; /*Temps maximum accordé pour la vérification d'une trappe.*/
    bool isPeakPassed; /*!<Flag indiquant que le temps accordé au pic de courant pour le démarrage du moteur est terminé.*/
    uint32_t id;
} motors;

/*********************************************************************
 * Function:        static void vPeakPassed(TimerHandle_t TimerHandle)
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
static void vPeakPassed(TimerHandle_t TimerHandle)
{
    motors.isPeakPassed = true;
}

/*********************************************************************
 * Function:        static void vCheckedTO()
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
static void vMotorCheckTO(TimerHandle_t timerHandle)
{
    motors.isMotorsCheckTO = true;
}

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
 * Function:        static void actvateBreakMotors(void)
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
static void actvateBreakMotors(void)
{
    PWR_Clear();
    delayMs(1);
    BRK_Clear();
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
    //    TickType_t xLastWakeTime = xTaskGetTickCount();
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
                    motors.motor[byIndex].isToBeReversed = false;
                    motors.motor[byIndex].lastdir = NONE;
                    motors.motor[byIndex].state = MOTORS_OFF;
                    actvateBreakMotors();
                    freeMotors();
                    break;
                }// </editor-fold>
                case MOTORS_OFF:
                    // <editor-fold desc="MOTORS_OFF">
                {
                    motors.motor[byIndex].state = MOTORS_IDLE;
                    if((byIndex > 2) && motors.motor[byIndex - 3].isToBeReversed)
                    {
                        motors.motor[byIndex - 3].isToBeReversed = false;
                        motors.motor[byIndex].state = MOTORS_REVERSE;
                    }
                    else
                    {
                        setLastDir(byIndex, NONE);
                    }
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
                    if(byIndex > 2)
                    {
                        xTimerStop(getHandleMotorCheckTimer(), 1 * SECONDE);
                    }

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
                        motors.isPeakPassed = false;
                        xTimerChangePeriod(motors.hTimerPeakMoteur, MOTOR_PEAK_DELAY, 1000);
                        xTimerStart(getHandleMotorCheckTimer(), 1 * SECONDE);
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
                        xTimerStart(getHandleMotorCheckTimer(), 1 * SECONDE);
                        if(motors.motor[byIndex].isSecurityActivated)
                        {
                            motors.isPeakPassed = false;
                            xTimerChangePeriod(motors.hTimerPeakMoteur,
                                               MOTOR_REVERSE_DELAY, 1000);
                        }
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
                    if(byIndex > 2)
                    {
                        if((motors.motor[byIndex].lastdir == FORWARD))
                        {
                            if(motors.isPeakPassed &&
                               (getDoorSwitchState(byIndex - 2) == KEY_HI) &&
                               (getDoorSwitchState(byIndex + 1) == KEY_HI))
                            {
                                setInputSecurity(byIndex - 3);
                                xTaskNotifyGive(getADCTaskHandle());
                                while(!getIsAdcDone());
                                if(getADCValue(byIndex - 3) > getSecurityValue(byIndex - 3))
                                {
                                    if(getIsADCCheckInProgress())
                                    {
                                        if(getADCValue(byIndex - 3) > getSecurityValue(byIndex - 3))
                                        {
                                            setSecurityValue(byIndex - 3, getADCValue(byIndex - 3));
                                        }
                                    }
                                    else
                                    {
                                        if(getADCValue(byIndex - 3) > ((getSecurityValue(byIndex - 3) * (100 + DELTA)) / 100))
                                        {
                                            setMotorState(byIndex, MOTORS_REVERSE);
                                            motors.motor[byIndex].isSecurityActivated = true;
                                        }
                                    }
                                }
                            }
                        }
                        if((motors.motor[byIndex].lastdir == REVERSE))
                        {
                            if(motors.motor[byIndex].isSecurityActivated && (motors.isPeakPassed || (getDoorSwitchState(byIndex - 2) != KEY_HI)))
                            {
                                motors.motor[byIndex].isSecurityActivated = false;
                                setMotorState(byIndex, MOTORS_FORWARD);
                            }
                        }
                    }
                    break;
                }// </editor-fold>
                default:
                {

                    break;
                }
            }
        }
        vTaskDelay(MOTOR_DELAY);
    }
}

/*********************************************************************
 * Function:        TimerHandle_t getHandleMotorTimerChecked(VOID
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
TimerHandle_t getHandleMotorCheckTimer(void)
{
    return motors.hTimerMotorCheck;
}

/*********************************************************************
 * Function:        bool getIsSecurityActivated(uint8_t num)
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
bool getIsSecurityActivated(void)
{

    return motors.motor[3].isSecurityActivated ||
        motors.motor[4].isSecurityActivated ||
        motors.motor[5].isSecurityActivated;
}

/*********************************************************************
 * Function:        DIRECTION getLastDir(const uint8_t num)
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
DIRECTION getLastDir(const uint8_t num)
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
void setLastDir(const uint8_t num, const DIRECTION direction)
{

    motors.motor[num].lastdir = direction;
}

/*********************************************************************
 * Function:        void setIsMotorChecked(const bool status)
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
void setIsMotorChecked(const bool status)
{

    motors.isMotorChecked = status;
}

/*********************************************************************
 * Function:        bool getIsMotorChecked()
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
bool getIsMotorChecked()
{

    return motors.isMotorChecked;
}

/*********************************************************************
 * Function:        bool getIsMotorCheckTO(void)
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
bool getIsMotorCheckTO(void)
{
    return motors.isMotorsCheckTO;
}

/*********************************************************************
 * Function:        void setIsSecurityCheckedTO(bool isChecked)
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
void setMotorCheckedTO(const bool isChecked)
{
    motors.isMotorsCheckTO = isChecked;
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
    motors.id = 1;
    //L'initialisation de l'état des moteurs est effectuée tout au début du programme
    //pour éviter un conflit entre les transistors.
    motors.motor[byIndex].isSecurityActivated = false;
    for(byIndex = 0; byIndex < MOTEURS_NUMBER; byIndex++)
    {
        motors.motor[byIndex].isSecurityActivated = false;
        motors.motor[byIndex].state = MOTORS_INIT;
    }
    if(!motors.hTimerMotorCheck)
    {
        motors.hTimerMotorCheck = xTimerCreate(MOTORS_NAME_TIMEOUT_CHECK,
                                               CHECK_MOTOR_TO, pdFALSE,
                                               (void*)motors.id,
                                               vMotorCheckTO);
    }
    if(motors.hTimerPeakMoteur == NULL)
    {
        motors.hTimerPeakMoteur = xTimerCreate(MOTOR_PEAK_TIMER_NAME,
                                               MOTOR_PEAK_DELAY, pdFALSE, NULL,
                                               vPeakPassed);
    }
    if(!motors.hMotorHandle)
    {
        xTaskCreate((TaskFunction_t)vTaskMoteur, MOTOR_TASK_NAME,
                    MOTOR_TASK_STACK, NULL, MOTOR_TASK_PRIORITY,
                    &motors.hMotorHandle);
    }
}

/**
 * @}
 */
/* *****************************************************************************
End of File
 */

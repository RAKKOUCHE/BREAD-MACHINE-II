/**
 * \addtogroup security
 * @{
 */

/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 01
 *
 * \file trap_security.h
 *
 * \brief Fichier source de la sécurité des trappes.
 *
 ***************************************************************************/

/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "trap_security.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/**
 * \def DELAY_ADC
 * \brief delay entre chaque vérification.
 */
#define DELAY_ADC (50  * MILLISEC)

/**
 * \brief
 */
#define ADC_TASK_NAME "TSK ADC"

/**\brief
 */
#define ADC_TASK_STACK 512

/**
 * \brief
 */
#define ADC_TASK_PRIORITY 4

/**
 * \struct ADC
 * \brief structure contenant les informations relatives au canal
 * analogique.
 */
typedef struct __attribute__((packed))
{
    //  bool isDataAvailable; /*!<Indique si la valeur est utilisable.*/
    ADC_INPUTS_POSITIVE id; /*!<Identifiant du canal analogique.*/
    uint32_t dwValue; /*!<Valeur analogique du canal.*/
}
ADC;

/**
 * \brief Structure des données du module de gestion de la sécurité des trappes.
 */
static struct __attribute__((packed))
{
    TaskHandle_t task_adc_handle;
    uint16_t value;
    uint8_t index;
    ADC adc[NUMBER_TRAP];
    uint8_t byIndex;
    bool isDone;
    bool isCheckInProgress; /*!<Indique si l'etalonnage de la sécurité est en cours.*/
    bool isCheckOver;
}
adcs;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

static void vTaskTrapSecurity(void *vParameter)
{
    IEC1SET = 2;
    uint8_t byIndex;
    while(true)
    {
        ulTaskNotifyTake(true, portMAX_DELAY);

        AD1CHSbits.CH0SA = adcs.adc[adcs.byIndex].id;
        adcs.isDone = false;
        adcs.adc[adcs.byIndex].dwValue = 0;
        for(byIndex = 0; byIndex < 16; byIndex++)
        {
            IFS1bits.AD1IF = 0;
            AD1CON1bits.SAMP = 1;
            while(!AD1CON1bits.DONE);
            while(!IFS1bits.AD1IF);
            IFS1bits.AD1IF = 0;
            adcs.adc[adcs.byIndex].dwValue += ADC1BUF0;
        }
        adcs.adc[adcs.byIndex].dwValue /= byIndex;
        adcs.isDone = true;
        //vTaskDelay(200);
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
 * Function:        void setAdcValue(uint8_t num, uint32_t value)
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
void setAdcValue(uint8_t num, uint32_t value)
{
    adcs.adc[num].dwValue = value;
}

/*********************************************************************
 * Function:        uint32_t getAdcValue(uint8_t num)
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
uint32_t getADCValue(uint8_t num)
{
    return adcs.adc[num].dwValue;
}

/*********************************************************************
 * Function:        void setIsADCCeckInProgress(bool isCheckInProgress)
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
void setIsADCCeckInProgress(bool isCheckInProgress)
{
    adcs.isCheckInProgress = isCheckInProgress;
}

/*********************************************************************
 * Function:        bool getIsADCCheckInProgress(void
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
bool getIsADCCheckInProgress(void)
{
    return adcs.isCheckInProgress;
}

/*********************************************************************
 * Function:        TaskHandle_t getADCTaskHandle()
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
TaskHandle_t getADCTaskHandle(void)
{
    return adcs.task_adc_handle;
}

/*********************************************************************
 * Function:        uint16_t getSecurityValue(void)
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
int getTrapSecurityValue(uint8_t byIndex)
{
    return adcs.adc[byIndex].dwValue;
}

/*********************************************************************
 * Function:        void setInputSecurity(uint8_t byIndex)
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
void setInputSecurity(uint8_t byIndex)
{
    adcs.byIndex = byIndex;
}

/*********************************************************************
 * Function:        bool getIsAdcDone(void)
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
bool getIsAdcDone(void)
{
    return adcs.isDone;
}

/*********************************************************************
 * Function:        void setIsCheckOver(bool data )
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
void setIsCheckOver(bool data)
{
    adcs.isCheckOver = data;
}

/*********************************************************************
 * Function:        bool getIsCheckOver(void
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
bool getIsCheckOver(void)
{
    return adcs.isCheckOver;
}

/*********************************************************************
 * Function:
 *         void vADCInit(void)
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
void vADCInit(void)
{
    uint8_t byIndex;
    adcs.adc[0].id = ADC_INPUT_POSITIVE_AN13;
    adcs.adc[1].id = ADC_INPUT_POSITIVE_AN14;
    adcs.adc[2].id = ADC_INPUT_POSITIVE_AN15;
    adcs.isCheckInProgress = false;
    AD1CON1bits.FORM = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON2bits.VCFG = 0;
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = 0;
    AD1CON2bits.BUFM = 0;
    AD1CON2bits.ALTS = 0;
    AD1CON3bits.ADRC = 1;
    AD1CON3bits.SAMC = 31;
    AD1CON3bits.ADCS = 255;
    AD1CON1bits.ASAM = 0;
    AD1CON1bits.ON = 1;
    IFS1bits.AD1IF = 0;

    for(byIndex = 0; byIndex < NUMBER_TRAP; byIndex++)
    {
        //adcs.adc[byIndex].isDataAvailable = false;
        adcs.adc[byIndex].dwValue = 0;
    }

    xTaskCreate((TaskFunction_t)vTaskTrapSecurity, ADC_TASK_NAME, ADC_TASK_STACK, NULL,
                ADC_TASK_PRIORITY, &adcs.task_adc_handle);
    adcs.isCheckOver = false;

};
/**
 * @}
 */

/* *****************************************************************************
End of File
 */

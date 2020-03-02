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

#include <stdint.h>

#include "trap_security.h"

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
 * \def DELAY_ADC
 * \brief delay entre chaque vérification.
 */
#define DELAY_ADC  (50  * MILLISEC)

/**
 * \brief
 */
#define ADC_TASK_NAME "ADC tsk"

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
    bool isDataAvailable; /*!<Indique si la valeur est utilisable.*/
    //    ADC_INPUT_POSITIVE id; /*!<Identifiant du canal analogique.*/
    uint32_t dwValue; /*!<Valeur analogique  sur canal.*/
}
ADC;

/**
 * \struct adcs
 * \brief Structure des données du module de gestion de la sécurité des trappes.
 */
struct
{
    TaskHandle_t task_handle;
    ADC adc[NUMBER_TRAP];
} adcs;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

static void vTaskTrapSecurity(void *vParameter)
{
    uint32_t dwLoad;
    while(1)
    {
        ulTaskNotifyTake(true, portMAX_DELAY);
        dwLoad = ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 +
                ADC1BUF6 + ADC1BUF7 + ADC1BUF8 + ADC1BUF9 + ADC1BUFA + ADC1BUFB +
                ADC1BUFC + ADC1BUFD + ADC1BUFE + ADC1BUFF;
        dwLoad /= 16;
    }
}

TaskHandle_t getADCTaskHandle()
{
    return adcs.task_handle;
}

void vCheckSecurity(uint8_t byIndex)
{
    //    ADC_InputSelect(ADC_MUX_A, adcs.adc[byIndex].id, ADC_INPUT_NEGATIVE_VREFL);
    //    ADC_InputScanSelect(1 << adcs.adc[byIndex].id);
    //
    //    ADC_Enable();
    //    ADC_SamplingStart();

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
    //    ADC_Disable();
    //    adcs.adc[0].id = ADC_INPUT_POSITIVE_AN13;
    //    adcs.adc[1].id = ADC_INPUT_POSITIVE_AN14;
    //    adcs.adc[2].id = ADC_INPUT_POSITIVE_AN15;

    for(byIndex = 0; byIndex < NUMBER_TRAP; byIndex++)
    {
        adcs.adc[byIndex].isDataAvailable = false;
    }
    xTaskCreate(vTaskTrapSecurity, ADC_TASK_NAME, ADC_TASK_STACK, NULL,
                ADC_TASK_PRIORITY, &adcs.task_handle);

};


/* *****************************************************************************
End of File
 */

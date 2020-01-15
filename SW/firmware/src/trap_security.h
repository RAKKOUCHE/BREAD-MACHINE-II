/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <stdbool.h>
#include "peripheral/adc/plib_adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "globaldef.h"
#include "delay_us.h"


/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /**
     * \def NUMBER_TRAP
     * \brief Nombre de trappe à vérifier.
     */
#define NUMBER_TRAP 3

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    TaskHandle_t getADCTaskHandle();
    
    /**
     * \brief
     * @param byIndex
     */
    void vCheckSecurity(uint8_t byIndex);

    /**
     * \brief
     */
    void vADCInit(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

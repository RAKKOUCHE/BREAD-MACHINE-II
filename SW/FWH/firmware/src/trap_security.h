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
 * \brief Fichier entête de la gestion de la sensibilité des trappes.
 *
 *
 ***************************************************************************/


#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

/**
 * \defgroup security SECURITY
 * Gestion de la sensibilité des trappes lors de fermeture pour la sécurité.
 * @{
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include <xc.h>
#include <sys/attribs.h>
#include "peripheral/adc/plib_adc.h"
#include "peripheral/adc/processor/adc_p32mx575f512l.h"
#include "driver/adc/drv_adc_static.h"
#include "peripheral/adc/plib_adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "communDef.h"
#include "system/int/sys_int_mapping.h"


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

    /**
     * \brief
     */
    void setAdcValue(uint8_t num, uint32_t value);

    /**
     * \brief
     * @param num
     * @return
     */
    uint32_t getADCValue(uint8_t num);

    /**
     * \brief
     * @return
     */
    bool getIsADCCheckInProgress(void);

    /**
     * \brief
     * @param isCheckInProgress
     */
    void setIsADCCeckInProgress(bool isCheckInProgress);

    /**
     * \brief
     * @return
     */
    TaskHandle_t getADCTaskHandle(void);

    /**
     * \brief
     * @return
     */
    bool getIsAdcDone(void);
    
    /**
     * \brief
     * @param data
     */
    void setIsCheckOver(bool data);
    
    /**
     * 
     * @return 
     */
    bool getIsCheckOver(void);

    /**
     * \brief
     */
    void vADCInit(void);
/**
 * @}
 */
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

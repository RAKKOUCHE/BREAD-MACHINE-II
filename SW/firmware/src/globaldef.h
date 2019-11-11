/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 01
 * 
 * \file globaldef.h
 * 
 * \brief Fichier des definitions utilis�es dans le programme.
 * 
 * \details
 *  
 ***************************************************************************/

#ifndef _GLOBAL_DEF_H    /* Guard against multiple inclusion */
#define _GLOBAL_DEF_H

/**
 * \defgroup globals GLOBALS
 * Definitions et variables globales.
 * @{
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "FreeRTOSConfig.h"
#include "third_party/rtos/FreeRTOS/Source/include/projdefs.h"

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

    /**
     * \brief Nombre de produits.
     */
#define PRODUCT_NUMBER 3

    /**
     * \brief Fr�quence d'horloge du CPU.
     */
#define GetSystemClock() configCPU_CLOCK_HZ

    /**
     * \brief D�finition d'une seconde pour Freertos
     */
#define SECONDE pdMS_TO_TICKS(1000)

    /**
     * \brief D�finition d'une milliseconde pour Freertos.
     */
#define MILLISEC pdMS_TO_TICKS(1)

    /**
     * \brief Provoque un d�lai de x milliseconde.
     */
#define delayMs(x) vTaskDelay(x)

    /**
     * \brief P�riode de clignotement de la led syst�me.
     */
#define FLASH_PERIOD 250


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
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
     @}
     */
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /*  */

/* *****************************************************************************
 End of File
 */

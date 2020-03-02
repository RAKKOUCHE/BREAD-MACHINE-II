/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 08
 *
 * \file hd44780.h
 *
 * \brief Fichier entête de la gestion de la sonde de température.
 *
 * \details Ce fichier fournit les prototypes et les définitions utilisés par le
 * programme pour gérer la sonde température.
 *
 ***************************************************************************/

#ifndef _DS18B20    /* Guard against multiple inclusion */
#define _DS18B20

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include <stdint.h>
#include <machine/types.h>
#include "FreeRTOS.h"
#include "task.h"
#include "communDef.h"
#include "MDB/mdb.h"
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

    /**
     * \brief Requête de la température.
     * @return Dermière température mesurée.
     */
    double getTemp(void);

    /**
     * \brief Initialisation du modu le de température.
     */
    void vDS18B20Init(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

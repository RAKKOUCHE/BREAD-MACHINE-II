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
 * \brief Fichier entête de la gestion des leds du clavier.
 *
 * \details Ce fichier fournit les prototypes et les définitions utilisés par le
 * programme pour  gérer les leds du clavier.
 *
 ***************************************************************************/

#ifndef _LEDS_H    /* Guard against multiple inclusion */
#define _LEDS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <GenericTypeDefs.h>
#include <machine/types.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "communDef.h"
#include "MDB/mdb.h"

/* This section lists the other files that are included in this file.
 */

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

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /**
     * \brief Enumération des états des leds.
     */
    typedef enum
    {
        LED_OFF, /*!<Led éteinte.*/
        LED_ON, /*!<Led allumée.*/
        LED_BLINK, /*!|Led clignotante.*/
        LED_IDLE, /*!<Aucune modification de l'état de la led.*/
    } LED_STATE;

    /**
     * \brief Enumération activation des leds
     */
    typedef enum
    {
        disable, /*!<Led ignorée.*/
        enable, /*!Led en service.*/
    } LED_ENABLE;

    // *****************************************************************************

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Etabli l'état d'une led.
     * \param[in] ledNum Numéro de la led concernée.
     * \param[in] etat Etat de la led concernée.
     */
    void setLedState(const uint8_t ledNum, const LED_STATE etat);

    /**
     * \brief Active ou desactive la led.
     * \param[in] ledNum Numéro de la led concernée.
     * \param[in] en Enable pour activer, Disable pour desactiver
     */
    void setLedEnable(const uint8_t ledNum, const LED_ENABLE en);

    /**
     * \brief Active ou desactive le mode défilement pour les leds du claviers.
     * @param[in] isOn True si le défilemet doit être activé.
     */
    void setLedChase(const BOOL isOn);

    /**
     * \brief Initialisation du module des leds.
     */
    void vLEDsKeybInit(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _LEDS_H */

/* *****************************************************************************
 End of File
 */

/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 01
 *
 * \file moteurs.h
 *
 * \brief Fichier entête de la gestion des moteurs.
 *
 ***************************************************************************/

/* ************************************************************************** */

#ifndef _MOTEURS_H    /* Guard against multiple inclusion */
#define _MOTEURS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <GenericTypeDefs.h>
#include <machine/types.h>
#include "FreeRTOS.h"
#include "task.h"
#include "delay_us.h"
#include "communDef.h"
#include "parameters.h"
#include "trap_security.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * \defgroup moteurs MOTEURS
     * Gestion des moteurs du système.
     * @{
     */

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /**
     * \brief La trappe descend.
     */
#define MOTORS_DOWN MOTORS_FORWARD

    /**
     * \brief La trappe monte
     */
#define MOTORS_UP MOTORS_REVERSE

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /**
     * \brief Activités des moteurs.
     */
    typedef enum
    {
        NONE, /*!<Moteur arreté */
        REVERSE, /*!<Moteur en mode ouverture.*/
        FORWARD, /*!<Moteur en mode fermeture.*/
    } DIRECTION;

    /**
     * \brief Etat des moteurs.
     */
    typedef enum
    {
        MOTORS_INIT, /*!<Initialisation du moteur.*/
        MOTORS_OFF, /*!<Moteur à l'arrêt.*/
        MOTORS_BREAK, /*!<Freinage.*/
        MOTORS_FORWARD, /*!<Activation du moteur pour la fermeture de la trappe ou pour le positonnement des bagutettes.*/
        MOTORS_REVERSE, /*!<Activation du moteur pour l'ouverture  de la trappe.*/
        MOTORS_IDLE, /*!<Aucune action sur le moteur.*/
    } MOTORS_SATE;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */
    // *****************************************************************************

    /**
     * \brief Cette fonction retournet l'indication d'une surconsommation.
     * @return True si une surconsommation d'un moteur de trappe a eu lieu.
     */
    bool getIsSecurityActivated(void);

    /**
     * \brief Cette fonction retourne la dernière direction activée pour le moteur indiqué.
     * @param[in] num Numéro du moteur concerné.
     * @return La dernière direction activé pour le moteur.
     */
    DIRECTION getLastDir(const uint8_t num);

    /**
     * \brief Cette fonction fixe la variable utilisée pour définir la direction d'u moteur. 
     * @param[in] num Numéro du moteur concerné.
     * @param[in] direction Direction du moteur.
     */
    void setLastDir(const uint8_t num, const DIRECTION direction);

    /**
     * \brief Récupère le handle du timer utilisé pour le délai d'activation du moteur.
     * @return Le handle du timer utilisé pour le délai d'activation du moteur.
     */
    TimerHandle_t getHandleMotorCheckTimer(void);

    /**
     * \brief Cette fonction renvoie le flag indiquant si le temps maximum de fonctionnement pour un moteur de trappe est atteint.
     * @return True si le temps accordé au fonctionnment du moteur est atteint.
     */
    bool getIsMotorCheckTO(void);

    /**
     * \brief Cette fonction fixe la valeur du flag indiquant si le temps maximum d'activité du moteur est atteint.
     * @param[in] isChecked Valeur du flag.
     */
    void setMotorCheckedTO(const bool isChecked);

    /**
     * \brief Cette fonction renvoie le flag indiquant l'accès à la tâche des moteurs.
     * \return True si le programme a accédé à la tâche des moteurs.
     */
    bool getIsMotorChecked(void);

    /**
     * \brief Cette fonction fixe le flag indiquant l'accès à la tâche des moteurs.
     * @param[in] status True si le programme a accédé à la tâche des moteurs, false si le flag a été utilisé.
     */
    void setIsMotorChecked(const bool status);

    /**
     * \brief Cette fonction enregistre l'état de la tâche pour un moteur. 
     * @param[in] num Numéro du moteur concerné.
     * @param[in] state Etat de la tâche pour le moteur concerné.
     */
    void setMotorState(const uint8_t num, const MOTORS_SATE state);

    /**
     * \brief Cette fonction retourne l'état de la tâche des moteurs pour un moteur défini.
     * @param[in] num Numéro du moteur concerné.
     * @return Etat du la Tâche pour le moteur concerné.
     */
    MOTORS_SATE getMotorState(const uint8_t num);

    /**
     * \brief Cette fonction initialise le module de gestion des moteurs.
     */
    void vMotorsInit(void);

    /**
     * @}
     */
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOTEURS_H */

/* *****************************************************************************
 End of File
 */

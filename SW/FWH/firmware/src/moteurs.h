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
 * \brief Fichier ent�te de la gestion des moteurs.
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
     * Gestion des moteurs du syst�me.
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
     * \brief Activit�s des moteurs.
     */
    typedef enum
    {
        NONE, /*!<Moteur arret� */
        REVERSE, /*!<Moteur en mode ouverture.*/
        FORWARD, /*!<Moteur en mode fermeture.*/
    } DIRECTION;

    /**
     * \brief Etat des moteurs.
     */
    typedef enum
    {
        MOTORS_INIT, /*!<Initialisation du moteur.*/
        MOTORS_OFF, /*!<Moteur � l'arr�t.*/
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
     * \brief Cette fonction retourne la derni�re direction activ�e pour le moteur indiqu�.
     * @param[in] num Num�ro du moteur concern�.
     * @return La derni�re direction activ� pour le moteur.
     */
    DIRECTION getLastDir(const uint8_t num);

    /**
     * \brief Cette fonction fixe la variable utilis�e pour d�finir la direction d'u moteur. 
     * @param[in] num Num�ro du moteur concern�.
     * @param[in] direction Direction du moteur.
     */
    void setLastDir(const uint8_t num, const DIRECTION direction);

    /**
     * \brief R�cup�re le handle du timer utilis� pour le d�lai d'activation du moteur.
     * @return Le handle du timer utilis� pour le d�lai d'activation du moteur.
     */
    TimerHandle_t getHandleMotorCheckTimer(void);

    /**
     * \brief Cette fonction renvoie le flag indiquant si le temps maximum de fonctionnement pour un moteur de trappe est atteint.
     * @return True si le temps accord� au fonctionnment du moteur est atteint.
     */
    bool getIsMotorCheckTO(void);

    /**
     * \brief Cette fonction fixe la valeur du flag indiquant si le temps maximum d'activit� du moteur est atteint.
     * @param[in] isChecked Valeur du flag.
     */
    void setMotorCheckedTO(const bool isChecked);

    /**
     * \brief Cette fonction renvoie le flag indiquant l'acc�s � la t�che des moteurs.
     * \return True si le programme a acc�d� � la t�che des moteurs.
     */
    bool getIsMotorChecked(void);

    /**
     * \brief Cette fonction fixe le flag indiquant l'acc�s � la t�che des moteurs.
     * @param[in] status True si le programme a acc�d� � la t�che des moteurs, false si le flag a �t� utilis�.
     */
    void setIsMotorChecked(const bool status);

    /**
     * \brief Cette fonction enregistre l'�tat de la t�che pour un moteur. 
     * @param[in] num Num�ro du moteur concern�.
     * @param[in] state Etat de la t�che pour le moteur concern�.
     */
    void setMotorState(const uint8_t num, const MOTORS_SATE state);

    /**
     * \brief Cette fonction retourne l'�tat de la t�che des moteurs pour un moteur d�fini.
     * @param[in] num Num�ro du moteur concern�.
     * @return Etat du la T�che pour le moteur concern�.
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

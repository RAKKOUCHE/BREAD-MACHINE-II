/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 01
 *
 * \file contacts.h
 *
 * \brief Fichier entête de la gestion des contacts du système.
 *
 ***************************************************************************/


#ifndef _CONTACTS_H    /* Guard against multiple inclusion */
#define _CONTACTS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <machine/types.h>
#include "freertos.h"
#include "task.h"
#include "MDB/mdb.h"
#include "product.h"

/* This section lists the other files that are included in this file.
 */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * \defgroup contacts CONTACTS
     * Gestion des contacts du système.
     * @{
     */

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /**
     * \brief
     */
#define STR_DOOR_OPEN " PORTE OUVERTE"

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * brief Enumération des états de la touche.
     */
    typedef enum
    {
        KEY_LO, /*!<La touche vient d'être appuyée.*/
        KEY_HI, /*!<La touche est relachée.*/
        KEY_CHECKED, /*!<La touche est vérifiée.*/
        KEY_USED, /*!<La touche est toujours utilisée.*/
    } KEY_STATES;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief
     * @param[in] state
     */
    void setShiftState(const bool state);

    /**
     * \brief
     * @return
     */
    bool getShiftState(void);

    //    /**
    //     * \brief Demande l'état du clavier.
    //     * \param[in] Numéro de la touche.
    //     * \return Etat du clavier.
    //     */
    //    KEY_STATES getKeyState(const uint8_t numKey);

    /**
     * \brief Inverse l'état shifted.
     */
    void shiftStateToggle(void);

    /**
     * \brief
     * @return
     */
    TaskHandle_t getSwitchsHandle(void);

    /**
     * \brief
     * @return
     */
    bool getIsDoorOpen();

    /**
     * \brief
     * @param status
     */
    void setIsDoorOpen(const bool status);

    /**
     * \brief
     * @return
     */
    bool getIsTaskKeyChecked(void);

    /**
     * \brief
     * @param status
     */
    void setIsTaskKeyChecked(bool status);

    /**
     * \brief
     * @param byIndex
     * @return
     */
    KEY_STATES getDoorSwitchState(const uint8_t byIndex);

    /**
     * \brief
     * @param byIndex
     * @return
     */
    KEY_STATES getOptoState(const uint8_t byIndex);
    //
    //    /**
    //     * \brief Fxe l'état du clavier.
    //     * @param numKey Numéro de la touche concernée.
    //     * @param state Etat à envoyé à la touche.
    //     */
    //    void setKeyState(const uint8_t numKey, const KEY_STATES state);
    //

    /**
     * \brief Demande la touche utilisée
     * @return 0 Si aucune touche n'est utilisée. Sinon le numéro de la touche.
     */
    uint8_t getSelection();

    /**
     * \brief Positionne la sélection à zéro.
     */
    void clrSelection();

    /**
     * \brief
     */
    void clrIsDoorMoved(void);

    /**
     * \brief
     * @return
     */
    bool getIsDoorMoved(void);

    /**
     * \brief Initialisation du clavier.
     */
    void vKeyboardInit(void);
    /**
     * @}
     */
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _CONTACTS_H */

/* *****************************************************************************
 End of File
 */

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

#ifndef _CLAVIER_H    /* Guard against multiple inclusion */
#define _CLAVIER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <machine/types.h>
#include "freertos.h"
#include "task.h"
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
    //
    //    /**
    //     * \brief Demande l'état du clavier.
    //     * \param[in] Numéro de la touche.
    //     * \return Etat du clavier.
    //     */
    //    KEY_STATES getKeyState(const uint8_t numKey);

    /**
     * \brief
     * @param byIndex
     * @return
     */
    KEY_STATES getDoorSwitchState(const uint8_t byIndex);
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

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _CLAVIER_H */

/* *****************************************************************************
 End of File
 */

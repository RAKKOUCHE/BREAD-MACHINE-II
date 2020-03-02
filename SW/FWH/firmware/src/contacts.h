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
     * brief Enum�ration des �tats de la touche.
     */
    typedef enum
    {
        KEY_LO, /*!<La touche vient d'�tre appuy�e.*/
        KEY_HI, /*!<La touche est relach�e.*/
        KEY_CHECKED, /*!<La touche est v�rifi�e.*/
        KEY_USED, /*!<La touche est toujours utilis�e.*/
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
    //     * \brief Demande l'�tat du clavier.
    //     * \param[in] Num�ro de la touche.
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
    //     * \brief Fxe l'�tat du clavier.
    //     * @param numKey Num�ro de la touche concern�e.
    //     * @param state Etat � envoy� � la touche.
    //     */
    //    void setKeyState(const uint8_t numKey, const KEY_STATES state);
    //

    /**
     * \brief Demande la touche utilis�e
     * @return 0 Si aucune touche n'est utilis�e. Sinon le num�ro de la touche.
     */
    uint8_t getSelection();

    /**
     * \brief Positionne la s�lection � z�ro.
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

/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MAINBOARD.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "MAINBOARD_Initialize" and "MAINBOARD_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "MAINBOARD_STATES" definition).  Both
    are defined here for convenience.
 *******************************************************************************/

/**
 * \file MAINBOARD.h
 *
 * \brief Ce fichier en-t�te fournit les prototypes et les de�finitions pour
 * l'application.
 *
 * \details Ce fichier d'en-t�te fournit des prototypes de fonctions et
 * des d�finitions de types de donn�es pour l'application.  Certaines d'entre
 * elles sont requises par le syst�me (telles que la  "MAINBOARD_Initialize" et
 * "MAINBOARD_Tasks") et certains d'entre eux sont seulement utilis�s en
 * interne par l'application (comme la d�finition "MAINBOARD_STATES").
 * Les deux sont d�finies ici pour plus de commodit�.
 */

#ifndef _MAINBOARD_H
#define _MAINBOARD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "audits.h"
#include "hd44780.h"
#include "communDef.h"
#include "parameters.h"
#include "dataCommun.h"
#include "MDB/mdb.h"
#include "contacts.h"
#include "leds.h"
#include "DS18B20.h"
#include "contacts.h"
#include "moteurs.h"
#include "contacts.h"
#include "MDB/mdb_bv.h"
#include "moteurs.h"
#include "trap_security.h"


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C"
{

#endif
    // DOM-IGNORE-END

    /**
     * \defgroup main MAIN
     * \brief Module principale
     * @{
     */
    // *****************************************************************************
    // *****************************************************************************
    // Section: Type Definitions
    // *****************************************************************************
    // *****************************************************************************

#ifdef __DEBUG
#define VERSION "2.00_D"
#else
#define VERSION "2.00  "
#endif

    /**
     * \brief Enum�ration de la machine d'�tat principale.
     * \details Cette �num�ration d�finit les �tats d'application valides,
     * ces �tats d�terminent le comportement de l'application � diff�rents moments.
     */
    typedef enum
    {
        /* Application's state machine's initial state. */
        MAINBOARD_STATE_INIT = 0, /*!<Initialisation de l'application.*/
        MAINBOARD_STATE_SERVICE_TASKS, /*!<Etat de l'application en fonctionnement.*/
        MAINBOARD_STATE_DISPLAY_SELECT, /*!<Affichage choix du produit.*/
        MAINBOARD_STATE_DISPLAY_AMOUNT, /*!<Affichage du montant disponible.*/
        MAINBOARD_STATE_CHANGE, /*!<Lance la proc�dure de change.*/
    } MAINBOARD_STATES;


    // *****************************************************************************
    /* Application Data

      Summary:
        Holds application data

      Description:
        This structure holds the application's data.

      Remarks:
        Application strings and buffers are be defined outside this structure.
     */

    /**
     * \brief Structure contenant les donn�es utilis�s dans la t�che principale.
     */
    typedef struct
    {
        /* The application's current state */
        MAINBOARD_STATES state; /*!<Etat de la t�che principale de l'application.*/
        int32_t lAmountDispo; /*!<Montant disponible pour un achat.*/
        uint32_t lAmountRequested; /*!<Montant demand� pour un produit s�lectionn�.*/
        //bool isMDBChecked; /*!<Flag indiquant que les p�riph�riques MDB sont initalis�.*/
    } MAINBOARD_DATA;

    /**
     * \brief Handle timer de cumul.
     */
    TimerHandle_t hTOCumul;

    /**
     * \brief Handle du to d�clenchant la proc�dure de trop per�u.
     */
    TimerHandle_t hTimerOverPay;

    /**
     * \brief Handle du to d�clenhant l'annulation de l'affichage du choix.
     */
    TimerHandle_t hTimerDisplaySelection;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Routines
    // *****************************************************************************
    // *****************************************************************************
    //
    //    /**
    //     * \brief Requ�te de l'�tat de la T�che de l'application
    //     * @return Etat de la t�che.
    //     */
    //    MAINBOARD_STATES getMainBoardTaskState(void);

    /**
     * \brief Fixe l'�tat de la t�che de l'application
     * @param state Etat de la t�che de l'application � utiliser.
     */
    void setMainBoardTaskState(MAINBOARD_STATES state);

    /**
     * \brief Requ�te du montant � fournir.
     * @param amount Montant du produit.
     */
    void setAmountRequested(uint32_t amount);
    /**
     * \brief Requ�te du montant disponible.
     * @return Le montant disponible en cts.
     */
    int32_t getAmountDispo(void);

    /**
     * \brief Enregistre le montant disponible.
     * @param amount Montant disponible;
     */
    void setAmountDispo(uint32_t amount);
    //
    //    /**
    //     * \brief Lit le flag indiquant si les p�ruiph�riques MDB sont pr�t.
    //     * @return true si les p�riph�riques sont initialis�s
    //     */
    //    bool getMDBChecked(void);
    //
    //    /**
    //     * brief Fixe l'�tat du flag indiquant si le p�riph�rique sont pr�t
    //     * @param isChecked Etat du flag choisi.
    //     */
    //    void setMDBChecked(bool isChecked);

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Initialization and State Machine Functions
    // *****************************************************************************
    // *****************************************************************************

    /*******************************************************************************
      Function:
        void MAINBOARD_Initialize ( void )

      Summary:
         MPLAB Harmony application initialization routine.

      Description:
        This function initializes the Harmony application.  It places the
        application in its initial state and prepares it to run so that its
        MAINBOARD_Tasks function can be called.

      Precondition:
        All other system initialization routines should be called before calling
        this routine (in "SYS_Initialize").

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        MAINBOARD_Initialize();
        </code>

      Remarks:
        This routine must be called from the SYS_Initialize function.
     */
    void MAINBOARD_Initialize(void);


    /*******************************************************************************
      Function:
        void MAINBOARD_Tasks ( void )

      Summary:
        MPLAB Harmony Demo application tasks function

      Description:
        This routine is the Harmony Demo application's tasks function.  It
        defines the application's state machine and core logic.

      Precondition:
        The system and application initialization ("SYS_Initialize") should be
        called before calling this.

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        MAINBOARD_Tasks();
        </code>

      Remarks:
        This routine must be called from SYS_Tasks() routine.
     */
    void MAINBOARD_Tasks(void);

    /**
     * @}
     */
#endif /* _MAINBOARD_H */

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */


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
 * \file mainboard.h
 *
 * \brief Ce fichier en-tête fournit les prototypes et les deéfinitions pour
 * l'application.
 *
 * \details Ce fichier d'en-tête fournit des prototypes de fonctions et
 * des définitions de types de données pour l'application.  Certaines d'entre
 * elles sont requises par le système (telles que la  "MAINBOARD_Initialize" et
 * "MAINBOARD_Tasks") et certains d'entre eux sont seulement utilisés en
 * interne par l'application (comme la définition "MAINBOARD_STATES").
 * Les deux sont définies ici pour plus de commodité.
 */

#ifndef _MAINBOARD_H
#define _MAINBOARD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

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
#include "modemGSM.h"


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
#define VERSION "2.11_D"
#else
#define VERSION "2.11  "
#endif
    
#define LCDCAR 16

    /**
     * \brief Enumération de la machine d'état principale.
     * \details Cette énumération définit les états d'application valides,
     * ces états déterminent le comportement de l'application à différents moments.
     */
    typedef enum
    {
        /* Application's state machine's initial state. */
        MAINBOARD_STATE_INIT = 0, /*!<Initialisation de l'application.*/
        MAINBOARD_STATE_SERVICE_TASKS, /*!<Etat de l'application en fonctionnement.*/
        MAINBOARD_STATE_DISPLAY_SELECT, /*!<Affichage choix du produit.*/
        MAINBOARD_STATE_DISPLAY_AMOUNT, /*!<Affichage du montant disponible.*/
        MAINBOARD_STATE_CHECK_DISPENSE, /*!<Affichage durant la distribution.*/
        MAINBOARD_STATE_CHANGE, /*!<Lance la procédure de change.*/
        MAINBOARD_STATE_ENABLE_DEVICES, /*!<Active les moyen de paiement.*/
        MAINBOARD_STATE_IDLE, /*!<Une opération longue est en cours.*/
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
     * \brief Handle du to déclenchant la procédure de trop perçu.
     */

    /**
     * \brief Handle du to déclenhant l'annulation de l'affichage du choix.
     */
    TimerHandle_t hTimerDisplaySelection;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Routines
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief
     * @return
     */
    TimerHandle_t hGetTimerCumul(void);
//
//    /**
//     * \brief
//     */
//    void vCreateTimerCumul(void);

    /**
     * \brief
     * @return
     */
    TimerHandle_t hGetTimerOverPay(void);

    /**
     * \brief
     */
    void vCreateTimerOverPay(void);

    /**
     * \brief Fixe l'état de la tâche de l'application
     * @param state Etat de la tâche de l'application à utiliser.
     */
    void setMainBoardTaskState(MAINBOARD_STATES state);

    /**
     * \brief Requête du montant à fournir.
     * @param amount Montant du produit.
     */
    void setAmountRequested(uint32_t amount);
    /**
     * \brief Requête du montant disponible.
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
    //     * \brief Lit le flag indiquant si les péruiphériques MDB sont prêt.
    //     * @return true si les périphériques sont initialisés
    //     */
    //    bool getMDBChecked(void);
    //
    //    /**
    //     * brief Fixe l'état du flag indiquant si le périphérique sont prêt
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
    void vMAINBOARD_Tasks(void);

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


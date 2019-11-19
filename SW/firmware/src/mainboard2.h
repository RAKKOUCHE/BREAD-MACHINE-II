/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mainboard2.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "MAINBOARD2_Initialize" and "MAINBOARD2_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "MAINBOARD2_STATES" definition).  Both
    are defined here for convenience.
 *******************************************************************************/

/**
 * \file mainboard2.h
 * 
 * \brief Ce fichier en-tête fournit les prototypes et les deéfinitions pour 
 * l'application.
 * 
 * \details Ce fichier d'en-tête fournit des prototypes de fonctions et 
 * des définitions de types de données pour l'application.  Certaines d'entre 
 * elles sont requises par le système (telles que la  "MAINBOARD2_Initialize" et 
 * "MAINBOARD2_Tasks") et certains d'entre eux sont seulement utilisés en 
 * interne par l'application (comme la définition "MAINBOARD2_STATES").  
 * Les deux sont définies ici pour plus de commodité.
 */

#ifndef _MAINBOARD2_H
#define _MAINBOARD2_H

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
#include "configuration.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "audits.h"
#include "hd44780.h"
#include "globaldef.h"
#include "parameters.h"

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
     * \brief Enumération de la machine d'état principale.
     * \details Cette énumération définit les états d'application valides, 
     * ces états déterminent le comportement de l'application à différents moments.
     */
    typedef enum
    {
        /* Application's state machine's initial state. */
        MAINBOARD2_STATE_INIT = 0, /*!<Initialisation de l'application*/
        MAINBOARD2_STATE_SERVICE_TASKS, /*!<Etat de l'application en fonctionnement*/
        MAINBOARD2_STATE_DISPLAY_CHOICE, /*!<Affichage choix du produit*/
    } MAINBOARD2_STATES;


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
     * \brief Structure contenant les données utilisés dans la tâche principale.
     */
    typedef struct
    {
        /* The application's current state */
        MAINBOARD2_STATES state;

        /* TODO: Define any additional data used by the application. */

    } MAINBOARD2_DATA;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Callback Routines
    // *****************************************************************************
    // *****************************************************************************
    /* These routines are called by drivers when certain events occur.
     */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Initialization and State Machine Functions
    // *****************************************************************************
    // *****************************************************************************

    /*******************************************************************************
      Function:
        void MAINBOARD2_Initialize ( void )

      Summary:
         MPLAB Harmony application initialization routine.

      Description:
        This function initializes the Harmony application.  It places the
        application in its initial state and prepares it to run so that its
        MAINBOARD2_Tasks function can be called.

      Precondition:
        All other system initialization routines should be called before calling
        this routine (in "SYS_Initialize").

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        MAINBOARD2_Initialize();
        </code>

      Remarks:
        This routine must be called from the SYS_Initialize function.
     */
    void MAINBOARD2_Initialize(void);


    /*******************************************************************************
      Function:
        void MAINBOARD2_Tasks ( void )

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
        MAINBOARD2_Tasks();
        </code>

      Remarks:
        This routine must be called from SYS_Tasks() routine.
     */
    void MAINBOARD2_Tasks(void);

    /**
     * @}
     */
#endif /* _MAINBOARD2_H */

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */


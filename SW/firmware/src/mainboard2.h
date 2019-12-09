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
 * \brief Ce fichier en-t�te fournit les prototypes et les de�finitions pour 
 * l'application.
 * 
 * \details Ce fichier d'en-t�te fournit des prototypes de fonctions et 
 * des d�finitions de types de donn�es pour l'application.  Certaines d'entre 
 * elles sont requises par le syst�me (telles que la  "MAINBOARD2_Initialize" et 
 * "MAINBOARD2_Tasks") et certains d'entre eux sont seulement utilis�s en 
 * interne par l'application (comme la d�finition "MAINBOARD2_STATES").  
 * Les deux sont d�finies ici pour plus de commodit�.
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
#include "peripheral/gpio/plib_gpio.h"
#include "config/default/peripheral/uart/plib_uart3.h"
#include "dataCommun.h"
#include "MDB/mdb.h"

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
        MAINBOARD2_STATE_INIT = 0, /*!<Initialisation de l'application.*/
        MAINBOARD2_STATE_SERVICE_TASKS, /*!<Etat de l'application en fonctionnement.*/
        MAINBOARD2_STATE_DISPLAY_CHOICE, /*!<Affichage choix du produit.*/
        MAINBOARD2_STATE_DISPLAY_AMOUNT, /*!<Affichage du montant disponible.*/
        MAINBOARD2_STATE_CHANGE, /*!<Lance la proc�dure de change.*/

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
     * \brief Structure contenant les donn�es utilis�s dans la t�che principale.
     */
    typedef struct
    {
        /* The application's current state */
        MAINBOARD2_STATES state; /*!<Etat de la t�che principale de l'application.*/
        int32_t lAmountDispo; /*!<Montant disponible pour un achat.*/
        uint32_t lAmountRequested; /*!<Montant demand� pour un produit s�lectionn�.*/
        bool isMDBChecked; /*!<Flag indiquant que les p�riph�riques MDB sont initalis�.*/
    } MAINBOARD2_DATA;

    /**
     * \brief Handle timer de cumul.
     */
    TimerHandle_t hTOCumul;
    
    /**
     * \brief Handle du to d�clenchant la proc�dure de trop per�u.
     */
    TimerHandle_t hTimerOverPay;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Routines
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Requ�te de l'�tat de la T�che de l'application
     * @return Etat de la t�che.
     */
    MAINBOARD2_STATES getMainBoardTaskState(void);

    /**
     * \brief Fixe l'�tat de la t�che de l'application
     * @param state Etat de la t�che de l'application � utiliser.
     */
    void setMainBoardTaskState(MAINBOARD2_STATES state);
    
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
    
    /**
     * \brief Lit le flag indiquant si les p�ruiph�riques MDB sont pr�t.
     * @return true si les p�riph�riques sont initialis�s
     */
    bool getMDBChecked(void);
    
    /**
     * brief Fixe l'�tat du flag indiquant si le p�riph�rique sont pr�t
     * @param isChecked Etat du flag choisi.
     */
    void setMDBChecked(bool isChecked);

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


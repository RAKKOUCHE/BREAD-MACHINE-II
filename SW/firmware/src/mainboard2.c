/** ***************************************************************************
 * \date 2019 11 08
 * 
 * \file mainboard2.c
 * 
 * \brief Ce fichier contient le code source pour le module principale de 
 * l'applicatin.
 * 
 * \details Ce fichier contient le code source du module principale de 
 * l'application. Il implémente la logique de la machine d'état de l'application 
 * et peut appeler les routines API des modules MPLAB Harmony du système, 
 * tels que les pilotes,  services système et middleware.  Toutefois, il
 *  n'appelle aucune des interfaces système (telles que les fonctions 
 * "Initialiser" et "Tâches") des modules du système ou  faire des suppositions 
 * sur le moment où ces fonctions sont exécutées s'appellent.  C'est de la 
 * responsabilité du système spécifique à la configuration fichiers.
 * 
 ******************************************************************************/

/*******************************************************************************
 *   MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    mainboard2.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "mainboard2.h"

/**
 * \addtogroup main
 * @{
 */
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the MAINBOARD2_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

MAINBOARD2_DATA mainboard2Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void MAINBOARD2_Initialize ( void )

  Remarks:
    See prototype in mainboard2.h.
 */

void MAINBOARD2_Initialize(void)
{
    /* Place the App state machine in its initial state. */
    mainboard2Data.state = MAINBOARD2_STATE_INIT;
    vLCDInit();
    vAuditsInit();


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void MAINBOARD2_Tasks ( void )

  Remarks:
    See prototype in mainboard2.h.
 */

void MAINBOARD2_Tasks(void)
{

    /* Check the application's current state. */
    switch(mainboard2Data.state)
    {
            /* Application's initial state. */
        case MAINBOARD2_STATE_INIT:
        {
            vHD44780Init();
            mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_CHOICE;
            vLCD_CLEAR();
            printf("%s", "MT DISTRIBUTION");
            vLCDGotoXY(1, 2);
            printf(" %s %s", "Version ", VERSION);
            delayMs(1 * SECONDE);
            break;
        }
        case MAINBOARD2_STATE_SERVICE_TASKS:
        {
            if(getIsRAZAudit())
            {
                setIsRAZAudit(false);
                mainboard2Data.state = MAINBOARD2_STATE_DISPLAY_CHOICE;
            }
            break;
        }
        case MAINBOARD2_STATE_DISPLAY_CHOICE:
            // <editor-fold desc="MAINBOARD2_STATE_DISPLAY_CHOICE"> 
        {
            mainboard2Data.state = MAINBOARD2_STATE_SERVICE_TASKS;
            vLCD_CLEAR();
            printf("%s", "  Choisssisez");
            vLCDGotoXY(1, 2);
            printf("%s", " votre produit");
            break;
        }// </editor-fold>
            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/**
 * @}
 */

/*******************************************************************************
 End of File
 */

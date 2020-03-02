/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    //Securisation des commandes moteurs.
    PWR_OutputEnable();
    PWR_Clear(); //Desactive la tension positive des moteurs des carrousels.
    BRK_OutputEnable();
    BRK_Set(); //Desavitve le freinage des moteurs des carrousels.

    CMD_CARROUSEL_1_OutputEnable();
    CMD_CARROUSEL_1_Set(); //Desactive la tension n?gative du moteur du carrousel 1.
    CMD_CARROUSEL_2_OutputEnable();
    CMD_CARROUSEL_2_Set(); //Desactive la tension n?gative du moteur du carrousel 2.
    CMD_CARROUSEL_3_OutputEnable();
    CMD_CARROUSEL_3_Set(); //Desactive la tension n?gative du moteur du carrousel 3.

    CMD_TRAP_P11_OutputEnable();
    CMD_TRAP_P11_Clear(); //Desactive la premi?re tension positive du moteur de la trappe 1.
    CMD_TRAP_P12_OutputEnable();
    CMD_TRAP_P12_Clear(); //Desactive la deuxi?me tension positive du moteur de la trappe 1.
    CMD_TRAP_N11_OutputEnable();
    CMD_TRAP_N11_Set(); //D?sactive la premi?re tension negative du moteur de la trappe 1.
    CMD_TRAP_N12_OutputEnable();
    CMD_TRAP_N12_Set(); //D?sactive la deuxieme tension negative du moteur de la trappe 1.

    CMD_TRAP_P21_OutputEnable();
    CMD_TRAP_P21_Clear(); //Desactive la premi?re tension positive du moteur de la trappe 2.
    CMD_TRAP_P22_OutputEnable();
    CMD_TRAP_P22_Clear(); //Desactive la deuxi?me tension positive du moteur de la trappe 2.
    CMD_TRAP_N21_OutputEnable();
    CMD_TRAP_N21_Set(); //D?sactive la premi?re tension negative du moteur de la trappe 2.
    CMD_TRAP_N22_OutputEnable();
    CMD_TRAP_N22_Set(); //D?sactive la deuxieme tension negative du moteur de la trappe 2.

    CMD_TRAP_P31_OutputEnable();
    CMD_TRAP_P31_Clear(); //Desactive la premi?re tension positive du moteur de la trappe 3.
    CMD_TRAP_P32_OutputEnable();
    CMD_TRAP_P32_Clear(); //Desactive la deuxi?me tension positive du moteur de la trappe 3.
    CMD_TRAP_N31_OutputEnable();
    CMD_TRAP_N31_Set(); //D?sactive la premi?re tension negative du moteur de la trappe 3.
    CMD_TRAP_N32_OutputEnable();
    CMD_TRAP_N32_Set(); //D?sactive la deuxieme tension negative du moteur de la trappe 3.

    /* Initialize all modules */
    SYS_Initialize(NULL);

    while(true)
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    /* Execution should not come here during normal operation */

    return( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */


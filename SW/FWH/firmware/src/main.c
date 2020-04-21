/*******************************************************************************
  MPLAB Harmony Project Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for an MPLAB Harmony project.

  Description:
    This file contains the "main" function for an MPLAB Harmony project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all MPLAB Harmony modules in the system and it calls the
    "SYS_Tasks" function from within a system-wide "super" loop to maintain
    their correct operation. These two functions are implemented in
    configuration-specific files (usually "system_init.c" and "system_tasks.c")
    in a configuration-specific folder under the "src/system_config" folder
    within this project's top-level folder.  An MPLAB Harmony project may have
    more than one configuration, each contained within it's own folder under
    the "system_config" folder.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

/** ****************************************************************************
 * \mainpage DOCUMENTATION DU LOGICIEL DE LA CARTE BREADMACHINE II VERSION PIC32MX575F512L
 *
 *  <b>RASoftware</b> <BR>
 *	2 rue Georges MELIES <BR>
 *   78390 BOIS D'ARCY <BR>
 *	+33 651 60 40 47 <BR>
 *	<a href = "http://www.rasoftware.fr">http://www.rasoftware.fr </a> <BR><BR>
 *<CENTER>Copyright<b>© RASoftware</b> 2019 </CENTER>  <BR>
 *
 *
 * The information contained here-in is the property of RASoftware and is not
 * to be disclosed or used without the prior written permission of RASoftware.
 * This	copyright extends to all media in which this information may be
 * preserved including magnetic storage, computer print-out or visual
 * display.
 * <CENTER>___________________________________________</CENTER><BR><BR>
 *
 * Documentation du logiciel qui gère l'électronique de la carte Bread machine version 2B
 **/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "system/common/sys_module.h"   // SYS function prototypes
#include "communDef.h"

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
    CMD_CARROUSEL_1_Set(); //Desactive la tension négative du moteur du carrousel 1.
    CMD_CARROUSEL_2_OutputEnable();
    CMD_CARROUSEL_2_Set(); //Desactive la tension négative du moteur du carrousel 2.
    CMD_CARROUSEL_3_OutputEnable();
    CMD_CARROUSEL_3_Set(); //Desactive la tension négative du moteur du carrousel 3.

    CMD_TRAP_P11_OutputEnable();
    CMD_TRAP_P11_Clear(); //Desactive la première tension positive du moteur de la trappe 1.
    CMD_TRAP_P12_OutputEnable();
    CMD_TRAP_P12_Clear(); //Desactive la deuxième tension positive du moteur de la trappe 1.
    CMD_TRAP_N11_OutputEnable();
    CMD_TRAP_N11_Set(); //D?sactive la première tension négative du moteur de la trappe 1.
    CMD_TRAP_N12_OutputEnable();
    CMD_TRAP_N12_Set(); //D?sactive la deuxieme tension négative du moteur de la trappe 1.

    CMD_TRAP_P21_OutputEnable();
    CMD_TRAP_P21_Clear(); //Desactive la première tension positive du moteur de la trappe 2.
    CMD_TRAP_P22_OutputEnable();
    CMD_TRAP_P22_Clear(); //Desactive la deuxième tension positive du moteur de la trappe 2.
    CMD_TRAP_N21_OutputEnable();
    CMD_TRAP_N21_Set(); //D?sactive la première tension négative du moteur de la trappe 2.
    CMD_TRAP_N22_OutputEnable();
    CMD_TRAP_N22_Set(); //D?sactive la deuxieme tension négative du moteur de la trappe 2.

    CMD_TRAP_P31_OutputEnable();
    CMD_TRAP_P31_Clear(); //Desactive la première tension positive du moteur de la trappe 3.
    CMD_TRAP_P32_OutputEnable();
    CMD_TRAP_P32_Clear(); //Desactive la deuxième tension positive du moteur de la trappe 3.
    CMD_TRAP_N31_OutputEnable();
    CMD_TRAP_N31_Set(); //D?sactive la première tension négative du moteur de la trappe 3.
    CMD_TRAP_N32_OutputEnable();
    CMD_TRAP_N32_Set(); //D?sactive la deuxieme tension négative du moteur de la trappe 3.

    /* Initialize all MPLAB Harmony modules, including application(s). */
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


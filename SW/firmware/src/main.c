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


/** ****************************************************************************
 * \mainpage DOCUMENTATION DU LOGICIEL DE LA CARTE BREADMACHINE II
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
 * Documentation du logiciel qui gère l'éléctronique de la carte Bread machine version 2
 **/

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/


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
#include "configuration.h"
#include "FreeRTOS.h"
#include "task.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

    /**
     * \brief Enum�ration de la machine d'�tat principale.
     * \details Cette �num�ration d�finit les �tats d'application valides, 
     * ces �tats d�terminent le comportement de l'application � diff�rents moments.
     */
typedef enum
{
    /* Application's state machine's initial state. */
    MAINBOARD2_STATE_INIT=0, /*!<Initialisation de l'application*/
    MAINBOARD2_STATE_SERVICE_TASKS, /*!<Etat de l'application en fonctionnement*/
    /* TODO: Define states used by the application state machine. */

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
void MAINBOARD2_Initialize ( void );


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
void MAINBOARD2_Tasks( void );



#endif /* _MAINBOARD2_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */


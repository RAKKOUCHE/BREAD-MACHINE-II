/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config PWP =        OFF
#pragma config BWP =        OFF
#pragma config CP =         OFF


/*** DEVCFG1 ***/
#pragma config FNOSC =      FRCPLL
#pragma config FPBDIV =     DIV_2
#pragma config FSOSCEN =    OFF
#pragma config IESO =       ON
#pragma config POSCMOD =    OFF
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     OFF
#pragma config FWDTWINSZ =  WINSZ_25


/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_24
#pragma config FPLLODIV =   DIV_1
#pragma config UPLLEN =     OFF
#pragma config UPLLIDIV =   DIV_2

/*** DEVCFG3 ***/
#pragma config FSRSSEL =    PRIORITY_7
#pragma config FVBUSONIO =  ON
#pragma config USERID =     0xffff
#pragma config PMDL1WAY =   OFF
#pragma config IOL1WAY =    OFF
#pragma config FUSBIDIO =   ON




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_AT24 Initialization Data">

/* I2C PLIB Interface Initialization for AT24 Driver */
const DRV_AT24_PLIB_INTERFACE drvAT24PlibAPI = {

    /* I2C PLIB WriteRead function */
    .writeRead = (DRV_AT24_PLIB_WRITE_READ)I2C1_WriteRead,

    /* I2C PLIB Write function */
    .write = (DRV_AT24_PLIB_WRITE)I2C1_Write,

    /* I2C PLIB Read function */
    .read = (DRV_AT24_PLIB_READ)I2C1_Read,

    /* I2C PLIB Transfer Status function */
    .isBusy = (DRV_AT24_PLIB_IS_BUSY)I2C1_IsBusy,

    /* I2C PLIB Error Status function */
    .errorGet = (DRV_AT24_PLIB_ERROR_GET)I2C1_ErrorGet,

    /* I2C PLIB Callback Register */
    .callbackRegister = (DRV_AT24_PLIB_CALLBACK_REGISTER)I2C1_CallbackRegister,
};

/* AT24 Driver Initialization Data */
const DRV_AT24_INIT drvAT24InitData =
{
    /* I2C PLIB API  interface*/
    .i2cPlib = &drvAT24PlibAPI,

    /* 7-bit I2C Slave address */
    .slaveAddress = 0x50,

    /* EEPROM Page Size in bytes */
    .pageSize = DRV_AT24_EEPROM_PAGE_SIZE,

    /* Total size of the EEPROM in bytes */
    .flashSize = DRV_AT24_EEPROM_FLASH_SIZE,

    /* AT24 Number of clients */
    .numClients = DRV_AT24_CLIENTS_NUMBER_IDX,

    .blockStartAddress =    0x0,
};

// </editor-fold>


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************



/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();

  
    CLK_Initialize();
	GPIO_Initialize();

    /* Configure KSEG0 as cacheable memory. This is needed for Prefetch Buffer */
    __builtin_mtc0(16, 0,(__builtin_mfc0(16, 0) | 0x3));

    /* Configure Flash Wait States and Prefetch */
    CHECONbits.PFMWS = 2;
    CHECONbits.PREFEN = 3;

    /* Set the SRAM wait states to zero */
    BMXCONbits.BMXWSDRM = 0;




	UART3_Initialize();

    I2C1_Initialize();

    sysObj.drvAT24 = DRV_AT24_Initialize(DRV_AT24_INDEX, (SYS_MODULE_INIT *)&drvAT24InitData);




    MAINBOARD2_Initialize();


    EVIC_Initialize();

	/* Enable global interrupts */
    __builtin_enable_interrupts();


}


/*******************************************************************************
 End of File
*/

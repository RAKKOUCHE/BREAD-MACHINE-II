/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************

/*** Macros for BTN_MTR_2 pin ***/
#define BTN_MTR_2_Set()               (LATESET = (1<<5))
#define BTN_MTR_2_Clear()             (LATECLR = (1<<5))
#define BTN_MTR_2_Toggle()            (LATEINV= (1<<5))
#define BTN_MTR_2_Get()               ((PORTE >> 5) & 0x1)
#define BTN_MTR_2_OutputEnable()      (TRISECLR = (1<<5))
#define BTN_MTR_2_InputEnable()       (TRISESET = (1<<5))
#define BTN_MTR_2_PIN                  GPIO_PIN_RE5
/*** Macros for BTN_MTR_3 pin ***/
#define BTN_MTR_3_Set()               (LATESET = (1<<6))
#define BTN_MTR_3_Clear()             (LATECLR = (1<<6))
#define BTN_MTR_3_Toggle()            (LATEINV= (1<<6))
#define BTN_MTR_3_Get()               ((PORTE >> 6) & 0x1)
#define BTN_MTR_3_OutputEnable()      (TRISECLR = (1<<6))
#define BTN_MTR_3_InputEnable()       (TRISESET = (1<<6))
#define BTN_MTR_3_PIN                  GPIO_PIN_RE6
/*** Macros for CMD_TRAP_N21 pin ***/
#define CMD_TRAP_N21_Set()               (LATESET = (1<<7))
#define CMD_TRAP_N21_Clear()             (LATECLR = (1<<7))
#define CMD_TRAP_N21_Toggle()            (LATEINV= (1<<7))
#define CMD_TRAP_N21_Get()               ((PORTE >> 7) & 0x1)
#define CMD_TRAP_N21_OutputEnable()      (TRISECLR = (1<<7))
#define CMD_TRAP_N21_InputEnable()       (TRISESET = (1<<7))
#define CMD_TRAP_N21_PIN                  GPIO_PIN_RE7
/*** Macros for LED_MDB pin ***/
#define LED_MDB_Set()               (LATCSET = (1<<1))
#define LED_MDB_Clear()             (LATCCLR = (1<<1))
#define LED_MDB_Toggle()            (LATCINV= (1<<1))
#define LED_MDB_Get()               ((PORTC >> 1) & 0x1)
#define LED_MDB_OutputEnable()      (TRISCCLR = (1<<1))
#define LED_MDB_InputEnable()       (TRISCSET = (1<<1))
#define LED_MDB_PIN                  GPIO_PIN_RC1
/*** Macros for DOOR pin ***/
#define DOOR_Set()               (LATCSET = (1<<2))
#define DOOR_Clear()             (LATCCLR = (1<<2))
#define DOOR_Toggle()            (LATCINV= (1<<2))
#define DOOR_Get()               ((PORTC >> 2) & 0x1)
#define DOOR_OutputEnable()      (TRISCCLR = (1<<2))
#define DOOR_InputEnable()       (TRISCSET = (1<<2))
#define DOOR_PIN                  GPIO_PIN_RC2
/*** Macros for TOP_1 pin ***/
#define TOP_1_Set()               (LATCSET = (1<<3))
#define TOP_1_Clear()             (LATCCLR = (1<<3))
#define TOP_1_Toggle()            (LATCINV= (1<<3))
#define TOP_1_Get()               ((PORTC >> 3) & 0x1)
#define TOP_1_OutputEnable()      (TRISCCLR = (1<<3))
#define TOP_1_InputEnable()       (TRISCSET = (1<<3))
#define TOP_1_PIN                  GPIO_PIN_RC3
/*** Macros for TOP_2 pin ***/
#define TOP_2_Set()               (LATCSET = (1<<4))
#define TOP_2_Clear()             (LATCCLR = (1<<4))
#define TOP_2_Toggle()            (LATCINV= (1<<4))
#define TOP_2_Get()               ((PORTC >> 4) & 0x1)
#define TOP_2_OutputEnable()      (TRISCCLR = (1<<4))
#define TOP_2_InputEnable()       (TRISCSET = (1<<4))
#define TOP_2_PIN                  GPIO_PIN_RC4
/*** Macros for DQ pin ***/
#define DQ_Set()               (LATGSET = (1<<6))
#define DQ_Clear()             (LATGCLR = (1<<6))
#define DQ_Toggle()            (LATGINV= (1<<6))
#define DQ_Get()               ((PORTG >> 6) & 0x1)
#define DQ_OutputEnable()      (TRISGCLR = (1<<6))
#define DQ_InputEnable()       (TRISGSET = (1<<6))
#define DQ_PIN                  GPIO_PIN_RG6
/*** Macros for LED_SYS pin ***/
#define LED_SYS_Set()               (LATASET = (1<<0))
#define LED_SYS_Clear()             (LATACLR = (1<<0))
#define LED_SYS_Toggle()            (LATAINV= (1<<0))
#define LED_SYS_Get()               ((PORTA >> 0) & 0x1)
#define LED_SYS_OutputEnable()      (TRISACLR = (1<<0))
#define LED_SYS_InputEnable()       (TRISASET = (1<<0))
#define LED_SYS_PIN                  GPIO_PIN_RA0
/*** Macros for CMD_TRAP_N32 pin ***/
#define CMD_TRAP_N32_Set()               (LATESET = (1<<8))
#define CMD_TRAP_N32_Clear()             (LATECLR = (1<<8))
#define CMD_TRAP_N32_Toggle()            (LATEINV= (1<<8))
#define CMD_TRAP_N32_Get()               ((PORTE >> 8) & 0x1)
#define CMD_TRAP_N32_OutputEnable()      (TRISECLR = (1<<8))
#define CMD_TRAP_N32_InputEnable()       (TRISESET = (1<<8))
#define CMD_TRAP_N32_PIN                  GPIO_PIN_RE8
/*** Macros for CMD_TRAP_N31 pin ***/
#define CMD_TRAP_N31_Set()               (LATESET = (1<<9))
#define CMD_TRAP_N31_Clear()             (LATECLR = (1<<9))
#define CMD_TRAP_N31_Toggle()            (LATEINV= (1<<9))
#define CMD_TRAP_N31_Get()               ((PORTE >> 9) & 0x1)
#define CMD_TRAP_N31_OutputEnable()      (TRISECLR = (1<<9))
#define CMD_TRAP_N31_InputEnable()       (TRISESET = (1<<9))
#define CMD_TRAP_N31_PIN                  GPIO_PIN_RE9
/*** Macros for CMD_TRAP_P22 pin ***/
#define CMD_TRAP_P22_Set()               (LATBSET = (1<<5))
#define CMD_TRAP_P22_Clear()             (LATBCLR = (1<<5))
#define CMD_TRAP_P22_Toggle()            (LATBINV= (1<<5))
#define CMD_TRAP_P22_Get()               ((PORTB >> 5) & 0x1)
#define CMD_TRAP_P22_OutputEnable()      (TRISBCLR = (1<<5))
#define CMD_TRAP_P22_InputEnable()       (TRISBSET = (1<<5))
#define CMD_TRAP_P22_PIN                  GPIO_PIN_RB5
/*** Macros for CMD_TRAP_P11 pin ***/
#define CMD_TRAP_P11_Set()               (LATBSET = (1<<4))
#define CMD_TRAP_P11_Clear()             (LATBCLR = (1<<4))
#define CMD_TRAP_P11_Toggle()            (LATBINV= (1<<4))
#define CMD_TRAP_P11_Get()               ((PORTB >> 4) & 0x1)
#define CMD_TRAP_P11_OutputEnable()      (TRISBCLR = (1<<4))
#define CMD_TRAP_P11_InputEnable()       (TRISBSET = (1<<4))
#define CMD_TRAP_P11_PIN                  GPIO_PIN_RB4
/*** Macros for CMD_TRAP_P12 pin ***/
#define CMD_TRAP_P12_Set()               (LATBSET = (1<<3))
#define CMD_TRAP_P12_Clear()             (LATBCLR = (1<<3))
#define CMD_TRAP_P12_Toggle()            (LATBINV= (1<<3))
#define CMD_TRAP_P12_Get()               ((PORTB >> 3) & 0x1)
#define CMD_TRAP_P12_OutputEnable()      (TRISBCLR = (1<<3))
#define CMD_TRAP_P12_InputEnable()       (TRISBSET = (1<<3))
#define CMD_TRAP_P12_PIN                  GPIO_PIN_RB3
/*** Macros for CMD_TRAP_N22 pin ***/
#define CMD_TRAP_N22_Set()               (LATBSET = (1<<2))
#define CMD_TRAP_N22_Clear()             (LATBCLR = (1<<2))
#define CMD_TRAP_N22_Toggle()            (LATBINV= (1<<2))
#define CMD_TRAP_N22_Get()               ((PORTB >> 2) & 0x1)
#define CMD_TRAP_N22_OutputEnable()      (TRISBCLR = (1<<2))
#define CMD_TRAP_N22_InputEnable()       (TRISBSET = (1<<2))
#define CMD_TRAP_N22_PIN                  GPIO_PIN_RB2
/*** Macros for CMD_TRAP_P21 pin ***/
#define CMD_TRAP_P21_Set()               (LATBSET = (1<<6))
#define CMD_TRAP_P21_Clear()             (LATBCLR = (1<<6))
#define CMD_TRAP_P21_Toggle()            (LATBINV= (1<<6))
#define CMD_TRAP_P21_Get()               ((PORTB >> 6) & 0x1)
#define CMD_TRAP_P21_OutputEnable()      (TRISBCLR = (1<<6))
#define CMD_TRAP_P21_InputEnable()       (TRISBSET = (1<<6))
#define CMD_TRAP_P21_PIN                  GPIO_PIN_RB6
/*** Macros for CMD_TRAP_P32 pin ***/
#define CMD_TRAP_P32_Set()               (LATBSET = (1<<7))
#define CMD_TRAP_P32_Clear()             (LATBCLR = (1<<7))
#define CMD_TRAP_P32_Toggle()            (LATBINV= (1<<7))
#define CMD_TRAP_P32_Get()               ((PORTB >> 7) & 0x1)
#define CMD_TRAP_P32_OutputEnable()      (TRISBCLR = (1<<7))
#define CMD_TRAP_P32_InputEnable()       (TRISBSET = (1<<7))
#define CMD_TRAP_P32_PIN                  GPIO_PIN_RB7
/*** Macros for RTNMTR pin ***/
#define RTNMTR_Set()               (LATASET = (1<<9))
#define RTNMTR_Clear()             (LATACLR = (1<<9))
#define RTNMTR_Toggle()            (LATAINV= (1<<9))
#define RTNMTR_Get()               ((PORTA >> 9) & 0x1)
#define RTNMTR_OutputEnable()      (TRISACLR = (1<<9))
#define RTNMTR_InputEnable()       (TRISASET = (1<<9))
#define RTNMTR_PIN                  GPIO_PIN_RA9
/*** Macros for BTNRTN pin ***/
#define BTNRTN_Set()               (LATASET = (1<<10))
#define BTNRTN_Clear()             (LATACLR = (1<<10))
#define BTNRTN_Toggle()            (LATAINV= (1<<10))
#define BTNRTN_Get()               ((PORTA >> 10) & 0x1)
#define BTNRTN_OutputEnable()      (TRISACLR = (1<<10))
#define BTNRTN_InputEnable()       (TRISASET = (1<<10))
#define BTNRTN_PIN                  GPIO_PIN_RA10
/*** Macros for CMD_TRAP_P31 pin ***/
#define CMD_TRAP_P31_Set()               (LATBSET = (1<<8))
#define CMD_TRAP_P31_Clear()             (LATBCLR = (1<<8))
#define CMD_TRAP_P31_Toggle()            (LATBINV= (1<<8))
#define CMD_TRAP_P31_Get()               ((PORTB >> 8) & 0x1)
#define CMD_TRAP_P31_OutputEnable()      (TRISBCLR = (1<<8))
#define CMD_TRAP_P31_InputEnable()       (TRISBSET = (1<<8))
#define CMD_TRAP_P31_PIN                  GPIO_PIN_RB8
/*** Macros for BRK pin ***/
#define BRK_Set()               (LATBSET = (1<<9))
#define BRK_Clear()             (LATBCLR = (1<<9))
#define BRK_Toggle()            (LATBINV= (1<<9))
#define BRK_Get()               ((PORTB >> 9) & 0x1)
#define BRK_OutputEnable()      (TRISBCLR = (1<<9))
#define BRK_InputEnable()       (TRISBSET = (1<<9))
#define BRK_PIN                  GPIO_PIN_RB9
/*** Macros for CMD_CARROUSEL_1 pin ***/
#define CMD_CARROUSEL_1_Set()               (LATBSET = (1<<10))
#define CMD_CARROUSEL_1_Clear()             (LATBCLR = (1<<10))
#define CMD_CARROUSEL_1_Toggle()            (LATBINV= (1<<10))
#define CMD_CARROUSEL_1_Get()               ((PORTB >> 10) & 0x1)
#define CMD_CARROUSEL_1_OutputEnable()      (TRISBCLR = (1<<10))
#define CMD_CARROUSEL_1_InputEnable()       (TRISBSET = (1<<10))
#define CMD_CARROUSEL_1_PIN                  GPIO_PIN_RB10
/*** Macros for CMD_CARROUSEL_2 pin ***/
#define CMD_CARROUSEL_2_Set()               (LATBSET = (1<<11))
#define CMD_CARROUSEL_2_Clear()             (LATBCLR = (1<<11))
#define CMD_CARROUSEL_2_Toggle()            (LATBINV= (1<<11))
#define CMD_CARROUSEL_2_Get()               ((PORTB >> 11) & 0x1)
#define CMD_CARROUSEL_2_OutputEnable()      (TRISBCLR = (1<<11))
#define CMD_CARROUSEL_2_InputEnable()       (TRISBSET = (1<<11))
#define CMD_CARROUSEL_2_PIN                  GPIO_PIN_RB11
/*** Macros for LCD_RS pin ***/
#define LCD_RS_Set()               (LATASET = (1<<1))
#define LCD_RS_Clear()             (LATACLR = (1<<1))
#define LCD_RS_Toggle()            (LATAINV= (1<<1))
#define LCD_RS_Get()               ((PORTA >> 1) & 0x1)
#define LCD_RS_OutputEnable()      (TRISACLR = (1<<1))
#define LCD_RS_InputEnable()       (TRISASET = (1<<1))
#define LCD_RS_PIN                  GPIO_PIN_RA1
/*** Macros for CS pin ***/
#define CS_Set()               (LATFSET = (1<<13))
#define CS_Clear()             (LATFCLR = (1<<13))
#define CS_Toggle()            (LATFINV= (1<<13))
#define CS_Get()               ((PORTF >> 13) & 0x1)
#define CS_OutputEnable()      (TRISFCLR = (1<<13))
#define CS_InputEnable()       (TRISFSET = (1<<13))
#define CS_PIN                  GPIO_PIN_RF13
/*** Macros for GSM_CTS pin ***/
#define GSM_CTS_Set()               (LATFSET = (1<<12))
#define GSM_CTS_Clear()             (LATFCLR = (1<<12))
#define GSM_CTS_Toggle()            (LATFINV= (1<<12))
#define GSM_CTS_Get()               ((PORTF >> 12) & 0x1)
#define GSM_CTS_OutputEnable()      (TRISFCLR = (1<<12))
#define GSM_CTS_InputEnable()       (TRISFSET = (1<<12))
#define GSM_CTS_PIN                  GPIO_PIN_RF12
/*** Macros for CMD_CARROUSEL_3 pin ***/
#define CMD_CARROUSEL_3_Set()               (LATBSET = (1<<12))
#define CMD_CARROUSEL_3_Clear()             (LATBCLR = (1<<12))
#define CMD_CARROUSEL_3_Toggle()            (LATBINV= (1<<12))
#define CMD_CARROUSEL_3_Get()               ((PORTB >> 12) & 0x1)
#define CMD_CARROUSEL_3_OutputEnable()      (TRISBCLR = (1<<12))
#define CMD_CARROUSEL_3_InputEnable()       (TRISBSET = (1<<12))
#define CMD_CARROUSEL_3_PIN                  GPIO_PIN_RB12
/*** Macros for LCD_RW pin ***/
#define LCD_RW_Set()               (LATASET = (1<<2))
#define LCD_RW_Clear()             (LATACLR = (1<<2))
#define LCD_RW_Toggle()            (LATAINV= (1<<2))
#define LCD_RW_Get()               ((PORTA >> 2) & 0x1)
#define LCD_RW_OutputEnable()      (TRISACLR = (1<<2))
#define LCD_RW_InputEnable()       (TRISASET = (1<<2))
#define LCD_RW_PIN                  GPIO_PIN_RA2
/*** Macros for LCD_EN pin ***/
#define LCD_EN_Set()               (LATASET = (1<<3))
#define LCD_EN_Clear()             (LATACLR = (1<<3))
#define LCD_EN_Toggle()            (LATAINV= (1<<3))
#define LCD_EN_Get()               ((PORTA >> 3) & 0x1)
#define LCD_EN_OutputEnable()      (TRISACLR = (1<<3))
#define LCD_EN_InputEnable()       (TRISASET = (1<<3))
#define LCD_EN_PIN                  GPIO_PIN_RA3
/*** Macros for LCD_D4 pin ***/
#define LCD_D4_Set()               (LATASET = (1<<4))
#define LCD_D4_Clear()             (LATACLR = (1<<4))
#define LCD_D4_Toggle()            (LATAINV= (1<<4))
#define LCD_D4_Get()               ((PORTA >> 4) & 0x1)
#define LCD_D4_OutputEnable()      (TRISACLR = (1<<4))
#define LCD_D4_InputEnable()       (TRISASET = (1<<4))
#define LCD_D4_PIN                  GPIO_PIN_RA4
/*** Macros for LCD_D5 pin ***/
#define LCD_D5_Set()               (LATASET = (1<<5))
#define LCD_D5_Clear()             (LATACLR = (1<<5))
#define LCD_D5_Toggle()            (LATAINV= (1<<5))
#define LCD_D5_Get()               ((PORTA >> 5) & 0x1)
#define LCD_D5_OutputEnable()      (TRISACLR = (1<<5))
#define LCD_D5_InputEnable()       (TRISASET = (1<<5))
#define LCD_D5_PIN                  GPIO_PIN_RA5
/*** Macros for TOP_3 pin ***/
#define TOP_3_Set()               (LATCSET = (1<<12))
#define TOP_3_Clear()             (LATCCLR = (1<<12))
#define TOP_3_Toggle()            (LATCINV= (1<<12))
#define TOP_3_Get()               ((PORTC >> 12) & 0x1)
#define TOP_3_OutputEnable()      (TRISCCLR = (1<<12))
#define TOP_3_InputEnable()       (TRISCSET = (1<<12))
#define TOP_3_PIN                  GPIO_PIN_RC12
/*** Macros for BOT_3 pin ***/
#define BOT_3_Set()               (LATCSET = (1<<15))
#define BOT_3_Clear()             (LATCCLR = (1<<15))
#define BOT_3_Toggle()            (LATCINV= (1<<15))
#define BOT_3_Get()               ((PORTC >> 15) & 0x1)
#define BOT_3_OutputEnable()      (TRISCCLR = (1<<15))
#define BOT_3_InputEnable()       (TRISCSET = (1<<15))
#define BOT_3_PIN                  GPIO_PIN_RC15
/*** Macros for CMD_TRAP_N12 pin ***/
#define CMD_TRAP_N12_Set()               (LATASET = (1<<14))
#define CMD_TRAP_N12_Clear()             (LATACLR = (1<<14))
#define CMD_TRAP_N12_Toggle()            (LATAINV= (1<<14))
#define CMD_TRAP_N12_Get()               ((PORTA >> 14) & 0x1)
#define CMD_TRAP_N12_OutputEnable()      (TRISACLR = (1<<14))
#define CMD_TRAP_N12_InputEnable()       (TRISASET = (1<<14))
#define CMD_TRAP_N12_PIN                  GPIO_PIN_RA14
/*** Macros for CMD_TRAP_N11 pin ***/
#define CMD_TRAP_N11_Set()               (LATASET = (1<<15))
#define CMD_TRAP_N11_Clear()             (LATACLR = (1<<15))
#define CMD_TRAP_N11_Toggle()            (LATAINV= (1<<15))
#define CMD_TRAP_N11_Get()               ((PORTA >> 15) & 0x1)
#define CMD_TRAP_N11_OutputEnable()      (TRISACLR = (1<<15))
#define CMD_TRAP_N11_InputEnable()       (TRISASET = (1<<15))
#define CMD_TRAP_N11_PIN                  GPIO_PIN_RA15
/*** Macros for BTN_2 pin ***/
#define BTN_2_Set()               (LATDSET = (1<<8))
#define BTN_2_Clear()             (LATDCLR = (1<<8))
#define BTN_2_Toggle()            (LATDINV= (1<<8))
#define BTN_2_Get()               ((PORTD >> 8) & 0x1)
#define BTN_2_OutputEnable()      (TRISDCLR = (1<<8))
#define BTN_2_InputEnable()       (TRISDSET = (1<<8))
#define BTN_2_PIN                  GPIO_PIN_RD8
/*** Macros for BTN_3 pin ***/
#define BTN_3_Set()               (LATDSET = (1<<9))
#define BTN_3_Clear()             (LATDCLR = (1<<9))
#define BTN_3_Toggle()            (LATDINV= (1<<9))
#define BTN_3_Get()               ((PORTD >> 9) & 0x1)
#define BTN_3_OutputEnable()      (TRISDCLR = (1<<9))
#define BTN_3_InputEnable()       (TRISDSET = (1<<9))
#define BTN_3_PIN                  GPIO_PIN_RD9
/*** Macros for TAKE_1_1 pin ***/
#define TAKE_1_1_Set()               (LATDSET = (1<<10))
#define TAKE_1_1_Clear()             (LATDCLR = (1<<10))
#define TAKE_1_1_Toggle()            (LATDINV= (1<<10))
#define TAKE_1_1_Get()               ((PORTD >> 10) & 0x1)
#define TAKE_1_1_OutputEnable()      (TRISDCLR = (1<<10))
#define TAKE_1_1_InputEnable()       (TRISDSET = (1<<10))
#define TAKE_1_1_PIN                  GPIO_PIN_RD10
/*** Macros for TAKE_1_2 pin ***/
#define TAKE_1_2_Set()               (LATDSET = (1<<11))
#define TAKE_1_2_Clear()             (LATDCLR = (1<<11))
#define TAKE_1_2_Toggle()            (LATDINV= (1<<11))
#define TAKE_1_2_Get()               ((PORTD >> 11) & 0x1)
#define TAKE_1_2_OutputEnable()      (TRISDCLR = (1<<11))
#define TAKE_1_2_InputEnable()       (TRISDSET = (1<<11))
#define TAKE_1_2_PIN                  GPIO_PIN_RD11
/*** Macros for BUZZER pin ***/
#define BUZZER_Set()               (LATDSET = (1<<0))
#define BUZZER_Clear()             (LATDCLR = (1<<0))
#define BUZZER_Toggle()            (LATDINV= (1<<0))
#define BUZZER_Get()               ((PORTD >> 0) & 0x1)
#define BUZZER_OutputEnable()      (TRISDCLR = (1<<0))
#define BUZZER_InputEnable()       (TRISDSET = (1<<0))
#define BUZZER_PIN                  GPIO_PIN_RD0
/*** Macros for BOT_1 pin ***/
#define BOT_1_Set()               (LATCSET = (1<<13))
#define BOT_1_Clear()             (LATCCLR = (1<<13))
#define BOT_1_Toggle()            (LATCINV= (1<<13))
#define BOT_1_Get()               ((PORTC >> 13) & 0x1)
#define BOT_1_OutputEnable()      (TRISCCLR = (1<<13))
#define BOT_1_InputEnable()       (TRISCSET = (1<<13))
#define BOT_1_PIN                  GPIO_PIN_RC13
/*** Macros for BOT_2 pin ***/
#define BOT_2_Set()               (LATCSET = (1<<14))
#define BOT_2_Clear()             (LATCCLR = (1<<14))
#define BOT_2_Toggle()            (LATCINV= (1<<14))
#define BOT_2_Get()               ((PORTC >> 14) & 0x1)
#define BOT_2_OutputEnable()      (TRISCCLR = (1<<14))
#define BOT_2_InputEnable()       (TRISCSET = (1<<14))
#define BOT_2_PIN                  GPIO_PIN_RC14
/*** Macros for PWR pin ***/
#define PWR_Set()               (LATDSET = (1<<1))
#define PWR_Clear()             (LATDCLR = (1<<1))
#define PWR_Toggle()            (LATDINV= (1<<1))
#define PWR_Get()               ((PORTD >> 1) & 0x1)
#define PWR_OutputEnable()      (TRISDCLR = (1<<1))
#define PWR_InputEnable()       (TRISDSET = (1<<1))
#define PWR_PIN                  GPIO_PIN_RD1
/*** Macros for TAKE_3_1 pin ***/
#define TAKE_3_1_Set()               (LATDSET = (1<<2))
#define TAKE_3_1_Clear()             (LATDCLR = (1<<2))
#define TAKE_3_1_Toggle()            (LATDINV= (1<<2))
#define TAKE_3_1_Get()               ((PORTD >> 2) & 0x1)
#define TAKE_3_1_OutputEnable()      (TRISDCLR = (1<<2))
#define TAKE_3_1_InputEnable()       (TRISDSET = (1<<2))
#define TAKE_3_1_PIN                  GPIO_PIN_RD2
/*** Macros for TAKE_3_2 pin ***/
#define TAKE_3_2_Set()               (LATDSET = (1<<3))
#define TAKE_3_2_Clear()             (LATDCLR = (1<<3))
#define TAKE_3_2_Toggle()            (LATDINV= (1<<3))
#define TAKE_3_2_Get()               ((PORTD >> 3) & 0x1)
#define TAKE_3_2_OutputEnable()      (TRISDCLR = (1<<3))
#define TAKE_3_2_InputEnable()       (TRISDSET = (1<<3))
#define TAKE_3_2_PIN                  GPIO_PIN_RD3
/*** Macros for TAKE_2_1 pin ***/
#define TAKE_2_1_Set()               (LATDSET = (1<<12))
#define TAKE_2_1_Clear()             (LATDCLR = (1<<12))
#define TAKE_2_1_Toggle()            (LATDINV= (1<<12))
#define TAKE_2_1_Get()               ((PORTD >> 12) & 0x1)
#define TAKE_2_1_OutputEnable()      (TRISDCLR = (1<<12))
#define TAKE_2_1_InputEnable()       (TRISDSET = (1<<12))
#define TAKE_2_1_PIN                  GPIO_PIN_RD12
/*** Macros for TAKE_2_2 pin ***/
#define TAKE_2_2_Set()               (LATDSET = (1<<13))
#define TAKE_2_2_Clear()             (LATDCLR = (1<<13))
#define TAKE_2_2_Toggle()            (LATDINV= (1<<13))
#define TAKE_2_2_Get()               ((PORTD >> 13) & 0x1)
#define TAKE_2_2_OutputEnable()      (TRISDCLR = (1<<13))
#define TAKE_2_2_InputEnable()       (TRISDSET = (1<<13))
#define TAKE_2_2_PIN                  GPIO_PIN_RD13
/*** Macros for LED_BTN_1 pin ***/
#define LED_BTN_1_Set()               (LATDSET = (1<<4))
#define LED_BTN_1_Clear()             (LATDCLR = (1<<4))
#define LED_BTN_1_Toggle()            (LATDINV= (1<<4))
#define LED_BTN_1_Get()               ((PORTD >> 4) & 0x1)
#define LED_BTN_1_OutputEnable()      (TRISDCLR = (1<<4))
#define LED_BTN_1_InputEnable()       (TRISDSET = (1<<4))
#define LED_BTN_1_PIN                  GPIO_PIN_RD4
/*** Macros for LED_BTN_2 pin ***/
#define LED_BTN_2_Set()               (LATDSET = (1<<5))
#define LED_BTN_2_Clear()             (LATDCLR = (1<<5))
#define LED_BTN_2_Toggle()            (LATDINV= (1<<5))
#define LED_BTN_2_Get()               ((PORTD >> 5) & 0x1)
#define LED_BTN_2_OutputEnable()      (TRISDCLR = (1<<5))
#define LED_BTN_2_InputEnable()       (TRISDSET = (1<<5))
#define LED_BTN_2_PIN                  GPIO_PIN_RD5
/*** Macros for LED_BTN_3 pin ***/
#define LED_BTN_3_Set()               (LATDSET = (1<<6))
#define LED_BTN_3_Clear()             (LATDCLR = (1<<6))
#define LED_BTN_3_Toggle()            (LATDINV= (1<<6))
#define LED_BTN_3_Get()               ((PORTD >> 6) & 0x1)
#define LED_BTN_3_OutputEnable()      (TRISDCLR = (1<<6))
#define LED_BTN_3_InputEnable()       (TRISDSET = (1<<6))
#define LED_BTN_3_PIN                  GPIO_PIN_RD6
/*** Macros for BTN_1 pin ***/
#define BTN_1_Set()               (LATDSET = (1<<7))
#define BTN_1_Clear()             (LATDCLR = (1<<7))
#define BTN_1_Toggle()            (LATDINV= (1<<7))
#define BTN_1_Get()               ((PORTD >> 7) & 0x1)
#define BTN_1_OutputEnable()      (TRISDCLR = (1<<7))
#define BTN_1_InputEnable()       (TRISDSET = (1<<7))
#define BTN_1_PIN                  GPIO_PIN_RD7
/*** Macros for HEATER pin ***/
#define HEATER_Set()               (LATFSET = (1<<0))
#define HEATER_Clear()             (LATFCLR = (1<<0))
#define HEATER_Toggle()            (LATFINV= (1<<0))
#define HEATER_Get()               ((PORTF >> 0) & 0x1)
#define HEATER_OutputEnable()      (TRISFCLR = (1<<0))
#define HEATER_InputEnable()       (TRISFSET = (1<<0))
#define HEATER_PIN                  GPIO_PIN_RF0
/*** Macros for COLD pin ***/
#define COLD_Set()               (LATFSET = (1<<1))
#define COLD_Clear()             (LATFCLR = (1<<1))
#define COLD_Toggle()            (LATFINV= (1<<1))
#define COLD_Get()               ((PORTF >> 1) & 0x1)
#define COLD_OutputEnable()      (TRISFCLR = (1<<1))
#define COLD_InputEnable()       (TRISFSET = (1<<1))
#define COLD_PIN                  GPIO_PIN_RF1
/*** Macros for LCD_D6 pin ***/
#define LCD_D6_Set()               (LATASET = (1<<6))
#define LCD_D6_Clear()             (LATACLR = (1<<6))
#define LCD_D6_Toggle()            (LATAINV= (1<<6))
#define LCD_D6_Get()               ((PORTA >> 6) & 0x1)
#define LCD_D6_OutputEnable()      (TRISACLR = (1<<6))
#define LCD_D6_InputEnable()       (TRISASET = (1<<6))
#define LCD_D6_PIN                  GPIO_PIN_RA6
/*** Macros for LCD_D7 pin ***/
#define LCD_D7_Set()               (LATASET = (1<<7))
#define LCD_D7_Clear()             (LATACLR = (1<<7))
#define LCD_D7_Toggle()            (LATAINV= (1<<7))
#define LCD_D7_Get()               ((PORTA >> 7) & 0x1)
#define LCD_D7_OutputEnable()      (TRISACLR = (1<<7))
#define LCD_D7_InputEnable()       (TRISASET = (1<<7))
#define LCD_D7_PIN                  GPIO_PIN_RA7
/*** Macros for MODE pin ***/
#define MODE_Set()               (LATESET = (1<<0))
#define MODE_Clear()             (LATECLR = (1<<0))
#define MODE_Toggle()            (LATEINV= (1<<0))
#define MODE_Get()               ((PORTE >> 0) & 0x1)
#define MODE_OutputEnable()      (TRISECLR = (1<<0))
#define MODE_InputEnable()       (TRISESET = (1<<0))
#define MODE_PIN                  GPIO_PIN_RE0
/*** Macros for CLR pin ***/
#define CLR_Set()               (LATESET = (1<<1))
#define CLR_Clear()             (LATECLR = (1<<1))
#define CLR_Toggle()            (LATEINV= (1<<1))
#define CLR_Get()               ((PORTE >> 1) & 0x1)
#define CLR_OutputEnable()      (TRISECLR = (1<<1))
#define CLR_InputEnable()       (TRISESET = (1<<1))
#define CLR_PIN                  GPIO_PIN_RE1
/*** Macros for AN pin ***/
#define AN_Set()               (LATGSET = (1<<14))
#define AN_Clear()             (LATGCLR = (1<<14))
#define AN_Toggle()            (LATGINV= (1<<14))
#define AN_Get()               ((PORTG >> 14) & 0x1)
#define AN_OutputEnable()      (TRISGCLR = (1<<14))
#define AN_InputEnable()       (TRISGSET = (1<<14))
#define AN_PIN                  GPIO_PIN_RG14
/*** Macros for GSM_RTS pin ***/
#define GSM_RTS_Set()               (LATGSET = (1<<12))
#define GSM_RTS_Clear()             (LATGCLR = (1<<12))
#define GSM_RTS_Toggle()            (LATGINV= (1<<12))
#define GSM_RTS_Get()               ((PORTG >> 12) & 0x1)
#define GSM_RTS_OutputEnable()      (TRISGCLR = (1<<12))
#define GSM_RTS_InputEnable()       (TRISGSET = (1<<12))
#define GSM_RTS_PIN                  GPIO_PIN_RG12
/*** Macros for RI pin ***/
#define RI_Set()               (LATGSET = (1<<13))
#define RI_Clear()             (LATGCLR = (1<<13))
#define RI_Toggle()            (LATGINV= (1<<13))
#define RI_Get()               ((PORTG >> 13) & 0x1)
#define RI_OutputEnable()      (TRISGCLR = (1<<13))
#define RI_InputEnable()       (TRISGSET = (1<<13))
#define RI_PIN                  GPIO_PIN_RG13
/*** Macros for MODEM pin ***/
#define MODEM_Set()               (LATESET = (1<<2))
#define MODEM_Clear()             (LATECLR = (1<<2))
#define MODEM_Toggle()            (LATEINV= (1<<2))
#define MODEM_Get()               ((PORTE >> 2) & 0x1)
#define MODEM_OutputEnable()      (TRISECLR = (1<<2))
#define MODEM_InputEnable()       (TRISESET = (1<<2))
#define MODEM_PIN                  GPIO_PIN_RE2
/*** Macros for SHIFT pin ***/
#define SHIFT_Set()               (LATESET = (1<<3))
#define SHIFT_Clear()             (LATECLR = (1<<3))
#define SHIFT_Toggle()            (LATEINV= (1<<3))
#define SHIFT_Get()               ((PORTE >> 3) & 0x1)
#define SHIFT_OutputEnable()      (TRISECLR = (1<<3))
#define SHIFT_InputEnable()       (TRISESET = (1<<3))
#define SHIFT_PIN                  GPIO_PIN_RE3
/*** Macros for BTN_MTR_1 pin ***/
#define BTN_MTR_1_Set()               (LATESET = (1<<4))
#define BTN_MTR_1_Clear()             (LATECLR = (1<<4))
#define BTN_MTR_1_Toggle()            (LATEINV= (1<<4))
#define BTN_MTR_1_Get()               ((PORTE >> 4) & 0x1)
#define BTN_MTR_1_OutputEnable()      (TRISECLR = (1<<4))
#define BTN_MTR_1_InputEnable()       (TRISESET = (1<<4))
#define BTN_MTR_1_PIN                  GPIO_PIN_RE4


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG2 = 98,
    GPIO_PIN_RG3 = 99,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;

typedef enum
{
  CN0_PIN = 1 << 0,
  CN1_PIN = 1 << 1,
  CN2_PIN = 1 << 2,
  CN3_PIN = 1 << 3,
  CN4_PIN = 1 << 4,
  CN5_PIN = 1 << 5,
  CN6_PIN = 1 << 6,
  CN7_PIN = 1 << 7,
  CN8_PIN = 1 << 8,
  CN9_PIN = 1 << 9,
  CN10_PIN = 1 << 10,
  CN11_PIN = 1 << 11,
  CN12_PIN = 1 << 12,
  CN13_PIN = 1 << 13,
  CN14_PIN = 1 << 14,
  CN15_PIN = 1 << 15,
  CN16_PIN = 1 << 16,
  CN17_PIN = 1 << 17,
  CN18_PIN = 1 << 18,
  CN19_PIN = 1 << 19,
  CN20_PIN = 1 << 20,
  CN21_PIN = 1 << 21,
}CN_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite(pin>>4, (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead(pin>>4) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable(pin>>4, 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H

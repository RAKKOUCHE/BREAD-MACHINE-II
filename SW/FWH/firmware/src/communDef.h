/* ************************************************************************* */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 01
 *
 * \file communDef.h
 *
 * \brief Fichier entête des definitions communes.
 
 */
/************************************************************************/

#ifndef COMMUNDEF_H
#define	COMMUNDEF_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "FreeRTOSConfig.h"

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data types and constants
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \defgroup Commmundef COMMUNDEF
     * Macros utilisées dans le programme.
     * @{
     */

    /** 
     * \brief Macros for BTN_MTR_2 pin
     */
#define BTN_MTR_2_Set()               (LATESET = (1<<5))
#define BTN_MTR_2_Clear()             (LATECLR = (1<<5))
#define BTN_MTR_2_Toggle()            (LATEINV= (1<<5))
#define BTN_MTR_2_Get()               ((PORTE >> 5) & 0x1)
#define BTN_MTR_2_OutputEnable()      (TRISECLR = (1<<5))
#define BTN_MTR_2_InputEnable()       (TRISESET = (1<<5))
#define BTN_MTR_2_PIN                  GPIO_PIN_RE5
    /** 
     * \brief Macros for BTN_MTR_3 pin
     */
#define BTN_MTR_3_Set()               (LATESET = (1<<6))
#define BTN_MTR_3_Clear()             (LATECLR = (1<<6))
#define BTN_MTR_3_Toggle()            (LATEINV= (1<<6))
#define BTN_MTR_3_Get()               ((PORTE >> 6) & 0x1)
#define BTN_MTR_3_OutputEnable()      (TRISECLR = (1<<6))
#define BTN_MTR_3_InputEnable()       (TRISESET = (1<<6))
#define BTN_MTR_3_PIN                  GPIO_PIN_RE6
    /** 
     * \brief Macros for CMD_TRAP_N21 pin
     */
#define CMD_TRAP_N21_Set()               (LATESET = (1<<7))
#define CMD_TRAP_N21_Clear()             (LATECLR = (1<<7))
#define CMD_TRAP_N21_Toggle()            (LATEINV= (1<<7))
#define CMD_TRAP_N21_Get()               ((PORTE >> 7) & 0x1)
#define CMD_TRAP_N21_OutputEnable()      (TRISECLR = (1<<7))
#define CMD_TRAP_N21_InputEnable()       (TRISESET = (1<<7))
#define CMD_TRAP_N21_PIN                  GPIO_PIN_RE7
    /** 
     * \brief Macros for LED_MDB pin
     */
#define LED_MDB_Set()               (LATCSET = (1<<1))
#define LED_MDB_Clear()             (LATCCLR = (1<<1))
#define LED_MDB_Toggle()            (LATCINV= (1<<1))
#define LED_MDB_Get()               ((PORTC >> 1) & 0x1)
#define LED_MDB_OutputEnable()      (TRISCCLR = (1<<1))
#define LED_MDB_InputEnable()       (TRISCSET = (1<<1))
#define LED_MDB_PIN                  GPIO_PIN_RC1
    /**
     * \brief Macros for DOOR pin 
     */
#define DOOR_Set()               (LATCSET = (1<<2))
#define DOOR_Clear()             (LATCCLR = (1<<2))
#define DOOR_Toggle()            (LATCINV= (1<<2))
#define DOOR_Get()               ((PORTC >> 2) & 0x1)
#define DOOR_OutputEnable()      (TRISCCLR = (1<<2))
#define DOOR_InputEnable()       (TRISCSET = (1<<2))
#define DOOR_PIN                  GPIO_PIN_RC2
    /** 
     * \brief Macros for TOP_1 pin 
     */
#define TOP_1_Set()               (LATCSET = (1<<3))
#define TOP_1_Clear()             (LATCCLR = (1<<3))
#define TOP_1_Toggle()            (LATCINV= (1<<3))
#define TOP_1_Get()               ((PORTC >> 3) & 0x1)
#define TOP_1_OutputEnable()      (TRISCCLR = (1<<3))
#define TOP_1_InputEnable()       (TRISCSET = (1<<3))
#define TOP_1_PIN                  GPIO_PIN_RC3
    /** 
     * \brief Macros for TOP_2 pin
     */
#define TOP_2_Set()               (LATCSET = (1<<4))
#define TOP_2_Clear()             (LATCCLR = (1<<4))
#define TOP_2_Toggle()            (LATCINV= (1<<4))
#define TOP_2_Get()               ((PORTC >> 4) & 0x1)
#define TOP_2_OutputEnable()      (TRISCCLR = (1<<4))
#define TOP_2_InputEnable()       (TRISCSET = (1<<4))
#define TOP_2_PIN                  GPIO_PIN_RC4
    /** 
     * \brief Macros for DQ pin
     */
#define DQ_Set()               (LATGSET = (1<<6))
#define DQ_Clear()             (LATGCLR = (1<<6))
#define DQ_Toggle()            (LATGINV= (1<<6))
#define DQ_Get()               ((PORTG >> 6) & 0x1)
#define DQ_OutputEnable()      (TRISGCLR = (1<<6))
#define DQ_InputEnable()       (TRISGSET = (1<<6))
    //#define DQ_PIN                  GPIO_PIN_RG6
    /** 
     * \brief Macros for LED_SYS pin
     */
#define LED_SYS_Set()               (LATASET = (1<<0))
#define LED_SYS_Clear()             (LATACLR = (1<<0))
#define LED_SYS_Toggle()            (LATAINV= (1<<0))
#define LED_SYS_Get()               ((PORTA >> 0) & 0x1)
#define LED_SYS_OutputEnable()      (TRISACLR = (1<<0))
#define LED_SYS_InputEnable()       (TRISASET = (1<<0))
#define LED_SYS_PIN                  GPIO_PIN_RA0
    /** 
     * \brief Macros for CMD_TRAP_N32 pin
     */
#define CMD_TRAP_N32_Set()               (LATESET = (1<<8))
#define CMD_TRAP_N32_Clear()             (LATECLR = (1<<8))
#define CMD_TRAP_N32_Toggle()            (LATEINV= (1<<8))
#define CMD_TRAP_N32_Get()               ((PORTE >> 8) & 0x1)
#define CMD_TRAP_N32_OutputEnable()      (TRISECLR = (1<<8))
#define CMD_TRAP_N32_InputEnable()       (TRISESET = (1<<8))
#define CMD_TRAP_N32_PIN                  GPIO_PIN_RE8
    /** 
     * \brief Macros for CMD_TRAP_N31 pin
     */
#define CMD_TRAP_N31_Set()               (LATESET = (1<<9))
#define CMD_TRAP_N31_Clear()             (LATECLR = (1<<9))
#define CMD_TRAP_N31_Toggle()            (LATEINV= (1<<9))
#define CMD_TRAP_N31_Get()               ((PORTE >> 9) & 0x1)
#define CMD_TRAP_N31_OutputEnable()      (TRISECLR = (1<<9))
#define CMD_TRAP_N31_InputEnable()       (TRISESET = (1<<9))
#define CMD_TRAP_N31_PIN                  GPIO_PIN_RE9
    /** 
     * \brief Macros for CMD_TRAP_P22 pin
     */
#define CMD_TRAP_P22_Set()               (LATBSET = (1<<5))
#define CMD_TRAP_P22_Clear()             (LATBCLR = (1<<5))
#define CMD_TRAP_P22_Toggle()            (LATBINV= (1<<5))
#define CMD_TRAP_P22_Get()               ((PORTB >> 5) & 0x1)
#define CMD_TRAP_P22_OutputEnable()      (TRISBCLR = (1<<5))
#define CMD_TRAP_P22_InputEnable()       (TRISBSET = (1<<5))
#define CMD_TRAP_P22_PIN                  GPIO_PIN_RB5
    /** 
     * \brief Macros for CMD_TRAP_P11 pin
     */
#define CMD_TRAP_P11_Set()               (LATBSET = (1<<4))
#define CMD_TRAP_P11_Clear()             (LATBCLR = (1<<4))
#define CMD_TRAP_P11_Toggle()            (LATBINV= (1<<4))
#define CMD_TRAP_P11_Get()               ((PORTB >> 4) & 0x1)
#define CMD_TRAP_P11_OutputEnable()      (TRISBCLR = (1<<4))
#define CMD_TRAP_P11_InputEnable()       (TRISBSET = (1<<4))
#define CMD_TRAP_P11_PIN                  GPIO_PIN_RB4
    /** 
     * \brief Macros for CMD_TRAP_P12 pin
     */
#define CMD_TRAP_P12_Set()               (LATBSET = (1<<3))
#define CMD_TRAP_P12_Clear()             (LATBCLR = (1<<3))
#define CMD_TRAP_P12_Toggle()            (LATBINV= (1<<3))
#define CMD_TRAP_P12_Get()               ((PORTB >> 3) & 0x1)
#define CMD_TRAP_P12_OutputEnable()      (TRISBCLR = (1<<3))
#define CMD_TRAP_P12_InputEnable()       (TRISBSET = (1<<3))
#define CMD_TRAP_P12_PIN                  GPIO_PIN_RB3
    /** 
     * \brief Macros for CMD_TRAP_N22 pin
     */
#define CMD_TRAP_N22_Set()               (LATBSET = (1<<2))
#define CMD_TRAP_N22_Clear()             (LATBCLR = (1<<2))
#define CMD_TRAP_N22_Toggle()            (LATBINV= (1<<2))
#define CMD_TRAP_N22_Get()               ((PORTB >> 2) & 0x1)
#define CMD_TRAP_N22_OutputEnable()      (TRISBCLR = (1<<2))
#define CMD_TRAP_N22_InputEnable()       (TRISBSET = (1<<2))
#define CMD_TRAP_N22_PIN                  GPIO_PIN_RB2
    /** 
     * \brief Macros for CMD_TRAP_P21 pin
     */
#define CMD_TRAP_P21_Set()               (LATBSET = (1<<6))
#define CMD_TRAP_P21_Clear()             (LATBCLR = (1<<6))
#define CMD_TRAP_P21_Toggle()            (LATBINV= (1<<6))
#define CMD_TRAP_P21_Get()               ((PORTB >> 6) & 0x1)
#define CMD_TRAP_P21_OutputEnable()      (TRISBCLR = (1<<6))
#define CMD_TRAP_P21_InputEnable()       (TRISBSET = (1<<6))
#define CMD_TRAP_P21_PIN                  GPIO_PIN_RB6
    /** 
     * \brief Macros for CMD_TRAP_P32 pin
     */
#define CMD_TRAP_P32_Set()               (LATBSET = (1<<7))
#define CMD_TRAP_P32_Clear()             (LATBCLR = (1<<7))
#define CMD_TRAP_P32_Toggle()            (LATBINV= (1<<7))
#define CMD_TRAP_P32_Get()               ((PORTB >> 7) & 0x1)
#define CMD_TRAP_P32_OutputEnable()      (TRISBCLR = (1<<7))
#define CMD_TRAP_P32_InputEnable()       (TRISBSET = (1<<7))
#define CMD_TRAP_P32_PIN                  GPIO_PIN_RB7
    /** 
     * \brief Macros for RTNMTR pin
     */
#define RTNMTR_Set()               (LATASET = (1<<9))
#define RTNMTR_Clear()             (LATACLR = (1<<9))
#define RTNMTR_Toggle()            (LATAINV= (1<<9))
#define RTNMTR_Get()               ((PORTA >> 9) & 0x1)
#define RTNMTR_OutputEnable()      (TRISACLR = (1<<9))
#define RTNMTR_InputEnable()       (TRISASET = (1<<9))
#define RTNMTR_PIN                  GPIO_PIN_RA9
    /** 
     * \brief Macros for BTNRTN pin
     */
#define BTNRTN_Set()               (LATASET = (1<<10))
#define BTNRTN_Clear()             (LATACLR = (1<<10))
#define BTNRTN_Toggle()            (LATAINV= (1<<10))
#define BTNRTN_Get()               ((PORTA >> 10) & 0x1)
#define BTNRTN_OutputEnable()      (TRISACLR = (1<<10))
#define BTNRTN_InputEnable()       (TRISASET = (1<<10))
#define BTNRTN_PIN                  GPIO_PIN_RA10
    /** 
     * \brief Macros for CMD_TRAP_P31 pin
     */
#define CMD_TRAP_P31_Set()               (LATBSET = (1<<8))
#define CMD_TRAP_P31_Clear()             (LATBCLR = (1<<8))
#define CMD_TRAP_P31_Toggle()            (LATBINV= (1<<8))
#define CMD_TRAP_P31_Get()               ((PORTB >> 8) & 0x1)
#define CMD_TRAP_P31_OutputEnable()      (TRISBCLR = (1<<8))
#define CMD_TRAP_P31_InputEnable()       (TRISBSET = (1<<8))
#define CMD_TRAP_P31_PIN                  GPIO_PIN_RB8
    /** 
     * \brief Macros for BRK pin
     */
#define BRK_Set()               (LATBSET = (1<<9))
#define BRK_Clear()             (LATBCLR = (1<<9))
#define BRK_Toggle()            (LATBINV= (1<<9))
#define BRK_Get()               ((PORTB >> 9) & 0x1)
#define BRK_OutputEnable()      (TRISBCLR = (1<<9))
#define BRK_InputEnable()       (TRISBSET = (1<<9))
#define BRK_PIN                  GPIO_PIN_RB9
    /** 
     * \brief Macros for CMD_CARROUSEL_1 pin
     */
#define CMD_CARROUSEL_1_Set()               (LATBSET = (1<<10))
#define CMD_CARROUSEL_1_Clear()             (LATBCLR = (1<<10))
#define CMD_CARROUSEL_1_Toggle()            (LATBINV= (1<<10))
#define CMD_CARROUSEL_1_Get()               ((PORTB >> 10) & 0x1)
#define CMD_CARROUSEL_1_OutputEnable()      (TRISBCLR = (1<<10))
#define CMD_CARROUSEL_1_InputEnable()       (TRISBSET = (1<<10))
#define CMD_CARROUSEL_1_PIN                  GPIO_PIN_RB10
    /** 
     * \brief Macros for CMD_CARROUSEL_2 pin
     */
#define CMD_CARROUSEL_2_Set()               (LATBSET = (1<<11))
#define CMD_CARROUSEL_2_Clear()             (LATBCLR = (1<<11))
#define CMD_CARROUSEL_2_Toggle()            (LATBINV= (1<<11))
#define CMD_CARROUSEL_2_Get()               ((PORTB >> 11) & 0x1)
#define CMD_CARROUSEL_2_OutputEnable()      (TRISBCLR = (1<<11))
#define CMD_CARROUSEL_2_InputEnable()       (TRISBSET = (1<<11))
#define CMD_CARROUSEL_2_PIN                  GPIO_PIN_RB11
    /** 
     * \brief Macros for LCD_RS pin
     */
#define LCD_RS_Set()               (LATASET = (1<<1))
#define LCD_RS_Clear()             (LATACLR = (1<<1))
#define LCD_RS_Toggle()            (LATAINV= (1<<1))
#define LCD_RS_Get()               ((PORTA >> 1) & 0x1)
#define LCD_RS_OutputEnable()      (TRISACLR = (1<<1))
#define LCD_RS_InputEnable()       (TRISASET = (1<<1))
#define LCD_RS_PIN                  GPIO_PIN_RA1
    /** 
     * \brief Macros for CS pin
     */
#define CS_Set()               (LATFSET = (1<<13))
#define CS_Clear()             (LATFCLR = (1<<13))
#define CS_Toggle()            (LATFINV= (1<<13))
#define CS_Get()               ((PORTF >> 13) & 0x1)
#define CS_OutputEnable()      (TRISFCLR = (1<<13))
#define CS_InputEnable()       (TRISFSET = (1<<13))

    /** 
     * \brief Macros for GSM_CTS pin
     */
#define GSM_CTS_Set()               (LATFSET = (1<<12))
#define GSM_CTS_Clear()             (LATFCLR = (1<<12))
#define GSM_CTS_Toggle()            (LATFINV= (1<<12))
#define GSM_CTS_Get()               ((PORTF >> 12) & 0x1)
#define GSM_CTS_OutputEnable()      (TRISFCLR = (1<<12))
#define GSM_CTS_InputEnable()       (TRISFSET = (1<<12))

    /** 
     * \brief Macros for CMD_CARROUSEL_3 pin
     */
#define CMD_CARROUSEL_3_Set()               (LATBSET = (1<<12))
#define CMD_CARROUSEL_3_Clear()             (LATBCLR = (1<<12))
#define CMD_CARROUSEL_3_Toggle()            (LATBINV= (1<<12))
#define CMD_CARROUSEL_3_Get()               ((PORTB >> 12) & 0x1)
#define CMD_CARROUSEL_3_OutputEnable()      (TRISBCLR = (1<<12))
#define CMD_CARROUSEL_3_InputEnable()       (TRISBSET = (1<<12))
#define CMD_CARROUSEL_3_PIN                  GPIO_PIN_RB12
    /** 
     * \brief Macros for LCD_RW pin
     */
#define LCD_RW_Set()               (LATASET = (1<<2))
#define LCD_RW_Clear()             (LATACLR = (1<<2))
#define LCD_RW_Toggle()            (LATAINV= (1<<2))
#define LCD_RW_Get()               ((PORTA >> 2) & 0x1)
#define LCD_RW_OutputEnable()      (TRISACLR = (1<<2))
#define LCD_RW_InputEnable()       (TRISASET = (1<<2))
#define LCD_RW_PIN                  GPIO_PIN_RA2
    /** 
     * \brief Macros for LCD_EN pin
     */
#define LCD_EN_Set()               (LATASET = (1<<3))
#define LCD_EN_Clear()             (LATACLR = (1<<3))
#define LCD_EN_Toggle()            (LATAINV= (1<<3))
#define LCD_EN_Get()               ((PORTA >> 3) & 0x1)
#define LCD_EN_OutputEnable()      (TRISACLR = (1<<3))
#define LCD_EN_InputEnable()       (TRISASET = (1<<3))
#define LCD_EN_PIN                  GPIO_PIN_RA3
    /** 
     * \brief Macros for LCD_D4 pin
     */
#define LCD_D4_Set()               (LATASET = (1<<4))
#define LCD_D4_Clear()             (LATACLR = (1<<4))
#define LCD_D4_Toggle()            (LATAINV= (1<<4))
#define LCD_D4_Get()               ((PORTA >> 4) & 0x1)
#define LCD_D4_OutputEnable()      (TRISACLR = (1<<4))
#define LCD_D4_InputEnable()       (TRISASET = (1<<4))

    /** 
     * \brief Macros for LCD_D5 pin
     */
#define LCD_D5_Set()               (LATASET = (1<<5))
#define LCD_D5_Clear()             (LATACLR = (1<<5))
#define LCD_D5_Toggle()            (LATAINV= (1<<5))
#define LCD_D5_Get()               ((PORTA >> 5) & 0x1)
#define LCD_D5_OutputEnable()      (TRISACLR = (1<<5))
#define LCD_D5_InputEnable()       (TRISASET = (1<<5))

    /** 
     * \brief Macros for TOP_3 pin
     */
#define TOP_3_Set()               (LATCSET = (1<<12))
#define TOP_3_Clear()             (LATCCLR = (1<<12))
#define TOP_3_Toggle()            (LATCINV= (1<<12))
#define TOP_3_Get()               ((PORTC >> 12) & 0x1)
#define TOP_3_OutputEnable()      (TRISCCLR = (1<<12))
#define TOP_3_InputEnable()       (TRISCSET = (1<<12))
#define TOP_3_PIN                  GPIO_PIN_RC12
    /** 
     * \brief Macros for BOT_3 pin
     */
#define BOT_3_Set()               (LATCSET = (1<<15))
#define BOT_3_Clear()             (LATCCLR = (1<<15))
#define BOT_3_Toggle()            (LATCINV= (1<<15))
#define BOT_3_Get()               ((PORTC >> 15) & 0x1)
#define BOT_3_OutputEnable()      (TRISCCLR = (1<<15))
#define BOT_3_InputEnable()       (TRISCSET = (1<<15))
#define BOT_3_PIN                  GPIO_PIN_RC15
    /** 
     * \brief Macros for CMD_TRAP_N12 pin
     */
#define CMD_TRAP_N12_Set()               (LATASET = (1<<14))
#define CMD_TRAP_N12_Clear()             (LATACLR = (1<<14))
#define CMD_TRAP_N12_Toggle()            (LATAINV= (1<<14))
#define CMD_TRAP_N12_Get()               ((PORTA >> 14) & 0x1)
#define CMD_TRAP_N12_OutputEnable()      (TRISACLR = (1<<14))
#define CMD_TRAP_N12_InputEnable()       (TRISASET = (1<<14))
#define CMD_TRAP_N12_PIN                  GPIO_PIN_RA14
    /** 
     * \brief Macros for CMD_TRAP_N11 pin
     */
#define CMD_TRAP_N11_Set()               (LATASET = (1<<15))
#define CMD_TRAP_N11_Clear()             (LATACLR = (1<<15))
#define CMD_TRAP_N11_Toggle()            (LATAINV= (1<<15))
#define CMD_TRAP_N11_Get()               ((PORTA >> 15) & 0x1)
#define CMD_TRAP_N11_OutputEnable()      (TRISACLR = (1<<15))
#define CMD_TRAP_N11_InputEnable()       (TRISASET = (1<<15))
#define CMD_TRAP_N11_PIN                  GPIO_PIN_RA15
    /** 
     * \brief Macros for BTN_2 pin
     */
#define BTN_2_Set()               (LATDSET = (1<<8))
#define BTN_2_Clear()             (LATDCLR = (1<<8))
#define BTN_2_Toggle()            (LATDINV= (1<<8))
#define BTN_2_Get()               ((PORTD >> 8) & 0x1)
#define BTN_2_OutputEnable()      (TRISDCLR = (1<<8))
#define BTN_2_InputEnable()       (TRISDSET = (1<<8))
#define BTN_2_PIN                  GPIO_PIN_RD8
    /** 
     * \brief Macros for BTN_3 pin
     */
#define BTN_3_Set()               (LATDSET = (1<<9))
#define BTN_3_Clear()             (LATDCLR = (1<<9))
#define BTN_3_Toggle()            (LATDINV= (1<<9))
#define BTN_3_Get()               ((PORTD >> 9) & 0x1)
#define BTN_3_OutputEnable()      (TRISDCLR = (1<<9))
#define BTN_3_InputEnable()       (TRISDSET = (1<<9))
#define BTN_3_PIN                  GPIO_PIN_RD9
    /** 
     * \brief Macros for TAKE_1_1 pin
     */
#define TAKE_1_1_Set()               (LATDSET = (1<<10))
#define TAKE_1_1_Clear()             (LATDCLR = (1<<10))
#define TAKE_1_1_Toggle()            (LATDINV= (1<<10))
#define TAKE_1_1_Get()               ((PORTD >> 10) & 0x1)
#define TAKE_1_1_OutputEnable()      (TRISDCLR = (1<<10))
#define TAKE_1_1_InputEnable()       (TRISDSET = (1<<10))
#define TAKE_1_1_PIN                  GPIO_PIN_RD10
    /** 
     * \brief Macros for TAKE_1_2 pin
     */
#define TAKE_1_2_Set()               (LATDSET = (1<<11))
#define TAKE_1_2_Clear()             (LATDCLR = (1<<11))
#define TAKE_1_2_Toggle()            (LATDINV= (1<<11))
#define TAKE_1_2_Get()               ((PORTD >> 11) & 0x1)
#define TAKE_1_2_OutputEnable()      (TRISDCLR = (1<<11))
#define TAKE_1_2_InputEnable()       (TRISDSET = (1<<11))
#define TAKE_1_2_PIN                  GPIO_PIN_RD11
    /** 
     * \brief Macros for BUZZER pin
     */
#define BUZZER_Set()               (LATDSET = (1<<0))
#define BUZZER_Clear()             (LATDCLR = (1<<0))
#define BUZZER_Toggle()            (LATDINV= (1<<0))
#define BUZZER_Get()               ((PORTD >> 0) & 0x1)
#define BUZZER_OutputEnable()      (TRISDCLR = (1<<0))
#define BUZZER_InputEnable()       (TRISDSET = (1<<0))
#define BUZZER_PIN                  GPIO_PIN_RD0
    /** 
     * \brief Macros for BOT_1 pin
     */
#define BOT_1_Set()               (LATCSET = (1<<13))
#define BOT_1_Clear()             (LATCCLR = (1<<13))
#define BOT_1_Toggle()            (LATCINV= (1<<13))
#define BOT_1_Get()               ((PORTC >> 13) & 0x1)
#define BOT_1_OutputEnable()      (TRISCCLR = (1<<13))
#define BOT_1_InputEnable()       (TRISCSET = (1<<13))
#define BOT_1_PIN                  GPIO_PIN_RC13
    /** 
     * \brief Macros for BOT_2 pin
     */
#define BOT_2_Set()               (LATCSET = (1<<14))
#define BOT_2_Clear()             (LATCCLR = (1<<14))
#define BOT_2_Toggle()            (LATCINV= (1<<14))
#define BOT_2_Get()               ((PORTC >> 14) & 0x1)
#define BOT_2_OutputEnable()      (TRISCCLR = (1<<14))
#define BOT_2_InputEnable()       (TRISCSET = (1<<14))
#define BOT_2_PIN                  GPIO_PIN_RC14
    /** 
     * \brief Macros for PWR pin
     */
#define PWR_Set()               (LATDSET = (1<<1))
#define PWR_Clear()             (LATDCLR = (1<<1))
#define PWR_Toggle()            (LATDINV= (1<<1))
#define PWR_Get()               ((PORTD >> 1) & 0x1)
#define PWR_OutputEnable()      (TRISDCLR = (1<<1))
#define PWR_InputEnable()       (TRISDSET = (1<<1))
#define PWR_PIN                  GPIO_PIN_RD1
    /** 
     * \brief Macros for TAKE_3_1 pin
     */
#define TAKE_3_1_Set()               (LATDSET = (1<<2))
#define TAKE_3_1_Clear()             (LATDCLR = (1<<2))
#define TAKE_3_1_Toggle()            (LATDINV= (1<<2))
#define TAKE_3_1_Get()               ((PORTD >> 2) & 0x1)
#define TAKE_3_1_OutputEnable()      (TRISDCLR = (1<<2))
#define TAKE_3_1_InputEnable()       (TRISDSET = (1<<2))
#define TAKE_3_1_PIN                  GPIO_PIN_RD2
    /** 
     * \brief Macros for TAKE_3_2 pin
     */
#define TAKE_3_2_Set()               (LATDSET = (1<<3))
#define TAKE_3_2_Clear()             (LATDCLR = (1<<3))
#define TAKE_3_2_Toggle()            (LATDINV= (1<<3))
#define TAKE_3_2_Get()               ((PORTD >> 3) & 0x1)
#define TAKE_3_2_OutputEnable()      (TRISDCLR = (1<<3))
#define TAKE_3_2_InputEnable()       (TRISDSET = (1<<3))
#define TAKE_3_2_PIN                  GPIO_PIN_RD3
    /** 
     * \brief Macros for TAKE_2_1 pin
     */
#define TAKE_2_1_Set()               (LATDSET = (1<<12))
#define TAKE_2_1_Clear()             (LATDCLR = (1<<12))
#define TAKE_2_1_Toggle()            (LATDINV= (1<<12))
#define TAKE_2_1_Get()               ((PORTD >> 12) & 0x1)
#define TAKE_2_1_OutputEnable()      (TRISDCLR = (1<<12))
#define TAKE_2_1_InputEnable()       (TRISDSET = (1<<12))
#define TAKE_2_1_PIN                  GPIO_PIN_RD12
    /** 
     * \brief Macros for TAKE_2_2 pin
     */
#define TAKE_2_2_Set()               (LATDSET = (1<<13))
#define TAKE_2_2_Clear()             (LATDCLR = (1<<13))
#define TAKE_2_2_Toggle()            (LATDINV= (1<<13))
#define TAKE_2_2_Get()               ((PORTD >> 13) & 0x1)
#define TAKE_2_2_OutputEnable()      (TRISDCLR = (1<<13))
#define TAKE_2_2_InputEnable()       (TRISDSET = (1<<13))
#define TAKE_2_2_PIN                  GPIO_PIN_RD13
    /** 
     * \brief Macros for LED_BTN_1 pin
     */
#define LED_BTN_1_Set()               (LATDSET = (1<<4))
#define LED_BTN_1_Clear()             (LATDCLR = (1<<4))
#define LED_BTN_1_Toggle()            (LATDINV= (1<<4))
#define LED_BTN_1_Get()               ((PORTD >> 4) & 0x1)
#define LED_BTN_1_OutputEnable()      (TRISDCLR = (1<<4))
#define LED_BTN_1_InputEnable()       (TRISDSET = (1<<4))
#define LED_BTN_1_PIN                  GPIO_PIN_RD4
    /**  
     * \brief Macros for LED_BTN_2 pin
     */
#define LED_BTN_2_Set()               (LATDSET = (1<<5))
#define LED_BTN_2_Clear()             (LATDCLR = (1<<5))
#define LED_BTN_2_Toggle()            (LATDINV= (1<<5))
#define LED_BTN_2_Get()               ((PORTD >> 5) & 0x1)
#define LED_BTN_2_OutputEnable()      (TRISDCLR = (1<<5))
#define LED_BTN_2_InputEnable()       (TRISDSET = (1<<5))
#define LED_BTN_2_PIN                  GPIO_PIN_RD5
    /** 
     * \brief Macros for LED_BTN_3 pin
     */
#define LED_BTN_3_Set()               (LATDSET = (1<<6))
#define LED_BTN_3_Clear()             (LATDCLR = (1<<6))
#define LED_BTN_3_Toggle()            (LATDINV= (1<<6))
#define LED_BTN_3_Get()               ((PORTD >> 6) & 0x1)
#define LED_BTN_3_OutputEnable()      (TRISDCLR = (1<<6))
#define LED_BTN_3_InputEnable()       (TRISDSET = (1<<6))
#define LED_BTN_3_PIN                  GPIO_PIN_RD6
    /** 
     * \brief Macros for BTN_1 pin
     */
#define BTN_1_Set()               (LATDSET = (1<<7))
#define BTN_1_Clear()             (LATDCLR = (1<<7))
#define BTN_1_Toggle()            (LATDINV= (1<<7))
#define BTN_1_Get()               ((PORTD >> 7) & 0x1)
#define BTN_1_OutputEnable()      (TRISDCLR = (1<<7))
#define BTN_1_InputEnable()       (TRISDSET = (1<<7))
#define BTN_1_PIN                  GPIO_PIN_RD7
    /** 
     * \brief Macros for HEATER pin
     */
#define HEATER_Set()               (LATFSET = (1<<0))
#define HEATER_Clear()             (LATFCLR = (1<<0))
#define HEATER_Toggle()            (LATFINV= (1<<0))
#define HEATER_Get()               ((PORTF >> 0) & 0x1)
#define HEATER_OutputEnable()      (TRISFCLR = (1<<0))
#define HEATER_InputEnable()       (TRISFSET = (1<<0))
#define HEATER_PIN                  GPIO_PIN_RF0
    /** 
     * \brief Macros for COLD pin
     */
#define COLD_Set()               (LATFSET = (1<<1))
#define COLD_Clear()             (LATFCLR = (1<<1))
#define COLD_Toggle()            (LATFINV= (1<<1))
#define COLD_Get()               ((PORTF >> 1) & 0x1)
#define COLD_OutputEnable()      (TRISFCLR = (1<<1))
#define COLD_InputEnable()       (TRISFSET = (1<<1))
#define COLD_PIN                  GPIO_PIN_RF1
    /** 
     * \brief Macros for LCD_D6 pin
     */
#define LCD_D6_Set()               (LATASET = (1<<6))
#define LCD_D6_Clear()             (LATACLR = (1<<6))
#define LCD_D6_Toggle()            (LATAINV= (1<<6))
#define LCD_D6_Get()               ((PORTA >> 6) & 0x1)
#define LCD_D6_OutputEnable()      (TRISACLR = (1<<6))
#define LCD_D6_InputEnable()       (TRISASET = (1<<6))
    /** 
     * \brief Macros for LCD_D7 pin
     */
#define LCD_D7_Set()               (LATASET = (1<<7))
#define LCD_D7_Clear()             (LATACLR = (1<<7))
#define LCD_D7_Toggle()            (LATAINV= (1<<7))
#define LCD_D7_Get()               ((PORTA >> 7) & 0x1)
#define LCD_D7_OutputEnable()      (TRISACLR = (1<<7))
#define LCD_D7_InputEnable()       (TRISASET = (1<<7))
    /** 
     * \brief Macros for MODE pin
     */
#define MODE_Set()               (LATESET = (1<<0))
#define MODE_Clear()             (LATECLR = (1<<0))
#define MODE_Toggle()            (LATEINV= (1<<0))
#define MODE_Get()               ((PORTE >> 0) & 0x1)
#define MODE_OutputEnable()      (TRISECLR = (1<<0))
#define MODE_InputEnable()       (TRISESET = (1<<0))
#define MODE_PIN                  GPIO_PIN_RE0
    /** 
     * \brief Macros for CLR pin
     */
#define CLR_Set()               (LATESET = (1<<1))
#define CLR_Clear()             (LATECLR = (1<<1))
#define CLR_Toggle()            (LATEINV= (1<<1))
#define CLR_Get()               ((PORTE >> 1) & 0x1)
#define CLR_OutputEnable()      (TRISECLR = (1<<1))
#define CLR_InputEnable()       (TRISESET = (1<<1))
#define CLR_PIN                  GPIO_PIN_RE1
    /** 
     * \brief Macros for AN pin
     */
#define AN_Set()               (LATGSET = (1<<14))
#define AN_Clear()             (LATGCLR = (1<<14))
#define AN_Toggle()            (LATGINV= (1<<14))
#define AN_Get()               ((PORTG >> 14) & 0x1)
#define AN_OutputEnable()      (TRISGCLR = (1<<14))
#define AN_InputEnable()       (TRISGSET = (1<<14))
    /** 
     * \brief Macros for GSM_RTS pin
     */
#define GSM_RTS_Set()               (LATGSET = (1<<12))
#define GSM_RTS_Clear()             (LATGCLR = (1<<12))
#define GSM_RTS_Toggle()            (LATGINV= (1<<12))
#define GSM_RTS_Get()               ((PORTG >> 12) & 0x1)
#define GSM_RTS_OutputEnable()      (TRISGCLR = (1<<12))
#define GSM_RTS_InputEnable()       (TRISGSET = (1<<12))
    /** 
     * \brief Macros for RI pin
     */
#define RI_Set()               (LATGSET = (1<<13))
#define RI_Clear()             (LATGCLR = (1<<13))
#define RI_Toggle()            (LATGINV= (1<<13))
#define RI_Get()               ((PORTG >> 13) & 0x1)
#define RI_OutputEnable()      (TRISGCLR = (1<<13))
#define RI_InputEnable()       (TRISGSET = (1<<13))
    /** 
     * \brief Macros for MODEM pin
     */
#define MODEM_Set()               (LATESET = (1<<2))
#define MODEM_Clear()             (LATECLR = (1<<2))
#define MODEM_Toggle()            (LATEINV= (1<<2))
#define MODEM_Get()               ((PORTE >> 2) & 0x1)
#define MODEM_OutputEnable()      (TRISECLR = (1<<2))
#define MODEM_InputEnable()       (TRISESET = (1<<2))
#define MODEM_PIN                  GPIO_PIN_RE2
    /** 
     * \brief Macros for SHIFT pin
     */
#define SHIFT_Set()               (LATESET = (1<<3))
#define SHIFT_Clear()             (LATECLR = (1<<3))
#define SHIFT_Toggle()            (LATEINV= (1<<3))
#define SHIFT_Get()               ((PORTE >> 3) & 0x1)
#define SHIFT_OutputEnable()      (TRISECLR = (1<<3))
#define SHIFT_InputEnable()       (TRISESET = (1<<3))
#define SHIFT_PIN                  GPIO_PIN_RE3
    /** 
     * \brief Macros for BTN_MTR_1 pin
     */
#define BTN_MTR_1_Set()               (LATESET = (1<<4))
#define BTN_MTR_1_Clear()             (LATECLR = (1<<4))
#define BTN_MTR_1_Toggle()            (LATEINV= (1<<4))
#define BTN_MTR_1_Get()               ((PORTE >> 4) & 0x1)
#define BTN_MTR_1_OutputEnable()      (TRISECLR = (1<<4))
#define BTN_MTR_1_InputEnable()       (TRISESET = (1<<4))
#define BTN_MTR_1_PIN                  GPIO_PIN_RE4
    
    

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /**
     * \brief Nombre de produits.
     */
#define PRODUCT_NUMBER 3

    /**
     * \brief Fréquence d'horloge du CPU.
     */
#define GetSystemClock() configCPU_CLOCK_HZ

    /**
     * \brief Définition d'une seconde pour Freertos
     */
#define SECONDE 1000UL

    /**
     * \brief Définition d'une milliseconde pour Freertos.
     */
#define MILLISEC 1UL

    /**
     * \brief Provoque un délai de x milliseconde.
     */
#define delayMs(x) vTaskDelay(x)

    /**
     * \brief Période de clignotement de la led systéme.
     */
#define FLASH_PERIOD 250


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /**
     * @}
     */

#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNDEF_H */


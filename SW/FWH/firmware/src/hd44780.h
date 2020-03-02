/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 08
 *
 * \file hd44780.h
 *
 * \brief Fichier ent�te de la gestion de l'afficheur.
 *
 * \details Ce fichier fournit les prototypes et les d�finitions utilis�s par le
 * programme pour  g�rer l'afficheur.
 *
 ***************************************************************************/

#ifndef _HD44780_H   /* Guard against multiple inclusion */
#define _HD44780_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdio.h>
#include <stdbool.h>
#include <GenericTypeDefs.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "delay_us.h"
#include "mainboard.h"
#include "communDef.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * \defgroup afficheur AFFICHEUR
     * \brief Gestion de l'afficheur.
     * @{
     */


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************

    /**
     * \brief Enum�ration des commandes HD44780
     */
    enum
    {
        LCD_CLEAR = 0b00000001, /*!<Efface l'affcheur et positionne le compteur
                                 * d'adresse � 0 et efface l'afficheur.*/
        LCD_HOME = 0b00000010, /*!<Positionne le curseur au premier caract�re de
                                * la prmi�re ligne.*/
        LCD_ENTRY_SET = 0b00000100, /*!<D�fini l'incr�mentation du curseur, la
                                     * direction du glissement.*/
        LCD_DISPLAY_CONTROL = 0b00001000, /*!<Active ou desactive l'afficheur,
                                           * Active ou desactive le curseur,
                                           * Active ou desactive le clignotement
                                           * du curseur.*/
        LCD_SHIFT_DISPLAY_CURSOR = 0b00010000, /*!<D�place la position du
                                                * curseur ou de l'afficheur
                                                * sans modifier l'affichage.*/
        LCD_FUNCTION_SET = 0b00100000, /*!<D�finie le type d'interface(4 / 8 bits),
                                        * le nombre de lignes et la fonte des
                                        * caract�res.*/
        LCD_SET_CGRAM_ADRESS = 0b01000000, /*!<Fixe la valeur du compteur
                                            * d'adresse de la ram graphiue.*/
        LCD_SET_DDRAM_ADDRESS = 0b10000000, /*!<Fixe la valeur du compteur
                                             * d'adresse de la ram de donn�es.*/
    };

    /**
     * \brief Indique si l'afficheur est actif ou non.
     */
    typedef enum
    {
        LCD_Off = 0, /*!<Afficheur d�sactiv�.*/
        LCD_On = 1, /*!<Afficheur activ�.*/
    } LCD_ON_OFF;

    /**
     * \brief Indique si le curseur est affich� ou non.
     */
    typedef enum
    {
        Cursor_Off = 0, /*!<Curseur �teint.*/
        Cursor_On = 1, /*!<Curseur actif.*/
    } Cursor_ON_OFF;

    /**
     * \brief Indique si le curseur clignote.
     */
    typedef enum
    {
        Blink_Off = 0, /*!<Le curseur ne clignote pas.*/
        Blink_On = 1, /*!<Le curseur clignote.*/
    } Blink_ON_OFF;

    /**
     * \brief Indique si c'est le curseur qui se d�place ou si c'est
     * les caract�res.
     */
    typedef enum
    {
        C_move = 0, /*!<Le curseur se d�place.*/
        D_shift = 1, /*!<Les caract�res se dplacent.*/
    } CursorDisplayShift;

    /**
     * \brief Indique si l'affichage se d�place par rapport au curseur.
     * \details Vers la droite si l'adresse est incr�ment�, vers la gauche si
     * l'adresse est d�cr�ment�e.
     */
    typedef enum
    {
        noShifted = 0, /*!<Pas de d?placment de l'affichage.*/
        shifted = 1, /*!<D?placement de l'affichage.*/
    } eShift;

    /**
     * \brief Mode de modification de l'adresse du compteur
     */
    typedef enum
    {
        decrement = 0, /*!<D�crementation de l'adresse.*/
        increment = 1, /*!<Incr�mentation de l'adresse.*/
    } eID;

    /**
     * \brief Direction du d�placement
     */
    typedef enum
    {
        left = 0, /*!<D�placement vers la gauche.*/
        right = 1, /*!<D�placement vers la drote.*/
    } eDirection;

    /**
     * \brief Type d'interface(4 ou 8 bits)
     */
    typedef enum
    {
        bits4 = 0, /*!<Interface 4 bit de DB4 � DB7.*/
        bits8 = 1, /*!<Interface 8 bits de DB0 � DB7.*/
    } eInterface;

    /**
     * \brief Nombre de lignes de l'afficheur.
     */
    typedef enum
    {
        one = 0, /*!<1 ligne. */
        more = 1, /*!<2 lignes ou plus.*/
    } eLines;

    /**
     * \brief Fonte utilis�e.
     */
    typedef enum
    {
        lo, /*!<5x8, n�cessaire si plus d'une ligne.*/
        hi, /*!<5x10, seulement pour 1 ligne.*/
    } eFont;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Requ�te sur la disponibilit� de l'afficheur.
     * @return True si l'afficheur est op�rationnel.
     */
    bool isLCDInitialized(void);

    /**
     *
     * @param format
     * @param ...
     */
    void vDisplayLCD(char *format, ...);

    /**
     *
     * @return
     */
    bool getIsLCDIntialiazed(void);

    /**
     * \brief Efface l'afficheur.
     */
    void vLCD_CLEAR();

    /**
     * \brief Positionne le curseur sur le premier caract�re de la premi�re
     * ligne sans effacer l'afficheur.
     */
    void vLCD_HOME();

    /**
     * \brief Positionne le curseur de l'afficheur.
     * @param X Position du curseur.
     * @param Y Ligne sur laquelle se positionne le curseur.
     */
    void vLCDGotoXY(uint8_t X, uint8_t Y);

    /**
     * \brief Efface une ligne.
     * @param[in] byLine Num�ro de la ligne � effacer.
     */
    void vLCDClearLine(const uint8_t byLine);

    /**
     * \brief Contr�le l'afficheur
     * @param[in] d_on Afficheur allum� ou non.
     * @param[in] c_on Curseur affich� ou non.
     * @param[in] b_on Curseur clignotant ou non.
     */
    void vLCD_Display_control(const LCD_ON_OFF d_on, const Cursor_ON_OFF c_on, const Blink_ON_OFF b_on);


    /**
     * \brief Mode de traitement des caract�res arrivant sur l'afficheur.
     * @param[in] inc Incr�mente ou d�cr�mente le compteur d'adresse.
     * @param[in] shift D�placement ou non des caract�res d�j� affich�s.
     */
    void vLCD_EntryMode(const eID inc, const eShift shift);

    /**
     * \brief D�place le curseur ou l'afficheur.
     * @param[in] beShifted Indique si c'est le curseur ou les caract�res.
     * @param[in] direction Indique la direction.
     */
    void vLCD_Shift(const CursorDisplayShift beShifted, const eDirection direction);

    /**
     * \brief Determine les param�tres de l'afficheur.
     * \details La fonte 5x10 ne peut �tre utilis�e que pour les afficheurs � 1
     * ligne.
     * \param[in] interface Bus 4 ou 8 bits.
     * \param[in] lines 1 ou plusieurs lignes.
     * \param[in] font Font 5x10 ou 5x8
     */
    void vLCD_Function(const eInterface interface, const eLines lines,
                       const eFont font);

    /**
     * \brief Initialise le contr�leur HD44780
     */
    void vHD44780Init(void);

    /**
     * \brief Intialisation du module de gestion de l'afficheur.
     */
    void vLCDInit(void);

    /**
     * @}
     */

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _HD44780_H */

/* *****************************************************************************
 End of File
 */

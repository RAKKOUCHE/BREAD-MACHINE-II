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
 * \brief Fichier entête de la gestion de l'afficheur.
 *
 * \details Ce fichier fournit les prototypes et les définitions utilisés par le
 * programme pour  gérer l'afficheur.
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
     * \brief Enumération des commandes HD44780
     */
    enum
    {
        LCD_CLEAR = 0b00000001, /*!<Efface l'affcheur et positionne le compteur
                                 * d'adresse à 0 et efface l'afficheur.*/
        LCD_HOME = 0b00000010, /*!<Positionne le curseur au premier caractère de
                                * la prmière ligne.*/
        LCD_ENTRY_SET = 0b00000100, /*!<Défini l'incrémentation du curseur, la
                                     * direction du glissement.*/
        LCD_DISPLAY_CONTROL = 0b00001000, /*!<Active ou desactive l'afficheur,
                                           * Active ou desactive le curseur,
                                           * Active ou desactive le clignotement
                                           * du curseur.*/
        LCD_SHIFT_DISPLAY_CURSOR = 0b00010000, /*!<Déplace la position du
                                                * curseur ou de l'afficheur
                                                * sans modifier l'affichage.*/
        LCD_FUNCTION_SET = 0b00100000, /*!<Définie le type d'interface(4 / 8 bits),
                                        * le nombre de lignes et la fonte des
                                        * caractères.*/
        LCD_SET_CGRAM_ADRESS = 0b01000000, /*!<Fixe la valeur du compteur
                                            * d'adresse de la ram graphiue.*/
        LCD_SET_DDRAM_ADDRESS = 0b10000000, /*!<Fixe la valeur du compteur
                                             * d'adresse de la ram de données.*/
    };

    /**
     * \brief Indique si l'afficheur est actif ou non.
     */
    typedef enum
    {
        LCD_Off = 0, /*!<Afficheur désactivé.*/
        LCD_On = 1, /*!<Afficheur activé.*/
    } LCD_ON_OFF;

    /**
     * \brief Indique si le curseur est affiché ou non.
     */
    typedef enum
    {
        Cursor_Off = 0, /*!<Curseur éteint.*/
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
     * \brief Indique si c'est le curseur qui se déplace ou si c'est
     * les caractères.
     */
    typedef enum
    {
        C_move = 0, /*!<Le curseur se déplace.*/
        D_shift = 1, /*!<Les caractères se dplacent.*/
    } CursorDisplayShift;

    /**
     * \brief Indique si l'affichage se déplace par rapport au curseur.
     * \details Vers la droite si l'adresse est incrémenté, vers la gauche si
     * l'adresse est décrémentée.
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
        decrement = 0, /*!<Décrementation de l'adresse.*/
        increment = 1, /*!<Incrémentation de l'adresse.*/
    } eID;

    /**
     * \brief Direction du déplacement
     */
    typedef enum
    {
        left = 0, /*!<Déplacement vers la gauche.*/
        right = 1, /*!<Déplacement vers la drote.*/
    } eDirection;

    /**
     * \brief Type d'interface(4 ou 8 bits)
     */
    typedef enum
    {
        bits4 = 0, /*!<Interface 4 bit de DB4 à DB7.*/
        bits8 = 1, /*!<Interface 8 bits de DB0 à DB7.*/
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
     * \brief Fonte utilisée.
     */
    typedef enum
    {
        lo, /*!<5x8, nécessaire si plus d'une ligne.*/
        hi, /*!<5x10, seulement pour 1 ligne.*/
    } eFont;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Requête sur la disponibilité de l'afficheur.
     * @return True si l'afficheur est opérationnel.
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
     * \brief Positionne le curseur sur le premier caractère de la première
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
     * @param[in] byLine Numéro de la ligne à effacer.
     */
    void vLCDClearLine(const uint8_t byLine);

    /**
     * \brief Contrôle l'afficheur
     * @param[in] d_on Afficheur allumé ou non.
     * @param[in] c_on Curseur affiché ou non.
     * @param[in] b_on Curseur clignotant ou non.
     */
    void vLCD_Display_control(const LCD_ON_OFF d_on, const Cursor_ON_OFF c_on, const Blink_ON_OFF b_on);


    /**
     * \brief Mode de traitement des caractères arrivant sur l'afficheur.
     * @param[in] inc Incrémente ou décrèmente le compteur d'adresse.
     * @param[in] shift Déplacement ou non des caractères déjà affichés.
     */
    void vLCD_EntryMode(const eID inc, const eShift shift);

    /**
     * \brief Déplace le curseur ou l'afficheur.
     * @param[in] beShifted Indique si c'est le curseur ou les caractères.
     * @param[in] direction Indique la direction.
     */
    void vLCD_Shift(const CursorDisplayShift beShifted, const eDirection direction);

    /**
     * \brief Determine les paramètres de l'afficheur.
     * \details La fonte 5x10 ne peut être utilisée que pour les afficheurs à 1
     * ligne.
     * \param[in] interface Bus 4 ou 8 bits.
     * \param[in] lines 1 ou plusieurs lignes.
     * \param[in] font Font 5x10 ou 5x8
     */
    void vLCD_Function(const eInterface interface, const eLines lines,
                       const eFont font);

    /**
     * \brief Initialise le contrôleur HD44780
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

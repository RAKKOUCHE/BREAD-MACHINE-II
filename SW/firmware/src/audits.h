/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 01
 * 
 * \file audits.h
 * 
 * \brief Fichier entête de la gestion des audits.
 * 
 * \details Gestion des audits
 *  
 ***************************************************************************/

#ifndef _AUDITS_H    /* Guard against multiple inclusion */
#define _AUDITS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * \defgroup audits AUDITS
     * Gestion des audits dans l'eeprom.
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
    // *****************************************************************************

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    /**
     * \brief Positionne le flag de RAZ
     * @param isRAZ flag à true quand les audits viennent d'être RAZ.
     */
    void setIsRAZAudit(bool isRAZ);

    /**
     * \brief retourne le flag indiquant si les audits sont à zéro
     * @return true si le reset vient d'6etre effectué.
     */
    bool getIsRAZAudit(void);

    /**
     * \brief Initialisation du module des audits.
     */
    void vAuditsInit(void);

    /**
     * @}
     */
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _AUDITS_H */

/* *****************************************************************************
 End of File
 */

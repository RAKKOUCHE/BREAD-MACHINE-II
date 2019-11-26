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

#include "MDB/mdb_cg.h"


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

#define ADDRESSBASEAUDIT 0
#define ADDRESSCGIN ADDRESSBASEAUDIT /*0*/
#define ADDRESSCGOUT (ADDRESSCGIN + (NUMBERCHANNELSCG * sizeof(uint32_t))) /*64*/
#define ADDRESSBVIN (ADDRESSCGOUT + (NUMBERCHANNELSCG * sizeof(uint32_t))) /*128*/
#define ADDRESSPRODUCT (ADDRESSBVIN + (NUMBERCHANNELSBV) * sizeof(uint32_t))) /*192*/
#define ADDRESSCASH (ADDRESSPRODUCT + (PRODUCT_NUMBER * sizeof(uint32_t))) /*204*/
#define ADDRESSCL (ADDRESSCASH + sizeof(uint32_t)) /*208*/
#define ADDRESSOVERPAY (ADDRESSCL + sizeof(uint32_t) /*212*/

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Etats de la tâche des audits.
     */
    typedef enum
    {
        AUDITS_STATE_INIT, /*!<Initialisation des audits.*/
        AUDITS_STATE_READ, /*!<Lecture des audits en eeprom. Si le flag 
                        * d'initialisation n'a pas la valeur 0xA5A5A5A5, les
                        * audits seront  remis à zéro.*/
        AUDITS_STATE_IDLE, /*!<Aucune opération requise sur les audits.*/
        AUDITS_STATE_CLEAR, /*!<Enregistre 0xFFFFFFFF pour le flag d'initialisation
                         * et positionne l'état en mode lecture pour provoquer 
                         * la remise à zéro des audits. */
        AUDITS_STATE_NUM, /*!<Nombre d'état.*/
        AUDITS_STATE_SEND_TO_PC, /*!<Envoie vers le PC les audits.*/
    } AUDITS_STATES;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Requête du montant de l'audit à l'adresse spécifié
     * @param Address Index dans la structure audits.
     * @return Le montant contenu à l'adresse indiquée.
     */
    uint32_t getAuditValue(uint32_t Address);
    
    /**
     * \brief Sauvegarde un audit.
     * @param[in] Address dans l'eeprom de la valeur.
     * @param[in] value Valeur à enregistrer.
     */
    void setAuditValue(const uint32_t Address, const uint32_t value);
    /**
     * \brief Modifie l'état de la machine d'état des audits
     * @param state Nouvel état de la machine d'état
     */
    void setAuditState(AUDITS_STATES state);

    /**
     * \brief Renvoi le flag indiquant si les audits ont étés remise à zéro.
     * @return true quand les audits viennent d'être remis à zéro.
     */
    bool getIsRAZAudit(void);
    /**
     * \brief Positionne le flag de RAZ
     * @param isRAZ flag à true quand les audits viennent d'être RAZ.
     */
    void setIsRAZAudit(bool isRAZ);

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

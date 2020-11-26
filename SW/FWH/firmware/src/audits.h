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
 * \brief Fichier ent�te de la gestion des audits.
 *
 * \details Gestion des audits
 *
 ***************************************************************************/

#ifndef _AUDITS_H    /* Guard against multiple inclusion */
#define _AUDITS_H

#include <string.h>
#include <machine/types.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "communDef.h"
#include "hd44780.h"
#include "MDB/mdb_bv.h"
#include "MDB/mdb_cg.h"
#include "eeprom.h"
#include "peripheral/nvm/processor/nvm_p32mx575f512l.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/usart/processor/usart_p32mx575f512l.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

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
#define ADDRESSCGOUT (ADDRESSCGIN + (NUMBERCHANNELSCG * sizeof(uint32_t))) /*32*/
#define ADDRESSBVIN (ADDRESSCGOUT + (NUMBERCHANNELSCG * sizeof(uint32_t))) /*64*/
#define ADDRESSPRODUCT (ADDRESSBVIN + (NUMBERCHANNELSBV) * sizeof(uint32_t))) /*96*/
#define ADDRESSOVERPAY (ADDRESSPRODUCT +  (PRODUCT_NUMBER * sizeof(uint32_t)) /*108*/
#define ADDRESSCL (ADDRESSOVERPAY + sizeof(uint32_t)) /*112*/

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Etats de la t�che des audits.
     */
    typedef enum
    {
        AUDITS_STATE_INIT, /*!<Initialisation des audits.*/
        AUDITS_STATE_READ, /*!<Lecture des audits en eeprom. Si le flag
                        * d'initialisation n'a pas la valeur 0xA5A5A5A5, les
                        * audits seront  remis � z�ro.*/
        AUDITS_STATE_IDLE, /*!<Aucune op�ration requise sur les audits.*/
        AUDITS_STATE_CLEAR, /*!<Enregistre 0xFFFFFFFF pour le flag d'initialisation
                         * et positionne l'�tat en mode lecture pour provoquer
                         * la remise � z�ro des audits. */
        AUDITS_STATE_NUM, /*!<Nombre d'�tat.*/
        AUDITS_STATE_SEND_TO_PC, /*!<Envoie vers le PC les audits.*/
    } AUDITS_STATES;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Requ�te du montant de l'audit � l'adresse sp�cifi�
     * @param Address Index dans la structure audits.
     * @return Le montant contenu � l'adresse indiqu�e.
     */
    uint32_t getAuditValue(uint32_t Address);

    /**
     * \brief Sauvegarde un audit.
     * @param[in] Address dans l'eeprom de la valeur.
     * @param[in] value Valeur � enregistrer.
     */
    void setAuditValue(const uint32_t Address, const uint32_t value);
    /**
     * \brief Modifie l'�tat de la machine d'�tat des audits
     * @param state Nouvel �tat de la machine d'�tat
     */
    void setAuditState(AUDITS_STATES state);

    /**
     * \brief Renvoie le flag indiquant si les audits ont �t�s remise � z�ro.
     * @return true quand les audits viennent d'�tre remis � z�ro.
     */
    bool getIsRAZAudit(void);
    /**
     * \brief Positionne le flag de RAZ
     * @param isRAZ flag � true quand les audits viennent d'�tre RAZ.
     */
    void setIsRAZAudit(bool isRAZ);

    /**
     * \brief Remise � z�ro des audits dans l'eeprom.
     */
    void RAZAudits(void);
    
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

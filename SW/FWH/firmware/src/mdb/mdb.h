/**
 * \file    mdb.h
 * \brief   gestion de la chaine MDB.
 * \author: Rachid AKKOUCHE
 * \version 1.0.0
 * \date 20 mars 2016, 18:46
 */

#ifndef MDB_H
#define	MDB_H

#ifdef	__cplusplus
extern "C"
{
#endif

    /*Includes*****************************************************************/
#include <GenericTypeDefs.h>
#include <stdio.h>
#include <stdbool.h>
//#include "globaldef.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "mdbGeneric.h"
#include "mdb_cg.h"
#include "mdb_bv.h"
#include "mainboard.h"
#include "hd44780.h"

    /*Defines*******************************************************/

    /**
     * \def MDB_POLLING_MS
     * \brief temps de polling en ms du lecteur cashless.
     */
    //#define MDB_POLLING_MS ((125 + 200) / 6) * MILLISEC //Environ 54
#define MDB_POLLING_MS (150)

    /**
     * \def MDBRETRY
     * \brief Nombre de loop avant de vérifier si un périphérique est disponible
     */
#define MDBRETRY 60

    /**
     * \def MDB_TO
     * \brief delay mamixmum de réponse du CL
     */
#define MDB_TO (15 * MILLISEC)

    //Réponses
#define ACK 0x00 /*!< Réponse OK. */
#define RET 0xAA, /*!< Retransmettre les données. */
#define NAK 0XFF /*!< Réponse incorrecte. */

    //Réponses POLL
#define RSP_NAK                     0xFF
#define RSP_RET                     0xAA
#define RSP_JUST_RESET              0x00 //Pour les changers et les lecteurs de billets

#define RSP_READER_CONFIG_DATA      0x01
#define RSP_DISPLAY_REQUEST         0x02
#define RSP_BEGIN_SESSION           0x03
#define RSP_SESSION_CANCEL_REQUEST  0x04
#define RSP_VEND_APPROVED           0x05
#define RSP_VEND_DENIED             0x06
#define RSP_END_SESSION             0x07
#define RSP_CANCELLED               0x08
#define RSP_PERIPHERAL_ID           0x09
#define RSP_MALFUNCTION_ERROR       0x0A
#define RSP_CMD_OUT_OF_SEQUENCE     0x0B
#define RSP_BUSY                    0x0C
#define RSP_REVALUE_APPROVED        0x0D
#define RSP_REVALUE_DENIED          0x0E
#define RSP_REVALUE_LIMIT_AMOUNT    0x0F
#define RSP_USER_FILE_DATA          0x10
#define RSP_TIME_DATE_REQUEST       0x11
#define RSP_DATA_ENTRY_REQUEST      0x12
#define RSP_DATA_ENTRY_CANCEL       0x13
#define RSP_FTL_REQ_TO_RCV          0x1B
#define RSP_FTL_RETRY_DENY          0x1C
#define RSP_FTL_SEND_BLOCK          0x1D
#define RSP_FTL_OK_TO_SEND          0x1E
#define RSP_FTL_REQ_TO_SEND         0x1F
#define RSP_DIAGNOSTIC_RESPONSE     0xFF

    // Commandes MDB.
#define CMD_RESET                   0x00 /*!< Reset le périphérique. */
#define CMD_SETUP                   0x01 /*!< Lecture des paramètres du périphérique. */
#define CMD_STATUS                  0x01 /*!< Lecture des paramètres du périphérique. */
#define CMD_POLL                    0x03 /*!< Obtient les informations du périphérique. */
#define CMD_SECURITY                0x02
#define CMD_VEND                    0x03 /*!< Demande d'approbation d'une vente. */
#define CMD_CHANGER_POLL            0x03 /*!< Demande d'approbation d'une vente. */
#define CMD_BILL_POLL               0x03
#define CMD_READER                  0x04 /*!< Active desactive le lecteur. */
#define CMD_BILL_TYPE               0x04
#define CMD_REVALUE                 0x05 /*!< Réevaluation de la clé. */
#define CMD_ESCROW                  0x05 /*!< Encaisse le billet*/
#define CMD_DISPENSE                0x05
#define CMD_STACKER                 0x06
#define CMD_NO_PENDING              0xFF

    // MDB sous commandes.
#define SUB_CONFIG_DATA             0x00
#define SUB_MAX_MIN_PRICE 0x01
#define SUB_VEND_REQUEST 0x00
#define SUB_VEND_CANCEL 0x01
#define SUB_VEND_SUCCESS 0x02
#define SUB_VEND_FAILURE 0x03
#define SUB_VEND_SESSION_COMPLETE 0x04
#define SUB_VEND_CASH_SALE 0x05
#define SUB_NEGATIVE_VEND_REQUEST 0x06
#define SUB_READER_DISABLE 0x00
#define SUB_READER_ENABLE 0x01
#define SUB_READER_CANCEL 0x02
#define SUB_REVALUE_REQUEST 0x00
#define SUB_REVALUE_LIMIT_REQUEST 0x01
#define SUB_READ_USER_FILE 0x01
#define SUB_WRITE_USER_FILE 0x02
#define SUB_WRITE_TIME_DATE 0x03

#define SUB_IDENTIFICATION_2 0x02
#define SUB_READER_FEATURE_ENABLE 0x04
#define SUB_CHANGER_FEATURE_ENABLE 0x01
#define SUB_BILL_FEATURE_ENABLE 0x01
#define SUB_FTL_REQ_TO_RCV 0xFA
#define SUB_FTL_RETRY_DENY 0xFB
#define SUB_FTL_SEND_BLOCK 0xFC
#define SUB_FTL_OK_TO_SEND 0xFD
#define SUB_FTL_REQ_TO_SEND 0xFE
#define SUB_DIAGNOSTICS 0xFF

    /*Enumerations*************************************************************/

    /*Structures***************************************************************/

    /*Prototypes***************************************************************/

    /**
     * @fn vMDBINIT
     * @brief Initialisation de la chaine MDB.
     */
    void vMDBInit(void);

    /**************************************************************************/

    /**
     * brief Requête du handle de la  tâche MDB.
     * @return handle de la tâche MDB.
     */
    TaskHandle_t getHandleMDB(void);

    /**
     * \brief Requête de la position du point dçimal.
     * @return Un octet contenant la position du point décimal.
     */
    uint8_t getMDBDecimalPos(void);

    /**
     * \brief Défini la position de la virgule.
     * @param value Position de la virgule
     */
    void setMDBDecimalPoint(uint8_t value);

    /**
     * \brief Défini la valeur du diviseur.
     * @param divider Dviseur.
     */
    void setMDBCurrencyDivider(uint16_t divider);

    /**
     * \brief requête du flag indiquant que la chaine MDB est prête.
     * @return true si la chaîne MDB est prête.
     */
    BOOL getIsMDBChecked(void);
    /**Checked
     * \brief Requête du diviseur MDB.
     * @return Le diviseur MDB
     */
    uint16_t getMDBCurrencyDivider(void);

    /**
     * \brief Requête de la configuration du périphérique.
     * @param byDeviceAddress Adresse du périphérique.
     * @param byStatus Configuration du périphérique.
     * @param byLen Taille de la striucture qui contient la ocnfiguration.
     * @return true si la réponse du périphérique est correcte.
     */
    BOOL isGetMDBConfig(const uint8_t byDeviceAddress, void *byStatus, const uint8_t byLen);

    /**
     * \brief Efectue la commande reset sur le périphérique
     * @param byDeviceAddress Adresse du périphérique
     * @return true si la réponse du périphérique est correcte
     */
    BOOL isMDBReset(const uint8_t byDeviceAddress);

    /**
     * @fn decimalDivider
     * @brief Calcul le diviseur du périphérique MDB
     * @detail On calcule 10 à la puissance byDecimal.
     * @param[in] byDecimal position de la virgule du module
     * @return le diviseur.
     */
    WORD decimalDivider(uint8_t byDecimal);

    /**************************************************************************/

    /**
     * @fn vDisplayRefused
     * @brief Affiche le texte lors du refus d'une devise.
     */
    void vDisplayRefused(void);

    /**************************************************************************/

    /**
     * @fn vVMCAcknowledge
     * @brief Renvoie ack ou nack en réponse au périphérique.
     * @param[in] byAcknowledge
     */
    void vVMCAcknowledge(const uint8_t byAcknowledge);

    /**************************************************************************/

    /**
     * \brief Envoie une commande au périphérique MDB
     * @param[in] byAddress Adresse du périphérique auquel on envoie la commande.
     * @param[in] byCommand Commande envoyée au périphérique
     * @param[in] byLenParameters Longeur des paramètres à envoyer au
     * periphérique.
     * @param ptrParameters Pointeur sur le tableau contenant les paramères à
     * envoyer au périphérique
     * @param ptrAnswer ptrAnswer Pointeur sur le tableau qui contiendra la
     * réponse.
     * @return Le nombre d'octet contenu dans la réponse.
     */
    uint8_t byMDBSendCommand(const uint8_t byAddress, const uint8_t byCommand,
                             const uint8_t byLenParameters, void *ptrParameters,
                             void *ptrAnswer);


    /**************************************************************************/

    /**
     * @fn isMDBPoll
     * @brief Vérifie régulièrement l'état des périphériques.
     * @param[in] byDeviceAddress Adresse du périphérique.
     * @param[out] byResponse Pointeur sur un tableau contenant la réponse du périphérique.
     * @param[out] byLenAnswer Longeur de la réponse.
     * @return true si l'opération s'est déroulé correctement.
     */
    BOOL isMDBPoll(const uint8_t byDeviceAddress, uint8_t *byResponse, uint8_t * byLenAnswer);

#ifdef	__cplusplus
}
#endif

#endif	/* MDB_H */


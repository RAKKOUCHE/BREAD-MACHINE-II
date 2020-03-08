/*
 * File:   mdb_cg.h
 * Author: Rachid AKKOUCHE
 *
 * Created on 20 mars 2016, 18:47
 */

#ifndef MDB_CG_H
#define	MDB_CG_H

#ifdef	__cplusplus
extern "C"
{
#endif

    /*Include******************************************************************/

#include <GenericTypeDefs.h>
#include "mdb.h"
#include "hd44780.h"
#include "mainboard.h"
#include "FreeRTOS.h"
#include "queue.h"

    /*Defines******************************************************************/

    /**
     * \brief Nombre de canaux du changeur.
     */
#define NUMBERCHANNELSCG 8

    /**
     * \def CGADDRESS
     * \brief Adresse du rendeur.
     */
#define CGADDRESS 0X08

#define COIN_DISPENDED_MANUALLY 0B10000000
#define COIN_INSERTED 0B01000000
#define COIN_REFUSED 0B00100000

    /*Enums********************************************************************/
    typedef enum __attribute__((packed))
    {
        CG_RESET = 0,
            CG_SETUP = 1,
            CG_TUBE_STATUS = 2,
            CG_POLL = 3,
            CG_COIN_TYPE = 4,
            CG_DISPENSE = 5,
            CG_EXPANSION_CMD = 7,
            CG_INIT,
    }
    CG_STATUS;

    typedef enum __attribute__((packed))
    {
        SUB_CHANGER_IDENTIFICATION = 0x00,
            SUB_FEATURE_ENABLE = 0x01,
            SUB_ALTERNATIVE_PAYOUT = 0x02,
            SUB_ALT_PAYOUT_STATUS = 0x03,
            SUB_PAYOUT_VALUE_POLL = 0x04,
            SUB_DIAGNOSTIC_STATUS = 0x05,
            SUB_MANUAL_FILL_REPORT = 0x06,
            SUB_MANUAL_PAYOUT_REPORT = 0x07,
    }
    CG_SUB_CMD;

    typedef enum __attribute__((packed))
    {
        CG_REQUEST_IDENTIFICATION,
            CG_FEATURE_ENALBE,
            CG_PAYOUT,
            CG_PAYOUT_STATUS,
            CG_PAYOUT_VALUE_POLL,
            CG_DIAGNOSTIC_STATUS,
    }
    EXPANSION_CMD;

    typedef enum __attribute__((packed))
    {
        CG_ESCROW = 0B00000001,
            CG_PAYOUT_BUSY = 0B00000010,
            CG_NO_CREDIT = 0B00000011,
            CG_DEFECTIVE_TUBE = 0B00000100,
            CG_DOUBLE_ARRIVAL = 0B00000101,
            CG_UNPLUGGED = 0B00000110,
            CG_TUBE_JAM = 0B00000111,
            CG_ROM_ERROR = 0B00001000,
            CG_ROUTE_ERROR = 0B00001001,
            CG_BUSY = 0B00001010,
            CG_JUST_RESET = 0B00001011,
            CG_COIN_JAM = 0B00001100,
            CG_COIN_REMOVAL = 0B00001101,
    }
    RSP_STATUS_CG;

    typedef enum __attribute__((packed))
    {
        POWER_UP = 1,
            POWER_DOWN = 2,
            OK = 3,
            KEYPAD_SHIFT = 4,
            MANUAL_FILL_PAYOUT = 5,
            INVENTORY_INFO = 5,
            INHIBIT = 6,
            CHANGER_ERROR = 10,
            DISCRIMINATOR_ERROR = 11,
            GATE_ERROR = 12,
            SEPARATOR_ERROR = 13,
            DISPENSER_ERROR = 14,
            TUBE_ERROR = 15,
    }
    DIAG_STATUS_Z1;

    typedef enum __attribute__((packed))
    {
        NON_SPECIFIC_ERROR = 0,
            POWERING_UP = 0,
            POWERING_DOWN = 0,
            READY = 0,
            SHIFTED = 0,
            CHECKSUM_1_ERROR = 1,
            CHECKSUM_2_ERROR = 2,
            LO_VOLTAGE = 3,
            MANUAL_ACTIVE = 10,
            FLIGHT_DECK_OPEN = 10,
            ESCROW_RETURN_OPEN = 11,
            COIN_JAM = 30,
            INVENTORY_AVAILABLE = 20,
    }
    DIAG_STATUS_Z2;

    /*Structures***************************************************************/

    /**
     * \typedef ChangeGiverConfig
     * \brief structure contenant la configuration des rendeurs
     */
    typedef struct __attribute__((packed))
    {
        MDBGENERICDEVICECONFIG deviceConfig; /*!<Niveau MDB, Country code*/
        uint8_t byScalingFactor; /*!< Facteur de multiplication appliqué à tous les
                               * montants du périphérique.*/
        uint8_t byDecimalPlace; /*!< Position de la virgule en partant du chiffre
                              * le moins significatif. */
        uint8_t byCoinRouting[2]; /*!<Liste des pièces pouvant entrer dans les
                                * tubes.*/
        uint8_t byCoinValue[NUMBERCHANNELSCG]; /*!Valeur des pièces.*/
    } CG_CONFIG;

    /**
     * \typedef TubeStatus
     * \brief Stucture contenant l'état des seuils et le niveau des tubes.
     */
    typedef struct __attribute__((packed))
    {
        uint8_t byFull[2];
        uint8_t byLevel[16];
    } TUBE_STATUS;

    /**
     * \typedef CoinType
     * \brief Strucute contenant la validation des pièces.
     */
    typedef struct __attribute__((packed))
    {

        union __attribute__((packed))
        {
            uint8_t byCoinEnable[2];
            WORD wCoinEnable;
        };
        WORD wDispenseEnable;
    } COIN_TYPE;

    /**
     * \typedef ChangerIdentification
     * \brief Structure contenant l'identification et les options du rendeur.
     */
    typedef struct __attribute__((packed))
    {
        uint8_t ManufacturerCode[3];
        uint8_t SerialNumber[12];
        uint8_t Model[12];
        uint8_t SWVersion[2];
        uint8_t Optionnal[4];
    } CG_IDENTIFICATION;

    typedef struct __attribute__((packed))
    {
        DIAG_STATUS_Z1 Z1;
        DIAG_STATUS_Z2 Z2;
    } CG_DIAG;


    /*Constante****************************************************************/

    /*Variables****************************************************************/
    /*Prototypes***************************************************************/

    /**
     * \brief
     * @return
     */
    TaskHandle_t getChangeTaskHandle(void);

    /**
     * \brief
     * @return
     */
    BOOL getGCInitialized(void);

    /**
     * \brief
     * @param isFinished
     */
    void setIsChangeFinished(const BOOL isFinished);

    /**
     * \brief
     * @return
     */
    BOOL getIsChangeFinished(void);

    /**
     * \brief
     * @param state
     */
    void setChangeGiverTaskState(CG_STATUS state);

    /**
     * \brief
     * @return
     */
    COIN_TYPE getCoinType(void);

    /**
     * \brief
     * @param byChannel
     * @return
     */
    uint32_t getCoinValue(uint8_t byChannel);

    /**
     * \brief
     * @param mask
     */
    void setCoinEnableMask(const uint32_t mask);

    /**
     * \brief
     */
    void vCGInit(void);

    /**
     * \brief
     * @return
     */
    COIN_TYPE getCoinType(void);

    /**
     * @fn isSetCoinEnable
     * @brief Active ou désactive les canaux du changeur.
     * @param isEnable booleen indiquant si les canaux sont activés ou non.
     * @param coinType Pointeur sur le tableau contenant l'état des canaux.
     * @return true si l'opération s'est déroulé correctement.
     */
    BOOL isSetCoinEnable(const BOOL isEnable, const COIN_TYPE *coinType);

    /**
     * @fn vTaskCG
     * @brief Tâche parcourant les états du changeur.
     */
    void vTaskCG(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MDB_CG_H */


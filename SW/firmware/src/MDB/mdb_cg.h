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
#include "mainboard2.h"
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
    typedef enum
    {
        CG_RESET = 0,
        CG_SETUP = 1,
        CG_TUBE_STATUS = 2,
        CG_POLL = 3,
        CG_COIN_TYPE = 4,
        CG_DISPENSE = 5,
        CG_EXPANSION_CMD = 7,
        CG_INIT,
    } CG_STATUS;

    typedef enum
    {
        SUB_CHANGER_IDENTIFICATION = 0x00,
        SUB_FEATURE_ENABLE = 0x01,
        SUB_ALTERNATIVE_PAYOUT = 0x02,
        SUB_ALT_PAYOUT_STATUS = 0x03,
        SUB_PAYOUT_VALUE_POLL = 0x04,
        SUB_DIAGNOSTIC_STATUS = 0x05,
        SUB_MANUAL_FILL_REPORT = 0x06,
        SUB_MANUAL_PAYOUT_REPORT = 0x07,
    } CG_SUB_CMD;

    typedef enum
    {
        CG_REQUEST_IDENTIFICATION,
        CG_FEATURE_ENALBE,
        CG_PAYOUT,
        CG_PAYOUT_STATUS,
        CG_PAYOUT_VALUE_POLL,
        CG_DIAGNOSTIC_STATUS,
    } EXPANSION_CMD;

    typedef enum
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
    } RSP_STATUS_CG;

    typedef enum
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
    } DIAG_STATUS_Z1;

    typedef enum
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
    } DIAG_STATUS_Z2;

    /*Structures***************************************************************/

    /**
     * \typedef ChangeGiverConfig
     * \brief structure contenant la configuration des rendeurs
     */
    typedef struct
    {
        MDBGENERICDEVICECONFIG deviceConfig; /*!<Niveau MDB, Country code*/
        BYTE byScalingFactor; /*!< Facteur de multiplication appliqué à tous les 
                               * montants du périphérique.*/
        BYTE byDecimalPlace; /*!< Position de la virgule en partant du chiffre 
                              * le moins significatif. */
        BYTE byCoinRouting[2]; /*!<Liste des pièces pouvant entrer dans les 
                                * tubes.*/
        BYTE byCoinValue[NUMBERCHANNELSCG]; /*!Valeur des pièces.*/
    } CG_CONFIG;

    /**
     * \typedef TubeStatus
     * \brief Stucture contenant l'état des seuils et le niveau des tubes.
     */
    typedef struct
    {
        BYTE byFull[2];
        BYTE byLevel[16];
    } TUBE_STATUS;

    /**
     * \typedef CoinType
     * \brief Strucute contenant la validation des pièces.
     */
    typedef struct
    {

        union
        {
            BYTE byCoinEnable[2];
            WORD wCoinEnable;
        };
        WORD wDispenseEnable;
    } COIN_TYPE;

    /**
     * \typedef ChangerIdentification
     * \brief Structure contenant l'identification et les options du rendeur.
     */
    typedef struct
    {
        BYTE ManufacturerCode[3];
        BYTE SerialNumber[12];
        BYTE Model[12];
        BYTE SWVersion[2];
        BYTE Optionnal[4];
    } CG_IDENTIFICATION;

    typedef struct
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
    bool getGCInitialized(void);

    /**
     * \brief
     * @param isFinished
     */
    void setIsCangeFinished(const bool isFinished);
    
    /**
     * \brief
     * @return 
     */
    bool getIsChangeFinished(void);
    
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
    bool isSetCoinEnable(const bool isEnable, const COIN_TYPE *coinType);

    /**
     * @fn vTaskCG
     * @brief Tâche parcourant les états du changeur.
     */
    void vTaskCG(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MDB_CG_H */


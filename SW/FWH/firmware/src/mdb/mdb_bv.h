/*
 * File:   mdb_bv.h
 * Author: Rachid AKKOUCHE
 *
 * Created on 20 mars 2016, 18:49
 */

#ifndef MDB_BV_H
#define	MDB_BV_H

#ifdef	__cplusplus
extern "C"
{
#endif


    /*Defines******************************************************************/

#include <stdbool.h>
    //#include <stdio.h>
#include "mdbGeneric.h"
#include "mdb.h"

    /**
     * \addtogroup MDB_BV
     * \ingroup MDB
     * \brief  Gestion du lecteur de billet.
     * @{
     */

    /**
     * \brief Nombre de canaux du lecteur de billets
     */
#define NUMBERCHANNELSBV 8

    /**
     * \def CGADDRESS
     * \brief Adresse du rendeur.
     */
#define BVADDRESS 0X30

#define BILL_ACCEPTED 0B10000000

    /*Enums********************************************************************/

    typedef enum
    {
        STACKED = 0B00000000,
            ESCROW = 0B00010000,
            RETURNED = 0B00100000,
            REJECTED = 0B01000000,
    }
    BILL_INTRODUCED;

    typedef enum
    {
        BV_RESET = 0X00,
            BV_SETUP = 0X01,
            BV_SECURITY = 0X02,
            BV_POLL = 0X03,
            BV_BILL_TYPE = 0X04,
            BV_ESCROW = 0X05,
            BV_STACKER = 0X06,
            BV_EXPANSION_CMD = 0X07,
            BV_INIT,
    }
    BV_STATUS;

    typedef enum
    {
        LEVEL1_ID_WO_OPTIONS = 0x00,
            LEVEL2_ENABLE_FEATURE = 0X01,
            LEVEL2_ID_W_OPTIONS = 0x02,
    }
    BV_SUB_CMD;

    typedef enum
    {
        BV_MOTOR_DEFAULT = 0B00000001,
            BV_SENSOR_DEFAULT = 0B00000010,
            BV_BUSY = 0B00000011,
            BV_ROM_ERROR = 0B00000100,
            BV_JAM_ACCEPTANCE = 0B00000101,
            BV_JUST_RESET = 0B00000110,
            BV_BILL_REMOVED = 0B00000111,
            BV_CASHBOX_OPEN = 0B00001000,
            BV_DISABLED = 0B00001001,
            BV_INVALID_ESCROW = 0B00001010,
            BV_REFUSED = 0B00001011,
            BV_BILL_REMOVAL = 0B00001100,

    }
    BV_STATUS_ACCEPTED;

    /*Structures***************************************************************/

    /**
     * \brief Strucute contenant la validation des pièces.
     */
    typedef struct 
    {

        union
        {
            uint8_t byBillEnable[2];
            uint16_t wBillEnable;
        };
        uint8_t byEscrowEnable[2];
    }
    BILL_TYPE;

    /**
     * \brief structure contenant la configuration des rendeurs
     */
    typedef struct
    {
        MDBGENERICDEVICECONFIG deviceConfig;
        uint16_t wScalingFactor; /*!< Facteur de multiplication appliqué à tous les montants du périphérique.*/
        uint8_t byDecimalPlace; /*!< Position de la virgule en partant du chiffre le moins significatif. */
        uint16_t wStackerCapacity;
        uint8_t bySecurityLevel[2];
        uint8_t byEscrow;
        uint8_t byBillValue[NUMBERCHANNELSBV];
    }
    BV_CONFIG;

    /**
     * \brief Structure contenant l'identification et les options du lecteur.
     */
    typedef struct
    {
        uint8_t ManufacturerCode[3];
        uint8_t SerialNumber[12];
        uint8_t Model[12];
        uint8_t SWVersion[2];
        uint8_t Optionnal[4];
    }
    BV_IDENTIFICATION;

    /*Variables****************************************************************/


    /*Prototypes***************************************************************/

    /**
     * \brief
     * @param status
     */
    void setBV_State(BV_STATUS status);

    /**
     * \brief Requête du mask d'inhibiton des billets.
     * @return Mask d'inhibition du lecteur de billets.
     */
    uint32_t getBillEnableMask(void);

    /**
     * \brief Defini le mask d'inhition du lecteur de billets.
     * @param[in] mask Masque d'inhibition.
     */
    void setBillEnableMask(const uint32_t mask);

    /**
     * \brief Requête de la valeur en cts d'un billet
     * @param byChannel Numéro du canal.
     * @return Valeur en cts des billets acceptés dans le canal.
     */
    uint32_t getBillValue(uint8_t byChannel);

    /**
     * @fn vTaskBV
     * @brief tâche parcourant les etats du lecteur de billet.
     */
    void vTaskBV(void);

    /**
     * \brief
     * @return
     */
    bool getIsBVInitialized(void);

    /**
     * \brief
     * @return
     */
    BILL_TYPE getBillType(void);

    /**
     * @fn isSetBillEnable
     * @brief Active ou desactive les canaux du lecteur de billet.
     * @param isEnable Indique si les canaux seront activés ou non.
     * @param billType Pointeur sur le tableau contenant la validation des
     * billets
     * @return True si l'opération s'est déroulé correctement.
     */
    bool isSetBillEnable(const bool isEnable, BILL_TYPE *billType);

    /**
     * \brief Initialisation de la tâche du lecteur du billets.
     */
    void vBVInit(void);

    /**
     * @}
     */
    /**************************************************************************/
#ifdef	__cplusplus
}
#endif

#endif	/* MDB_BV_H */


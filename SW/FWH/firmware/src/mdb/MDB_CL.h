/* 
 * File:   CASHLESS.H
 * Author: rachid
 *
 * Created on 9 septembre 2018, 00:29
 */

#ifndef CASHLESS_H
#define	CASHLESS_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "mdb.h"
    
    /*Defines**************************************************************/
    
    /**
     * \brief Adresse du lecteur cashless.
     */
#define ADDRESS_CL 0X10

    /**
     * \brief Adresse alternative du lecteur cashless.
     */
#define  ALTERNATE_ADDRESS_CL 0X60

    /**
     * \brief Nombre de passage dans le polling du cashLess
     */
#define CASHLESSRETRY (60 * SECOND) / (MDB_POLLING * 3)

    /*End of defines*******************************************************/

    /*Enumerations*********************************************************/

    /**
     * \brief Structure contenant les variables du module mdb.
     */
//    struct __attribute__((packed))
//    {
     //   DRV_HANDLE hUsart; /*!<Handle du port s?rie.*/
//        MDB_STATE state; /*!< Etat de la t?che du moteur.*/
//        TimerHandle_t hTimerMDBNAK; /*!<Handle du TO.*/
//        TimerHandle_t hTimerMDBReponse; /*!<Handle du timer utilis? pour le TO d'une r?ponse.*/
//        TimerHandle_t hTimerInterByte; /*!<Handle du timer utilis? pour le TO entre 2 octets d'une r?ponse.*/
//        SemaphoreHandle_t hSemaphoreMDB; /*!<Semaphore de verrouillage de la fonction de commande MDB*/
//        bool isInitialized; /*!<Flag indiquant que les op?rations d'initialisation sont termin?es.*/
//        bool isNAK; /*!<Indique le TO pour la r?ponse du p?riph?rique MDB est atteint.*/
//        bool isTOResponse; /*!<Flag indiquant si le delais accord? pour une r?ponse mdb.*/
//        bool isTOInterByte; /*!<Flag indiquant si le d?lai maixmum autoris? entre 2 octets est atteint.*/
//        bool isNAKMDB; /*!<Flag indiquant que le TO pour la r?ponse du p?riph?rique MDB est atteint.*/
//        uint8_t byLenAnswer; /*!<Nombre de caract?res renvoy?s par le p?riph?riques.*/
       uint8_t answerBuffer[36];
//    }
//    mdbMaster;
    
    /**
     * \brief commande du cashless
     */
    enum __attribute__((packed))
    {
        CL_RESETREQUEST = 0X00,
            CL_SETUP = 0X01,
            CL_POLL = 0X02,
            CL_VEND = 0X03,
            CL_READER = 0X04,
            CL_REVALUE = 0X05,
            CL_EXPANSION = 0X07,
    };

    /**
     * \brief sous-commande du cashess
     */
    enum __attribute__((packed))
    {
        CL_CONFIGREQUEST = 0X00,
            CL_MAXMINPRICE = 0X01,

            CL_VENDREQUEST = 0X00,
            CL_VENDCANCEL = 0X01,
            CL_VENDSUCCESS = 0X02,
            CL_VENDFAILURE = 0X03,
            CL_SENSSION_COMPLETE = 0X04,
            CL_CASH_SALE = 0X05,
            CL_NEGATIVEVEND = 0X06,

            CL_READERDISABLE = 0X00,
            CL_READERENABLE = 0X01,
            CL_READERCANCEL = 0X02,
            CL_READERDATAENTRY = 0X03,

            CL_REVALUEREQUEST = 0X00,
            CL_REVALUELIMITREQUEST = 0X01,

            CL_REQUESTID = 0X00,
            CL_OPTIONALFEATUREENABLE = 0X04
    };

    /**
     * \bref Réponse du périphérique sur un poll.
     */
    enum __attribute__((packed))
    {
        CL_JUSTRESET = 0X00,
            CL_CONFIGDATA = 0X01,
            CL_DISPLAYREQUEST = 0X02,
            CL_BEGINSESSION = 0X03,
            CL_CANCELREQUEST = 0X04,
            CL_VENDAPPROVE = 0X05,
            CL_VENDDENIED = 0X06,
            CL_ENDSESSION = 0X07,
            CL_CANCELLED = 0X08,
            CL_PERIPERAH_ID = 0X09,
            CL_MALFUNCTION = 0X0A,
            CL_CMDOUTSEQUENCE = 0X0B,
            CL_REVALUEAPPROVED = 0X0D,
            CL_REVALUEDENIED = 0X0E,
            CL_REVALUELIMITAMOUNT = 0X0F,
            CL_DIAGNOSTICREPONSE = 0XFF,
    };
    /**
     * \brief Etat du cashless.
     */
    typedef enum
    {
        CL_STATE_BEGIN, /*!<Initialisation de la tâche cashless*/
        CL_STATE_RETRY, /*!<Etat permettant de faire attentre la tâche avant de répéter un reset.*/
        CL_STATE_RESET, /*!<Etat du traimenet du reset cashless.*/
        CL_STATE_POLL, /*!<Polling du cashless.*/
        CL_STATE_SETUP_CONFIG_DATA, /*!<Envoie la configuration de la VMC et obtient la configuration du cashless*/
        CL_STATE_SETUP_MAX_MIN_PRICE, /*!<Envoie les prix max et min du cashless.*/
        CL_STATE_EXPANSION_REQUEST_ID, /*!<Obtient les informations supplémentaires et les options. Level 03.*/
        CL_STATE_ENABLE_OPTION, /*!<Active les options le cas écheant. Toujours désactivées pour cette version.*/
        CL_STATE_ENABLE_PERIPH, /*!<Active le périphérique.*/
        CL_STATE_IDLE, /*!<Etat de repos. Not used.*/
    } CASHLESS_STATE;

    /*End of enumeration***************************************************/

    /*Structures***********************************************************/


    /**
     * \brief Structure contenant l'identification de base d'une machine ou d'un périphérique.
     */
    typedef struct __attribute__((packed))
    {
        uint8_t byCmd;
        char ManufactureID[3]; /*!<identification du fabricant (RAS).*/
        uint8_t bySerialNumber[12]; /*!<Numéro de série de la VMC.*/
        uint8_t byModelNumber[12]; /*!<Numéro de modèle de la VMC.*/
        uint8_t byFW_Rev[2]; /*!<Version du FW.*/
    }
    DEVICEID;

    /**
     * \brief Structure contenant l'identifcation du cashless.
     */
    typedef struct __attribute__((packed))
    {
        DEVICEID periphalID;
        uint8_t OPTION[3];
    }
    PERIPHERALID;

    /**
     * \brief Structure contenant la configuration du lecteur cashless.
     */
    typedef struct __attribute__((packed))
    {
        MDBGENERICDEVICECONFIG deviceConfig; /*!< Information générique sur la configuration du lecteur cashless.*/
         uint8_t byScaleFactor; /*!< Facteur de multiplication appliqué à tous les montants du périphérique.*/
        uint8_t byDecimalPlace; /*!< Position de la virgule en partant du chiffre le moins significatif. */    
       uint8_t byMaxTimeResponse; /*!< Temps maximum accordé au lecteur pour répondre.*/
        uint8_t byMiscellaneous; /*!< Options du lecteur cashless.*/
    }
    READERCONFIG;

    /**
     * \brief structure contenant la liste des paramètres de la VMC
     */
    typedef struct __attribute__((packed))
    {
        uint8_t byCmd;
        uint8_t byLevel; /*!< Niveau de la vmc.*/
        uint8_t byDisplayColumns; /*!< Nombre de caractères par ligne.*/
        uint8_t byDisplayRows; /*!< Nombre de ligne.*/
        uint8_t byDisplayInfo; /*!< Information concernant les données de configuration du cashless.*/
    }
    VMCCONFIG;

    /**
     * \brief Structure contenant le prix maximum et le prix minimum des services.
     */
    typedef struct __attribute__((packed))
    {
        uint8_t byCmd;
        union
        {
            struct
            {
                uint16_t wMax; /*!< Prix du service le plus élevé.*/
                uint16_t wMin; /*!< Prix du service le moins élevé.*/
            } MinMaxLevel2;
            struct
            {
                uint32_t dwMax; /*!< Prix du service le plus élevé.*/
                uint32_t dwMin; /*!< Prix du service le moins élevé.*/
                uint8_t countryCode[2]; /*!<Code pays précéde par 1.*/
            } MinMaxLevel3;
        };
    }
    VMCMAXMIN;
    /**
     * \brief structurant contenant les variables du module cashless
     */
    typedef struct
    {
        bool isInitialized;
        bool isPolled;
        int iBeforeRetry;
        uint8_t byTryReset;
        uint8_t byIndex;
        uint8_t byLen;
        CASHLESS_STATE state;
        VMCCONFIG VMCConfig; /*!<Configuration de la VNC.*/
        READERCONFIG readerConfig; /*!<Configuration du lecteur cashLess.*/
        VMCMAXMIN vmcMaxMin; /*!<Data du minimum et du maximum.*/
        DEVICEID vmcID; /*!<identification de la VMC.*/
        PERIPHERALID peripheralID;

    } CASHLESS;

    /*End of structures****************************************************/


    /*Variables************************************************************/

    /**
     * \brief Variable contenant la structure des variables du module cashless     */
    CASHLESS cashLessReader;

    /*End of variables*****************************************************/

    /*Prototypes***********************************************************/

    /**
     * \brief Intialisation du module cashless
     */
    void vInitCashLess(void);

    /**
     * \brief Tâche de la machine d'état du cashless
     */
    void vTaskCashLess(void);
    //
    //    /**
    //     * \brief Envoie une requête concernant la configuraton du cashLess.   
    //     * \détails Certain périphériques renvoient directement la configuration, d'autres le font au prochain polling.
    //     * @param[in] byDeviceAddress Adresse du périphérique.
    //     * @param[in] ptrParameters Paramètres de la VMC.
    //     * @return la longeur de la réponse.
    //     */
    //    uint8_t CLSetupConfigData(const uint8_t byDeviceAddress, VMCCONFIG *ptrParameters);
    /*End of prototypes****************************************************/

#ifdef	__cplusplus
}
#endif

#endif	/* CASHLESS_H */


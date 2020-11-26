/* ************************************************************************** */
/** Descriptive File Name
 *
 *  Company    RASoftware
 *
 * \file parameters.h
 *
 * \brief Fichier entéte des paramétres.
 *
 ***************************************************************************** */
/* ************************************************************************** */

#ifndef _parameters_h    /* Guard against multiple inclusion */
#define _parameters_h


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <string.h>
#include <machine/types.h>
#include "peripheral/nvm/plib_nvm.h"
#include "driver/flash/drv_flash.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "dataCommun.h"
#include "MDB/mdb_cg.h"
#include "system_definitions.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/usart/processor/usart_p32mx575f512l.h"
#include "peripheral/reset/templates/reset_SoftwareResetTrigger_Default.h"
#include "driver/nvm/drv_nvm.h"
#include "peripheral/nvm/processor/nvm_p32mx575f512l.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * \defgroup parameters PARAMETRES
     * \brief Gestion des paramètres
     * @{
     */
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define NUM_PHONE 5

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Structure contenant l'habilitation des périphériques
     */
    typedef struct
    {
        uint16_t enable_GG; /*!<Habilitation des canaux du changeur.*/
        uint16_t enable_BV; /*!<Habilitation des canaux du lecteur de billets.*/
    } ENABLE;

    /**
     * \brief
     */
    //DRV_HANDLE hUartParameters;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief
     * @return 
     */
    uint32_t getSerialNumber(void);

    /**
     * \brief
     * @param byIndex
     * @param value
     */
    void setSecurityValue(uint8_t byIndex, uint32_t value);

    /**
     * \brief
     * @param byIndex
     * @return
     */
    uint32_t getSecurityValue(uint8_t byIndex);

    /**
     * \brief Requête de la température de lancement du chauffage.
     * @return Température de déclenchment du chauffage.
     */
    uint32_t getAlarmHeater(void);

    /**
     * \brief Requête de la température de lancement du groupe froid.
     * @return Température de déclemchement du groupe froid.
     */
    uint32_t getAlarmCold(void);

    /**
     * \brief Prix d'un produit.
     * @param num Numéro du produit -1
     * @return Prix du produit en centimes.
     */
    uint32_t getProductPrice(uint8_t num);

    /**
     * \brief Lit le delay de trop perçu.
     * @return Delai de trop percu.
     */
    uint32_t getDelayOverpay(void);

    /**
     * \brief Lit les activations des périphériques dans les paramètres.
     * @return Structure contenant les mots contenant les flags d'activations des\
     * périphériques.
     */
    ENABLE getEnableState();

    /**
     * \brief Requête du TO pour le cumul.
     * @return Un byte contenant le delai du time out en seconde;
     */
    uint8_t getTOCumul(void);

    /**
     * \brief Requête des canaux habilités.
     * @param isChangeGiver true pour le changer, false pour le lecteur de billet.
     * @return Un mot contenant le mask d'habilitation.
     */
    uint16_t getChannelEnable(bool isChangeGiver);

    /**
     * \brief
     * @param byIndex
     * @return 
     */
    bool getAlarmAuthorized(uint8_t byIndex);

    /**
     * \brief
     * @param byIndex
     * @return 
     */
    bool getAuditsAuthorized(uint8_t byIndex);

    /**
     * \brief Enregistre les paramétres dans la mémoire flash
     */
    void vParametersWrite(void);

    /**
     * \brief Lecture des paramétres.
     */
    void vParametersRead();

    /**
     * \brief Envoie les paramètres sur port micro USB.
     */
    void vParamSendToPC(void);

    /**
     * \brief Recoit les caractères du PC et les enregistre
     */
    void vParametersGetFromPC(void);

    /**
     * \brief
     * @param byIndex
     * @param isAudit
     * @return 
     */
    bool getIsCallEnable(BYTE byIndex, bool isAudit);

    /**
     * \brief
     * @param byIndex
     */
    void getPhoneNumber(BYTE byIndex, void* buffer);

    /**
     * @}
     */
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _parameters_h */

/* *****************************************************************************
 End of File
 */

/* ************************************************************************** */
/** Descriptive File Name
 * 
 *  Company    RASoftware
 * 
 * \file parameters.h
 * 
 * \brief Fichier entï¿½te des paramï¿½tres.
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
#include "peripheral/uart/plib_uart3.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "mainboard2.h"
#include "dataCommun.h"
#include "MDB/mdb_cg.h"


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

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
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
     * \brief Enregistre les paramï¿½tres dans la mï¿½moire flash
     */
    void vParametersWrite(void);

    /**
     * \brief Lecture des paramï¿½tres.
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

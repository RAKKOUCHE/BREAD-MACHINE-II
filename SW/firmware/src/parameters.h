/* ************************************************************************** */
/** Descriptive File Name
 * 
 *  Company    RASoftware
 * 
 * \file parameters.h
 * 
 * \brief Fichier ent�te des param�tres.
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
#include "peripheral/nvm/plib_nvm.h"
#include "peripheral/uart/plib_uart3.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "mainboard2.h"
#include "dataCommun.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * \defgroup parameters PARAMETRES
 * \brief Gestion des param�tres
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
     * \brief Requ�te du TO pour le cumul.
     * @return Un byte contenant le delai du time out en seconde;
     */
    uint8_t getTOCumul(void); 

    
    /**
     * \brief Requ�te des canaux habilit�s.
     * @param isChangeGiver true pour le changer, false pour le lecteur de billet.
     * @return Un mot contenant le mask d'habilitation.
     */
    uint16_t getChannelEnable(bool isChangeGiver);
    
    
    /**
     * \brief Enregistre les param�tres dans la m�moire flash
     */
    void vParametersWrite(void);
    
    /**
     * \brief Lecture des param�tres.
     */
    void vParametersRead();

    /**
     * \brief Envoie les param�tres sur port micro USB.
     */
    void vParamSendToPC(void);
    
    /**
     * \brief Recoit les caract�res du PC et les enregistre
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

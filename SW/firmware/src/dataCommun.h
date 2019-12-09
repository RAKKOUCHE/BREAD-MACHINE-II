/* ************************************************************************** */
/** Descriptive File Name
 * 
 * 
 * Company
 *      RASoftware  
 * \file datacommun.h
 * 
 * \brief Fichier entête superviseur des oonnées
 */
/* ************************************************************************** */

#ifndef _COMMUN_H_    /* Guard against multiple inclusion */
#define _COMMUN_H_


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

#include "definitions.h"
#include "driver/usart/drv_usart.h"
#include "timers.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * \defgroup dataRecord DATARECORD
     * \brief Module de communication avec le PC
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
     * \brief Enumération des états de la machine d'état de la communication.
     */
    typedef enum
    {
        STATE_PCCOMM_INIT, /*!<Initialisation du module.*/
        STATE_PCCOM_IDLE, /*!<Tâche en attente.*/
    } PCCOMM_STATE;

    /**
     * \brief Varialbe structure contenant les variables utilisées par le module.
     */
    struct
    {
        PCCOMM_STATE state; /*!<Etat de la tâche de communication avec le PC.*/
        TaskHandle_t handlePcCom; /*!<Handle de la tâche de communication avec le PC.*/
        TimerHandle_t hTimerTO_PC; /*!<Timer du TO de la communication.*/
        bool isTOReached; /*!<Flag indiquant que le TO est dépassé.*/
    } pcCom;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * \brief Initialise le module de communication avec le PC
     */
    void vDataInit(void);

    /**
     * @}
     */

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _COMMUN_H_ */

/* *****************************************************************************
 End of File
 */

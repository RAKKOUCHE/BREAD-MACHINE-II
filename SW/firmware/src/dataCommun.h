/* ************************************************************************** */
/** Descriptive File Name
 * 
 * 
 * Company
 *      RASoftware  
 * \file datacommun.h
 * 
 * \brief Fichier ent�te superviseur des oonn�es
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
     * \brief Enum�ration des �tats de la machine d'�tat de la communication.
     */
    typedef enum
    {
        STATE_PCCOMM_INIT, /*!<Initialisation du module.*/
        STATE_PCCOM_IDLE, /*!<T�che en attente.*/
    } PCCOMM_STATE;

    /**
     * \brief Varialbe structure contenant les variables utilis�es par le module.
     */
    struct
    {
        PCCOMM_STATE state; /*!<Etat de la t�che de communication avec le PC.*/
        TaskHandle_t handlePcCom; /*!<Handle de la t�che de communication avec le PC.*/
        TimerHandle_t hTimerTO_PC; /*!<Timer du TO de la communication.*/
        bool isTOReached; /*!<Flag indiquant que le TO est d�pass�.*/
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

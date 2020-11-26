/* 
 * File:   modemGSM.h
 * Author: Rachid AKKOUCHE
 *
 * Created on 30 mars 2016, 10:47
 */

#ifndef MODEMGSM_H
#define	MODEMGSM_H

#include <GenericTypeDefs.h>
#include "driver/usart/drv_usart_static.h"
#include "MDB/mdb.h"
#include "system_config.h"
#include "peripheral/usart/plib_usart.h"
#include "mdb/mdb_cg.h"
#include "audits.h"

/*Prototypes*******************************************************************/

/**
 * \brief
 * @return 
 */
QueueHandle_t getHandleQueueRead(void);

/**
 * \brief
 * @return 
 */
bool isGSMChecked(void);

/**
 * @fn vSendSMS
 * @brief Envoie un SMS
 * @param[in] msg
 */
void vSendSMS(const char *msg);

/**
 * \brief
 */
TaskHandle_t getGSMTaskHandle(void);

/**
 * \brief
 * @param canBeChecked
 */
void setIsGSMCanBeCecked(bool canBeChecked);


/**
 * @brief Envoie un SMS
 * @param[in] msg
 */
void vSendSMS(const char *msg);


/**
 * @brief Initialise les fonctions GSM.
 */
void vGSMInit(void);

/******************************************************************************/
#endif	/* MODEMGSM_H */


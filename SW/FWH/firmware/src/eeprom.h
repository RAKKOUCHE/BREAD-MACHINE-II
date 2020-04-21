/*
 * File:   eeprom.h
 * Author: Rachid AKKOUCHE
 *
 * Created on 26 mars 2016, 12:02
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "GenericTypeDefs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "communDef.h"
#include "peripheral/i2c/plib_i2c.h"
#include "peripheral/i2c/processor/i2c_p32mx575f512l.h"
#include "system_config.h"

    /*Defines******************************************************************/
    
    /**
     * \defgroup eeprom EEPROM
     * Gestion de l'eeprom I2C
     * @{
     */
    
#define EEPROM_DEVICE_ADDRESS 0XA0

    /*Enumérations*************************************************************/
    typedef enum
    {
        I2C_OK,
            I2C_NOT_IDLE,
            I2C_NAK,
            I2C_WR_FAULT,
            I2C_BUS_COLLISION,
    }
    I2C_BUS_STATE;

    /*Variables****************************************************************/

    /*Prototypes***************************************************************/
    /**
     * @brief Enregistre un tableau dans l'eeprom.
     * @param wADDRESS Adresse de début de l'enregistrement dans le tableau.
     * @param data Pointeur sur le tableau à enregistrer.
     * @param len Nombre d'octet à enregistrer.
     * @return Etat du bus après l'opération.
     */
    I2C_BUS_STATE EEpromWriteData(const WORD wADDRESS, void *data, const int len);
    /**************************************************************************/

    /**
     * @brief Enregistre une donnée dans l'eeprom.
     * @param wAddress Adresse à laquelle sera enregistrée la donnée.
     * @param byData Donnée à enregistrér.
     * @return Etat du bus après l'opération.
     */
    I2C_BUS_STATE EEpromWriteByte(WORD wAddress, BYTE byData);

    /**************************************************************************/

    /**
     * @brief Lit un tableau de données dans l'eeprom.
     * @param wAddress Adresse de début dans l'eeprom du tableau
     * @param data Pointeur sur le tableau dans lequel seront enregistrées les données lues.
     * @param length Nombre d'octet à lire.
     * @return Etat du bus après l'opération.
     */
    I2C_BUS_STATE EEPromReadData(WORD wAddress, void *data, int length);

    /**************************************************************************/
    /**
     * \brief
     */
    void vEEpromInit(void);

    /**
     * @}
     */
    
#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */


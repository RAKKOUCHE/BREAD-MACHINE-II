/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file hd44780.c
 * 
 * \brief Fichier source de la gestion de la sonde température DS18B20
 * 
 * \details Ce fichier fournit les fonctions et les définitions utilisés par le
 * programme pour gestion de la sonde température DS18B20.
 *  
 ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "DS18B20.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/**
 * \brief Nom en clair de la tâche de gestion de la sonde de température DS18B20.
 */
#define DS18B20_TASK_NAME "TEMP TSK"

/**
 * \brief Priority de la tâche de gestion de la sonde de température DS18B20.
 */
#define DS18B20_TASK_PRIORITY 1

/**
 * \brief Profondeur de la pile de la gestion de la sonde de température DS18B20.
 */
#define DS18B20_TASK_STACK 512

/**
 * \brief Delay entre 2 vérifications de la sonde.
 */
#ifdef __DEBUG
#define DS18B20_TASK_DELAY (60 * SECONDE)
#else
#define DS18B20_TASK_DELAY (60 * SECONDE)

#endif
/**
 * \brief Configuration 9 bits
 */
#define RESOLUTION9 0B00000000

/**
 * \brief Configuration 10 bits
 */
#define RESOLUTION10 0B00100000

/**
 * \brief Configuration 11 bits
 */
#define RESOLUTION11 0B01000000

/**
 * \brief Configuration 12 bits
 */
#define RESOLUTION12 0B01100000

/* ************************************************************************** */

/**
 * \brief Enumération des commandes du ds18b20
 */
typedef enum
{
    READ_ROM = 0X33, /*!<Lecture du code unique.*/
    MATCH_ROM = 0X33, /*!<Adressage du composants.*/
    SKIP_ROM = 0XCC, /*!<Broadcast des commandes.*/
    ALARM_SEARCH = 0XEC, /*!<Recherche une alarme.*/
    CONVERT_T = 0X44, /*!<Demande conversion.*/
    WRITE_SCRATCHPAD = 0X4E, /*!<Enregistre les alarmes et la configuration.*/
    READ_SCRATCHPAD = 0XBE, /*!<Lit les données des registres.*/
    COPY_SCRATCHPAD = 0X48, /*!<Enregistre les alarmes et la configuration dans 
                             * l'eeprom du DS18B20.*/
    RECALL_E2 = 0XB8, /*!<Relit les alarmes et la configuration dans l'eeprom.*/
    READ_PSU = 0XB4, /*!<Lit le type d'alimentation du DS18B20.*/
} COMMANDES;

/**
 * \brief Structure contenant la mémoire du ds18b20.
 */
typedef struct
{
    uint8_t Temp_LSB; /*!<Partie basse de la température.*/
    uint8_t Temp_MSB; /*!<Partie haute de la température.*/
    uint8_t Temp_HI; /*!<Température haute alarme.*/
    uint8_t Temp_LO; /*!<Température basse alarme.*/
    uint8_t Config; /*!<Registre de configuration.*/
    uint8_t Reserved1; /*!<NU.*/
    uint8_t Reserved2; /*!<NU.*/
    uint8_t Reserved3; /*!<NU.*/
    uint8_t CRC; /*!<CRC.*/
} SCRATCHPAD;

/**
 * \brief Structure contenant les variables utilisées par le module DS18B20
 */
struct
{

    union
    {
        SCRATCHPAD scratchpad; /*!<Registre du DS1B20.*/
        uint8_t byScratchpad[sizeof(SCRATCHPAD)]; /*!<Buffer contenant les DS1B20.*/
    };
    uint8_t laserCode[8]; /*!<lASER code unique du DS18B20.*/
    double Temperature;
    TaskHandle_t hDS18B20; /*!<Handle de la tâche.*/
} ds18b20;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         static bool vReset(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static bool vOneWireReset(void)
{
    uint8_t byIndex;
    DQ_OutputEnable();
    DQ_Clear();
    Delay10us(48);
    DQ_InputEnable();
    while(!DQ_Get());
    while(DQ_Get());
    for(byIndex = 0; byIndex < 4; byIndex++)
    {
        Delay10us(1);
        if(DQ_Get())
        {
            return false;
        }
    }
    Delay10us(20);
    if(!DQ_Get())
    {
        return false;
    }
    Delay10us(25);
    return true;
}

/*********************************************************************
 * Function:        
 *         static uint8_t OneWireReadByte()
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static uint8_t OneWireReadByte()
{
    uint8_t byIndex, data = 0;

    for(byIndex = 0; byIndex < 8; byIndex++)
    {
        DQ_OutputEnable();
        DQ_Clear();
        Delay10us(1);
        DQ_InputEnable();
        Delay10us(1);
        data += (DQ_Get() & 1) << byIndex;
        Delay10us(4);
    }
    return data;
}

/*********************************************************************
 * Function:        
 *         static void OneWireWriteByte(uint8_t data)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void OneWireWriteByte(uint8_t data)
{
    uint8_t byIndex;
    for(byIndex = 0; byIndex < 8; byIndex++)
    {
        DQ_OutputEnable();
        DQ_Clear();
        Delay10us(1);
        if((data >> byIndex) & 0x01)
        {
            DQ_InputEnable();
        }
        Delay10us(5);
        DQ_InputEnable();
        Delay10us(1);
    }
    Delay10us(1);
}

/*********************************************************************
 * Function:        
 *         static byte CRC(uint* byffer, uint8_t lenght)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
uint8_t dsCRC8(const uint8_t *addr, uint8_t len)
{
    uint8_t crc = 0;
    uint8_t i;
    while(len--)
    {
        uint8_t inbyte = *addr++;
        for(i = 8; i; i--)
        {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if(mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}

/*********************************************************************
 * Function:        
 *         static void sendCommand(COMMANDES commande)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void sendCommand(COMMANDES commande)
{
    OneWireWriteByte(commande);
}

/*********************************************************************
 * Function:        
 *         static void ReadROM(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static bool isOneWireReadROM(void)
{
    bool isResult = false;
    uint8_t byIndex;
    if(vOneWireReset())
    {
        sendCommand(READ_ROM);

        for(byIndex = 0; byIndex < 8; byIndex++)
        {
            ds18b20.laserCode[byIndex] = OneWireReadByte();
        }
        isResult = (ds18b20.laserCode[7] == dsCRC8(ds18b20.laserCode, 7));
    }
    return isResult;
}

/*********************************************************************
 * Function:        
 *         static void ds18b20ReadScratchPad()
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static bool ds18b20ReadScratchPad()
{
    uint8_t byIndex;
    bool isResult = false;
    if(vOneWireReset())
    {
        sendCommand(SKIP_ROM);
        sendCommand(READ_SCRATCHPAD);
        for(byIndex = 0; byIndex < 9; byIndex++)
        {
            ds18b20.byScratchpad[byIndex] = OneWireReadByte();
        }
        isResult = ds18b20.byScratchpad[8] == dsCRC8(ds18b20.byScratchpad, 8);
    }
    return isResult;
}

/*********************************************************************
 * Function:        
 *         static void converT(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void converT(void)
{
    if(vOneWireReset())
    {
        sendCommand(SKIP_ROM);
        sendCommand(CONVERT_T);
        delayMs(750);
    }
}

/*********************************************************************
 * Function:        
 *         static double getds18b20Temp(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static double getds18b20Temp()
{
    uint8_t byIndex;
    double data;

    double result = 0;
    converT();
    if(ds18b20ReadScratchPad())
    {
        data = 0.0625;
        for(byIndex = 0; byIndex < 8; byIndex++)
        {

            result += ((ds18b20.scratchpad.Temp_LSB >> byIndex) & 0x01) * data;
            data *= 2;
        }
        for(byIndex = 0; byIndex < 3; byIndex++)
        {
            result += ((ds18b20.scratchpad.Temp_MSB >> byIndex) & 0x01) * data;
            data *= 2;
        }
    }
    return result;
}

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         static void vTaskTemperature(void *vParameters)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
static void vTaskTemperature(void *vParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        if((ds18b20.Temperature = getds18b20Temp()))
        {
            if(ds18b20.Temperature > ((double) getAlarmHeater() + 0.25))
            {
                COLD_Set();
            }
            if(ds18b20.Temperature < ((double) getAlarmHeater() - 0.25))
            {
                COLD_Clear();
            }
            if(ds18b20.Temperature > ((double) getAlarmCold() + 0.25))
            {
                HEATER_Clear();
            }
            if(ds18b20.Temperature < ((double) getAlarmCold() - 0.25))
            {
                HEATER_Set();
            }
        }
        vTaskDelayUntil(&xLastWakeTime, DS18B20_TASK_DELAY);
    }
}
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         double getTemp(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
double getTemp(void)
{
    return ds18b20.Temperature;
}

/*********************************************************************
 * Function:        
 *         void vDS18B20Init(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         YY/MM/DD
 *
 * Summary:
 *         RECAPULATIF
 * 
 * Description:
 *         DESCRIPTION
 *
 * PreCondition:    
 *         None
 *
 * Input:     
 *         None
 *
 * Output:
 *         None
 *
 * Returns:
 *         None
 *
 * Side Effects:
 *         None
 * 
 * Example:
 *         <code>
 *         FUNC_NAME(FUNC_PARAM)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vDS18B20Init(void)
{
    if(ds18b20.hDS18B20 == NULL)
    {
        HEATER_Clear();
        COLD_Clear();
        xTaskCreate((TaskFunction_t)vTaskTemperature, DS18B20_TASK_NAME, DS18B20_TASK_STACK,
                    NULL, DS18B20_TASK_PRIORITY, &ds18b20.hDS18B20);
    }
}

/* *****************************************************************************
 End of File
 */

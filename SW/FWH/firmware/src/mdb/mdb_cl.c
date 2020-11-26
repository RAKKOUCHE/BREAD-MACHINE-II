/*******************************************************************************
 * \file            cashless.c
 * \brief			Source de la gestion du cashless
 * \version         1.0
 * \date            2019 05 25
 * \author          Rachid AKKOUCHE
 ******************************************************************************/

#include "MDB_CL.h"

static bool isEnablePeripherique(void)
{
    uint8_t byAcknowledge;
    uint8_t byBuff = 0X01;
    return((byMDBSendCommand(ADDRESS_CL, CL_READER, 1, &byBuff,
                             &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/********************************************************************/

/*********************************************************************
 * Function:        static bool isCLEnableOptions()
 *
 * Version:         
 *                  1.0
 * 
 * Date:            
 *                  2019.06.11
 * 
 * Author:          
 *                  Rachid AKKOUCHE  
 * 
 * Summary:         
 *                  Cette fonction active le lecteur cashless
 *
 * PreCondition:    
 *                  None                 
 *
 * Input:           
 *                  None                 
 *                  
 * Output:          
 *                  None                 
 * 
 * Returns          
 *                  True si l'opération s'est excutée correctement.                 
 *
 * Side Effects:    
 *                  None                 
 *
 * Note:            
 *                  None                 
 * 
 * Example:
 *                  <code>
 *                  code            
 *                  </code>
 * 
 ********************************************************************/
static bool isCLEnableOptions()

{
    uint8_t byBuff[4] = {0};
    uint8_t byAcknowledge;
    return((byMDBSendCommand(ADDRESS_CL, CL_EXPANSION, 4, byBuff,
                             &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/*******************************************************************/

/*********************************************************************
 * Function:        static uint8_t isRequestExpansionID(uint8_t byDeviceAddress, DEVICEID *deviceId)
 *
 * Version:         
 *                  1.0
 * 
 * Date:            
 *                  2019.06.11
 * 
 * Author:          
 *                  Rachid AKKOUCHE  
 * 
 * Summary:         
 *                  Cette fonction envoie l'identification de la VMC au périphérique qui retournera son identification.
 *
 * PreCondition:    
 *                  None                 
 *
 * Input:           
 *                  byDeviceAddress L'adresse du périphérique.                 
 *                  
 * Output:          
 *                   L'identification du périphérique.                
 * 
 * Returns          
 *                  La longueur de la réponse.                 
 *
 * Side Effects:    
 *                  Transfert la réponse dans le buffer d'identification du périphérique.                 
 *
 * Note:            
 *                  None                 
 * 
 * Example:
 *                  <code>
 *                  code            
 *                  </code>
 * 
 ********************************************************************/
static uint8_t isRequestExpansionID(uint8_t byDeviceAddress, DEVICEID *deviceId)

{
    uint8_t ptrAnswer[(sizeof(PERIPHERALID)) + 1] = {0};
    uint8_t byResult = byMDBSendCommand(byDeviceAddress, CL_EXPANSION,
                                        sizeof(DEVICEID), deviceId, ptrAnswer);
    memmove(&cashLessReader.peripheralID, &ptrAnswer,
            cashLessReader.readerConfig.deviceConfig.byLevel > 2 ? sizeof(PERIPHERALID) :
            sizeof(PERIPHERALID) - 2);
    return(byResult);
}

/*******************************************************************/

/*********************************************************************
 * Function:        static bool isSetupPriceMinMax(const uint8_t byDeviceAddress, VMCMaxMin *parameters)
 *
 * Version:         
 *                  1.0
 * 
 * Date:            
 *                  2019.06.10
 * 
 * Author:          
 *                  Rachid AKKOUCHE  
 * 
 * Summary:         
 *                  Cette fonction envoie kes informations concernant les prix
 *                  minimum et maxi au cashLess
 *
 * PreCondition:    
 *                  None                 
 *
 * Input:           
 *                  byDeviceAddress Adresse du périphérique.
 *                  parameters Pointeur sur le buffer des datas                 
 *                  
 * Output:          
 *                  None                 
 * 
 * Returns          
 *                  true si l'opération se déroule correctement.                 
 *
 * Side Effects:    
 *                  None                 
 *
 * Note:            
 *                  None                 
 * 
 * Example:
 *                  <code>
 *                  code            
 *                  </code>
 * 
 ********************************************************************/
static bool isSetupPriceMinMax(const uint8_t byDeviceAddress, VMCMAXMIN *parameters)
{
    uint8_t byAcknowledge;
    uint8_t byBuff[11] = {CL_MAXMINPRICE};
    if(cashLessReader.readerConfig.deviceConfig.byLevel > 2)
    {
        memmove(&byBuff[1], &cashLessReader.vmcMaxMin.MinMaxLevel2, 4);
    }
    else
    {
        memmove(&byBuff[1], &cashLessReader.vmcMaxMin.MinMaxLevel2, 10);
    }
    return((byMDBSendCommand(byDeviceAddress, CL_SETUP, cashLessReader.readerConfig.deviceConfig.byLevel > 2 ? 11 : 5,
                             byBuff, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}
/********************************************************************/

/*********************************************************************
 * Function:        static uint8_t CLSetupConfigData(const uint8_t byDeviceAddress, VMCCONFIG *ptrParameters)
 *
 * Version:         
 *                  1.0
 * 
 * Date:            
 *                  2019.06.10
 * 
 * Author:          
 *                  Rachid AKKOUCHE  
 * 
 * Summary:         
 *                  Cette fonction envoie une requête concernant la configuraton du cashLess.       
 *
 * PreCondition:    
 *                  None                 
 *
 * Input:           
 *                  byDeviceAddress Adresse du périphérique.                 
 *                  
 * Output:          
 *                  Certains périphériques retourne la configuration directement, d'autres au prochain polling.                 
 * 
 * Returns          
 *                  La longueur de la réponse.                 
 *
 * Side Effects:    
 *                  Peut remplir le buffer de configuration du périphérique.                 
 *
 * Note:            
 *                  Voir output                 
 * 
 * Example:
 *                  <code>
 *                  code            
 *                  </code>
 * 
 ********************************************************************/
static uint8_t CLSetupConfigData(const uint8_t byDeviceAddress, VMCCONFIG *ptrParameters)
{
    uint8_t ptrAnswer[sizeof(READERCONFIG) + 1] = {0};
    uint8_t byResult = byMDBSendCommand(byDeviceAddress, CL_SETUP, sizeof(VMCCONFIG), ptrParameters, ptrAnswer);
    if(((byResult == 1) && (ptrAnswer[0] != ACK)) || ((byResult != 1) && (byResult != (sizeof(READERCONFIG)) + 2)))
    {
        byResult = 0;
    }
    if(byResult > 1)
    {
        memmove(&cashLessReader.readerConfig, &ptrAnswer[1], sizeof(READERCONFIG));
    }
    return byResult;
}
/********************************************************************/

/*********************************************************************
 * Function:        
 *         void vInitCashLess(void) 
 * 
 * Version:
 *          1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/05/26
 *
 * Summary:
 *         Initialisation du module cashless
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
void vInitCashLess(void)
{
    uint8_t MANUFACTURER[] = "RAS";

    cashLessReader.state = CL_STATE_BEGIN;
    cashLessReader.isPolled = false;
    cashLessReader.byIndex = cashLessReader.byLen = 0;
    cashLessReader.VMCConfig.byCmd = CL_CONFIGREQUEST;
    cashLessReader.VMCConfig.byLevel = 0X02;
    cashLessReader.VMCConfig.byDisplayColumns = 0x00;
    cashLessReader.VMCConfig.byDisplayRows = 0x00;
    cashLessReader.VMCConfig.byDisplayInfo = 0x08;
    memmove(cashLessReader.vmcID.ManufactureID, MANUFACTURER, 3);
    memset(cashLessReader.vmcID.byModelNumber, 0x30, 12);
    memset(cashLessReader.vmcID.bySerialNumber, 0x30, 12);
    cashLessReader.vmcID.byFW_Rev[0] = 0X01;
    cashLessReader.vmcID.byFW_Rev[1] = 0X00;
}
/*******************************************************************/

/*********************************************************************
 * Function:        
 *         void vTaskCashLess(void) 
 * 
 * Version :
 *          1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/05/26
 *
 * Summary:
 *         Tâche du module cashless
 * 
 * Description:
 *         
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
 *         vTaskCashLess(void)
 *         <code>
 * 
 * Remarks:
 *         None
 *         
 ********************************************************************/
void vTaskCashLess(void)
{
    switch(cashLessReader.state)
    {
            cashLessReader.isPolled = true;
        case CL_STATE_BEGIN:
            // <editor-fold desc="CL_STATE_BEGIN"> 
        {
            cashLessReader.iBeforeRetry = 0;
            cashLessReader.state = CL_STATE_RETRY;
            cashLessReader.isInitialized = false;
            break;
        }// </editor-fold>
        case CL_STATE_RETRY:
            // <editor-fold desc="CL_STATE_RETRY"> 
        {
            if(!cashLessReader.iBeforeRetry--)
            {
                cashLessReader.byTryReset = 2;
                cashLessReader.state = CL_STATE_RESET;
            }
            break;
        }// </editor-fold>
        case CL_STATE_RESET:
            // <editor-fold desc="CL_STATE_RESET"> 
        {
            if(--cashLessReader.byTryReset)
            {
                if(isMDBReset(ADDRESS_CL))
                {
                    cashLessReader.state = CL_STATE_POLL;
                }
            }
            else
            {
                cashLessReader.state = CL_STATE_RETRY;
            }
            break;
        }// </editor-fold>
        case CL_STATE_POLL:
            // <editor-fold desc="CL_STATE_POLL"> 
        {
            if(!cashLessReader.byIndex)
            {
               isMDBPoll(ADDRESS_CL, &cashLessReader.byLen , answerBuffer);
            }
            if(cashLessReader.byIndex < (cashLessReader.byLen - 1))
            {
                switch(answerBuffer[cashLessReader.byIndex])
                {
                    case CL_JUSTRESET:
                        // <editor-fold desc="CL_JUSTRESET">
                    {
                        cashLessReader.state = CL_CONFIGDATA;
                        break;
                    }// </editor-fold>
                    default:
                    {
                        cashLessReader. byIndex++;
                        break;
                    }
                }
            }
            else
            {
                cashLessReader.byIndex = 0;
            }
            break;
        }// </editor-fold>
        case CL_STATE_SETUP_CONFIG_DATA:
            // <editor-fold desc="CL_STATE_SETUP_CONFIG_DATA">
        {
            cashLessReader.state = cashLessReader.isInitialized ? CL_STATE_POLL : CL_STATE_SETUP_MAX_MIN_PRICE;
            CLSetupConfigData(ADDRESS_CL, &cashLessReader.VMCConfig);
            if(cashLessReader.readerConfig.deviceConfig.byLevel > 2)
            {
                cashLessReader.vmcMaxMin.MinMaxLevel3.dwMax = 5000;
                cashLessReader.vmcMaxMin.MinMaxLevel3.dwMin = 0;
                cashLessReader.vmcMaxMin.MinMaxLevel3.countryCode[0] = 19;
                cashLessReader.vmcMaxMin.MinMaxLevel3.countryCode[1] = 78;
            }
            else
            {
                cashLessReader.vmcMaxMin.MinMaxLevel2.wMax = 5000;
                cashLessReader.vmcMaxMin.MinMaxLevel2.wMin = 0;
            }
            break;
        }// </editor-fold>
        case CL_STATE_SETUP_MAX_MIN_PRICE:
            // <editor-fold desc="CL_STATE_SETUP_MAX_MIN_PRICE">
        {
            cashLessReader.state = cashLessReader.isInitialized ? CL_STATE_POLL : CL_STATE_EXPANSION_REQUEST_ID;
            isSetupPriceMinMax(ADDRESS_CL, &cashLessReader.vmcMaxMin);
            break;
        }// </editor-fold>
        case CL_STATE_EXPANSION_REQUEST_ID:
            // <editor-fold desc="CL_STATE_EXPANSION_REQUEST_ID">
        {
            cashLessReader.state = cashLessReader.isInitialized ? CL_STATE_POLL : CL_STATE_ENABLE_OPTION;
            if(cashLessReader.readerConfig.deviceConfig.byLevel > 2)
            {
                isRequestExpansionID(ADDRESS_CL, &cashLessReader.vmcID);
            }
            break;
        }// </editor-fold>
        case CL_STATE_ENABLE_OPTION:
            // <editor-fold desc="CL_STATE_ENABLE_OPTION">
        {
            cashLessReader.state = cashLessReader.isInitialized ? CL_STATE_POLL : CL_STATE_ENABLE_OPTION;
            if(cashLessReader.readerConfig.deviceConfig.byLevel > 2)
            {
                isCLEnableOptions();
            }
            break;
        }// </editor-fold>
        case CL_STATE_ENABLE_PERIPH:
            // <editor-fold desc="CL_STATE_ENABLE_PERIPH">
        {
            cashLessReader.state = (cashLessReader.isInitialized = isEnablePeripherique()) ?
                CL_STATE_POLL : CL_STATE_RETRY;
            break;
        }// </editor-fold>
        default:
        {
            break;
        }
    }
}
/***********************************************************************/

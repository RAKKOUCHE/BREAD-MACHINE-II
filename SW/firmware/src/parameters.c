/* ************************************************************************** */


/** Descriptive File Name
 * 
 * 
 * Company
 *      RASoftware  
 * \file parameters.c
 * 
 * \brief Source des paramètres
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "parameters.h"

/**
 * \addtogroup parameters
 * @{
 */
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/**
 * \brief Taille des lignes.
 */
#define NVM_FLASH_ROWSIZE          (512U)

/**
 * brief Taille des pages
 */
#define NVM_FLASH_PAGESIZE         (4096U)

/**
 * \brief Adresse des donées en flash
 */
#define NVM_MEDIA_START_ADDRESS 0X9D070000

/**
 * \brief Structure contenant les informations sur un numéro de téléphone
 */
typedef struct
{
    unsigned int phone[13]; /*!<Numéro de téléphone en sur 12 chiffres.*/
    unsigned int isAuditInform; /*!<La consultation des audits est autorisée sur ce ab
                         * numéro*/
    unsigned int isAlarmed; /*!<Ce numéro sera informé de l'activité de la 
                               * machine.*/
} PHONES;

/**
 * \brief type structure contenant les paramètres.
 */
typedef struct
{
    uint32_t id; /*!<Identification de la machine.*/
    uint32_t prices[3]; /*!<Prix des produits en cash.*/
    uint32_t pricesCL[3]; /*!<Prix des produits en cashless.*/
    PHONES phones[6]; /*!<Numéro et activation des numéros de t'léphones.*/
    uint32_t sensitivity[3]; /*!<Sensitivité de la sécurité des trappes.*/
    uint32_t TOcumul; /*!<Délai maximum accordé pour réinsérer une autre pièce.*/
    uint32_t TOOverpay; /*!<Délai maximum de maintien du trop perçu*/

    union
    {
        ENABLE enables;
        uint32_t u32Enables;
    };
    int32_t cooler; /*!<Températeur de déclenchement du refroidissement.*/
    int32_t heater; /*!<Températirue de déclenchement du chauffage.*/
} PARAMETERS;

/**
 * \brief Variable contant les apram
 */
static union
{
    uint32_t buffer[sizeof(PARAMETERS) / sizeof(uint32_t)]; /*!<Buffer des paramètres.*/
    PARAMETERS data; /*!<Paramètres de la machine.*/
} parameters;

/**
 * \brief constante en flash contenant les paramètres sauvegardés.
 */
const unsigned int __attribute__((space(prog),
                                  address(NVM_MEDIA_START_ADDRESS))) gNVMFlashReserveArea[NVM_FLASH_PAGESIZE / sizeof(uint32_t)]
= {
   1,
   100, 100, 100,
   100, 100, 100,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X31, 0, 0,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X32, 0, 0,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X33, 0, 0,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X34, 0, 0,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X35, 0, 0,
   0X30, 0X30, 0X33, 0X33, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X36, 0, 0,
   0, 0, 0,
   30, 60,
   983103, //Activation par défaut des moyens de paiement 0X001F001F 
   22, 18,
};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */

/* ************************************************************************** */

/*********************************************************************
 * Function:        
 *         uint32 getProductPrice(uint8_t num)
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
uint32_t getProductPrice(uint8_t num)
{
    return parameters.data.prices[num];
}

/*********************************************************************
 * Function:        
 *         uint8_t getDelayOverpay(void)
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
uint32_t getDelayOverpay(void)
{
    return parameters.data.TOOverpay;
}

/*********************************************************************
 * Function:        
 *         ENABLE getEnableState()
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
ENABLE getEnableState()
{
    return parameters.data.enables;
}

/*********************************************************************
 * Function:        
 *         uint8_t getTOCumul(void)
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
uint8_t getTOCumul(void)
{
    return(uint8_t) parameters.data.TOcumul;
}

/*********************************************************************
 * Function:        
 *         uint16_t getChannelEnable(bool isChangeGiver)
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
uint16_t getChannelEnable(bool isChangeGiver)
{
    return isChangeGiver ? parameters.data.enables.enable_GG :
            parameters.data.enables.enable_BV;
}

/*********************************************************************
 * Function:        
 *         void vParametreWrite(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/12
 *
 * Summary:
 *         Enregistre les paramètres en flash.
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
void vParametersWrite(void)
{
    NVM_PageErase(NVM_MEDIA_START_ADDRESS);
    while(NVM_IsBusy());
    NVM_RowWrite(parameters.buffer, NVM_MEDIA_START_ADDRESS);
    while(NVM_IsBusy());    
}

/*********************************************************************
 * Function:        
 *         void vParametersRead(void)
 * 
 * Version:
 *         1.0
 * 
 * Author:
 *         Rachid AKKOUCHE
 * 
 * Date:
 *         19/11/12
 *
 * Summary:
 *         Lit les paramètres en flash
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
void vParametersRead(void)
{
    memmove(&parameters, &gNVMFlashReserveArea, sizeof(parameters));
}

/*********************************************************************
 * Function:        
 *         void vParamSendToPC(void)
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
void vParamSendToPC(void)
{

    union
    {
        uint32_t value;
        uint8_t buffer[sizeof(uint32_t)];
    } values;
    uint8_t byChannel;
    while(!UART3_TransmitterIsReady());
    UART3_WriteByte(6);
    while(!UART3_TransmitComplete());
    UART3_Write(VERSION, 6);
    while(!UART3_TransmitComplete());
    UART3_WriteByte(11);
    while(!UART3_TransmitComplete());
    UART3_Write(__DATE__, 11);
    while(!UART3_TransmitComplete());

    uint32_t dwParameterSize = sizeof(PARAMETERS);
    UART3_Write(&dwParameterSize, sizeof(dwParameterSize));
    while(!UART3_TransmitComplete());

    UART3_Write(&parameters.data, sizeof(PARAMETERS));
    while(!UART3_TransmitComplete());
    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        values.value = changeGiver.config.byCoinValue[byChannel] * changeGiver.config.byScalingFactor;
        UART3_Write(values.buffer, sizeof(uint32_t));
        while(!UART3_TransmitComplete());
    }
    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        values.value = billValidator.config.byBillValue[byChannel] * billValidator.config.wScalingFactor;
        UART3_Write(values.buffer, sizeof(uint32_t));
        while(!UART3_TransmitComplete());
    }
}

/*********************************************************************
 * Function:        
 *         void vParametersGetFromPC(void)
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
void vParametersGetFromPC(void)
{
    //TODO placer un timer et effectuer les vérifications
    UART3_WriteByte(0X5A);
    while(!UART3_TransmitComplete());
//    pcCom.isTOReached = false;
    xTimerStart(pcCom.hTimerTO_PC, 1000);
    while(!UART3_ReceiverIsReady());// && !pcCom.isTOReached);
//    if(!pcCom.isTOReached)
    {
        if(UART3_Read(&parameters.data, sizeof(PARAMETERS)))
        {
            while(!UART3_TransmitComplete());
            changeGiver.coins_enable.coinEnable.wCoinEnable = parameters.data.enables.enable_GG;
            isSetCoinEnable(true, &changeGiver.coins_enable);
            billValidator.byBillType.wBillEnable = parameters.data.enables.enable_BV;
            isSetBillEnable(true, &billValidator.byBillType);            
            vParametersWrite();
        }
        vParametersRead();
    }
    //vParamSendToPC();
}

/**
 * @}
 */
/* *****************************************************************************
End of File
 */

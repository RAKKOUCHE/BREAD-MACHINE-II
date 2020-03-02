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
#include "peripheral/usart/plib_usart.h"
#include "driver/usart/drv_usart_definitions.h"

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
        ENABLE enables; /*!<Habilitation des canaux.*/
        uint32_t u32Enables;
    };
    int32_t heater; /*!<Températirue de déclenchement du chauffage.*/
    int32_t cooler; /*!<Températeur de déclenchement du refroidissement.*/
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
 *         uint32_t getAlarmHeater(void)
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
uint32_t getAlarmHeater(void)
{
    return parameters.data.heater;
}

/*********************************************************************
 * Function:
 *         uint32_t getAlarmCold(void)
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
uint32_t getAlarmCold(void)
{
    return parameters.data.cooler;
}

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
    uint32_t buffer[DRV_FLASH_PAGE_SIZE / sizeof(uint32_t)] = {0};
    uint8_t byIndex;
    DRV_FLASH_ErasePage(flash.handle, DRV_NVM_MEDIA_START_ADDRESS);
    vTaskSuspendAll();
    while(DRV_FLASH_IsBusy());
    DRV_FLASH_WriteRow(flash.handle, DRV_NVM_MEDIA_START_ADDRESS, buffer);
    while(DRV_FLASH_IsBusy());
    //
    //
    //    for(byIndex = 0; byIndex < PRODUCTS_NUMBER; byIndex++)
    //    {
    //        buffer[byIndex] = sProducts.product[byIndex].i32Prix;
    //    }
    //
    //    DRV_FLASH_WriteRow(flash.handle, DRV_NVM_MEDIA_START_ADDRESS, buffer);
    //    while(DRV_FLASH_IsBusy(flash.handle));
    //    xTaskResumeAll();
    //
    //
    //
    //    NVM_PageErase(NVM_MEDIA_START_ADDRESS);
    //    while(NVM_IsBusy());
    //    NVM_RowWrite(parameters.buffer, NVM_MEDIA_START_ADDRESS);
    //    while(NVM_IsBusy());
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
    hUartParameters = DRV_USART_Open(sysObj.drvUsart2, DRV_IO_INTENT_READWRITE);
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
    unsigned int total;
    uint32_t dwParameterSize = sizeof(PARAMETERS);

    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 6);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    total = 0;
    do
    {
        total += DRV_USART_Write(hUartParameters, VERSION, 6);
    } while(total < 6);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 11);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    total = 0;
    do
    {
        total += DRV_USART_Write(hUartParameters, __DATE__, 11);
    } while(total < 11);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    total = 0;
    do
    {
        total += DRV_USART_Write(hUartParameters, &dwParameterSize, sizeof(dwParameterSize));
    } while(total < sizeof(dwParameterSize));
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    total = 0;
    do
    {
        total += DRV_USART_Write(hUartParameters, &parameters.data, dwParameterSize);
    } while(total < dwParameterSize);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        values.value = getCoinValue(byChannel);
        total = 0;
        do
        {
            total += DRV_USART_Write(hUartParameters, values.buffer, sizeof(uint32_t));
        } while(total < sizeof(uint32_t));
        while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    }
    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        values.value = getBillValue(byChannel);
        total = 0;
        do
        {
            total += DRV_USART_Write(hUartParameters, values.buffer, sizeof(uint32_t));
        } while(total < sizeof(uint32_t));
        while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
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
    unsigned int total = 0;
    BILL_TYPE billType;
    COIN_TYPE coinType;
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 0X5A);
    xTimerStart(pcCom.hTimerTO_PC, 1000);
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_TRANSMIT_EMPTY));
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_RECEIVER_EMPTY));
    do
    {
        total += DRV_USART_Read(hUartParameters, &parameters.data, sizeof(PARAMETERS));
    } while(total < sizeof(PARAMETERS));
    while(!(DRV_USART_TransferStatus(hUartParameters) & DRV_USART_TRANSFER_STATUS_RECEIVER_EMPTY));
    xTimerStop(pcCom.hTimerTO_PC, 1000);
    setCoinEnableMask(parameters.data.enables.enable_GG);

    setCoinEnableMask(parameters.data.enables.enable_GG);
    coinType = getCoinType();
    isSetCoinEnable(true, &coinType);
    setBillEnableMask(parameters.data.enables.enable_BV);
    billType = getBillType();
    isSetBillEnable(true, &billType); // &billValidator.byBillType);
    vParametersWrite();
    delayMs(100);
    vParametersRead();
}

/**
 * @}
 */
/* *****************************************************************************
End of File
 */

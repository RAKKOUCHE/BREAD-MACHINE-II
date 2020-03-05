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
#include "driver/nvm/drv_nvm.h"
#include "peripheral/nvm/processor/nvm_p32mx575f512l.h"
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
    uint32_t dwBuffer[sizeof(PARAMETERS) / sizeof(uint32_t)]; /*!<Buffer des paramètres.*/
    uint8_t buffer[sizeof(PARAMETERS)]; /*!<Buffer des paramètres.*/
    PARAMETERS data; /*!<Paramètres de la machine.*/
} parameters, backToto;

/**
 * \brief constante en flash contenant les paramètres sauvegardés.
 */
const uint32_t __attribute__((space(prog), address(NVM_MEDIA_START_ADDRESS))) gNVMFlashReserveArea[NVM_FLASH_PAGESIZE / sizeof(uint32_t)]
= {
   1,
   100, 100, 100,
   100, 100, 100,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 3, 3, 6, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0,
   0, 0, 0,
   30, 60,
   983103, //Activation par défaut des moyens de paiement 0X001F001F
   22, 18,
   0, 0,
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
    uint8_t byIndex;
    //    uint32_t buffer[DRV_FLASH_PAGE_SIZE / sizeof(uint32_t)] = {0};
    //
    //    memmove(buffer, parameters.buffer, sizeof(parameters));


    vTaskSuspendAll();
    DRV_FLASH0_ErasePage(DRV_NVM_MEDIA_START_ADDRESS);
    while(DRV_FLASH0_IsBusy());
    DRV_FLASH0_WriteRow(DRV_NVM_MEDIA_START_ADDRESS, parameters.dwBuffer);
    while(DRV_FLASH0_IsBusy());
    //
    //    DRV_HANDLE NVMHandle = DRV_NVM_Open(NVM_ID_0, DRV_IO_INTENT_READWRITE);
    //    DRV_NVM_W
    //    NVM_PageErase(NVM_MEDIA_START_ADDRESS);
    //    while(NVM_IsBusy());
    //    NVM_RowWrite(parameters.buffer, NVM_MEDIA_START_ADDRESS);
    //    while(NVM_IsBusy());



    xTaskResumeAll();
    delayMs(100);



    //DRV_FLASH_ErasePage(flash.handle, DRV_NVM_MEDIA_START_ADDRESS);

    //while(DRV_FLASH_IsBusy());
    //    DRV_FLASH_WriteRow(flash.handle, DRV_NVM_MEDIA_START_ADDRESS, buffer);
    //
    //    while(DRV_FLASH_IsBusy());
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
    memmove(&parameters.buffer, &gNVMFlashReserveArea, sizeof(parameters));
    memmove(&backToto.buffer, &gNVMFlashReserveArea, sizeof(backToto));
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

    uint32_t value;
    uint8_t byChannel;
    uint32_t dwParameterSize = sizeof(PARAMETERS);
    int byIndex;
    uint8_t dwBuffer[11];
    while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 6);
    memmove(dwBuffer, VERSION, 6);

    for(byIndex = 0; byIndex < 6; byIndex++)
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
        PLIB_USART_TransmitterByteSend(USART_ID_2, dwBuffer[byIndex]);
    }

    while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 11);
    memmove(dwBuffer, __DATE__, 11);
    for(byIndex = 0; byIndex < 11; byIndex++)
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
        PLIB_USART_TransmitterByteSend(USART_ID_2, dwBuffer[byIndex]);
    }

    memmove(dwBuffer, &dwParameterSize, sizeof(dwParameterSize));
    for(byIndex = 0; byIndex < sizeof(dwParameterSize); byIndex++)
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
        PLIB_USART_TransmitterByteSend(USART_ID_2, dwBuffer[byIndex]);
    }

    for(byIndex = 0; byIndex < dwParameterSize; byIndex++)
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
        PLIB_USART_TransmitterByteSend(USART_ID_2, parameters.buffer[byIndex]);
    }

    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        value = getCoinValue(byIndex);
        memmove(dwBuffer, &value, 4);
        for(byIndex = 0; byIndex < 4; byIndex++)
        {
            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
            PLIB_USART_TransmitterByteSend(USART_ID_2, dwBuffer[byIndex]);
        }
    }

    for(byChannel = 0; byChannel < 8; byChannel++)
    {
        value = getBillValue(byIndex);
        memmove(dwBuffer, &value, 4);
        for(byIndex = 0; byIndex < 4; byIndex++)
        {

            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
            PLIB_USART_TransmitterByteSend(USART_ID_2, dwBuffer[byIndex]);
        }
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
    int byIndex;
    BILL_TYPE billType;
    COIN_TYPE coinType;

    while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));
    PLIB_USART_TransmitterByteSend(USART_ID_2, 0X5A);
    xTimerStart(pcCom.hTimerTO_PC, 1000);
    while(!PLIB_USART_TransmitterIsEmpty(USART_ID_2));

    for(byIndex = 0; byIndex < sizeof(PARAMETERS); byIndex++)
    {
        while(!PLIB_USART_ReceiverDataIsAvailable(USART_ID_2));
        parameters.buffer[byIndex] = PLIB_USART_ReceiverByteReceive(USART_ID_2);

    }
    xTimerStop(pcCom.hTimerTO_PC, 1000);
    setCoinEnableMask(parameters.data.enables.enable_GG);

    setCoinEnableMask(parameters.data.enables.enable_GG);
    coinType = getCoinType();
    isSetCoinEnable(true, &coinType);
    setBillEnableMask(parameters.data.enables.enable_BV);
    billType = getBillType();
    isSetBillEnable(true, &billType); // &billValidator.byBillType);
    vParametersWrite();
    //vParametersRead();
}

/**
 * @}
 */
/* *****************************************************************************
End of File
 */

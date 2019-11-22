/* ************************************************************************** */

#include <machine/types.h>

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
 * \brief Structure contenant l'habilitation des périphériques
 */
typedef struct
{
    uint16_t enable_GG; /*!<Habilitation des canaux du changeur.*/
    uint16_t enable_BV; /*!<Habilitation des canaux du lecteur de billets.*/
} ENABLE;

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
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 2, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 3, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 4, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 5, 0, 0,
   0, 0, 3, 3, 6, 5, 1, 6, 0, 4, 0, 4, 6, 0, 0,
   0, 0, 0,
   60, 30,
   983071, //Activation par défaut des moyens de paiement 0X001F001F 
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
    pcCom.isTOReached = false;
    xTimerStart(pcCom.hTimerTO_PC, 1000);
    while(!UART3_ReceiverIsReady() && !pcCom.isTOReached);
    if(!pcCom.isTOReached)
    {
        if(UART3_Read(&parameters.data, sizeof(PARAMETERS)))
        {
            while(!UART3_TransmitComplete());
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

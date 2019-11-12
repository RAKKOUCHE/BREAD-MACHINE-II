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

#include <string.h>
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
    unsigned int isAuditInform; /*!<La consultation des audits est autorisée sur ce 
                         * numéro*/
    unsigned int isActivityInform; /*!<Ce numéro sera informé de l'activité de la 
                               * machine.*/
} PHONES;

/**
 * \brief type structure contenant les paramètres.
 */
typedef struct
{
    uint32_t id; /*!<Identification de la machine*/
    int prices[3]; /*!<Prix des produits en cash.*/
    int pricesCL[3]; /*!<Prix des produits en cashless.*/
    PHONES phones[6]; /*!<Numéro et activation des numéros de t'léphones.*/
    int sensitivity[3]; /*!<Sensitivité de la sécurité des trappes.*/
    int TOcumul; /*!<Délai maximum accordé pour réinsérer une autre pièce.*/
    int TOOverpay; /*!<Délai maximum de maintien du trop perçu.*/
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
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   0, 0, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
   800, 800, 800,
   60, 60
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
void vParametreWrite(void)
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

/**
 * @}
 */
/* *****************************************************************************
 End of File
 */

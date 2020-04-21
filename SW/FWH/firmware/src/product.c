/**
 * \addtogroup product
 * @{
 */

/** *************************************************************************
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 08
 *
 * \file audits.c
 *
 * \brief Fichier gestion des produits.
 *
 * \details Gestion des produits.
 *
 ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "product.h"

/**
 * \brief
 */
typedef struct __attribute__((packed))
{
    bool isSelectable;
}
PRODUCT;

/**
 * \brief
 */
static PRODUCT products[PRODUCT_NUMBER];

/*********************************************************************
 * Function:        void setIsProductSelectable(const uint8_t byNumber, const bool isSelectable)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void setIsProductSelectable(const uint8_t byNumber, const bool isSelectable)
{
    products[byNumber].isSelectable = isSelectable;
}

/*********************************************************************
 * Function:        bool getIsProductSelectable(uint8_t byNumber)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
bool getIsProductSelectable(const uint8_t byNumber)
{
    return products[byNumber].isSelectable;
}

/*********************************************************************
 * Function:        void vInitProduct(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vProductInit(void)
{
    uint8_t byIndex;
    for(byIndex = 0; byIndex < PRODUCT_NUMBER; byIndex++)
    {
        products[byIndex].isSelectable = true;
    }
}

/**
 * @}
 */
/* *****************************************************************************
 End of File
 */

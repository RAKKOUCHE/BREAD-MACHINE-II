/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 *
 *  Company RASoftware
 *
 * \date 2019 11 01
 *
 * \file product.h
 *
 * \brief Fichier entête de la gestion des produits.
 *
 ***************************************************************************/

#ifndef _PRODUCT_H    /* Guard against multiple inclusion */
#define _PRODUCT_H

/**
 * \defgroup product PRODUCTS
 * Gestion de la disponibilité des produits.
 * @{
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <stdbool.h>
#include <stdint.h>
#include "communDef.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif
    
    /**
     * \brief
     */
    void setIsProductSelectable(uint8_t byNumber, const bool isSelectable);

    /**
     * \brief
     */
    bool getIsProductSelectable(uint8_t byNumber);

    /**
     * \brief
     */
    void vProductInit(void);
    
/**
 * @}
 */
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}

#endif

#endif /* _PRODUCT_H */

/* *****************************************************************************
 End of File
 */

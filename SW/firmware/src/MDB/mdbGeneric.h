/* 
 * File:   mdbGeneric.h
 * Author: Rachid AKKOUCHE
 *
 * Created on 21 mars 2016, 02:23
 */

#ifndef MDBGENERIC_H
#define	MDBGENERIC_H

#ifdef	__cplusplus
extern "C"
{
#endif
    
#include <stdint.h>
    /*Structures***************************************************************/

    typedef struct __attribute__((packed))
    {
        uint8_t byLevel; /*!< Niveau MDB du périphérique.*/
        uint8_t byCountryCode[2]; /*!< Currency code. Cf l'appendix 1 de la documentation MDB. */
    }
    MDBGENERICDEVICECONFIG;

#ifdef	__cplusplus
}
#endif

#endif	/* MDBGENERIC_H */


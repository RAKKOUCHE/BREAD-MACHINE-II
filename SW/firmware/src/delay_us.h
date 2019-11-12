/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file delay_us.h
 * 
 * \brief Fichier entête du delais de 10 us.
 *  
 ***************************************************************************/
#ifndef __DELAY_H
#define __DELAY_H

#include <GenericTypeDefs.h>
#include "globaldef.h"
#include  "xc-pic32m.h"

/**
 * \defgroup delais DELAIS
 * \brief Module gérant les délais de 10us utilisés par le programme.
 * @{
 */

/**
 * brief Attend un délai de 10 microsecondex x dwCount
 * @param dwCount Multiplicateur 
 */
void Delay10us(DWORD dwCount);

/**
 * @}
 */

#endif	/* DELAY_H */


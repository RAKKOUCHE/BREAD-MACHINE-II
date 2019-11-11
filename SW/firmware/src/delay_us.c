/* ************************************************************************** */
/**
 * \author Rachid AKKOUCHE
 * 
 *  Company RASoftware
 * 
 * \date 2019 11 08
 * 
 * \file delay_us.c
 * 
 * \brief Fichier source de délai de 10 us.
 *  
 ***************************************************************************/

#include "delay_us.h"

/**
 * \addtogroup delais
 * @{
 */
/*********************************************************************
 * Function:        void Delay10us(DWORD dwCount)
 *
 * PreCondition:    La valeur configCPU_CLOCK_HZ doit être définie dans
 *                  FreeRTOSConfig.h
 *
 * Input:           DWORD dwCount. Delai en microsecondes * 10.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Attend le nombre de secondes fixé en microseconde *10
 *
 * Note:            None
 ********************************************************************/
void Delay10us(DWORD dwCount)
{
    volatile DWORD _dcnt;
    
    _dcnt = dwCount * ((DWORD)(0.00001 / (1.0 / GetSystemClock()) / 10));

    while(_dcnt--)
    {
        Nop();       
        Nop();
        Nop();
        Nop();
        Nop();
    }
}
/**
 * @}
 */
/*****************************************************************************/

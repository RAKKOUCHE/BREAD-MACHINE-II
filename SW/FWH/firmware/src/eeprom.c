#include "eeprom.h"

/*********************************************************************
 * Function:        static I2C_BUS_STATE vEEpromWriteBuffer(uint8_t *byData,
 *                                                          int length)
 *
 * Version:         1.0
 *
 * Date:            01/01/2017
 *
 * Author:          Rachid AKKOUCHE
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
static I2C_BUS_STATE vEEpromWriteBuffer(uint8_t *byData, DWORD dwLen)
{
    while(dwLen--)
    {
        while(PLIB_I2C_TransmitterIsBusy(I2C_ID_3));
        while(!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3));
        while(!PLIB_I2C_BusIsIdle(I2C_ID_3));

        PLIB_I2C_TransmitterByteSend(I2C_ID_3, *byData++);
        if(PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_3))
        {
            return I2C_WR_FAULT;
        }
        while(PLIB_I2C_TransmitterIsBusy(I2C_ID_3));
        while(!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3));

        if(!PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_3))
        {
            return I2C_NAK;
        }
    }

    return I2C_OK;
}

/*********************************************************************
 * Function:
     void vEEpromInit(void)
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
void vEEpromInit(void)
{
    PLIB_I2C_BaudRateSet(I2C_ID_3, SYS_CLK_BUS_PERIPHERAL_1, 100000);
    PLIB_I2C_HighFrequencyEnable(I2C_ID_3);
    PLIB_I2C_Enable(I2C_ID_3);
}

/******************************************************************************/

/*********************************************************************
 * Function:        I2C_BUS_STATE vEEpromSetAddress(WORD wAddress)
 *
 * Version:         1.0
 *
 * Date:            01/01/2017
 *
 * Author:          Rachid AKKOUCHE
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
static I2C_BUS_STATE vEEpromSetAddress(WORD wAddress)
{

    uint8_t byData[] = {/*EEPROM_DEVICE_ADDRESS,*/ wAddress >> 8, wAddress};
    if(!(PLIB_I2C_BusIsIdle(I2C_ID_3)))
    {
        return I2C_NOT_IDLE;
    }

    if(PLIB_I2C_ArbitrationLossHasOccurred(I2C_ID_3))
    {
        PLIB_I2C_ArbitrationLossClear(I2C_ID_3);
        return I2C_BUS_COLLISION;
    }

    PLIB_I2C_MasterStart(I2C_ID_3);

    while(!PLIB_I2C_BusIsIdle(I2C_ID_3));
    while(!PLIB_I2C_StartWasDetected(I2C_ID_3));

    PLIB_I2C_TransmitterByteSend(I2C_ID_3, EEPROM_DEVICE_ADDRESS);

    while(!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3));

    /* check if writing to I2CxTRN caused a transmitter overflow */
    if(PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_3))
    {
        return I2C_WR_FAULT;
    }

    if(!PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_3))
    {
        return I2C_NAK;
    }

    return vEEpromWriteBuffer(byData, sizeof(byData));
}

/******************************************************************************/

/*********************************************************************
 * Function:        I2C_BUS_STATE vEEpromWriteByte(WORD wAddress, uint8_t byData)
 *
 * Version:         1.0
 *
 * Date:            01/01/2017
 *
 * Author:          Rachid AKKOUCHE
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


I2C_BUS_STATE EEpromWriteByte(WORD wAddress, uint8_t byData)
{

    I2C_BUS_STATE result;

    if((result = vEEpromSetAddress(wAddress)) == I2C_OK)
    {
        result = vEEpromWriteBuffer(&byData, 1);

        /* if bus is not idle return with false */
        while(!(PLIB_I2C_BusIsIdle(I2C_ID_3)));
        /* Issue stop */
        PLIB_I2C_MasterStop(I2C_ID_3);

        while(!PLIB_I2C_BusIsIdle(I2C_ID_3));
        while(!PLIB_I2C_StopWasDetected(I2C_ID_3));


        //Write delay
        do
        {
            Delay10us(1);
            PLIB_I2C_MasterStart(I2C_ID_3);

            while(!PLIB_I2C_BusIsIdle(I2C_ID_3));
            while(!PLIB_I2C_StartWasDetected(I2C_ID_3));

            PLIB_I2C_TransmitterByteSend(I2C_ID_3, EEPROM_DEVICE_ADDRESS);

            while(!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3));

        } while(!PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_3));
    }
    return result;
}
/******************************************************************************/

/*********************************************************************
 * Function:        I2C_BUS_STATE vEEpromWriteData(WORD wADDRESS, void *data,
 *                                                 int length)
 *
 * Version:         1.0
 *
 * Date:            01/01/2017
 *
 * Author:          Rachid AKKOUCHE
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
I2C_BUS_STATE EEpromWriteData(const WORD wADDRESS, void *data, const int len)
{
    //    //result = I2C_OK;
    //    vTaskSuspendAll();
    //    vEEpromSetAddress(wADDRESS);
    //    vEEpromWriteBuffer(data, len);
    //
    //    xTaskResumeAll();

    uint8_t byIndex;
    I2C_BUS_STATE result;
    uint8_t *byData;
    byData = data;
    vTaskSuspendAll();
    for(byIndex = 0; byIndex < len; byIndex++)
    {

        if((result = EEpromWriteByte(wADDRESS + byIndex, *byData++)) != I2C_OK)
        {
            break;
        }
    }
    xTaskResumeAll();
    return result;
}

/******************************************************************************/

/*********************************************************************
 * Function:        I2C_BUS_STATE vEEPromReadData(WORD wAddress, void *data,
 *                                                int length)
 *
 * Version:         1.0
 *
 * Date:            01/01/2017
 *
 * Author:          Rachid AKKOUCHE
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
I2C_BUS_STATE EEPromReadData(WORD wAddress, void *data, int length)
{
    I2C_BUS_STATE result;
    uint8_t *byData;
    uint8_t byIndex;
    uint8_t device = EEPROM_DEVICE_ADDRESS | 0x01;
    byData = data;

    if((result = vEEpromSetAddress(wAddress)) == I2C_OK)
    {
        if(PLIB_I2C_BusIsIdle(I2C_ID_3))
        {
            if(!PLIB_I2C_ArbitrationLossHasOccurred(I2C_ID_3))
            {
                PLIB_I2C_MasterStart(I2C_ID_3);
                while(!PLIB_I2C_StartWasDetected(I2C_ID_3));
                while(!PLIB_I2C_BusIsIdle(I2C_ID_3));
            }
            else
            {
                PLIB_I2C_ArbitrationLossClear(I2C_ID_3);
                return I2C_BUS_COLLISION;

            }
            if((result = vEEpromWriteBuffer(&device, 1)) == I2C_OK)
            {
                for(byIndex = 0; byIndex < length; byIndex++)
                {
                    while(!PLIB_I2C_BusIsIdle(I2C_ID_3));

                    while(PLIB_I2C_ReceiverOverflowHasOccurred(I2C_ID_3))
                    {
                        PLIB_I2C_ReceiverOverflowClear(I2C_ID_3);
                        delayMs(1);
                    }

                    /* Initiate clock to receive */
                    PLIB_I2C_MasterReceiverClock1Byte(I2C_ID_3);

                    while(!PLIB_I2C_ReceivedByteIsAvailable(I2C_ID_3));

                    byData[byIndex] = PLIB_I2C_ReceivedByteGet(I2C_ID_3);
                    while(!PLIB_I2C_MasterReceiverReadyToAcknowledge(I2C_ID_3));
                    PLIB_I2C_ReceivedByteAcknowledge(I2C_ID_3, byIndex < (length - 1));

                    while(!PLIB_I2C_ReceiverByteAcknowledgeHasCompleted(I2C_ID_3));
                }

                while(!(PLIB_I2C_BusIsIdle(I2C_ID_3)));
                PLIB_I2C_MasterStop(I2C_ID_3);
                while(!(PLIB_I2C_BusIsIdle(I2C_ID_3)));
                while(!PLIB_I2C_StopWasDetected(I2C_ID_3));
            }

        }
        else
        {
            result = I2C_NOT_IDLE;
        }
    }
    return result;
}
/******************************************************************************/

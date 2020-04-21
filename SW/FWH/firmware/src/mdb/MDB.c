/**
 * \addtogroup MDB
 * @{
 */

#include "mdb.h"

#define MDB_TASK_NAME "TSK MDB"

/**
 * \brief Priorité de la tâche MDB.
 */
#define MDB_TASK_PRIORITY 4

/**
 * \brief Taille du tas de la tâche MDB.
 */
#define MDB_TASK_STACK 512

typedef enum
{
    MDB_INIT,
    MDB_POLL_CG,
    MDB_POLL_BV,
    MDB_IDLE,
}
MDB_STATUS;

typedef struct
{
    uint8_t byData;
    bool isBit9th;
}
UARTDATA;

typedef union
{
    UARTDATA uartData;
    WORD wData;
}
uUART_DATA;

/*Variables****************************************************************/

struct
{
    bool isMDBChecked;
    uint8_t byDecimalPos;
    WORD wCurrencyDivider;
    MDB_STATUS state;
    /**
     \brief Indique le TO pour la réponse du périphérique MDB est atteint.
     */
    bool isNAK;

    /**
     *\brief Handle du timer utilisé pour le TO de la réponse d'un périphérique MDB.
     */
    TimerHandle_t hTimerMDBNAK;
    SemaphoreHandle_t hSemaphoreTask;
    SemaphoreHandle_t hSemaphorePoll;
    TaskHandle_t hTaskMdb;
} mdb;

/*********************************************************************
 * Function:        void vNAKTO_MDB(const TimerHandle_t HandleTimer)
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
static void vNAKTO_MDB(const TimerHandle_t HandleTimer)
{
    mdb.isNAK = true;
}
/******************************************************************************/

/*********************************************************************
 * Function:        static void vTaskMDB(void)
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
static void vTaskMDB(void)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        switch(mdb.state)
        {
            case MDB_INIT:
                // <editor-fold defaultstate="collapsed" desc="MDB_INIT">
            {
                mdb.isMDBChecked = false;
                vLCD_CLEAR();
                vDisplayLCD("%s", "  Verification");
                vLCDGotoXY(1, 2);
                vDisplayLCD("%s", "      MDB");

                PLIB_USART_LineControlModeSelect(USART_ID_4, USART_9N1);
                PLIB_USART_BaudRateSet(USART_ID_4, SYS_CLK_BUS_PERIPHERAL_1, 9600);
                PLIB_USART_OperationModeSelect(USART_ID_4, USART_ENABLE_TX_RX_USED);
                PLIB_USART_TransmitterEnable(USART_ID_4);
                PLIB_USART_ReceiverEnable(USART_ID_4);
                PLIB_USART_Enable(USART_ID_4);

                if(mdb.hSemaphoreTask == NULL)
                {
                    mdb.hSemaphoreTask = xSemaphoreCreateBinary();
                }
                if(mdb.hTimerMDBNAK == NULL)
                {
                    mdb.hTimerMDBNAK = xTimerCreate((const char * const)"TMR MDB", MDB_TO, pdFALSE,
                                                    NULL, vNAKTO_MDB);
                }
                mdb.wCurrencyDivider = 1;
                vCGInit();
                vBVInit();
                mdb.state = MDB_POLL_CG;
                break;
            }
                // </editor-fold>

            case MDB_POLL_CG:
                // <editor-fold defaultstate="collapsed" desc="MDB_POLL_CG">
            {
                mdb.state = MDB_POLL_BV;
                vTaskCG();
                break;
            }
                // </editor-fold>

            case MDB_POLL_BV:
                // <editor-fold defaultstate="collapsed" desc="MDB_POLL_BV">
            {
                mdb.state = MDB_IDLE;
                vTaskBV();
                break;
            }
                // </editor-fold>

            case MDB_IDLE:
                // <editor-fold defaultstate="collapsed" desc="MDB_IDLE">
            {
                mdb.state = MDB_POLL_CG;
                if(!mdb.isMDBChecked && getGCInitialized() && getIsBVInitialized())
                {
                    mdb.isMDBChecked = true;
                    setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_SELECT);
                }
                break;
            }
                // </editor-fold>

            default:
            {
                break;
            }
        }
        vTaskDelayUntil(&xLastWakeTime, MDB_POLLING_MS);
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:        uint8_t byCheckSum(uint8_t byLen, const uUART_DATA* ptrBuffer)
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
static uint8_t byCheckSum(uint8_t byLen, const uUART_DATA* ptrBuffer)
{
    uint8_t byResult = 0;
    while(byLen--)
    {
        byResult += (ptrBuffer[byLen].uartData.byData) & 0X00FF;
    }
    return byResult;
}

/******************************************************************************/

/*********************************************************************
 * Function:        void vMDBINIT(void)
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
void vMDBInit(void)
{
    mdb.isMDBChecked = false;
    if(mdb.hSemaphorePoll == NULL)
    {
        xSemaphoreGive(mdb.hSemaphorePoll = xSemaphoreCreateBinary());
    }
    mdb.state = MDB_INIT;

    if(mdb.hTaskMdb == NULL)
    {
        xTaskCreate((TaskFunction_t)vTaskMDB, MDB_TASK_NAME, MDB_TASK_STACK, NULL,
                    MDB_TASK_PRIORITY, &mdb.hTaskMdb);
        vTaskSuspend(mdb.hTaskMdb);
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:
 *         TaskHandle_t getHandleMDB(void)
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
TaskHandle_t getHandleMDB(void)
{
    return mdb.hTaskMdb;
}

/*********************************************************************
 * Function:
 *         uint8_t getMDBDecimalPoint(void)
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
uint8_t getMDBDecimalPos(void)
{
    return mdb.byDecimalPos;
}

/*********************************************************************
 * Function:
 *         void setMDBDecimalPoint(uint8_t value)
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
void setMDBDecimalPoint(uint8_t value)
{
    mdb.byDecimalPos = value;
}

/*********************************************************************
 * Function:
 *         void setMDBCurrencyDivider(uint16_t divider)
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
void setMDBCurrencyDivider(uint16_t divider)
{
    mdb.wCurrencyDivider = divider;
}

/*********************************************************************
 * Function:
 *         bool getisMDBChecked(void)
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
bool getIsMDBChecked(void)
{
    return mdb.isMDBChecked;
}

/*********************************************************************
 * Function:
 *         uint16_t getMDBCurrencyDivider(void)
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
uint16_t getMDBCurrencyDivider(void)
{
    return mdb.wCurrencyDivider;
}

/*********************************************************************
 * Function:        WORD decimalDivider(uint8_t byDecimal)
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
WORD decimalDivider(uint8_t byDecimal)
{
    WORD wResult = 1;
    while(byDecimal--)
    {
        wResult *= 10;
    }
    return wResult;
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vVMCAcknowledge(const uint8_t byAcknowledge)
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
void vVMCAcknowledge(const uint8_t byAcknowledge)
{
    uUART_DATA uaAcknowledge;
    uaAcknowledge.wData = byAcknowledge;
    mdb.isNAK = false;
    xTimerStart(mdb.hTimerMDBNAK, 60 * SECONDE);
    while(!PLIB_USART_TransmitterIsEmpty(USART_ID_4));
    if(!mdb.isNAK)
    {
        PLIB_USART_Transmitter9BitsSend(USART_ID_4, uaAcknowledge.uartData.byData, false);
    }
    xTimerStop(mdb.hTimerMDBNAK, 60 * SECONDE);
}
/******************************************************************************/

/*********************************************************************
 * Function:
 *         uint8_t byMDBSendCommand(const uint8_t byAddress, const uint8_t byCommand,
                      const uint8_t byLenParameters, void *ptrParameters,
                      void *ptrAnswer)
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
uint8_t byMDBSendCommand(const uint8_t byAddress, const uint8_t byCommand,
                         const uint8_t byLenParameters, void *ptrParameters,
                         void *ptrAnswer)
{
    uint8_t byIndex = 0;
    uUART_DATA data[36];
    uint8_t *byPtrParameters, *byPtrAnswer;
    byPtrParameters = ptrParameters;
    byPtrAnswer = ptrAnswer;
    bool isRepeat = false;
    xSemaphoreTake(mdb.hSemaphorePoll, SECONDE);

    do
    {
        memset(&data, 0, sizeof(data));
        //Formate la transmision du premier mot
        data[0].uartData.byData = (byAddress + byCommand);
        data[0].uartData.isBit9th = true;

        //Complete le buffer à transmettre
        for(byIndex = 1; byIndex <= byLenParameters; byIndex++)
        {
            data[byIndex].uartData.byData = (uint8_t)byPtrParameters[byIndex - 1];
            data[byIndex].uartData.isBit9th = false;
        }

        //Calcul du checksum de la transmission
        data[byLenParameters + 1].uartData.byData = byCheckSum(byLenParameters + 1, data);
        data[byLenParameters + 1].uartData.isBit9th = false;

        //Transmission des données
        mdb.isNAK = false;
        for(byIndex = 0; byIndex < (byLenParameters + 2); byIndex++)
        {
            xTimerChangePeriod(mdb.hTimerMDBNAK, 5 * MILLISEC, SECONDE);
            while(!PLIB_USART_TransmitterIsEmpty(USART_ID_4) && !mdb.isNAK);
            if(!mdb.isNAK)
            {
                PLIB_USART_Transmitter9BitsSend(USART_ID_4, data[byIndex].uartData.byData, data[byIndex].uartData.isBit9th);

            }
            else
            {
                byPtrAnswer[0] = NAK;
                break;
            }
        }

        while(!PLIB_USART_TransmitterIsEmpty(USART_ID_4) && !mdb.isNAK);

        if(!mdb.isNAK)
        {
            //Réception
            byPtrAnswer[byIndex = 0] = NAK;
            xTimerChangePeriod(mdb.hTimerMDBNAK, 500 * MILLISEC, SECONDE);
            do
            {
                while(!PLIB_USART_ReceiverDataIsAvailable(USART_ID_4) & !mdb.isNAK);
                if(!mdb.isNAK)
                {
                    data[byIndex].wData = PLIB_USART_Receiver9BitsReceive(USART_ID_4);
                    byPtrAnswer[byIndex] = data[byIndex].uartData.byData;
                    //Si la réponse du périphérique est NAK
                    if((byIndex == 1) && (data[byIndex].uartData.byData == 0XFF))
                    {
                        mdb.isNAK = true;
                    }
                }
            }while(!data[byIndex++].uartData.isBit9th && !mdb.isNAK);
            if(!mdb.isNAK)
            {
                if(byCheckSum(byIndex - 1, data) != data[byIndex - 1].uartData.byData)
                {
                    byPtrAnswer[0] = NAK;
                    mdb.isNAK = true;
                    byIndex = 0;
                }
            }
            xTimerStop(mdb.hTimerMDBNAK, SECONDE);
            if((isRepeat = (mdb.isNAK ? !isRepeat : false)))
            {
                delayMs(100);
            }
        }
    }while(isRepeat);
    if(mdb.isNAK)
    {
        byIndex = 0;
    }
    else
    {
        LED_MDB_Toggle();
    }
    xSemaphoreGive(mdb.hSemaphorePoll);

    return byIndex;
}
/******************************************************************************/

/*********************************************************************
 * Function:        bool isMDBPoll(const uint8_t byDeviceAddress, uint8_t *byResponse,
 *                  uint8_t *byLenAnswer)
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
bool isMDBPoll(const uint8_t byDeviceAddress, uint8_t *byResponse, uint8_t * byLenAnswer)
{

    uint8_t byResult = byMDBSendCommand(byDeviceAddress, CMD_POLL, 0, NULL,
                                        byResponse);
    if(byResult > 1)
    {
        vVMCAcknowledge(ACK);
    }
    *byLenAnswer = byResult;
    return(byResult > 1) || ((byResult == 1) && (byResponse[0] == ACK));

}

/******************************************************************************/

/*********************************************************************
 * Function:        bool isMDBReset(const uint8_t byDeviceAddress)
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
bool isMDBReset(const uint8_t byDeviceAddress)
{
    uint8_t byAcknowledge;
    return((byMDBSendCommand(byDeviceAddress, CMD_RESET, 0, NULL, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        bool isGetMDBConfig(const uint8_t byDeviceAddress,
 *                  void *byStatus, const uint8_t byLen)
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
bool isGetMDBConfig(const uint8_t byDeviceAddress, void *byStatus, const uint8_t byLen)
{
    if(byMDBSendCommand(byDeviceAddress, CMD_SETUP, 0, NULL, byStatus) > 1)
    {
        vVMCAcknowledge(ACK);
        return true;
    }
    vVMCAcknowledge(NAK);
    return false;
}

/******************************************************************************/

/*********************************************************************
 * Function:        void vDisplayRefused(void)
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
void vDisplayRefused(void)
{
    //Traitement des espèces non identifiées.
    vLCD_CLEAR();
    delayMs(100);
    vDisplayLCD("%s", "Refusee...");
    delayMs(1000);
    if(getAmountDispo())
    {
        setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
    }
    else
    {
        //TODO Traitement du clavier
        //        if(clavier.keyInUse >= NUMBTNS)
        //        {
        //            mainBoardData.state = MAINBOARD_STATE_DISPLAY_SELECT;
        //        }
        //        else
        //        {
        //            xQueueSendToBack(clavier.queue, &clavier.keyInUse, portMAX_DELAY);
        //        }
    }
}
/**
 * @}
 */
/******************************************************************************/

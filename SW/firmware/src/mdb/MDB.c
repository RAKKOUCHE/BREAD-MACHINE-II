#include "mdb.h"

#define MDB_TASK_NAME "TSK MDB"

/**
 * \brief Priorité de la tâche MDB.
 */
#define MDB_TASK_PRIORITY 3

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
    BYTE byData;
    BYTE bit9th;
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
    BYTE byDecimalPos;
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
        LED_MDB_Toggle();
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
                if(mdb.hSemaphoreTask == NULL)
                {
                    mdb.hSemaphoreTask = xSemaphoreCreateBinary();
                }
                if(mdb.hTimerMDBNAK == NULL)
                {
                    mdb.hTimerMDBNAK = xTimerCreate((const char * const) "TMR MDB", MDB_TO, pdFALSE,
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
                    setMainBoardTaskState(MAINBOARD2_STATE_DISPLAY_SELECT);
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
 * Function:        BYTE byCheckSum(BYTE byLen, const uUART_DATA* ptrBuffer)
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
static BYTE byCheckSum(BYTE byLen, const uUART_DATA* ptrBuffer)
{
    BYTE byResult = 0;
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
        xTaskCreate((TaskFunction_t) vTaskMDB, MDB_TASK_NAME, MDB_TASK_STACK, NULL,
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
 * Function:        WORD decimalDivider(BYTE byDecimal)
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
WORD decimalDivider(BYTE byDecimal)
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
 * Function:        void vVMCAcknowledge(const BYTE byAcknowledge)
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
void vVMCAcknowledge(const BYTE byAcknowledge)
{
    uUART_DATA uaAcknowledge;
    uaAcknowledge.wData = byAcknowledge;
    mdb.isNAK = false;
    xTimerStart(mdb.hTimerMDBNAK, 60 * SECONDE);
    while(!UART1_TransmitterIsReady() && !mdb.isNAK);
    if(!mdb.isNAK)
    {
        UART1_WriteByte(uaAcknowledge.wData);
        while(!UART1_TransmitComplete() && !mdb.isNAK);
    }

    xTimerStop(mdb.hTimerMDBNAK, 60 * SECONDE);
}
/******************************************************************************/

/*********************************************************************
 * Function:        
 *         BYTE byMDBSendCommand(const BYTE byAddress, const BYTE byCommand,
                      const BYTE byLenParameters, void *ptrParameters,
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
BYTE byMDBSendCommand(const BYTE byAddress, const BYTE byCommand,
                      const BYTE byLenParameters, void *ptrParameters,
                      void *ptrAnswer)
{
    BYTE byIndex = 0;
    uUART_DATA data[36];
    BYTE *byPtrParameters, *byPtrAnswer;
    byPtrParameters = ptrParameters;
    byPtrAnswer = ptrAnswer;
    BOOL isRepeat = false;
    xSemaphoreTake(mdb.hSemaphorePoll, SECONDE);

    //TODO faire clignoter la led MDB
    //    leds.red.state = LED_TOGGLE;
    do
    {
        memset(&data, 0, sizeof(data));
        //Formate la transmision du premier mot
        data[0].uartData.byData = (byAddress + byCommand);
        data[0].uartData.bit9th = 0X01;

        //Complete le buffer à transmettre
        for(byIndex = 1; byIndex <= byLenParameters; byIndex++)
        {
            data[byIndex].uartData.byData = (BYTE) byPtrParameters[byIndex - 1];
            data[byIndex].uartData.bit9th = 0X00;
        }

        //Calcul du checksum de la transmission    
        data[byLenParameters + 1].uartData.byData = byCheckSum(byLenParameters + 1, data);
        data[byLenParameters + 1].uartData.bit9th = 0X00;

        //Transmission des données
        mdb.isNAK = false;
        for(byIndex = 0; byIndex < (byLenParameters + 2); byIndex++)
        {
            xTimerChangePeriod(mdb.hTimerMDBNAK, 5 * MILLISEC, SECONDE);
            while(!UART1_TransmitterIsReady() && !mdb.isNAK);

            if(!mdb.isNAK)
            {
                UART1_WriteByte(data[byIndex].wData);
                while(UART1_TransmitComplete() && !mdb.isNAK);
            }
            else
            {
                byPtrAnswer[0] = NAK;
                break;
            }
        }

        if(!mdb.isNAK)
        {
            //Réception
            byPtrAnswer[byIndex = 0] = NAK;
            //memset(&byPtrAnswer, 0
            xTimerChangePeriod(mdb.hTimerMDBNAK, 20 * MILLISEC, SECONDE);
            while(!UART1_ReceiverIsReady() && !mdb.isNAK);
            if(!mdb.isNAK)
            {
                do
                {
                    if(byIndex)
                    {
                        xTimerChangePeriod(mdb.hTimerMDBNAK, 10 * MILLISEC, SECONDE);
                        while(!UART1_ReceiverIsReady() && !mdb.isNAK);
                    }
                    if(!mdb.isNAK)
                    {
                        data[byIndex].wData = UART1_ReadByte();
                        byPtrAnswer[byIndex] = data[byIndex].uartData.byData;
                    }
                    else
                    {
                        byPtrAnswer[0] = NAK;
                    }
                } while((!(data[byIndex++].wData & 0x0100)) && !mdb.isNAK);
                //Si la réponse du périphérique est NAK
                if((byIndex == 1) && (data[byIndex].uartData.byData == 0XFF))
                {
                    mdb.isNAK = true;
                }
            }
        }
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
    } while(isRepeat);
    if(mdb.isNAK)
    {
        byIndex = 0;
    }
    xSemaphoreGive(mdb.hSemaphorePoll);

    return byIndex;
}
/******************************************************************************/

/*********************************************************************
 * Function:        bool isMDBPoll(const BYTE byDeviceAddress, BYTE *byResponse, 
 *                  BYTE *byLenAnswer)
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
bool isMDBPoll(const BYTE byDeviceAddress, BYTE *byResponse, BYTE * byLenAnswer)
{

    BYTE byResult = byMDBSendCommand(byDeviceAddress, CMD_POLL, 0, NULL,
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
 * Function:        bool isMDBReset(const BYTE byDeviceAddress)
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
bool isMDBReset(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    return((byMDBSendCommand(byDeviceAddress, CMD_RESET, 0, NULL, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        bool isGetMDBConfig(const BYTE byDeviceAddress, 
 *                  void *byStatus, const BYTE byLen)
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
bool isGetMDBConfig(const BYTE byDeviceAddress, void *byStatus, const BYTE byLen)
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
    vDisplayLCD("%s", "Refusee...");
    delayMs(1000);
    if(getAmountDispo())
    {
        setMainBoardTaskState(MAINBOARD2_STATE_DISPLAY_AMOUNT);
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

/******************************************************************************/

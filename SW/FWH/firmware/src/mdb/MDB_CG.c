/**
 * \addtogroup MDB_CG
 * @{
 */

#include "mdb_cg.h"

/*Constante*******************************************************************/

/**
 * \brief Priorité de la tâche de change.
 */
#define MDB_TASK_PRIORITY 3

/**
 * \brief Taille du tas de la tâche de change.
 */
#define MDB_TASK_STACK 512

/**
 * \brief
 */
const uint8_t changeBase[] = {250, 200, 100, 50, 20, 10, 0, 0};

/*****************************************************************************/

/**
 * \brief
 */
struct
{
    uint8_t byDUMMY[10];
    uint8_t data[36];
    uint8_t byCoinsBuffer[NUMBERCHANNELSCG + 1];
    int iBeforeRetry;
    long lAmountInTubes;
    long lAmountDispensed;
    EXPANSION_CMD expandCmd;
    CG_STATUS state;
    CG_CONFIG config;
    TUBE_STATUS tubes;
    CG_DIAG diagnostic;
    COIN_TYPE coins_enable;
    CG_IDENTIFICATION id;
    TaskHandle_t hChangeTask;
    bool isChangerEnable;
    bool isInitialized;
    bool isChangeFinished;
    bool isJustReseted;
} changeGiver;

/*********************************************************************
 * Function:        static void vResetCG(void)
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
static void vResetCG(void)
{
    changeGiver.iBeforeRetry = MDBRETRY;
    changeGiver.isInitialized = false;
    changeGiver.isChangerEnable = false;
    changeGiver.isJustReseted = true;
    changeGiver.state = CG_RESET;
}

/******************************************************************************/

/*********************************************************************
 * Function:        static void vChangeTask(void)
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
static void vTaskChange(void)
{
    while(1)
    {
        ulTaskNotifyTake(true, portMAX_DELAY);
        if(getAmountDispo())
        {
            changeGiver.lAmountDispensed = 0;
            changeGiver.state = CG_EXPANSION_CMD;
            changeGiver.expandCmd = SUB_ALTERNATIVE_PAYOUT;
        }
        else
        {
            changeGiver.isChangeFinished = true;
        }
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isGetMDBTubeStatus()
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
static bool isGetMDBTubeStatus()
{
    uint8_t byIndex;

    if(byMDBSendCommand(CGADDRESS, CG_TUBE_STATUS, 0x00, NULL,
                        &changeGiver.tubes) == sizeof(TUBE_STATUS) + 1)
    {
        vVMCAcknowledge(ACK);
        changeGiver.lAmountInTubes = 0;
        setMDBDecimalPoint(changeGiver.config.byDecimalPlace);
        setMDBCurrencyDivider(decimalDivider(getMDBDecimalPos()));
        for(byIndex = 0; byIndex < NUMBERCHANNELSCG; byIndex++)
        {
            if((changeGiver.config.byCoinValue[byIndex] < 0xFF) && changeGiver.tubes.byLevel[byIndex])
            {
                changeGiver.lAmountInTubes += changeGiver.config.byCoinValue[byIndex] *
                    changeGiver.config.byScalingFactor *
                    changeGiver.tubes.byLevel[byIndex];
            }
        }
        return true;
    }
    else
    {
        vVMCAcknowledge(NAK);
    }
    return false;
}

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isSetMDBCoinType(COIN_TYPE_ENABLE *coinType)
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
static bool isSetMDBCoinType(COIN_TYPE *coinType)
{
    uint8_t byAcknowledge;
    return((byMDBSendCommand(CGADDRESS, CG_COIN_TYPE, sizeof(coinType), coinType,
                             &byAcknowledge) == 1) && (byAcknowledge == ACK));

}

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isGetCGId(CG_IDENTIFICATION *Idenfication)
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
static bool isGetCGId(CG_IDENTIFICATION *Idenfication)
{
    uint8_t byParameter = SUB_CHANGER_IDENTIFICATION;
    if(byMDBSendCommand(CGADDRESS, CG_EXPANSION_CMD, 0x01, &byParameter,
                        Idenfication) == sizeof(CG_IDENTIFICATION) + 1)
    {
        vVMCAcknowledge(ACK);
        return(true);
    }
    else
    {
        vVMCAcknowledge(NAK);
    }
    return false;
}

/*********************************************************************
 * Function:        bool isCGEnableFeature()
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
static bool isCGEnableFeature()
{
    uint8_t byAcknowledge;
    uint8_t byParameters[5] = {SUB_CHANGER_FEATURE_ENABLE, 0X00, 0X00, 0X00, 0B00000111};
    return((byMDBSendCommand(CGADDRESS, CG_EXPANSION_CMD, sizeof(byParameters),
                             byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isPayoutStatus(uint8_t *byChannels)
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
static bool isPayoutStatus(uint8_t *byChannels)
{
    uint8_t byParameter = SUB_ALT_PAYOUT_STATUS;

    return(byMDBSendCommand(CGADDRESS, CG_EXPANSION_CMD, sizeof(byParameter), &byParameter, byChannels) >= NUMBERCHANNELSCG);
};

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isAlternatePayout(const uint8_t byAmount)
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
static bool isAlternatePayout(const uint8_t byAmount)
{
    uint8_t byAcknowledge;
    uint8_t byParameters[2] = {SUB_ALTERNATIVE_PAYOUT, byAmount};
    return((byMDBSendCommand(CGADDRESS, CG_EXPANSION_CMD, sizeof(byParameters),
                             byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
};

/******************************************************************************/

/*********************************************************************
 * Function:
 *         static bool isGetDiagnostic(CG_DIAG *diag)
 *
 * Author:
 *         Rachid AKKOUCHE
 *
 * Date:
 *         19/08/21
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

static bool isGetDiagnostic(CG_DIAG *diag)
{
    uint8_t byParameter = SUB_DIAGNOSTIC_STATUS;
    return(byMDBSendCommand(CGADDRESS, CG_EXPANSION_CMD, sizeof(byParameter), &byParameter, &changeGiver.diagnostic) == 2);
}
/******************************************************************************/

/*********************************************************************
 * Function:
 *         TaskHandle_t getTaskHandleChange(void)
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
TaskHandle_t getChangeTaskHandle(void)
{
    return changeGiver.hChangeTask;
}

/*********************************************************************
 * Function:
 *         bool getGCInitialized(void)
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
bool getGCInitialized(void)
{
    return changeGiver.isInitialized;
}

/*********************************************************************
 * Function:
 *         bool getIsChangeFinished(void)
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
bool getIsChangeFinished(void)
{
    return changeGiver.isChangeFinished;
}

/*********************************************************************
 * Function:
 *         void setChangeGiverTaskState(CG_STATUS state)
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
void setChangeGiverTaskState(CG_STATUS state)
{
    changeGiver.state = state;
}

/*********************************************************************
 * Function:
 *         void setIsCangeFinished(const bool isFinished)
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
void setIsChangeFinished(const bool isFinished)
{
    changeGiver.isChangeFinished = isFinished;
}

/*********************************************************************
 * Function:
 *         uint32_t getCoinValue(uint8_t byChannel)
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
uint32_t getCoinValue(uint8_t byChannel)
{
    return changeGiver.config.byCoinValue[byChannel] * changeGiver.config.byScalingFactor;
}

/*********************************************************************
 * Function:
 *         void setCoinEnableMask(const uint32_t mask)
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
void setCoinEnableMask(const uint32_t mask)
{
    changeGiver.coins_enable.wCoinEnable = mask;
}

/*********************************************************************
 * Function:
 *         COIN_TYPE getCoinType(void)
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
COIN_TYPE getCoinType(void)
{
    return changeGiver.coins_enable;
}

/*********************************************************************
 * bool isSetCoinEnable(const bool isEnable, const COIN_TYPE_ENABLE *coinType)
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
bool isSetCoinEnable(const bool isEnable, const COIN_TYPE *coinType)
{
    //uint8_t byIndex;
    COIN_TYPE wEnable;
    bool isResult = false;

    wEnable.wCoinEnable = isEnable ? coinType->wCoinEnable >> 8 | coinType->wCoinEnable << 8 : 0;
    isResult = isSetMDBCoinType(&wEnable);
    return isResult;
}

/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskCG(void)
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
void vTaskCG(void)
{
    uint8_t byLenAnswer;
    uint8_t byIndex;
    uint8_t byChannel;
    BILL_TYPE billType;
    bool isDispensed;
    static long lAmountToDispense;

    switch(changeGiver.state)
    {
        case CG_INIT:
            // <editor-fold defaultstate="collapsed" desc="CG_INIT">
        {
            vResetCG();
            changeGiver.iBeforeRetry = 0; //pas de délai avant de lancer la communication
            break;
        }// </editor-fold>

        case CG_RESET:
            // <editor-fold defaultstate="collapsed" desc="CG_RESET">
        {
            if(!changeGiver.iBeforeRetry--)
            {
                changeGiver.iBeforeRetry = MDBRETRY;
                changeGiver.state = CG_POLL;

                if(!isMDBReset(CGADDRESS))
                {
                    vResetCG();
                    changeGiver.isInitialized = true;
                }
                else
                {
                    changeGiver.isInitialized = false;
                }
            }
            break;
        }// </editor-fold>

        case CG_SETUP:
            // <editor-fold defaultstate="collapsed" desc="CG_SETUP">
        {
            if(isGetMDBConfig(CGADDRESS, &changeGiver.config, sizeof(CG_CONFIG)))
            {
                if(!changeGiver.isInitialized)
                {
                    if(changeGiver.config.deviceConfig.byLevel < 3)
                    {
                        changeGiver.state = CG_TUBE_STATUS;
                    }
                    else
                    {
                        changeGiver.state = CG_EXPANSION_CMD;
                        changeGiver.expandCmd = SUB_CHANGER_IDENTIFICATION;
                    }
                }
                else
                {
                    changeGiver.state = CG_COIN_TYPE;
                }
            }
            else
            {
                vResetCG();
            }
            break;
        }
            // </editor-fold>

        case CG_TUBE_STATUS:
            // <editor-fold defaultstate="collapsed" desc="CG_TUBE_STATUS">
        {
            if(isGetMDBTubeStatus())
            {
                changeGiver.state = changeGiver.isInitialized ? CG_POLL : CG_COIN_TYPE;
            }
            else
            {
                vResetCG();
            }
            break;
        }
            // </editor-fold>

        case CG_POLL:
            // <editor-fold defaultstate="collapsed" desc="CG_POLL">
        {
            byLenAnswer = 0;
            memset(changeGiver.data, 0X00, sizeof(changeGiver.data));
            if(isMDBPoll(CGADDRESS, changeGiver.data, &byLenAnswer))
            {
                byIndex = 0;
                do
                {
                    //COINS DISPENSED MANUALLY
                    if((changeGiver.data[byIndex] & COIN_DISPENDED_MANUALLY))
                    {
                        //Traitement des pièces distribuées manuellement.
                        ++byIndex;
                    }
                    else
                    {
                        //COINS INSERTED
                        if((changeGiver.data[byIndex] & COIN_INSERTED) && !(changeGiver.data[byIndex] & COIN_REFUSED)/*Pièce refusée*/)
                        {
                            if(hGetTimerCumul())
                            {
                                xTimerReset(hGetTimerCumul(), 1 * SECONDE);
                            }
                            byChannel = changeGiver.data[byIndex] & 0X0F;
                            //Traitement des pièces insérées.
                            setAmountDispo(getAmountDispo() + (long)(changeGiver.config.byCoinValue[byChannel] *
                                                                     changeGiver.config.byScalingFactor));

                            //TODO afficher le montant à payer.

                            setAuditValue((uint32_t)(ADDRESSCGIN + (byChannel *
                                                                    sizeof(uint32_t))),
                                          getAuditValue((uint32_t)(ADDRESSCGIN +
                                                                   (byChannel *
                                                                    sizeof(uint32_t)))) + 1);
                            ++byIndex;
                            //setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
                        }
                        else
                        {
                            //SLUG
                            if(changeGiver.data[byIndex] & COIN_REFUSED)
                            {
                                //Traitement des pièces non identifiées.
                                vDisplayRefused();
                            }
                            else
                            {
                                //STATUS
                                if(changeGiver.data[byIndex] & 0X0F)
                                {
                                    switch(changeGiver.data[byIndex])
                                    {
                                        case CG_ESCROW:
                                        {
                                            setMainBoardTaskState(MAINBOARD_STATE_CHANGE);
                                            break;
                                        }
                                        case CG_PAYOUT_BUSY:
                                        {
                                            break;
                                        }
                                        case CG_NO_CREDIT:
                                        {
                                            break;
                                        }
                                        case CG_DEFECTIVE_TUBE:
                                        {
                                            //TODO Envoyé message
                                            //vSendSMS("Problème tube changeur.");
                                            break;
                                        }
                                        case CG_DOUBLE_ARRIVAL:
                                        {
                                            break;
                                        }
                                        case CG_UNPLUGGED:
                                        {
                                            break;
                                        }
                                        case CG_TUBE_JAM:
                                        {
                                            //TODO Envoyé message
                                            //vSendSMS("Bourrage tube changeur");
                                            break;
                                        }
                                        case CG_ROM_ERROR:
                                        {
                                            //TODO Envoyé message
                                            //vSendSMS("Defaut ROM changeur");
                                            break;
                                        }
                                        case CG_ROUTE_ERROR:
                                        {
                                            break;
                                        }
                                        case CG_BUSY:
                                        {
                                            break;
                                        }
                                        case CG_JUST_RESET:
                                        {
                                            changeGiver.isInitialized = false;
                                            changeGiver.isChangerEnable = true;
                                            changeGiver.isJustReseted = false;
                                            changeGiver.state = CG_SETUP;
                                            break;
                                        }
                                        case CG_COIN_JAM:
                                        {
                                            //TODO Envoyé message
                                            //vSendSMS("Bourrage pièce");
                                            break;
                                        }
                                        case CG_COIN_REMOVAL:
                                        {
                                            break;
                                        }
                                        default:
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(changeGiver.isJustReseted)
                    {
                        byIndex = byLenAnswer;
                        vResetCG();
                    }
                    ++byIndex;
                }while(byIndex < (byLenAnswer - 1));
            }
            else
            {
                vResetCG();
            }
            break;
        }
            // </editor-fold>

        case CG_COIN_TYPE:
            // <editor-fold defaultstate="collapsed" desc="CG_COIN_TYPE">
        {
            if(changeGiver.isInitialized)
            {
                isSetCoinEnable(changeGiver.isChangerEnable, &changeGiver.coins_enable) ? changeGiver.state = CG_POLL : vResetCG();
            }
            else
            {
                changeGiver.isInitialized = true;
                changeGiver.coins_enable.wCoinEnable = getChannelEnable(true); // (parameters.sparameters.enableCG << 8) & ~0x3F;
                changeGiver.isInitialized = isSetCoinEnable(false, &changeGiver.coins_enable);
                //changeGiver.isInitialized = isSetCoinEnable(changeGiver.isChangerEnable , &changeGiver.coins_enable);
            }
            break;
        }
            // </editor-fold>

        case CG_DISPENSE:
            // <editor-fold defaultstate="collapsed" desc="CG_DISPENSE">
        {
            break;
        }// </editor-fold>

        case CG_EXPANSION_CMD:
            // <editor-fold defaultstate="collapsed" desc="CG_EXPANSION_CMD">
        {
            switch(changeGiver.expandCmd)
            {
                case SUB_CHANGER_IDENTIFICATION:
                    // <editor-fold defaultstate="collapsed" desc="SUB_CHANGER_IDENTIFICATION">
                {
                    if(isGetCGId(&changeGiver.id))
                    {
                        if(!changeGiver.isInitialized)
                        {
                            changeGiver.expandCmd = SUB_FEATURE_ENABLE;
                        }
                        else
                        {
                            changeGiver.state = CG_POLL;
                        }
                    }
                    else
                    {
                        changeGiver.iBeforeRetry = MDBRETRY;
                        changeGiver.state = CG_RESET;
                    }
                    break;
                }
                    // </editor-fold>
                case SUB_FEATURE_ENABLE:
                    // <editor-fold defaultstate="collapsed" desc="SUB_FEATURE_ENABLE">
                {
                    if(isCGEnableFeature())
                    {
                        changeGiver.state = (changeGiver.isInitialized ? CG_POLL : CG_TUBE_STATUS);
                    }
                    else
                    {
                        changeGiver.iBeforeRetry = MDBRETRY;
                        changeGiver.state = CG_RESET;
                    }
                    break;
                }
                    // </editor-fold>
                case SUB_ALTERNATIVE_PAYOUT:
                    // <editor-fold defaultstate="collapsed" desc="SUB_ALTERNATIVE_PAYOUT">
                {
                    if(hGetTimerCumul())
                    {
                        xTimerStop(hGetTimerCumul(), 1 * SECONDE);
                    }
                    byIndex = 0;
                    do
                    {
                        lAmountToDispense = (getAmountDispo() / changeGiver.config.byScalingFactor) > changeBase[byIndex] ?
                            changeBase[byIndex] : (getAmountDispo() / changeGiver.config.byScalingFactor);
                    }while(lAmountToDispense && !isAlternatePayout(lAmountToDispense) && changeBase[byIndex++]);
                    if(!lAmountToDispense || !changeBase[byIndex])
                    {
                        changeGiver.isChangeFinished = true;
                        changeGiver.state = CG_POLL;
                    }
                    else
                    {
                        changeGiver.expandCmd = SUB_ALT_PAYOUT_STATUS;
                    }
                    break;
                }
                    // </editor-fold>

                case SUB_ALT_PAYOUT_STATUS:
                    // <editor-fold defaultstate="collapsed" desc="SUB_ALT_PAYOUT_STATUS">
                {
                    isDispensed = false; //On ne sait pas si une distribution a eu lieu.
                    //Vérifie si la distribution est terminée.

                    if(isPayoutStatus(changeGiver.byCoinsBuffer))
                    {
                        //Vérifie dans chaque canal si des pièces sont retournées
                        for(byIndex = 0; byIndex < NUMBERCHANNELSCG; byIndex++)
                        {
                            //Si le canal a une valeur et qu'il y a des pièces distribuées de ce canal.
                            if(changeGiver.config.byCoinValue[byIndex] && (changeGiver.config.byCoinValue[byIndex] < 0XFF) &&
                               changeGiver.byCoinsBuffer[byIndex])
                            {
                                /*
                                 * Calcul le montant rendu.
                                 * Si oui on sauvegarde le montant dans l'eeprom pour l'audit.
                                 *
                                 */
                                changeGiver.lAmountDispensed += (changeGiver.byCoinsBuffer[byIndex] * changeGiver.config.byCoinValue[byIndex] *
                                                                 changeGiver.config.byScalingFactor);
                                setAuditValue((uint32_t)(ADDRESSCGOUT + (byIndex *
                                                                         sizeof(uint32_t))),
                                              getAuditValue((uint32_t)(ADDRESSCGOUT +
                                                                       (byIndex *
                                                                        sizeof(uint32_t)))) + 1);

                                setAmountDispo(getAmountDispo() -
                                               (changeGiver.byCoinsBuffer[byIndex] * changeGiver.config.byCoinValue[byIndex]
                                                * changeGiver.config.byScalingFactor));
                                //Et on indique qu'au moins une pièce a été distribué.
                                isDispensed = true;
                            }
                        }
                        if(lAmountToDispense > (changeGiver.lAmountDispensed / changeGiver.config.byScalingFactor))
                        {
                            //                        audits.saudit.dwOverPay += (lAmountToDispense - changeGiver.lAmountDispensed) * changeGiver.config.byScalingFactor;
                            //                        EEpromWriteData(ADDRESS_OVERPAY, &audits.saudit.dwOverPay,
                            //                                        sizeof (audits.saudit.dwOverPay));audits.saudit.dwOverPay += (lAmountToDispense - changeGiver.lAmountDispensed) * changeGiver.config.byScalingFactor;
                            if(hGetTimerOverPay())
                            {
                                xTimerStart(hGetTimerOverPay(), 1 * SECONDE);
                            }
                            //setMainBoardTaskState(MAINBOARD_STATE_DISPLAY_AMOUNT);
                            isDispensed = false;
                            setAmountRequested(0);
                        }
                        if(getAmountDispo() < 0)
                        {
                            setAmountDispo(0);
                        }
                        vLCD_CLEAR();

                        vDisplayLCD("Rendu : %.*f\7", getMDBDecimalPos(),
                                    (double)(changeGiver.lAmountDispensed) /
                                    getMDBCurrencyDivider());
                        if(isDispensed)
                        {
                            changeGiver.expandCmd = SUB_ALTERNATIVE_PAYOUT;
                            if(hGetTimerOverPay())
                            {
                                xTimerStart(hGetTimerOverPay(), 1 * SECONDE);
                            }
                        }
                        else
                        {
                            changeGiver.isChangeFinished = true;
                            changeGiver.state = CG_POLL;
                            if(getAmountDispo())
                            {
                                isSetCoinEnable(changeGiver.isChangerEnable = true, &changeGiver.coins_enable);
                                billType = getBillType();
                                isSetBillEnable(true, &billType);
                            }
                        }
                    }
                    break;
                }// </editor-fold>

                case SUB_DIAGNOSTIC_STATUS:
                    // <editor-fold desc="SUB_DIAGNOSTIC_STATUS">
                {
                    if(isGetDiagnostic(&changeGiver.diagnostic) && (changeGiver.diagnostic.Z1 == OK))
                    {
                        Nop();
                    }
                    changeGiver.state = (changeGiver.isInitialized ? CG_POLL : CG_TUBE_STATUS);
                    break;
                }// </editor-fold>
                case SUB_PAYOUT_VALUE_POLL:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }// </editor-fold>

        default:
        {
            break;
        }
    }
}

/*********************************************************************
 * Function:        static void vCGInit(void)
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
void vCGInit(void)
{
    changeGiver.state = CG_INIT;
    xTaskCreate((TaskFunction_t)vTaskChange, "TSK CHANGE", MDB_TASK_STACK, NULL,
                MDB_TASK_PRIORITY, &changeGiver.hChangeTask);
}
/**
 * @}
 */
/******************************************************************************/

/******************************************************************************/

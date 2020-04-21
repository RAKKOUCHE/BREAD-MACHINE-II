
/**
 * \addtogroup MDB_BV
 * @{
 */

#include "mdb_bv.h"

struct __attribute__((packed))
{
    bool isStackerFull;
    bool isEnable;
    bool isInitialized;
    bool isPresent;
    uint16_t wBeforeRetry;
    BILL_TYPE byBillType;
    int16_t i16BillInStacker;
    BV_SUB_CMD expandCmd;
    BV_STATUS state;
    BV_CONFIG config;
    BV_IDENTIFICATION id;
    uint8_t data[36];
}
billValidator;

/*********************************************************************
 * Function:        static bool isGetBVtackerStatus()
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
static bool isGetBVtackerStatus()
{
    if(billValidator.isPresent)
    {
        if(byMDBSendCommand(BVADDRESS, CMD_STACKER, 0X00, NULL, &billValidator.i16BillInStacker) == sizeof(billValidator.i16BillInStacker) + 1)
        {
            vVMCAcknowledge(ACK);
            return true;
        }
        else
        {
            vVMCAcknowledge(NAK);
        }
    }
    return false;
}

/******************************************************************************/

/**
 * \fn isBVEnableFeature
 * \brief Valide les options du niveau 3 du rendeur.
 * \return true si l'opération s'est effectuée correctement.
 */
static bool isBVEnableFeature()
{
    uint8_t byAcknowledge;
    uint8_t byParameters[5] = {SUB_BILL_FEATURE_ENABLE, 0X00, 0X00, 0X00, 0X0F};
    return((billValidator.isPresent &&
            byMDBSendCommand(BVADDRESS, BV_EXPANSION_CMD, sizeof(byParameters),
                             byParameters, &byAcknowledge) == 1) &&
           (byAcknowledge == ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        void NewFunction(void)
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
static bool isGetBVId(BV_IDENTIFICATION *Idenfication, bool boWOptions)
{
    uint8_t byOption = boWOptions ? LEVEL2_ID_W_OPTIONS : LEVEL1_ID_WO_OPTIONS;
    if(billValidator.isPresent)
    {
        if(byMDBSendCommand(BVADDRESS, BV_EXPANSION_CMD, sizeof(byOption), &byOption,
                            Idenfication) == (sizeof(BV_IDENTIFICATION)- (4 * (uint8_t)!boWOptions)) + 1)
        {
            vVMCAcknowledge(ACK);
            return(true);
        }
        else
        {
            vVMCAcknowledge(NAK);
        }
    }
    return false;
}

/******************************************************************************/

/*********************************************************************
 * Function:        static bool isSetMDBillType()
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
static bool isSetMDBillType()
{
    uint8_t byAcknowledge;
    uint8_t byBuffer[4] = {0};
    memmove(byBuffer, billValidator.byBillType.byBillEnable, sizeof(billValidator.byBillType.byBillEnable));
    return((billValidator.isPresent &&
            byMDBSendCommand(BVADDRESS, CMD_BILL_TYPE, sizeof(byBuffer),
                             byBuffer, &byAcknowledge) == 1) &&
           (byAcknowledge == ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        static void vResetBV(void)
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
static void vResetBV(void)
{
    billValidator.isInitialized = false;
    billValidator.wBeforeRetry = MDBRETRY;
    billValidator.state = BV_RESET;
}
/******************************************************************************/

/*********************************************************************
 * Function:
 *         bool getIsBVInitialized(void)
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
bool getIsBVInitialized(void)
{
    return billValidator.isInitialized;
}

/*********************************************************************
 * Function:
 *         void setBV_State(BV_STATUS status)
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
void setBV_State(BV_STATUS status)
{
    billValidator.state = status;
}

/*********************************************************************
 * Function:
 *         BILL_TYPE* getBillType(void)
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
BILL_TYPE getBillType(void)
{
    return billValidator.byBillType;
}

/*********************************************************************
 * Function:        bool isSetBillEnable(const bool isEnable, BILL_TYPE *billType)
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
bool isSetBillEnable(const bool isEnable, BILL_TYPE *billType)
{
    bool isResult = false;

    WORD wEnable;
    if(billValidator.isPresent)
    {
        wEnable = billType->wBillEnable;
        if(!isEnable)
        {
            memset(&billType->wBillEnable, 0x00, sizeof(billType));
            //memset(&billType->byEscrowEnable, 0x7F, sizeof(billType->byEscrowEnable));
        }
        isResult = isSetMDBillType();
        billType->wBillEnable = wEnable;
    }
    return isResult;
}

/******************************************************************************/

/*********************************************************************
 * Function:
 *         uint32_t getBillEnableMask(void)
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
uint32_t getBillEnableMask(void)
{
    return billValidator.byBillType.wBillEnable;
}

/*********************************************************************
 * Function:
 *         void setBillEnableMask(uint32_t mask)
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
void setBillEnableMask(const uint32_t mask)
{
    billValidator.byBillType.wBillEnable = mask;
}

/*********************************************************************
 * Function:
 *         uint32_t getBilleValue(uint8_t byChannel)
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
uint32_t getBillValue(uint8_t byChannel)
{
    return billValidator.config.byBillValue[byChannel] * billValidator.config.wScalingFactor;
}

/*********************************************************************
 * Function:        void vTaskBV(void)
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
void vTaskBV(void)
{
    uint8_t byLenAnswer;
    uint8_t byIndex;
    uint8_t byChannel;

    switch(billValidator.state)
    {
        case BV_INIT:
            // <editor-fold defaultstate="collapsed" desc="BV_INIT">
        {
            billValidator.isPresent = false;
            billValidator.wBeforeRetry = 0; //pas de délai avant de lancer la communication
            billValidator.byBillType.wBillEnable = getEnableState().enable_BV;
            billValidator.byBillType.wBillEnable = billValidator.byBillType.wBillEnable << 8 | billValidator.byBillType.wBillEnable >> 8;
            billValidator.state = BV_RESET; //Après ça on lance un reset.
            break;
        }
            // </editor-fold>

        case BV_RESET:
            // <editor-fold defaultstate="collapsed" desc="BV_RESET">
        {
            if(!billValidator.wBeforeRetry--)
            {
                billValidator.state = BV_POLL;
                if(!isMDBReset(BVADDRESS))
                {
                    vResetBV();
                    billValidator.isInitialized = true;
                }
                else
                {
                    billValidator.isInitialized = false;
                }
            }
            break;
        }
            // </editor-fold>

        case BV_SETUP:
            // <editor-fold defaultstate="collapsed" desc="BV_SETUP">
        {
            if(isGetMDBConfig(BVADDRESS, &billValidator.config, sizeof(BV_CONFIG)))
            {
                billValidator.config.wScalingFactor = ((billValidator.config.wScalingFactor >> 8) | (billValidator.config.wScalingFactor << 8));
                billValidator.config.wStackerCapacity = ((billValidator.config.wStackerCapacity >> 8) | (billValidator.config.wStackerCapacity << 8));
                billValidator.state = billValidator.isInitialized ? BV_POLL : BV_EXPANSION_CMD;
                if(billValidator.config.deviceConfig.byLevel == 1)
                {
                    billValidator.expandCmd = LEVEL1_ID_WO_OPTIONS;
                }
                else
                {
                    billValidator.expandCmd = LEVEL2_ID_W_OPTIONS;
                }
            }
            else
            {
                vResetBV();
            }
            break;
        }
            // </editor-fold>

        case BV_SECURITY:
            // <editor-fold defaultstate="collapsed" desc="BV_SECURITY">
        {
            billValidator.state = BV_POLL;
            break;
        }
            // </editor-fold>

        case BV_POLL:
            // <editor-fold defaultstate="collapsed" desc="BV_POLL">
        {
            byLenAnswer = 0;
            memset(billValidator.data, 0X00, sizeof(billValidator.data));
            if(isMDBPoll(BVADDRESS, billValidator.data, &byLenAnswer))
            {
                if(byLenAnswer)
                {
                    byIndex = 0;
                    do
                    {
                        //BILL ACCEPTED
                        if(billValidator.data[byIndex] & BILL_ACCEPTED)
                        {
                            byChannel = billValidator.data[byIndex] & 0X0F;
                            switch(billValidator.data[byIndex] & 0B01110000)
                            {
                                case STACKED:
                                {
                                    if(hGetTimerCumul())
                                    {
                                        xTimerReset(hGetTimerCumul(), 1 * SECONDE);
                                    }
                                    setAmountDispo(getAmountDispo() + (long)(billValidator.config.byBillValue[byChannel] *
                                                                             billValidator.config.wScalingFactor));
                                    setAuditValue((uint32_t)(ADDRESSBVIN + (byChannel *
                                                                            sizeof(uint32_t))),
                                                  getAuditValue((uint32_t)(ADDRESSBVIN +
                                                                           (byChannel *
                                                                            sizeof(uint32_t)))) + 1);
                                    break;
                                }
                                case RETURNED:
                                case REJECTED:
                                {
                                    vDisplayRefused();
                                    break;
                                }
                                case ESCROW:
                                {

                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            switch(billValidator.data[byIndex] & 0B00001111)
                            {
                                case BV_MOTOR_DEFAULT:
                                {
                                    //TODO envoyé un message pour indiquer le défaut.
                                    // vSendSMS("Défaut moteur lecteur de billets");
                                    break;
                                }
                                case BV_SENSOR_DEFAULT:
                                {
                                    //TODO envoyé un message pour indiquer le défaut.
                                    //vSendSMS("Défaut sensor lecteur de billets");
                                    break;
                                }
                                case BV_ROM_ERROR:
                                {
                                    //TODO envoyé un message pour indiquer le défaut.
                                    //vSendSMS("Défaut ROM lecteur de billets");
                                    break;
                                }
                                case BV_BUSY:
                                {
                                    break;
                                }
                                case BV_JAM_ACCEPTANCE:
                                {
                                    //TODO envoyé un message pour indiquer le défaut.
                                    //vSendSMS("Bourrage lecteur de billets");
                                    break;
                                }
                                case BV_JUST_RESET:
                                {
                                    billValidator.state = BV_SETUP;
                                    billValidator.isPresent = true;
                                    break;
                                }
                                case BV_BILL_REMOVED:
                                {

                                    break;
                                }
                                case BV_CASHBOX_OPEN:
                                {
                                    //TODO envoyé un message pour indiquer le défaut.
                                    //vSendSMS("Caisse lecteur de billets ouverte");

                                    break;
                                }
                                case BV_DISABLED:
                                {
                                    break;
                                }
                                case BV_INVALID_ESCROW:
                                {

                                    break;
                                }
                                case BV_REFUSED:
                                {
                                    vDisplayRefused();
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }

                        }
                        ++byIndex;
                    }while(byIndex < (byLenAnswer - 1));
                }
            }
            else
            {
                vResetBV();
            }
            break;
        }
            // </editor-fold>

        case BV_BILL_TYPE:
            // <editor-fold defaultstate="collapsed" desc="BV_BILL_TYPE">
        {
            if(!billValidator.isInitialized)
            {
                billValidator.isInitialized = true;
                billValidator.isEnable = true;
                billValidator.byBillType.byBillEnable[0] = 0;
                billValidator.byBillType.byBillEnable[1] = getChannelEnable(false);
            }

            if(isSetBillEnable(billValidator.isEnable, &billValidator.byBillType))
            {
                billValidator.state = BV_POLL;
            }
            else
            {
                vResetBV();
            }
            break;
        }
            // </editor-fold>

        case BV_ESCROW:
            // <editor-fold defaultstate="collapsed" desc="BV_ESCROW">
        {
            billValidator.state = BV_POLL;
            break;
        }
            // </editor-fold>

        case BV_STACKER:
            // <editor-fold defaultstate="collapsed" desc="BV_STACKER">
        {
            if(isGetBVtackerStatus())
            {
                if((billValidator.isStackerFull = (billValidator.i16BillInStacker < 0)))
                {
                    //TODO envoyé message sms
                    // vSendSMS("Caisse lecteur de billets pleine.");
                }
                billValidator.i16BillInStacker = abs(billValidator.i16BillInStacker);
                billValidator.i16BillInStacker = (billValidator.i16BillInStacker >> 8) | (billValidator.i16BillInStacker << 8);
                billValidator.state = (billValidator.isInitialized ? BV_POLL : BV_BILL_TYPE);
            }
            else
            {
                vResetBV();
            }
            break;
        }
            // </editor-fold>

        case BV_EXPANSION_CMD:
            // <editor-fold defaultstate="collapsed" desc="BV_EXPANSION_CMD">
        {
            memset(&billValidator.id, 0, sizeof(billValidator.id));
            switch(billValidator.expandCmd)
            {
                case LEVEL1_ID_WO_OPTIONS:
                {
                    if(isGetBVId(&billValidator.id, false))
                    {
                        billValidator.state = BV_STACKER;
                    }
                    else
                    {
                        vResetBV();
                    }
                    break;
                }
                case LEVEL2_ENABLE_FEATURE:
                {
                    if(isBVEnableFeature())
                    {
                        billValidator.state = BV_STACKER;
                    }
                    else
                    {
                        vResetBV();
                    }
                    break;
                }
                case LEVEL2_ID_W_OPTIONS:
                {
                    if(isGetBVId(&billValidator.id, true))
                    {
                        billValidator.state = LEVEL2_ENABLE_FEATURE;
                    }
                    else
                    {
                        vResetBV();
                    }
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

/******************************************************************************/

/*********************************************************************
 * Function:
 *         void vBVInit(void)
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
void vBVInit(void)
{
    billValidator.state = BV_INIT;
}

/**
 * @}
 */
#include "modemGSM.h"
//#include "driver/usart/drv_usart.h"

/*Constantes*******************************************************************/

#define LALORRAINE "La lorraine"
#define READ_AUDITS "audits"
#define RESETAUDITS "reset"
#define DEFAUTGSM "DEFAUT GSM..."

#define VERIFGSM "Verification GSM"
#define PATIENCE     "  Un instant..."

/*Defines**********************************************************************/
#define UART_GSM USART_ID_3 
#define PORT_MODEM PORTS_ID_0, PORT_CHANNEL_G
#define STAT PORT_MODEM, PORTS_BIT_POS_14
#define PWRKEY PORT_MODEM, PORTS_BIT_POS_12
#define RTS PORT_MODEM, PORTS_BIT_POS_9
#define RI PORT_MODEM, PORTS_BIT_POS_13
#define CTS PORT_MODEM, PORTS_BIT_POS_7

#define CTRL_Z 0X1A
#define CR 0X0D
#define LF 0X0A

#define GSMTOINIT (30 * SECONDE)
//#define GSMTOINIT (10 * SECONDE)
#define GSMTOCOMMAND (300 * MILLISEC)

#define ONEMINUTE 60
#define LENPHONE 16


// Set of basic AT commands
const char atc0[] = "AT"; // Every AT command starts with "AT"
const char atc1[] = "ATE0"; // Pas d'echo.
const char atc2[] = "AT+CMGF=1"; // TXT messages
char atc3[] = "AT+CMGS=\""; // sends SMS to desired number
const char atc9[] = "AT+CMGR=1"; //Read SMS
const char atc10[] = "AT+CSCS=\"GSM\"";
char atc5[] = "AT+CMGD=1,4"; // Erasing all messages from inbox
const char atc8[] = "AT+CSQ"; //QUALITY SIGNAL REPORT
const char Prompt[] = "> ";
const char CSQ[] = "+CSQ: ";
const char ok[] = "OK";

//Basic answer
const char Starting[] = "Mise en service...";

/*Structures*******************************************************************/

/**
 * \brief Enumeration des status concernant la machine d'état du GSM
 */
typedef enum __attribute__((packed))
{
    MODEM_INIT,
        MODEM_AUTOBAUD,
        MODEM_ECHO,
        MODEM_TEXT,
        MODEM_ERASE_MSG,
        MODEM_SMS_FORMAT,
        MODEM_FACTORY_SETTING,
        MODEM_SEND_SMS,
        MODEM_READ_SMS,
        MODEM_IDLE,
        MODEM_RECHECK,
}
MODEM_STATUS;

/*Variables********************************************************************/

/**
 * \brief structure contenant les variables du modem GSM
 */
struct
{
    bool isGSMChecked;
    bool isTaskGSMChecked;
    bool isAudits;
    bool isData;
    bool isReady;
    bool isTOInit;
    bool isAnswerOK;
    bool isCSQ;
    bool isPromptSMSText;
    uint8_t u8OldSignalLevel;
    uint8_t u8SignalLevel;
    uint8_t u8Recheck;
    BYTE byGPUSE;
    BYTE byData;
    BYTE byBuffer[32];
    BYTE byPhoneNumber[64];
    BYTE data[255];
    MODEM_STATUS state;
    DRV_HANDLE usartHandle;
    QueueHandle_t hQueueRead;
    QueueHandle_t hQueueWrite;
    TimerHandle_t hTimerTOInit;
    TaskHandle_t hTaskGSM;
    TaskHandle_t hTaskRead;
    TaskHandle_t hTaskWrite;
    TaskHandle_t hTaskRing;
} modem;

/*********************************************************************
 * Function:        void vTOInit(const TimerHandle_t HandleTimer)
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
static void vTOInit(const TimerHandle_t HandleTimer)
{
    modem.isTOInit = true;
}

/*********************************************************************
 * Function:        static void vPrintDefaultGMS(void)
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
static void vPrintDefaultGMS(void)
{
    if(!modem.isGSMChecked)
    {
        vLCD_Clear();
        printf("%s", DEFAUTGSM);
        delayMs(1000);
        if(!modem.isGSMChecked)
        {
            modem.isGSMChecked = true;
        }
    }
}

/*********************************************************************
 * Function:        static void vModemSendCommand(const char* str)
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
static void vModemSendCommand(const char* str)
{
    BYTE byData;
    while(*str)
    {
        byData = *str++;
        xQueueSendToBack(modem.hQueueWrite, &byData, 1 * SECONDE);
    }
    byData = CR;
    xQueueSendToBack(modem.hQueueWrite, &byData, 1 * SECONDE);
}

/*********************************************************************
 * Function:        static void vModemWrite(void)
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
static void vModemWrite(void)
{
    BYTE byData;
    while(1)
    {
        xQueueReceive(modem.hQueueWrite, &byData, portMAX_DELAY);
        DRV_USART_WriteByte(DRV_USART_INDEX_0, byData);
    }
}

/*********************************************************************
 * Function:        static void vModemRead(void)
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
static void vModemRead(void)
{
    BYTE byData;
    BYTE u8Index = 0;
    uint8_t u8IndexData = 0;
    while(1)
    {
        xQueueReceive(modem.hQueueRead, &byData, portMAX_DELAY);

        modem.byBuffer[u8Index++] = byData;
        if(modem.isData)
        {
            modem.data[u8IndexData++] = byData;
        }
        if(byData > 0X7F)
        {
            memset(modem.byBuffer, 0, sizeof(modem.byBuffer));
            delayMs(100);
            u8Index = 0;
        }
        else
        {
            if(strstr(modem.byBuffer, Prompt))
            {
                modem.isPromptSMSText = true;
                memset(modem.byBuffer, 0, sizeof(modem.byBuffer));
                byData = 0;
                u8Index = 0;
            }

            if(byData == 0x0A)
            {
                if(strstr(modem.byBuffer, CSQ))
                {
                    modem.u8SignalLevel = (((modem.byBuffer[6] - 0x30) * 10) +
                                           (modem.byBuffer[7] - 0x30));
                    modem.isCSQ = true;
                }
                if(strstr(modem.byBuffer, ok))
                {
                    modem.isAnswerOK = true;
                    u8IndexData = 0;
                }

                memset(modem.byBuffer, 0, sizeof(modem.byBuffer));
                byData = 0;
                u8Index = 0;
            };
        };
    }
}

/*********************************************************************
 * Function:        static void vComposePhoneNumber(char* cNumber)
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
static void vComposePhoneNumber(char* cNumber)
{
    memset(&modem.byPhoneNumber, 0, sizeof(modem.byPhoneNumber));
    sprintf(modem.byPhoneNumber, "%s%s\"", atc3, cNumber);
    //sprintf(modem.byPhoneNumber, "%s%s\"", atc3, "0033651604047");
    //----------------
}

/*********************************************************************
 * Function:        static void vSendAudit(bool isToBeReseted)
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
static void vSendAudit(bool isToBeReseted)
{
    uint32_t u32Amount = 0;
    uint8_t u8Index;
    char buffer[255];
    for(u8Index = 0; u8Index < NUMBERCHANNELSCG; u8Index++)
    {
        u32Amount += getAuditValue((uint32_t)(ADDRESSCGIN +
                                              (u8Index * sizeof(uint32_t))));
    }
    sprintf(buffer, "%c%cPièces recues: %.2f E%c%c", CR, LF,
            (double)(u32Amount) / getMDBCurrencyDivider(), CR, LF);

    u32Amount = 0;
    for(u8Index = 0; u8Index < NUMBERCHANNELSCG; u8Index++)
    {
        u32Amount += getAuditValue((uint32_t)(ADDRESSCGOUT +
                                              (u8Index * sizeof(uint32_t))));
    }
    sprintf(buffer, "%sPièces rendues: %.2f E%c%c", buffer,
            (double)(u32Amount) / getMDBCurrencyDivider(), CR, LF);

    u32Amount = 0;
    for(u8Index = 0; u8Index < NUMBERCHANNELSBV; u8Index++)
    {
        u32Amount += getAuditValue((uint32_t)(ADDRESSBVIN +
                                              (u8Index * sizeof(uint32_t))));
    }
    sprintf(buffer, "%sBillets recus: %.2f E%c%c", buffer,
            (double)(u32Amount) / getMDBCurrencyDivider(), CR, LF);
    sprintf(buffer, "%sTrop percu: %.2f E%c%c", buffer,
            (double)(getAuditValue(ADDRESSOVERPAY)) / getMDBCurrencyDivider(), CR, LF);

    u32Amount = 0;
    for(u8Index = 0; u8Index < NUMBERCHANNELSCG; u8Index++)
    {
        u32Amount += getAuditValue((uint32_t)(ADDRESSCGIN +
                                              (u8Index * sizeof(uint32_t))));
    }
    for(u8Index = 0; u8Index < NUMBERCHANNELSBV; u8Index++)
    {
        u32Amount += getAuditValue((uint32_t)(ADDRESSBVIN +
                                              (u8Index * sizeof(uint32_t))));
    }

    for(u8Index = 0; u8Index < NUMBERCHANNELSCG; u8Index++)
    {
        u32Amount -= getAuditValue((uint32_t)(ADDRESSCGOUT +
                                              (u8Index * sizeof(uint32_t))));
    }
    sprintf(buffer, "%sTotal: %.2f E%c%c%c%c", buffer,
            (double)(u32Amount) / getMDBCurrencyDivider(), CR, LF, CR, LF);
    if(isToBeReseted)
    {
        RAZAudits();
        sprintf(buffer, "%s%s%c%c", buffer, "RAZ effectuée.", CR, LF);
    }
    modem.isAudits = true;
    vSendSMS(buffer);
}

/******************************************************************************/

/*********************************************************************
 * Function:        static void vTaskRing(void)
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
static void vGSMTaskRing(void)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        if(!SYS_PORTS_PinRead(RI))
        {
            if(modem.isReady)
            {
                delayMs(100);
                modem.state = MODEM_READ_SMS;
            }
            else
            {
                if(modem.byGPUSE)
                {
                    --modem.byGPUSE;
                }
            }
        }
        vTaskDelayUntil(&xLastWakeTime, 50);
    }
}

/*********************************************************************
 * Function:        static void vGSMTask(void)
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
static void vGSMTask(void)
{
    BYTE byRetry;
    bool isOneMsgErased;
    BYTE byPhoneNumber[LENPHONE];
    while(1)
    {
        switch(modem.state)
        {
            case MODEM_INIT:
                // <editor-fold desc="MODEM_INIT"> 
            {
                byRetry = 3;
                if(!modem.hQueueRead)
                {
                    modem.hQueueRead = xQueueCreate(32, sizeof(BYTE));
                }
                if(!modem.hQueueWrite)
                {
                    modem.hQueueWrite = xQueueCreate(8, sizeof(BYTE));
                }
                if(!modem.hTimerTOInit)
                {
                    modem.hTimerTOInit = xTimerCreate((const char * const)"INIT_GSM",
                                                      GSMTOINIT, pdFALSE, NULL,
                                                      vTOInit);
                }
                if(modem.hTaskRead == NULL)
                {
                    xTaskCreate((TaskFunction_t)vModemRead, "TSK MODEMREAD", 512, NULL, 3, modem.hTaskRead);
                }
                if(modem.hTaskWrite == NULL)
                {
                    xTaskCreate((TaskFunction_t)vModemWrite, "TSK MODEMWRITE", 512, NULL, 3, modem.hTaskWrite);
                }
                GSM_PWRKEYOff();
                vLCD_Clear();
                printf("%s", VERIFGSM);
                vLCDGotoXY(1, 2);
                printf("%s", PATIENCE);
                delayMs(2500);
                do
                {
                    modem.byGPUSE = 1;
                    modem.isTOInit = false;
                    xTimerStart(modem.hTimerTOInit, 60 * SECONDE);

                    GSM_PWRKEYOn();
                    delayMs(1100);
                    while(!GSM_STATStateGet() && !modem.isTOInit);

                    GSM_PWRKEYOff();

                    //Pulse              
                    if(!modem.isTOInit)
                    {
                        while(GSM_RIStateGet() && !modem.isTOInit);
                    }
                    delayMs(10);
                    modem.isTOInit = GSM_RIStateGet();
                    if(!modem.isTOInit)
                    {
                        while(!GSM_RIStateGet() && !modem.isTOInit);
                    }
                    if(modem.hTaskRing == NULL)
                    {
                        xTaskCreate((TaskFunction_t)vGSMTaskRing, "TSK RING", 512, NULL, 5, modem.hTaskRing);
                    }
                }while(--byRetry && modem.isTOInit);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);

                if(!modem.isTOInit)
                {
                    modem.state = MODEM_AUTOBAUD;
                }
                else
                {
                    vPrintDefaultGMS();
                    modem.u8Recheck = ONEMINUTE;
                    modem.state = MODEM_RECHECK;
                }
                break;
            }// </editor-fold>

            case MODEM_AUTOBAUD:
                // <editor-fold desc="MODEM_AUTOBAUD">
            {
                memset(modem.byBuffer, 0, sizeof(modem.byBuffer));
                modem.isTOInit = false;
                modem.isAnswerOK = false;
                xTimerChangePeriod(modem.hTimerTOInit, GSMTOCOMMAND, 60 * SECONDE);
                vModemSendCommand(atc0);

                while(!modem.isAnswerOK && !modem.isTOInit);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                modem.state = MODEM_ECHO;
                break;
            }// </editor-fold>

            case MODEM_ECHO:
                // <editor-fold defaultstate="collapsed" desc="MODEM_ECHO">
            {
                modem.isAnswerOK = false;
                xTimerStart(modem.hTimerTOInit, 60 * SECONDE);
                vModemSendCommand(atc1);
                
                while(!modem.isAnswerOK && !modem.isTOInit);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                
                
                if(modem.isTOInit)
                {
                    modem.u8Recheck = ONEMINUTE;
                    modem.state = MODEM_RECHECK;
                }
                else
                {
                    modem.state = MODEM_TEXT;
                }
                break;
            }// </editor-fold>

            case MODEM_TEXT:
                // <editor-fold desc="MODEM_TEXT"> 
            {
                modem.isAnswerOK = false;
                xTimerStart(modem.hTimerTOInit, 60 * SECONDE);
                vModemSendCommand(atc2);
                while(!modem.isAnswerOK && !modem.isTOInit);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                //En cas d'absence de la carte sim, on continura l'initialisation
                if(modem.isTOInit)
                {
                    vPrintDefaultGMS();
                    modem.u8Recheck = ONEMINUTE;
                    modem.state = MODEM_RECHECK;
                }
                else
                {
                    modem.state = MODEM_ERASE_MSG;
                }
                break;
            }// </editor-fold>

            case MODEM_ERASE_MSG:
                // <editor-fold desc="SEL"> 
            {
                for(modem.byGPUSE = '1'; modem.byGPUSE < '4'; modem.byGPUSE++)
                {
                    delayMs(500);
                    atc5[8] = modem.byGPUSE;
                    modem.isAnswerOK = false;
                    modem.isTOInit = false;
                    xTimerStart(modem.hTimerTOInit, 60 * SECONDE);
                    vModemSendCommand(atc5);
                    while(!modem.isAnswerOK && !modem.isTOInit);
                    if(!isOneMsgErased)
                    {
                        isOneMsgErased = !modem.isTOInit;
                    }
                }
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                if((modem.isTOInit = !isOneMsgErased) && modem.isGSMChecked)
                {
                    modem.u8Recheck = ONEMINUTE;
                    modem.state = MODEM_RECHECK;
                }
                else
                {
                    modem.state = MODEM_IDLE;
                }
                atc5[8] = '1';
                break;
            }// </editor-fold>


            case MODEM_SEND_SMS:
                // <editor-fold defaultstate="collapsed" desc="MODEM_SEND_SMS">                      
            {
                modem.isData = false;
                for(modem.byGPUSE = 0; modem.byGPUSE < NUM_PHONE; modem.byGPUSE++)
                {
                    modem.isPromptSMSText = false;
                    if(modem.isAudits ? getIsCallEnable(modem.byGPUSE, true) :
                       getIsCallEnable(modem.byGPUSE, false))
                    {
                        modem.isAnswerOK = false;
                        xTimerStart(modem.hTimerTOInit, 60 * SECONDE);
                        vModemSendCommand(atc10);
                        while(!modem.isAnswerOK && !modem.isTOInit);
                        if(!modem.isTOInit)
                        {
                            memset(byPhoneNumber, sizeof(byPhoneNumber), 0);
                            getPhoneNumber(modem.byGPUSE, byPhoneNumber);
                            vComposePhoneNumber(byPhoneNumber);
                            modem.isTOInit = false;
                            xTimerStart(modem.hTimerTOInit, 60 * SECONDE);
                            vModemSendCommand(modem.byPhoneNumber);
                            while(!modem.isPromptSMSText && !modem.isTOInit);
                        }
                        if(!modem.isTOInit)
                        {
                            modem.isAnswerOK = false;
                            xTimerChangePeriod(modem.hTimerTOInit, 12000, 60 * SECONDE);
                            vModemSendCommand(modem.data);
                            while(!modem.isAnswerOK && !modem.isTOInit);
                            if(modem.isTOInit)
                            {
                                vPrintDefaultGMS();
                                taskYIELD();
                            }
                        }
                    }
                }
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                modem.isTOInit = false;
                modem.u8OldSignalLevel = 0;
                modem.state = MODEM_ERASE_MSG;
                break;
            }
                // </editor-fold>

            case MODEM_READ_SMS:
                // <editor-fold defaultstate="collapsed" desc="MODEM_READ_SMS">
            {
                modem.isAnswerOK = false;
                modem.isData = true;
                vModemSendCommand(atc9);
                memset(modem.data, 0, sizeof(modem.data));
                while(!modem.isAnswerOK);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                byRetry = 0;
                while(!modem.data[byRetry++]);
                memmove(modem.data, &modem.data[byRetry], sizeof(modem.data) - byRetry);
                if(strstr(modem.data, RESETAUDITS) != NULL)
                {
                    vSendAudit(true);
                }
                if(strstr(modem.data, READ_AUDITS) != NULL)
                {
                    vSendAudit(false);
                }
                break;
            }
                // </editor-fold>


            case MODEM_IDLE:
                // <editor-fold desc="MODEM_IDLE"> 
            {
                modem.isCSQ = false;
                modem.isAnswerOK = false;
                if(!modem.isGSMChecked)
                {
                    modem.isGSMChecked = true;
                }

                xTimerChangePeriod(modem.hTimerTOInit, GSMTOCOMMAND, 60 * SECONDE);
                vModemSendCommand(atc8);
                while(!modem.isCSQ && !modem.isAnswerOK && !modem.isTOInit);
                xTimerStop(modem.hTimerTOInit, 60 * SECONDE);
                if(!modem.isTOInit)
                {
                    if(modem.u8OldSignalLevel != modem.u8SignalLevel)
                    {
                        vLCDGotoXY(16, 2);
                        modem.u8OldSignalLevel = modem.u8SignalLevel;
                        if(modem.u8SignalLevel && modem.u8SignalLevel < 32)
                        {
                            printf("%c", ((modem.u8SignalLevel - 2) / 6) + 1);
                        }
                        else
                        {
                            printf("%c", ' ');
                        }
                    }
                    if(!modem.isReady)
                    {
                        modem.isReady = true;
                        vSendSMS(Starting);
                    }
                }
                break;
            }// </editor-fold>

            case MODEM_RECHECK:
                // <editor-fold desc="MODEM_RECHECK"> 
            {
                if(0 == --modem.u8Recheck)
                {
                    modem.state = MODEM_AUTOBAUD;
                }
                break;
            }// </editor-fold>
            default:
            {
                break;
            }
        }
        vTaskDelay(1 * SECONDE);
    }
}

/*********************************************************************
 * Function:        QueueHandle_t getHandleQueueRead(void)
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
QueueHandle_t getHandleQueueRead(void)
{
    return modem.hQueueRead;
}

/*********************************************************************
 * Function:        bool isGSMChecked(void)
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
bool isGSMChecked(void)
{
    return modem.isGSMChecked;
}

/*********************************************************************
 * Function:        TaskHandle_t getGSMTaskHandle(void)
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
TaskHandle_t getGSMTaskHandle(void)
{
    return modem.hTaskGSM;
}

/*********************************************************************
 * Function:        void vSendSMS(char *msg)
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
void vSendSMS(const char *msg)
{
    if(modem.isReady)
    {
        sprintf(modem.data, "v%s%c%c%s %u%c%c%s%c", VERSION, CR, LF, LALORRAINE,
                getSerialNumber(), CR, LF, msg, CTRL_Z);
        modem.state = MODEM_SEND_SMS;
    }
    else
    {
        modem.state = MODEM_IDLE;
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:        void vGSMInit(void)
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
void vGSMInit(void)
{
    if(MODEMStateGet())
    {
        modem.isAudits = false;
        modem.isData = false;
        modem.isReady = false;
        modem.isTOInit = false;
        modem.isGSMChecked = false;
        modem.state = MODEM_INIT;
        xTaskCreate((TaskFunction_t)vGSMTask, "TSK GSM", 512, NULL, 2, modem.hTaskGSM);
    }
    else
    {
        modem.isGSMChecked = true;
    }

}
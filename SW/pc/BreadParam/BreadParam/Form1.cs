/**
 * BreadParam
 * Gestion de l'audit et des paramètres de la carte BreadMachine.
 * 
 * Release
 * Version 1.1 
 * Date 2017 04 11
 * Extension des téléphones à 13 chiffres (international)
 * 
 * Version 1.2
 * Date 2017 04 14
 * Detection des ports de communication en temps réel.
 * (Permet la connection de la prise USB après le lancement du programme.)
 * 
 * Version 1.3
 * Date 2017 04 27
 * Les numéros de téléphone repassent à 10 chiffres.
 * 
 * Version 1.5
 * Date 2017 06 05
 * Mise en place de la vérification de la lecture avant l'écriture.
 * 
 * Version 1.6
 * Date 2017 06 09
 * Vérification de l'enregistrement des paramètres.
 **/

using System;
using System.Threading;
using System.Windows.Forms;
using System.Text;
using System.Globalization;

namespace BreadParam
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// Longueur maximum du numéro de téléphone
        /// </summary>
        const Byte lenPhoneNumber = 13;

        /// <summary>
        /// Buffer à usage général.
        /// </summary>
        byte[] byBuffer;

        /// <summary>
        /// Flag correspondant à la lecture de la carte.
        /// </summary>
        bool isParametersReaded;

        /// <summary>
        /// Flag indiquant une modification
        /// </summary>
        bool isParametersModified;

        /// <summary>
        /// Tableau contenant la valeur des pièces acceptées par le changeur.
        /// </summary>
        uint[] coinsValue;

        /// <summary>
        /// Tableau contant la valeur des billets acceptés par le lecteur de billets.
        /// </summary>
        uint[] billsValue;

        /// <summary>
        /// Header indiquant les paramètres en cours de transmission 
        /// </summary>
        enum HEADER
        {
            NONE,
            SERIAL,
            ENABLEGC,
            ENABLEBV,
            TROPPERCU,
            TOCUMUL,
            PRODUITPRIX,
            PHONE,
            TRAP = 12,
            AUDITS = 0XAA,
            RAZAUDITS = 0X55,
            GETPARAMS = 0X5A,
            SAVE_PARAM = 0XA5
        };

        /// <summary>
        /// Réponse de la CPU.
        /// </summary>
        enum ANSWER
        {
            ACK = 0X00,
            NACK = 0XFF,
        }

        /// <summary>
        /// Constructeur de la form
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            coinsValue = new uint[8];
            billsValue = new uint[8];
        }


        /// <summary>
        /// Vérifie que le port série est ouvert.
        /// </summary>
        /// <returns>
        /// true si le port est ouvert.
        /// </returns>

        private bool IsSerialPortOpen()
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    throw new Exception(BreadParam.Properties.Resources.Str_Serial_Port_Select);
                }
                uint num = Convert.ToUInt32(MachineID.Text, CultureInfo.CurrentCulture);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
                throw;
            }
            return true;
        }

        /// <summary>
        /// Quitte le programme.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// Quitte le programme par le menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void QuitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BtnExit_Click(sender, e);
        }

        /// <summary>
        /// Pendant le chargement de la fenêtre.
        /// Fixe la hauteur de la fenêtre du programme pour cacher les audits
        /// Recherche tous les ports séries disponibles
        /// Remplit les tableaux avec des valeurs par défaut.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            //this.Height = 425;
            isParametersReaded = false;
            CBSerialPorts.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            for (int byIndex = 1; byIndex < 9; byIndex++)
            {
                dataGridViewCG.Rows.Add(byIndex, true, string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0)));
                dataGridViewBV.Rows.Add(byIndex, true, string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditCGIN.Rows.Add(byIndex, string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditCGOUT.Rows.Add(byIndex, string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditBV.Rows.Add(byIndex, string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0)));
            }
            for (int byIndex = 1; byIndex < 4; byIndex++)
            {
                dataGridViewPrice.Rows.Add(byIndex, string.Format(CultureInfo.CurrentCulture, "{0:F2}", 0.00), string.Format(CultureInfo.CurrentCulture, "{0:F2}", 0.00));
                dataGridViewAuditProduit.Rows.Add(byIndex, 0);
            }
            for (int byIndex = 0; byIndex < 6; byIndex++)
            {
                dataGridViewTelephone.Rows.Add(false, false, "0033612345678");
            }
            isParametersReaded = isParametersModified = false;
            timer1.Enabled = true;
        }

        /// <summary>
        /// Calcul du checksum du buffer
        /// </summary>
        /// <param name="byLength">Nombre d'octet dans le buffer à additionner.</param>
        /// <returns>
        /// La somme des octets modulo 256.
        /// </returns>
        //byte ByCheckSum(byte byLength)
        //{
        //    UInt16 ui16Result = 0;
        //    for (int byIndex = 0; byIndex < byLength; byIndex++)
        //    {
        //        ui16Result += byBuffer[byIndex];
        //    }
        //    return Convert.ToByte((ui16Result % 256));
        //}


        /// <summary>
        /// Envoie les paramètres à la cpu.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void BtnSave_Click(object sender, EventArgs e)
        {
            Int32 value;
            try
            {
                if (IsSerialPortOpen() && (MessageBox.Show(BreadParam.Properties.Resources.Str_Confirm_modify_param, BreadParam.Properties.Resources.Str_Confirm, MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK))
                {
                    if (!isParametersReaded)
                    {
                        throw new Exception(BreadParam.Properties.Resources.Str_Fail_save);
                    }
                    serialPort1.DiscardOutBuffer();
                    serialPort1.DiscardInBuffer();

                    byte[] byParamSave = { Convert.ToByte(HEADER.SAVE_PARAM, CultureInfo.CurrentCulture) };
                    serialPort1.Write(byParamSave, 0, 1);
                    byParamSave[0] = Convert.ToByte(serialPort1.ReadByte());
                    if (byParamSave[0] == 0X5A)
                    {
                        //Envoie l'identification de la machine.
                        byBuffer = new byte[4];
                        value = Int32.Parse(MachineID.Text, CultureInfo.CurrentCulture);
                        byBuffer[0] = Convert.ToByte(value % 0x100);
                        byBuffer[1] = Convert.ToByte(value / 0x100);
                        byBuffer[2] = Convert.ToByte(value / 0x10000);
                        byBuffer[3] = Convert.ToByte(value / 0x1000000);
                        serialPort1.Write((byte[])byBuffer, 0, 4);

                        //Envoie les prix en cash
                        byBuffer = new byte[12];
                        for (int i = 0; i < 3; i++)
                        {
                            value = (Int32)(Convert.ToDouble(dataGridViewPrice["Prix", i].Value, CultureInfo.CurrentCulture) * 100);
                            byBuffer[4 * i + 0] = Convert.ToByte(value % 0x100, CultureInfo.CurrentCulture);
                            byBuffer[4 * i + 1] = Convert.ToByte(value / 0x100, CultureInfo.CurrentCulture);
                            byBuffer[4 * i + 2] = Convert.ToByte(value / 0x10000, CultureInfo.CurrentCulture);
                            byBuffer[4 * i + 3] = Convert.ToByte(value / 0x1000000, CultureInfo.CurrentCulture);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 12);

                        //Envoie les prix cashless
                        byBuffer = new byte[12];
                        for (int i = 0; i < 3; i++)
                        {
                            value = (Int32)(Convert.ToDouble(dataGridViewPrice["CashLess", i].Value, CultureInfo.CurrentCulture) * 100);
                            byBuffer[4 * i + 0] = Convert.ToByte(value % 0x100);
                            byBuffer[4 * i + 1] = Convert.ToByte(value / 0x100);
                            byBuffer[4 * i + 2] = Convert.ToByte(value / 0x10000);
                            byBuffer[4 * i + 3] = Convert.ToByte(value / 0x1000000);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 12);

                        //Envoi les informations des téléphones.
                        byBuffer = new byte[360];
                        for (int i = 0; i < 6; i++)
                        {
                            byte[] array1 = Encoding.ASCII.GetBytes(dataGridViewTelephone["Numero", i].Value.ToString().Trim());
                            byte[] array2 = new byte[13];
                            int j;
                            for (j = 0; j < 13 - array1.Length; j++)
                            {
                                array2[j] = 0x20;
                            }

                            for (int k = j; k < 13; k++)
                            {
                                array2[k] = array1[k - j];
                            }
                            for (j = 0; j < 13; j++)
                            {
                                byBuffer[60 * i + (j * 4)] = Convert.ToByte(array2[j]);// - 0x30);
                            }
                            byBuffer[(60 * (i + 1)) - 8] = Convert.ToByte(dataGridViewTelephone["EnableAudit", i].Value, CultureInfo.CurrentCulture);
                            byBuffer[(60 * (i + 1)) - 4] = Convert.ToByte(dataGridViewTelephone["EnableAlarm", i].Value, CultureInfo.CurrentCulture);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 360);

                        //Envoi les valeurs de sécurité.
                        byBuffer = new byte[12];
                        for (int i = 0; i < 3; i++)
                        {
                            byBuffer[(i * 4) + 0] = Convert.ToByte(Trap1UpDown.Value % 0x100);
                            byBuffer[(i * 4) + 1] = Convert.ToByte(Trap1UpDown.Value / 0x100);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 12);

                        //Envoi du délai de cumul
                        byBuffer = new byte[4];
                        for (int i = 0; i < 4; i++)
                        {
                            byBuffer[0] = Convert.ToByte(numericCumul.Value);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 4);

                        //Envoi la valeur du TO overpay.
                        byBuffer = new byte[4];
                        for (int i = 0; i < 4; i++)
                        {
                            byBuffer[0] = Convert.ToByte(TOUpDown.Value);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 4);

                        //Envoi les habilitations des périphériques.
                        byBuffer = new byte[4];
                        for (byte i = 0; i < 8; i++)
                        {
                            byBuffer[0] += Convert.ToByte(Convert.ToByte(dataGridViewCG["EnableCG", i].Value, CultureInfo.CurrentCulture) << i, CultureInfo.CurrentCulture);
                            byBuffer[2] += Convert.ToByte(Convert.ToByte(dataGridViewBV["EnableBV", i].Value, CultureInfo.CurrentCulture) << i, CultureInfo.CurrentCulture);
                        }
                        serialPort1.Write((byte[])byBuffer, 0, 4);

                        //Envoi les valeurs des commandes de températures.
                        byBuffer = new byte[8];
                        byBuffer[0] = Convert.ToByte(UDHot.Value);
                        byBuffer[4] = Convert.ToByte(UDCold.Value);
                        serialPort1.Write((byte[])byBuffer, 0, 8);
                        MessageBox.Show(BreadParam.Properties.Resources.Str_param_saved, BreadParam.Properties.Resources.Str_Record, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    BtnRead_Click(sender, e);
                    isParametersModified = false;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }


        /// <summary>
        /// Vérifie la cohérence du numéro de la machine.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void MachineID_Leave(object sender, EventArgs e)
        {
            try
            {
                if (!Int32.TryParse(MachineID.Text, out Int32 usResult))
                {
                    throw new Exception(string.Format(CultureInfo.CurrentCulture, BreadParam.Properties.Resources.Str_Number_Machine_Error, Int32.MaxValue));
                }
            }
            catch (Exception exception)
            {
                MachineID.Text = BreadParam.Properties.Resources.Str_zero;
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                ((TextBox)sender).Select();
                ((TextBox)sender).SelectAll();
                throw;
            }
        }


        /// <summary>
        /// Affiche la partie inférieur pour montrer les audits.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void BtnAudit_Click(object sender, EventArgs e)
        {
            int byLength;
            byte[] byBuffer;
            Double TotalAmountInCG = 0;
            Double TotalAmountOutCG = 0;
            Double TotalAmountInBv = 0;
            Double OverPay;
            Double CashLess;
            try
            {
                if (IsSerialPortOpen())
                {
                    serialPort1.DiscardOutBuffer();
                    serialPort1.DiscardInBuffer();

                    byte[] byAuditRequest = { Convert.ToByte(HEADER.AUDITS, CultureInfo.CurrentCulture) };
                    serialPort1.Write(byAuditRequest, 0, 1);
                    byLength = 0;
                    byBuffer = new byte[sizeof(uint)];
                    for (int i = 0; i < sizeof(uint); i++)
                    {
                        byBuffer[i] = Convert.ToByte(serialPort1.ReadByte(), CultureInfo.CurrentCulture);
                    }
                    byLength = byBuffer[0] + (byBuffer[1] * 100) + (byBuffer[2] * 10000) + (byBuffer[3] * 1000000);
                    byBuffer = new byte[byLength];
                    for (int byIndex = 0; byIndex < byLength; byIndex++)
                    {
                        byBuffer[byIndex] = Convert.ToByte(serialPort1.ReadByte());
                    }
                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditCGIN["MontantInCG", byIndex].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}",
                            Convert.ToDouble(byBuffer[byIndex * 4] + (byBuffer[(byIndex * 4) + 1] * 0X100) +
                            (byBuffer[(byIndex * 4) + 2] * 0X10000) + (byBuffer[(byIndex * 4) + 3] * 0X1000000)) * coinsValue[byIndex] / 100);
                        TotalAmountInCG += Convert.ToDouble(byBuffer[byIndex * 4] + (byBuffer[(byIndex * 4) + 1] * 0X100) +
                            (byBuffer[(byIndex * 4) + 2] * 0X10000) + (byBuffer[(byIndex * 4) + 3] * 0X1000000)) * coinsValue[byIndex] / 100;
                    }
                    TotalInCG.Text = string.Format(CultureInfo.CurrentCulture, "{0:F2}", TotalAmountInCG);

                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditCGOUT["MontantOutCG", byIndex].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}",
                            Convert.ToDouble(byBuffer[32 + (byIndex * 4)] + (byBuffer[32 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[32 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[32 + (byIndex * 4) + 3] * 0X1000000)) * coinsValue[byIndex] / 100);
                        TotalAmountOutCG += Convert.ToDouble(byBuffer[32 + (byIndex * 4)] + (byBuffer[32 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[32 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[32 + (byIndex * 4) + 3] * 0X1000000)) * coinsValue[byIndex] / 100;
                    }
                    TotalOutCG.Text = string.Format(CultureInfo.CurrentCulture, "{0:F2}", TotalAmountOutCG);

                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditBV["MontantInBV", byIndex].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}",
                            Convert.ToDouble(byBuffer[64 + (byIndex * 4)] + (byBuffer[64 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[64 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[64 + (byIndex * 4) + 3] * 0X1000000)) * billsValue[byIndex] / 100);
                        TotalAmountInBv += Convert.ToDouble(byBuffer[64 + (byIndex * 4)] + (byBuffer[64 + ((byIndex * 4) + 1)] * 0X100) +
                         (byBuffer[64 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[64 + (byIndex * 4) + 3] * 0X1000000)) * billsValue[byIndex] / 100;
                    }
                    TotalInBV.Text = string.Format(CultureInfo.CurrentCulture, "{0:F2}", TotalAmountInBv);

                    for (int byIndex = 0; byIndex < 3; byIndex++)
                    {
                        dataGridViewAuditProduit["NumProduitAudit", byIndex].Value = string.Format(CultureInfo.CurrentCulture, "{0:d}", byBuffer[96 + (byIndex * 4)] +
                            (byBuffer[96 + ((byIndex * 4) + 1)] * 0X100) + (byBuffer[96 + (byIndex * 4) + 2] * 0X10000) +
                            (byBuffer[96 + (byIndex * 4) + 3] * 0X1000000));
                    }

                    OverPay = Convert.ToDouble(byBuffer[108] + (byBuffer[109] * 0X100) + (byBuffer[110] * 0X10000) + (byBuffer[111] * 0X1000000)) / 100;
                    LOverPay.Text = string.Format(CultureInfo.CurrentCulture, "{0:F2}", OverPay);
                    CashLess = Convert.ToDouble(byBuffer[112] + (byBuffer[113] * 0X100) + (byBuffer[114] * 0X10000) + (byBuffer[115] * 0X1000000));
                    lCashLess.Text = string.Format(CultureInfo.CurrentCulture, "{0:F2}", CashLess);
                    Total.Text = String.Format(CultureInfo.CurrentCulture, "{0:F2}", TotalAmountInCG + TotalAmountInBv + OverPay /*+ InCash*/ - TotalAmountOutCG);

                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }


        /// <summary>
        /// Vérifie la saisie d'une valeur monétaire.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void DataGridView_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            string sResult;
            if ((((DataGridView)sender).CurrentCell.ColumnIndex == 1) || (((DataGridView)sender).CurrentCell.ColumnIndex == 2))
            {
                try
                {
                    sResult = ((DataGridView)sender).CurrentCell.Value.ToString().Replace('.', ',');
                    if (!double.TryParse(sResult, out double dResult))
                    {
                        throw new Exception(BreadParam.Properties.Resources.Str_Incorrect_Entry);
                        //MessageBox.Show("Entrée incorrecte!!!", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        ((DataGridView)sender).CurrentCell.Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", dResult);
                    }
                }
                catch (Exception exception)
                {
                    MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    throw;
                }
            }
        }


        /// <summary>
        /// Vérifie la cohérence d'un numéro de téléphone saisie
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void DataGridViewTelephone_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            string sResult;
            try
            {
                if (((DataGridView)sender).CurrentCell.ColumnIndex == 2)
                {
                    sResult = ((DataGridView)sender).CurrentCell.Value.ToString().Replace(" ", "");
                    sResult = sResult.Replace(".", "");
                    if ((sResult.Length > lenPhoneNumber) || (sResult.Length < 6))
                    {
                        throw new Exception(BreadParam.Properties.Resources.Str_Phone_Number_Error);
                    }
                    foreach (char car in sResult)
                    {
                        if (!byte.TryParse(car.ToString(CultureInfo.CurrentCulture), out byte chiffre))
                        {
                            throw new Exception(BreadParam.Properties.Resources.Str_Phone_Car_Error);
                        }
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                ((DataGridView)sender)[0, ((DataGridView)sender).CurrentCell.RowIndex].Value = false;
                ((DataGridView)sender)[1, ((DataGridView)sender).CurrentCell.RowIndex].Value = false;
                ((DataGridView)sender).CurrentCell.Value = "06 12 34 56 78";
                throw;
            }
        }


        /// <summary>
        /// Ouvre le port série choisi.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void CBSerialPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (CBSerialPorts.SelectedIndex != -1)
                {
                    timer1.Enabled = false;
                    if (!serialPort1.IsOpen)
                    {
                        serialPort1.PortName = CBSerialPorts.SelectedItem.ToString();
                        serialPort1.Open();
                    }
                    toolStripComLabel.Text = serialPort1.PortName;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }


        /// <summary>
        /// Remet à zéro les compteurs et les envoie à la CPU.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void BtnRazAudit_Click(object sender, EventArgs e)
        {
            try
            {
                for (int byIndex = 0; byIndex < 8; byIndex++)
                {
                    dataGridViewAuditCGIN[1, byIndex].Value = dataGridViewAuditCGOUT[1, byIndex].Value =
                    dataGridViewAuditBV[1, byIndex].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(0));
                }
                for (int byIndex = 0; byIndex < 3; byIndex++)
                {
                    dataGridViewAuditProduit[1, byIndex].Value = 0;
                }
                byte[] byAuditRequest = { Convert.ToByte(HEADER.RAZAUDITS, CultureInfo.CurrentCulture) };
                serialPort1.Write(byAuditRequest, 0, 1);
                if (serialPort1.ReadByte() == 0xFF)
                {
                    BtnAudit_Click(sender, e);
                }
                MessageBox.Show(BreadParam.Properties.Resources.Str_Reset_Audit);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }


        /// <summary>
        /// Lecture des paramètres de la carte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void BtnRead_Click(object sender, EventArgs e)
        {
            int byPos;
            int dwLength;
            try
            {
                if (IsSerialPortOpen())
                {
                    byte[] byParamRequest = { Convert.ToByte(HEADER.GETPARAMS, CultureInfo.CurrentCulture) };
                    serialPort1.Write(byParamRequest, 0, 1);
                    byPos = serialPort1.ReadByte();

                    //Version FW
                    LVersionFW.Text = "";
                    for (int i = 0; i < byPos; i++)
                    {
                        LVersionFW.Text += (char)serialPort1.ReadByte();
                    }

                    //Date FW
                    LDateFW.Text = "";
                    byPos = serialPort1.ReadByte();
                    for (int i = 0; i < byPos; i++)
                    {
                        LDateFW.Text += (char)serialPort1.ReadByte();
                    }

                    //Parametres
                    byBuffer = new byte[4];
                    for (int i = 0; i < 4; i++)
                    {
                        byBuffer[i] = Convert.ToByte(serialPort1.ReadByte());
                    }
                    dwLength = byBuffer[0] + (byBuffer[1] * 0x100) + (byBuffer[2] * 0x10000) + (byBuffer[3] * 0x1000000);
                    byBuffer = new byte[dwLength];
                    for (int i = 0; i < dwLength; i++)
                    {
                        byBuffer[i] = Convert.ToByte(serialPort1.ReadByte());

                    }

                    //Identification
                    MachineID.Text = string.Format(CultureInfo.CurrentCulture, "{0,0:D}", (byBuffer[0] + (byBuffer[1] * 0x100) + (byBuffer[2] * 0x10000) + (byBuffer[3] * 0x1000000)));

                    //Activation periphériques
                    for (int i = 0; i < 8; i++)
                    {
                        dataGridViewCG["EnableCG", i].Value = (byBuffer[408] >> i) & 0X01;
                        dataGridViewBV["EnableBV", i].Value = (byBuffer[410] >> i) & 0X01;
                    }

                    //Prix
                    for (int i = 0; i < 3; i++)
                    {
                        dataGridViewPrice["Prix", i].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(byBuffer[4 * i + 4] + (byBuffer[4 * i + 5] * 0x100) + (byBuffer[4 * i + 6] * 0x10000) + (byBuffer[4 * i + 7] * 0x1000000)) / 100);
                        //CashLess
                        dataGridViewPrice["CashLess", i].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDouble(byBuffer[4 * i + 16] + (byBuffer[4 * i + 17] * 0x100) + (byBuffer[4 * i + 18] * 0x10000) + (byBuffer[4 * i + 19] * 0x1000000)) / 100);
                    }

                    //Téléphones
                    for (int i = 0; i < 6; i++)
                    {
                        string s = "";
                        for (int k = 0; k < 13; k++)
                        {
                            if ((byBuffer[(i * 60) + (28 + (k * 4))]) != 0x20)
                            {
                                s += string.Format(CultureInfo.CurrentCulture, "{0:d}", (byBuffer[(i * 60) + (28 + (k * 4))]) - 0x30);
                            }
                        }
                        dataGridViewTelephone["Numero", i].Value = s;
                        //dataGridViewTelephone["Numero", i].Value = string.Format(CultureInfo.CurrentCulture, "{0:d}{1:d}{2:d}{3:d}{4:d}{5:d}{6:d}{7:d}{8:d}{9:d}{10:d}{11:d}{12:d}",
                        //    byBuffer[i * 60 + 28] - 0x30, byBuffer[i * 60 + 32] - 0x30, byBuffer[i * 60 + 36] - 0x30, byBuffer[i * 60 + 40] - 0x30, byBuffer[i * 60 + 44] - 0x30,
                        //    byBuffer[i * 60 + 48] - 0x30, byBuffer[i * 60 + 52] - 0x30, byBuffer[i * 60 + 56] - 0x30, byBuffer[i * 60 + 60] - 0x30, byBuffer[i * 60 + 64] - 0x30,
                        //    byBuffer[i * 60 + 68] - 0x30, byBuffer[i * 60 + 72] - 0x30, byBuffer[i * 60 + 76] - 0x30);
                        dataGridViewTelephone["EnableAudit", i].Value = byBuffer[i * 60 + 80] & 0x01;
                        dataGridViewTelephone["EnableAlarm", i].Value = byBuffer[i * 60 + 84] & 0x01;
                    }

                    ///Sensibilité des trappes.
                    Trap1UpDown.Value = byBuffer[388] + (byBuffer[389] * 0x100);
                    if (Trap1UpDown.Value == 0)
                    {
                        RBAuto1.Checked = true;
                    }
                    else
                    {
                        RBFixed1.Checked = true;
                    }
                    Trap2UpDown.Value = byBuffer[392] + (byBuffer[393] * 0x100);
                    if (Trap2UpDown.Value == 0)
                    {
                        RBAuto2.Checked = true;
                    }
                    else
                    {
                        RBFixed2.Checked = true;
                    }
                    Trap3UpDown.Value = byBuffer[396] + (byBuffer[397] * 0x100);
                    if (Trap3UpDown.Value == 0)
                    {
                        RBAuto3.Checked = true;
                    }
                    else
                    {
                        RBFixed3.Checked = true;
                    }
                    TOUpDown.Value = byBuffer[400];
                    numericCumul.Value = byBuffer[404];
                    UDCold.Value = byBuffer[412];
                    UDHot.Value = byBuffer[416];
                    isParametersReaded = true;
                    isParametersModified = false;

                    for (int i = 0; i < 32; i++)
                    {
                        byBuffer[i] = Convert.ToByte(serialPort1.ReadByte(), CultureInfo.CurrentCulture);
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        coinsValue[i] = Convert.ToUInt32(byBuffer[i * 4] + (byBuffer[1 + (i * 4)] * 0x100) + (byBuffer[2 + (i * 4)] * 0x10000) + (byBuffer[3 + (i * 4)] * 0x1000000));
                        dataGridViewCG["ValueCG", i].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDecimal(coinsValue[i]) / 100);

                    }
                    for (int i = 0; i < 32; i++)
                    {
                        byBuffer[i] = Convert.ToByte(serialPort1.ReadByte(), CultureInfo.CurrentCulture);
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        billsValue[i] = Convert.ToUInt32(byBuffer[i * 4] + (byBuffer[1 + (i * 4)] * 0x100) + (byBuffer[2 + (i * 4)] * 0x10000) + (byBuffer[3 + (i * 4)] * 0x1000000));
                        dataGridViewBV["ValueBV", i].Value = string.Format(CultureInfo.CurrentCulture, "{0:F2}", Convert.ToDecimal(billsValue[i]) / 100);

                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, BreadParam.Properties.Resources.Str_Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }

        /// <summary>
        /// Vérifie la modification des ports série et corrige la liste si nécessaire.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Timer1_Tick_1(object sender, EventArgs e)
        {
            if (CBSerialPorts.Items.Count != System.IO.Ports.SerialPort.GetPortNames().Length)
            {
                CBSerialPorts.Items.Clear();
                CBSerialPorts.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            }
            for (int i = 0; i < CBSerialPorts.Items.Count; i++)
            {
                try
                {
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Close();
                    }
                    serialPort1.PortName = (string)CBSerialPorts.Items[i];
                    serialPort1.Open();

                    byte[] byCheckBoardPresence = new byte[1] { 0XAF };
                    serialPort1.Write(byCheckBoardPresence, 0, 1);
                    if ((serialPort1.Read(byCheckBoardPresence, 0, 1) == 1) && (byCheckBoardPresence[0] == 0xFA))
                    {
                        serialPort1.ReadTimeout = 5000;
                        CBSerialPorts.SelectedIndex = i;
                        Refresh();
                        BtnRead_Click(sender, e);
                        BtnAudit_Click(sender, e);
                        break;
                    }
                }
                catch (InvalidOperationException)
                {
                    throw;
                }
#pragma warning disable CA1031 // Do not catch general exception types
                catch (Exception)
                {
                    serialPort1.Close();
                }
#pragma warning restore CA1031 // Do not catch general exception types
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if ((isParametersReaded && !isParametersModified) || (MessageBox.Show(BreadParam.Properties.Resources.Str_Leave_Without_Save, BreadParam.Properties.Resources.Str_Confirm, MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK))
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                }
            }
            else
            {
                e.Cancel = true;
            }
        }

        private void RBSerialAuto_CheckedChanged(object sender, EventArgs e)
        {
            CBSerialPorts.Enabled = RBSerialFixed.Checked;
        }

        private void RBAuto1_CheckedChanged(object sender, EventArgs e)
        {
            switch (((RadioButton)sender).Name)
            {
                case "RBAuto1":
                {
                    if (((RadioButton)sender).Checked)
                    {
                        Trap1UpDown.Value = 0;
                    }
                    break;
                }
                case "RBAuto2":
                {
                    if (((RadioButton)sender).Checked)
                    {
                        Trap2UpDown.Value = 0;
                    }
                    break;
                }
                case "RBAuto3":
                {
                    if (((RadioButton)sender).Checked)
                    {
                        Trap3UpDown.Value = 0;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        private void MachineID_TextChanged(object sender, EventArgs e)
        {
            Refresh();
            isParametersModified = true;
        }

        private void Form1_Activated(object sender, EventArgs e)
        {
        }

        private void Trap1UpDown_Leave(object sender, EventArgs e)
        {
            switch (((NumericUpDown)sender).Name)
            {
                case "Trap1UpDown":
                {
                    RBFixed1.Checked = ((NumericUpDown)sender).Value > 0;
                    break;
                }
                case "Trap2UpDown":
                {
                    RBFixed2.Checked = ((NumericUpDown)sender).Value > 0;
                    break;
                }
                case "Trap3UpDown":
                {
                    RBFixed3.Checked = ((NumericUpDown)sender).Value > 0;
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
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

namespace BreadParam
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// Constante contenant le texte de l'erreur d'enreg
        /// </summary>
        const String strSaveError = "Erreur durant l'enregistrement/r/nLes paramètres ne sont pas correctement enregistrés";

        /// <summary>
        /// Longueur maximum du numéro de téléphone
        /// </summary>
        const Byte lenPhoneNumber = 16;

        /// <summary>
        /// Buffer à usage général.
        /// </summary>
        byte[] byBuffer = new byte[32];

        /// <summary>
        /// Flag correspondant à la lecture de la carte.
        /// </summary>
        bool isParametersReaded;

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
            AUDITS = 0X80,
            RAZAUDITS = 0X81,
            GETPARAMS = 0X5A,
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
                    throw new Exception("Sélectionnez un port série.");
                }
                UInt16 num = Convert.ToUInt16(MachineID.Text);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
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
            serialPort1.Close();
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
                dataGridViewCG.Rows.Add(byIndex, true, string.Format("{0:F2}", Convert.ToDouble(0)));
                dataGridViewBV.Rows.Add(byIndex, true, string.Format("{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditCGIN.Rows.Add(byIndex, string.Format("{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditCGOUT.Rows.Add(byIndex, string.Format("{0:F2}", Convert.ToDouble(0)));
                dataGridViewAuditBV.Rows.Add(byIndex, string.Format("{0:F2}", Convert.ToDouble(0)));
            }
            for (int byIndex = 1; byIndex < 4; byIndex++)
            {
                dataGridViewPrice.Rows.Add(byIndex, string.Format("{0:F2}", 0.00), string.Format("{0:F2}", 0.00));
                dataGridViewAuditProduit.Rows.Add(byIndex, 0);
            }
            for (int byIndex = 0; byIndex < 6; byIndex++)
            {
                dataGridViewTelephone.Rows.Add(false, false, "0033612345678");
            }
        }

        /// <summary>
        /// Calcul du checksum du buffer
        /// </summary>
        /// <param name="byLength">Nombre d'octet dans le buffer à additionner.</param>
        /// <returns>
        /// La somme des octets modulo 256.
        /// </returns>
        byte ByCheckSum(byte byLength)
        {
            UInt16 ui16Result = 0;
            for (int byIndex = 0; byIndex < byLength; byIndex++)
            {
                ui16Result += byBuffer[byIndex];
            }
            return (byte)(ui16Result % 256);
        }

        /// <summary>
        /// Envoie les paramètres à la cpu.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnSave_Click(object sender, EventArgs e)
        {
            byte byRepeat = 0;
            byte byLength;
            try
            {
                if (IsSerialPortOpen() && (MessageBox.Show("Etes-vous sûr de vouloir modifier les paramètres de la machine ?", "Confirmation", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK))
                {
                    if (!isParametersReaded)
                    {
                        throw new Exception("Impossible d'enregistrer les paramètres!\r\nLes paramètres enregistrés dans la CPU n'ont pas été lus.");
                    }

                    //Envoi le numéro de la machine.
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 2;
                        byBuffer[1] = (byte)HEADER.SERIAL;
                        byBuffer[2] = (byte)(Convert.ToUInt16(MachineID.Text) % 256);
                        byBuffer[3] = (byte)(Convert.ToUInt16(MachineID.Text) / 256);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }

                    //Envoi la validation des pièces.
                    if (byRepeat < 2)
                    {
                        byBuffer[0] = byLength = 1;
                        byBuffer[1] = (byte)HEADER.ENABLEGC;
                        byBuffer[2] = 0;
                        for (int byIndex = 0; byIndex < 8; byIndex++)
                        {
                            byBuffer[2] += (byte)((Convert.ToByte(dataGridViewCG["EnableCG", byIndex].Value)) << byIndex);
                        }
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }


                    //Envoie la validation des billets
                    if (byRepeat < 2)
                    {
                        //Envoi la validation des pièces.
                        byBuffer[0] = byLength = 1;
                        byBuffer[1] = (byte)HEADER.ENABLEBV;
                        byBuffer[2] = 0;
                        for (int byIndex = 0; byIndex < 8; byIndex++)
                        {
                            byBuffer[2] += (byte)((Convert.ToByte(dataGridViewBV["EnableBV", byIndex].Value)) << byIndex);
                        }
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoie le délai du trop perçu.
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 1;
                        byBuffer[1] = (byte)HEADER.TROPPERCU;
                        byBuffer[2] = Convert.ToByte(TOUpDown.Value);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoie le délai de cumul.
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 1;
                        byBuffer[1] = (byte)HEADER.TOCUMUL;
                        byBuffer[2] = Convert.ToByte(numericCumul.Value);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoie le prix dex produits
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 12;
                        byBuffer[1] = (byte)HEADER.PRODUITPRIX;
                        for (int byIndex = 0; byIndex < byLength / 2; byIndex++)
                        {
                            byBuffer[2 + (byIndex * 2)] = (byte)(((Convert.ToDouble(dataGridViewPrice["Prix", byIndex].Value) + 0.001) * 100) % 256);
                            byBuffer[3 + (byIndex * 2)] = (byte)(((Convert.ToDouble(dataGridViewPrice["Prix", byIndex].Value) + 0.01) * 100) / 256);
                        }
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoie les paramètres des telephones.
                    for (int byIndex = 0; byIndex < 5; byIndex++)
                    {
                        if (byRepeat < 2)
                        {
                            Array.Clear(byBuffer, 0, 32);
                            //Elimine les espaces
                            string sResult = Convert.ToString(dataGridViewTelephone["Numero", byIndex].Value).Replace(" ", "");
                            //Elimine les points
                            sResult = sResult.Replace(".", "");
                            byRepeat = 0;
                            //Longueur d'un numéro + les autorisations
                            byBuffer[0] = byLength = (lenPhoneNumber + 5);
                            byBuffer[1] = (byte)(HEADER.PHONE + byIndex);
                            //Autorisation des audits
                            byBuffer[2] = (byte)(Convert.ToByte(dataGridViewTelephone["EnableAudit", byIndex].Value) > 0 ? 1 : 0);
                            //Autorisation des alarmes
                            byBuffer[3] = (byte)((Convert.ToByte(dataGridViewTelephone["EnableAlarm", byIndex].Value) > 0) ? 1 : 0);
                            for (int byIndex2 = 0; byIndex2 < lenPhoneNumber; byIndex2++)
                            {
                                try
                                {
                                    byBuffer[4 + byIndex2] = (byte)sResult[byIndex2];
                                }
                                catch (Exception)
                                {
                                    break;
                                }
                            }
                            byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                            do
                            {
                                serialPort1.Write(byBuffer, 0, byLength + 3);
                                if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                                {
                                    Thread.Sleep(1000);
                                    ++byRepeat;
                                }
                            } while ((byRepeat > 0) && (byRepeat < 2));
                        }
                        else
                        {
                            throw new Exception(strSaveError);
                        }
                    }

                    //Envoi la sensibilité trappe 1
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 2;
                        byBuffer[1] = (byte)HEADER.TRAP;
                        byBuffer[2] = Convert.ToByte(Trap1UpDown.Value % 256);
                        byBuffer[3] = Convert.ToByte(Trap1UpDown.Value / 256);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoi la sensibilité trappe 2
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 2;
                        byBuffer[1] = (byte)HEADER.TRAP + 1;
                        byBuffer[2] = Convert.ToByte(Trap2UpDown.Value % 256);
                        byBuffer[3] = Convert.ToByte(Trap2UpDown.Value / 256);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    //Envoi la sensibilité trappe 3
                    if (byRepeat < 2)
                    {
                        byRepeat = 0;
                        byBuffer[0] = byLength = 2;
                        byBuffer[1] = (byte)HEADER.TRAP + 2;
                        byBuffer[2] = Convert.ToByte(Trap3UpDown.Value % 256);
                        byBuffer[3] = Convert.ToByte(Trap3UpDown.Value / 256);
                        byBuffer[byLength + 2] = ByCheckSum((byte)(byLength + 2));
                        do
                        {
                            serialPort1.Write(byBuffer, 0, byLength + 3);
                            if (!(serialPort1.ReadByte() == (byte)ANSWER.ACK))
                            {
                                Thread.Sleep(1000);
                                ++byRepeat;
                            }
                        } while ((byRepeat > 0) && (byRepeat < 2));
                    }
                    else
                    {
                        throw new Exception(strSaveError);
                    }

                    MessageBox.Show("Les nouveaux paramètres sont enregistrés.", "Enregistrement", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                if (!ushort.TryParse(MachineID.Text, out ushort usResult))
                {
                    MessageBox.Show("Le numéro de la machine doit être compris entre 0 et 65535", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Affiche la partie inférieur pour montrer les audits.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnAudit_Click(object sender, EventArgs e)
        {
            byte[] byBuffer;
            Double TotalAmountInCG = 0;
            Double TotalAmountOutCG = 0;
            Double TotalAmountInBv = 0;
            Double OverPay;
            Double InCash;
            try
            {
                if (IsSerialPortOpen())
                {
                    byte[] byAuditRequest = { (byte)HEADER.AUDITS };
                    serialPort1.Write(byAuditRequest, 0, 1);
                    byte byLength = (byte)serialPort1.ReadByte();
                    byBuffer = new byte[byLength];
                    for (int byIndex = 0; byIndex < byLength; byIndex++)
                    {
                        byBuffer[byIndex] = (byte)serialPort1.ReadByte();
                    }
                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditCGIN["MontantInCG", byIndex].Value = string.Format("{0:F2}",
                            Convert.ToDouble(byBuffer[byIndex * 4] + (byBuffer[(byIndex * 4) + 1] * 0X100) +
                            (byBuffer[(byIndex * 4) + 2] * 0X10000) + (byBuffer[(byIndex * 4) + 3] * 0X1000000)) / 100);
                        TotalAmountInCG += Convert.ToDouble(byBuffer[byIndex * 4] + (byBuffer[(byIndex * 4) + 1] * 0X100) +
                            (byBuffer[(byIndex * 4) + 2] * 0X10000) + (byBuffer[(byIndex * 4) + 3] * 0X1000000)) / 100;
                    }
                    TotalInCG.Text = string.Format("{0:F2}", TotalAmountInCG);

                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditCGOUT["MontantOutCG", byIndex].Value = string.Format("{0:F2}",
                            Convert.ToDouble(byBuffer[32 + (byIndex * 4)] + (byBuffer[32 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[32 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[32 + (byIndex * 4) + 3] * 0X1000000)) / 100);
                        TotalAmountOutCG += Convert.ToDouble(byBuffer[32 + (byIndex * 4)] + (byBuffer[32 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[32 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[32 + (byIndex * 4) + 3] * 0X1000000)) / 100;
                    }
                    TotalOutCG.Text = string.Format("{0:F2}", TotalAmountOutCG);

                    for (int byIndex = 0; byIndex < 8; byIndex++)
                    {
                        dataGridViewAuditBV["MontantInBV", byIndex].Value = string.Format("{0:F2}",
                            Convert.ToDouble(byBuffer[64 + (byIndex * 4)] + (byBuffer[64 + ((byIndex * 4) + 1)] * 0X100) +
                            (byBuffer[64 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[64 + (byIndex * 4) + 3] * 0X1000000)) / 100);
                        TotalAmountInBv += Convert.ToDouble(byBuffer[64 + (byIndex * 4)] + (byBuffer[64 + ((byIndex * 4) + 1)] * 0X100) +
                         (byBuffer[64 + (byIndex * 4) + 2] * 0X10000) + (byBuffer[64 + (byIndex * 4) + 3] * 0X1000000)) / 100;
                    }
                    TotalInBV.Text = string.Format("{0:F2}", TotalAmountInBv);

                    for (int byIndex = 0; byIndex < 6; byIndex++)
                    {
                        dataGridViewAuditProduit["NumProduitAudit", byIndex].Value = string.Format("{0:d}", byBuffer[96 + (byIndex * 4)] +
                            (byBuffer[96 + ((byIndex * 4) + 1)] * 0X100) + (byBuffer[96 + (byIndex * 4) + 2] * 0X10000) +
                            (byBuffer[96 + (byIndex * 4) + 3] * 0X1000000));
                    }
                    OverPay = Convert.ToDouble(byBuffer[120] + (byBuffer[121] * 0X100) + (byBuffer[122] * 0X10000) + (byBuffer[123] * 0X1000000)) / 100;
                    LOverPay.Text = string.Format("{0:F2}", OverPay);
                    InCash = Convert.ToDouble(byBuffer[124] + (byBuffer[125] * 0X100) + (byBuffer[126] * 0X10000) + (byBuffer[127] * 0X1000000));
                    CoinsInCash.Text = string.Format("{0:F2}", InCash);
                    Total.Text = String.Format("{0:F2}", TotalAmountInCG + TotalAmountInBv + /*OverPay + InCash*/ -TotalAmountOutCG);
                    this.Height = 725;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
            if (((DataGridView)sender).CurrentCell.ColumnIndex == 1)
            {
                try
                {
                    sResult = ((DataGridView)sender).CurrentCell.Value.ToString().Replace('.', ',');
                    if (!double.TryParse(sResult, out double dResult))
                    {
                        throw new Exception("Entrée incorrecte!...");
                        //MessageBox.Show("Entrée incorrecte!!!", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        ((DataGridView)sender).CurrentCell.Value = string.Format("{0:F2}", dResult);
                    }
                }
                catch (Exception exception)
                {
                    MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                    if ((sResult.Length >= lenPhoneNumber) || (sResult.Length < 6))
                    {
                        throw new Exception("Le numéro de téléphone est incohérent!...");
                    }
                    foreach (char car in sResult)
                    {
                        if (!byte.TryParse(car.ToString(), out byte chiffre))
                        {
                            throw new Exception("Seul les chiffres sont acceptés pour le numéro de téléphone!!!");
                        }
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                ((DataGridView)sender)[0, ((DataGridView)sender).CurrentCell.RowIndex].Value = false;
                ((DataGridView)sender)[1, ((DataGridView)sender).CurrentCell.RowIndex].Value = false;
                ((DataGridView)sender).CurrentCell.Value = "06 12 34 56 78";
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
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Close();
                    }
                    serialPort1.PortName = CBSerialPorts.SelectedItem.ToString();
                    serialPort1.Open();
                    if (serialPort1.IsOpen)
                    {
                        toolStripComLabel.Text = serialPort1.PortName;
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                    dataGridViewAuditBV[1, byIndex].Value = string.Format("{0:F2}", Convert.ToDouble(0));
                }
                for (int byIndex = 0; byIndex < 6; byIndex++)
                {
                    dataGridViewAuditProduit[1, byIndex].Value = 0;
                }
                TotalInCG.Text = TotalOutCG.Text = TotalInBV.Text = CoinsInCash.Text = TotalInCG.Text = LOverPay.Text = Total.Text = string.Format("{0:F2}", Convert.ToDouble(0));
                byte[] byAuditRequest = { (byte)HEADER.RAZAUDITS };
                serialPort1.Write(byAuditRequest, 0, 1);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Lecture des paramètres de la carte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnRead_Click(object sender, EventArgs e)
        {
            int dwLength;
            try
            {
                if (IsSerialPortOpen())
                {

                    byte[] byParamRequest = { (byte)HEADER.GETPARAMS };
                    serialPort1.Write(byParamRequest, 0, 1);

                    //Date FW
                    LVersionFW.Text = "";
                    int byPos = serialPort1.ReadByte();
                    for (int i = 0; i < byPos; i++)
                    {
                        LVersionFW.Text += (char)serialPort1.ReadByte();
                    }
                    LDateFW.Text = "";

                    //Date FW
                    byPos = (byte)serialPort1.ReadByte();
                    for (int i = 0; i < byPos; i++)
                    {
                        LDateFW.Text += (char)serialPort1.ReadByte();
                    }

                    //Parametres
                    for (int i = 0; i < 4; i++)
                    {
                        byBuffer[i] = (byte)serialPort1.ReadByte();
                    }
                    dwLength = byBuffer[0] + (byBuffer[1] * 0x100) + (byBuffer[2] * 0x10000) + (byBuffer[3] * 0x1000000);
                    byBuffer = new byte[dwLength];
                    for (int i = 0; i < dwLength; i++)
                    {
                        byBuffer[i] = (byte)serialPort1.ReadByte();

                    }

                    //Identification
                    MachineID.Text = string.Format("{0,0:D}", (byBuffer[0] + (byBuffer[1] * 0x100) + (byBuffer[2] * 0x10000) + (byBuffer[3] * 0x1000000)));

                    //Activation periphériques
                    for (int i = 0; i < 8; i++)
                    {
                        dataGridViewCG["EnableCG", i].Value = (byBuffer[410] >> i) & 0X01;
                        dataGridViewBV["EnableBV", i].Value = (byBuffer[408] >> i) & 0X01;
                    }

                    //Prix
                    for (int i = 0; i < 3; i++)
                    {
                        dataGridViewPrice["Prix", i].Value = string.Format("{0:F2}", Convert.ToDouble(byBuffer[4 * i + 4] + (byBuffer[4 * i + 5] * 0x100) + (byBuffer[4 * i + 6] * 0x10000) + (byBuffer[4 * i + 7] * 0x1000000)));
                        //CashLess
                        dataGridViewPrice["CashLess", i].Value = string.Format("{0:F2}", Convert.ToDouble(byBuffer[4 * i + 16] + (byBuffer[4 * i + 17] * 0x100) + (byBuffer[4 * i + 18] * 0x10000) + (byBuffer[4 * i + 19] * 0x1000000)));
                    }

                    //Téléphones
                    for (int i = 0; i < 6; i++)
                    {
                        dataGridViewTelephone["Numero", i].Value = string.Format("{0:d}{1:d}{2:d}{3:d}{4:d}{5:d}{6:d}{7:d}{8:d}{9:d}{10:d}{11:d}{12:d}", byBuffer[i * 60 + 28], byBuffer[i * 60 + 32], byBuffer[i * 60 + 36], byBuffer[i * 60 + 40], byBuffer[i * 60 + 44],
                     byBuffer[i * 60 + 48], byBuffer[i * 60 + 52], byBuffer[i * 60 + 56], byBuffer[i * 60 + 60], byBuffer[i * 60 + 64], byBuffer[i * 60 + 68], byBuffer[i * 60 + 72], byBuffer[i * 60 + 76]);
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
                    isParametersReaded = true;
                    Refresh();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Vérifie la modification des ports série et corrige la liste si nécessaire.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Timer1_Tick_1(object sender, EventArgs e)
        {
            byte[] byCheckBoardPresence = { 0XAF };
            if (CBSerialPorts.Items.Count != System.IO.Ports.SerialPort.GetPortNames().Length)
            {
                CBSerialPorts.Items.Clear();
                CBSerialPorts.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            }
            for (int i = 0; i < CBSerialPorts.Items.Count; i++)
            {
                try
                {
                    serialPort1.PortName = (string)CBSerialPorts.Items[i];
                    serialPort1.Open();
                    serialPort1.Write(byCheckBoardPresence, 0, 1);
                    if ((serialPort1.Read(byCheckBoardPresence, 0, 1) == 1) &&
                        (byCheckBoardPresence[0] == 0xFA))
                    {
                        timer1.Enabled = false;
                        CBSerialPorts.SelectedIndex = i;
                        Refresh();
                        BtnRead_Click(sender, e);
                        ///BtnAudit_Click(sender, e);
                        break;
                    }
                }
                catch (InvalidOperationException)
                {
                }
                catch (Exception)
                {
                    serialPort1.Close();
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort1.Close();
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
                    Trap1UpDown.Value = 0;
                    break;
                }
                case "RBAuto2":
                {
                    Trap2UpDown.Value = 0;
                    break;
                }
                case "RBAuto3":
                {
                    Trap3UpDown.Value = 0;
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
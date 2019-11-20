using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BreadParam
{
    public partial class FormApropos : Form
    {
        public FormApropos()
        {
            InitializeComponent();
        }

        private void AdresseInternet_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.rasoftware.fr");
        }
    }
}

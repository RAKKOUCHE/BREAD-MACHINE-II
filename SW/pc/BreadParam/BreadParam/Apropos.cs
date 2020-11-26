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

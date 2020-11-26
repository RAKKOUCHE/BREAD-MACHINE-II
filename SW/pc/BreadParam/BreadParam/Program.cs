using System;
using System.Windows.Forms;

namespace BreadParam
{
    static class Program
    {
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
#pragma warning disable CA2000 // Dispose objects before losing scope
            Application.Run(new Form1());
#pragma warning restore CA2000 // Dispose objects before losing scope
        }
    }
}

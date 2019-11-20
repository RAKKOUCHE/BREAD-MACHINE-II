namespace BreadParam
{
    partial class FormApropos
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormApropos));
            this.AdresseInternet = new System.Windows.Forms.LinkLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // AdresseInternet
            // 
            this.AdresseInternet.AutoSize = true;
            this.AdresseInternet.Location = new System.Drawing.Point(13, 236);
            this.AdresseInternet.Name = "AdresseInternet";
            this.AdresseInternet.Size = new System.Drawing.Size(64, 13);
            this.AdresseInternet.TabIndex = 0;
            this.AdresseInternet.TabStop = true;
            this.AdresseInternet.Text = "RASoftware";
            this.AdresseInternet.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.AdresseInternet_LinkClicked);
            // 
            // panel1
            // 
            this.panel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel1.BackgroundImage")));
            this.panel1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Location = new System.Drawing.Point(16, 154);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(81, 79);
            this.panel1.TabIndex = 1;
            // 
            // FormApropos
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.AdresseInternet);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormApropos";
            this.Text = "A propros...";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.LinkLabel AdresseInternet;
        private System.Windows.Forms.Panel panel1;
    }
}
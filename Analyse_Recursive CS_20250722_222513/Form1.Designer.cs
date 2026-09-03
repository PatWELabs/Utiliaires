using System.Resources;

namespace Analyse_Recursive_CS
{
    partial class Form1
    {
        public ToolTip ToolTip1;
        public Button Command3;
        public Button Command2;
        public Button Command1;
        public ListBox List1;
        public ListBox dossiers;
        public Label label1;
        public Label label0;
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            ToolTip1 = new ToolTip(components);
            Command3 = new Button();
            Command2 = new Button();
            Command1 = new Button();
            List1 = new ListBox();
            dossiers = new ListBox();
            label1 = new Label();
            label0 = new Label();
            SuspendLayout();
            // 
            // Command3
            // 
            Command3.BackColor = SystemColors.Control;
            Command3.ForeColor = SystemColors.ControlText;
            Command3.Location = new Point(631, 1);
            Command3.Name = "Command3";
            Command3.RightToLeft = RightToLeft.No;
            Command3.Size = new Size(57, 25);
            Command3.TabIndex = 6;
            Command3.Text = "Quitter";
            Command3.UseVisualStyleBackColor = false;
            Command3.Click += Command3_Click;
            // 
            // Command2
            // 
            Command2.BackColor = SystemColors.Control;
            Command2.ForeColor = SystemColors.ControlText;
            Command2.Location = new Point(567, 1);
            Command2.Name = "Command2";
            Command2.RightToLeft = RightToLeft.No;
            Command2.Size = new Size(57, 25);
            Command2.TabIndex = 5;
            Command2.Text = "Generer";
            Command2.UseVisualStyleBackColor = false;
            Command2.Click += Command2_Click;
            // 
            // Command1
            // 
            Command1.BackColor = SystemColors.Control;
            Command1.ForeColor = SystemColors.ControlText;
            Command1.Location = new Point(383, 1);
            Command1.Name = "Command1";
            Command1.RightToLeft = RightToLeft.No;
            Command1.Size = new Size(177, 25);
            Command1.TabIndex = 4;
            Command1.Text = "Selectioner le dossier de travail";
            Command1.UseVisualStyleBackColor = false;
            Command1.Click += Command1_Click;
            // 
            // List1
            // 
            List1.BackColor = SystemColors.Window;
            List1.ForeColor = SystemColors.WindowText;
            List1.ItemHeight = 15;
            List1.Location = new Point(8, 230);
            List1.Name = "List1";
            List1.RightToLeft = RightToLeft.No;
            List1.Size = new Size(681, 199);
            List1.TabIndex = 1;
            // 
            // dossiers
            // 
            dossiers.BackColor = SystemColors.Window;
            dossiers.ForeColor = SystemColors.WindowText;
            dossiers.ItemHeight = 15;
            dossiers.Location = new Point(8, 30);
            dossiers.Name = "dossiers";
            dossiers.RightToLeft = RightToLeft.No;
            dossiers.Size = new Size(681, 184);
            dossiers.TabIndex = 0;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.ForeColor = SystemColors.ControlText;
            label1.Location = new Point(8, 214);
            label1.Name = "label1";
            label1.RightToLeft = RightToLeft.No;
            label1.Size = new Size(47, 15);
            label1.TabIndex = 3;
            label1.Text = "Fichiers";
            // 
            // label0
            // 
            label0.AutoSize = true;
            label0.BackColor = Color.Transparent;
            label0.ForeColor = SystemColors.ControlText;
            label0.Location = new Point(16, 6);
            label0.Name = "label0";
            label0.RightToLeft = RightToLeft.No;
            label0.Size = new Size(79, 15);
            label0.TabIndex = 2;
            label0.Text = "Arborescence";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.Control;
            ClientSize = new Size(699, 441);
            Controls.Add(Command3);
            Controls.Add(Command2);
            Controls.Add(Command1);
            Controls.Add(List1);
            Controls.Add(dossiers);
            Controls.Add(label1);
            Controls.Add(label0);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            Icon = (Icon)resources.GetObject("$this.Icon");
            Location = new Point(3, 25);
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Form1";
            RightToLeft = RightToLeft.No;
            ShowInTaskbar = false;
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }


        #endregion
    }
}

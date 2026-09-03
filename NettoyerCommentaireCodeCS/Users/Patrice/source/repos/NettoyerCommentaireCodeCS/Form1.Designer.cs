
using System;
using System.Drawing;
using System.Windows.Forms;

namespace NettoyerCommentaireCodeCS
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.CmdFileLoad = new LinkLabel();
            this.textBox1 = new TextBox();
            this.openFileDialog1 = new OpenFileDialog();
            this.label1 = new Label();
            this.label2 = new Label();
            this.listBox1 = new ListBox();
            this.listBox2 = new ListBox();
            this.CmdSauvegarder = new LinkLabel();
            this.CmdQuitter = new LinkLabel();
            this.CmdCascade = new LinkLabel();
            this.folderBrowserDialog1 = new FolderBrowserDialog();
            this.comboBox1 = new ComboBox();
            this.SuspendLayout();
            // 
            // CmdFileLoad
            // 
            this.CmdFileLoad.AutoSize = true;
            this.CmdFileLoad.Location = new Point(626, 563);
            this.CmdFileLoad.Name = "CmdFileLoad";
            this.CmdFileLoad.Size = new Size(40, 15);
            this.CmdFileLoad.TabIndex = 0;
            this.CmdFileLoad.TabStop = true;
            this.CmdFileLoad.Text = "Ouvrir";
            this.CmdFileLoad.LinkClicked += this.CmdFileLoad_LinkClicked;
            // 
            // textBox1
            // 
            this.textBox1.Location = new Point(1, 555);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new Size(616, 23);
            this.textBox1.TabIndex = 1;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new Point(1, 4);
            this.label1.Name = "label1";
            this.label1.Size = new Size(43, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "Source";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new Point(617, 4);
            this.label2.Name = "label2";
            this.label2.Size = new Size(44, 15);
            this.label2.TabIndex = 5;
            this.label2.Text = "Généré";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.IntegralHeight = false;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new Point(1, 22);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new Size(610, 522);
            this.listBox1.TabIndex = 6;
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.HorizontalScrollbar = true;
            this.listBox2.IntegralHeight = false;
            this.listBox2.ItemHeight = 15;
            this.listBox2.Location = new Point(617, 22);
            this.listBox2.Name = "listBox2";
            this.listBox2.Size = new Size(610, 522);
            this.listBox2.TabIndex = 7;
            // 
            // CmdSauvegarder
            // 
            this.CmdSauvegarder.AutoSize = true;
            this.CmdSauvegarder.Location = new Point(1096, 563);
            this.CmdSauvegarder.Name = "CmdSauvegarder";
            this.CmdSauvegarder.Size = new Size(72, 15);
            this.CmdSauvegarder.TabIndex = 8;
            this.CmdSauvegarder.TabStop = true;
            this.CmdSauvegarder.Text = "Sauvegarder";
            this.CmdSauvegarder.LinkClicked += this.CmdSauvegarder_LinkClicked;
            // 
            // CmdQuitter
            // 
            this.CmdQuitter.AutoSize = true;
            this.CmdQuitter.Location = new Point(1174, 563);
            this.CmdQuitter.Name = "CmdQuitter";
            this.CmdQuitter.Size = new Size(44, 15);
            this.CmdQuitter.TabIndex = 9;
            this.CmdQuitter.TabStop = true;
            this.CmdQuitter.Text = "Quitter";
            this.CmdQuitter.LinkClicked += this.CmdQuitter_LinkClicked;
            // 
            // CmdCascade
            // 
            this.CmdCascade.AutoSize = true;
            this.CmdCascade.Location = new Point(626, 587);
            this.CmdCascade.Name = "CmdCascade";
            this.CmdCascade.Size = new Size(115, 15);
            this.CmdCascade.TabIndex = 10;
            this.CmdCascade.TabStop = true;
            this.CmdCascade.Text = "Procéder en cascade";
            this.CmdCascade.LinkClicked += this.CmdCascade_LinkClicked;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new Point(1, 584);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new Size(616, 23);
            this.comboBox1.TabIndex = 11;
            this.comboBox1.SelectedIndexChanged += this.comboBox1_SelectedIndexChanged;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new SizeF(7F, 15F);
            this.AutoScaleMode = AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            this.ClientSize = new Size(1230, 624);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.CmdCascade);
            this.Controls.Add(this.CmdQuitter);
            this.Controls.Add(this.CmdSauvegarder);
            this.Controls.Add(this.listBox2);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.CmdFileLoad);
            this.FormBorderStyle = FormBorderStyle.Fixed3D;
            this.Icon = (Icon)resources.GetObject("$this.Icon");
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "Form1";
            Load += this.Form1_Load;
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
        private LinkLabel CmdFileLoad;
        private TextBox textBox1;
        private OpenFileDialog openFileDialog1;
        private Label label1;
        private Label label2;
        private ListBox listBox1;
        private ListBox listBox2;
        private LinkLabel CmdSauvegarder;
        private LinkLabel CmdQuitter;
        private LinkLabel CmdCascade;
        private FolderBrowserDialog folderBrowserDialog1;
        private ComboBox comboBox1;

    }
}


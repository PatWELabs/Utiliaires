namespace Reservations
{
    partial class Form1
    {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            Commandes = new Panel();
            Quitter = new Button();
            Suivant = new Button();
            Precedent = new Button();
            panel1 = new Panel();
            pictureBox1 = new PictureBox();
            label1 = new Label();
            pConnexion = new Panel();
            identifier = new Button();
            textBox1 = new TextBox();
            label4 = new Label();
            comboBox1 = new ComboBox();
            label3 = new Label();
            label2 = new Label();
            Etape4 = new Panel();
            dateTimePicker1 = new DateTimePicker();
            label5 = new Label();
            label6 = new Label();
            HeurStart = new ComboBox();
            label7 = new Label();
            comboBox2 = new ComboBox();
            button1 = new Button();
            Commandes.SuspendLayout();
            panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            pConnexion.SuspendLayout();
            Etape4.SuspendLayout();
            SuspendLayout();
            // 
            // Commandes
            // 
            Commandes.Controls.Add(Quitter);
            Commandes.Controls.Add(Suivant);
            Commandes.Controls.Add(Precedent);
            Commandes.Dock = DockStyle.Bottom;
            Commandes.Location = new Point(0, 414);
            Commandes.Name = "Commandes";
            Commandes.Size = new Size(800, 36);
            Commandes.TabIndex = 0;
            // 
            // Quitter
            // 
            Quitter.Location = new Point(699, 3);
            Quitter.Name = "Quitter";
            Quitter.Size = new Size(98, 29);
            Quitter.TabIndex = 2;
            Quitter.Text = "Abandonner";
            Quitter.UseVisualStyleBackColor = true;
            // 
            // Suivant
            // 
            Suivant.Enabled = false;
            Suivant.Location = new Point(480, 3);
            Suivant.Name = "Suivant";
            Suivant.Size = new Size(85, 29);
            Suivant.TabIndex = 1;
            Suivant.Text = "Suivant >";
            Suivant.UseVisualStyleBackColor = true;
            // 
            // Precedent
            // 
            Precedent.Enabled = false;
            Precedent.Location = new Point(382, 3);
            Precedent.Name = "Precedent";
            Precedent.Size = new Size(92, 29);
            Precedent.TabIndex = 0;
            Precedent.Text = "< Précédent";
            Precedent.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            panel1.Controls.Add(pictureBox1);
            panel1.Controls.Add(label1);
            panel1.Dock = DockStyle.Left;
            panel1.Location = new Point(0, 0);
            panel1.Name = "panel1";
            panel1.Size = new Size(88, 414);
            panel1.TabIndex = 1;
            // 
            // pictureBox1
            // 
            pictureBox1.BackColor = Color.White;
            pictureBox1.BackgroundImageLayout = ImageLayout.Center;
            pictureBox1.Dock = DockStyle.Fill;
            pictureBox1.Image = Properties.Resources.Autheur;
            pictureBox1.Location = new Point(0, 15);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(88, 399);
            pictureBox1.TabIndex = 1;
            pictureBox1.TabStop = false;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Dock = DockStyle.Top;
            label1.Location = new Point(0, 0);
            label1.Name = "label1";
            label1.Size = new Size(89, 15);
            label1.TabIndex = 0;
            label1.Text = "Wizzard System";
            label1.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // pConnexion
            // 
            pConnexion.AutoSize = true;
            pConnexion.BorderStyle = BorderStyle.FixedSingle;
            pConnexion.Controls.Add(identifier);
            pConnexion.Controls.Add(textBox1);
            pConnexion.Controls.Add(label4);
            pConnexion.Controls.Add(comboBox1);
            pConnexion.Controls.Add(label3);
            pConnexion.Controls.Add(label2);
            pConnexion.Location = new Point(188, 90);
            pConnexion.Name = "pConnexion";
            pConnexion.Size = new Size(350, 181);
            pConnexion.TabIndex = 2;
            // 
            // identifier
            // 
            identifier.Location = new Point(232, 144);
            identifier.Name = "identifier";
            identifier.Size = new Size(90, 23);
            identifier.TabIndex = 5;
            identifier.Text = "Valider login";
            identifier.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(142, 89);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(144, 23);
            textBox1.TabIndex = 4;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(59, 92);
            label4.Name = "label4";
            label4.Size = new Size(77, 15);
            label4.TabIndex = 3;
            label4.Text = "Mot de passe";
            // 
            // comboBox1
            // 
            comboBox1.FormattingEnabled = true;
            comboBox1.Location = new Point(140, 55);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(146, 23);
            comboBox1.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(59, 63);
            label3.Name = "label3";
            label3.Size = new Size(60, 15);
            label3.TabIndex = 1;
            label3.Text = "Utilisateur";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(31, 29);
            label2.Name = "label2";
            label2.Size = new Size(122, 15);
            label2.TabIndex = 0;
            label2.Text = "Connexion au serveur";
            // 
            // Etape4
            // 
            Etape4.Controls.Add(button1);
            Etape4.Controls.Add(comboBox2);
            Etape4.Controls.Add(label7);
            Etape4.Controls.Add(HeurStart);
            Etape4.Controls.Add(label6);
            Etape4.Controls.Add(label5);
            Etape4.Controls.Add(dateTimePicker1);
            Etape4.Location = new Point(188, 277);
            Etape4.Name = "Etape4";
            Etape4.Size = new Size(350, 181);
            Etape4.TabIndex = 3;
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(129, 26);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(178, 23);
            dateTimePicker1.TabIndex = 0;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(7, 30);
            label5.Name = "label5";
            label5.Size = new Size(96, 15);
            label5.TabIndex = 1;
            label5.Text = "Réservation pour";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(69, 68);
            label6.Name = "label6";
            label6.Size = new Size(54, 15);
            label6.TabIndex = 2;
            label6.Text = "Débute a";
            // 
            // HeurStart
            // 
            HeurStart.FormattingEnabled = true;
            HeurStart.Location = new Point(129, 64);
            HeurStart.Name = "HeurStart";
            HeurStart.Size = new Size(121, 23);
            HeurStart.TabIndex = 3;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(69, 96);
            label7.Name = "label7";
            label7.Size = new Size(38, 15);
            label7.TabIndex = 4;
            label7.Text = "Fini a ";
            // 
            // comboBox2
            // 
            comboBox2.FormattingEnabled = true;
            comboBox2.Location = new Point(129, 93);
            comboBox2.Name = "comboBox2";
            comboBox2.Size = new Size(121, 23);
            comboBox2.TabIndex = 5;
            // 
            // button1
            // 
            button1.Location = new Point(211, 154);
            button1.Name = "button1";
            button1.Size = new Size(131, 23);
            button1.TabIndex = 6;
            button1.Text = "Vérifier disponibilité";
            button1.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            ClientSize = new Size(800, 450);
            Controls.Add(Etape4);
            Controls.Add(pConnexion);
            Controls.Add(panel1);
            Controls.Add(Commandes);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            Commandes.ResumeLayout(false);
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            pConnexion.ResumeLayout(false);
            pConnexion.PerformLayout();
            Etape4.ResumeLayout(false);
            Etape4.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Panel Commandes;
        private Button Precedent;
        private Button Quitter;
        private Button Suivant;
        private Panel panel1;
        private Label label1;
        private PictureBox pictureBox1;
        private Panel pConnexion;
        private Label label4;
        private ComboBox comboBox1;
        private Label label3;
        private Label label2;
        private Button identifier;
        private TextBox textBox1;
        private Panel Etape4;
        private Label label5;
        private DateTimePicker dateTimePicker1;
        private ComboBox comboBox2;
        private Label label7;
        private ComboBox HeurStart;
        private Label label6;
        private Button button1;
    }
}
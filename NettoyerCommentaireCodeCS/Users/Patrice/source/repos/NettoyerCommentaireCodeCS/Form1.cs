using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
#pragma warning disable CS8600 // Conversion de littéral ayant une valeur null ou d'une éventuelle valeur null en type non-nullable.
#pragma warning disable CS8602 // Déréférencement d'une éventuelle référence nulle.
#pragma warning disable CS8604 // Déréférencement référence nulle.
#pragma warning disable CS8618 // Un champ non-nullable doit contenir une valeur non-nulle lors de la fermeture du constructeur. Envisagez de déclarer le champ comme nullable.
using System.Drawing.Printing;
using System.IO;

namespace NettoyerCommentaireCodeCS
{
    public partial class Form1 : Form
    {
        private Font printFont;
        private StreamReader streamToPrint;
        Bitmap memoryImage;
        private PrintDocument printDocument1 = new PrintDocument();
        public Form1()
        {
            InitializeComponent();
            printDocument1.PrintPage += new PrintPageEventHandler(ImprimerFormulaire);
        }
        private void ImprimerFormulaire(Object sender, PrintPageEventArgs e) => e.Graphics.DrawImage(memoryImage, 0, 0);
        private void ImprimerFichier(object sender, PrintPageEventArgs ev)
        {
            float linesPerPage = 0;
            float yPos = 0;
            int count = 0;
            float leftMargin = ev.MarginBounds.Left / 2;
            float topMargin = ev.MarginBounds.Top / 2;
            string line = null;
            linesPerPage = ev.MarginBounds.Height / printFont.GetHeight(ev.Graphics);
            while (count < linesPerPage && ((line = streamToPrint.ReadLine()) != null))
            {
                yPos = topMargin + (count *
                   printFont.GetHeight(ev.Graphics));
                ev.Graphics.DrawString(line, printFont, Brushes.Black,
                   leftMargin, yPos, new StringFormat());
                count++;
            }
            if (line != null)
                ev.HasMorePages = true;
            else
                ev.HasMorePages = false;
        }
        private void ImpressionFichier(string fichier)
        {
            try
            {
                streamToPrint = new StreamReader(fichier);
                try
                {
                    printFont = new Font("Arial", 10);
                    PrintDocument pd = new PrintDocument();
                    pd.PrintPage += new PrintPageEventHandler(this.ImprimerFichier);
                    pd.Print();
                }
                finally
                {
                    streamToPrint.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void CmdFileLoad_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            openFileDialog1.Filter = "Fichiers C Sharp|*.cs";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                listBox1.Items.Clear();
                listBox2.Items.Clear();
                label1.Text = openFileDialog1.SafeFileName;
                label2.Text = Environment.CurrentDirectory + "\\" + label1.Text.Replace("frm", string.Empty);
                textBox1.Text = openFileDialog1.FileName;
                StreamReader rd = new StreamReader(textBox1.Text);
                while (rd.Peek() >= 0)
                {
                    listBox1.Items.Add(rd.ReadLine().ToString());
                    Application.DoEvents();
                }
                rd.Close();
                for (int x = 0; x < listBox1.Items.Count; x++)
                {
                    if (listBox1.Items[x].ToString() != string.Empty)
                    {
                        if (!listBox1.Items[x].ToString().Contains("//"))
                        {

                            listBox2.Items.Add(listBox1.Items[x].ToString());
                        }
                    }
                }
            }

        }

        private void CmdQuitter_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Text = Application.ProductName + "  " + Application.ProductVersion;
        }

        private void CmdSauvegarder_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StreamWriter sw = new StreamWriter(label2.Text);
            sw.WriteLine("//" + Text + " " + DateTime.Now.ToString());
            for (int x = 0; x < listBox2.Items.Count; x++)
            {
                sw.WriteLine(listBox2.Items[x].ToString());
            }
            sw.Close();
        }

        private void CmdCascade_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            string Chemin = Environment.CurrentDirectory;
            folderBrowserDialog1.RootFolder = Environment.SpecialFolder.System;
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                Chemin = folderBrowserDialog1.SelectedPath;
                comboBox1.Items.Clear();
            }
            else { return; }
            List<string> lstFichiers = new List<string>(Directory.EnumerateFiles(Chemin, "*.cs", SearchOption.AllDirectories));
            foreach (string p in lstFichiers)
            {
                comboBox1.Items.Add(p);
            }
            /*
             * if (lstFichiers.Count > 1)
             {
                 for (int x = 0; x < lstFichiers.Count; x++)
                 {
                     textBox1.Text = lstFichiers[x];
                     listBox1.Items.Clear();
                     listBox2.Items.Clear();
                     // simple matrice 2D
                     label1.Text = lstFichiers[x].Split('\\')[lstFichiers[x].Split('\\').Length - 1];
                     label2.Text = Environment.CurrentDirectory + "\\" + label1.Text.Replace("frm", string.Empty);
                     StreamReader rd = new StreamReader(textBox1.Text);
                     while (rd.Peek() >= 0)
                     {
                         listBox1.Items.Add(rd.ReadLine().ToString());
                         Application.DoEvents();
                     }
                     rd.Close();
                     for (int y = 0; y < listBox1.Items.Count; y++)
                     {
                         if (listBox1.Items[y].ToString() != string.Empty)
                         {
                             string str = listBox1.Items[y].ToString();
                             Application.DoEvents();
                             if (!str.Contains('\''))
                             {
                                 int nbr = listBox2.Items.Add(str);
                             }
                             else
                             { //si le commentaire n'est pas en debut de ligne
                                 int nbr = listBox2.Items.Add(str.Split('\'')[0]);
                             }
                         }
                     }
                     StreamWriter sw = new StreamWriter(label2.Text);
                     sw.WriteLine("'" + Text + " " + DateTime.Now.ToString());
                     for (int a = 0; a < listBox2.Items.Count; a++)
                     {
                         sw.WriteLine(listBox2.Items[a].ToString());
                     }
                     sw.Close();

                 }
             }
             */
        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBox1.Text = comboBox1.SelectedItem.ToString();
            label1.Text = textBox1.Text.Split('\\')[textBox1.Text.Split('\\').Length - 1];
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            label2.Text = Environment.CurrentDirectory + "\\" + label1.Text.Replace("frm", string.Empty);
            StreamReader rd = new StreamReader(textBox1.Text);
            while (rd.Peek() >= 0)
            {
                listBox1.Items.Add(rd.ReadLine().ToString());
                Application.DoEvents();
            }
            rd.Close();
            for (int y = 0; y < listBox1.Items.Count; y++)
            {
                if (listBox1.Items[y].ToString() != string.Empty)
                {
                    if (!listBox1.Items[y].ToString().Contains("//"))
                    {
                        int nbr = listBox2.Items.Add(listBox1.Items[y].ToString());
                    }
                }
            }
        }
    }
}

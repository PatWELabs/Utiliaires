using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
#pragma warning disable CS0169
namespace WinReservations
{
    public partial class Main : Form
    {
        List<Employes> lst = new List<Employes>();
        SqlDataReader reader=null;
        SqlCommand cmd;
        SqlConnection con;
        public static string strSQL = "Data Source=INTRANET\\SQLEXPRESS;Initial Catalog=Reservations;Integrated Security=True";
        public Main()
        {
            InitializeComponent();
        }
        public static void ExecuteSQL(string requeteSQL)
        {
            SqlConnection con = new SqlConnection(strSQL);
            try { 
                con.Open(); 
                SqlCommand cmd = new SqlCommand(requeteSQL, con); cmd.ExecuteNonQuery(); }
            catch (Exception ex) { MessageBox.Show(ex.Message, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Stop); }
            con.Close();
        }
        private void ListerSalles() 
        {
            con = new SqlConnection(strSQL);
            con.Open();
            cmd = new SqlCommand("SELECT [NOM] FROM [DBO].[TABLESALLES]", con);
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                comboBox2.Items.Add(reader[0].ToString());
            }
            con.Close();
        }
        private void AddUserFromServer() 
        {
            con = new SqlConnection("Data Source=INTRANET\\SQLEXPRESS;User ID=sa;PWD=Password01$;Initial Catalog=AutoGRB;");
            con.Open();
            cmd = new SqlCommand("select distinct [employe],[loginname],[passwd],[noemploye] from Grb_Employés where actif=1 and Supprimé=0", con);
            reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Employes emp = new Employes(reader[0].ToString(), reader[1].ToString(), reader[2].ToString(), (int)reader[3]);
                lst.Add(emp);
                comboBox1.Items.Add(reader[0].ToString());
            }
            con.Close();
        }
        private void Main_Load(object sender, EventArgs e)
        {
            this.Text = "Projet: Réservation de salles GRB Solution Inc.";
            toolStripStatusLabel1.Text = DateTime.Now.ToLongDateString();
            AddUserFromServer();
            GenererPlageHorraires();
            HeurStart.SelectedIndex = 0;
            HeurEnd.SelectedIndex = 0;
            ListerSalles();
            for(int x=1; x<21; x++) { comboBox3.Items.Add(x.ToString()); }
        }
        private void GenererPlageHorraires()
        {
            for (int x = 8; x < 17; x++)
            {
                string str = x.ToString().PadLeft(2, '0') + ":00";
                HeurStart.Items.Add(str);
                HeurEnd.Items.Add(str);
                str = x.ToString().PadLeft(2, '0') + ":30";
                HeurStart.Items.Add(str);
                HeurEnd.Items.Add(str);
            }
            HeurStart.Items.Remove("16:30");
            HeurEnd.Items.Remove("08:00");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            foreach(Employes p in lst)
            {
                if (p.Nom == comboBox1.Items[comboBox1.SelectedIndex].ToString())
                {
                    if (p.Password == textBox1.Text)
                    {
                        toolStripStatusLabel2.Text = p.Id.ToString();
                        toolStripStatusLabel1.Text = p.Nom;
                        panel2.Enabled = true;
                        panel1.Enabled = false;
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (HeurStart.Text == HeurEnd.Text) { MessageBox.Show("Une durée nulle n'est pas permise", Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Stop);return; }
            if (comboBox2.Text == null) { MessageBox.Show("Une salle doit être sélectionée", Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Stop); return; }
            if (comboBox3.Text == null) { return; }
            if (int.Parse(comboBox3.Text) < 2) { MessageBox.Show("Il n'y a pas assez de participants", Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Stop); return; }
            string sql = $"INSERT INTO [DBO].[RESERVATIONSALLE]([SALLE],[ASSIGNEEA],[DATE],[DEBUT],[FIN],[PARTICIPANTS],[CONFERENCE],[FORMATION],[REUNION])VALUES({comboBox2.SelectedIndex+1},{toolStripStatusLabel1.Text},{dateTimePicker1.Value.ToShortDateString()},{HeurStart.Text},{HeurEnd.Text},{comboBox3.Text},{int.Parse(comboBox3.Text)},{Conférence.Checked},{Formation.Checked},{Réunion.Checked})";
            ExecuteSQL(sql);
        }
        private void button4_Click(object sender, EventArgs e) => new Form2().Show();
        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

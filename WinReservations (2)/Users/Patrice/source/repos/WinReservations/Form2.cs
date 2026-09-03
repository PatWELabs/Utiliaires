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

namespace WinReservations
{
    public partial class Form2 : Form
    {
        int ID = 0;
        public Form2()
        {
            InitializeComponent();
        }

        protected void GetNewID() 
        {
            SqlConnection con = new SqlConnection(Main.strSQL);
            con.Open();
            SqlCommand cmd = new SqlCommand("SELECT [NUMERO] FROM [DBO].[TABLESALLES]", con);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read()){ID = (int)reader[0];}
            ID++;
            con.Close();


        }
        private void Form2_Load(object sender, EventArgs e)
        {
            GetNewID();
            this.textBox1.Text = ID.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Main.ExecuteSQL($"INSERT INTO [DBO].[TABLESALLES]([NUMERO],[NOM])VALUES('{textBox2.Text}')"); 
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}

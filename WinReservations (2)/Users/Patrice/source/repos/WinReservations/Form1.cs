namespace Reservations
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        void GenererPlageHorraires()
        {
            for (int x = 8; x < 17; x++)
            {
                string str = x.ToString().PadRight(2, '0') + ":00";
                HeurStart.Items.Add(str);
                str = x.ToString().PadRight(2, '0') + ":30";
                HeurStart.Items.Add(str);
                if (x > 8)
                {
                    HeurEnd.Items.Add(str);
                }
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            Text = "Réservations de salles";
        }
    }
}
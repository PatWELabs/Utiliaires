using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CreationUtilisateurSQL
{
    class Program
    {

        static string StringSQL { get; set; } = $"Data Source=production\\SQLEXPRESS;Initial Catalog=master;Integrated Security=false;Persist Security Info=True;User ID=sa; pwd=Password01$;";
        static int CreerUtilisateurSQL(string TextLoging,string TextPassword)
        {
            string requeteSQL = $"CREATE LOGIN[{TextLoging}] WITH PASSWORD = N'{TextPassword}', DEFAULT_DATABASE =[master], DEFAULT_LANGUAGE =[Français], CHECK_EXPIRATION = OFF, CHECK_POLICY = ON " +
            $"ALTER LOGIN[{TextLoging}]  ALTER SERVER ROLE[sysadmin] ADD MEMBER[{TextLoging}]";
            SqlCommand cmd = new SqlCommand(requeteSQL, con);
            con.Close();
            return cmd.ExecuteNonQuery(); 
        }
        static void EnumEmployes()
        {    
         SqlConnection con = new SqlConnection(StringSQL);
            if (con.State == ConnectionState.Closed) { con.Open(); }
        }
        static void Main(string[] args)
        {
            Console.Title = Environment.OSVersion.VersionString +" " +Environment.OSVersion.ServicePack;
            if (Environment.Is64BitProcess) { Console.Title += " x64"; }
            SqlConnection con = new SqlConnection(StringSQL);
            con.Open();
            SqlDataReader reader = new SqlCommand($"SELECT DISTINCT * FROM [AUTOGRB].DBO.GRB_EMPLOYÉS WHERE ACTIF=1 AND SUPPRIMÉ=0", con).ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine($"Traitement {(int)reader[0]} Employé: {reader[3]} a retourné {CreerUtilisateurSQL(reader[1].ToString(),reader[2].ToString())} comme résultat");
            }
            con.Close();
        }
    }
}

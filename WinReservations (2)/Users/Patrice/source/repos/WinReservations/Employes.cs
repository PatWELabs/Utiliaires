#pragma warning disable CS0169
namespace WinReservations
{
    public class Employes 
    {
        public Employes(string nom, string useName, string password, int id)
        {
            Nom = nom;
            UseName = useName;
            Password = password;
            Id = id;
        }

        public string Nom { get; set; }
        public string UseName { get; set; }
        public string Password { get; set; }
        public int Id { get; set; }
    }
}

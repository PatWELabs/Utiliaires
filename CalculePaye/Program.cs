using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
/*
 [21:38] CHANTAL DUSABIMANA INGABIRE (Etudiant)
Exercice 1.   Un employeur désire un programme qui calculera la paie hebdomadaire 
 * de ses employés payés à l’heure. 
 * Le programme doit demander le nom de l’employé, son taux horaire et le nombre d’heures travaillées. 
 * Par la suite, le programme doit afficher le nom de l’employé, le salaire brut, le salaire net, 
 * le nombre d’heures travaillées et l’impôt retenu. 
 * Le salaire brut est calculé ainsi : 40 premières heures au taux régulier, les heures supplémentaires à taux et demi. 
 * L’impôt retenu est calculé de la façon suivante : si le salaire hebdomadaire multiplié par 52 est inférieur ou égal à 10 000 $
 * , on retient 10 % du salaire brut. S’il est plus grand que 10 000 $, on lui retient 15 % d’impôt

*/
namespace CalculePaye
{
    class Program
    {
        static void Main(string[] args)
        {
            double impot = 0;
            Console.Write("Saisissez votre nom\t"); string nom = Console.ReadLine();
            Console.Write("Saisissez le nombre d'heures travailés\t"); double nHeures = Convert.ToDouble(Console.ReadLine());
            Console.Write("Saisissez votre tarif horraire\t"); double TarifHeure = Convert.ToDouble(Console.ReadLine());
            double salaireHeb = TarifHeure * 40;
            if (nHeures > 40)
            {
                salaireHeb = ((nHeures - 40) * 1.5) * TarifHeure + (nHeures * TarifHeure);
            }
            else {
                salaireHeb = nHeures * TarifHeure;
            }
            double salaireAn = salaireHeb * 52;
            if (salaireAn <= 10000)
            {
                impot = salaireAn * .1;
            }
            else {
                impot = salaireAn * .15;
            }
            Console.WriteLine("Mr. \t"+nom);
            Console.WriteLine("Heures travaillees \t"+nHeures.ToString());
            Console.WriteLine("Salaire brut\t"+salaireAn.ToString());
            Console.WriteLine("Salaire net\t"+Convert.ToString(salaireAn- impot));
            Console.WriteLine("Retenue impot \t"+Convert.ToString(impot));
            Console.ReadLine();
        }
    }
}

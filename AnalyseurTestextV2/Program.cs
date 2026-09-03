using System;
namespace AnalyseurTestextV2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "AnalyseurTestext V2.00  Patrice Waechter-Ebling 14-02-2022";
            AnalyserTexte(Console.Title);
            Console.WriteLine("Veuillez entrer un texte à analyser :");
            String texte = Console.ReadLine();
            if (string.IsNullOrEmpty(texte))
            {
                Console.WriteLine("Aucun texte saisi. Veuillez entrer un texte à analyser :");
                texte = Console.ReadLine();
            }
            else
            {
                AnalyserTexte(texte);
            }
        }
        static void AnalyserTexte(string texte)
        {
            string[] beta = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
            string tmp = null;
            int digit = 0;
            int autre = 0;
            char txt;
            int b = texte.Length;
            Console.WriteLine($"Début de la procédure avec {tmp}");
            for (int x = 0; x < b; x++)
            {
                if (char.IsLetter(texte[x]))
                {
                    for (int z = 97; z < 123; z++)
                    {
                        if (texte[x] == z)
                        {
                            int y = 0;
                            for (int a = 0; a < b; a++)
                            {
                                if (char.IsWhiteSpace(texte[x]))
                                {
                                    Console.WriteLine($"Espace détecté offset: {x}");
                                }
                                if (texte.Substring(a, 1).Contains((char)z))
                                {
                                    y++;
                                    txt = (char)y;
                                    beta[2] = txt.ToString();
                                    Console.WriteLine(beta[2]);
                                }
                            }
                            tmp = tmp + (char)(z);
                        }
                    }
                }
                else if (char.IsDigit(texte[x]))
                {
                    digit++;
                    tmp = tmp + (char)texte[x];
                }
                else
                {
                    autre++;
                    tmp = tmp + texte[x];
                }
            }
            for (int x = 0; x < 26; x++)
            {
                Console.WriteLine($"Nombre occurences de {(char)(x + 97)} ou {(char)(x + 65)} dans le texte = {beta[2]}.");
            }
            Console.WriteLine($"Nombre total de caractères numériques dans le texte = {digit}.");
            Console.WriteLine($"Nombre total d'occurences de caractères de ponctuations parmi .,;!?  =  {autre}.");
            Console.WriteLine(texte);
        }
    }
}

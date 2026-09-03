using System;

namespace ASCII_TexteScanner
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Entrez une chaine de caracteres svp: ");
            string tmp = Console.ReadLine();
            ASCII_TexteScannerFunc(tmp);
               
        }
        static void ASCII_TexteScannerFunc(string texte)
        {
            int[] alpha = { 0xFF };
            int x = 0;
            do
            {
                for(int y=0x13; y<0xFF; y++)
                {
                    if (texte[x] == y) alpha[x] = y;
                    Console.Write($"{texte[x]} donne le caractere {(char)y} contenu {alpha[x]} fois dans la sequence");
                }
            } while( x < texte.Length);
            for (int a=0; a <0xFF; a++)
            {
                Console.WriteLine($"{a} donne le caractere {(char)a} contenu {alpha[a]} fois dans la sequence");
            }
        }
    }
}

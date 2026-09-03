// DecomposeurBinaire.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>

int tableBin[17];
int ValeurtableBin[17];

void CreerTableDe2()
{
    for(int a=0; a<17; a++)
    {
        tableBin[a] = pow(2, a);
    }

}

int RechercherLaPlusHautePuissance(int Valeur,int reste)
{
    for (int a = 0; a < 17; a++)
        if (pow(2, a) > Valeur)
        {
            printf("\n%d :: %5.0lf :: reste %d", a, Valeur - (pow(2, a)),reste);
            reste=Valeur-(pow(2,a));
    return a-1;
        }
}

int main()
{
    CreerTableDe2();
    int x = 4125;
    int reste = 0;
    std::cout << "Hello World!\n";
    int pMax = RechercherLaPlusHautePuissance(x,reste);
    printf("\nValeur de x=%d a retourne une puissance de 2^%d  reste %d", x,pMax,reste);
  
}

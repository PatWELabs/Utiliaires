// Comparateur2Salaire.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    double capital, taux, total,capital2,taux2,total2;
    std::string tmp; std::string tmp2;
    int nAnnees=1;
    SetConsoleTitleA("Calculateur de progression pour Investissement");
    std::cout << "Programme developppe dans le cadre de l'AEC!\nBase sur un taux fixe\n\nEntrez le montant du salaire initial fourni par la 1ere compagnie ";
    std::cin >> capital;
    std::cout << "Entrez le montant d'augmentation ";
    cin >> tmp;
    taux = atof(tmp.c_str());
    std::cout << "nEntrez le montant du salaire initial fourni par la 2e compagnie ";
    std::cin >> capital2;
    std::cout << "Entrez le montant d'augmentation ";
    cin >> tmp2;
    taux2 = atof(tmp2.c_str());
    total = capital + taux;
    total2 = capital2 + taux2;
    std::cout << "Total de la 1ere annee " << total << " soit un gain de " << total - capital << "$\n";
    std::cout << "Total de la 1ere annee " << total2 << " soit un gain de " << total2 - capital2 << "$\n";
    double nCapital,nCapital2;
    while(total!=total2){
        nAnnees++;
        nCapital = total;
        nCapital2 = total2;
        total = nCapital + taux;
        total2 = nCapital2 + taux2;
        std::cout << "Expansion " << nAnnees + 1 << "e annee  Compagnie 1:" << total << "^$ Compagnie 2:" << total2 << "$\n";
        if (total > total2) { std::cout << "Nombre d'annees " << nAnnees +1;   return 0x01;  }
    }
}

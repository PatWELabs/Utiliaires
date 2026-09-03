#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

static void Pause2s(){printf("\nTerminer ? (attente 2s)\n");Sleep(2000);}
static void ClearScreen(){system("cls");}
static void FormatageBinaire(const char* in, char* out)
{
    int len = strlen(in);
    int i, j = 0;
    int count = 0;
    for (i = 0; i < len; i++)
    {
        out[j++] = in[i];
        count++;
        if (count == 4 && i != len - 1){out[j++] = ' ';count = 0;}
    }
    out[j] = '\0';
}
static void DecimalEnBinaire(unsigned int value, char* out)
{
    char temp[128]{};
    int index = 0;
    if (value == 0){strcpy(out, "0");return;}
    while (value > 0){temp[index++] = (value % 2) ? '1' : '0';value /= 2;}
    int i;
    for (i = 0; i < index; i++)out[i] = temp[index - 1 - i];
    out[index] = '\0';
}
static unsigned int BinaireEnDecimal(const char* bin)
{
    unsigned int result = 0;
    int i;
    int len = strlen(bin);
    for (i = 0; i < len; i++)
    {
        if (bin[i] != '0' && bin[i] != '1'){printf("Erreur: valeur binaire invalide.\n");return 0;}
        result = result * 2 + (bin[i] - '0');
    }
    return result;
}
static void Operations(const char* b1, const char* b2, int mode, int details)
{
    unsigned int v1 = BinaireEnDecimal(b1);
    unsigned int v2 = BinaireEnDecimal(b2);
    unsigned int result = 0;
    double fresult = 0.0;
    if (details)
    {
        printf("\n--- MODE DTAILL ---\n");
        printf("b1 = %s -> %u\n", b1, v1);
        printf("b2 = %s -> %u\n", b2, v2);
    }
    switch (mode)
    {
    case 1: result = v1 + v2; break;
    case 2: result = v1 - v2; break;
    case 3: result = v1 * v2; break;
    case 4:
        if (v2 == 0){printf("Division par z‚ro !\n");return;}
        result = v1 / v2;
        break;
    case 5:
        if (v2 == 0){printf("Fraction impossible (division par z‚ro)\n");return;}
        fresult = (double)v1 / (double)v2;
        break;
    case 6:
        result = 1;
        for (unsigned int i = 0; i < v2; i++) result *= v1;
        break;
    }
    if (mode == 5)
    {
        printf("R‚sultat fraction = %.6f\n", fresult);
    }
    else
    {
        char bin[128];
        char spaced[128];
        DecimalEnBinaire(result, bin);
        FormatageBinaire(bin, spaced);
        printf("R‚sultat d‚cimal = %u\n", result);
        printf("R‚sultat binaire = %s\n", spaced);
    }
}
static void Menu()
{
    int choix;
    char b1[128], b2[128];
    while (1)
    {
        ClearScreen();
        printf("=== CALCULATEUR BINAIRE AVANCE ===\n\n");
        printf("1 - Addition\n");
        printf("2 - Soustraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - Fraction (v1/v2)\n");
        printf("6 - Puissance (v1^v2)\n");
        printf("7 - Addition d‚taill‚e\n");
        printf("8 - Soustraction d‚taill‚e\n");
        printf("9 - Multiplication d‚taill‚e\n");
        printf("10 - Division d‚taill‚e\n");
        printf("11 - Fraction d‚taill‚e\n");
        printf("12 - Puissance d‚taill‚e\n");
        printf("13 - Quitter\n\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        if (choix == 13)return;
        if (choix < 1 || choix > 13){printf("Choix invalide.\n");Pause2s();continue;}
        printf("Entrez binaire 1 : ");
        scanf("%s", b1);
        printf("Entrez binaire 2 : ");
        scanf("%s", b2);
        int mode = choix;
        int details = 0;
        if (choix >= 7 && choix <= 12){mode -= 6;details = 1;}
        Operations(b1, b2, mode, details);
        Pause2s();
    }
}
int main(){Menu();return 0;}

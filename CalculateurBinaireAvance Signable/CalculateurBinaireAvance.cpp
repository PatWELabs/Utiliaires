#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
static void ClearScreen(){system("cls");}
static void Pause2s(){    printf("\nTerminer ? (attente 2s)\n");  Sleep(2000);}
static void FormatBinary(const char* in, char* out)
{
    int len = strlen(in);
    int i, j = 0, count = 0;
    for (i = 0; i < len; i++)
    {
        out[j++] = in[i];count++;
        if (count == 4 && i != len - 1){out[j++] = ' ';count = 0;}
    }
    out[j] = '\0';}
static int CoontroleErreurBinaire(const char* bin)
{
    int len = strlen(bin);
    int i;
    if (len == 0){printf("Erreur: chaîne vide.\n");return 1;}
    for (i = 0; i < len; i++)
    {
        if (bin[i] != '0' && bin[i] != '1'){printf("Erreur: caractère invalide '%c'.\n", bin[i]);return 1;}
    }
    if (len > 32){printf("Erreur: dépassement 32 bits (%d bits).\n", len);return 1;}
    return 0;
}
static int BinaireEnDecimalSigne(const char* bin)
{
    int len = strlen(bin);
    int sign = bin[0] == '1'; // bit de signe
    int value = 0;
    int i;
    if (!sign)
    {
        for (i = 0; i < len; i++)value = (value << 1) | (bin[i] - '0');
        return value;
    }
    int temp = 0;
    for (i = 0; i < len; i++)temp = (temp << 1) | (bin[i] - '0');
    int max = 1 << len;
    return temp - max;
}
static void DecimalEnBinaireSigne(int value, int bits, char* out)
{
    unsigned int mask = (1 << bits) - 1;
    unsigned int v = (unsigned int)value & mask;
    int i;
    for (i = bits - 1; i >= 0; i--){out[bits - 1 - i] = ((v >> i) & 1) ? '1' : '0';}
    out[bits] = '\0';
}
static void OperationsSignees(const char* b1, const char* b2, int mode, int details)
{
    if (CoontroleErreurBinaire(b1) || CoontroleErreurBinaire(b2)) return;
    int len1 = strlen(b1);
    int len2 = strlen(b2);
    int bits = (len1 > len2) ? len1 : len2;
    int v1 = BinaireEnDecimalSigne(b1);
    int v2 = BinaireEnDecimalSigne(b2);
    int result = 0;
    if (details)
    {
        printf("\n--- MODE DÉTAILLÉ ---\n");
        printf("b1 = %s -> %d\n", b1, v1);
        printf("b2 = %s -> %d\n", b2, v2);
    }
    switch (mode)
    {
        case 1: result = v1 + v2; break;
        case 2: result = v1 - v2; break;
        case 3: result = v1 * v2; break;
        case 4:
            if (v2 == 0)
            {
                printf("Division par zéro !\n");
                return;
            }
            result = v1 / v2;
            break;
        case 5:
            if (v2 == 0)
            {
                printf("Fraction impossible (division par zéro)\n");
                return;
            }
            printf("Résultat fraction = %.6f\n", (double)v1 / (double)v2);
            return;
        case 6:
        {
            result = 1;
            int i;
            for (i = 0; i < v2; i++)
                result *= v1;
        }
        break;
    }
    char bin[64];
    char spaced[64];
    DecimalEnBinaireSigne(result, bits, bin);
    FormatBinary(bin, spaced);
    printf("Résultat décimal signé = %d\n", result);
    printf("Résultat binaire signé = %s\n", spaced);
}
static void MenuPrincipal()
{
    int choix;
    char b1[64], b2[64];
    while (1)
    {
        ClearScreen();
        printf("=== CALCULATEUR BINAIRE SIGNE VS6 ===\n\n");
        printf("1 - Addition\n");
        printf("2 - Soustraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - Fraction (v1/v2)\n");
        printf("6 - Puissance (v1^v2)\n");
        printf("7 - Addition détaillée\n");
        printf("8 - Soustraction détaillée\n");
        printf("9 - Multiplication détaillée\n");
        printf("10 - Division détaillée\n");
        printf("11 - Fraction détaillée\n");
        printf("12 - Puissance détaillée\n");
        printf("13 - Quitter\n\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        if (choix == 13)return;
        if (choix < 1 || choix > 13){printf("Choix invalide.\n");Pause2s();continue;}
        printf("Entrez binaire signé 1 : ");
        scanf("%s", b1);
        printf("Entrez binaire signé 2 : ");
        scanf("%s", b2);
        int mode = choix;
        int details = 0;
        if (choix >= 7 && choix <= 12){mode -= 6;details = 1;}
        OperationsSignees(b1, b2, mode, details);
        Pause2s();
    }
}
int main()
{
    MenuPrincipal();
    return 0;
}

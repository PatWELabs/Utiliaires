// BinaireVirguleFlottante2Decimal_v1.01.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
//11101010010101100000000000000000

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:4244)
int signe= 0;
int TableBinaire[64];
bool exposant32[8] = { 0 };
bool mantisse32[23] = { 0 };
bool Table32[32] = {0};
bool exposant64[11] = { 0 };
bool mantisse64[52] = { 0 };
bool Table64[64] = { 0 };
int TableDecimauxExposants[52];
bool positif = 1;
int exposantExces = 0;
HANDLE console;

void ProcedeFloat();
void ProcedeDouble();
void Erreur(char* Message);
void Erreur(char* Message, int code);

bool SauvegarderTamponConsole() { //base sur les API decrites dans MSDN
    Erreur((char*)"L'agorithme de sauvegarde est un prototype\n Il est probable que le texte généré nse soit pas alligné correctement dans un éditeur Windows");
    FILE* f = fopen("SauvegardeTamponMemoireConsole.txt", "w+");
    HANDLE hStdout;
    SMALL_RECT srctReadRect;
    CHAR_INFO chiBuffer[0x4FFF]; // [256][80];
    COORD coordBufSize;
    COORD coordBufCoord;
    BOOL fSuccess;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    srctReadRect.Top = 0;
    srctReadRect.Left = 0;
    srctReadRect.Bottom = 0xFF;
    srctReadRect.Right = 0x4F;
    coordBufSize.Y = srctReadRect.Bottom;
    coordBufSize.X = srctReadRect.Right;
    coordBufCoord.X = 0;
    coordBufCoord.Y = 0;
    fSuccess = ReadConsoleOutput(hStdout, chiBuffer, coordBufSize, coordBufCoord, &srctReadRect);
    srctReadRect = { 0 };
    if (!fSuccess)
    {
        printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
        return 1;
    }
    for (int a = 0; a < 0x4FFF; a++)
    {
        fprintf(f, "%c", chiBuffer[a].Char.AsciiChar);
        if (chiBuffer[a].Char.AsciiChar == '\n')
        {
            fprintf(f, "%c%c", 0x0A, 0x0D);
        }
    }
    return fclose(f);
}


void ProcedeFloat() {
     int posmant ;
    for (int a = 7; a >= 0; a--)
    {
        exposant32[a] = pow(2, a);
    }
    printf("\nTable des exposants generee\n");
    if (Table32[0]==1)
    {
        printf("Valeur négative");
    }
    else 
    {
        printf("Valeur positive");
    }
    printf("\nExposant en binaire par excés[127] : %.1d%.1d%.1d%.1d%.1d%.1d%.1d%.1d\n" , Table32[2], Table32[3], Table32[4], Table32[5], Table32[6], Table32[7], Table32[8], Table32[9]);
    int b=0;
    for (int a = 2; a <8; a++) 
    {
        if (Table32[a] == 1) 
        {
            b += exposant32[7 - a];
        }     
    }
    //calcule la valeur des bits de l'exposant au format theorique (8bits)
    for (int a = 1; a <9; a++) {
        printf("\nTable32 pos: %d actif:%d ==>%d", a,Table32[a],(int) (Table32[a]* pow(2,(8 - a))));
        b += (int)(Table32[a] * pow(2, (8 - a)));
    }
    exposantExces = b - 0x7F;
    // resout l'equation par exces
    printf("\nRetrait de l'excés = %d-127=%d", b, exposantExces);
    printf("\n\nExposant par excés %d\n", exposantExces);
    for (int i = 31; i >= 9; i--) {
        if (Table32[i] == '1') break;
            posmant = i - 9;
    }
    for (int a = 0; a < posmant; a++) {
        int c = 0;
        printf("Traitement mantisse position %d ?<", a);
        scanf("%d", &c);
        mantisse32[a] = c;
        Table32[a + 9] = c;
    }
    float valeur = 0,nval=0;
    for (int a = 0; a < 24; a++) {
        if (mantisse32[a] == 1) {
            if (a == 0) { 
                valeur = .5;
                printf("\nbit %d ==> %f",a, valeur);
                nval += valeur;
            }
            else {
                valeur = pow(2, (0 - a));
                nval += valeur;
                printf("\nbit %d ==> %f", a, valeur);
            }
        }
    }
    printf("\nTotal décimal: %.5lf", nval);
    //epose la forme exponentielle
    printf("\nForme exponentielle :");
    //signer
        if (positif) {
            printf("(1,");
        }
        else 
        {
            printf("-(1,");
        }
    char matMantisse[23];
    matMantisse[0] = 0x31;
    for (int a = 0; a < posmant; a++) {
            printf("%d", mantisse32[a]);
        matMantisse[a + 1] = (mantisse32[a]+0x30);
    }
    //remet la virgue a sa place
    printf(")[2]x2^%d\nRésultat: ", exposantExces);
    for (int a = 0; a <= posmant; a++) {
        if (a == posmant - exposantExces+1) //ajouter +1 a cause du 1, dans la mantisse
        {
            printf(",");
        }
        printf("%c",matMantisse[a]);
    }
    printf("\nConvertion Table 32bits vers Norme IEEE 754\n");
    for (int a = 0; a < 32; a++) {
        printf("%d", Table32[a]);
        if (a == 0 || a == 8) {
            printf("|");
        }
    }
    
   
}
void ProcedeDouble() {
    int posmant;
    for (int a = 11; a >= 0; a--)
    {
        exposant64[a] = pow(2, a);
    }
    printf("\nTable des exposants générée\nEntrez le 1er chiffre de la représentation flotante: ");
    scanf("%d", &signe);
    if (signe == 0 || signe == 1)
    {
        positif = signe;
        Table64[0] = signe;
    }
    if (positif)
    {
        printf("Valeur négative");
    }
    else
    {
        printf("Valeur positive");
    }
    printf("\nEntrez les 11 chiffes de l'exposant\n");
    int b = 0;
    for (int x = 0; x < 11; x++) { //realoue les  bits dans la table des exposants
        printf("Position %d : valeur: %d : ?", x + 1, exposant32[11 - x]);
        scanf("%d", &b);
        exposant64[x] = b;
        Table64[x + 1] = b;
    }
    //inscrit l'exposant entre les bits 1 et 12
    printf("Mise a jour info Table 64bits\n");
    printf("Exposant en binaire par excés[1023] : %.1d%.1d%.1d%.1d%.1d%.1d%.1d%.1d%.1d%.1d%.1d\n", exposant64[0], exposant64[1], exposant64[2], exposant64[3], exposant64[4], exposant64[5], exposant64[6], exposant64[7], exposant64[8], exposant64[9], exposant64[10]);
    for (int a = 0; a < 12; a++)
    {
        if (exposant64[a] == 1)
        {
            b += exposant32[13 - a];
        }
    }
    //calcule la valeur des bits de l'exposant au format theorique (8bits)
    for (int a = 1; a < 12; a++) {
        printf("\nTable64 pos: %d actif:%d ==>%d", a, Table64[a], (Table64[a] * exposant32[12 - a]));
    }
    exposantExces = b - 0x3FF;//1023 en 64bit
    // resout l'equation par exces
    printf("\nRetrait de l'excés = %d-1023=%d", b, exposantExces);
    printf("\nExposant par excés %d\n", exposantExces);
    printf("\nPosition du dernier 1 dans la mantisse: [1 a 53]?");
    scanf("%d", &posmant);
    for (int a = 0; a < posmant; a++) {
        int c = 0;
        printf("Traitement mantisse position %d ?<", a);
        scanf("%d", &c);
        mantisse64[a] = c;
        Table64[a + 9] = c;
    }
    float valeur = 0, nval = 0;
    for (int a = 0; a < 53; a++) {
        if (mantisse64[a] == 1) {
            if (a == 0) {
                valeur = .5;
                printf("\nbit %d ==> %f", a, valeur);
                nval += valeur;
            }
            else {
                valeur = pow(2, (0 - a));
                nval += valeur;
                printf("\nbit %d ==> %f", a, valeur);
            }
        }
    }
    printf("\nTotal décimal: %.5lf", nval);
    //epose la forme exponentielle
    printf("\nForme exponentielle :");
    //signer
    if (positif) {
        printf("(1,");
    }
    else
    {
        printf("-(1,");
    }
    char matMantisse[52];
    matMantisse[0] = 0x31;
    for (int a = 0; a < posmant; a++) {
        printf("%d", mantisse64[a]);
        matMantisse[a + 1] = (mantisse64[a] + 0x30);
    }
    //remet la virgue a sa place
    printf(")[2]x2^%d\nRésultat: ", exposantExces);
    for (int a = 0; a <= posmant; a++) {
        if (a == posmant - exposantExces + 1) //ajouter +1 a cause du 1, dans la mantisse
        {
            printf(",");
        }
        printf("%c", matMantisse[a]);
    }
    printf("\nConvertion Table 64bits vers Norme IEEE 754\n");
    for (int a = 0; a < 64; a++) {
        printf("%d", Table64[a]);
        if (a == 0 || a == 8) {
            printf("|");
        }
    }
}
void Erreur(char* Message) {
    SetConsoleTextAttribute(console,  FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%s\n", Message);
    SetConsoleTextAttribute(console,  FOREGROUND_GREEN | FOREGROUND_INTENSITY);

}
void Erreur(char* Message,int code) {
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%d %s\n",code, Message);
    SetConsoleTextAttribute(console,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
int main()
{
    //look style PowerShell
    char fill = (char)0x00; 
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(0xFDE9); //francais Canada
    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
    //initialisation programme
    printf("Convertion de Virgule flottante 32/64bit vers décimal!\n%cPatrice Waechter-Ebling 2022\tApplications.Maths.Appliquées.Info\tv1.01\n\n",184);
    char tmp[64];
   //Generation table binaire 
    for (int a = 63; a >= 0; a--)
    {
        TableBinaire[a] = pow(2, a);
    }
    //menu
    std::cout << "\n Représentation [32 ou 64] bits à détection automatique \nPWE?> ";

    scanf("%s", &tmp);
    int i = strlen(tmp);
    printf("%d octets entrés\nNormalisation IEEE 754\n", i);
   switch (i) {
        case 32:{
          for (int a = 0; a < i; a++) 
          {
                if (a == 1 || a == 9) printf("|");
                Table32[a] = (int)(tmp[a]-48);
                printf("%d", Table32[a]);
          }
          ProcedeFloat();  
        }break;
        case 64:{
            for (int a = 0; a < i; a++)
            {
                if (a == 1 || a == 12) printf("|");
                Table64[a] = (int)(tmp[a] - 48);
                printf("%d", Table64[a]);
            }
            ProcedeDouble(); 
        }break;
        default: {
            Erreur((char*)"\n non valide possibilitées 32 ou 64 \nViolation des paramètres\nAbandon du programme\n",i);
        }break;
    }
     SauvegarderTamponConsole();
    return 0;
}
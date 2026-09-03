#pragma warning (disable:4267) 
#pragma warning (disable:6031)
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HISTORY 100
char history[MAX_HISTORY][256];
int  historyCount = 0;
int  logEnabled = 0;   // 0 = pas de log, 1 = log activé
static void AjouterHistorique(const char* entry)
{
    if (historyCount < MAX_HISTORY) strcpy(history[historyCount++], entry);
}
static void EnregistrerLog(const char* entry)
{
    if (!logEnabled)return;
    FILE* f = fopen("conversion.log", "a");
    if (f){fprintf(f, "%s\n", entry);fclose(f);}
}
static void FormatagePourBinaire(const char* in, char* out)
{
    int len = strlen(in);
    int i, j = 0;
    for (i = 0; i < len; i++)
    {
        out[j++] = in[i];
        if ((i % 4) == 3 && i != len - 1)out[j++] = ' ';
    }
    out[j] = '\0';
}
static int BinaireEnDecimal(const char* bin, int details)
{
    int result = 0;
    int len = strlen(bin);
    int i;
    for (i = 0; i < len; i++)
    {
        if (bin[i] != '0' && bin[i] != '1'){printf("Erreur: valeur binaire invalide.\n");return -1;}
        result = result * 2 + (bin[i] - '0');
        if (details)printf("Étape %d : bit=%c -> résultat=%d\n", i + 1, bin[i], result);
    }
    return result;
}
static void DecimalEnBinaire(int value, char* out, int details)
{
    char temp[64];
    int index = 0;
    if (value == 0){strcpy(out, "0");return;}
    while (value > 0)
    {
        int bit = value % 2;
        temp[index++] = bit ? '1' : '0';
        if (details) printf("value=%d | %d\n", value, bit); 
        value /= 2;
    }
    int i;
    for (i = 0; i < index; i++)out[i] = temp[index - 1 - i];
    out[index] = '\0';
}
static int SousMenuOperation(int loopMode)
{
    if (loopMode)return 1;
    int choix;
    printf("\n1 - Retour au menu\n");
    printf("2 - Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    switch (choix) {
        case 2:return 0; break;
    }
    return 1;
}
static void MenuOperation()
{
    int choix;
    char buffer[128];
    bool loopMode = 0; // 0 = pause, 1 = boucle continue
    while (1)
    {
        system("cls");
        printf("\n=== MENU CONVERSION ===\n");
        printf("1 - Convertir binaire vers décimal\n");
        printf("2 - Convertir décimal vers binaire\n");
        printf("3 - Convertir binaire vers décimal (détaillé)\n");
        printf("4 - Convertir décimal vers binaire (détaillé)\n");
        printf("5 - Activer/Désactiver mode boucle continue (actuel: %s)\n",loopMode ? "ACTIVÉ" : "DÉSACTIVÉ");
        printf("6 - Afficher historique des conversions\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        system("cls");
        switch (choix) {
            case 0: {
                printf("Au revoir.\n");
                return;
            }break;
            case 1: {
                printf("Entrez une valeur binaire : ");
                scanf("%s", buffer);
                int dec = BinaireEnDecimal(buffer, 0);
                if (dec >= 0)
                {
                    printf("Décimal = %d\n", dec);
                    char log[256];
                    sprintf(log, "Bin2Dec : %s = %d", buffer, dec);
                    AjouterHistorique(log);
                    EnregistrerLog(log);
                }
                if (!SousMenuOperation(loopMode)) return;
            }break;
            case 2: {
                int val;
                char bin[64];
                char formatted[128];
                printf("Entrez une valeur décimale : ");
                scanf("%d", &val);
                DecimalEnBinaire(val, bin, 0);
                FormatagePourBinaire(bin, formatted);
                printf("Binaire = %s\n", formatted);
                char log[256];
                sprintf(log, "Dec2Bin : %d = %s", val, formatted);
                AjouterHistorique(log);
                EnregistrerLog(log);
                if (!SousMenuOperation(loopMode)) return;
            }break;
            case 3: {
                printf("Entrez une valeur binaire : ");
                scanf("%s", buffer);
                int dec = BinaireEnDecimal(buffer, 1);
                if (dec >= 0)
                {
                    printf("Décimal = %d\n", dec);
                    char log[256];
                    sprintf(log, "Bin2Dec: %s = %d", buffer, dec);
                    AjouterHistorique(log);
                    EnregistrerLog(log);
                }
                if (!SousMenuOperation(loopMode)) return;
            }break;
            case 4: {
                int val;
                char bin[64];
                char formatted[128];
                printf("Entrez une valeur décimale : ");
                scanf("%d", &val);
                DecimalEnBinaire(val, bin, 1);
                FormatagePourBinaire(bin, formatted);
                printf("Binaire = %s\n", formatted);
                char log[256];
                sprintf(log, "Dec2Bin: %d = %s", val, formatted);
                AjouterHistorique(log);
                EnregistrerLog(log);
                if (!SousMenuOperation(loopMode)) return;
            }break;
            case 5: {
                loopMode = !loopMode;
                printf("Mode boucle continue %s.\n", loopMode ? "ACTIVÉ" : "DÉSACTIVÉ");
                if (!SousMenuOperation(loopMode)) return;
            }break;
            case 6: {
                printf("=== HISTORIQUE ===\n");
                int i;
                for (i = 0; i < historyCount; i++)printf("%s\n", history[i]);
                if (!SousMenuOperation(loopMode)) return;
            }break;
            default: {
                printf("Choix invalide.\n");
                if (!SousMenuOperation(loopMode)) return;
            }break;
        }
    }
}
int main(int argc, char* argv[])
{
    int details = 0;
    logEnabled = 0;
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "/d") == 0)details = 1;
        if (strcmp(argv[i], "/log") == 0)logEnabled = 1;
        if (strcmp(argv[i], "/nolog") == 0)logEnabled = 0;
    }
    if (argc == 1 || (argc >= 2 && argv[1][0] != '-' && argv[1][0] != '/')){MenuOperation();return 0;}
    if (argc >= 3)
    {
        if (strcmp(argv[1], "-bin") == 0)
        {
            int dec = BinaireEnDecimal(argv[2], details);
            if (dec >= 0)
            {
                printf("Décimal = %d\n", dec);
                char log[256];
                sprintf(log, "Bin2Dec : %s = %d", argv[2], dec);
                EnregistrerLog(log);
            }
            return 0;
        }
        else if (strcmp(argv[1], "-dec") == 0)
        {
            int val = atoi(argv[2]);
            char bin[64];
            char formatted[128];
            DecimalEnBinaire(val, bin, details);
            FormatagePourBinaire(bin, formatted);
            printf("Binaire = %s\n", formatted);
            char log[256];
            sprintf(log, "Dec2Bin : %d = %s", val, formatted);
            EnregistrerLog(log);
            return 0;
        }
    }
    printf("Usage:\n");
    printf("  convert -bin <valeur> [/d] [/log] [/nolog]\n");
    printf("  convert -dec <valeur> [/d] [/log] [/nolog]\n");
    printf("  convert\n");
    return 0;
}

// AjoutUtilisateurSSH_RS232.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SMALL   256
#define BUF_MEDIUM  1024
#define BUF_LARGE   4096
#define COLOR_DEFAULT 7
#define COLOR_INFO    11
#define COLOR_WARN    14
#define COLOR_ERROR   12
#define COLOR_OK      10
#define COLOR_BOX     9 | FOREGROUND_GREEN | FOREGROUND_INTENSITY  
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma warning(disable : 4996) /* pour les fonctions de string non sécurisées */
HANDLE hSerial = INVALID_HANDLE_VALUE;
volatile int gRunRX = 1;

char gVendor[64];
int  gPrompt = 0;   /* 0=unknown, 1=user, 2=priv, 3=config */
enum {PROMPT_UNKNOWN = 0,PROMPT_USER = 1,   /* > */PROMPT_PRIV = 2,   /* # */PROMPT_CONFIG = 3    /* (config)# */};

static void Colorier(int c){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);}
static void Cadre(const char* text)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),COLOR_BOX|FOREGROUND_GREEN|FOREGROUND_RED);
    int len = strlen(text);
    int width = len + 4;
    int i;
    printf("%c",0xC9);
    for (i = 0; i < width; i++) printf("%c",0xCD);
    printf("%c\n",0xBB);
    printf("%c  %s  %c\n",0xBA   ,text,0xBA);
    printf("%c",0xC8);
    for (i = 0; i < width; i++) printf("%c",0xCD);
    printf("%c\n",0xBC);
    Colorier(COLOR_DEFAULT);
}
static int Lecture(char* buf, int maxLen, DWORD timeoutMs)
{
    DWORD start = GetTickCount();
    DWORD total = 0;
    while ((GetTickCount() - start) < timeoutMs && total < (DWORD)(maxLen - 1))
    {
        DWORD read = 0;
        if (ReadFile(hSerial, buf + total, maxLen - 1 - total, &read, NULL) && read > 0){total += read;}
        else{Sleep(10);}
    }
    buf[total] = 0;
    return (int)total;
}
DWORD WINAPI LectureRX(LPVOID lp)
{
    char buf[BUF_MEDIUM];
    DWORD read;
    while (gRunRX)
    {
        if (ReadFile(hSerial, buf, BUF_MEDIUM - 1, &read, NULL) && read > 0)
        {
            buf[read] = 0;
            Colorier(COLOR_OK);
            printf("%s", buf);
            Colorier(COLOR_DEFAULT);
        }
        else{Sleep(10);}
    }
    return 0;
}
static void EnvoiDirect(const char* s){DWORD written;WriteFile(hSerial, s, (DWORD)strlen(s), &written, NULL);}
static void EnvoiLigne(const char* s)
{
    char out[BUF_SMALL];
    sprintf(out, "%s\r", s);
    EnvoiDirect(out);
    Sleep(80);
}
static int DetectionPrompt(const char* s)
{
    int len = strlen(s);
    if (strstr(s, "(config") != NULL)  return PROMPT_CONFIG;
    if (strchr(s, '#') != NULL)        return PROMPT_PRIV;
    if (strchr(s, '>') != NULL)        return PROMPT_USER;
    return PROMPT_UNKNOWN;
}
static void ActualiserPrompt()
{
    char buf[BUF_LARGE];
    int n = Lecture(buf, BUF_LARGE, 500);
    if (n > 0)
    {
        int p = DetectionPrompt(buf);
        if (p != PROMPT_UNKNOWN)gPrompt = p;
    }
}
static int ConfigurationDebit(DWORD baud)
{
    DCB dcb;
    COMMTIMEOUTS t;
    memset(&dcb, 0, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(hSerial, &dcb))return 0;
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcb))return 0;
    memset(&t, 0, sizeof(t));
    t.ReadIntervalTimeout = 50;
    t.ReadTotalTimeoutConstant = 50;
    t.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &t);
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    return 1;
}
static int DebitAutomatique(DWORD* foundBaud)
{
    DWORD bauds[] = { 9600, 19200, 38400, 57600, 115200 };
    int i;
    char buf[BUF_MEDIUM];
    for (i = 0; i < 5; i++)
    {
        DWORD b = bauds[i];
        if (!ConfigurationDebit(b))continue;
        EnvoiDirect("\r\r\r");
        Sleep(500);
        int n = Lecture(buf, BUF_MEDIUM, 800);
        if (n > 0)
        {
            int k;
            int printable = 0;
            for (k = 0; k < n; k++)
            {
                if (buf[k] >= 0x20 && buf[k] <= 0x7E){printable = 1;break;}
            }
            if (printable){*foundBaud = b;return 1;}
        }
    }
    return 0;
}
static int OuvrirPortCOM(const char* port)
{
    hSerial = CreateFileA(port,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if (hSerial == INVALID_HANDLE_VALUE)return 0;
    if (!ConfigurationDebit(9600))return 0;
    return 1;
}
static void AfficherTypePrompt()
{
    Colorier(COLOR_INFO);
    if (gPrompt == PROMPT_USER)        printf("Prompt detecte : USER (>).\n");
    else if (gPrompt == PROMPT_PRIV)   printf("Prompt detecte : PRIV (#).\n");
    else if (gPrompt == PROMPT_CONFIG) printf("Prompt detecte : CONFIG ((config)#).\n");
    else printf("Prompt detecte : INCONNU.\n");
    Colorier(COLOR_DEFAULT);
}
static int ConfirmerON(const char* question)
{
    char buf[BUF_SMALL];
    Cadre(question);
    Colorier(COLOR_WARN);
    printf("(o/n) : ");
    Colorier(COLOR_DEFAULT);
    fgets(buf, BUF_SMALL, stdin);
    if (buf[0] == 'o' || buf[0] == 'O' || buf[0] == 'y' || buf[0] == 'Y')return 1;
    return 0;
}
static void ActiverModePrivilegie(const char* enablePassword)
{
    ActualiserPrompt();
    AfficherTypePrompt();
    if (gPrompt == PROMPT_PRIV || gPrompt == PROMPT_CONFIG)        return;
    if (!ConfirmerON("Le switch est en mode USER (>). Voulez-vous passer en ENABLE ?"))        return;
    EnvoiLigne("enable");
    Sleep(300);
    if (enablePassword != NULL && enablePassword[0] != 0){EnvoiLigne(enablePassword);Sleep(300);}
    ActualiserPrompt();
    AfficherTypePrompt();
}
void EnsureConfigMode(const char* enablePassword)
{
    ActualiserPrompt();
    AfficherTypePrompt();
    if (gPrompt == PROMPT_CONFIG)return; /* déjà en config */
    if (gPrompt == PROMPT_USER)ActiverModePrivilegie(enablePassword);
    if (!ConfirmerON("Voulez-vous entrer en mode configuration (conf t) ?"))return;
    EnvoiLigne("conf t");
    Sleep(300);
    ActualiserPrompt();
    AfficherTypePrompt();
}
static void SortieModeConfig()
{
    ActualiserPrompt();
    if (gPrompt == PROMPT_CONFIG)
    {
        if (ConfirmerON("Vous etes en mode CONFIG. Voulez-vous revenir en mode PRIV (#) ?"))
        {
            EnvoiLigne("end");
            Sleep(300);
            ActualiserPrompt();
            AfficherTypePrompt();
        }
    }
}
static void DetectVendor()
{
    char buf[BUF_LARGE];
    int n;
    memset(gVendor, 0, sizeof(gVendor));
    strcpy(gVendor, "Unknown");
    Cadre("Detection du vendor en cours...");
    EnvoiLigne("");
    Sleep(300);
    EnvoiLigne("show version");
    Sleep(1500);
    n = Lecture(buf, BUF_LARGE, 1000);
    if (n <= 0)
    {
        Colorier(COLOR_ERROR);
        printf("Aucune reponse au show version.\n");
        Colorier(COLOR_DEFAULT);
        return;
    }

    if (strstr(buf, "Cisco") != NULL)        strcpy(gVendor, "Cisco");
    else if (strstr(buf, "Aruba") != NULL)   strcpy(gVendor, "Aruba");
    else if (strstr(buf, "HP ") != NULL || strstr(buf, "ProCurve") != NULL)        strcpy(gVendor, "HP");
    else if (strstr(buf, "Juniper") != NULL) strcpy(gVendor, "Juniper");
    Colorier(COLOR_INFO);
    printf("Vendor detecte : %s\n", gVendor);
    Colorier(COLOR_DEFAULT);
}
/// <summary>
/// J'ai utilisé l'IA pour générer automatiquement les commandes
/// de configuration SSH en fonction du vendor détecté.
/// </summary>
static void GenererScriptSSH(char script[][BUF_SMALL], int* count,const char* user, const char* pass)
{
    int i = 0;
    memset(script, 0, sizeof(char) * 100 * BUF_SMALL);
    *count = 0;
    if (strcmp(gVendor, "Cisco") == 0)
    {
        strcpy(script[i++], "username ");
        strcat(script[i - 1], user);
        strcat(script[i - 1], " privilege 15 secret ");
        strcat(script[i - 1], pass);
        strcpy(script[i++], "ip ssh version 2");
        strcpy(script[i++], "line vty 0 4");
        strcpy(script[i++], "login local");
        strcpy(script[i++], "transport input ssh");
        strcpy(script[i++], "end");
        strcpy(script[i++], "wr mem");
    }
    else if (strcmp(gVendor, "HP") == 0 || strcmp(gVendor, "Aruba") == 0)
    {
        strcpy(script[i++], "password manager user-name ");
        strcat(script[i - 1], user);
        strcat(script[i - 1], " plaintext ");
        strcat(script[i - 1], pass);

        strcpy(script[i++], "crypto key generate ssh rsa");
        strcpy(script[i++], "ip ssh");
        strcpy(script[i++], "write memory");
    }
    else if (strcmp(gVendor, "Juniper") == 0)
    {
        strcpy(script[i++], "set system login user ");
        strcat(script[i - 1], user);
        strcat(script[i - 1], " class super-user");
        strcpy(script[i++], "set system login user ");
        strcat(script[i - 1], user);
        strcat(script[i - 1], " authentication plain-text-password");
        strcpy(script[i++], "# Tapez le mot de passe manuellement : ");
        strcat(script[i - 1], pass);
        strcpy(script[i++], "commit");
        strcpy(script[i++], "exit");
    }
    else{strcpy(script[i++], "echo Vendor inconnu, script non disponible");}
    *count = i;
}
static void EnvoiScriptSSH(char script[][BUF_SMALL], int count,const char* enablePassword)
{
    int i;
    Cadre("Envoi du script SSH");
    for (i = 0; i < count; i++)
    {
        if (strcmp(script[i], "end") == 0){SortieModeConfig();continue;}
        if (strstr(script[i], "username") != NULL ||strstr(script[i], "ip ssh") != NULL ||strstr(script[i], "line vty") != NULL ||
            strstr(script[i], "password manager") != NULL ||strstr(script[i], "crypto key") != NULL ||strstr(script[i], "set system") != NULL){
            EnsureConfigMode(enablePassword);
        }
        EnvoiLigne(script[i]);
        Sleep(300);
        ActualiserPrompt();
    }
    Colorier(COLOR_OK);
    printf("Script SSH envoye avec succes.\n");
    Colorier(COLOR_DEFAULT);
}
static void VisualiserScriptSSH(char script[][BUF_SMALL], int count)
{
    int i;
    Cadre("Apercu du script SSH genere");
    Colorier(COLOR_INFO);
    for (i = 0; i < count; i++){printf("  %d) %s\n", i + 1, script[i]);}
    Colorier(COLOR_DEFAULT);
}
static int SauvergarderScriptSSH(const char* filename, char script[][BUF_SMALL], int count)
{
    FILE* f = fopen(filename, "w");
    int i;
    if (!f)
    {
        Colorier(COLOR_ERROR);
        printf("Erreur : impossible d'ouvrir %s pour ecriture.\n", filename);
        Colorier(COLOR_DEFAULT);
        return 0;
    }
    fprintf(f, "# Script SSH genere automatiquement\n");
    fprintf(f, "# Vendor : %s\n\n", gVendor);
    for (i = 0; i < count; i++) fprintf(f, "%s\n", script[i]);
    fclose(f);
    Colorier(COLOR_OK);
    printf("Script exporte dans : %s\n", filename);
    Colorier(COLOR_DEFAULT);
    return 1;
}
static void ConsoleInteractive()
{
    char line[BUF_SMALL];
    Cadre("Mode console interactif (tapez 'exit-console' pour quitter)");
    fgets(line, BUF_SMALL, stdin);
    while (1)
    {
        Colorier(COLOR_WARN);
        printf("SW# ");
        Colorier(COLOR_DEFAULT);
        if (!fgets(line, BUF_SMALL, stdin))break;
        line[strcspn(line, "\r\n")] = 0;
        if (strcmp(line, "exit-console") == 0)break;
        EnvoiLigne(line);
    }
    Cadre("Fin du mode console interactif");
}
static void AssistantSauvegardeScript(char script[][BUF_SMALL], int count,const char* user)
{
    char filename[BUF_SMALL];
    sprintf(filename, "ssh_%s.txt", user);
    if (ConfirmerON("Voulez-vous exporter le script SSH dans un fichier .txt ?"))
    {
        SauvergarderScriptSSH(filename, script, count);
    }
    else
    {
        Colorier(COLOR_WARN);
        printf("Export ignore.\n");
        Colorier(COLOR_DEFAULT);
    }
}
static void AssistantEnvoiScript(char script[][BUF_SMALL], int count,
    const char* enablePassword)
{
    if (ConfirmerON("Voulez-vous envoyer le script SSH au commutateur ?"))
    {
        EnvoiScriptSSH(script, count, enablePassword);
    }
    else
    {
        Colorier(COLOR_WARN);
        printf("Envoi du script ignore.\n");
        Colorier(COLOR_DEFAULT);
    }
}
static void AssistantConsoleInteractive()
{
    if (ConfirmerON("Voulez-vous entrer en mode console interactif ?"))
    {
        ConsoleInteractive();
    }
    else
    {
        Colorier(COLOR_WARN);
        printf("Mode console ignore.\n");
        Colorier(COLOR_DEFAULT);
    }
}
static void FermerPortCOM()
{
    if (hSerial != INVALID_HANDLE_VALUE){CloseHandle(hSerial);hSerial = INVALID_HANDLE_VALUE;}
}
static void AttenteTouche()
{
    char tmp[BUF_SMALL];
    Colorier(COLOR_WARN);
    printf("Appuyez sur ENTREE pour continuer...");
    Colorier(COLOR_DEFAULT);
    fgets(tmp, BUF_SMALL, stdin);
}
static void Banniere()
{
    Colorier(COLOR_INFO);
    printf("\n");
    printf("=============================================================\n");
    printf("   Provision SSH Console — Win64   \n");
    printf("=============================================================\n");
    printf("\n");
    Colorier(COLOR_DEFAULT);
}
static void AfficherInformationSession(const char* port, DWORD baud)
{
    char msg[BUF_SMALL];
    sprintf(msg, "Port ouvert : %s", port);    Cadre(msg);
    sprintf(msg, "Debit detecte : %lu", baud);    Cadre(msg);
    sprintf(msg, "Vendeur detecte : %s", gVendor);    Cadre(msg);
    AfficherTypePrompt();
}
static void DemanderePasswordPrivilegie(char* out)
{
    char buf[BUF_SMALL];
    memset(out, 0, BUF_SMALL);
    if (ConfirmerON("Le mode privilegie necessite-t-il un mot de passe ?"))
    {
        Cadre("Entrez le mot de passe privilegie");
        fgets(buf, BUF_SMALL, stdin);
        buf[strcspn(buf, "\r\n")] = 0;
        strcpy(out, buf);
    }
    else{strcpy(out, "");}
}
static void GenereUtilisateurSSH(char* user, char* pass)
{
    char buf[BUF_SMALL];
    Cadre("Nom de l'utilisateur SSH a creer");
    fgets(buf, BUF_SMALL, stdin);
    buf[strcspn(buf, "\r\n")] = 0;
    strcpy(user, buf);
    Cadre("Mot de passe SSH");
    fgets(buf, BUF_SMALL, stdin);
    buf[strcspn(buf, "\r\n")] = 0;
    strcpy(pass, buf);
}
static void PrepareScriptSSH(char script[][BUF_SMALL], int* count,
    const char* user, const char* pass)
{
    Cadre("Generation du script SSH");
    GenererScriptSSH(script, count, user, pass);
    Colorier(COLOR_OK);
    printf("Script genere (%d lignes).\n", *count);
    Colorier(COLOR_DEFAULT);
    VisualiserScriptSSH(script, *count);
}
static void ExecuterScript(const char* enablePassword,char script[][BUF_SMALL], int count)
{
    ActiverModePrivilegie(enablePassword);
    EnsureConfigMode(enablePassword);
    AssistantEnvoiScript(script, count, enablePassword);
    SortieModeConfig();
}
int main()
{
	SetConsoleTitle(L"Assistant configuration SSH Console - RS232");
    Cadre("Assistant configuration SSH Console - RS232   v:1.00   Patrice Waechter-Ebling");
    char port[BUF_SMALL];
    char enablePassword[BUF_SMALL];
    char user[BUF_SMALL];
    char pass[BUF_SMALL];
    char script[100][BUF_SMALL];
    int scriptCount = 0;
    DWORD baudDetected = 0;
    Banniere();
    Cadre("Entrez le port COM (ex : COM3)");
    fgets(port, BUF_SMALL, stdin);
    port[strcspn(port, "\r\n")] = 0;
    char fullPort[BUF_SMALL];
    sprintf(fullPort, "\\\\.\\%s", port);
    strcpy(port, fullPort);
    if (!OuvrirPortCOM(port))
    {
        Colorier(COLOR_ERROR);
        printf("Erreur : impossible d'ouvrir le port %s\n", port);
        Colorier(COLOR_DEFAULT);
        AttenteTouche();
        return 1;
    }
    Cadre("Port ouvert avec succes");
    Cadre("Debit automatique en cours...");
    if (!DebitAutomatique(&baudDetected))
    {
        Colorier(COLOR_ERROR);
        printf("Echec de l'debit automatique.\n");
        Colorier(COLOR_DEFAULT);
        FermerPortCOM();
        AttenteTouche();
        return 1;
    }
    char msg[BUF_SMALL];
    sprintf(msg, "Baud detecte : %lu", baudDetected);
    Cadre(msg);
    HANDLE hThread = CreateThread(NULL, 0, LectureRX, NULL, 0, NULL);
    if (!hThread)
    {
        Colorier(COLOR_ERROR);
        printf("Erreur : impossible de lancer le thread RX.\n");
        Colorier(COLOR_DEFAULT);
        FermerPortCOM();
        AttenteTouche();
        return 1;
    }
    Sleep(800);
    ActualiserPrompt();
    AfficherTypePrompt();
    DetectVendor();
    DemanderePasswordPrivilegie(enablePassword);
    GenereUtilisateurSSH(user, pass);
    PrepareScriptSSH(script, &scriptCount, user, pass);
    AssistantSauvegardeScript(script, scriptCount, user);
    ExecuterScript(enablePassword, script, scriptCount);
    AssistantConsoleInteractive();
    gRunRX = 0;
    Sleep(200);
    FermerPortCOM();
    Cadre("Fin du programme");
    AttenteTouche();
    return 0;
}

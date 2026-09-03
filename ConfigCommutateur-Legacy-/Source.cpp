// ©2026 Patrice Waechter-Ebling, All rights reserved.
// Construction Legacy 90's style
// sans namespace
// sans auto
// sans atomic
// sans mutex
// sans thread C++
// sans initialisation moderne
// sans range‑for
// sans to_string
// sans commentaires
// utilise CreateThread + CRITICAL_SECTION
// utilise sprintf pour conversions
// utilise char buffers
// utilise boucles classiques
//  *  NOMETAFILE        - typedef METAFILEPICT
//  *  NOMINMAX          - Macros min(a,b) and max(a,b)
//  *  NOOPENFILE        - OpenFile(), OemToAnsi, AnsiToOem, and OF_*

#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <fstream>
#define POOL_SIZE 200000

#pragma warning(disable:4996) // for sprintf
char g_pool[POOL_SIZE];
int g_pool_pos = 0;
void* pool_alloc(int sz) {
    if (g_pool_pos + sz >= POOL_SIZE) return NULL;
    void* p = g_pool + g_pool_pos;
    g_pool_pos += sz;
    return p;
}
struct Vlan {
    int id;
    char name[64];
    Vlan* next;
};
struct Ports {
    char iface[64];
    int vlanId;
    char description[128];
    int portSecurity;
    Ports* next;
};
struct LigneACL {
    char line[256];
    LigneACL* next;
};
struct ConfigSNMP {
    int enabled;
    char ro[64];
    char rw[64];
    char contact[128];
    char location[128];
};
volatile BOOL g_running = TRUE;
CRITICAL_SECTION g_cs;
HANDLE g_thread;
HANDLE g_rs232;
int g_capture = 0;
std::ofstream g_log;
enum Fabricant {
    VENDOR_CISCO,
    VENDOR_HP,
    VENDOR_ARUBA,
    VENDOR_JUNIPER
};
void Colorisation(WORD c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int ChoixValeur(const char* s) {
    for (;;) {
        std::cout << s;
        std::string x;
        std::getline(std::cin, x);
        std::stringstream ss(x);
        int v;
        if (ss >> v) return v;
    }
}
int ValiderON(const char* s) {
    for (;;) {
        std::cout << s << " (o/n) : ";
        std::string x;
        std::getline(std::cin, x);
        if (x == "o" || x == "O" || x == "y" || x == "Y") return 1;
        if (x == "n" || x == "N") return 0;
    }
}
const char* NomFabricants(Fabricant v) {
    if (v == VENDOR_CISCO) return "Cisco";
    if (v == VENDOR_HP) return "HP";
    if (v == VENDOR_ARUBA) return "Aruba";
    return "Juniper";
}
HANDLE OuvrirPortSerie(const char* port, int baud) {
    char full[64];
    sprintf(full, "\\\\.\\%s", port);
    HANDLE h = CreateFileA(full, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (h == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE;
    DCB dcb;
    ZeroMemory(&dcb, sizeof(dcb));
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(h, &dcb)) { CloseHandle(h); return INVALID_HANDLE_VALUE; }
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    if (!SetCommState(h, &dcb)) { CloseHandle(h); return INVALID_HANDLE_VALUE; }
    COMMTIMEOUTS t;
    ZeroMemory(&t, sizeof(t));
    t.ReadIntervalTimeout = 50;
    t.ReadTotalTimeoutConstant = 50;
    t.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(h, &t);
    return h;
}
int ConfigurationPortSerie(HANDLE h, int baud) {
    DCB dcb;
    ZeroMemory(&dcb, sizeof(dcb));
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(h, &dcb)) return 0;
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    if (!SetCommState(h, &dcb)) return 0;
    return 1;
}
void EnvoiSerieDonneeBrute(HANDLE h, const char* data) {
    DWORD w = 0;
    WriteFile(h, data, (DWORD)strlen(data), &w, NULL);
}
void EnvoiLigneSerie(HANDLE h, const char* line) {
    char buf[512];
    sprintf(buf, "%s\r\n", line);
    EnvoiSerieDonneeBrute(h, buf);
}
int LireDonneesSerie(HANDLE h, char* out, int max) {
    DWORD r = 0;
    if (!ReadFile(h, out, max - 1, &r, NULL)) return 0;
    if (r == 0) { out[0] = 0; return 0; }
    out[r] = 0;
    return r;
}
Fabricant DetectionVendeur(const char* txt) {
    char buf[2048];
    int i;
    for (i = 0; i < (int)strlen(txt); i++) {
        char c = txt[i];
        if (c >= 'A' && c <= 'Z') buf[i] = c + 32;
        else buf[i] = c;
    }
    buf[i] = 0;
    if (strstr(buf, "cisco")) return VENDOR_CISCO;
    if (strstr(buf, "hp ") || strstr(buf, "procurve")) return VENDOR_HP;
    if (strstr(buf, "aruba")) return VENDOR_ARUBA;
    if (strstr(buf, "juniper") || strstr(buf, "junos")) return VENDOR_JUNIPER;
    if (strstr(buf, "login:") || strstr(buf, "username:")) return VENDOR_JUNIPER;
    return VENDOR_CISCO;
}
int DetectionDebit(HANDLE h, int* bauds, int count) {
    const char* patterns[9] = { "#", " >", "username:", "password:", "login:","press any key", "invalid", "help", "?" };
    int best = 0;
    int bestScore = -1;
    int i;
    for (i = 0; i < count; i++) {
        int b = bauds[i];
        if (!ConfigurationPortSerie(h, b)) continue;
        PurgeComm(h, PURGE_RXCLEAR | PURGE_TXCLEAR);
        EnvoiSerieDonneeBrute(h, "\r\n?\r\n");
        Sleep(500);
        char r[2048];
        int n = LireDonneesSerie(h, r, sizeof(r));
        if (n <= 0) continue;
        int s = 0;
        int k;
        for (k = 0; k < 9; k++) {
            if (strstr(r, patterns[k])) s++;
        }
        if (s > bestScore) {
            bestScore = s;
            best = b;
        }
    }
    return best;
}
void DetectionTypeCable(HANDLE h) {
    EnvoiLigneSerie(h, "show controllers");
    Sleep(800);
    char r[2048];
    LireDonneesSerie(h, r, sizeof(r));
    if (strstr(r, "DCE")) std::cout << "DCE\n";
    else if (strstr(r, "DTE")) std::cout << "DTE\n";
    else std::cout << "Inconnu\n";
}
DWORD WINAPI LectureFlux(LPVOID lp) {
    HANDLE h = (HANDLE)lp;
    char buf[2048];
    while (g_running) {
        int n = LireDonneesSerie(h, buf, sizeof(buf));
        if (n > 0) {
            EnterCriticalSection(&g_cs);
            int err = 0;
            int pr = 0;
            if (strstr(buf, "Invalid") || strstr(buf, "Error") || strstr(buf, "Unknown")) err = 1;
            if (strstr(buf, ">") || strstr(buf, "#")) pr = 1;
            if (err) Colorisation(FOREGROUND_RED | FOREGROUND_INTENSITY);
            else if (pr) Colorisation(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else Colorisation(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << buf;
            std::cout.flush();
            if (g_capture && g_log.is_open()) {
                g_log << buf;
                g_log.flush();
            }
            Colorisation(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            LeaveCriticalSection(&g_cs);
        }
        Sleep(20);
    }
    return 0;
}
struct Historique {
    char line[256];
    Historique* next;
};
void AjoutHistorique(Historique*& head, const char* s) {
    Historique* n = (Historique*)pool_alloc(sizeof(Historique));
    if (!n) return;
    strcpy(n->line, s);
    n->next = NULL;
    if (!head) { head = n; return; }
    Historique* p = head;
    while (p->next) p = p->next;
    p->next = n;
}
int CompteHistorique(Historique* head) {
    int c = 0;
    while (head) { c++; head = head->next; }
    return c;
}
const char* LireHistorique(Historique* head, int index) {
    int i = 0;
    while (head) {
        if (i == index) return head->line;
        head = head->next;
        i++;
    }
    return "";
}
void ConsoleInteractive(HANDLE h) {
    std::cout << "\n=== MODE CONSOLE MANUELLE ===\n";
    std::cout << "CTRL+X pour quitter\n\n";
    Historique* hist = NULL;
    int histIndex = -1;
    char line[256];
    int len = 0;
    line[0] = 0;
    for (;;) {
        if (GetAsyncKeyState(0x18) & 0x8000) return;
        if (_kbhit()) {
            int c = _getch();
            if (c == 13) {
                std::cout << "\n";
                if (len > 0) {
                    line[len] = 0;
                    AjoutHistorique(hist, line);
                    histIndex = CompteHistorique(hist);
                    EnvoiLigneSerie(h, line);
                    len = 0;
                    line[0] = 0;
                }
                else {
                    EnvoiSerieDonneeBrute(h, "\r\n");
                }
            }
            else if (c == 8) {
                if (len > 0) {
                    len--;
                    line[len] = 0;
                    std::cout << "\b \b";
                }
            }
            else if (c == 0 || c == 224) {
                int c2 = _getch();
                if (c2 == 72) {
                    int count = CompteHistorique(hist);
                    if (count > 0 && histIndex > 0) {
                        histIndex--;
                        const char* s = LireHistorique(hist, histIndex);
                        while (len > 0) { std::cout << "\b \b"; len--; }
                        strcpy(line, s);
                        len = (int)strlen(line);
                        std::cout << line;
                    }
                }
                else if (c2 == 80) {
                    int count = CompteHistorique(hist);
                    if (count > 0 && histIndex < count - 1) {
                        histIndex++;
                        const char* s = LireHistorique(hist, histIndex);
                        while (len > 0) { std::cout << "\b \b"; len--; }
                        strcpy(line, s);
                        len = (int)strlen(line);
                        std::cout << line;
                    }
                    else if (histIndex == count - 1) {
                        histIndex++;
                        while (len > 0) { std::cout << "\b \b"; len--; }
                        line[0] = 0;
                    }
                }
            }
            else {
                if (len < 255) {
                    line[len++] = (char)c;
                    line[len] = 0;
                    std::cout << (char)c;
                }
            }
        }
        Sleep(5);
    }
}
void AppliquerPersonalisation(Fabricant v, Vlan*& vlHead, ConfigSNMP* sn, LigneACL*& aclHead) {
    vlHead = NULL;
    aclHead = NULL;
    if (sn) {
        sn->enabled = 0;
        sn->ro[0] = 0;
        sn->rw[0] = 0;
        sn->contact[0] = 0;
        sn->location[0] = 0;
    }
    if (v == VENDOR_CISCO) {
        Vlan* a = (Vlan*)pool_alloc(sizeof(Vlan));
        if (a) { a->id = 10; strcpy(a->name, "USERS"); a->next = NULL; vlHead = a; }
        Vlan* b = (Vlan*)pool_alloc(sizeof(Vlan));
        if (b) { b->id = 20; strcpy(b->name, "SERVERS"); b->next = NULL; if (vlHead) vlHead->next = b; else vlHead = b; }
        Vlan* c = (Vlan*)pool_alloc(sizeof(Vlan));
        if (c) { c->id = 30; strcpy(c->name, "VOICE"); c->next = NULL; if (b) b->next = c; else if (vlHead) vlHead->next = c; else vlHead = c; }
        if (sn) {
            sn->enabled = 1;
            strcpy(sn->ro, "public");
            sn->contact[0] = 0;
        }
    }
    else if (v == VENDOR_HP) {
        Vlan* a = (Vlan*)pool_alloc(sizeof(Vlan));
        if (a) { a->id = 1; strcpy(a->name, "DEFAULT_VLAN"); a->next = NULL; vlHead = a; }
        Vlan* b = (Vlan*)pool_alloc(sizeof(Vlan));
        if (b) { b->id = 100; strcpy(b->name, "MGMT"); b->next = NULL; if (vlHead) vlHead->next = b; else vlHead = b; }
        if (sn) {
            sn->enabled = 1;
            strcpy(sn->ro, "manager");
        }
    }
    else if (v == VENDOR_ARUBA) {
        Vlan* a = (Vlan*)pool_alloc(sizeof(Vlan));
        if (a) { a->id = 100; strcpy(a->name, "CORP"); a->next = NULL; vlHead = a; }
        Vlan* b = (Vlan*)pool_alloc(sizeof(Vlan));
        if (b) { b->id = 200; strcpy(b->name, "GUEST"); b->next = NULL; if (vlHead) vlHead->next = b; else vlHead = b; }
        if (sn) {
            sn->enabled = 1;
            strcpy(sn->ro, "aruba");
        }
    }
    else if (v == VENDOR_JUNIPER) {
        Vlan* a = (Vlan*)pool_alloc(sizeof(Vlan));
        if (a) { a->id = 10; strcpy(a->name, "CORP"); a->next = NULL; vlHead = a; }
        Vlan* b = (Vlan*)pool_alloc(sizeof(Vlan));
        if (b) { b->id = 20; strcpy(b->name, "SERVERS"); b->next = NULL; if (vlHead) vlHead->next = b; else vlHead = b; }
        LigneACL* l1 = (LigneACL*)pool_alloc(sizeof(LigneACL));
        if (l1) {
            strcpy(l1->line, "set firewall family inet filter BLOCK term 1 from source-address 10.0.0.0/8");
            l1->next = NULL;
            aclHead = l1;
        }
        LigneACL* l2 = (LigneACL*)pool_alloc(sizeof(LigneACL));
        if (l2) {
            strcpy(l2->line, "set firewall family inet filter BLOCK term 1 then discard");
            l2->next = NULL;
            if (aclHead) aclHead->next = l2; else aclHead = l2;
        }
        if (sn) {
            sn->enabled = 1;
            strcpy(sn->ro, "juniper");
        }
    }
}
void AjoutVLAN(Vlan*& head, int id, const char* name) {
    Vlan* v = (Vlan*)pool_alloc(sizeof(Vlan));
    if (!v) return;
    v->id = id;
    strcpy(v->name, name);
    v->next = NULL;
    if (!head) { head = v; return; }
    Vlan* p = head;
    while (p->next) p = p->next;
    p->next = v;
}
void AjouterPort(Ports*& head, const char* iface, int vlanId, const char* desc, int ps) {
    Ports* p = (Ports*)pool_alloc(sizeof(Ports));
    if (!p) return;
    strcpy(p->iface, iface);
    p->vlanId = vlanId;
    strcpy(p->description, desc);
    p->portSecurity = ps;
    p->next = NULL;
    if (!head) { head = p; return; }
    Ports* q = head;
    while (q->next) q = q->next;
    q->next = p;
}
void AjouterACL(LigneACL*& head, const char* line) {
    LigneACL* a = (LigneACL*)pool_alloc(sizeof(LigneACL));
    if (!a) return;
    strcpy(a->line, line);
    a->next = NULL;
    if (!head) { head = a; return; }
    LigneACL* p = head;
    while (p->next) p = p->next;
    p->next = a;
}
std::string GenererConfiguration(Fabricant v,
    const char* hostname,
    const char* activerSecret,
    int mg,
    const char* mgName,
    const char* ip,
    const char* mask,
    const char* gw,
    const char* upl,
    Vlan* vlHead,
    Ports* ptHead,
    LigneACL* aclHead,
    ConfigSNMP* sn,
    const char* ban) {
    std::ostringstream o;
    if (v == VENDOR_CISCO || v == VENDOR_HP || v == VENDOR_ARUBA) {
        o << "hostname " << hostname << "\n";
        if (activerSecret && activerSecret[0]) o << "enable secret " << activerSecret << "\n";
        if (ban && ban[0]) o << "banner motd #" << ban << "#\n";
        o << "vlan " << mg << "\n name " << mgName << "\n";
        Vlan* vcur = vlHead;
        while (vcur) {
            if (vcur->id != mg) {
                o << "vlan " << vcur->id << "\n name " << vcur->name << "\n";
            }
            vcur = vcur->next;
        }
        o << "interface vlan " << mg << "\n ip address " << ip << " " << mask << "\n no shutdown\n";
        o << "ip default-gateway " << gw << "\n";
        Ports* p = ptHead;
        while (p) {
            o << "interface " << p->iface << "\n description " << p->description << "\n switchport mode access\n switchport access vlan " << p->vlanId << "\n";
            if (p->portSecurity) {
                o << " switchport port-security\n switchport port-security maximum 2\n switchport port-security violation restrict\n";
            }
            o << " spanning-tree portfast\n no shutdown\n";
            p = p->next;
        }
        o << "interface " << upl << "\n switchport mode trunk\n no shutdown\n";
        LigneACL* a = aclHead;
        while (a) {
            o << a->line << "\n";
            a = a->next;
        }
        if (sn && sn->enabled) {
            if (sn->ro[0]) o << "snmp-server community " << sn->ro << " RO\n";
            if (sn->rw[0]) o << "snmp-server community " << sn->rw << " RW\n";
            if (sn->contact[0]) o << "snmp-server contact " << sn->contact << "\n";
            if (sn->location[0]) o << "snmp-server location " << sn->location << "\n";
        }
        o << "end\nwrite memory\n";
    }
    else {
        o << "set system host-name " << hostname << "\n";
        if (ban && ban[0]) o << "set system login message \"" << ban << "\"\n";
        o << "set interfaces vlan unit 0 family inet address " << ip << "/24\n";
        Vlan* vcur2 = vlHead;
        while (vcur2) {
            o << "set vlans VLAN-" << vcur2->id << " vlan-id " << vcur2->id << "\n";
            vcur2 = vcur2->next;
        }
        LigneACL* a2 = aclHead;
        while (a2) {
            o << a2->line << "\n";
            a2 = a2->next;
        }
        if (sn && sn->enabled) {
            if (sn->ro[0]) o << "set snmp community " << sn->ro << " authorization read-only\n";
            if (sn->contact[0]) o << "set snmp contact \"" << sn->contact << "\"\n";
            if (sn->location[0]) o << "set snmp location \"" << sn->location << "\"\n";
        }
        o << "commit\n";
    }
    return o.str();
}
int main() {
    InitializeCriticalSection(&g_cs);
    g_rs232 = INVALID_HANDLE_VALUE;
    std::cout << "=== Configuration Commutateur Legacy 90's ===\n\n";
    char ports[64][16];
    int portCount = 0;
    int i;
    for (i = 1; i <= 256; i++) {
        char p[16];
        sprintf(p, "COM%d", i);
        char full[64];
        sprintf(full, "\\\\.\\%s", p);
        HANDLE h = CreateFileA(full, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (h != INVALID_HANDLE_VALUE) {
            if (portCount < 64) {
                strcpy(ports[portCount], p);
                portCount++;
            }
            CloseHandle(h);
        }
    }
    if (portCount == 0) {
        std::cout << "Aucun port COM\n";
        DeleteCriticalSection(&g_cs);
        return 0;
    }
    for (i = 0; i < portCount; i++) {
        std::cout << i + 1 << ". " << ports[i] << "\n";
    }
    int c = ChoixValeur("Choisir port : ");
    if (c < 1 || c > portCount) {
        DeleteCriticalSection(&g_cs);
        return 0;
    }
    char port[16];
    strcpy(port, ports[c - 1]);
    g_rs232 = OuvrirPortSerie(port, 9600);
    if (g_rs232 == INVALID_HANDLE_VALUE) {
        std::cout << "Erreur port\n";
        DeleteCriticalSection(&g_cs);
        return 0;
    }
    int bauds[5] = { 9600,19200,38400,57600,115200 };
    int b = DetectionDebit(g_rs232, bauds, 5);
    if (b == 0) b = 9600;
    ConfigurationPortSerie(g_rs232, b);
    g_running = TRUE;
    g_thread = CreateThread(NULL, 0, LectureFlux, g_rs232, 0, NULL);
    EnvoiSerieDonneeBrute(g_rs232, "\r\n");
    Sleep(800);
    char first[2048];
    LireDonneesSerie(g_rs232, first, sizeof(first));
    Fabricant Vendeur = DetectionVendeur(first);
    std::cout << "Constructeur detecte : " << NomFabricants(Vendeur) << "\n";
    std::string utilisateur, motPasse;
    if (ValiderON("Auto-login ?")) {
        std::cout << "Username : ";
        std::getline(std::cin, utilisateur);
        std::cout << "Password : ";
        std::getline(std::cin, motPasse);
        EnvoiSerieDonneeBrute(g_rs232, "\r\n");
        Sleep(500);
        char r[2048];
        LireDonneesSerie(g_rs232, r, sizeof(r));
        if (strstr(r, "Username:") || strstr(r, "login:")) {
            EnvoiLigneSerie(g_rs232, utilisateur.c_str());
            Sleep(500);
            EnvoiLigneSerie(g_rs232, motPasse.c_str());
        }
        else if (strstr(r, "Password:")) {
            EnvoiLigneSerie(g_rs232, motPasse.c_str());
        }
    }
    std::string hote, secretActif, mgNom, ip, mask, gw, upl, ban;
    int mg;
    std::cout << "Hostname : ";
    std::getline(std::cin, hote);
    std::cout << "Enable secret : ";
    std::getline(std::cin, secretActif);
    mg = ChoixValeur("VLAN mgmt : ");
    std::cout << "Nom VLAN mgmt : ";
    std::getline(std::cin, mgNom);
    std::cout << "IP mgmt : ";
    std::getline(std::cin, ip);
    std::cout << "Masque : ";
    std::getline(std::cin, mask);
    std::cout << "Gateway : ";
    std::getline(std::cin, gw);
    std::cout << "Uplink : ";
    std::getline(std::cin, upl);
    std::cout << "Banniere : ";
    std::getline(std::cin, ban);
    Vlan* vlHead = NULL;
    Ports* ptHead = NULL;
    LigneACL* enteteACL = NULL;
    ConfigSNMP sn;
    sn.enabled = 0;
    sn.ro[0] = 0;
    sn.rw[0] = 0;
    sn.contact[0] = 0;
    sn.location[0] = 0;
    for (;;) {
		system("cls");
        std::cout << "\n1.Ajout VLAN\n2.Liste VLAN\n3.Ajout port access\n4.Liste ports\n5.Ajout ACL\n6.SNMP\n7.Gen script\n8.Save script\n9.Send script\n10.Console\n11.Capture\n12.Cable\n13.Profil\n0.Quit\n";
        int x = ChoixValeur("Choix : ");
        if (x == 0) break;
        if (x == 1) {
            int id = ChoixValeur("ID : ");
            std::string name;
            std::cout << "Nom : ";
            std::getline(std::cin, name);
            AjoutVLAN(vlHead, id, name.c_str());
        }
        else if (x == 2) {
            std::cout << mg << " : " << mgNom << " (mgmt)\n";
            Vlan* vcur = vlHead;
            while (vcur) {
                std::cout << vcur->id << " : " << vcur->name << "\n";
                vcur = vcur->next;
            }
        }
        else if (x == 3) {
            std::string iface, desc;
            int vid;
            int ps;
            std::cout << "Iface : ";
            std::getline(std::cin, iface);
            vid = ChoixValeur("VLAN : ");
            std::cout << "Desc : ";
            std::getline(std::cin, desc);
            ps = ValiderON("Port-security ?");
            AjouterPort(ptHead, iface.c_str(), vid, desc.c_str(), ps);
        }
        else if (x == 4) {
            Ports* p = ptHead;
            while (p) {
                std::cout << p->iface << " -> " << p->vlanId << " " << p->description << " PS=" << (p->portSecurity ? "ON" : "OFF") << "\n";
                p = p->next;
            }
        }
        else if (x == 5) {
            std::string line;
            std::cout << "ACL : ";
            std::getline(std::cin, line);
            if (!line.empty()) AjouterACL(enteteACL, line.c_str());
        }
        else if (x == 6) {
            sn.enabled = ValiderON("Activer SNMP ?");
            if (sn.enabled) {
                std::cout << "RO : ";
                std::getline(std::cin, (std::string&)utilisateur);
                strncpy(sn.ro, utilisateur.c_str(), sizeof(sn.ro) - 1);
                sn.ro[sizeof(sn.ro) - 1] = 0;
                std::cout << "RW : ";
                std::getline(std::cin, (std::string&)motPasse);
                strncpy(sn.rw, motPasse.c_str(), sizeof(sn.rw) - 1);
                sn.rw[sizeof(sn.rw) - 1] = 0;
                std::cout << "Contact : ";
                std::getline(std::cin, (std::string&)hote);
                strncpy(sn.contact, hote.c_str(), sizeof(sn.contact) - 1);
                sn.contact[sizeof(sn.contact) - 1] = 0;
                std::cout << "Location : ";
                std::getline(std::cin, (std::string&)mgNom);
                strncpy(sn.location, mgNom.c_str(), sizeof(sn.location) - 1);
                sn.location[sizeof(sn.location) - 1] = 0;
            }
        }
        else if (x == 7 || x == 8 || x == 9) {
            std::string cfg = GenererConfiguration(Vendeur, hote.c_str(), secretActif.c_str(), mg, mgNom.c_str(), ip.c_str(), mask.c_str(), gw.c_str(), upl.c_str(), vlHead, ptHead, enteteACL, &sn, ban.c_str());
            if (x == 7) {
                std::cout << cfg << "\n";
            }
            else if (x == 8) {
                std::string fn = hote + ".cfg";
                std::ofstream f(fn.c_str());
                f << cfg;
                f.close();
            }
            else if (x == 9) {
                std::istringstream ss(cfg);
                std::string l;
                while (std::getline(ss, l)) {
                    if (!l.empty()) EnvoiLigneSerie(g_rs232, l.c_str());
                    Sleep(150);
                }
            }
        }
        else if (x == 10) {
            ConsoleInteractive(g_rs232);
        }
        else if (x == 11) {
            if (!g_capture) {
                g_log.open("session_log.txt", std::ios::app);
                g_capture = 1;
            }
            else {
                g_capture = 0;
                if (g_log.is_open()) g_log.close();
            }
        }
        else if (x == 12) {
            DetectionTypeCable(g_rs232);
        }
        else if (x == 13) {
            AppliquerPersonalisation(Vendeur, vlHead, &sn, enteteACL);
        }
    }
    g_running = FALSE;
    WaitForSingleObject(g_thread, INFINITE);
    CloseHandle(g_thread);
    if (g_rs232 != INVALID_HANDLE_VALUE) CloseHandle(g_rs232);
    if (g_log.is_open()) g_log.close();
    DeleteCriticalSection(&g_cs);
    return 0;
}

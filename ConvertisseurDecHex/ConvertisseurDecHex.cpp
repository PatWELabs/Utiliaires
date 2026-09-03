// ConvertisseurDecHex.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>

std::string dec2bin(int n) {
    if (n == 0) return "0";
    std::string result;
    while (n > 0) {result += (n % 2) ? '1' : '0';n /= 2; }
    std::reverse(result.begin(), result.end());
    return result;
}
std::string dec2hex(int n) {
    if (n == 0) return "0";
    const char* hexDigits = "0123456789ABCDEF";
    std::string result;
    while (n > 0) {result += hexDigits[n % 16];n /= 16; }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    int n;
	SetConsoleTitle(L"Convertisseur Decimal vers Binaire et Hexadecimal");
    std::cout << "Utilitaire de conversion de nombres decimaux en binaire et hexadecimal\nEntrez un nombre decimal : ";
    std::cin >> n;
    std::cout << "Binaire     : " << dec2bin(n) << std::endl;
    std::cout << "Hexadecimal : " << dec2hex(n) << std::endl;
    return 0;
}

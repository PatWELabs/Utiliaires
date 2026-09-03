<<<<<<< HEAD
#include "StdAfx.h"
#include "ASCII_4_Windows.h"
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

int bin32[32];
UINT valeur=0;
float t=0x02;
int LectureBin[32] = { 0 };
char binaire[32] = { 0 };

TBinaire::TBinaire(void)
{
	InitTableauBinaire();
}

TBinaire::~TBinaire(void)
{
	MessageBoxA(0,"Ce module a été codé par Patrice Waechter-Ebling","Binaire",0);
}

int TBinaire::GetValeur(void)
{
	return 0;
}

void TBinaire::SetValeur(int Valeur)
{
	valeur=abs(Valeur); // bin theorique uniquement >=0
}

char* TBinaire::GetResultatBinaire(void)
{
	for(int a=31; a>=0;a--){
		binaire[a]=(char)(bin32[a]+0x30);
	}
	return binaire;
}
/*
    */
void TBinaire::InitTableauBinaire(void)
{
    for (int a = 31; a >= 0; a--)
    {
        bin32[a] = pow(t, a);
    }
}

int TBinaire::GetMaxExposant(float  Valeur)
{
	return (int)floor((log(Valeur)/log10(t)));
}

float TBinaire::GetMaxPowerValue(void)
{
	Exposants=GetMaxExposant(valeur);
	return 0;
}

float TBinaire::GetMaxPowerValue(float Valeur)
{
	Exposants=GetMaxExposant((int) Valeur);
	return 	Exposants;
}

int TBinaire::RechercherLaPlusHautePuissance(int Valeur, int reste)
{
	int a;
    for (a = 0; a < 32; a++)
        if (pow(t, a) > Valeur)
        {
            printf("\n%d :: %5.0lf :: reste %d", a, Valeur - (pow(t, a)),reste);
			reste=Valeur-(pow(t,a));
		}
    return a-1;
}
void TBinaire::CreerTableDe2()
{
    for (int a = 0; a <= 32; a++)
    {
        binaire[a] = (char)0x1E;
        bin32[a] = pow(t, a);
    }
}
void TBinaire::AfficheTableDe2()
{
    for (int a = 0; a <= 32; a++)
    {
        printf("\n2^%2d = %5d", a, bin32[a]);
    }
}
int TBinaire::toBase_8(int number) 
{
    int base(8);
    double resTemp = (double)number / base;
    int entier1 = (int)resTemp;
    double decimal = resTemp - entier1;
    double entier2 = decimal * (double)base;
    int res = ((entier1 * 10) + (int)entier2);
    return res;
}
int TBinaire::toBase_2_8bits(float number) {
    if (number > 0 && number <= 255) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void TBinaire::AfficherTable8bits()
{
    for (int a = 7; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, bin32[a], LectureBin[a]);
    }
}
void TBinaire::AfficherBinaire8b()
{
    for (int a = 7; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}
int TBinaire::toBase_2_16bits(float number) {
    if (number > 0 && number <= 0xFFFF) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void TBinaire::AfficherTable16bits()
{
    for (int a = 16; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, bin32[a], LectureBin[a]);
    }
}
void TBinaire::AfficherBinaire16b()
{
    for (int a = 16; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}
void TBinaire::CreerTableDeBaseDesiree(int BaseN)
{
    for (int a = 0; a <= 16; a++)
    {
        binaire[a] = (char)0x1E;
        bin32[a] = pow((float)BaseN, a);
    }
}
int TBinaire::RechercherLaPlusHautePuissance(int valeur)
{
    int reste;
    if (valeur < 2) return 1;
    int a = 0;
    for (a = 16; a >= 0; a--) {
        if (a == 16)
        {
            reste = valeur;
        }
        if (bin32[a] > reste)
        {
            LectureBin[a] = 0;
        }
        else
        {
            LectureBin[a] = 1;
            return a + 1;
        }

    }
}
int TBinaire::ExtractPuissanceLog2(int Valeur)
{
    return  abs((log((float)Valeur)/log10(t)));
}
void TBinaire::GenerationBaseN(int ValeurBase) 
{
}
/*
//8 bits
//16bits

=======
#include "StdAfx.h"
#include "ASCII_4_Windows.h"
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

int bin32[32];
UINT valeur=0;
float t=0x02;
int LectureBin[32] = { 0 };
char binaire[32] = { 0 };

TBinaire::TBinaire(void)
{
	InitTableauBinaire();
}

TBinaire::~TBinaire(void)
{
	MessageBoxA(0,"Ce module a été codé par Patrice Waechter-Ebling","Binaire",0);
}

int TBinaire::GetValeur(void)
{
	return 0;
}

void TBinaire::SetValeur(int Valeur)
{
	valeur=abs(Valeur); // bin theorique uniquement >=0
}

char* TBinaire::GetResultatBinaire(void)
{
	for(int a=31; a>=0;a--){
		binaire[a]=(char)(bin32[a]+0x30);
	}
	return binaire;
}
/*
    */
void TBinaire::InitTableauBinaire(void)
{
    for (int a = 31; a >= 0; a--)
    {
        bin32[a] = pow(t, a);
    }
}

int TBinaire::GetMaxExposant(float  Valeur)
{
	return (int)floor((log(Valeur)/log10(t)));
}

float TBinaire::GetMaxPowerValue(void)
{
	Exposants=GetMaxExposant(valeur);
	return 0;
}

float TBinaire::GetMaxPowerValue(float Valeur)
{
	Exposants=GetMaxExposant((int) Valeur);
	return 	Exposants;
}

int TBinaire::RechercherLaPlusHautePuissance(int Valeur, int reste)
{
	int a;
    for (a = 0; a < 32; a++)
        if (pow(t, a) > Valeur)
        {
            printf("\n%d :: %5.0lf :: reste %d", a, Valeur - (pow(t, a)),reste);
			reste=Valeur-(pow(t,a));
		}
    return a-1;
}
void TBinaire::CreerTableDe2()
{
    for (int a = 0; a <= 32; a++)
    {
        binaire[a] = (char)0x1E;
        bin32[a] = pow(t, a);
    }
}
void TBinaire::AfficheTableDe2()
{
    for (int a = 0; a <= 32; a++)
    {
        printf("\n2^%2d = %5d", a, bin32[a]);
    }
}
int TBinaire::toBase_8(int number) 
{
    int base(8);
    double resTemp = (double)number / base;
    int entier1 = (int)resTemp;
    double decimal = resTemp - entier1;
    double entier2 = decimal * (double)base;
    int res = ((entier1 * 10) + (int)entier2);
    return res;
}
int TBinaire::toBase_2_8bits(float number) {
    if (number > 0 && number <= 255) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void TBinaire::AfficherTable8bits()
{
    for (int a = 7; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, bin32[a], LectureBin[a]);
    }
}
void TBinaire::AfficherBinaire8b()
{
    for (int a = 7; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}
int TBinaire::toBase_2_16bits(float number) {
    if (number > 0 && number <= 0xFFFF) {
        int pos(0);
        int bits = 0;
        while ((int)number != 0 || pos == 7)
        {
            number = number / 2;
            if (number == (int)number) {
                LectureBin[pos] = 0;// si paire 
            }
            else {
                LectureBin[pos] = 1;
                binaire[pos] = (char)0x31;
                if (bits == 0) { bits = pos; }
            }
            number = (int)number;
            pos++;
        }
        return bits;
    }
    else {

        return 0;
    }
}
void TBinaire::AfficherTable16bits()
{
    for (int a = 16; a >= 0; a--)
    {
        printf("\n2^%2d=%5d => b:%d ", a, bin32[a], LectureBin[a]);
    }
}
void TBinaire::AfficherBinaire16b()
{
    for (int a = 16; a >= 0; a--) {
        printf("%d", LectureBin[a]);
    }
}
void TBinaire::CreerTableDeBaseDesiree(int BaseN)
{
    for (int a = 0; a <= 16; a++)
    {
        binaire[a] = (char)0x1E;
        bin32[a] = pow((float)BaseN, a);
    }
}
int TBinaire::RechercherLaPlusHautePuissance(int valeur)
{
    int reste;
    if (valeur < 2) return 1;
    int a = 0;
    for (a = 16; a >= 0; a--) {
        if (a == 16)
        {
            reste = valeur;
        }
        if (bin32[a] > reste)
        {
            LectureBin[a] = 0;
        }
        else
        {
            LectureBin[a] = 1;
            return a + 1;
        }

    }
}
int TBinaire::ExtractPuissanceLog2(int Valeur)
{
    return  abs((log((float)Valeur)/log10(t)));
}
void TBinaire::GenerationBaseN(int ValeurBase) 
{
}
/*
//8 bits
//16bits

>>>>>>> 0e50cecb47656a8e5624f3386586a456f1179eec
*/
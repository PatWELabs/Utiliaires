<<<<<<< HEAD
#pragma once

#include "resource.h"

class TBinaire
{
public:
	TBinaire(void);
	~TBinaire(void);
	int GetValeur(void);
	void SetValeur(int Valeur);
	char* GetResultatBinaire(void);
	float Exposants;
	char tmp[32];
protected:
	static void InitTableauBinaire(void);
	int GetMaxExposant(float  Valeur);
	void CreerTableDe2();
	int toBase_8(int number);
	int toBase_2_8bits(float number);
	int toBase_2_16bits(float number);
	void CreerTableDeBaseDesiree(int BaseN);
	int ExtractPuissanceLog2(int Valeur);
	void GenerationBaseN(int ValeurBase);
public:
	float GetMaxPowerValue(void);
	float GetMaxPowerValue(float Valeur);
	void AfficheTableDe2();
	void AfficherTable8bits();
	void AfficherBinaire8b();
	void AfficherTable16bits();
	void AfficherBinaire16b();
	int RechercherLaPlusHautePuissance(int Valeur, int reste);
	int RechercherLaPlusHautePuissance(int valeur);
};
/*
=======
#pragma once

#include "resource.h"

class TBinaire
{
public:
	TBinaire(void);
	~TBinaire(void);
	int GetValeur(void);
	void SetValeur(int Valeur);
	char* GetResultatBinaire(void);
	float Exposants;
	char tmp[32];
protected:
	static void InitTableauBinaire(void);
	int GetMaxExposant(float  Valeur);
	void CreerTableDe2();
	int toBase_8(int number);
	int toBase_2_8bits(float number);
	int toBase_2_16bits(float number);
	void CreerTableDeBaseDesiree(int BaseN);
	int ExtractPuissanceLog2(int Valeur);
	void GenerationBaseN(int ValeurBase);
public:
	float GetMaxPowerValue(void);
	float GetMaxPowerValue(float Valeur);
	void AfficheTableDe2();
	void AfficherTable8bits();
	void AfficherBinaire8b();
	void AfficherTable16bits();
	void AfficherBinaire16b();
	int RechercherLaPlusHautePuissance(int Valeur, int reste);
	int RechercherLaPlusHautePuissance(int valeur);
};
/*
>>>>>>> 0e50cecb47656a8e5624f3386586a456f1179eec
*/
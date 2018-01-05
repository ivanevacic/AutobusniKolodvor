#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <locale>
#include <iterator>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <list>
#include <cmath>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include "tinyxml2.h"
#include "Grad.h"
#include "Karta.h"
#include "Zaposlenik.h"

#define PI 4.0*atan(1.0)


using namespace std;
using namespace tinyxml2;


class Kolodvor
{
public:
	Kolodvor();
	~Kolodvor();

	void UcitajGradove();
	void UcitajKarte();
	void UcitajZaposlenike();
	void SpremiPromjeneGrad();
	void SpremiPromjeneKarta();
	void IspisiGradove();
	void Login();
	void Izbornik();
	void KreirajKartu();
	void DodajGrad();
	void AzurirajGrad();
	void PregledKreiranihKarata();
	void Odjava();
	string Vrijeme();
	double Haversine(double lat1, double  lon1, double  lat2, double  lon2);
	void ProvjeraCijeneKarte();
	void PritisnutaTipka();

	bool less_than_key(Karta k1,  Karta k2);
	tinyxml2::XMLDocument xml_Gradovi;
	XMLElement *xml_GradoviDataset;
	tinyxml2::XMLDocument xml_Karte;
	XMLElement *xml_KarteDataset;
	tinyxml2::XMLDocument xml_Zaposlenici;
	XMLElement *xml_ZaposleniciDataset;

	vector<Grad*> vGradovi;
	vector<Karta> vKarte;
	vector<Zaposlenik*>vZaposlenici;

	
};


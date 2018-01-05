#pragma once

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Karta
{
public:
	Karta(string datumKreiranja,string polaziste,string odrediste,string tipKarte,double udaljenost,double cijena);
	~Karta();
	

	string s_DatumKreiranja;
	string s_Polaziste;
	string s_Odrediste;
	string s_TipKarte;
	double d_Udaljenost;
	double d_Cijena;
	bool operator<(const Karta &k1);
	int date_to_int(string datum);
};


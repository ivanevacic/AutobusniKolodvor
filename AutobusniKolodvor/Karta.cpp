#include "stdafx.h"
#include "Karta.h"


Karta::Karta(string datumKreiranja,string polaziste,string odrediste,string tipKarte,double udaljenost,double cijena)
{
	s_DatumKreiranja = datumKreiranja;
	s_Polaziste = polaziste;
	s_Odrediste = odrediste;
	s_TipKarte = tipKarte;
	d_Udaljenost = udaljenost;
	d_Cijena = cijena;
}

bool Karta::operator<(const Karta &a)
{
	string s1 = s_DatumKreiranja;
	string s2 = a.s_DatumKreiranja;
	s1.erase(4, 1);
	s1.erase(6, 1);
	s2.erase(4, 1);
	s2.erase(6, 1);
	int datum1 = stoi(s1);
	int datum2 = stoi(s2);
	
	return(datum1 < datum2);
}

int Karta::date_to_int(string datum)
{
	datum.erase(4, 1);
	datum.erase(6, 1);
	int datum1;
	datum1 = stoi(datum);
	return datum1;

}

Karta::~Karta()
{
}




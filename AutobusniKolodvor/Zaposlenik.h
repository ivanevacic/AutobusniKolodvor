#pragma once

#include <iostream>
#include <string>

using namespace std;

class Zaposlenik
{
public:
	Zaposlenik(string korisnickoIme,string lozinka);
	~Zaposlenik();

	string s_KorisnickoIme;
	string s_Lozinka;
};


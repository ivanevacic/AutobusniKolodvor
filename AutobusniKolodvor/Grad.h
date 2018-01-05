#pragma once

#include <iostream>
#include <string>

using namespace std;

class Grad
{
public:
	Grad(int id,string naziv,double latituda,double longituda,int dostupan);
	~Grad();

	int i_ID;
	string s_NazivGrada;
	double d_Latituda;
	double d_Longituda;
	int i_Dostupan;
	void PromjeniDostupnost(int dostupnost);
	int DajID();
};


#include "stdafx.h"
#include "Grad.h"


Grad::Grad(int id,string naziv,double latituda,double longituda,int dostupan)
{
	i_ID = id;
	s_NazivGrada = naziv;
	d_Latituda = latituda;
	d_Longituda = longituda;
	i_Dostupan = dostupan;
}

void Grad::PromjeniDostupnost(int dostupan)
{
	i_Dostupan = dostupan;
}

int Grad::DajID()
{
	return i_ID;
}

Grad::~Grad()
{
}

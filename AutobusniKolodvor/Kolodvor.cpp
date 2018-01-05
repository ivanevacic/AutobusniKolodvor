#include "stdafx.h"
#include "Kolodvor.h"

#define ESC 27
#define ENTER 13


Kolodvor::Kolodvor()
{
	UcitajGradove();
	UcitajKarte();
	UcitajZaposlenike();
	
}

bool Kolodvor::less_than_key( Karta k1, Karta k2)
{
	return (k1 < k2);
}


void Kolodvor::PregledKreiranihKarata()
{
	sort(vKarte.begin(), vKarte.begin()+6);
	for (int i = 0; i < vKarte.size(); i++)
	{
		cout << "[Datum kreiranja Karte]: " << vKarte[i].s_DatumKreiranja << " [Polaziste]: " << vKarte[i].s_Polaziste << " [Odrediste]: " << vKarte[i].s_Odrediste << " [Tip karte]: " << vKarte[i].s_TipKarte << " [Udaljenost]: " << vKarte[i].d_Udaljenost << " [Cijena]: " << vKarte[i].d_Cijena << endl;
		cout << endl;
		cout << endl;
	}
}

void Kolodvor::UcitajGradove()
{
	xml_Gradovi.LoadFile("Gradovi.xml");
	xml_GradoviDataset = xml_Gradovi.FirstChildElement("Gradovi");
	XMLElement *pChildGrad;
	for (pChildGrad = xml_GradoviDataset->FirstChildElement("Grad"); pChildGrad != NULL; pChildGrad = pChildGrad->NextSiblingElement())
	{
		int i_ID = stof(pChildGrad->Attribute("ID"));
		string s_NazivGrada = pChildGrad->Attribute("Naziv_grada");
		double d_Latituda = stof(pChildGrad->Attribute("Latituda"));
		double d_Longituda = stof(pChildGrad->Attribute("Longituda"));
		int i_Dostupan = stof(pChildGrad->Attribute("Dostupan"));
		vGradovi.push_back(new Grad(i_ID, s_NazivGrada, d_Latituda, d_Longituda, i_Dostupan));
	}
}


void Kolodvor::UcitajKarte()
{
	xml_Karte.LoadFile("Karte.xml");
	xml_KarteDataset = xml_Karte.FirstChildElement("Karte");
	XMLElement *pChildKarta;
	for (pChildKarta = xml_KarteDataset->FirstChildElement("Karta"); pChildKarta != NULL; pChildKarta = pChildKarta->NextSiblingElement())
	{
		string s_DatumKreiranja = pChildKarta->Attribute("Datum_kreiranja_karte");
		string s_Polazište = pChildKarta->Attribute("Polaziste");
		string s_Odredište = pChildKarta->Attribute("Odrediste");
		string s_TipKarte = pChildKarta->Attribute("Tip_karte");
		double d_Udaljenost = stof(pChildKarta->Attribute("Udaljenost"));
		double d_Cijena = stof(pChildKarta->Attribute("Cijena"));
		Karta k1(s_DatumKreiranja, s_Polazište, s_Odredište, s_TipKarte, d_Udaljenost, d_Cijena);
		vKarte.push_back(k1);
	}
}

void Kolodvor::UcitajZaposlenike()
{
	xml_Zaposlenici.LoadFile("Zaposlenici.xml");
	xml_ZaposleniciDataset = xml_Zaposlenici.FirstChildElement("Zaposlenici");
	XMLElement *pChildZaposlenik;
	for (pChildZaposlenik = xml_ZaposleniciDataset->FirstChildElement("Zaposlenik"); pChildZaposlenik != NULL; pChildZaposlenik = pChildZaposlenik->NextSiblingElement())
	{
		string s_KorisnickoIme = pChildZaposlenik->Attribute("Korisnicko_ime");
		string s_Lozinka = pChildZaposlenik->Attribute("Lozinka");
		vZaposlenici.push_back(new Zaposlenik(s_KorisnickoIme, s_Lozinka));
	}
}

void Kolodvor::SpremiPromjeneKarta()
{
	xml_KarteDataset->DeleteChildren();
	for (int i = 0; i < vKarte.size(); i++)
	{
		XMLElement *newKarta = xml_Karte.NewElement("Karta");
		newKarta->SetAttribute("Datum_kreiranja_karte", (vKarte[i].s_DatumKreiranja).c_str());
		newKarta->SetAttribute("Polaziste", (vKarte[i].s_Polaziste).c_str());
		newKarta->SetAttribute("Odrediste", (vKarte[i].s_Odrediste).c_str());
		newKarta->SetAttribute("Tip_karte", (vKarte[i].s_TipKarte).c_str());
		newKarta->SetAttribute("Udaljenost", vKarte[i].d_Udaljenost);
		newKarta->SetAttribute("Cijena", vKarte[i].d_Cijena);
		xml_KarteDataset->LinkEndChild(newKarta);
	}
	xml_Karte.SaveFile("Karte.xml");
}

void Kolodvor::SpremiPromjeneGrad()
{
	xml_GradoviDataset->DeleteChildren();
	for (int i = 0; i < vGradovi.size(); i++)
	{
		XMLElement *newGrad = xml_Gradovi.NewElement("Grad");
		newGrad->SetAttribute("ID", vGradovi[i]->i_ID);
		newGrad->SetAttribute("Naziv_grada", (vGradovi[i]->s_NazivGrada).c_str());
		newGrad->SetAttribute("Latituda", vGradovi[i]->d_Latituda);
		newGrad->SetAttribute("Longituda", vGradovi[i]->d_Longituda);
		newGrad->SetAttribute("Dostupan", vGradovi[i]->i_Dostupan);
		xml_GradoviDataset->LinkEndChild(newGrad);
	}
	xml_Gradovi.SaveFile("Gradovi.xml");
}

void Kolodvor::Login()
{
	string unos_k_ime;
	string unos_loz;
	cout << "Unesite korisnicko ime" << endl;
	cin >> unos_k_ime;
	cout << "Unesite lozinku" << endl;
	cin >> unos_loz;
	for (int i = 0; i < vZaposlenici.size(); i++)
	{
		if (unos_k_ime == vZaposlenici[i]->s_KorisnickoIme && unos_loz == vZaposlenici[i]->s_Lozinka)
		{
			Izbornik();
			goto stop;
			break;
		}
	}
	cout << "Podatci koje ste unjeli nistu tocni.Pokusajte ponovno!" << endl;
	cout << endl;
	Login();
stop:
	cout << endl;
}

void Kolodvor::Izbornik()
{
	cout << endl;
	int odabir;
	cout << "Odaberite jednu od opcija" << endl;
	cout << endl;
	cout << "1)Kreiraj kartu" << endl;
	cout << "2)Pregled kreiranih karata" << endl;
	cout << "3)Provjera cijene karte" << endl;
	cout << "4)Dodaj grad" << endl;
	cout << "5)Azuriraj grad" << endl;
	cout << "6)Odjava" << endl;
	cout << endl;
	cin >> odabir;
	switch (odabir)
	{
	case 1:
		KreirajKartu();
		PritisnutaTipka();
		break;
	case 2:
		PregledKreiranihKarata();
		PritisnutaTipka();
		break;
	case 3:
		ProvjeraCijeneKarte();
		PritisnutaTipka();
		break;
	case 4:
		DodajGrad();
		PritisnutaTipka();
		break;
	case 5:
		AzurirajGrad();
		PritisnutaTipka();
		break;
	case 6:
		Odjava();
		break;
	default:
		break;
	}
}

void Kolodvor::DodajGrad()
{
	int najveci_id = 0;
	string s_NazivGrada;
	double d_Latituda;
	double d_Longituda;
	int i_Dostupan = 1;

	
	cout << "Dodavanje novog grada" << endl;
	cout << endl;
	cout << "Unesite naziv grada:" << endl;
	cin >> s_NazivGrada;
	cout << "Unesite latitudu grada:" << endl;
	cin >> d_Latituda;
	cout << "Unesite longitudu grada:" << endl;
	cin >> d_Longituda;
	
	Grad* ptr_najveci = vGradovi[0];
	
	for (int i = 0; i < vGradovi.size(); i++)
	{
		if (ptr_najveci->DajID() < vGradovi[i]->DajID())
		{
			ptr_najveci = vGradovi[i];
			najveci_id = vGradovi[i]->DajID();
		}
	}
	najveci_id += 1;

	vGradovi.push_back(new Grad(najveci_id,s_NazivGrada,d_Latituda,d_Longituda,i_Dostupan));
	SpremiPromjeneGrad();
	
	
}

void Kolodvor::PritisnutaTipka()
{
	char ch;
	cout << "Pritisnite tipku B za povratak u glavni izbornik,ili tipku E za izlaz iz programa" << endl;
	cin >> ch;
	if (ch == 'b')
	{
		system("cls");
		Izbornik();
	}
	if (ch == 'e')
	{
		Odjava();
	}
}



void Kolodvor::AzurirajGrad()
{
	int odabir;
	int index;
	int dostupnost;
	IspisiGradove();
	cout << "Odaberite grad prema ID-u kojem zelite azurirati dostupnost" << endl;
	cout << endl;
	cin >> odabir;
	for(int i = 0; i < vGradovi.size();i++)
	{
		if (odabir == vGradovi[i]->i_ID)
		{
			index = i;
		}
		else
		{
			cout << "Grad sa unesenim ID-om ne postoji!" << endl;
			break;
		}
	}
	cout << endl;
	cout << "Unesite dostupnost" << endl;
	cin >> dostupnost;
	vGradovi[index]->PromjeniDostupnost(dostupnost);
	SpremiPromjeneGrad();
	
}

void Kolodvor::IspisiGradove()
{
	for (int i = 0; i < vGradovi.size(); i++)
	{
		if (vGradovi[i]->i_Dostupan == 1)
		{
			cout << "[ID]: " << vGradovi[i]->i_ID << " [Naziv grada]: " << vGradovi[i]->s_NazivGrada << " [Latituda]: " << vGradovi[i]->d_Latituda << " [Longituda]: " << vGradovi[i]->d_Longituda << " [Dostupan]: " << vGradovi[i]->i_Dostupan << endl;
			cout << endl;
		}
	}
}

void Kolodvor::KreirajKartu()
{
	Vrijeme();
	string s_Polaziste;
	int i_PolazisteOdabir;
	int i_OdredisteOdabir;
	string s_Odrediste;
	int i_TipKarteSwitch;
	string s_TipKarte;
	double d_Udaljenost;
	double d_Cijena1;
	double d_Cijena;
	double d_Cijena2;
	double lat1, lon1, lat2, lon2;
	cout << "Kreiranje karte" << endl;
	cout << endl;
	IspisiGradove();
	cout << "Unesite polaziste" << endl;
	cin >> i_PolazisteOdabir;
	cout << "Unesite odrediste" << endl;
	cin >> i_OdredisteOdabir;
	for (int i = 0; i < vGradovi.size(); i++)
	{
		if (i_PolazisteOdabir == vGradovi[i]->i_ID)
		{
			s_Polaziste = vGradovi[i]->s_NazivGrada;
			lat1 = vGradovi[i]->d_Latituda;
			lon1 = vGradovi[i]->d_Longituda;
		}
		if (i_OdredisteOdabir == vGradovi[i]->i_ID)
		{
			s_Odrediste = vGradovi[i]->s_NazivGrada;
			lat2 = vGradovi[i]->d_Latituda;
			lon2 = vGradovi[i]->d_Longituda;
		}
	}
	
	
	cout << "Unesite tip karte(1-jednosmjerna,2-povratna)" << endl;
	cin >> i_TipKarteSwitch;
	switch (i_TipKarteSwitch)
	{
	case 1:
		s_TipKarte = "Jednosmjerna";
		d_Cijena = Haversine(lat1,lon1,lat2,lon2) * 0.45;
		d_Udaljenost = Haversine(lat1, lon1, lat2, lon2);
		break;
	case 2:
		s_TipKarte = "Povratna";
		d_Cijena1 = ((Haversine(lat1, lon1, lat2, lon2) * 0.45) * 2);
		d_Cijena2 = ((Haversine(lat1, lon1, lat2, lon2) * 0.45) * 2) * 0.3;
		d_Cijena = d_Cijena1 - d_Cijena2;
		d_Udaljenost = Haversine(lat1, lon1, lat2, lon2) * 2;
		break;
	}
	Karta k2(Vrijeme(), s_Polaziste, s_Odrediste, s_TipKarte, d_Udaljenost, d_Cijena);
	vKarte.push_back(k2);
	SpremiPromjeneKarta();
}


void Kolodvor::ProvjeraCijeneKarte()
{
	string s_Polaziste;
	int i_PolazisteOdabir;
	int i_OdredisteOdabir;
	string s_Odrediste;
	int i_TipKarteSwitch;
	double d_Udaljenost;
	double d_Cijena1;
	double d_Cijena2;
	double d_Cijena;
	double lat1, lon1, lat2, lon2;
	cout << endl;
	IspisiGradove();
	cout << "Unesite polaziste" << endl;
	cin >> i_PolazisteOdabir;
	cout << "Unesite odrediste" << endl;
	cin >> i_OdredisteOdabir;
	for (int i = 0; i < vGradovi.size(); i++)
	{
		if (i_PolazisteOdabir == vGradovi[i]->i_ID)
		{
			s_Polaziste = vGradovi[i]->s_NazivGrada;
			lat1 = vGradovi[i]->d_Latituda;
			lon1 = vGradovi[i]->d_Longituda;

		}
		if (i_OdredisteOdabir == vGradovi[i]->i_ID)
		{
			s_Odrediste = vGradovi[i]->s_NazivGrada;
			lat2 = vGradovi[i]->d_Latituda;
			lon2 = vGradovi[i]->d_Longituda;
		}
	}

	cout << "Unesite tip karte(1-jednosmjerna,2-povratna)" << endl;
	cin >> i_TipKarteSwitch;
	switch (i_TipKarteSwitch)
	{
	case 1:
		d_Cijena = Haversine(lat1, lon1, lat2, lon2) * 0.45;
		d_Udaljenost = Haversine(lat1, lon1, lat2, lon2);
		break;
	case 2:
		d_Cijena1 = ((Haversine(lat1, lon1, lat2, lon2) * 0.45) * 2);
		d_Cijena2 = ((Haversine(lat1, lon1, lat2, lon2) * 0.45) * 2) * 0.3;
		d_Cijena = d_Cijena1 - d_Cijena2;
		d_Udaljenost = Haversine(lat1, lon1, lat2, lon2) * 2;
		break;
	}
	cout << endl;
	cout << "Udaljenost:" << d_Udaljenost << " kilometara" << endl;
	cout << "Cijena:" << d_Cijena << " kuna" << endl;
}




double Kolodvor::Haversine(double lat1, double  lon1, double  lat2, double  lon2)
{
	double dLat1 = lat1*(PI / 180);
	double dLon1 = lon1*(PI / 180);
	double dLat2 = lat2*(PI / 180);
	double dLon2 = lon2*(PI / 180);
	double dLat = dLat1 - dLat2;
	double dLon = dLon1 - dLon2;
	double aHarv = pow(sin(dLat / 2.0), 2.0) + cos(dLat1)*cos(dLat2)*pow(sin(dLon / 2), 2);
	double cHarv = 2 * atan2(sqrt(aHarv), sqrt(1.0 - aHarv));
	const double earth = 6356.750;
	double distance = earth*cHarv;
	return distance;
}


string Kolodvor::Vrijeme()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
	std::string str(buffer);

	return str;
}




void Kolodvor::Odjava()
{
	exit(0);
}


Kolodvor::~Kolodvor()
{
}

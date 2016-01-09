//---------------------------------------------------------------------------

#pragma hdrstop

#include "UProdukty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/// Konstruktor obiektu Opinia, domy�lne ustawienie serwisu jako Ceneo
Opinia::Opinia(AnsiString ATextOpinia)
{
	TextOpinia = ATextOpinia;
	Morele = false;
}
//---------------------------------------------------------------------------
/// Konstruktor obiektu DaneProduktu, w konstruktorze nast�puje czyszczenie danych na wszelki wypadek
DaneProdukt::DaneProdukt()
{
	CzyscProdukt();
}
//---------------------------------------------------------------------------
///Metoda odpowiedzialna za wprowadzenie przekazanych danych produktu.
void __fastcall DaneProdukt::DodajDaneProduktu(AnsiString AMarka, AnsiString AModel, int AKodProduktu, AnsiString ARodzajUrz, AnsiString ADodUwagi)
{
	Marka = AMarka;
	Model = AModel;
	KodProduktu = AKodProduktu;
	RodzajUrz = ARodzajUrz;
	DodUwagi = ADodUwagi;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za dodanie nowej opini do wektora opini
void __fastcall DaneProdukt::DodajOpinie(Opinia* AOpinia)
{
	Opinie.push_back(AOpinia);
}
//---------------------------------------------------------------------------
/// Metoda zwracajaca ilosc opini w wektorze
int __fastcall DaneProdukt::IloscOpini()
{
	return Opinie.size();
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wyczyszczenie danych produktu
void __fastcall DaneProdukt::CzyscProdukt()
{
	Marka = "";
	Model = "";
	KodProduktu = -1;
	RodzajUrz = "";
	DodUwagi = "";
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wyczyszczenie wektora danych opini
void __fastcall DaneProdukt::CzyscOpinie()
{
	std::vector<Opinia*>::iterator it;
	for (it = Opinie.begin(); it != Opinie.end(); it++)
	{
		if ((*it) != NULL) delete (*it); (*it) = NULL;
	}
	Opinie.clear();
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo�anie ca�kowitego czyszczenia danych produktu z pami�ci (dane produktu + opinie)
void __fastcall DaneProdukt::Czysc()
{
	CzyscProdukt();
	CzyscOpinie();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
#ifndef UProduktyH

/// Obiekty tej klasy odpowiadaj� za przetrzymywanie szczeg�owych danych poszczeg�lnych opini.
class Opinia
{
private:

					  // porobic property
public:
	Opinia(AnsiString ATextOpinia);
	/// Autor opini
	AnsiString Autor;
	/// Tekst opini
	AnsiString Opinia;
	/// Wady produktu
	AnsiString Wady;
	/// Zalety produktu
	AnsiString Zalety;
	/// Liczba gwiazdek (ocena)
	AnsiString LGwiazdek;
	/// Data wystawienia opini
	AnsiString Data;
	/// Czy autor opini poleca produkt
	AnsiString PolecNPolec;
	/// procentowa przydatnosc opini
	AnsiString PrzydatnaOpiniaPr;
	/// Ile os�b oceni�o opini� jako przydatn�
	AnsiString IleOsOcPrzydatnosc;
	/// Tekst opini przed parsowaniem
	AnsiString TextOpinia;
	/// Zmienna odpowiedzialna za przetrzymanie informacji o tym z jakiego serwisu pochodzi opinia Ceneo/ Morele
	bool Morele;
};
//---------------------------------------------------------------------------
/// Obiekt tej klasy odpowiada za przetrzymywanie danych produktu.
/// Posiada on wektor wska�nik�w do utworzonych obiekt�w opinii.
class DaneProdukt
{
private:
public:
	DaneProdukt();
	/// Marka produktu
	AnsiString Marka;
	/// Model produktu
	AnsiString Model;
	/// Kod produktu
	int KodProduktu;
	/// Rodzaj urz�dzenia
	AnsiString RodzajUrz;
	/// dodatkowe uwagi na temat produktu
	AnsiString DodUwagi;
	void __fastcall DodajDaneProduktu(AnsiString AMarka, AnsiString AModel, int AKodProduktu, AnsiString ARodzajUrz, AnsiString ADodUwagi);
	void __fastcall DodajOpinie(Opinia* AOpinia);
	int __fastcall IloscOpini();
	/// Wektor opini produktu
	std::vector<Opinia*> Opinie;
	void __fastcall Czysc();
	void __fastcall CzyscProdukt();
	void __fastcall CzyscOpinie();
};

class Produkty
{
	std::vector<DaneProdukt*> DaneProdukty;
};

#define UProduktyH
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef UParsujH
#define UParsujH
#include "UProdukty.h"
//---------------------------------------------------------------------------
/// Klasa odpowiedzialna za dostarczenie metod s�u��cych do parsowania danych
/// oraz przeprowadzenie poszczeg�lnych operacji na analizowanych tekstach.
class ParsujDane
{
private:
	/// Wska�nik do przekazywanego obiektu produktu
	DaneProdukt *FProdukt;
	/// Przekazany tekst z danymi produktu oraz opiniami, tekst przed procesem parsowania
	AnsiString Text;
	/// Tekst zawieraj�cy wszystkie dane produktu, z kt�rego w kolejnych etapach stopniowo wyci�gane s� kolejne dane
	AnsiString DaneProduktuText;

	void __fastcall ZaladujDaneProduktu();
	AnsiString __fastcall ZnajdzDane(AnsiString &AText, AnsiString AZnacznikPocz, char AZnakKonca);
	void __fastcall ZaladujTextyOpini();
	void __fastcall ZaladujDaneOpini();
	void __fastcall WyczyscZnaczniki(AnsiString &AText);
	void __fastcall UsunZnacznik(AnsiString &AText, AnsiString AZnacznik, bool AWstawENDL = false);
	void __fastcall DostosujWadyIZalety(AnsiString &AText);
	void __fastcall DostosujZnakiSpecjalne(AnsiString &AText);


public:
	static AnsiString __fastcall ZnajdzTekstOpini(AnsiString &ATextOpini, AnsiString AZnacznikPocz, AnsiString AZnacznikKoniec, bool ATnij = true);
	ParsujDane(DaneProdukt *AProdukt, AnsiString AText);
	/// Zmienna informuj�ca o b�edzie wynikaj�cym z nieobs�ugiwanej kategorii (brak parsera dla wprowadzonej kategorii produktu).
	bool BladKategorii;
};

#endif

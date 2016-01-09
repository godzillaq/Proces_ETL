//---------------------------------------------------------------------------

#ifndef UParsujH
#define UParsujH
#include "UProdukty.h"
//---------------------------------------------------------------------------
/// Klasa odpowiedzialna za dostarczenie metod s³u¿¹cych do parsowania danych
/// oraz przeprowadzenie poszczególnych operacji na analizowanych tekstach.
class ParsujDane
{
private:
	/// WskaŸnik do przekazywanego obiektu produktu
	DaneProdukt *FProdukt;
	/// Przekazany tekst z danymi produktu oraz opiniami, tekst przed procesem parsowania
	AnsiString Text;
	/// Tekst zawieraj¹cy wszystkie dane produktu, z którego w kolejnych etapach stopniowo wyci¹gane s¹ kolejne dane
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
	/// Zmienna informuj¹ca o b³edzie wynikaj¹cym z nieobs³ugiwanej kategorii (brak parsera dla wprowadzonej kategorii produktu).
	bool BladKategorii;
};

#endif

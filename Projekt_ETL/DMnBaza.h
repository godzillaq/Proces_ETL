//---------------------------------------------------------------------------

#ifndef DMnBazaH
#define DMnBazaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include "UProdukty.h"
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
/// Klasa ta odpowiada za utworzenie po³¹czenia z baz¹ danych oraz wykonywanie operacji bazodanowych,
/// odpowiada równie¿ za czyszczenie bazy z danych, zwracania informacji o iloœci poszczególnych danych w bazie,
/// oraz za uzupe³nianie listy produktów ComboBoxów.
class TDMBaza : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ACPolaczenie;
	TADOQuery *Query;
private:	// User declarations
	/// WskaŸnik do przekazywanego obiektu produktu
	DaneProdukt *FProdukt;
public:		// User declarations
	__fastcall TDMBaza(TComponent* Owner, DaneProdukt *AProdukt);
	void __fastcall ZaladujDaneProduktu();
	void __fastcall CzyscBaze();
	int __fastcall IloscProduktow();
	int __fastcall IloscOpini(int AId = -1);
	/// Zmienna odpowiedzialna za poinformowanie czy zosta³ dodany nowy produkt do bazy
	bool DodanoProdukt;
	/// Zmienna odpowiedzialna za przetrzymywanie informacji o iloœci dodanych opini do bazy
	int DodanychOpini;
	void __fastcall ZaladujCbxIdProd(TComboBox *ACbx);
};
//---------------------------------------------------------------------------
extern PACKAGE TDMBaza *DMBaza;
//---------------------------------------------------------------------------
#endif

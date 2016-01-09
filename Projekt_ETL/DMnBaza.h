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
/// Klasa ta odpowiada za utworzenie po��czenia z baz� danych oraz wykonywanie operacji bazodanowych,
/// odpowiada r�wnie� za czyszczenie bazy z danych, zwracania informacji o ilo�ci poszczeg�lnych danych w bazie,
/// oraz za uzupe�nianie listy produkt�w ComboBox�w.
class TDMBaza : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ACPolaczenie;
	TADOQuery *Query;
private:	// User declarations
	/// Wska�nik do przekazywanego obiektu produktu
	DaneProdukt *FProdukt;
public:		// User declarations
	__fastcall TDMBaza(TComponent* Owner, DaneProdukt *AProdukt);
	void __fastcall ZaladujDaneProduktu();
	void __fastcall CzyscBaze();
	int __fastcall IloscProduktow();
	int __fastcall IloscOpini(int AId = -1);
	/// Zmienna odpowiedzialna za poinformowanie czy zosta� dodany nowy produkt do bazy
	bool DodanoProdukt;
	/// Zmienna odpowiedzialna za przetrzymywanie informacji o ilo�ci dodanych opini do bazy
	int DodanychOpini;
	void __fastcall ZaladujCbxIdProd(TComboBox *ACbx);
};
//---------------------------------------------------------------------------
extern PACKAGE TDMBaza *DMBaza;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------


#pragma hdrstop

#include "DMnBaza.h"
#include "UProdukty.h"
#include "UParsuj.h"
#include <vcl.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TDMBaza *DMBaza;
//---------------------------------------------------------------------------
/// Konstruktor klasy, przypisuje równie¿ przekazywany obiekt do wskaŸnika wewn¹trz obiektu Bazy
__fastcall TDMBaza::TDMBaza(TComponent* Owner, DaneProdukt *AProdukt)
	: TDataModule(Owner)
{
	FProdukt = AProdukt;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za za³adowanie danych produktu, metoda ta pomija dane w przypadku gdy istniej¹ ju¿ w bazie
void __fastcall TDMBaza::ZaladujDaneProduktu()
{
	AnsiString sql;
	int i = 0;
	DodanoProdukt = true;
	std::vector<Opinia*>::iterator itOpinie;

	sql = "Insert into Produkt values(" + AnsiString(FProdukt->KodProduktu) + ", \'" + AnsiString(FProdukt->Marka) + "\', \'";
	sql += AnsiString(FProdukt->Model) + "\', \'" + AnsiString(FProdukt->RodzajUrz) + "\', \'" + AnsiString(FProdukt->DodUwagi) + "\');";
	Query->SQL->Text = sql;

	try
	{
		Query->ExecSQL();
	}
	catch (...) { DodanoProdukt = false; }

	for (itOpinie = FProdukt->Opinie.begin(); itOpinie != FProdukt->Opinie.end(); itOpinie++)
	{
		sql = "Insert into Opinia values(" + AnsiString(FProdukt->KodProduktu);
		sql += ", \'" + (*itOpinie)->Autor + "\', \'";
		sql += (*itOpinie)->Opinia + "\', \'";
		sql += (*itOpinie)->Wady + "\', \'";
		sql += (*itOpinie)->Zalety + "\', \'";
		sql += (*itOpinie)->LGwiazdek + "\', \'";
		sql += (*itOpinie)->Data + "\', \'";
		sql += (*itOpinie)->PolecNPolec + "\', \'";
		sql += (*itOpinie)->PrzydatnaOpiniaPr + "\', \'";
		sql += (*itOpinie)->IleOsOcPrzydatnosc + "\')";
		Query->SQL->Text = sql;
		try
		{
			Query->ExecSQL();
		}
		catch(...) {
		//ShowMessage(sql);
		continue;  }
		i++;
	}
	DodanychOpini = i;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie na bazie polecenia czyszcz¹cego wszystkie dane produktów wraz z opiniami.
void __fastcall TDMBaza::CzyscBaze()
{
	AnsiString sql;
	sql = "delete from Produkt cascade";
	Query->SQL->Text = sql;
	Query->ExecSQL();
}
//---------------------------------------------------------------------------
/// Metoda wywo³uje odpowiednie zapytanie na bazie oraz zwraca iloœæ produktów dodanych do bazy danych.
int __fastcall TDMBaza::IloscProduktow()
{
	AnsiString sql;
	TField *ilProd;
	int ileProduktow;
	sql = "select COUNT(*) as IloscProduktow from Produkt";
	Query->SQL->Text = sql;
	Query->Open();
	ilProd = Query->FieldByName("IloscProduktow");
	ileProduktow = ilProd->AsInteger;
	Query->Close();
	return ileProduktow;
}
//---------------------------------------------------------------------------
/// Metoda wywo³uje odpowiednie zapytanie na bazie oraz zwraca iloœæ opini dodanych do bazy danych.
int __fastcall TDMBaza::IloscOpini(int AId)
{
	AnsiString sql;
	TField *ilOpin;
	int ileOpini;
	sql = "select COUNT(*) as IloscOpini from Opinia";
	if (AId != -1) { sql += " where IdProdukt = "; sql += AnsiString(AId); }
	Query->SQL->Text = sql;
	Query->ExecSQL();
	Query->Open();
	ilOpin = Query->FieldByName("IloscOpini");
	ileOpini= ilOpin->AsInteger;
	Query->Close();
	return ileOpini;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna jest za pobranie z bazy danych wszystkich Id Produktów
/// oraz za³adowanie ich do przekazanego przez wskaŸnik komponentu ComboBox (lista rozwijalna).
void __fastcall TDMBaza::ZaladujCbxIdProd(TComboBox *ACbx)
{
	AnsiString str, sql = "";
	TField *FKodProduktu;
	sql = "Select * From Produkt";
	Query->SQL->Text = sql;
	Query->Open();
	if (!Query->Eof)
	{
		FKodProduktu = Query->FieldByName("KodProduktu");
		for (Query->First(); !Query->Eof; Query->Next())
		{
    		ACbx->Items->Add(FKodProduktu->AsString);
		}
	}
	Query->Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

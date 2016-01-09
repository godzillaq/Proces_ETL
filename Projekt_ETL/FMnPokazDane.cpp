//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FMnPokazDane.h"
#include "UProdukty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma link "cgauges"
#pragma link "pies"
#pragma resource "*.dfm"


TFMainPokazDane *FMainPokazDane;
/// Konstruktor okna odpowiedzialnego za prezentacje danych dodanych do bazy danych.
/// Konstruktor ten odpowada również za ustawienie kolumn widocznych w gridzie,
/// wywołuje również metodę odpowiedzialną za załadowanie danych kodów produktów do ComboBoxa.
//---------------------------------------------------------------------------
__fastcall TFMainPokazDane::TFMainPokazDane(TComponent* Owner, TDMBaza *ABaza)
	: TForm(Owner)
{
	FBaza = ABaza;
	StringGrid1->ColWidths[0] = 0;
	StringGrid1->ColWidths[1] = 170;
	StringGrid1->ColWidths[2] = 300;
	StringGrid1->ColWidths[3] = 150;
	StringGrid1->ColWidths[4] = 150;
	StringGrid1->ColWidths[5] = 200;
	StringGrid1->EditorMode = false;
	FBaza->ZaladujCbxIdProd(Cbx);
}
//---------------------------------------------------------------------------
/// Event odpowiedzialny za rysowanie danych w gridzie, dzięki czemu można łamać tekst w kolumnie (standardowo nie jest to obsługiwane).
void __fastcall TFMainPokazDane::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
    if (FBlokujOdswiezanie) return;
	if (State.Contains(gdFixed))
	{
		  StringGrid1->Canvas->Brush->Color = clBtnFace;
		  StringGrid1->Canvas->Font->Color = clWindowText;
		  StringGrid1->Canvas->FillRect(Rect);
		  Frame3D(StringGrid1->Canvas, Rect, clBtnHighlight, clBtnShadow, 1);
	}
	// jeżeli cela wybrana
	else if (State.Contains(gdSelected))
	{
		  StringGrid1->Canvas->Brush->Color = clHighlight;
		  StringGrid1->Canvas->Font->Color = clHighlightText;
		  StringGrid1->Canvas->FillRect(Rect);
	}
	else
	{
		  StringGrid1->Canvas->Brush->Color = StringGrid1->Color;
		  StringGrid1->Canvas->Font->Color = StringGrid1->Font->Color;
		  StringGrid1->Canvas->FillRect(Rect);
	}
	TRect DrawRect = Rect;
	AnsiString CellText = StringGrid1->Cells[ACol][ARow];
	DrawTextA(StringGrid1->Canvas->Handle,CellText.c_str(),-1,
			&DrawRect,DT_WORDBREAK | DT_CALCRECT | DT_LEFT);
	if(StringGrid1->RowHeights[ARow] < (DrawRect.Bottom - DrawRect.Top) +2)
		  StringGrid1->RowHeights[ARow] = (DrawRect.Bottom - DrawRect.Top) +2;
	DrawTextA(StringGrid1->Canvas->Handle,CellText.c_str(),CellText.Length(),
		  &DrawRect,DT_WORDBREAK | DT_LEFT);
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za załadowanie danych produktu do Labeli widocznych w oknie.
void __fastcall TFMainPokazDane::ZaladujDaneProduktu()
{
	AnsiString str, sql = "";
	int i = 0;
	TField *FKodProduktu, *FMarka, *FModel, *FRodzUrz, *FDodUwagi;
	sql = "Select * From Produkt";
	sql += " where KodProduktu = "; sql += AnsiString(FIdProdukt);
	FBaza->Query->SQL->Text = sql;
	FBaza->Query->Open();
	if (!FBaza->Query->Eof)
	{
		FKodProduktu = FBaza->Query->FieldByName("KodProduktu");
		FMarka = FBaza->Query->FieldByName("Marka");
		FModel = FBaza->Query->FieldByName("Model");
		FRodzUrz = FBaza->Query->FieldByName("RodzajUrz");
		FDodUwagi = FBaza->Query->FieldByName("DodUwagi");
		for (FBaza->Query->First(); !FBaza->Query->Eof; FBaza->Query->Next())
		{
			LblKodProduktu->Caption = FKodProduktu->AsString;
			LblMarka->Caption = FMarka->AsString;
			LblModel->Caption = FModel->AsString;
			LblRodzUrz->Caption = FRodzUrz->AsString;
			LblDodUwagi->Caption = FDodUwagi->AsString;
		}
	}
	FBaza->Query->Close();
}
//---------------------------------------------------------------------------
///Metoda odpowiedzialna za odpytanie bazy o dane opini dla konkretnego produktu oraz
/// załadowanie pobranych danych do grida, metoda wywoływana jest również w celu załadowania pliku tekstowego do zapisu do pliku CSV
AnsiString __fastcall TFMainPokazDane::ZaladujGridDanymi(bool ALadujDoCsv)
{

	AnsiString text, str, sql = "";
	int i = 0;
	TField *FAutor, *FData, *FPolecNPolec, *FOpinia,
			*FWady, *FZalety, *FLGwiazdek, *FPrPrzydatnoscOpini, *FIleOsOcPrzydatnosc;
	sql = "Select * From Opinia";
	sql += " where IdProdukt = "; sql += AnsiString(FIdProdukt);

	FBaza->Query->SQL->Text = sql;
	FBaza->Query->Open();
	if (!FBaza->Query->Eof)
	{
		FAutor = FBaza->Query->FieldByName("Autor");
		FData = FBaza->Query->FieldByName("Data");
		FPolecNPolec = FBaza->Query->FieldByName("Polecnpolec");
		FOpinia = FBaza->Query->FieldByName("Opinia");
		FWady = FBaza->Query->FieldByName("Wady");
		FZalety = FBaza->Query->FieldByName("Zalety");
		FLGwiazdek = FBaza->Query->FieldByName("LGwiazdek");
		FPrPrzydatnoscOpini = FBaza->Query->FieldByName("PrzydatnaOpiniaPr");
		FIleOsOcPrzydatnosc  = FBaza->Query->FieldByName("IleOsOcPrzydatnosc");

		if (ALadujDoCsv)
		{
			text += "Lp."; text += ";";
			text += "Autor"; text += ";";
			text += "Data"; text += ";";
			text += "CzyPoleca"; text += ";";
			text += "Opinia"; text += ";";
			text += "Wady"; text += ";";
			text += "Zalety"; text += ";";
			text += "LiczbaGwiazdek"; text += ";";
			text += "PrzydatnoscOpini"; text += ";";
			text += "IleOsOceniaPrzydatn"; text += ";";
			text += "\n";
		}

		for (FBaza->Query->First(); !FBaza->Query->Eof; FBaza->Query->Next())
		{
			if (!ALadujDoCsv)
			{
				StringGrid1->Cells[1][i] = "Lp. " + AnsiString(i+1) + "\n" + FAutor->AsString + "\n" + FData->AsString + "\n" + FPolecNPolec->AsString;
				str = FOpinia->AsString;
				ZmienZnacznikENDL(str);
				StringGrid1->Cells[2][i] = str;
				str = "Wady:\n" + FWady->AsString;
				ZmienZnacznikENDL(str);
				StringGrid1->Cells[3][i] = str;
				str = "Zalety:\n" + FZalety->AsString;
				ZmienZnacznikENDL(str);
				StringGrid1->Cells[4][i] = str;
				str = "Ocena: "; str += FLGwiazdek->AsString; str += "\n";
				str += "Opinia przydatna dla: "; str += FPrPrzydatnoscOpini->AsString; str += "% ";
				str += FIleOsOcPrzydatnosc->AsString;
				StringGrid1->Cells[5][i] = str;

				StringGrid1->RowCount = StringGrid1->RowCount + 1;
			}
			if (ALadujDoCsv)
			{
				text += AnsiString(i+1); text += ";";
				text += FAutor->AsString; text += ";";
				text += FData->AsString; text += ";";
				text += FPolecNPolec->AsString; text += ";";
				text += FOpinia->AsString; text += ";";
				text += FWady->AsString; text += ";";
				text += FZalety->AsString; text += ";\'";
				text += FLGwiazdek->AsString; text += ";";
				text += FPrPrzydatnoscOpini->AsString; text += ";";
				text += FIleOsOcPrzydatnosc->AsString; text += ";";
				text += "\n";
			}
			i++;
		}
		if (!ALadujDoCsv) StringGrid1->RowCount = StringGrid1->RowCount - 1;
	}
	FBaza->Query->Close();
	return text;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za dostosowanie widocznego tekstu - usunięcie znaczników
void __fastcall TFMainPokazDane::ZmienZnacznikENDL(AnsiString &AText)
{
	int pozycja;
	AnsiString znakENDL = "<ENDL>";
	if (AText.IsEmpty()) return;

	while (true)
	{
		pozycja = AText.Pos(znakENDL);
		if (pozycja <= 0) break;
		if (pozycja > 0) AText.Delete(pozycja, znakENDL.Length());
		AText.Insert("\n", pozycja);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za zmiane oraz przeładowanie widocznych danych po kliknięciu
/// w wybrany kod produktu w ComboBoxie
void __fastcall TFMainPokazDane::CbxClick(TObject *Sender)
{
	//
	int ile;
	FIdProdukt = Cbx->Items->Strings[Cbx->ItemIndex].ToInt();
	LblIlOpini->Caption = AnsiString(FBaza->IloscOpini(FIdProdukt));

	ile = StringGrid1->RowCount;
	FBlokujOdswiezanie = true;
	for(int c = 0; c < ile; c++)
	{
		int i=0, j=0;
		for (i = c;i < StringGrid1->RowCount - 1;i++)
			for (j = 0;j < StringGrid1->ColCount;j++)
				StringGrid1->Cells[j][i]=StringGrid1->Cells[j][i + 1];
		StringGrid1->RowCount = StringGrid1->RowCount - 1;
	}
	FBlokujOdswiezanie = false;
	ZaladujDaneProduktu();
	ZaladujGridDanymi();
	if (FBaza->IloscOpini(FIdProdukt) == 0) StringGrid1->Visible = false;
	else StringGrid1->Visible = true;
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za zapis wszystkich widocznych opini do pliku *.CSV,
/// użytkownik sam ma możliwość wybrania katolgu docelowego oraz nazwy dla tworzonego pliku.
void __fastcall TFMainPokazDane::BtnZapiszClick(TObject *Sender)
{
	TFileStream *file;
	AnsiString text, plik;
	if (FIdProdukt <= 0)
	{
		ShowMessage("Wybierz produkt z listy!");
		return;
	}

	if (SDialog->Execute())
	{
		plik = SDialog->FileName + ".csv";
		file=new TFileStream(plik.c_str(),fmCreate);
		text = ZaladujGridDanymi(true);
		file->WriteBuffer(text.c_str(), text.Length());
		delete file;
	}
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za zapis wybranej opini do pliku Txt
void __fastcall TFMainPokazDane::BtnZapisTxtClick(TObject *Sender)
{
	TFileStream *file;
	AnsiString str, text, sql, plik;
	int idOpini;
	TField *FAutor, *FData, *FPolecNPolec, *FOpinia,
			*FWady, *FZalety, *FLGwiazdek, *FPrPrzydatnoscOpini, *FIleOsOcPrzydatnosc;

	try
	{
		idOpini = EdIdOpini->Text.ToInt();
		if (idOpini == 0 || idOpini > FBaza->IloscOpini(FIdProdukt))
		{
			ShowMessage("Brak opini o podanym Id");
			EdIdOpini->Clear();
			return;
		}
	}
	catch(...) { EdIdOpini->Clear(); throw; }

	if (FIdProdukt <= 0)
	{
		ShowMessage("Wybierz produkt z listy!");
		return;
	}

	if (SDialog2->Execute())
	{
		sql = "with opinieWiersze As(";
		sql += " select *, ROW_NUMBER() OVER () RN from opinia";
		sql += " where IdProdukt = "; sql += AnsiString(FIdProdukt);
		sql += " ) select * from opinieWiersze where RN = ";
		sql += EdIdOpini->Text;

		FBaza->Query->SQL->Text = sql;
		FBaza->Query->Open();
		if (!FBaza->Query->Eof)
		{
			FAutor = FBaza->Query->FieldByName("Autor");
			FData = FBaza->Query->FieldByName("Data");
			FPolecNPolec = FBaza->Query->FieldByName("Polecnpolec");
			FOpinia = FBaza->Query->FieldByName("Opinia");
			FWady = FBaza->Query->FieldByName("Wady");
			FZalety = FBaza->Query->FieldByName("Zalety");
			FLGwiazdek = FBaza->Query->FieldByName("LGwiazdek");
			FPrPrzydatnoscOpini = FBaza->Query->FieldByName("PrzydatnaOpiniaPr");
			FIleOsOcPrzydatnosc  = FBaza->Query->FieldByName("IleOsOcPrzydatnosc");

			text +=	"Autor: "; text += FAutor->AsString; text += "\n";
			text +=	"Data: "; text += FData->AsString; text += "\n";
			text +=	"Czy poleca: "; text += FPolecNPolec->AsString; text += "\n";
			str = FOpinia->AsString;
			ZmienZnacznikENDL(str);
			text +=	"Opinia: "; text += str; text += "\n";
			str = FWady->AsString;
			ZmienZnacznikENDL(str);
			text +=	"Wady: "; text += str; text += "\n";
			str = FZalety->AsString;
			ZmienZnacznikENDL(str);
			text +=	"Zalety: "; text += str; text += "\n";
			text +=	"Liczba gwiazdek: "; text += FLGwiazdek->AsString; text += "\n";
			text += "Przydatność opini [%]: "; text += FPrPrzydatnoscOpini->AsString; text += "\n";
			text += "Ile osób oceniło opinię jako przydatną: "; text += FIleOsOcPrzydatnosc->AsString; text += "\n";
		}

		plik = SDialog2->FileName + ".txt";

		file=new TFileStream(plik.c_str(),fmCreate);
		file->WriteBuffer(text.c_str(), text.Length());
		delete file;
	}
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FMnExTractor.h"
#include "UProdukty.h"
#include "UParsuj.h"
#include <time.h>
#include "DMnBaza.h"
#include "FMnPokazDane.h"

/**
\mainpage Proces ETL dokumentacja.

Autor: Tomasz Lisowski
*/


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_2K_SRVR"
#pragma resource "*.dfm"
TFMainExtractor *FMainExtractor;
//---------------------------------------------------------------------------
/// Konstruktor klasy g³ównego okna programu, tworzy obiekt g³ównego po³¹czenia z baz¹ danych
/// oraz g³ówny obiekt produktu, do którego ³adowane bêd¹ dane opini
/// odpowiada równie¿ za wyœwietlenie statystyk na temat iloœci danych w bazie danych.
__fastcall TFMainExtractor::TFMainExtractor(TComponent* Owner)
	: TForm(Owner)
{
	Produkt = new DaneProdukt();
	Baza = new TDMBaza(NULL, Produkt);
	AktualizujLicznikDanych();
	BtnT->Enabled = false;
	BtnL->Enabled = false;
}
//---------------------------------------------------------------------------
/// Destruktor odpowiedzialny za calkowite wyczyszczenie z pamieci danych produktu
/// wraz z opiniami oraz za usuniêcie obiektu odpowiedzialnego za po³¹czenie z baz¹ danych,
/// wczeœniej na wszelki wypadek dokonywane jest zamkniêcie obiektu Query
__fastcall TFMainExtractor::~TFMainExtractor()
{
	Produkt->Czysc();
	delete Produkt;
	Baza->Query->Close();
	delete Baza;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za ekstrakcjê tekstów, wywo³uje ona "pod program" w jêzyku skryptowym,
/// za pomoc¹ którego dokonywana jest w³aœciwa ekstrakcja tekstów.
/// Metoda przyjmuje jako parametr kod produktu oraz parametr odpowiedzialny za rozpoznanie serwisu,
/// z którego pobierany bêdzie tekst.
///
/// Pierwsz¹ pod aplikacj¹ napisan¹ w jêzyku skryptowym AutoIt jest "extractor"
/// jako parametr przyjmuje ona kod produktu z serwisu ceneo po czym nastêpuje pobieranie stron,
/// po zakoñczeniu dzia³ania pod aplikacji zwracany jest pojedyczny plik tekstowy zawieraj¹cy
/// dane produktu oraz jego opini. Skrypt odpowiada równie¿ za znalezienie na stronie z produktem
/// odniesienia do danych tego samego produktu w innym serwisie, w przypadku niniejszej aplikacji jest to serwis Morele
///
/// Drug¹ pod aplikacj¹ napisan¹ równie¿ w jêzyku skryptowym jest "extractorMorele"
/// s³u¿y do wyci¹gania danych opini z serwisu Morele. Skrypt przyjmuje jako parametr
/// adres strony do produktu w serwisie Morele, nastepnie wyszukiwany zostaje kod produktu.
/// Dane opini w serwisie Morele wyci¹gane s¹ dziêki zastosowaniu "Ajax'owego call'a", wiêc
/// kod prouktu zostaje wywo³ywany dziêki zastosowaniu "ajaxGetReviews" ze strony
/// dzieki czemu uzyskujemy dostêp do wszystkich danych opini na jednej stronie. Wspomniane opinie zostaj¹
/// zapisane w jednym zwracanym pliku tekstowym.
bool __fastcall TFMainExtractor::Extract(AnsiString AKodProduktu, bool AMorele)
{
	int x;
	bool ret = true;
	wchar_t wstr[1000];
	SHELLEXECUTEINFO rSEI = { 0 };

	if (!AMorele)
	{
		FKodProduktu = EdKodProduktu->Text;
		AKodProduktu = FKodProduktu;
	}
	if (FKodProduktu.IsEmpty()) ret = false;
	try { x = FKodProduktu.ToInt(); }catch(...) { ret = false; }

	if (!ret && !AMorele)
	{
		ShowMessage("Niepoprawny format kodu produktu!");
		OdblokujPrzyciski();
		MDane->Clear();
		return false;
	}

	rSEI.cbSize = sizeof( rSEI );
	rSEI.lpVerb = L"open";
	if (!AMorele) rSEI.lpFile = L"extractor";
	else rSEI.lpFile = L"extractorMorele";
	rSEI.lpParameters = AKodProduktu.WideChar(wstr, 1000);
	rSEI.nShow = SW_NORMAL;
	rSEI.fMask = SEE_MASK_NOCLOSEPROCESS;

	ShellExecuteEx( &rSEI );
	while( TRUE )
	{
		DWORD nStatus= MsgWaitForMultipleObjects(1, &rSEI.hProcess, FALSE, INFINITE, QS_ALLINPUT);
		if ( nStatus == WAIT_OBJECT_0 )
		{
			break;
		}
		MSG msg;
		while( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
		{
			DispatchMessage( &msg );
		}
	}
	DWORD dwCode;
	GetExitCodeProcess( rSEI.hProcess, &dwCode );  // ERRORLEVEL value
	return true;
}
//---------------------------------------------------------------------------
/// Metoda wywo³uj¹ca obiekt klasy odpowiedzialnej za parsowanie pobranego tekstu.
bool __fastcall TFMainExtractor::Parsuj()
{
	bool ret = true;
	ParsujDane * parsuj = new ParsujDane(Produkt, FPobranyTekst);
	if (parsuj->BladKategorii) ret =  false;
	else ret = true;
	delete parsuj; parsuj = NULL;
	return ret;
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za wywo³anie i przeprowadzenie ca³ego procesu ETL krok po kroku.
void __fastcall TFMainExtractor::BtnETLClick(TObject *Sender)
{
	TStringList *text;
	AnsiString kodDlaMorele, str, plik, plikMorele;
	plik = "Opinie.txt";
	plikMorele = "Opinie2.txt";

	BtnCzyscBaze->Enabled = false;
	BtnETL->Enabled = false;
	BtnE->Enabled = false;
	BtnT->Enabled = false;
	BtnL->Enabled = false;
	BtnDane->Enabled = false;


	MDane->Lines->Clear();
	str = "###############################";
	MDane->Lines->Add(str);
	str = "          Rozpoczêto proces ETL";
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);


	str = "Trwa ekstrakcja textów dla produktu: " + EdKodProduktu->Text;
	MDane->Lines->Add(str);
	if (!Extract(FKodProduktu)) { OdblokujPrzyciski(); return; }
	str = "Pobrano plik dla serwisu Ceneo";
	MDane->Lines->Add(str);

	text = new TStringList;
	try
	{
		text->LoadFromFile(plik);
		DeleteFileW(plik);
		str = "Usuniêto pobrany plik dla serwisu Ceneo";
		MDane->Lines->Add(str);
		FPobranyTekst = Utf8ToAnsi(text->Text); // okazuje siê ¿e AutoIt zapisuje tekst jako UTF-8 w celu nie "wykrzaczania" polskich znaków lepiej siê zabezpieczyæ!
		if (FPobranyTekst.IsEmpty())
		{
			ShowMessage("Coœ posz³o nie tak, b³êdny Id produktu?!");
			OdblokujPrzyciski();
			return;// false;
		}

		kodDlaMorele = ParsujDane::ZnajdzTekstOpini(FPobranyTekst, "<MORELE>", "</MORELE>");
		if (kodDlaMorele.Length() > 1)
		{
			Extract(kodDlaMorele, true);
			str = "Pobrano plik dla serwisu Morele";
			MDane->Lines->Add(str);
			text->Clear();
			text->LoadFromFile(plikMorele);
			FPobranyTekst += Utf8ToAnsi(text->Text);
			try
			{
				DeleteFileW(plikMorele);
			}
			catch(...) { }
			str = "Usuniêto pobrany plik dla serwisu Morele";
			MDane->Lines->Add(str);
		}
		else
		{
			str = "Brak odniesienia w Ceneo dla produktu w serwisie Morele";
			MDane->Lines->Add(str);
		}
	}
	catch(...) { if (text != NULL) delete text; text = NULL; throw; }
	if (text != NULL) delete text;
	text = NULL;

	str = "Trwa parsowanie danych";
	MDane->Lines->Add(str);
	if (!Parsuj()) { OdblokujPrzyciski(); return; }
	str = "Parsowanie zakoñczone.";
	MDane->Lines->Add(str);
	str = "Trwa ³adowanie danych do bazy:";
	MDane->Lines->Add(str);
	Laduj();
	str = "Dodano nowy produkt: "; if (Baza->DodanoProdukt) str += "Tak"; else str += "Nie";
	MDane->Lines->Add(str);
	str = "Dodano nowych opini: "; str += AnsiString(Baza->DodanychOpini);
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);
	str = "                     Zakoñczono";
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);

	Produkt->Czysc();
	OdblokujPrzyciski();
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie metody (po³¹czenie z baz¹) odpowiedzialnej za za³adowanie danych do bazy danych.
/// Metoda ta aktualizuje równie¿ widoczny "Licznik danych".
bool __fastcall TFMainExtractor::Laduj()
{
	Baza->ZaladujDaneProduktu();
	AktualizujLicznikDanych();
	return true;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie metody czyszczenia wszystkich danych w bazie oraz aktualizacji widocznego "Licznika danych"
void __fastcall TFMainExtractor::BtnCzyscBazeClick(TObject *Sender)
{
	Baza->CzyscBaze();
	AktualizujLicznikDanych();
	MDane->Clear();
}
//---------------------------------------------------------------------------
/// Metoda ta aktualizuje widoczny w g³ównym oknie programu licznik danych za³adowanych do bazy danych.
void __fastcall TFMainExtractor::AktualizujLicznikDanych()
{
	LblIlProduktow->Caption = Baza->IloscProduktow();
	LblIlOpini->Caption = Baza->IloscOpini();
	if (Baza->IloscOpini() == 0) BtnDane->Enabled = false;
	else BtnDane->Enabled = true;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie okna, za którego pomoc¹ mo¿na przegl¹daæ dane produktów oraz poszczególne opinie do nich nale¿¹ce.
void __fastcall TFMainExtractor::BtnDaneClick(TObject *Sender)
{
	TFMainPokazDane * z = new TFMainPokazDane(NULL, Baza);
	try
	{
		z->ShowModal();
	}
	catch(...) { if (z != NULL) delete z; z = NULL; throw; }
	if (z != NULL) delete z;
}
//---------------------------------------------------------------------------

void __fastcall TFMainExtractor::Button2Click(TObject *Sender)
{
//	TStringList *test = new TStringList;
//	test->Sorted = true;
//	test->Duplicates = System::Classes::dupIgnore;
//	test->LoadFromFile("ProduktyKat.txt");
//
//	for (int i = 0; i < test->Count; i++)
//	{
//        MDane->Lines->Clear();
//		MDane->Lines->Add(AnsiString(i) + " z " + AnsiString(test->Count));
//		EdKodProduktu->Text = test->Strings[i];
//		BtnETLClick(NULL);
//	}

}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie pierwszego kroku procesu ETL. E - extract
void __fastcall TFMainExtractor::BtnEClick(TObject *Sender)
{
	TStringList *text;
	AnsiString kodDlaMorele, str, plik, plikMorele;
	plik = "Opinie.txt";
	plikMorele = "Opinie2.txt";

	BtnCzyscBaze->Enabled = false;
	BtnETL->Enabled = false;
	BtnE->Enabled = false;
	BtnT->Enabled = false;
	BtnL->Enabled = false;
	BtnDane->Enabled = false;


	MDane->Lines->Clear();
	str = "###############################";
	MDane->Lines->Add(str);
	str = "          Rozpoczêto proces ETL";
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);


	str = "Trwa ekstrakcja textów dla produktu: " + EdKodProduktu->Text;
	MDane->Lines->Add(str);
	if (!Extract(FKodProduktu)) { OdblokujPrzyciski(); return; }
	str = "Pobrano plik dla serwisu Ceneo";
	MDane->Lines->Add(str);

	text = new TStringList;
	try
	{
		text->LoadFromFile(plik);
		DeleteFileW(plik);
		str = "Usuniêto pobrany plik dla serwisu Ceneo";
		MDane->Lines->Add(str);
		FPobranyTekst = Utf8ToAnsi(text->Text); // okazuje siê ¿e AutoIt zapisuje tekst jako UTF-8 w celu nie "wykrzaczania" polskich znaków lepiej siê zabezpieczyæ!

		kodDlaMorele = ParsujDane::ZnajdzTekstOpini(FPobranyTekst, "<MORELE>", "</MORELE>");
		if (kodDlaMorele.Length() > 1)
		{
			Extract(kodDlaMorele, true);
			str = "Pobrano plik dla serwisu Morele";
			MDane->Lines->Add(str);
			text->Clear();
			text->LoadFromFile(plikMorele);
			FPobranyTekst += Utf8ToAnsi(text->Text);
			try
			{
				DeleteFileW(plikMorele);
			}
			catch(...) { }
			str = "Usuniêto pobrany plik dla serwisu Morele";
			MDane->Lines->Add(str);
		}
		else
		{
			str = "Brak odniesienia w Ceneo dla produktu w serwisie Morele";
			MDane->Lines->Add(str);
		}
	}
	catch(...) { if (text != NULL) delete text; text = NULL; throw; }
	if (text != NULL) delete text;
	text = NULL;
	BtnT->Enabled = true;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie drugiego kroku procesu ETL. T - transform
void __fastcall TFMainExtractor::BtnTClick(TObject *Sender)
{
	AnsiString str;
	BtnT->Enabled = false;
	str = "Trwa parsowanie danych";
	MDane->Lines->Add(str);
	if (!Parsuj()) { OdblokujPrzyciski(); return; }
	str = "Parsowanie zakoñczone.";
	MDane->Lines->Add(str);
	BtnL->Enabled = true;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za wywo³anie trzeciego kroku procesu ETL. L - load
void __fastcall TFMainExtractor::BtnLClick(TObject *Sender)
{
	AnsiString str;
	BtnL->Enabled = false;
	str = "Trwa ³adowanie danych do bazy:";
	MDane->Lines->Add(str);
	Laduj();
	str = "Dodano nowy produkt: "; if (Baza->DodanoProdukt) str += "Tak"; else str += "Nie";
	MDane->Lines->Add(str);
	str = "Dodano nowych opini: "; str += AnsiString(Baza->DodanychOpini);
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);
	str = "                     Zakoñczono";
	MDane->Lines->Add(str);
	str = "###############################";
	MDane->Lines->Add(str);

	Produkt->Czysc();
	OdblokujPrzyciski();
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za odblokowanie wszystkich przycisków po zakoñczeniu
/// ca³oœciowego procesu ETL lub po wykonaniu ostatniego kroku procesu ETL
void __fastcall TFMainExtractor::OdblokujPrzyciski()
{
	BtnCzyscBaze->Enabled = true;
	BtnETL->Enabled = true;
	BtnE->Enabled = true;
	BtnT->Enabled = false;
	BtnL->Enabled = false;
	BtnDane->Enabled = true;
}
//---------------------------------------------------------------------------
/// Metoda wywo³uj¹ca okno z podstawowymi informacjami o programie.
void __fastcall TFMainExtractor::BtnInfoClick(TObject *Sender)
{
	AnsiString txt;
	txt = "\tProjekt systemu ETL"; txt += "\n"; txt += "\n";
	txt += "Autor: Tomasz Lisowski"; txt += "\n";
	txt += "Obs³ugiwane systemy: Ceneo.pl Morele.pl"; txt += "\n";
	txt += "Obs³ugiwane kategorie:"; txt += "\n";
	txt += " - \"Komputery\""; txt += "\n";
	txt += " - \"Fotografia\""; txt += "\n";
	txt += " - \"Telefony_i_akcesoria\"";
	ShowMessage(txt);
}
//---------------------------------------------------------------------------


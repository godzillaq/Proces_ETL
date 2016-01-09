//---------------------------------------------------------------------------

#pragma hdrstop
#include <vcl.h>
#include "UParsuj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/// Konstruktor klasy, odpowiada za wywo³anie metod ³adowania danych
ParsujDane::ParsujDane(DaneProdukt *AProdukt, AnsiString AText)
{
	FProdukt = AProdukt;
	Text = AText;
	BladKategorii = false;
	ZaladujDaneProduktu();
	if (BladKategorii) return;
	ZaladujTextyOpini();
	ZaladujDaneOpini();
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za wyci¹gniêcie oraz sparsowanie poszczególnych danych produktu
/// po czym przypisuje te dane do przekazanego obiektu.
void __fastcall ParsujDane::ZaladujDaneProduktu()
{

	AnsiString znacznikDaneProduktu, znacznikMarka, nazwaMarki, znacznikModel, nazwaModel, znacznikKod, kodProduktu,
				znacznikRodzUrz, rodzajUrzadzenia, znacznikKategoria, kategoria, dodUwagi, str;
	int index;
	TStringList *listaKat = new TStringList;
	try
	{
		listaKat->Add("Komputery");
		listaKat->Add("Fotografia");
		listaKat->Add("Telefony_i_akcesoria");
		listaKat->Sort();
		//----
		znacznikDaneProduktu = "keys : [";
		DaneProduktuText = ZnajdzDane(Text, znacznikDaneProduktu, ']');
		UsunZnacznik(DaneProduktuText, "'");
		//----                                                                    `
		znacznikKategoria = "Cat1:  \'";
		kategoria = ZnajdzDane(Text, znacznikKategoria, '\'');
        bool x = listaKat->Find(kategoria, index);

		if (!listaKat->Find(kategoria, index))
		{
			BladKategorii = true;
			ShowMessage("Proces parsowania tekstu nie powiód³ siê - brak parsera dla wybranej kategorii!");
			return;
		}
		//----
		znacznikMarka = "\"Producent: ";
		nazwaMarki = ZnajdzDane(DaneProduktuText, znacznikMarka, '\"');
		//----
		znacznikModel = "\"" + nazwaMarki;
		znacznikModel = znacznikModel.LowerCase();
		DaneProduktuText = DaneProduktuText.LowerCase();
		nazwaModel = ZnajdzDane(DaneProduktuText, znacznikModel, '\"');
		//----
		while (true)
		{
			DaneProduktuText.Delete(DaneProduktuText.Pos(","), 1);
			if (DaneProduktuText.IsEmpty()) break;
			str = ZnajdzDane(DaneProduktuText, '\"', '\"');
			if (str.Pos(":") == 0) continue;
			dodUwagi += str + ";";
		}
		//----
		znacznikKod = "productID: \'";
		kodProduktu = ZnajdzDane(Text, znacznikKod, '\'');
		//----
		znacznikRodzUrz = "catmin: \'";
		rodzajUrzadzenia = ZnajdzDane(Text, znacznikRodzUrz, '\'');
		// ----
		FProdukt->DodajDaneProduktu(nazwaMarki, nazwaModel, kodProduktu.ToInt(), rodzajUrzadzenia, dodUwagi);
	}
	catch(...) { if (listaKat != NULL) delete listaKat; listaKat = NULL; throw; }
	if (listaKat != NULL) delete listaKat;
	listaKat = NULL;
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za znalezienie danych w przekazanym tekœcie, szukany tekst musi znajdowaæ siê pomiêdzy
/// pocz¹tkowym znacznikiem a znakiem wystêpuj¹cym na koñcu tekstu, w przypadku nie znalezienie znacznika pocz¹tkowego
/// metoda zwraca pusty tekst.
AnsiString __fastcall ParsujDane::ZnajdzDane(AnsiString &AText, AnsiString AZnacznikPocz, char AZnakKonca)
{
	int pozycjaZnacznik, start, koniec;
	AnsiString tekst, str = "";
	pozycjaZnacznik = AText.Pos(AZnacznikPocz);
	start = pozycjaZnacznik;
	if (pozycjaZnacznik == 0) return "";
	pozycjaZnacznik = pozycjaZnacznik + AZnacznikPocz.Length();

	while(AText[pozycjaZnacznik] != AZnakKonca)
	{
		str += AText[pozycjaZnacznik];
		pozycjaZnacznik++;
		if ((AText[pozycjaZnacznik] == ']' && AText[pozycjaZnacznik - 1] != '\"') ||
		(AText[pozycjaZnacznik] == '\"' && AText[pozycjaZnacznik - 1] == '\\'))
		{
            str += AText[pozycjaZnacznik];
			pozycjaZnacznik++;
		}
	}
	koniec = pozycjaZnacznik;
	AText.Delete(start,  koniec + 1 - start);
	str.TrimLeft(); str.TrimRight();
	return str;
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za wstêpne wyci¹gniêcie danych poszczególnych opini oraz za³adowanie ich do obiektów,
/// nastêpnie dane te przypisywane s¹ do wektora opini danego produktu, metoda ta odpowiada równie¿
// za wstêpne usuniêcie zbêdnych znaków niepotrzebnych w dalszym parsowaniu tekstów.
void __fastcall ParsujDane::ZaladujTextyOpini()
{
	AnsiString znacznikStart, znacznikKoniec,
			znacznikStartMorele, znacznikKoniecMorele, str;
	int start, koniec, ileMorele;
	Opinia *opinia;
	znacznikStart = "<START>";
	znacznikKoniec = "<KONIEC>";
	znacznikStartMorele = "<STARTMORELE>";
	znacznikKoniecMorele = "<KONIECMORELE>";

	while (Text.Pos(znacznikStart) != 0)
	{
		start = Text.Pos(znacznikStart);
		koniec = Text.Pos(znacznikKoniec) + znacznikKoniec.Length() - Text.Pos(znacznikStart);
		str = Text.SubString(start, koniec);
		UsunZnacznik(str, '\n');
		UsunZnacznik(str, '\r');
		UsunZnacznik(str, '\t');
		opinia = new Opinia(str);
		FProdukt->DodajOpinie(opinia);
		Text.Delete(start, koniec);
	}

	while (Text.Pos(znacznikStartMorele) != 0)
	{
		start = Text.Pos(znacznikStartMorele);
		koniec = Text.Pos(znacznikKoniecMorele) + znacznikKoniecMorele.Length() - Text.Pos(znacznikStartMorele);
		str = Text.SubString(start, koniec);
		UsunZnacznik(str, '\n');
		UsunZnacznik(str, '\r');
		UsunZnacznik(str, '\t');
		opinia = new Opinia(str);
		opinia->Morele = true;
		FProdukt->DodajOpinie(opinia);
		Text.Delete(start, koniec);
		ileMorele++;
	}
}
//---------------------------------------------------------------------------
/// Metoda odpowiada za parsowanie poszczególnych danych wczeœniej wyci¹gnietych opini (danych wstêpnie sparsowanych),
/// metoda posiada wenw¹trz okreœlone znaczniki pocz¹tkowe oraz koñcowe, pomiêdzy którymi znajduj¹ siê wymagane teksty.
/// Metoda ta odpowiada równie¿ za wywo³anie w trakcie parsowania danych metod odpowiedzialnych za czyszczenie
/// niepotrzebnych znaczników z tekstów.
void __fastcall ParsujDane::ZaladujDaneOpini()
{
	AnsiString str, ile, zIlu;
	std::vector<Opinia*>::iterator itOpinie;

	for (itOpinie = FProdukt->Opinie.begin(); itOpinie != FProdukt->Opinie.end(); itOpinie++)
	{
		if (!(*itOpinie)->Morele)
		{
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<div class=\"product-reviewer\">", "</div>");
			if (str.IsEmpty()) str = "Anonim";
			WyczyscZnaczniki(str);
			(*itOpinie)->Autor = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<p class=\"product-review-body\">", "</p>");
			WyczyscZnaczniki(str);
			(*itOpinie)->Opinia = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span class=\"cons\">Wady</span>", "</span>");
			WyczyscZnaczniki(str);
			DostosujWadyIZalety(str);
			if (str.Pos("<ENDL>") == 1 && str.Length() == 6) str = "";
			(*itOpinie)->Wady = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span class=\"pros\">Zalety</span>", "</span>");
			WyczyscZnaczniki(str);
			DostosujWadyIZalety(str);
            if (str.Pos("<ENDL>") == 1 && str.Length() == 6) str = "";
			(*itOpinie)->Zalety = str;
			(*itOpinie)->LGwiazdek = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span class=\"review-score-count\">", "</span>");
			(*itOpinie)->Data = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<time datetime=\"", "\">");
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<em class=\"product-recommended\">", "</em>");
			if (str.IsEmpty()) str = "Nie polecam";
			(*itOpinie)->PolecNPolec = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span id=\"votes-yes-percent-", "\">", false);
			(*itOpinie)->PrzydatnaOpiniaPr = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span id=\"votes-yes-percent-" + str + "\">", "</span>", false);
			ile = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span id=\"votes-yes-" + str + "\">", "</span>", false);
			zIlu = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<span id=\"votes-" + str + "\">", "</span>", false);
			(*itOpinie)->IleOsOcPrzydatnosc = ile + " z " + zIlu;
		}
		else
		{
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"author\">Autor: <strong>", "</strong></li><li class=\"rate\">");
			if (str.IsEmpty()) str = "Anonim";
			WyczyscZnaczniki(str);
		   	(*itOpinie)->Autor = str;// + "\n *Morele*";
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"rcomment\">", "</li>");
			WyczyscZnaczniki(str);
			(*itOpinie)->Opinia = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"bad\"><strong>Minusy:</strong>", "</li>");
			WyczyscZnaczniki(str);
			//	DostosujWadyIZalety(str);
			if (str.Pos("<ENDL>") == 1 && str.Length() == 6) str = "";
			(*itOpinie)->Wady = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"good\"><strong>Plusy:</strong>", "</li>");
			WyczyscZnaczniki(str);
		   //	DostosujWadyIZalety(str);
		   	if (str.Pos("<ENDL>") == 1 && str.Length() == 6) str = "";
			(*itOpinie)->Zalety = str;
			str = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<img src=\"\/img\/ratestar_", ".gif\"");
			(*itOpinie)->LGwiazdek = AnsiString((str.ToInt())/2) + "/5";
			(*itOpinie)->Data = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"date\">", "</li>");
			(*itOpinie)->PolecNPolec = "Polecenie: Morele - b.d.";
			(*itOpinie)->PrzydatnaOpiniaPr = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "(<strong>", "</strong>");
			ile = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "(<strong>", "</strong>");
			zIlu = ZnajdzTekstOpini((*itOpinie)->TextOpinia, "<li class=\"rate-count\">Iloœæ ocen: <strong>", "</strong>");
			(*itOpinie)->IleOsOcPrzydatnosc = "(" + ile + "%) z " + zIlu;
		}
	}
}
//---------------------------------------------------------------------------
/// Meotoda odpowiada za w³aœciwe wyszukiwanie danych opini, metoda przyjmuje znaczniki pocz¹tkowe oraz koñcowe,
/// pomiêdzy którymi znajduj¹ siê po¿¹dane teksty.
AnsiString __fastcall ParsujDane::ZnajdzTekstOpini(AnsiString &ATextOpini, AnsiString AZnacznikPocz, AnsiString AZnacznikKoniec, bool ATnij)
{
	AnsiString txt;
	int pozycjaZnacznik, start, koniec;
	pozycjaZnacznik = ATextOpini.Pos(AZnacznikPocz);
	if (pozycjaZnacznik == 0) return "";
	while (true)
	{
		txt += ATextOpini[pozycjaZnacznik];
		if (ATnij) { if (txt.Pos(AZnacznikPocz) > 0) { txt = txt.Delete(1, AZnacznikPocz.Length()); } }
		if (txt.Pos(AZnacznikKoniec) > 0) break;
		pozycjaZnacznik++;
	}
	if (!ATnij)
	{
		start = AZnacznikPocz.Length() + 1;
		koniec = txt.Length() - AZnacznikPocz.Length() - AZnacznikKoniec.Length();
	}
	else
	{
		start = 1;
		koniec = txt.Length() - AZnacznikKoniec.Length();
	}
	txt = txt.SubString(start, koniec);
	txt.TrimLeft(); txt.TrimRight();
	return txt;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za okreœlenie znaczników do usuniêcia oraz wywo³anie metody przekazuj¹c jej jako argument
/// usuwane znaczniki
void __fastcall ParsujDane::WyczyscZnaczniki(AnsiString &AText)
{
	AnsiString znacznik;

	znacznik = "<br>";
	UsunZnacznik(AText, znacznik);
	znacznik = "<br/>";
	UsunZnacznik(AText, znacznik, true);
	znacznik = "<ul>";
	UsunZnacznik(AText, znacznik);
	znacznik = "</ul>";
	UsunZnacznik(AText, znacznik);
	znacznik = "<li>";
	UsunZnacznik(AText, znacznik);
	znacznik = "</li>";
	UsunZnacznik(AText, znacznik, true);
	UsunZnacznik(AText, ' ');
	UsunZnacznik(AText, "'");
	znacznik = "<p>";
	UsunZnacznik(AText, znacznik);
	znacznik = "</p>";
	UsunZnacznik(AText, znacznik, true);
	UsunZnacznik(AText, ";");
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za usunieciê przekazanych znaczników z przekazanego tekstu,
/// metoda umo¿liwia umieszczenie znacznika konca lini w zamian za przyjmowany znacznik
void __fastcall ParsujDane::UsunZnacznik(AnsiString &AText, AnsiString AZnacznik, bool AWstawENDL)
{
	int pozycjaZnacznik, i;
	i = 0;
	while (true)
	{
		pozycjaZnacznik = AText.Pos(AZnacznik);
		if (AZnacznik == ' ')
		{
			if (AText.Pos(' ') > 1) break;
		}
		if (pozycjaZnacznik > 0) AText.Delete(pozycjaZnacznik, AZnacznik.Length());
		if (pozycjaZnacznik > 0 && AWstawENDL) AText.Insert("<ENDL>",pozycjaZnacznik);
		if (pozycjaZnacznik == 0) break;
	}
	AText.TrimLeft(); AText.TrimRight();
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za dostosowanie wad i zalet do zapisu do bazy danych
void __fastcall ParsujDane::DostosujWadyIZalety(AnsiString &AText)
{
	int pozycjaZnacznik;
	AnsiString str, text, znakKonca;
	if (AText.IsEmpty()) return;
	znakKonca = "<ENDL>";

	while (true)
	{
		pozycjaZnacznik = AText.Pos(znakKonca);

		if (pozycjaZnacznik > 0) AText.Delete(pozycjaZnacznik, znakKonca.Length());
		if (pozycjaZnacznik == 0) break;
		text = AText.SubString(1, pozycjaZnacznik - 1);
		UsunZnacznik(text, ' ');
		str += text + "<ENDL>";
		AText.Delete(1, pozycjaZnacznik);
	}
	AText = str;
}
//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za dostosowanie znaków specjalnych w tekœcie (apostrofy itp.),
/// poprzez dodanie dodanie "\"
void __fastcall ParsujDane::DostosujZnakiSpecjalne(AnsiString &AText)
{
	AnsiString str;
	int pozycjaZnacznik = 0;

	while(pozycjaZnacznik != AText.Length())
	{
		str = AText[pozycjaZnacznik];
		if (str == "\'" || str == "\"") AText.Insert("\\", pozycjaZnacznik - 1);
		pozycjaZnacznik++;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------











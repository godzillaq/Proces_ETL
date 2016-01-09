//---------------------------------------------------------------------------

#ifndef FMnPokazDaneH
#define FMnPokazDaneH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "cdiroutl.h"
#include "cgauges.h"
#include "pies.h"
#include "DMnBaza.h"
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>

//---------------------------------------------------------------------------
/// Klasa odpowiedzialna za utworzenie okna prezentuj¹cego dane pochodz¹ce z bazy danych, oraz za prezentacjê
/// poszczególnych danych.
class TFMainPokazDane : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *LblKodProduktu;
	TLabel *LblMarka;
	TLabel *LblModel;
	TLabel *LblRodzUrz;
	TLabel *LblDodUwagi;
	TLabel *Label6;
	TLabel *LblIlOpini;
	TComboBox *Cbx;
	TSaveDialog *SDialog;
	TButton *BtnZapisz;
	TLabel *Label7;
	TEdit *EdIdOpini;
	TLabel *Label8;
	TButton *BtnZapisTxt;
	TSaveDialog *SDialog2;
	TLabel *Label9;
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall CbxClick(TObject *Sender);
	void __fastcall BtnZapiszClick(TObject *Sender);
	void __fastcall BtnZapisTxtClick(TObject *Sender);
private:	// User declarations
	/// WskaŸnik do przekazanego obiektu odpowiedzialnego za po³¹czenie oraz operacje na bazie danych.
	TDMBaza *FBaza;
	/// Zmiena przetrzymuj¹ca Id aktualnie wybranego z listy produktu
	int FIdProdukt;
	void __fastcall ZaladujDaneProduktu();
	AnsiString __fastcall ZaladujGridDanymi(bool ALadujDoCsv = false);
	void __fastcall ZmienZnacznikENDL(AnsiString &AText);
	/// Zmienna odpowiedzialna za blokowanie odœwie¿ania grida danych
	bool FBlokujOdswiezanie;
public:		// User declarations
	__fastcall TFMainPokazDane(TComponent* Owner, TDMBaza *ABaza);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMainPokazDane *FMainPokazDane;
//---------------------------------------------------------------------------
#endif

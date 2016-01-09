//---------------------------------------------------------------------------

#ifndef FMnExTractorH
#define FMnExTractorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "UProdukty.h"
#include "DMnBaza.h"
#include <IWBaseControl.hpp>
#include <IWBaseHTMLControl.hpp>
#include <IWCompGrids.hpp>
#include <IWControl.hpp>
#include <IWDBGrids.hpp>
#include <IWVCLBaseControl.hpp>
#include "Excel_2K_SRVR.h"
#include <Vcl.OleServer.hpp>
//---------------------------------------------------------------------------
/// Klasa odpowiedzialna za utworzenie g��wnego okna programu,
/// odpowiada r�wnie� za wywo�ywanie poszczeg�lncyh funkcjonalno�ci programu.
class TFMainExtractor : public TForm
{
__published:	// IDE-managed Components
	TButton *BtnETL;
	TEdit *EdKodProduktu;
	TButton *BtnCzyscBaze;
	TGroupBox *GbBazaDane;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *LblIlProduktow;
	TLabel *LblIlOpini;
	TMemo *MDane;
	TButton *BtnDane;
	TButton *Button2;
	TButton *BtnE;
	TButton *BtnT;
	TButton *BtnL;
	TLabel *Label3;
	TButton *BtnInfo;
	void __fastcall BtnETLClick(TObject *Sender);
	void __fastcall BtnCzyscBazeClick(TObject *Sender);
	void __fastcall BtnDaneClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall BtnEClick(TObject *Sender);
	void __fastcall BtnTClick(TObject *Sender);
	void __fastcall BtnLClick(TObject *Sender);
	void __fastcall BtnInfoClick(TObject *Sender);
private:	// User declarations
	/// warto�� tekstowa kodu produktu
	AnsiString FKodProduktu;
	/// tekst uzyskany w procesie ekstrakcji tekst�w Ceneo + Morele
	AnsiString FPobranyTekst;
	bool __fastcall Extract(AnsiString AKodProduktu, bool AMorele = false);
	bool __fastcall Parsuj();
	bool __fastcall Laduj();
	void __fastcall AktualizujLicznikDanych();
	void __fastcall OdblokujPrzyciski();

public:		// User declarations
	__fastcall TFMainExtractor(TComponent* Owner);
	__fastcall ~TFMainExtractor();
	/// wska�nik przetrzymuj�cy dane produktu z opiniami
	DaneProdukt *Produkt;
	/// wska�nik odpowiedzialny za po��czenie z baz� danych, �adowanie i odczyt danych itp.
	TDMBaza *Baza;

};
//---------------------------------------------------------------------------
extern PACKAGE TFMainExtractor *FMainExtractor;
//---------------------------------------------------------------------------
#endif

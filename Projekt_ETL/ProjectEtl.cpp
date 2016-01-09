//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("DMnBaza.cpp", DMBaza); /* TDataModule: File Type */
USEFORM("FMnExTractor.cpp", FMainExtractor);
USEFORM("FMnPokazDane.cpp", FMainPokazDane);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFMainExtractor), &FMainExtractor);
		Application->CreateForm(__classid(TDMBaza), &DMBaza);
		Application->CreateForm(__classid(TFMainPokazDane), &FMainPokazDane);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

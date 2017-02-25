//---------------------------------------------------------------------------

#include <fmx.h>
#include <System.Inifiles.hpp>
#include <System.IOUtils.hpp>
#include <memory>

//#include <Androidapi.JNI.JavaTypes.hpp>
//#include <Androidapi.JNI.GraphicsContentViewText.hpp>
//#include <Androidapi.Helpers.hpp>

#pragma hdrstop
#include "FormConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

String TfrmConfig::FAppNASAKey = "";

void __fastcall TfrmConfig::btnLinkClick(TObject *Sender)
{
   #ifdef _Windows
//	 ShellExecuteA(0, "open", "https://api.nasa.gov/index.html#getting-started", NULL, NULL, SW_SHOWNORMAL);
	ShellExecuteW(0, _T("open"), _T("https://api.nasa.gov/index.html#getting-started"), NULL, NULL, SW_SHOWNORMAL);
   #endif
   #ifndef _Windows

//	Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent = TJIntent::Create();
//	intent->setType(StringToJString("https://api.nasa.gov/index.html#getting-started"));
//	intent->setAction(TJIntent::JavaClass->ACTION_VIEW);
//	intent->putExtra(TJIntent::JavaClass->EXTRA_TEXT, StringToJString(text));
//	if (MainActivity()->getPackageManager()->queryIntentActivities(intent, TJPackageManager::JavaClass->MATCH_DEFAULT_ONLY)->size() > 0) {
//		MainActivity()->startActivity(intent);
//	} else {
//		ShowMessage("Receiver not found");
//	}


//	system("open https://api.nasa.gov/index.html#getting-started");
   #endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::Label1Click(TObject *Sender)
{
	btnLinkClick(Sender);
}
//---------------------------------------------------------------------------

String TfrmConfig::LoadAppNASAKey()
{
	 if (FAppNASAKey == "") {
		String libPath(System::Ioutils::TPath::GetDocumentsPath()); // GetLibraryPath()
		libPath += "\\spaceDaily.conf"; // make it const
		if (TFile::Exists(libPath)) {
			std::unique_ptr<System::Inifiles::TIniFile> ini(new TIniFile(libPath));
			FAppNASAKey = ini->ReadString("spaceDaily", "appKey", "" );
		};
	 };
     return FAppNASAKey;
}

void __fastcall TfrmConfig::btnOkClick(TObject *Sender)
{
	if (edtAPIKey->Text != "") {
		String libPath(System::Ioutils::TPath::GetDocumentsPath());
		libPath += "\\spaceDaily.conf"; // make it const
		std::unique_ptr<System::Inifiles::TIniFile> ini(new TIniFile(libPath));
		ini->WriteString( "spaceDaily", "appKey", edtAPIKey->Text );
		FAppNASAKey = "";
		LoadAppNASAKey();
		Hide();

	} else {
		// toast & not hide;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btnCancelClick(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::FormCreate(TObject *Sender)
{
	edtAPIKey->Text = TfrmConfig::AppNASAKey;
}
//---------------------------------------------------------------------------


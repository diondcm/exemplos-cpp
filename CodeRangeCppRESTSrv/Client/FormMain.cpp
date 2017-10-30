//---------------------------------------------------------------------------

#include <fmx.h>
#include <memory>
#pragma hdrstop

#include "FormMain.h"
#include "ClientModuleUnit.h"

#include <FireDAC.Stan.StorageXML.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>

#include <FMX.Platform.hpp>
#include <FMX.DialogService.Async.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMainClient *frmMainClient;
//---------------------------------------------------------------------------
__fastcall TfrmMainClient::TfrmMainClient(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainClient::buttonUploadClick(TObject *Sender)
{
	TImage* img(NULL);
	if(radioButLogo1->IsChecked)
	   img = imageLogo1;
	if(radioButLogo2->IsChecked)
	   img = imageLogo2;
	if(radioButLogo3->IsChecked)
	   img = imageLogo3;

	if(img != NULL) {
		TMemoryStream* lStm = new TMemoryStream();
		img->Bitmap->SaveToStream(lStm);
		lStm->Position = 0;
		System::UnicodeString str(ClientModule->ServerRESTClient->SaveImage(lStm));
		Caption = str;
	} else {
		TDialogServiceAsync::ShowMessage("Please select an image to upload.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainClient::buttonLoadCoutryListClick(TObject *Sender)
{
	 //std::auto_ptr<TMemoryStream> lStm(new TMemoryStream());
	 TFDMemTable* lmem = new TFDMemTable(this);
	 TMemoryStream* lStm2(dynamic_cast<TMemoryStream*>(ClientModule->ServerRESTClient->GetCountryListStm()));
	 lStm2->Position = 0;
	 lmem->LoadFromStream(lStm2, sfJSON);
	 BindSourceDB1->DataSet = lmem;
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainClient::TakePhotoFromLibraryAction1DidFinishTaking(TBitmap *Image)

{
    imageLogo1->MultiResBitmap->Assign(Image);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#include <fmx.h>
#include <memory>
#pragma hdrstop

#include "FormMain.h"
#include "FormCompleteList.h"
#include "FormConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner), FLastDistance(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actShowListExecute(TObject *Sender)
{
	if (TfrmConfig::AppNASAKey != "") {
		frmCompleteList->NasaApiUrl = "https://api.nasa.gov/planetary/apod?api_key=" + TfrmConfig::AppNASAKey;
		frmCompleteList->Show();
	} else {
		ShowMessage("Cadastre a sua API Key primeiramente.");
        //toast
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrShowInitialTimer(TObject *Sender)
{
	tmrShowInitial->Enabled = false;
	actLoadImage->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actLoadImageExecute(TObject *Sender)
{
	String lImgURL("");
	if (TfrmConfig::AppNASAKey != "") {
		RESTClient1->BaseURL = "https://api.nasa.gov/planetary/apod?api_key=" + TfrmConfig::AppNASAKey;

		try {
			RESTRequest1->Execute();
		} catch(Exception& e) {
			// toast e.message
			return;
		};

		if ((!fdmImageDay->IsEmpty()) && (fdmImageDay->FieldByName("url")->AsString != "")) {
		  lImgURL = fdmImageDay->FieldByName("url")->AsString;
		}

	} else  {
	   // just for demo;
	   lImgURL = "http://apod.nasa.gov/apod/image/1702/Calabash_HubbleSchmidt_960.jpg";
	   lblImageName->Text = "Go to configurations and enable the daily image!";
	}

	if (lImgURL != "") {
		std::unique_ptr<System::Classes::TMemoryStream> sm(new System::Classes::TMemoryStream());
		NetHTTPClient1->Get(lImgURL, sm.get());
		imgSpace->Bitmap->LoadFromStream(sm.get());
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actConfigExecute(TObject *Sender)
{
	frmConfig->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled)
{
	if (EventInfo.GestureID == static_cast<short>(igiZoom)) {
		IControl *LObj = this->ObjectAtPoint(ClientToScreen(EventInfo.Location));
		if (static_cast<TImage*>((TImage*)LObj)) {
			if (!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin) &&
				!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
				// zoom the image
				TImage * LImage = dynamic_cast<TImage*>(LObj->GetObject());
				TPointF LImageCenter = LImage->Position->Point + PointF(LImage->Width / 2,
					LImage->Height / 2);
				LImage->Width = LImage->Width + (EventInfo.Distance - FLastDistance);
				LImage->Height = LImage->Height + (EventInfo.Distance - FLastDistance);
				LImage->Position->X = LImageCenter.X - LImage->Width / 2;
				LImage->Position->Y = LImageCenter.Y - LImage->Height / 2;
			}
			FLastDistance = EventInfo.Distance;
		}
    }
}
//---------------------------------------------------------------------------


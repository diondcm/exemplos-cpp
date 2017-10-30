 
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMainServer.h"
#include <Datasnap.DSSession.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMainServer *frmMainServer;
//---------------------------------------------------------------------------
__fastcall TfrmMainServer::TfrmMainServer(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::ButtonStartClick(TObject *Sender)
{
  StartServer();
}
//---------------------------------------------------------------------------
void TerminateThreads(void)
{
  if (TDSSessionManager::Instance != NULL)
  {
    TDSSessionManager::Instance->TerminateAllSessions();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::ButtonStopClick(TObject *Sender)
{
  TerminateThreads();
  FServer->Active = false;
  FServer->Bindings->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::ButtonOpenBrowserClick(TObject *Sender)
{
  StartServer();
  String url;
  url.sprintf(L"http://localhost:%s", EditPort->Text.c_str());
  ShellExecuteW(0,
        NULL,
        url.c_str(),
        NULL, NULL, SW_SHOWNOACTIVATE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
  ButtonStart->Enabled = !FServer->Active;
  ButtonStop->Enabled = FServer->Active;
  EditPort->Enabled = !FServer->Active;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::StartServer()
{
  if (!FServer->Active)
  {
    FServer->Bindings->Clear();
    FServer->DefaultPort = StrToInt(EditPort->Text);
    FServer->Active = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainServer::FormCreate(TObject *Sender)
{
  FServer = new TIdHTTPWebBrokerBridge(this);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainServer::FormShow(TObject *Sender)
{
    StartServer();
}
//---------------------------------------------------------------------------

 
//---------------------------------------------------------------------------

#ifndef FormMainServerH
#define FormMainServerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.AppEvnts.hpp>
#include <IdHTTPWebBrokerBridge.hpp>
//---------------------------------------------------------------------------
class TfrmMainServer : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonOpenBrowser;
	TApplicationEvents *ApplicationEvents1;
	TEdit *EditPort;
	TButton *ButtonStop;
	TButton *ButtonStart;
	TLabel *Label1;
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall ButtonOpenBrowserClick(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	TIdHTTPWebBrokerBridge *FServer;
    
	void __fastcall StartServer();
public:		// User declarations
	__fastcall TfrmMainServer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMainServer *frmMainServer;
//---------------------------------------------------------------------------
#endif



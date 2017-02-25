//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.ExtCtrls.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <IPPeerClient.hpp>
#include <REST.Client.hpp>
#include <REST.Response.Adapter.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Rtti.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TLayout *lytImage;
	TToolBar *ToolBar1;
	TButton *btnList;
	TActionList *ActionList1;
	TAction *actShowList;
	TStyleBook *StyleBook1;
	TRESTRequest *RESTRequest1;
	TRESTResponse *RESTResponse1;
	TRESTResponseDataSetAdapter *RESTResponseDataSetAdapter1;
	TRESTClient *RESTClient1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TFDMemTable *fdmImageDay;
	TNetHTTPClient *NetHTTPClient1;
	TTimer *tmrShowInitial;
	TAction *actLoadImage;
	TButton *btnConfig;
	TAction *actConfig;
	TImage *imgSpace;
	TLabel *lblDate;
	TLabel *lblImageName;
	TLinkPropertyToField *LinkPropertyToFieldText3;
	TLinkPropertyToField *LinkPropertyToFieldText4;
	void __fastcall actShowListExecute(TObject *Sender);
	void __fastcall tmrShowInitialTimer(TObject *Sender);
	void __fastcall actLoadImageExecute(TObject *Sender);
	void __fastcall actConfigExecute(TObject *Sender);
	void __fastcall FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled);
private:	// User declarations
    int FLastDistance;
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

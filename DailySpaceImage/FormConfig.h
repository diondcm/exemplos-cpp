//---------------------------------------------------------------------------

#ifndef FormConfigH
#define FormConfigH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmConfig : public TForm
{
__published:	// IDE-managed Components
	TGridPanelLayout *GridPanelLayout1;
	TEdit *edtAPIKey;
	TButton *btnOk;
	TButton *btnCancel;
	TButton *btnLink;
	void __fastcall btnLinkClick(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	static String FAppNASAKey;
	static String LoadAppNASAKey();
public:		// User declarations
	__fastcall TfrmConfig(TComponent* Owner);
	__property String AppNASAKey = {read=LoadAppNASAKey, write=FAppNASAKey };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
#endif

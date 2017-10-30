//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <Data.DB.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FireDAC.Stan.StorageBin.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.MediaLibrary.Actions.hpp>
#include <FMX.StdActns.hpp>
#include <System.Actions.hpp>
#include <FireDAC.Stan.StorageJSON.hpp>

//---------------------------------------------------------------------------
class TfrmMainClient : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB1;
	TFDStanStorageBinLink *FDStanStorageBinLink1;
	TLayout *Layout1;
	TImage *imageLogo1;
	TImage *imageLogo2;
	TImage *imageLogo3;
	TRadioButton *radioButLogo1;
	TRadioButton *radioButLogo2;
	TRadioButton *radioButLogo3;
	TLayout *Layout2;
	TButton *buttonUpload;
	TLayout *Layout3;
	TButton *buttonLoadCoutryList;
	TButton *buttonFromGalery;
	TActionList *ActionList;
	TTakePhotoFromLibraryAction *TakePhotoFromLibraryAction1;
	TFDStanStorageJSONLink *FDStanStorageJSONLink1;
	void __fastcall buttonUploadClick(TObject *Sender);
	void __fastcall buttonLoadCoutryListClick(TObject *Sender);
	void __fastcall TakePhotoFromLibraryAction1DidFinishTaking(TBitmap *Image);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMainClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMainClient *frmMainClient;
//---------------------------------------------------------------------------
#endif

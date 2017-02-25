//---------------------------------------------------------------------------

// This software is Copyright (c) 2016 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef FormCompleteListH
#define FormCompleteListH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "CustomAdapterU.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <FMX.Calendar.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
//---------------------------------------------------------------------------
class TfrmCompleteList : public TForm
{
__published:	// IDE-managed Components
	TLayout *lytImageListView;
	TTimer *tmrShowImages;
	TToolBar *ToolBar1;
	TButton *btnList;
	TButton *btnIncDate;
	TLabel *lblMonth;
	TLabel *lblSelectedMonth;
	TButton *Button1;
	TButton *btnDecDate;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tmrShowImagesTimer(TObject *Sender);
	void __fastcall btnApplyClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnListClick(TObject *Sender);
	void __fastcall btnDecDateClick(TObject *Sender);
	void __fastcall btnIncDateClick(TObject *Sender);
private:	// User declarations
	TListViewBase * FListView;
	TCustomAdapter * FAdapter;
	String FNasaApiUrl;
    TDateTime FBaseDate;

	int FTotal;
	TStringList * FStrings;
	void __fastcall AddItems(const int HowMany);
	void __fastcall PullRefresh(TObject * Sender);
	void __fastcall ButtonClicked(TObject * Sender);
	void __fastcall RefreshDate();
public:		// User declarations
	__fastcall TfrmCompleteList(TComponent* Owner);

	__property String NasaApiUrl ={read=FNasaApiUrl, write=FNasaApiUrl};
	void RefreshView();
};


//---------------------------------------------------------------------------
extern PACKAGE TfrmCompleteList *frmCompleteList;
//---------------------------------------------------------------------------
#endif

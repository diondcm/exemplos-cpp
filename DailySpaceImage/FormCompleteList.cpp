//---------------------------------------------------------------------------
// Copyright (c) 2016 Embarcadero Technologies, Inc. All rights reserved.  
//
// This software is the copyrighted property of Embarcadero Technologies, Inc. 
// ("Embarcadero") and its licensors. You may only use this software if you 
// are an authorized licensee of Delphi, C++Builder or RAD Studio 
// (the "Embarcadero Products").  This software is subject to Embarcadero's 
// standard software license and support agreement that accompanied your 
// purchase of the Embarcadero Products and is considered a Redistributable, 
// as such term is defined thereunder. Your use of this software constitutes 
// your acknowledgement of your agreement to the foregoing software license 
// and support agreement. 
//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FormCompleteList.h"
#include "System.DateUtils.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCompleteList *frmCompleteList;

//---------------------------------------------------------------------------
__fastcall TfrmCompleteList::TfrmCompleteList(TComponent* Owner)
	: TForm(Owner)
{
	FTotal = 0;
	FStrings = new TStringList();
}

void __fastcall TfrmCompleteList::AddItems(const int HowMany)
{

	FAdapter->NasaApiUrl = FNasaApiUrl;
	FAdapter->BaseDate = StartOfTheMonth(FBaseDate);
	FAdapter->Clear();
	for(int i = 0; i < HowMany; i++) {
		FTotal++;
		FStrings->Add("");
	}
	FTotal++;
}
void __fastcall TfrmCompleteList::ButtonClicked(TObject * Sender)
{
//	TListItemTextButton *button = static_cast<TListItemTextButton*>(Sender);
//	TListItem *item = static_cast<TListItem*>(button->TagObject);
//	if(!item)
//		return;
//	TListItemText *itemText = static_cast<TListItemText*>(item->View->FindDrawable("title"));
//	if(!itemText)
//		return;
//	ShowMessage(UnicodeString().sprintf(L"%s says Hi!", itemText->Text.c_str()));
}
//---------------------------------------------------------------------------
void __fastcall TfrmCompleteList::FormCreate(TObject *Sender)
{
	FListView = new TPresentedListView(this);
	FListView->ControlType = TControlType::Platform;
	FStrings = new TStringList();
	FAdapter = new TCustomAdapter(FListView, FStrings);
//	FAdapter->OnButtonClicked = &ButtonClicked;
	FListView->Adapter = FAdapter;
	FListView->Parent = lytImageListView;
	FListView->Align = TAlignLayout::Client;
	FListView->PullToRefresh = true;
	FListView->PullRefreshWait = true;
	FBaseDate = StartOfTheMonth((IncMonth(Now(), -1)));
	RefreshDate();
	FListView->OnPullRefresh = &PullRefresh;
}

void __fastcall TfrmCompleteList::RefreshDate()
{
	lblSelectedMonth->Text = String().sprintf(L"%d/%d", YearOf(FBaseDate), MonthOf(FBaseDate));
}

//---------------------------------------------------------------------------
void __fastcall TfrmCompleteList::PullRefresh(TObject *Sender)
{
	RefreshView();
}

void __fastcall TfrmCompleteList::FormDestroy(TObject *Sender)
{
	FAdapter = NULL;
	delete FListView;
	delete FStrings;
}
//---------------------------------------------------------------------------

void TfrmCompleteList::RefreshView()
{
	int days = DaysInAMonth(YearOf(Now()), MonthOf(Now() - 30));
	AddItems(days);
}

void __fastcall TfrmCompleteList::tmrShowImagesTimer(TObject *Sender)
{
	tmrShowImages->Enabled = false;
	RefreshView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompleteList::btnApplyClick(TObject *Sender)
{
	RefreshView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompleteList::FormShow(TObject *Sender)
{
	tmrShowImages->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompleteList::btnListClick(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompleteList::btnDecDateClick(TObject *Sender)
{
	FBaseDate = IncMonth(FBaseDate, -1);
	RefreshDate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCompleteList::btnIncDateClick(TObject *Sender)
{
	FBaseDate = IncMonth(FBaseDate, 1);
	if (FBaseDate > Now()) {
	   FBaseDate = Now();
	}
	RefreshDate();

}
//---------------------------------------------------------------------------


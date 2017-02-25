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
#pragma hdrstop


#include "CustomAdapterU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TCustomAdapter::TCustomAdapter(Fmx::Listview::TListViewBase* const Parent,
	const System::Classes::TStringList *AStrings)
{
	FStrings = const_cast<TStringList*>(AStrings);
	FParent = Parent;
	FUriRegex = new TRegEx("\\[(http://.*)\\]", TRegExOptions() << roNotEmpty);
	FNameRegex = new TRegEx("\\[([A-Za-z]+)\\]", TRegExOptions() << roNotEmpty);
	FIdRegex = new TRegEx("\\[([0-9]+)\\]", TRegExOptions() << roNotEmpty);
	CreateThreads();
	FStrings->OnChanging = StringListChanging;
	FStrings->OnChange = StringListChange;

	FCS = new TCriticalSection;
	FSem = new TSemaphore(NULL, 0, 1000, "", false);
	FExitRequested = false;
    FIndex = 0;
}

__fastcall TCustomAdapter::~TCustomAdapter(void)
{
	DestroyThreads();
	delete FRegexMonitor;
}

void __fastcall TCustomAdapter::Clear()
{
	ClearIndex();
	if (FIndex == 0) {
		FStrings->Clear();
		FBitmaps.clear();
		FParent->RebuildList();
	}
}

void __fastcall TCustomAdapter::ImagesLoaded()
{
	std::map<int,TBitmapString*>::iterator it;
	for(it = FBitmaps.begin(); it != FBitmaps.end(); it++){
		if(FStrings->Count > 0) {
			TListItem * item = ((TListItem*)(FStrings->Objects[it->first]));
			TListItemImage * BitmapDrawable = static_cast<TListItemImage*>(item->View->FindDrawable("bitmap"));
			if((BitmapDrawable != NULL) && (BitmapDrawable->Bitmap == NULL)) {
				BitmapDrawable->Bitmap = static_cast<TBitmap*>(it->second);
			}

			TListItemText* TextDrawable = static_cast<TListItemText*>(item->View->FindDrawable("info"));
			if(TextDrawable != NULL) {
				TextDrawable->Text = static_cast<TBitmapString*>(it->second)->ImgName;
			}
			MatchView(item);
		}
	}
	FParent->StopPullRefresh();
	ItemsResize();
	ItemsInvalidate();
}

void __fastcall TCustomAdapter::MatchView(Fmx::Listview::Types::TListItem* const Item)
{
	TListItemImage * BitmapDrawable = static_cast<TListItemImage*>(Item->View->FindDrawable("bitmap"));
	if((BitmapDrawable != NULL) && (BitmapDrawable->Bitmap != NULL)) {
		double Width = FParent->Width - FParent->ItemSpaces->Left - FParent->ItemSpaces->Right;
		BitmapDrawable->Width = Width;
		double Aspect = Width / BitmapDrawable->Bitmap->Width;
		Item->Height = BitmapDrawable->Bitmap->Height * Aspect + 0.5;

		TListItemText * TextDrawable = static_cast<TListItemText*>(Item->View->FindDrawable("info"));
		TextDrawable->Width = Width - 100;
	}
}

void __fastcall TCustomAdapter::ResetView(TListItem* const Item)
{
	if (FOnResetView != NULL){
		FOnResetView(Item);
	}
	DoResetView(Item);
}

__fastcall TCustomAdapter::TThreadProcedure::TThreadProcedure(TCustomAdapter * p_Adapter)
{
	m_Adapter = p_Adapter;
}

void __fastcall TCustomAdapter::TThreadProcedure::InsertImage(void){
	try {
		TBitmapString * bitmap = new TBitmapString();
		bitmap->LoadFromStream(m_stream);
        bitmap->ImgName = m_imgName;
		m_stream->Clear();
		if((bitmap != NULL) && (bitmap->Width > 0) && (bitmap->Height > 0)) {
			m_Adapter->FBitmaps.insert(std::pair<int, TBitmapString*>(m_index, bitmap));
		}
		if((bitmap != NULL) && (bitmap->Width > 0) && (bitmap->Height > 0)) {
			m_Adapter->ImagesLoaded();
		}
	}
	catch(...){
	}
}

void __fastcall TCustomAdapter::TThreadProcedure::Invoke(void)
{
	std::unique_ptr<Rest::Client::TRESTClient> rc(new Rest::Client::TRESTClient(nullptr));
	rc->Accept = "application/json, text/plain; q=0.9, text/html;q=0.8,";
	rc->AcceptCharset = "UTF-8, *;q=0.8";
	rc->RaiseExceptionOn500 = false;

	std::unique_ptr<Rest::Client::TRESTResponse> rp(new Rest::Client::TRESTResponse(nullptr));
	rp->ContentType = "application/json";

	std::unique_ptr<Rest::Client::TRESTRequest> rt(new Rest::Client::TRESTRequest(nullptr));
	rt->Client = rc.get();
	rt->Response = rp.get();

	std::unique_ptr<Firedac::Comp::Client::TFDMemTable> fd(new Firedac::Comp::Client::TFDMemTable(nullptr));
	fd->FieldDefs->Add("copyright", Data::Db::ftString, 20);
	fd->FieldDefs->Add("date", Data::Db::ftString, 20);
	fd->FieldDefs->Add("explanation", Data::Db::ftString, 200);
	fd->FieldDefs->Add("hdurl", Data::Db::ftString, 20);
	fd->FieldDefs->Add("media_type", Data::Db::ftString, 20);
	fd->FieldDefs->Add("service_version", Data::Db::ftString, 20);
	fd->FieldDefs->Add("title", Data::Db::ftString, 20);
	fd->FieldDefs->Add("url", Data::Db::ftString, 20);
	fd->FetchOptions->Mode = fmAll;
	fd->StoreDefs = true;

	std::unique_ptr<Rest::Response::Adapter::TRESTResponseDataSetAdapter> rd(new Rest::Response::Adapter::TRESTResponseDataSetAdapter(nullptr));
	rd->Response = rp.get();
	rd->Dataset = fd.get();
	rd->Active = true;

	std::unique_ptr<System::Net::Httpclientcomponent::TNetHTTPClient> nc(new System::Net::Httpclientcomponent::TNetHTTPClient(nullptr));

	UnicodeString URI;
	m_stream = new TMemoryStream;

	m_index = m_Adapter->NextIndex();
	while(m_index != -1)
	{
        m_imgName = "";
		String nasaAPI(m_Adapter->FNasaApiUrl);
		if (nasaAPI == "") {
		   URI = "https://apod.nasa.gov/apod/image/1702/Encke3tails_Hemmerich_960.jpg";
		} else {
		   String dateStr;
		   if (m_Adapter->FBaseDate < Now()) {
				dateStr	= FormatDateTime("yyyy-mm-dd", IncDay(m_Adapter->FBaseDate, m_index));
		   } else {
				dateStr	= FormatDateTime("yyyy-mm-dd", Now());
		   }
		   nasaAPI += "&date=" + dateStr;

		   rc->BaseURL = nasaAPI;
		   rt->Execute();

		   if ((!fd->IsEmpty()) && (fd->FieldByName("url")->AsString != "")) {
			  if (fd->FieldByName("media_type")->AsString == "image") {
				URI = fd->FieldByName("url")->AsString;
				 m_imgName = fd->FieldByName("date")->AsString + ": " +  fd->FieldByName("title")->AsString;

			  } else {
                 m_imgName = "File or Video not suported";
			  }
		   }
		}
		try
		{
			if (URI != "") {
				nc->Get(URI, m_stream);
				TThread::Synchronize(NULL, InsertImage);
			}
		}
		catch(...)
		{
			m_Adapter->AddIndex(m_index); // push back so it's picked up later
			TThread::CurrentThread->Sleep(Random(100) + 100);
		}
		m_index = m_Adapter->NextIndex();
	}
	delete m_stream;
}


void __fastcall TCustomAdapter::AddIndex(int Index)
{
	try
	{
		FCS->Acquire();
		FRequests.push(Index);
		FSem->Release(); //Increase available
	}
	__finally
	{
		FCS->Release();
	}
}

void __fastcall TCustomAdapter::ClearIndex()
{
	try
	{
		FCS->Acquire();
		FIndex = 0;
	}
	__finally
	{
		FCS->Release();
	}
}

int __fastcall TCustomAdapter::NextIndex()	//wait for available, -1 if end requested
{
	int Result;
	FSem->Acquire();
	if(FExitRequested)
		return -1;
	try
	{
		FCS->Acquire();
		Result = FIndex;
		FIndex++;
	}
	__finally
	{
		FCS->Release();
	}
	return Result;
}

void __fastcall TCustomAdapter::CreateThreads(void)
{
	for(int i = 0; i < ThreadPoolSize; i++) {
		System::Classes::TThread *myThread = System::Classes::TThread::CreateAnonymousThread(new TThreadProcedure(this));
		myThread->FreeOnTerminate = false;
		myThread->Start();
		FThreads.push_back(myThread);
	}
}

void __fastcall TCustomAdapter::DestroyThreads(void)
{
	FExitRequested = True;
  	FSem->Release(ThreadPoolSize);

	for(size_t i = 0; i < FThreads.size(); i++) {
		TThread *th = static_cast<TThread*>(FThreads[i]);
		th->WaitFor();
		static_cast<TThread*>(FThreads[i])->WaitFor();
	}
	FThreads.clear();
}
System::UnicodeString __fastcall TCustomAdapter::GetName(const int Index)
{
	TMatch match = FNameRegex->Match((*FStrings)[Index]);
	if(match.Success) {
		return match.Groups[1].Value;
	}
	return EmptyStr;
}

System::UnicodeString __fastcall TCustomAdapter::GetId(const int Index)
{
	TMatch match = FIdRegex->Match((*FStrings)[Index]);
	if(match.Success) {
		return match.Groups[1].Value;
	}
	return EmptyStr;
}

System::UnicodeString __fastcall TCustomAdapter::GetUri(const int Index)
{
	UnicodeString _return = EmptyStr;
	UnicodeString uri = (*FStrings)[Index];
	if(FStrings->Count > 0) {
		TMatch match = FUriRegex->Match((*FStrings)[Index]);
		if(match.Success)
			_return =  match.Groups[1].Value;
	}
	return _return;
}

System::UnicodeString __fastcall TCustomAdapter::GetText(const int Index)
{
  return GetName(Index);
}

System::UnicodeString __fastcall TCustomAdapter::GetIndexTitle(const int Index)
{
	return "";
}

void __fastcall TCustomAdapter::ButtonClicked(System::TObject* Sender)
{
	if(FOnButtonClicked != NULL) {
		OnButtonClicked(Sender);
    }
}

void __fastcall TCustomAdapter::SetOnButtonClicked(const System::Classes::TNotifyEvent Value)
{
	FOnButtonClicked = Value;
}

TListItemTextButton* __fastcall TCustomAdapter::GetTextButtonDrawable(const int Index)
{
	return static_cast<TListItemTextButton*>(static_cast<TListItem*>(FStrings->Objects[Index])->View->FindDrawable("button"));
}

void __fastcall TCustomAdapter::DoCreateNewViews(void)
{
	// nothing!
}

void __fastcall TCustomAdapter::ItemsMayChange(void) {
	if(FOnItemsMayChange != NULL) {
		FOnItemsMayChange(this);
    }
}

void __fastcall TCustomAdapter::SetOnItemsMayChange(const System::Classes::TNotifyEvent Value)
{
    FOnItemsMayChange = Value;
}

void __fastcall TCustomAdapter::SetOnItemsResize(const System::Classes::TNotifyEvent Value)
{
    FOnItemsResize = Value;
}

void __fastcall TCustomAdapter::ItemsResize(void) {
	if(FOnItemsResize != NULL) {
		FOnItemsResize(this);
	}
}

void __fastcall TCustomAdapter::ItemsInvalidate(void) {
	if(FOnItemsInvalidate != NULL) {
		FOnItemsInvalidate(this);
	}
}

void __fastcall TCustomAdapter::DoResetViews(const Fmx::Listview::Types::TListItemPurposes APurposes)
{
	for(int i = 0; i < FStrings->Count; i++) {
		this->ResetView(((TListItem*)FStrings->Objects[i]));
	}
	ItemsResize();
}

void __fastcall TCustomAdapter::DoResetView(Fmx::Listview::Types::TListItem* const Item)
{
	if(Item->View->Count == 0) {

		TListItemImage * BitmapDrawable = new TListItemImage(Item);
		BitmapDrawable->Name = "bitmap";
		BitmapDrawable->OwnsBitmap = false;
		BitmapDrawable->Bitmap = NULL;
		BitmapDrawable->Align = TListItemAlign::Trailing;
		BitmapDrawable->ScalingMode = TImageScalingMode::StretchWithAspect;

		TListItemText * TextDrawable = new TListItemText(Item);
		TextDrawable = new TListItemText(Item);
		TextDrawable->Name = "info";
		TextDrawable->Text = GetId(Item->Index);
		TextDrawable->Font->Size = 16;
//		TextDrawable->Font->Family = "@MS Gothic";
		TextDrawable->TextColor = TAlphaColorRec::Aqua;
		TextDrawable->SelectedTextColor = TAlphaColorRec::White;
		TextDrawable->Align = TListItemAlign::Leading;
		TextDrawable->VertAlign = TListItemAlign::Trailing;
		TextDrawable->WordWrap = true;
		TextDrawable->Height = 35;
		TextDrawable->PlaceOffset->X = 10;

		AddIndex(Item->Index);
	}
	else {
		MatchView(Item);
	}
}

void __fastcall TAbstractListViewAdapter::ItemsMayChange(void)
{
	if (FOnItemsMayChange != NULL){
		FOnItemsMayChange(this);
	}
}

void __fastcall TCustomAdapter::StringListChanging(System::TObject* Sender)
{
	ItemsMayChange();
}

void __fastcall TCustomAdapter::SetOnItemsCouldHaveChanged(const System::Classes::TNotifyEvent Value)
{
	FOnItemsCouldHaveChanged = Value;
}

void __fastcall TCustomAdapter::ItemsCouldHaveChanged(void)
{
	if(FOnItemsCouldHaveChanged != NULL){
		FOnItemsCouldHaveChanged(this);
	}
}

void __fastcall TCustomAdapter::StringListChange(System::TObject* Sender)
{
	ItemsCouldHaveChanged();
	ItemsResize();
	ItemsInvalidate();
}

int __fastcall TCustomAdapter::GetCount(void)
{
	return FStrings->Count;
}

TListItem * __fastcall TCustomAdapter::GetItem(const int Index)
{
	TListItem * _return = static_cast<TListItem*>(FStrings->Objects[Index]);
	if(_return == NULL) {
		_return = new TListItem(FParent->Adapter, *FParent);
		_return->Height = GetDefaultViewHeight();
		_return->Index = Index;
		FStrings->Objects[Index] = _return;
		this->ResetView(_return);
	}
	return _return;
}

int __fastcall TCustomAdapter::IndexOf(Fmx::Listview::Types::TListItem* const AItem)
{
	return -1;
}

System::Generics::Collections::TEnumerator__1<Fmx::Listview::Types::TListItem*>* __fastcall TCustomAdapter::GetEnumerator(void)
{
	return NULL;
}

int __fastcall TCustomAdapter::GetDefaultViewHeight(void)
{
	return 33;
}


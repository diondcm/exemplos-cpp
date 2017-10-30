//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//--------------------Example Include's--------------------------------------
#include <pngimage.hpp>
#include <memory>
#include <FireDAC.Comp.Client.hpp>

#include "ServerRESTUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TServerREST::TServerREST(TComponent* Owner)
	: TDSServerModule(Owner)
{
}
//----------------------------------------------------------------------------
System::UnicodeString TServerREST::EchoString(System::UnicodeString value)
{
    return value;
}
//----------------------------------------------------------------------------
System::UnicodeString TServerREST::ReverseString(System::UnicodeString value)
{
    return ::ReverseString(value);
}
//----------------------------------------------------------------------------
System::UnicodeString TServerREST::SaveImage(System::Classes::TStream* val)
{
	// Example Include's

	val->Position = 0;
//  new compiler
	std::auto_ptr<TPngImage> png(new TPngImage);
	png->LoadFromStream(val);
	// runing on threads
	System::String imgName("Img");
	imgName += "_" + IntToStr(Random(1000000)) + "_" + IntToStr((int) TThread::CurrentThread->ThreadID) + ".png";
	png->SaveToFile(imgName);
	return imgName;
	//leaks

}
//----------------------------------------------------------------------------
System::Classes::TStream* TServerREST::GetCountryListStm()
{
	std::auto_ptr<TFDMemTable> lmem(new TFDMemTable(NULL));
	TMemoryStream* lStm(new TMemoryStream());

	lmem->LoadFromFile("country.xml"); // connect to a SGDB, this is just an example
	lmem->SaveToStream(lStm, sfJSON);
	lStm->Position = 0;

	return lStm;
}
//----------------------------------------------------------------------------
System::UnicodeString TServerREST::GetCountryList()
{
	std::auto_ptr<TStringList> lStl(new TStringList());
	lStl->LoadFromStream(GetCountryListStm());
	return lStl->Text;
}
//----------------------------------------------------------------------------
System::Json::TJSONObject* TServerREST::GetJSON()
{
	TJSONObject* jObj = new TJSONObject();
	jObj->AddPair("client", "Test");
    return jObj;
}


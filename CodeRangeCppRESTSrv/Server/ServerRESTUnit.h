//---------------------------------------------------------------------------

#ifndef ServerRESTUnitH
#define ServerRESTUnitH
//---------------------------------------------------------------------------
#include <System.JSON.hpp>

#include <System.Classes.hpp>
#include <DataSnap.DSServer.hpp>
#include <Datasnap.DSProviderDataModuleAdapter.hpp>
#include <FireDAC.Stan.StorageBin.hpp>
#include <FireDAC.Stan.StorageJSON.hpp>
#include <FireDAC.Stan.StorageXML.hpp>

//---------------------------------------------------------------------------
class TServerREST : public TDSServerModule
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TServerREST(TComponent* Owner);
	System::UnicodeString EchoString(System::UnicodeString value);
	System::UnicodeString ReverseString(System::UnicodeString value);

	System::UnicodeString SaveImage(System::Classes::TStream* val);
	System::UnicodeString GetCountryList();
	System::Classes::TStream* GetCountryListStm();

	///  What more?
	System::Json::TJSONObject* GetJSON();
};
//---------------------------------------------------------------------------
extern PACKAGE TServerREST *ServerREST;
//---------------------------------------------------------------------------
#endif


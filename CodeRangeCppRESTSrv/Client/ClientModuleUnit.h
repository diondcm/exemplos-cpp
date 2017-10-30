//----------------------------------------------------------------------------

#ifndef ClientModuleUnitH
#define ClientModuleUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "ClientClassesUnit.h"
#include <Datasnap.DSClientRest.hpp>
//----------------------------------------------------------------------------
class TClientModule : public TDataModule
{
__published:	// IDE-managed Components
	TDSRestConnection *DSRestConnection1;
private:	// User declarations
	bool FInstanceOwner;
	TServerRESTClient* FServerRESTClient;
	TServerRESTClient* GetServerRESTClient(void);
public:		// User declarations
	__fastcall TClientModule(TComponent* Owner);
	__fastcall ~TClientModule();
	__property bool InstanceOwner = {read=FInstanceOwner, write=FInstanceOwner};
	__property TServerRESTClient* ServerRESTClient = {read=GetServerRESTClient, write=FServerRESTClient};
};
//---------------------------------------------------------------------------
extern PACKAGE TClientModule *ClientModule;
//---------------------------------------------------------------------------
#endif

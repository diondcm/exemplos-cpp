//----------------------------------------------------------------------------

#pragma hdrstop
#include <stdio.h>
#include <memory>

#include "ClientModuleUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma resource "*.dfm"
TClientModule *ClientModule;
//---------------------------------------------------------------------------
__fastcall TClientModule::TClientModule(TComponent* Owner)
	: TDataModule(Owner)
{
	FInstanceOwner = true;
}

__fastcall TClientModule::~TClientModule()
{
	delete FServerRESTClient;
}

TServerRESTClient* TClientModule::GetServerRESTClient(void)
{
	if (FServerRESTClient == NULL)
		FServerRESTClient= new TServerRESTClient(DSRestConnection1, FInstanceOwner);
	return FServerRESTClient;
};


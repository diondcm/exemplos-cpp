// 
// Created by the DataSnap proxy generator.
// 29/10/2017 21:42:18
// 

#include "ClientClassesUnit.h"

  struct TDSRestParameterMetaData TServerREST_EchoString[] =
  {
    {"value", 1, 26, "String"},
    {"", 4, 26, "String"}
  };

  struct TDSRestParameterMetaData TServerREST_ReverseString[] =
  {
    {"value", 1, 26, "String"},
    {"", 4, 26, "String"}
  };

  struct TDSRestParameterMetaData TServerREST_SaveImage[] =
  {
    {"val", 1, 33, "TStream"},
    {"", 4, 26, "String"}
  };

  struct TDSRestParameterMetaData TServerREST_GetCountryList[] =
  {
    {"", 4, 26, "String"}
  };

  struct TDSRestParameterMetaData TServerREST_GetCountryListStm[] =
  {
    {"", 4, 33, "TStream"}
  };

  struct TDSRestParameterMetaData TServerREST_GetCountryListStm_Cache[] =
  {
    {"", 4, 26, "String"}
  };

  struct TDSRestParameterMetaData TServerREST_GetJSON[] =
  {
    {"", 4, 37, "TJSONObject"}
  };

  struct TDSRestParameterMetaData TServerREST_GetJSON_Cache[] =
  {
    {"", 4, 26, "String"}
  };

System::UnicodeString __fastcall TServerRESTClient::EchoString(System::UnicodeString value, const String& ARequestFilter)
{
  if (FEchoStringCommand == NULL)
  {
    FEchoStringCommand = FConnection->CreateCommand();
    FEchoStringCommand->RequestType = "GET";
    FEchoStringCommand->Text = "TServerREST.EchoString";
    FEchoStringCommand->Prepare(TServerREST_EchoString, 1);
  }
  FEchoStringCommand->Parameters->Parameter[0]->Value->SetWideString(value);
  FEchoStringCommand->Execute(ARequestFilter);
  System::UnicodeString result = FEchoStringCommand->Parameters->Parameter[1]->Value->GetWideString();
  return result;
}

System::UnicodeString __fastcall TServerRESTClient::ReverseString(System::UnicodeString value, const String& ARequestFilter)
{
  if (FReverseStringCommand == NULL)
  {
    FReverseStringCommand = FConnection->CreateCommand();
    FReverseStringCommand->RequestType = "GET";
    FReverseStringCommand->Text = "TServerREST.ReverseString";
    FReverseStringCommand->Prepare(TServerREST_ReverseString, 1);
  }
  FReverseStringCommand->Parameters->Parameter[0]->Value->SetWideString(value);
  FReverseStringCommand->Execute(ARequestFilter);
  System::UnicodeString result = FReverseStringCommand->Parameters->Parameter[1]->Value->GetWideString();
  return result;
}

System::UnicodeString __fastcall TServerRESTClient::SaveImage(TStream* val, const String& ARequestFilter)
{
  if (FSaveImageCommand == NULL)
  {
    FSaveImageCommand = FConnection->CreateCommand();
    FSaveImageCommand->RequestType = "POST";
    FSaveImageCommand->Text = "TServerREST.\"SaveImage\"";
    FSaveImageCommand->Prepare(TServerREST_SaveImage, 1);
  }
  FSaveImageCommand->Parameters->Parameter[0]->Value->SetStream(val, FInstanceOwner);
  FSaveImageCommand->Execute(ARequestFilter);
  System::UnicodeString result = FSaveImageCommand->Parameters->Parameter[1]->Value->GetWideString();
  return result;
}

System::UnicodeString __fastcall TServerRESTClient::GetCountryList(const String& ARequestFilter)
{
  if (FGetCountryListCommand == NULL)
  {
    FGetCountryListCommand = FConnection->CreateCommand();
    FGetCountryListCommand->RequestType = "GET";
    FGetCountryListCommand->Text = "TServerREST.GetCountryList";
    FGetCountryListCommand->Prepare(TServerREST_GetCountryList, 0);
  }
  FGetCountryListCommand->Execute(ARequestFilter);
  System::UnicodeString result = FGetCountryListCommand->Parameters->Parameter[0]->Value->GetWideString();
  return result;
}

TStream* __fastcall TServerRESTClient::GetCountryListStm(const String& ARequestFilter)
{
  if (FGetCountryListStmCommand == NULL)
  {
    FGetCountryListStmCommand = FConnection->CreateCommand();
    FGetCountryListStmCommand->RequestType = "GET";
    FGetCountryListStmCommand->Text = "TServerREST.GetCountryListStm";
    FGetCountryListStmCommand->Prepare(TServerREST_GetCountryListStm, 0);
  }
  FGetCountryListStmCommand->Execute(ARequestFilter);
  TStream* result = FGetCountryListStmCommand->Parameters->Parameter[0]->Value->GetStream(FInstanceOwner);
  return result;
}

_di_IDSRestCachedStream __fastcall TServerRESTClient::GetCountryListStm_Cache(const String& ARequestFilter)
{
  if (FGetCountryListStmCommand_Cache == NULL)
  {
    FGetCountryListStmCommand_Cache = FConnection->CreateCommand();
    FGetCountryListStmCommand_Cache->RequestType = "GET";
    FGetCountryListStmCommand_Cache->Text = "TServerREST.GetCountryListStm";
    FGetCountryListStmCommand_Cache->Prepare(TServerREST_GetCountryListStm_Cache, 0);
  }
  FGetCountryListStmCommand_Cache->ExecuteCache(ARequestFilter);
  _di_IDSRestCachedStream _resultIntf;
  {
  TDSRestCachedStream* obj(new TDSRestCachedStream(FGetCountryListStmCommand_Cache->Parameters->Parameter[0]->Value->GetString()));
  obj->GetInterface(_resultIntf);
  }
  return _resultIntf;
}

TJSONObject* __fastcall TServerRESTClient::GetJSON(const String& ARequestFilter)
{
  if (FGetJSONCommand == NULL)
  {
    FGetJSONCommand = FConnection->CreateCommand();
    FGetJSONCommand->RequestType = "GET";
    FGetJSONCommand->Text = "TServerREST.GetJSON";
    FGetJSONCommand->Prepare(TServerREST_GetJSON, 0);
  }
  FGetJSONCommand->Execute(ARequestFilter);
  TJSONObject* result = (TJSONObject*)FGetJSONCommand->Parameters->Parameter[0]->Value->GetJSONValue(FInstanceOwner);
  return result;
}

_di_IDSRestCachedJSONObject __fastcall TServerRESTClient::GetJSON_Cache(const String& ARequestFilter)
{
  if (FGetJSONCommand_Cache == NULL)
  {
    FGetJSONCommand_Cache = FConnection->CreateCommand();
    FGetJSONCommand_Cache->RequestType = "GET";
    FGetJSONCommand_Cache->Text = "TServerREST.GetJSON";
    FGetJSONCommand_Cache->Prepare(TServerREST_GetJSON_Cache, 0);
  }
  FGetJSONCommand_Cache->ExecuteCache(ARequestFilter);
  _di_IDSRestCachedJSONObject _resultIntf;
  {
  TDSRestCachedJSONObject* obj(new TDSRestCachedJSONObject(FGetJSONCommand_Cache->Parameters->Parameter[0]->Value->GetString()));
  obj->GetInterface(_resultIntf);
  }
  return _resultIntf;
}


__fastcall  TServerRESTClient::TServerRESTClient(TDSRestConnection *ARestConnection): TDSAdminRestClient(ARestConnection)
{
}

__fastcall  TServerRESTClient::TServerRESTClient(TDSRestConnection *ARestConnection, bool AInstanceOwner): TDSAdminRestClient(ARestConnection, AInstanceOwner)
{
}

__fastcall  TServerRESTClient::~TServerRESTClient()
{
  delete FEchoStringCommand;
  delete FReverseStringCommand;
  delete FSaveImageCommand;
  delete FGetCountryListCommand;
  delete FGetCountryListStmCommand;
  delete FGetCountryListStmCommand_Cache;
  delete FGetJSONCommand;
  delete FGetJSONCommand_Cache;
}


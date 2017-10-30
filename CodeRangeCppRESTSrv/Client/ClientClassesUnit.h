#ifndef ClientClassesUnitH
#define ClientClassesUnitH

#include "Data.DBXCommon.hpp"
#include "System.Classes.hpp"
#include "System.SysUtils.hpp"
#include "Data.DB.hpp"
#include "Data.SqlExpr.hpp"
#include "Data.DBXDBReaders.hpp"
#include "Data.DBXCDSReaders.hpp"
#include "DataSnap.DSProxyRest.hpp"

  class TServerRESTClient : public TDSAdminRestClient
  {
  private:
    TDSRestCommand *FEchoStringCommand;
    TDSRestCommand *FReverseStringCommand;
    TDSRestCommand *FSaveImageCommand;
    TDSRestCommand *FGetCountryListCommand;
    TDSRestCommand *FGetCountryListStmCommand;
    TDSRestCommand *FGetCountryListStmCommand_Cache;
    TDSRestCommand *FGetJSONCommand;
    TDSRestCommand *FGetJSONCommand_Cache;
  public:
    __fastcall TServerRESTClient(TDSRestConnection *ARestConnection);
    __fastcall TServerRESTClient(TDSRestConnection *ADBXConnection, bool AInstanceOwner);
    __fastcall ~TServerRESTClient();
    System::UnicodeString __fastcall EchoString(System::UnicodeString value, const String& ARequestFilter = String());
    System::UnicodeString __fastcall ReverseString(System::UnicodeString value, const String& ARequestFilter = String());
    System::UnicodeString __fastcall SaveImage(TStream* val, const String& ARequestFilter = String());
    System::UnicodeString __fastcall GetCountryList(const String& ARequestFilter = String());
    TStream* __fastcall GetCountryListStm(const String& ARequestFilter = String());
    _di_IDSRestCachedStream __fastcall GetCountryListStm_Cache(const String& ARequestFilter = String());
    TJSONObject* __fastcall GetJSON(const String& ARequestFilter = String());
    _di_IDSRestCachedJSONObject __fastcall GetJSON_Cache(const String& ARequestFilter = String());
  };

#endif

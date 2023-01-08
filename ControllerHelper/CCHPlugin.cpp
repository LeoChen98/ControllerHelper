#include "pch.h"
#include "CCHPlugin.h"

// TAG ITEM TYPE
const int TAG_ITEM_TYPE_RTE_CHK = 1; // Route check indicator
const int TAG_ITEM_TYPE_CRZ_ALT = 2; // Curise altitude indicator

// TAG ITEM FUNCTION
const int TAG_ITEM_FUNCTION_RTE_CHK_MENU = 1; // Open route check popup menu
const int TAG_ITEM_FUNCTION_RTE_CHK_CHECK = 11; // Route check manually check function
const int TAG_ITEM_FUNCTION_RTE_CHK_RTE_POPUP = 12; // Route check open route popup menu
const int TAG_ITEM_FUNCTION_RTE_CHK_RESET = 13; // Reset route check status
const int TAG_ITEM_FUNCTION_RTE_CHK_RTE_SHOW = 100; // Route check show routes index list
													// Remarks: 101-199 reversed for route item index 
const int TAG_ITEM_FUNCTION_ALT_CHK_MENU = 2; // Open route check popup menu
CCHPlugin::CCHPlugin()
	: EuroScopePlugIn::CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
		MY_PLUGIN_NAME.c_str(),
		MY_PLUGIN_VERSION.c_str(),
		MY_PLUGIN_DEVELOPER.c_str(),
		MY_PLUGIN_COPYRIGHT.c_str())
{
	DisplayUserMessage("Message", "CHPlugin", std::string("Version " + MY_PLUGIN_VERSION + " loaded").c_str(), false, false, false, false, false);

	RegisterTagItemType("Route check indicator", TAG_ITEM_TYPE_RTE_CHK);
	RegisterTagItemType("Curise altitude indicator", TAG_ITEM_TYPE_CRZ_ALT);

	RegisterTagItemFunction("Open route check popup menu", TAG_ITEM_FUNCTION_RTE_CHK_MENU);
	RegisterTagItemFunction("Open altitude check popup menu", TAG_ITEM_FUNCTION_ALT_CHK_MENU);

	_socket = new SocketClient(this);
	_socket->Start();
}

CCHPlugin::~CCHPlugin()
{
}

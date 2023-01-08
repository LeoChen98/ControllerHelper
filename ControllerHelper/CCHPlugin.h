#pragma once
#include <string>
#include "EuroScopePlugIn.h"
#include "SocketClient.h"
#include "version.h"

using namespace std;
using namespace EuroScopePlugIn;

const string MY_PLUGIN_NAME = "Controller Helper";
const string MY_PLUGIN_VERSION = PLUGIN_VERSION;
const string MY_PLUGIN_DEVELOPER = "Leo Chen and other ControllerHelper project contributors";
const string MY_PLUGIN_COPYRIGHT = "Copyright (c) 2022 ControllerHelper project contributors; licenced under GPL 3.0.";

class SocketClient;

class CCHPlugin :
	public EuroScopePlugIn::CPlugIn
{
private:
	SocketClient* _socket;

public:
	CCHPlugin();
	virtual ~CCHPlugin();

	//virtual void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagMemData,
	//	char sItemString[16], int* pColorCode, COLORREF* pRGB, double* pFontSize);
	//virtual void OnFunctionCall(int FunctionId, const char* sItemString, POINT Pt, RECT Area);
	//virtual void OnFlightPlanControllerAssignedDataUpdate(CFlightPlan FlightPlan, int DataType);
	//virtual void OnFlightPlanDisconnect(CFlightPlan FlightPlan);
	//virtual void OnFlightPlanFlightPlanDataUpdate(CFlightPlan FlightPlan);
	//virtual void OnRadarTargetPositionUpdate(CRadarTarget RadarTarget);
	//virtual bool OnCompileCommand(const char* sCommandLine);
};

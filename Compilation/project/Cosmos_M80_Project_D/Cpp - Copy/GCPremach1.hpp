#if !defined _GCPREMACH1_HPP_
#define _GCPREMACH1_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCPremach1 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		MAIN = 43,
		KEY_ACTION = 55,
		GBUTTON00006 = 6,
		KEY_DURING_MACHINING = 7,
		KEY_POST_MACHINING = 8,
		KEY_DIAGNOSIS = 9,
		KEY_MAINTENANCE = 10,
		KEY_CUT_O_METER = 11,
		KEY_CALC_WINDOW = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		KEY_BACK = 15,
		GCODE_BUTTON = 18,
		GBUTTON00023 = 23,
		MCODE_BUTTON = 24,
		GBUTTON00025 = 25,
		CUTT_PARM_BUTTON = 26,
		DRILL_SEL_BUTTON = 27,
		GBUTTON00028 = 28,
		TOOL_MAG_SETT_BUTTON = 29,
		MAG_VIEW_BUTTON = 30,
		LOAD_TYPE_BUTTON = 31,
		GBUTTON00032 = 32,
		FACE_MILL_BUTTON = 33,
		POCK_MILL_BUTTON = 34,
		SPIGOT_MILL_BUTTON = 35,
		THREAD_MILL_BUTTON = 36,
		GBUTTON00037 = 37,
		MACH_LEVELS_BUTTON = 38,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 47,
		ICON2 = 48,
		ICON3 = 49,
		ICON4 = 50,
		ICON5 = 51,
		ICON6 = 52,
		ICON7 = 53,
		GSLINE00019 = 19,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPremach1();
	virtual ~GCPremach1();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long CUTT_PARM_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DRILL_SEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long FACE_MILL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long GCODE_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long LOAD_TYPE_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MACH_LEVELS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MAG_VIEW_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MCODE_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long POCK_MILL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long SPIGOT_MILL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long THREAD_MILL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_MAG_SETT_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD


	short Cursor_Pos;
	short Tab_Pos;
    bool bCalcWindowOpened;

	void SetCursor(short cur_pos);
	void ClearWarningMessage();
	void ScreenTransition(short ScreenNo);
	void DisableButtonName();
	long User(long lLParam, long lUParam);
	void EnableButtonName();
	//void ReadIconStatus(int i);
	void ReadIconStatus();
	void SetWarningMessage(int warnnum);
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCPremach1( GBaseObject *pObject );
short GCINewGCPremach1( GBaseObject *pObject );
}
#endif /* _GCPREMACH1_HPP_ */


#if !defined _GCPOSTMACH_HPP_
#define _GCPOSTMACH_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCPostmach : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 65,
		CYCLE_TIME_BUTTON = 18,
		DU_REPORT_BUTTON = 26,
		DU_HISTORY_BUTTON = 27,
		DT_HISTORY_BUTTON = 29,
		DT_ANALYSIS_BUTTON = 30,
		OEE_HISTORY_BUTTON = 33,
		OEE_REPORT_BUTTON = 34,
		KEY_PRE_MACHINING = 40,
		KEY_DURING_MACHINING = 41,
		GBUTTON00042 = 42,
		KEY_DIAGNOSIS = 43,
		KEY_MAINTENANCE = 44,
		KEY_CUT_O_METER = 45,
		KEY_CALC_WINDOW = 46,
		GBUTTON00047 = 47,
		GBUTTON00048 = 48,
		KEY_BACK = 49,
		GBUTTON00051 = 51,
		GBUTTON00052 = 52,
		GBUTTON00053 = 53,
		GBUTTON00054 = 54,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 57,
		ICON2 = 58,
		ICON3 = 59,
		ICON4 = 60,
		ICON5 = 61,
		ICON6 = 62,
		ICON7 = 63,
		GSLINE00019 = 19,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPostmach();
	virtual ~GCPostmach();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long CYCLE_TIME_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DT_ANALYSIS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DT_HISTORY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DU_HISTORY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DU_REPORT_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long OEE_HISTORY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long OEE_REPORT_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
	void ReadIconStatus();
	void SetWarningMessage(int warnnum);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCPostmach( GBaseObject *pObject );
short GCINewGCPostmach( GBaseObject *pObject );
}
#endif /* _GCPOSTMACH_HPP_ */


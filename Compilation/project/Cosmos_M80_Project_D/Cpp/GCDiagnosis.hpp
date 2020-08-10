#if !defined _GCDIAGNOSIS_HPP_
#define _GCDIAGNOSIS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDiagnosis : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 74,
		IP_LIST_BUTTON = 18,
		ELECTRICAL_BUTTON = 26,
		PNEUMATICS_BUTTON = 27,
		LATCH_RELAY_BUTTON = 29,
		PLC_BITS_BUTTON = 30,
		OP_LIST_BUTTON = 40,
		HYDRAULICS_BUTTON = 41,
		REGISTERS_BUTTON = 42,
		WORK_OFFSET_BUTTON = 44,
		KEY_HISTORY_BUTTON = 45,
		TOOL_OFFSET_BUTTON = 46,
		TOUCH_HISTORY_BUTTON = 47,
		HW_SW_VERSION_BUTTON = 49,
		KEY_PRE_MACHINING = 50,
		KEY_DURING_MACHINING = 51,
		KEY_POST_MACHINING = 52,
		GBUTTON00053 = 53,
		KEY_MAINTENANCE = 54,
		KEY_CUT_O_METER = 55,
		KEY_CALC_WINDOW = 56,
		GBUTTON00057 = 57,
		GBUTTON00058 = 58,
		KEY_BACK = 59,
		GBUTTON00060 = 60,
		GBUTTON00061 = 61,
		GBUTTON00062 = 62,
		GBUTTON00063 = 63,
		GBUTTON00064 = 64,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 66,
		ICON2 = 67,
		ICON3 = 68,
		ICON4 = 69,
		ICON5 = 70,
		ICON6 = 71,
		ICON7 = 72,
		GSLINE00019 = 19,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDiagnosis();
	virtual ~GCDiagnosis();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long ELECTRICAL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long HW_SW_VERSION_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long HYDRAULICS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long IP_LIST_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_HISTORY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long LATCH_RELAY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long OP_LIST_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PLC_BITS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PNEUMATICS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long REGISTERS_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_OFFSET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TOUCH_HISTORY_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long WORK_OFFSET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
void GCIDeleteGCDiagnosis( GBaseObject *pObject );
short GCINewGCDiagnosis( GBaseObject *pObject );
}
#endif /* _GCDIAGNOSIS_HPP_ */


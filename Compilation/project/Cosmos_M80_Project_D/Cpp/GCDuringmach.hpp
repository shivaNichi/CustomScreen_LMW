#if !defined _GCDURINGMACH_HPP_
#define _GCDURINGMACH_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDuringmach : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 64,
		CUT_O_METER_BUTTON = 18,
		OP_SETUP_BUTTON = 26,
		KEY_PRE_MACHINING = 40,
		GBUTTON00041 = 41,
		KEY_POST_MACHINING = 42,
		KEY_DIAGNOSIS = 43,
		KEY_MAINTENANCE = 44,
		KEY_CUT_O_METER = 45,
		KEY_CALC_WINDOW = 46,
		GBUTTON00047 = 47,
		GBUTTON00048 = 48,
		KEY_BACK = 49,
		GBUTTON00050 = 50,
		GBUTTON00051 = 51,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 56,
		ICON2 = 57,
		ICON3 = 58,
		ICON4 = 59,
		ICON5 = 60,
		ICON6 = 61,
		ICON7 = 62,
		GSLINE00019 = 19,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDuringmach();
	virtual ~GCDuringmach();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long CUT_O_METER_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long OP_SETUP_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
void GCIDeleteGCDuringmach( GBaseObject *pObject );
short GCINewGCDuringmach( GBaseObject *pObject );
}
#endif /* _GCDURINGMACH_HPP_ */


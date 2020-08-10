#if !defined _GCMCODE_HPP_
#define _GCMCODE_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMcode : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 26,
		KEY_GCODE = 6,
		KEY_PARAMETER = 7,
		KEY_TOOLDATA = 8,
		KEY_CYCLES = 9,
		KEY_MACHINING_COND = 10,
		KEY_CUT_O_METER = 11,
		KEY_CALC_WINDOW = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		KEY_BACK = 15,
		HTML_OBJECT = 16,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 18,
		ICON2 = 19,
		ICON3 = 20,
		ICON4 = 21,
		ICON5 = 22,
		ICON6 = 23,
		ICON7 = 24,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMcode();
	virtual ~GCMcode();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CYCLESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_GCODEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MACHINING_CONDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PARAMETEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOLDATAOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
void GCIDeleteGCMcode( GBaseObject *pObject );
short GCINewGCMcode( GBaseObject *pObject );
}
#endif /* _GCMCODE_HPP_ */


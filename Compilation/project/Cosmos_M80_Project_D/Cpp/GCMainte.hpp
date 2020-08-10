#if !defined _GCMAINTE_HPP_
#define _GCMAINTE_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMainte : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 71,
		DAILY_CHECK_BUTTON = 18,
		MONTHLY_CHECK_BUTTON = 26,
		QUATERLY_CHECK_BUTTON = 30,
		PREVENT_CHECK_BUTTON = 44,
		KEY_PRE_MACHINING = 45,
		KEY_DURING_MACHINING = 46,
		KEY_POST_MACHINING = 47,
		KEY_DIAGNOSIS = 48,
		GBUTTON00049 = 49,
		KEY_CUT_O_METER = 50,
		KEY_CALC_WINDOW = 51,
		GBUTTON00052 = 52,
		GBUTTON00053 = 53,
		KEY_BACK = 54,
		GBUTTON00055 = 55,
		GBUTTON00056 = 56,
		GBUTTON00057 = 57,
		GBUTTON00058 = 58,
		GBUTTON00069 = 69,
		BACKUP_BUTTON = 70,
		GLABEL00003 = 3,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 61,
		ICON2 = 62,
		ICON3 = 63,
		ICON4 = 64,
		ICON5 = 65,
		ICON6 = 66,
		ICON7 = 67,
		GSLINE00019 = 19,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMainte();
	virtual ~GCMainte();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BACKUP_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DAILY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MONTHLY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PREVENT_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long QUATERLY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
void GCIDeleteGCMainte( GBaseObject *pObject );
short GCINewGCMainte( GBaseObject *pObject );
}
#endif /* _GCMAINTE_HPP_ */


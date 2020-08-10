#if !defined _GCDRILLSEL_HPP_
#define _GCDRILLSEL_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDrillSel : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_CODES = 6,
		KEY_CUTTING_PARA = 7,
		KEY_TOOLDATA = 8,
		KEY_CYCLES = 9,
		KEY_MACHINING_COND = 10,
		KEY_CUT_O_METER = 11,
		KEY_CALC_WINDOW = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		KEY_BACK = 15,
		DATA = 25,
		GLABEL00003 = 3,
		GLABEL00017 = 17,
		GLABEL00018 = 18,
		GLABEL00019 = 19,
		GLABEL00023 = 23,
		GLABEL00024 = 24,
		GLABEL00030 = 30,
		GLABEL00031 = 31,
		GLABEL00035 = 35,
		GLABEL00038 = 38,
		TAP_SIZE = 48,
		PITCH_THREAD = 49,
		DRILL_SIZE = 50,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 40,
		ICON2 = 41,
		ICON3 = 42,
		ICON4 = 43,
		ICON5 = 44,
		ICON6 = 45,
		ICON7 = 46,
		GSRECT00016 = 16,
		GSRECT00034 = 34,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDrillSel();
	virtual ~GCDrillSel();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CODESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUTTING_PARAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CYCLESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MACHINING_CONDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOLDATAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PITCH_THREADOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TAP_SIZEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

	GTCHAR inpBuff[10];
	int WarningBit;
	short Cursor_Pos;
	short Tab_Pos;
    bool bCalcWindowOpened;
	float GlobaleValue;
	void SetCursor(short cur_pos);
	void ClearWarningMessage();
	void ScreenTransition(short ScreenNo);
	void DisableButtonName();
	long User(long lLParam, long lUParam);
	void EnableButtonName();
	//void ReadIconStatus(int i);
	void ReadIconStatus();
	void SetWarningMessage(int warnnum);
	void MainFunction();
	void Calcuations();
	long CheckRange(char *dat, int cellpos);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCDrillSel( GBaseObject *pObject );
short GCINewGCDrillSel( GBaseObject *pObject );
}
#endif /* _GCDRILLSEL_HPP_ */


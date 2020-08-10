#if !defined _GCCUTPARA_HPP_
#define _GCCUTPARA_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCCutPara : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_CODES = 6,
		KEY_DRILLSEL = 7,
		KEY_TOOLDATA = 8,
		KEY_CYCLES = 9,
		KEY_MACHINING_COND = 10,
		KEY_CUT_O_METER = 11,
		KEY_CALC_WINDOW = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		KEY_BACK = 15,
		DATA = 33,
		GLABEL00003 = 3,
		GLABEL00017 = 17,
		GLABEL00018 = 18,
		GLABEL00019 = 19,
		GLABEL00020 = 20,
		GLABEL00021 = 21,
		GLABEL00024 = 24,
		GLABEL00025 = 25,
		GLABEL00032 = 32,
		GLABEL00038 = 38,
		GLABEL00039 = 39,
		GLABEL00040 = 40,
		GLABEL00041 = 41,
		GLABEL00045 = 45,
		GLABEL00048 = 48,
		GLABEL00049 = 49,
		CUTTER_DIA = 58,
		FLUTES = 59,
		CUTTING_SPEED = 60,
		FEED_TOOTH = 61,
		SPINDLE_RPM = 62,
		CUTTING_FEEDRATE = 63,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 50,
		ICON2 = 51,
		ICON3 = 52,
		ICON4 = 53,
		ICON5 = 54,
		ICON6 = 55,
		ICON7 = 56,
		GSRECT00042 = 42,
		GSRECT00044 = 44,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCCutPara();
	virtual ~GCCutPara();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long CUTTER_DIAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CUTTING_SPEEDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long FEED_TOOTHOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long FLUTESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CODESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CYCLESOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DRILLSELOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MACHINING_CONDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOLDATAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

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
void GCIDeleteGCCutPara( GBaseObject *pObject );
short GCINewGCCutPara( GBaseObject *pObject );
}
#endif /* _GCCUTPARA_HPP_ */


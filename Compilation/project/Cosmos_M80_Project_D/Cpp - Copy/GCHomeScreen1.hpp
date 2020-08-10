#if !defined _GCHOMESCREEN1_HPP_
#define _GCHOMESCREEN1_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHomeScreen1 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		MAIN = 429,
		KEY_ACTION = 448,
		DURING_MACHINING = 146,
		KEY_PRE_MACHINING = 63,
		KEY_DURING_MACHINING = 77,
		KEY_POST_MACHINING = 78,
		KEY_DIAGNOSIS = 79,
		KEY_MAINTENANCE = 80,
		KEY_CUT_O_METER = 81,
		GBUTTON00082 = 82,
		KEY_DOWNTIMEDATA = 83,
		GBUTTON00084 = 84,
		KEY_EXIT = 85,
		PRE_MACHINING = 98,
		POST_MACHINING = 114,
		MAINTENANCE = 176,
		CUT_O_METER = 185,
		DIAGNOSIS = 388,
		GLABEL00104 = 104,
		GLABEL00107 = 107,
		GLABEL00108 = 108,
		GLABEL00109 = 109,
		TOOL_LIFE_TOOL_NAME = 170,
		GLABEL00030 = 30,
		GLABEL00101 = 101,
		GLABEL00102 = 102,
		GLABEL00103 = 103,
		GLABEL00105 = 105,
		GLABEL00187 = 187,
		GLABEL00188 = 188,
		GLABEL00189 = 189,
		GLABEL00190 = 190,
		GLABEL00191 = 191,
		GLABEL00192 = 192,
		GLABEL00346 = 346,
		GLABEL00348 = 348,
		GLABEL00350 = 350,
		GLABEL00352 = 352,
		TOLERANCE = 359,
		GLABEL00364 = 364,
		GLABEL00372 = 372,
		GLABEL00373 = 373,
		GLABEL00376 = 376,
		GLABEL00377 = 377,
		GLABEL00380 = 380,
		GLABEL00393 = 393,
		PART_COUNT_SET = 390,
		PART_COUNT_CURRENT = 391,
		PRG_VALUE_PERCENT = 392,
		TOLERANCE_LEVEL = 394,
		SP_VALUE = 418,
		FIFTH_VALUE = 419,
		FOURTH_VALUE = 420,
		Z_VALUE = 421,
		Y_VALUE = 422,
		X_VALUE = 431,
		GNCPLCBUTTON00347 = 347,
		GNCPLCBUTTON00349 = 349,
		GNCPLCBUTTON00351 = 351,
		GNCPLCBUTTON00353 = 353,
		GNCPLCBUTTON00424 = 424,
		GNCPLCBUTTON00425 = 425,
		GNCPLCBUTTON00426 = 426,
		GNCPLCBUTTON00427 = 427,
		GNCPLCBUTTON00428 = 428,
		TOOL_LIFE_TOOL_NO = 433,
		TOOL_LIFE_SET = 434,
		TOOL_LIFE_CURRENT = 435,
		GNXALARMMESSAGE00027 = 27,
		GNXCOUNTER00354 = 354,
		GNXFEEDRATE00356 = 356,
		GNXMONITORSTATUS00029 = 29,
		GNXONB00355 = 355,
		GNXPRGBUFF00369 = 369,
		GNXSPCOMMAND00357 = 357,
		GNXTIME00028 = 28,
		GPICTURE00038 = 38,
		ICON1 = 440,
		ICON2 = 441,
		ICON3 = 442,
		ICON4 = 443,
		ICON5 = 444,
		ICON6 = 445,
		ICON7 = 446,
		TOOL_LIFE = 150,
		PART_COUNT = 151,
		PRG_STATUS = 152,
		TOLERANCE_BAR = 363,
		FOURTH_GREEN_PROGRESS = 342,
		FOURTH_YELLOW_PROGRESS = 395,
		FOURTH_RED_PROGRESS = 396,
		X_GREEN_PROGRESS = 398,
		X_YELLOW_PROGRESS = 399,
		X_RED_PROGRESS = 400,
		Y_GREEN_PROGRESS = 402,
		Y_YELLOW_PROGRESS = 403,
		Y_RED_PROGRESS = 404,
		Z_GREEN_PROGRESS = 406,
		Z_YELLOW_PROGRESS = 407,
		Z_RED_PROGRESS = 408,
		FIFTH_GREEN_PROGRESS = 410,
		FIFTH_YELLOW_PROGRESS = 411,
		FIFTH_RED_PROGRESS = 412,
		SP_GREEN_PROGRESS = 414,
		SP_YELLOW_PROGRESS = 415,
		SP_RED_PROGRESS = 416,
		GSLINE00047 = 47,
		GSLINE00147 = 147,
		GSLINE00167 = 167,
		GSLINE00168 = 168,
		GSLINE00177 = 177,
		GSLINE00184 = 184,
		GSLINE00334 = 334,
		GSLINE00335 = 335,
		GSLINE00336 = 336,
		GSLINE00337 = 337,
		GSLINE00370 = 370,
		GSLINE00371 = 371,
		GSRECT00174 = 174,
		GSRECT00157 = 157,
		GSRECT00159 = 159,
		GSRECT00186 = 186,
		GSRECT00193 = 193,
		GSRECT00236 = 236,
		GSRECT00237 = 237,
		GSRECT00238 = 238,
		GSRECT00358 = 358,
		MSGBOX = 31,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHomeScreen1();
	virtual ~GCHomeScreen1();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DOWNTIMEDATAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_EXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD


	short Cursor_Pos;
    bool bDownTimeDataWindowOpened;


	void SetCursor(short cur_pos);
	void ClearWarningMessage();
	void ScreenTransition(short ScreenNo);
	void DisableButtonName();
	long User(long lLParam, long lUParam);
	void EnableButtonName();
	//void ReadIconStatus(int i);
	void ReadIconStatus();
	void ReadProgressBarStatus();

	short sToolTypeArray[14];


protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCHomeScreen1( GBaseObject *pObject );
short GCINewGCHomeScreen1( GBaseObject *pObject );
}
#endif /* _GCHOMESCREEN1_HPP_ */


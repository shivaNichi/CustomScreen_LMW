#if !defined _GCMAGLIST_HPP_
#define _GCMAGLIST_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMaglist : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_POT_SEARCH = 123,
		KEY_TOOL_SEARCH = 124,
		KEY_SET_BUTTON = 125,
		KEY_MAGAZINE_CLEAR = 126,
		KEY_POT_LOCK = 127,
		KEY_TOOL_CLEAR = 128,
		KEY_HELP_WINDOW = 129,
		KEY_CANCEL_BUTTON = 130,
		NEXTBUTTON = 131,
		KEY_BACK = 132,
		KEYACTION = 15,
		GLABEL00014 = 14,
		GLABEL00016 = 16,
		GLABEL00018 = 18,
		GLABEL00020 = 20,
		GLABEL00022 = 22,
		GLABEL00024 = 24,
		GLABEL00027 = 27,
		GLABEL00028 = 28,
		GLABEL00029 = 29,
		GLABEL00033 = 33,
		GLABEL00034 = 34,
		GLABEL00035 = 35,
		GLABEL00036 = 36,
		GLABEL00116 = 116,
		GLABEL00119 = 119,
		GLABEL00134 = 134,
		GLABEL00135 = 135,
		RPM = 30,
		FEED = 31,
		XTEXTBOX = 85,
		YTEXTBOX = 87,
		ZTEXTBOX = 88,
		SPTEXTBOX = 89,
		SPINDLETOOL = 17,
		WAITTOOL = 19,
		COMMANDTOOL = 21,
		GRPSQRTOOL = 23,
		CURRENTLOAD = 112,
		GNCPLCTEXTBOX00117 = 117,
		TOOL_MANAGE_TABLE = 0,
		GNXALARMMESSAGE00120 = 120,
		GNXMONITORSTATUS00122 = 122,
		GNXTIME00121 = 121,
		GPICTURE00133 = 133,
		ICON1 = 136,
		ICON2 = 137,
		ICON3 = 138,
		ICON4 = 139,
		ICON5 = 140,
		ICON6 = 141,
		ICON7 = 142,
		P1X = 58,
		P2X = 97,
		P3X = 98,
		P1Y = 99,
		P2Y = 100,
		P3Y = 101,
		P1Z = 102,
		P2Z = 103,
		P3Z = 104,
		P1SP = 105,
		P2SP = 106,
		P3SP = 107,
		GSLINE00038 = 38,
		GSLINE00039 = 39,
		GSLINE00040 = 40,
		GSLINE00041 = 41,
		GSLINE00042 = 42,
		GSLINE00043 = 43,
		GSLINE00045 = 45,
		GSLINE00049 = 49,
		GSLINE00050 = 50,
		GSLINE00051 = 51,
		GSLINE00052 = 52,
		GSLINE00053 = 53,
		GSLINE00054 = 54,
		GSLINE00055 = 55,
		GSLINE00056 = 56,
		GSLINE00044 = 44,
		GSLINE00108 = 108,
		GSLINE00115 = 115,
		STAT1 = 94,
		STAT2 = 95,
		STAT3 = 96,
		HELPBOX = 111,
		MSGBOX = 118,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMaglist();
	virtual ~GCMaglist();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CANCEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_HELP_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MAGAZINE_CLEAROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POT_LOCKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_POT_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_SET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOL_CLEAROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOL_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_MANAGE_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_MANAGE_TABLEOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD


	
	unsigned short usTotToolData[48];
	short sTimerFlg;
	short sHelpFlg;
	struct Bit{
		unsigned short bit : 1;
	}bit_g[12][16];

	void ReadSpindleToolStatusClntType();
	void clearWarningMessage();
	void ClearToolTable();
	void FetchData();
	void setPotNumbers();
	void SplitToolData();
	void PrintToolData();
	void PrintSplitToolData(Bit bit_g[][16]);
	void setWarningMessage(int warnnum);
	short checkInputValue(char *, unsigned short , unsigned short );
	short CheckForLargTool(unsigned short usToolNumIdx);
	short checkDataRange(unsigned short, unsigned short);
	void ModifyData(char *, unsigned short , unsigned short );
	void DisableButtonName();
	void clearHelpMessage();
	void ToolDataHelp(int HlpMsg);
	void InitToolTable();
	void ClearToolData(unsigned short, unsigned short);
	void MagClearData();
	void ClearTable();
	long User(long lLParam, long lUParam);
	void EnableButtonName();
	void ReadIconStatus();
	void ReadProgressBarStatus();

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMaglist( GBaseObject *pObject );
short GCINewGCMaglist( GBaseObject *pObject );
}
#endif /* _GCMAGLIST_HPP_ */


#if !defined _GCLOADTYPE_HPP_
#define _GCLOADTYPE_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"



class GCLoadType : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_TOOL_SEARCH = 6,
		GBUTTON00007 = 7,
		KEY_TEACH_MODE = 8,
		KEY_TREND_VIEW = 9,
		KEY_MARGIN_INPUT = 10,
		KEY_SET_BUTTON = 11,
		KEY_CANCEL_BUTTON = 12,
		KEY_TEACHLOAD_SET = 13,
		KEY_HELP_WINDOW = 14,
		KEY_BACK = 15,
		MARGIN_INPUT = 59,
		MAX_LOAD_RECORD = 61,
		KEYACTION = 53,
		GLABEL00003 = 3,
		GLABEL00024 = 24,
		GLABEL00026 = 26,
		GLABEL00028 = 28,
		GLABEL00030 = 30,
		GLABEL00033 = 33,
		GLABEL00034 = 34,
		GLABEL00035 = 35,
		GLABEL00036 = 36,
		GLABEL00037 = 37,
		GLABEL00054 = 54,
		GLABEL00060 = 60,
		GLABEL00062 = 62,
		GNCDATATEXTBOX00038 = 38,
		GNCDATATEXTBOX00039 = 39,
		GNCDATATEXTBOX00040 = 40,
		GNCDATATEXTBOX00041 = 41,
		GNCPLCTEXTBOX00025 = 25,
		GNCPLCTEXTBOX00027 = 27,
		GNCPLCTEXTBOX00029 = 29,
		GNCPLCTEXTBOX00031 = 31,
		TOOL_MANAGE_TABLE = 16,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 71,
		ICON2 = 72,
		ICON3 = 73,
		ICON4 = 74,
		ICON5 = 75,
		ICON6 = 76,
		ICON7 = 77,
		P3X = 42,
		P1Y = 43,
		P2Y = 44,
		P3Y = 45,
		P1Z = 46,
		P2Z = 47,
		P3Z = 48,
		P1SP = 49,
		P2SP = 50,
		P3SP = 51,
		P1X = 55,
		P2X = 56,
		GSLINE00017 = 17,
		GSLINE00018 = 18,
		GSLINE00019 = 19,
		GSLINE00020 = 20,
		GSLINE00021 = 21,
		GSLINE00022 = 22,
		GSLINE00023 = 23,
		GSLINE00032 = 32,
		MSGBOX = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCLoadType();
	virtual ~GCLoadType();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_CANCEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_HELP_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_MARGIN_INPUTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_SET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TEACHLOAD_SETOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TEACH_MODEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TOOL_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_TREND_VIEWOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_MANAGE_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long TOOL_MANAGE_TABLEOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

	unsigned short usTotToolData[12];
	unsigned short usTotMaxLoadData[12];
	unsigned short usTotMinLoadData[12];
	unsigned short usTotONOFFData[12];
	unsigned short usTotToolTypeData[12];

	union tooldata{				
		 struct {
			unsigned b0:1;
			unsigned b1:1;
			unsigned b2:1;
			unsigned b3:1;
			unsigned b4:1;
			unsigned b5:1;
			unsigned b6:1;
			unsigned b7:1;
			unsigned b8:1;
			unsigned b9:1;
			unsigned b10:1;
			unsigned b11:1;
			unsigned b12:1;
			unsigned b13:1;
			unsigned b14:1;
			unsigned b15:1;
		}bits;
	  unsigned int num;
	}tData;

	short sTimerFlg;
	short sHelpFlg;
	struct Bit{
		unsigned short bit : 1;
	}bit_g[12][16];

	
	unsigned short usTotTool;		// Total Number of Tools
	unsigned short usTotPages;		// Total Nuber of pages
	unsigned short usPotsPerPage;	// Number of Pots Per page
	unsigned short usRemainPots;	// Remaining Pots
	unsigned short usInitIndex[5];	// To store the Starting address of the device
	unsigned short usPageNo;		// Current page number


	char *sToolTypeArray[14];
	
	bool bTeachModeFlag;
	
	
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
	short checkDataRange(unsigned short, unsigned short);
	void ModifyData(char *, unsigned short , unsigned short );
	void DisableButtonName();
	void InitToolTable();
	void ClearTable();
	long User(long lLParam, long lUParam);
	void EnableButtonName();
	void ReadIconStatus();
	void ReadProgressBarStatus();

	void TeachModeProcess();
	bool ToolSearch(char *cInputData);
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCLoadType( GBaseObject *pObject );
short GCINewGCLoadType( GBaseObject *pObject );
}
#endif /* _GCLOADTYPE_HPP_ */


#if !defined _GCINITSCREEN_HPP_
#define _GCINITSCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCINITSCREEN : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 27,
		BDBTN1 = 51,
		BUTTONIOLIST = 0,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		BUTTONGCODE = 4,
		BUTTONMCODE = 5,
		BUTTONALARM = 6,
		BUTTONIOLISTL = 7,
		GBUTTON00008 = 8,
		HOMEBTN = 9,
		BUTTONSYSINFO = 40,
		DPBTN1 = 41,
		BDBTN2 = 52,
		DPBTN2 = 53,
		BDBTN3 = 54,
		DPBTN3 = 55,
		BDBTN4 = 56,
		DPBTN4 = 57,
		BDBTN6 = 76,
		DPBTN6 = 77,
		BDBTN7 = 78,
		DPBTN7 = 79,
		BDBTN8 = 80,
		DPBTN8 = 81,
		BDBTN9 = 82,
		DPBTN9 = 83,
		BDBTN10 = 84,
		DPBTN10 = 85,
		BDBTN11 = 86,
		DPBTN11 = 87,
		BDBTN12 = 88,
		DPBTN12 = 89,
		BDBTN13 = 90,
		DPBTN13 = 91,
		BDBTN5 = 92,
		DPBTN5 = 93,
		GLABEL00012 = 12,
		GLABEL00030 = 30,
		GNCDATATEXTBOX00094 = 94,
		GNXMONITORSTATUS00021 = 21,
		GNXTIME00029 = 29,
		GSLINE00031 = 31,
		GSRECT00042 = 42,
		MSGBOX = 28,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCINITSCREEN();
	virtual ~GCINITSCREEN();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN10OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN11OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN12OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN13OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN2OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN3OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN4OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN5OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN6OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN7OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN8OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DPBTN9OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void CopyFiles(int btncursor);
	void setWarningMessage(int warnnum,char *name);
	void ScreenTransition(short ScreenNo);
	void clearWarningMessage();
	void setSelectButton();
	void CopyFile1(char *sName);
	short Cursor;
	void setColorButton(int btncursor);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCINITSCREEN( GBaseObject *pObject );
short GCINewGCINITSCREEN( GBaseObject *pObject );
}
#endif /* _GCINITSCREEN_HPP_ */


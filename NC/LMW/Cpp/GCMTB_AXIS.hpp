#if !defined _GCMTB_AXIS_HPP_
#define _GCMTB_AXIS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMTB_AXIS : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNENABLE = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		BTNSPORIENT = 4,
		BTNSPSPEED = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		BTNHOME = 9,
		CHKBOX1 = 52,
		DATA = 58,
		GLABEL00025 = 25,
		GLABEL00028 = 28,
		GLABEL00037 = 37,
		GLABEL00038 = 38,
		GLABEL00039 = 39,
		GLABEL00040 = 40,
		GLABEL00041 = 41,
		GLABEL00042 = 42,
		GLABEL00045 = 45,
		GLABEL00054 = 54,
		GLABEL00055 = 55,
		GLABEL00064 = 64,
		GLABEL00065 = 65,
		TXT1 = 48,
		TXT2 = 49,
		TXT3 = 50,
		TXT4 = 51,
		TXT5 = 56,
		TXT6 = 57,
		GNCDATATEXTBOX00066 = 66,
		GNXALARMMESSAGE00063 = 63,
		GNXCOUNTER00061 = 61,
		GNXMONITORSTATUS00026 = 26,
		GNXTIME00027 = 27,
		GSLINE00029 = 29,
		GSRECT00024 = 24,
		GSRECT00036 = 36,
		MSGBOX = 59,
		HELP = 60,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMTB_AXIS();
	virtual ~GCMTB_AXIS();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNENABLEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSPORIENTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSPSPEEDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CHKBOX1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

	short Cursor;
	void SetColor(short cur_pos);
	void SetData(short cur_pos);

	#define MAX_TXT 6
	#define DATA_SCRN 2
	 unsigned char ucChkStatus;
	 long GetEditKeyProtection();
	 	void ClearWarningMessage();
	void SetWarningMessage(int warnnum);
	void SetRange(int ScreenNo,short cur_pos);
	long checkRange(char *dat,int ScreenNo, int cellpos);
	void StoreData();



protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMTB_AXIS( GBaseObject *pObject );
short GCINewGCMTB_AXIS( GBaseObject *pObject );
}
#endif /* _GCMTB_AXIS_HPP_ */


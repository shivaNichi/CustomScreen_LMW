#if !defined _GCMTB_SPSPEED_HPP_
#define _GCMTB_SPSPEED_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"




class GCMTB_SPSPEED : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNENABLE = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		BTNAXIS = 4,
		BTNSPORIENT = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		BTNHOME = 9,
		CHKBOX1 = 52,
		DATA = 53,
		GLABEL00025 = 25,
		GLABEL00028 = 28,
		GLABEL00037 = 37,
		GLABEL00038 = 38,
		GLABEL00039 = 39,
		GLABEL00040 = 40,
		GLABEL00041 = 41,
		GLABEL00042 = 42,
		GLABEL00045 = 45,
		GLABEL00062 = 62,
		TXT1 = 48,
		TXT2 = 49,
		TXT3 = 50,
		TXT4 = 51,
		GNCDATATEXTBOX00063 = 63,
		GNXALARMMESSAGE00057 = 57,
		GNXMONITORSTATUS00026 = 26,
		GNXTIME00027 = 27,
		GSLINE00029 = 29,
		GSRECT00024 = 24,
		GSRECT00036 = 36,
		MSGBOX = 54,
		HELP = 55,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMTB_SPSPEED();
	virtual ~GCMTB_SPSPEED();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNAXISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNENABLEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSPORIENTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CHKBOX1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

	short Cursor;
	void SetColor(short cur_pos);
	void SetData(short cur_pos);

	#define MAX_TXT 4
	#define DATA_SCRN 0
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
void GCIDeleteGCMTB_SPSPEED( GBaseObject *pObject );
short GCINewGCMTB_SPSPEED( GBaseObject *pObject );
}
#endif /* _GCMTB_SPSPEED_HPP_ */


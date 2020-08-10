#if !defined _GCMTB_SPORIENTATION_HPP_
#define _GCMTB_SPORIENTATION_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"

class GCMTB_SPORIENTATION : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNENABLE = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		BTNAXIS = 4,
		BTNSPSPEED = 5,
		GBUTTON00006 = 6,
		BTNPROXIM = 7,
		GBUTTON00008 = 8,
		BTNHOME = 9,
		CHKBOX1 = 52,
		CHKBOX2 = 58,
		DATA = 53,
		GLABEL00025 = 25,
		GLABEL00028 = 28,
		GLABEL00037 = 37,
		GLABEL00038 = 38,
		GLABEL00039 = 39,
		GLABEL00040 = 40,
		GLABEL00045 = 45,
		GLABEL00057 = 57,
		GLABEL00059 = 59,
		GLABEL00061 = 61,
		TXT2 = 48,
		TXT1 = 49,
		GNCDATATEXTBOX00062 = 62,
		GNXALARMMESSAGE00056 = 56,
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
	GCMTB_SPORIENTATION();
	virtual ~GCMTB_SPORIENTATION();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNAXISOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNENABLEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNPROXIMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSPSPEEDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CHKBOX1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CHKBOX2OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

	short Cursor;
	void SetColor(short cur_pos);
	void SetData(short cur_pos);

	#define MAX_TXT 1
	#define DATA_SCRN 1
	unsigned char ucChkStatus;

   long GetEditKeyProtection();
	void SetProximity();
	void GetProximity();
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
void GCIDeleteGCMTB_SPORIENTATION( GBaseObject *pObject );
short GCINewGCMTB_SPORIENTATION( GBaseObject *pObject );
}
#endif /* _GCMTB_SPORIENTATION_HPP_ */


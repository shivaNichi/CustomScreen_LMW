#if !defined _GCMTB_PASSWORD_HPP_
#define _GCMTB_PASSWORD_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMTB_PASSWORD : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNSYSINFO = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		GBUTTON00004 = 4,
		GBUTTON00005 = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		BTNMAIN = 9,
		BTN_PASSWORD = 23,
		DATA = 22,
		GLABEL00021 = 21,
		MSGBOX = 25,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMTB_PASSWORD();
	virtual ~GCMTB_PASSWORD();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNMAINOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSYSINFOOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTN_PASSWORDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);
	bool CheckPassword();
	void setWarningMessage(int warnnum);
	


protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMTB_PASSWORD( GBaseObject *pObject );
short GCINewGCMTB_PASSWORD( GBaseObject *pObject );
}
#endif /* _GCMTB_PASSWORD_HPP_ */


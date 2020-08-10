#if !defined _GCMAINSCREEN_HPP_
#define _GCMAINSCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMAINSCREEN : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 27,
		BUTTONIOLIST = 0,
		BUTTONINITIAL = 1,
		GBUTTON00002 = 2,
		MTB_SCREEN = 3,
		BUTTONGCODE = 4,
		BUTTONMCODE = 5,
		BUTTONALARM = 6,
		BUTTONLACHRELAY = 7,
		GBUTTON00008 = 8,
		BUTTONPREVNT = 9,
		GLABEL00030 = 30,
		GPICTURE00029 = 29,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMAINSCREEN();
	virtual ~GCMAINSCREEN();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BUTTONALARMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONGCODEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONINITIALOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONIOLISTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONLACHRELAYOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONMCODEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONPREVNTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long MTB_SCREENOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

		void ScreenTransition(short ScreenNo);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMAINSCREEN( GBaseObject *pObject );
short GCINewGCMAINSCREEN( GBaseObject *pObject );
}
#endif /* _GCMAINSCREEN_HPP_ */


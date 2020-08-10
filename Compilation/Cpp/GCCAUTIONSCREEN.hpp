#if !defined _GCCAUTIONSCREEN_HPP_
#define _GCCAUTIONSCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCCAUTIONSCREEN : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 16,
		BTNPROCEED = 18,
		GLABEL00000 = 0,
		GLABEL00004 = 4,
		GLABEL00012 = 12,
		GLABEL00013 = 13,
		GLABEL00014 = 14,
		GLABEL00015 = 15,
		GNCDATATEXTBOX00019 = 19,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00003 = 3,
		GPICTURE00021 = 21,
		GSLINE00005 = 5,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCCAUTIONSCREEN();
	virtual ~GCCAUTIONSCREEN();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNPROCEEDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCCAUTIONSCREEN( GBaseObject *pObject );
short GCINewGCCAUTIONSCREEN( GBaseObject *pObject );
}
#endif /* _GCCAUTIONSCREEN_HPP_ */


#if !defined _GCLOGOSCREEN_HPP_
#define _GCLOGOSCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCLOGOSCREEN : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 2,
		GLABEL00001 = 1,
		GPICTURE00000 = 0,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCLOGOSCREEN();
	virtual ~GCLOGOSCREEN();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);
	void TimeCalculation();
	long lSettime;

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCLOGOSCREEN( GBaseObject *pObject );
short GCINewGCLOGOSCREEN( GBaseObject *pObject );
}
#endif /* _GCLOGOSCREEN_HPP_ */


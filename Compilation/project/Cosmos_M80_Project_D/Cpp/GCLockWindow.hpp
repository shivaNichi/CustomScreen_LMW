#if !defined _GCLOCKWINDOW_HPP_
#define _GCLOCKWINDOW_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCLockWindow : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEYACTION = 1,
		GLABEL00000 = 0,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCLockWindow();
	virtual ~GCLockWindow();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

	short sStringArray[3];
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCLockWindow( GBaseObject *pObject );
short GCINewGCLockWindow( GBaseObject *pObject );
}
#endif /* _GCLOCKWINDOW_HPP_ */


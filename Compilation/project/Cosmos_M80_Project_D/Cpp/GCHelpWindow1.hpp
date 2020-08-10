#if !defined _GCHELPWINDOW1_HPP_
#define _GCHELPWINDOW1_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHelpWindow1 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEYACTION = 0,
		HELPFRAME = 1,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHelpWindow1();
	virtual ~GCHelpWindow1();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCHelpWindow1( GBaseObject *pObject );
short GCINewGCHelpWindow1( GBaseObject *pObject );
}
#endif /* _GCHELPWINDOW1_HPP_ */


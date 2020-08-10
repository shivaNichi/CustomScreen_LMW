#if !defined _GCCONFIRM_WINDOW_HPP_
#define _GCCONFIRM_WINDOW_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCCONFIRM_WINDOW : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEYACTION = 1,
		GLABEL00000 = 0,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCCONFIRM_WINDOW();
	virtual ~GCCONFIRM_WINDOW();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCCONFIRM_WINDOW( GBaseObject *pObject );
short GCINewGCCONFIRM_WINDOW( GBaseObject *pObject );
}
#endif /* _GCCONFIRM_WINDOW_HPP_ */


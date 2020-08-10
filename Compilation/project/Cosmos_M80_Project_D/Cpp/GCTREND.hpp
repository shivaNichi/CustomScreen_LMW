#if !defined _GCTREND_HPP_
#define _GCTREND_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCTREND : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		MAIN = 62,
		KEYACTION = 84,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		GBUTTON00009 = 9,
		GBUTTON00010 = 10,
		GBUTTON00011 = 11,
		GBUTTON00012 = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		KEY_BACK = 15,
		GLABEL00003 = 3,
		GLABEL00071 = 71,
		GLABEL00072 = 72,
		GLABEL00074 = 74,
		GLABEL00076 = 76,
		GNCTRENDGRAPH00060 = 60,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 77,
		ICON2 = 78,
		ICON3 = 79,
		ICON4 = 80,
		ICON5 = 81,
		ICON6 = 82,
		ICON7 = 83,
		GSLINE00073 = 73,
		GSLINE00075 = 75,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCTREND();
	virtual ~GCTREND();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

	void ReadIconStatus();

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCTREND( GBaseObject *pObject );
short GCINewGCTREND( GBaseObject *pObject );
}
#endif /* _GCTREND_HPP_ */


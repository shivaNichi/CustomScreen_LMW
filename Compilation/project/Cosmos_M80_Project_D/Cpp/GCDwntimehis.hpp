#if !defined _GCDWNTIMEHIS_HPP_
#define _GCDWNTIMEHIS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDwntimehis : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00064 = 64,
		GBUTTON00065 = 65,
		GBUTTON00066 = 66,
		GBUTTON00067 = 67,
		GBUTTON00068 = 68,
		GBUTTON00069 = 69,
		GBUTTON00070 = 70,
		GBUTTON00071 = 71,
		GBUTTON00072 = 72,
		GBUTTON00073 = 73,
		GLABEL00003 = 3,
		GLABEL00018 = 18,
		GLABEL00041 = 41,
		GLABEL00042 = 42,
		GLABEL00043 = 43,
		GLABEL00044 = 44,
		GLABEL00045 = 45,
		GLABEL00046 = 46,
		GLABEL00047 = 47,
		GLABEL00048 = 48,
		GLABEL00049 = 49,
		GLABEL00050 = 50,
		GLABEL00051 = 51,
		GLABEL00052 = 52,
		GLABEL00053 = 53,
		GNCTABLE00016 = 16,
		GNCTABLE00032 = 32,
		GNCTABLE00033 = 33,
		GNCTABLE00034 = 34,
		GNCTABLE00035 = 35,
		GNCTABLE00036 = 36,
		GNCTABLE00037 = 37,
		GNCTABLE00038 = 38,
		GNCTABLE00039 = 39,
		GNCTABLE00040 = 40,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00076 = 76,
		GPICTURE00077 = 77,
		GPICTURE00078 = 78,
		GPICTURE00079 = 79,
		GPICTURE00080 = 80,
		GPICTURE00081 = 81,
		GPICTURE00082 = 82,
		GSRECT00075 = 75,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDwntimehis();
	virtual ~GCDwntimehis();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00032OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00032OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00033OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00033OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00034OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00034OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00035OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00035OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00037OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00037OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00038OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00038OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00039OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00039OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00040OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00040OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCDwntimehis( GBaseObject *pObject );
short GCINewGCDwntimehis( GBaseObject *pObject );
}
#endif /* _GCDWNTIMEHIS_HPP_ */


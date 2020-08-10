#if !defined _GCOEER_HPP_
#define _GCOEER_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCOeeR : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00098 = 98,
		GBUTTON00099 = 99,
		GBUTTON00100 = 100,
		GBUTTON00101 = 101,
		GBUTTON00102 = 102,
		GBUTTON00103 = 103,
		GBUTTON00104 = 104,
		GBUTTON00105 = 105,
		GBUTTON00106 = 106,
		GBUTTON00107 = 107,
		GLABEL00003 = 3,
		GLABEL00018 = 18,
		GLABEL00055 = 55,
		GLABEL00057 = 57,
		GLABEL00058 = 58,
		GLABEL00059 = 59,
		GLABEL00061 = 61,
		GLABEL00066 = 66,
		GLABEL00067 = 67,
		GLABEL00071 = 71,
		GLABEL00076 = 76,
		GNCDATATEXTBOX00064 = 64,
		GNCDATATEXTBOX00068 = 68,
		GNCDATATEXTBOX00069 = 69,
		GNCDATATEXTBOX00072 = 72,
		GNCDATATEXTBOX00077 = 77,
		GNCTABLE00016 = 16,
		GNCTABLE00036 = 36,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00109 = 109,
		GPICTURE00110 = 110,
		GPICTURE00111 = 111,
		GPICTURE00112 = 112,
		GPICTURE00113 = 113,
		GPICTURE00114 = 114,
		GPICTURE00115 = 115,
		GSRECT00054 = 54,
		GSRECT00060 = 60,
		GSRECT00070 = 70,
		GSRECT00075 = 75,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCOeeR();
	virtual ~GCOeeR();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCOeeR( GBaseObject *pObject );
short GCINewGCOeeR( GBaseObject *pObject );
}
#endif /* _GCOEER_HPP_ */


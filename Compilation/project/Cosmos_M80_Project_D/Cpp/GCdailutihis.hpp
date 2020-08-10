#if !defined _GCDAILUTIHIS_HPP_
#define _GCDAILUTIHIS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCdailutihis : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00105 = 105,
		GBUTTON00106 = 106,
		GBUTTON00107 = 107,
		GBUTTON00108 = 108,
		GBUTTON00109 = 109,
		GBUTTON00110 = 110,
		GBUTTON00111 = 111,
		GBUTTON00112 = 112,
		GBUTTON00113 = 113,
		GBUTTON00114 = 114,
		GLABEL00003 = 3,
		GLABEL00018 = 18,
		GLABEL00041 = 41,
		GLABEL00058 = 58,
		GLABEL00059 = 59,
		GLABEL00060 = 60,
		GLABEL00061 = 61,
		GLABEL00065 = 65,
		GLABEL00066 = 66,
		GNCDATATEXTBOX00062 = 62,
		GNCDATATEXTBOX00064 = 64,
		GNCDATATEXTBOX00067 = 67,
		GNCDATATEXTBOX00068 = 68,
		GNCDATATEXTBOX00069 = 69,
		GNCDATATEXTBOX00070 = 70,
		GNCDATATEXTBOX00071 = 71,
		GNCDATATEXTBOX00072 = 72,
		GNCDATATEXTBOX00073 = 73,
		GNCDATATEXTBOX00074 = 74,
		GNCTABLE00016 = 16,
		GNCTABLE00036 = 36,
		GNCTABLE00037 = 37,
		GNCTABLE00038 = 38,
		GNCTABLE00039 = 39,
		GNCTABLE00040 = 40,
		GNCTABLE00054 = 54,
		GNCTABLE00055 = 55,
		GNCTABLE00056 = 56,
		GNCTABLE00057 = 57,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00116 = 116,
		GPICTURE00117 = 117,
		GPICTURE00118 = 118,
		GPICTURE00119 = 119,
		GPICTURE00120 = 120,
		GPICTURE00121 = 121,
		GPICTURE00122 = 122,
		GSRECT00115 = 115,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCdailutihis();
	virtual ~GCdailutihis();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam );
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
	long GNCTABLE00054OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00054OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00055OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00055OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00056OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00056OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00057OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00057OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCdailutihis( GBaseObject *pObject );
short GCINewGCdailutihis( GBaseObject *pObject );
}
#endif /* _GCDAILUTIHIS_HPP_ */


#if !defined _GCOPERSET_HPP_
#define _GCOPERSET_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCOperset : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00057 = 57,
		GBUTTON00058 = 58,
		GBUTTON00059 = 59,
		GBUTTON00060 = 60,
		GBUTTON00061 = 61,
		GBUTTON00062 = 62,
		GBUTTON00063 = 63,
		GBUTTON00064 = 64,
		GBUTTON00065 = 65,
		GBUTTON00066 = 66,
		GINPUTBOX00025 = 25,
		GLABEL00003 = 3,
		GLABEL00017 = 17,
		GLABEL00024 = 24,
		GLABEL00035 = 35,
		GLABEL00038 = 38,
		GLABEL00043 = 43,
		GLABEL00045 = 45,
		GLABEL00048 = 48,
		GLABEL00049 = 49,
		GLABEL00055 = 55,
		GLABEL00067 = 67,
		GNCDATATEXTBOX00041 = 41,
		GNCDATATEXTBOX00042 = 42,
		GNCDATATEXTBOX00044 = 44,
		GNCDATATEXTBOX00046 = 46,
		GNCDATATEXTBOX00050 = 50,
		GNCDATATEXTBOX00056 = 56,
		GNXALARMMESSAGE00000 = 0,
		GNXCYCLETIME00040 = 40,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00077 = 77,
		GPICTURE00078 = 78,
		GPICTURE00079 = 79,
		GPICTURE00080 = 80,
		GPICTURE00081 = 81,
		GPICTURE00082 = 82,
		GPICTURE00083 = 83,
		GSRECT00016 = 16,
		GSRECT00034 = 34,
		GSRECT00047 = 47,
		GTEXTBOX00004 = 4,
		GTEXTBOX00076 = 76,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCOperset();
	virtual ~GCOperset();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GINPUTBOX00025OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00025OnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00025OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCOperset( GBaseObject *pObject );
short GCINewGCOperset( GBaseObject *pObject );
}
#endif /* _GCOPERSET_HPP_ */


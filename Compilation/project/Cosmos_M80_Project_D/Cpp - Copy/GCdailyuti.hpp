#if !defined _GCDAILYUTI_HPP_
#define _GCDAILYUTI_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCdailyuti : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00086 = 86,
		GBUTTON00087 = 87,
		GBUTTON00088 = 88,
		GBUTTON00089 = 89,
		GBUTTON00090 = 90,
		GBUTTON00091 = 91,
		GBUTTON00092 = 92,
		GBUTTON00093 = 93,
		GBUTTON00094 = 94,
		GBUTTON00095 = 95,
		GLABEL00003 = 3,
		GLABEL00018 = 18,
		GLABEL00055 = 55,
		GLABEL00056 = 56,
		GLABEL00057 = 57,
		GLABEL00058 = 58,
		GLABEL00059 = 59,
		GLABEL00061 = 61,
		GLABEL00062 = 62,
		GNCDATATEXTBOX00064 = 64,
		GNCDATATEXTBOX00065 = 65,
		GNCTABLE00016 = 16,
		GNCTABLE00036 = 36,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00096 = 96,
		GPICTURE00097 = 97,
		GPICTURE00098 = 98,
		GPICTURE00099 = 99,
		GPICTURE00100 = 100,
		GPICTURE00101 = 101,
		GPICTURE00102 = 102,
		GSRECT00054 = 54,
		GSRECT00060 = 60,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCdailyuti();
	virtual ~GCdailyuti();

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
void GCIDeleteGCdailyuti( GBaseObject *pObject );
short GCINewGCdailyuti( GBaseObject *pObject );
}
#endif /* _GCDAILYUTI_HPP_ */


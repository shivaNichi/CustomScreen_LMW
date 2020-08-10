#if !defined _GCOEEHIS_HPP_
#define _GCOEEHIS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCOeehis : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00092 = 92,
		GBUTTON00093 = 93,
		GBUTTON00094 = 94,
		GBUTTON00095 = 95,
		GBUTTON00096 = 96,
		GBUTTON00097 = 97,
		GBUTTON00098 = 98,
		GBUTTON00099 = 99,
		GBUTTON00100 = 100,
		GBUTTON00101 = 101,
		GLABEL00003 = 3,
		GLABEL00018 = 18,
		GLABEL00080 = 80,
		GLABEL00106 = 106,
		GNCDATATEXTBOX00081 = 81,
		GNCTABLE00016 = 16,
		GNCTABLE00036 = 36,
		GNCTABLE00037 = 37,
		GNCTABLE00038 = 38,
		GNCTABLE00039 = 39,
		GNCTABLE00040 = 40,
		GNCTABLE00075 = 75,
		GNCTABLE00076 = 76,
		GNCTABLE00077 = 77,
		GNCTABLE00078 = 78,
		GNCTABLE00102 = 102,
		GNCTABLE00103 = 103,
		GNCTABLE00104 = 104,
		GNCTABLE00105 = 105,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00107 = 107,
		GPICTURE00108 = 108,
		GPICTURE00109 = 109,
		GPICTURE00110 = 110,
		GPICTURE00111 = 111,
		GPICTURE00112 = 112,
		GPICTURE00113 = 113,
		GSRECT00079 = 79,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCOeehis();
	virtual ~GCOeehis();

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
	long GNCTABLE00075OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00075OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00076OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00076OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00077OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00077OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00078OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00078OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00102OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00102OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00103OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00103OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00104OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00104OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00105OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00105OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCOeehis( GBaseObject *pObject );
short GCINewGCOeehis( GBaseObject *pObject );
}
#endif /* _GCOEEHIS_HPP_ */


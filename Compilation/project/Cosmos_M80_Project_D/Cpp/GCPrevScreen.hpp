#if !defined _GCPREVSCREEN_HPP_
#define _GCPREVSCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCPrevScreen : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		CNTSTRTBTN = 23,
		CNTSTOPBTN = 24,
		GBUTTON00025 = 25,
		ALLTIMBTN = 26,
		CUTTIMBTN = 27,
		PSWBTN = 28,
		SETBTN = 29,
		CANBTN = 30,
		GBUTTON00031 = 31,
		MAINBTN = 32,
		DATA = 6,
		GLABEL00001 = 1,
		GLABEL00003 = 3,
		GLABEL00007 = 7,
		GLABEL00033 = 33,
		GNCPLCBUTTON00042 = 42,
		GNCPLCBUTTON00050 = 50,
		GNCPLCBUTTON00051 = 51,
		GNCPLCBUTTON00052 = 52,
		GNCPLCBUTTON00053 = 53,
		GNCPLCBUTTON00054 = 54,
		GNCPLCBUTTON00055 = 55,
		GNCPLCBUTTON00056 = 56,
		GNCPLCBUTTON00057 = 57,
		GNCPLCBUTTON00058 = 58,
		MAINTENANCETABLE = 0,
		GNXALARMMESSAGE00009 = 9,
		GNXMONITORSTATUS00011 = 11,
		GNXTIME00010 = 10,
		GPICTURE00012 = 12,
		GPICTURE00034 = 34,
		GPICTURE00035 = 35,
		GPICTURE00036 = 36,
		GPICTURE00037 = 37,
		GPICTURE00038 = 38,
		GPICTURE00039 = 39,
		GPICTURE00040 = 40,
		RANG = 2,
		ALMMSG = 8,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPrevScreen();
	virtual ~GCPrevScreen();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCPrevScreen( GBaseObject *pObject );
short GCINewGCPrevScreen( GBaseObject *pObject );
}
#endif /* _GCPREVSCREEN_HPP_ */


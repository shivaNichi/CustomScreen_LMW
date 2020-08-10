#if !defined _GCALARMHELP_HPP_
#define _GCALARMHELP_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCAlarmhelp : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00018 = 18,
		GBUTTON00019 = 19,
		GBUTTON00020 = 20,
		GBUTTON00021 = 21,
		GBUTTON00022 = 22,
		GBUTTON00023 = 23,
		GBUTTON00024 = 24,
		GBUTTON00025 = 25,
		GBUTTON00026 = 26,
		GBUTTON00027 = 27,
		GHTMLBROWSER00017 = 17,
		GINPUTBOX00029 = 29,
		GLABEL00003 = 3,
		GLABEL00028 = 28,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00030 = 30,
		GPICTURE00031 = 31,
		GPICTURE00032 = 32,
		GPICTURE00033 = 33,
		GPICTURE00034 = 34,
		GPICTURE00035 = 35,
		GPICTURE00036 = 36,
		GTEXTBOX00004 = 4,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCAlarmhelp();
	virtual ~GCAlarmhelp();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GINPUTBOX00029OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00029OnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCAlarmhelp( GBaseObject *pObject );
short GCINewGCAlarmhelp( GBaseObject *pObject );
}
#endif /* _GCALARMHELP_HPP_ */


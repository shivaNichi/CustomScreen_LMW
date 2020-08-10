#if !defined _GCMCCOND_HPP_
#define _GCMCCOND_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMCCond : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		GBUTTON00009 = 9,
		GBUTTON00010 = 10,
		GBUTTON00011 = 11,
		GBUTTON00012 = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		GBUTTON00015 = 15,
		GINPUTBOX00027 = 27,
		GLABEL00003 = 3,
		GLABEL00017 = 17,
		GLABEL00018 = 18,
		GLABEL00019 = 19,
		GLABEL00020 = 20,
		GLABEL00021 = 21,
		GLABEL00023 = 23,
		GLABEL00024 = 24,
		GLABEL00026 = 26,
		GLABEL00028 = 28,
		GLABEL00030 = 30,
		GLABEL00031 = 31,
		GLABEL00032 = 32,
		GNCTABLE00016 = 16,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00034 = 34,
		GPICTURE00035 = 35,
		GPICTURE00036 = 36,
		GPICTURE00037 = 37,
		GPICTURE00038 = 38,
		GPICTURE00039 = 39,
		GPICTURE00040 = 40,
		GSRECT00022 = 22,
		GTEXTBOX00004 = 4,
		GTEXTBOX00025 = 25,
		GTEXTBOX00029 = 29,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMCCond();
	virtual ~GCMCCond();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GINPUTBOX00027OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00027OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00027OnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long GINPUTBOX00027OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMCCond( GBaseObject *pObject );
short GCINewGCMCCond( GBaseObject *pObject );
}
#endif /* _GCMCCOND_HPP_ */


#if !defined _GCBACKUP_HPP_
#define _GCBACKUP_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCBackup : public GCPanel
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
		GINPUTBOX00025 = 25,
		GLABEL00003 = 3,
		GLABEL00017 = 17,
		GLABEL00018 = 18,
		GLABEL00019 = 19,
		GLABEL00024 = 24,
		GLABEL00048 = 48,
		GLABEL00049 = 49,
		GLABEL00052 = 52,
		GLABEL00053 = 53,
		GLABEL00056 = 56,
		GLABEL00059 = 59,
		GLABEL00060 = 60,
		GLABEL00061 = 61,
		GLABEL00062 = 62,
		GLABEL00064 = 64,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		GPICTURE00040 = 40,
		GPICTURE00041 = 41,
		GPICTURE00042 = 42,
		GPICTURE00043 = 43,
		GPICTURE00044 = 44,
		GPICTURE00045 = 45,
		GPICTURE00046 = 46,
		GSRECT00016 = 16,
		GSRECT00057 = 57,
		GTEXTBOX00004 = 4,
		GTEXTBOX00026 = 26,
		GTEXTBOX00027 = 27,
		GTEXTBOX00050 = 50,
		GTEXTBOX00051 = 51,
		GTEXTBOX00054 = 54,
		GTEXTBOX00055 = 55,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCBackup();
	virtual ~GCBackup();

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
void GCIDeleteGCBackup( GBaseObject *pObject );
short GCINewGCBackup( GBaseObject *pObject );
}
#endif /* _GCBACKUP_HPP_ */


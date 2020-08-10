#if !defined _GCSUB_SYSINFO_HPP_
#define _GCSUB_SYSINFO_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCSUB_SysInfo : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 191,
		BTNLUBE = 176,
		GBUTTON00177 = 177,
		BTNSPINDLE = 178,
		BTNHYD = 179,
		BTNCHIP = 180,
		GBUTTON00181 = 181,
		BTNATC = 182,
		BTNCOOL = 183,
		BTNEOS = 184,
		BTNEXIT = 185,
		DBTNLUBE = 186,
		DBTNHYD = 187,
		DBTNCOOL = 188,
		DBTNCHIP = 189,
		DBTNATC = 190,
		DBTNSPINDLE = 193,
		GLABEL00025 = 25,
		GLABEL00156 = 156,
		GLABEL00175 = 175,
		GNCDATATEXTBOX00195 = 195,
		GNCEXMENU00016 = 16,
		GNXMONITORSTATUS00192 = 192,
		GNXTIME00006 = 6,
		GSLINE00047 = 47,
		GSLINE00148 = 148,
		GSLINE00149 = 149,
		GSLINE00150 = 150,
		GSLINE00152 = 152,
		GSLINE00154 = 154,
		GSLINE00194 = 194,
		GSOVAL00144 = 144,
		GSOVAL00155 = 155,
		GSRECT00196 = 196,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCSUB_SysInfo();
	virtual ~GCSUB_SysInfo();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNATCOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNCHIPOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNCOOLOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNHYDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNLUBEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNSPINDLEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNATCOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNCHIPOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNCOOLOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNHYDOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNLUBEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DBTNSPINDLEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCSUB_SysInfo( GBaseObject *pObject );
short GCINewGCSUB_SysInfo( GBaseObject *pObject );
}
#endif /* _GCSUB_SYSINFO_HPP_ */


#if !defined _GCMAINT_HOME_HPP_
#define _GCMAINT_HOME_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMaint_Home : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 222,
		BTNGM = 212,
		BTNPREV = 213,
		GBUTTON00214 = 214,
		GBUTTON00215 = 215,
		BTNALARM = 216,
		BTNPOWER = 217,
		BTNIO = 218,
		BTNTOOL = 219,
		BTNEOS = 220,
		BTNEXIT = 221,
		GLABEL00025 = 25,
		GLABEL00176 = 176,
		GLABEL00177 = 177,
		GLABEL00178 = 178,
		GLABEL00179 = 179,
		GLABEL00180 = 180,
		GLABEL00181 = 181,
		GLABEL00210 = 210,
		GNCDATATEXTBOX00223 = 223,
		GNCEXMENU00016 = 16,
		GNXMONITORSTATUS00211 = 211,
		GNXTIME00006 = 6,
		GPICTURE00170 = 170,
		GPICTURE00171 = 171,
		GPICTURE00172 = 172,
		GPICTURE00173 = 173,
		GPICTURE00174 = 174,
		GPICTURE00175 = 175,
		GSLINE00047 = 47,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMaint_Home();
	virtual ~GCMaint_Home();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNALARMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNGMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNIOOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNPOWEROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNPREVOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMaint_Home( GBaseObject *pObject );
short GCINewGCMaint_Home( GBaseObject *pObject );
}
#endif /* _GCMAINT_HOME_HPP_ */


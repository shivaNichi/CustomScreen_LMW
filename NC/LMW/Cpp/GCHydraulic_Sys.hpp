#if !defined _GCHYDRAULIC_SYS_HPP_
#define _GCHYDRAULIC_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHydraulic_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 221,
		BTN1 = 157,
		BTN2 = 158,
		BTN3 = 159,
		BTN4 = 160,
		BTN5 = 165,
		BTNMC = 211,
		GBUTTON00212 = 212,
		GBUTTON00213 = 213,
		GBUTTON00214 = 214,
		GBUTTON00215 = 215,
		GBUTTON00216 = 216,
		GBUTTON00217 = 217,
		GBUTTON00218 = 218,
		BTNEOS = 219,
		BTNEXIT = 220,
		BTN6 = 222,
		GBUTTON00224 = 224,
		GBUTTON00226 = 226,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00142 = 142,
		GLABEL00143 = 143,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00206 = 206,
		GLABEL00225 = 225,
		GLABEL00227 = 227,
		GLABEL00228 = 228,
		GNCDATATEXTBOX00223 = 223,
		GNXALARMMESSAGE00208 = 208,
		GNXMONITORSTATUS00207 = 207,
		GNXTIME00006 = 6,
		GPICTURE00210 = 210,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00171 = 171,
		MSGBOX = 209,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHydraulic_Sys();
	virtual ~GCHydraulic_Sys();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNMCOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	#define NO_BTN 6
	void ScreenTransition(short ScreenNo);
	void Fetchdata();
	char sAdress[20][10];
	void displaydata();
	bool Readstatus(char *cInputData);
	void setWarningMessage(int warnnum);


protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCHydraulic_Sys( GBaseObject *pObject );
short GCINewGCHydraulic_Sys( GBaseObject *pObject );
}
#endif /* _GCHYDRAULIC_SYS_HPP_ */


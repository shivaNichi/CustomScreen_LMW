#if !defined _GCCHIP_CONVY_SYS_HPP_
#define _GCCHIP_CONVY_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCChip_CONVY_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 222,
		BTN1 = 157,
		BTN2 = 158,
		BTN5 = 165,
		BTN6 = 166,
		BTNMC = 212,
		GBUTTON00213 = 213,
		GBUTTON00214 = 214,
		GBUTTON00215 = 215,
		GBUTTON00216 = 216,
		GBUTTON00217 = 217,
		GBUTTON00218 = 218,
		GBUTTON00219 = 219,
		BTNEOS = 220,
		BTNEXIT = 221,
		BTN3 = 225,
		BTN4 = 226,
		BTN8 = 228,
		BTN7 = 230,
		GBUTTON00232 = 232,
		GBUTTON00234 = 234,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00152 = 152,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00207 = 207,
		GLABEL00223 = 223,
		GLABEL00224 = 224,
		GLABEL00229 = 229,
		GLABEL00233 = 233,
		GLABEL00235 = 235,
		GLABEL00236 = 236,
		GNCDATATEXTBOX00231 = 231,
		GNXALARMMESSAGE00209 = 209,
		GNXMONITORSTATUS00208 = 208,
		GNXTIME00006 = 6,
		GPICTURE00211 = 211,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00171 = 171,
		MSGBOX = 210,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCChip_CONVY_Sys();
	virtual ~GCChip_CONVY_Sys();

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
	#define NO_BTN 7
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
void GCIDeleteGCChip_CONVY_Sys( GBaseObject *pObject );
short GCINewGCChip_CONVY_Sys( GBaseObject *pObject );
}
#endif /* _GCCHIP_CONVY_SYS_HPP_ */


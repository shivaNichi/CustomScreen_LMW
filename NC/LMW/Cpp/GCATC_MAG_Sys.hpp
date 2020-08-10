#if !defined _GCATC_MAG_SYS_HPP_
#define _GCATC_MAG_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCATC_MAG_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 211,
		BTN1 = 157,
		BTN2 = 158,
		BTN3 = 159,
		BTN4 = 163,
		BTN5 = 165,
		BTN6 = 166,
		BTN7 = 167,
		BTNARM = 200,
		GBUTTON00201 = 201,
		GBUTTON00202 = 202,
		GBUTTON00203 = 203,
		GBUTTON00204 = 204,
		GBUTTON00205 = 205,
		GBUTTON00206 = 206,
		GBUTTON00207 = 207,
		BTNEOS = 208,
		BTNEXIT = 209,
		BTN12 = 210,
		BTN8 = 212,
		BTN9 = 213,
		BTN10 = 214,
		BTN11 = 215,
		BTN13 = 216,
		BTN14 = 218,
		GBUTTON00220 = 220,
		GBUTTON00222 = 222,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00142 = 142,
		GLABEL00146 = 146,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00152 = 152,
		GLABEL00153 = 153,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00195 = 195,
		GLABEL00221 = 221,
		GLABEL00223 = 223,
		GNCDATATEXTBOX00219 = 219,
		GNCEXMENU00016 = 16,
		GNXALARMMESSAGE00197 = 197,
		GNXMONITORSTATUS00196 = 196,
		GNXTIME00006 = 6,
		GPICTURE00199 = 199,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00171 = 171,
		MSGBOX = 198,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCATC_MAG_Sys();
	virtual ~GCATC_MAG_Sys();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNARMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	#define NO_BTN 14
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
void GCIDeleteGCATC_MAG_Sys( GBaseObject *pObject );
short GCINewGCATC_MAG_Sys( GBaseObject *pObject );
}
#endif /* _GCATC_MAG_SYS_HPP_ */


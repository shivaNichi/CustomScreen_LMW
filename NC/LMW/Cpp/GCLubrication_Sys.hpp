#if !defined _GCLUBRICATION_SYS_HPP_
#define _GCLUBRICATION_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCLubrication_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 217,
		BTN1 = 157,
		BTN2 = 158,
		BTN3 = 159,
		BTN4 = 160,
		BTN5 = 161,
		BTN6 = 165,
		BTNMC = 207,
		GBUTTON00208 = 208,
		GBUTTON00209 = 209,
		GBUTTON00210 = 210,
		GBUTTON00211 = 211,
		GBUTTON00212 = 212,
		GBUTTON00213 = 213,
		GBUTTON00214 = 214,
		BTNEOS = 215,
		BTNEXIT = 216,
		BTN7 = 222,
		GBUTTON00224 = 224,
		GBUTTON00226 = 226,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00142 = 142,
		GLABEL00143 = 143,
		GLABEL00144 = 144,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00206 = 206,
		GLABEL00225 = 225,
		GLABEL00227 = 227,
		GLABEL00228 = 228,
		GNCDATATEXTBOX00223 = 223,
		GNCEXMENU00016 = 16,
		GNXALARMMESSAGE00220 = 220,
		GNXMONITORSTATUS00218 = 218,
		GNXTIME00006 = 6,
		GPICTURE00221 = 221,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00171 = 171,
		MSGBOX = 219,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCLubrication_Sys();
	virtual ~GCLubrication_Sys();

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
void GCIDeleteGCLubrication_Sys( GBaseObject *pObject );
short GCINewGCLubrication_Sys( GBaseObject *pObject );
}
#endif /* _GCLUBRICATION_SYS_HPP_ */


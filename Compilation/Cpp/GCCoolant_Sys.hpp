#if !defined _GCCOOLANT_SYS_HPP_
#define _GCCOOLANT_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCCoolant_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 198,
		BTN1 = 157,
		BTN2 = 158,
		BTN3 = 159,
		BTN4 = 160,
		BTN5 = 161,
		BTN7 = 165,
		BTN8 = 166,
		BTN9 = 167,
		BTNMC = 188,
		GBUTTON00189 = 189,
		GBUTTON00190 = 190,
		GBUTTON00191 = 191,
		GBUTTON00192 = 192,
		GBUTTON00193 = 193,
		GBUTTON00194 = 194,
		GBUTTON00195 = 195,
		BTNEOS = 196,
		BTNEXIT = 197,
		BTN6 = 206,
		BTN10 = 207,
		BTN11 = 209,
		BTN14 = 210,
		BTN13 = 211,
		BTN12 = 212,
		GBUTTON00214 = 214,
		GBUTTON00216 = 216,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00142 = 142,
		GLABEL00143 = 143,
		GLABEL00144 = 144,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00152 = 152,
		GLABEL00153 = 153,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00187 = 187,
		GLABEL00204 = 204,
		GLABEL00205 = 205,
		GLABEL00215 = 215,
		GLABEL00217 = 217,
		GLABEL00218 = 218,
		GNCDATATEXTBOX00213 = 213,
		GNCEXMENU00016 = 16,
		GNXALARMMESSAGE00202 = 202,
		GNXMONITORSTATUS00200 = 200,
		GNXTIME00006 = 6,
		GPICTURE00199 = 199,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSLINE00203 = 203,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00171 = 171,
		MSGBOX = 201,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCCoolant_Sys();
	virtual ~GCCoolant_Sys();

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
void GCIDeleteGCCoolant_Sys( GBaseObject *pObject );
short GCINewGCCoolant_Sys( GBaseObject *pObject );
}
#endif /* _GCCOOLANT_SYS_HPP_ */


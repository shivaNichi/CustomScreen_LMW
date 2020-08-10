#if !defined _GCATC_ARM_SYS_HPP_
#define _GCATC_ARM_SYS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCATC_ARM_Sys : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 217,
		BTN1 = 157,
		BTN2 = 158,
		BTN3 = 159,
		BTN4 = 165,
		BTN5 = 166,
		BTNMAG = 201,
		GBUTTON00202 = 202,
		GBUTTON00203 = 203,
		GBUTTON00204 = 204,
		GBUTTON00205 = 205,
		GBUTTON00206 = 206,
		GBUTTON00207 = 207,
		GBUTTON00208 = 208,
		BTNEOS = 209,
		BTNEXIT = 210,
		BTN8 = 213,
		BTN9 = 214,
		BTN10 = 215,
		BTN6 = 218,
		BTN7 = 219,
		GBUTTON00221 = 221,
		GBUTTON00223 = 223,
		GLABEL00025 = 25,
		GLABEL00140 = 140,
		GLABEL00141 = 141,
		GLABEL00142 = 142,
		GLABEL00150 = 150,
		GLABEL00151 = 151,
		GLABEL00152 = 152,
		GLABEL00170 = 170,
		GLABEL00173 = 173,
		GLABEL00196 = 196,
		GLABEL00222 = 222,
		GLABEL00224 = 224,
		GNCDATATEXTBOX00220 = 220,
		GNCEXMENU00016 = 16,
		GNXALARMMESSAGE00198 = 198,
		GNXMONITORSTATUS00197 = 197,
		GNXTIME00006 = 6,
		GPICTURE00212 = 212,
		GSLINE00047 = 47,
		GSLINE00138 = 138,
		GSLINE00148 = 148,
		GSRECT00139 = 139,
		GSRECT00149 = 149,
		GSRECT00211 = 211,
		MSGBOX = 199,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCATC_ARM_Sys();
	virtual ~GCATC_ARM_Sys();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNMAGOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	#define NO_BTN 10
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
void GCIDeleteGCATC_ARM_Sys( GBaseObject *pObject );
short GCINewGCATC_ARM_Sys( GBaseObject *pObject );
}
#endif /* _GCATC_ARM_SYS_HPP_ */


#if !defined _GCATC_INFO_HPP_
#define _GCATC_INFO_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCATC_Info : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BASE1 = 126,
		DATA = 138,
		BTN1 = 101,
		BTN2 = 102,
		BTN3 = 103,
		BTN4 = 104,
		BTN5 = 105,
		BTN6 = 106,
		BTN7 = 107,
		BTN8 = 108,
		BTN9 = 109,
		BTN10 = 110,
		BTN11 = 111,
		BTN12 = 112,
		BTN13 = 113,
		GBUTTON00128 = 128,
		GBUTTON00129 = 129,
		GBUTTON00130 = 130,
		GBUTTON00131 = 131,
		GBUTTON00132 = 132,
		GBUTTON00133 = 133,
		GBUTTON00134 = 134,
		GBUTTON00135 = 135,
		GBUTTON00136 = 136,
		GBUTTON00137 = 137,
		BTN14 = 140,
		BTN15 = 141,
		BTN16 = 142,
		BTN17 = 143,
		GLABEL00025 = 25,
		GLABEL00075 = 75,
		GLABEL00076 = 76,
		GLABEL00077 = 77,
		GLABEL00078 = 78,
		GLABEL00079 = 79,
		GLABEL00080 = 80,
		GLABEL00081 = 81,
		GLABEL00082 = 82,
		GLABEL00083 = 83,
		GLABEL00086 = 86,
		GLABEL00087 = 87,
		GLABEL00088 = 88,
		GLABEL00089 = 89,
		GLABEL00090 = 90,
		GLABEL00091 = 91,
		GLABEL00095 = 95,
		GLABEL00098 = 98,
		GLABEL00127 = 127,
		GNCEXMENU00016 = 16,
		GNCPLCTEXTBOX00069 = 69,
		GNCPLCTEXTBOX00071 = 71,
		GNCPLCTEXTBOX00073 = 73,
		GNXALARMMESSAGE00146 = 146,
		GNXMONITORSTATUS00144 = 144,
		GNXTIME00006 = 6,
		GPICTURE00139 = 139,
		GSLINE00046 = 46,
		GSLINE00047 = 47,
		GSLINE00070 = 70,
		GSLINE00072 = 72,
		GSLINE00084 = 84,
		GSRECT00068 = 68,
		GSRECT00074 = 74,
		GSRECT00085 = 85,
		GSRECT00096 = 96,
		MSGBOX = 145,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCATC_Info();
	virtual ~GCATC_Info();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	#define NO_BTN 17
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
void GCIDeleteGCATC_Info( GBaseObject *pObject );
short GCINewGCATC_Info( GBaseObject *pObject );
}
#endif /* _GCATC_INFO_HPP_ */


#if !defined _GCSPINDLE_STATUS_HPP_
#define _GCSPINDLE_STATUS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCSPINDLE_Status : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 230,
		BTN1 = 198,
		BTN2 = 199,
		BTN3 = 200,
		BTNMC = 220,
		GBUTTON00221 = 221,
		GBUTTON00222 = 222,
		GBUTTON00223 = 223,
		GBUTTON00224 = 224,
		GBUTTON00225 = 225,
		GBUTTON00226 = 226,
		GBUTTON00227 = 227,
		BTNEOS = 228,
		BTNEXIT = 229,
		GBUTTON00242 = 242,
		GBUTTON00244 = 244,
		GLABEL00025 = 25,
		GLABEL00165 = 165,
		GLABEL00169 = 169,
		GLABEL00172 = 172,
		GLABEL00174 = 174,
		GLABEL00179 = 179,
		GLABEL00181 = 181,
		GLABEL00186 = 186,
		GLABEL00187 = 187,
		GLABEL00188 = 188,
		GLABEL00191 = 191,
		GLABEL00192 = 192,
		GLABEL00193 = 193,
		GLABEL00194 = 194,
		GLABEL00201 = 201,
		GLABEL00202 = 202,
		GLABEL00215 = 215,
		GLABEL00243 = 243,
		GLABEL00245 = 245,
		GNCDATATEXTBOX00231 = 231,
		GNCDATATEXTBOX00232 = 232,
		GNCDATATEXTBOX00233 = 233,
		GNCDATATEXTBOX00241 = 241,
		GNCEXMENU00016 = 16,
		GNCMETER00176 = 176,
		GNCMETER00177 = 177,
		GNCPLCTEXTBOX00164 = 164,
		GNCPLCTEXTBOX00168 = 168,
		GNCPLCTEXTBOX00180 = 180,
		GNXMONITORSTATUS00216 = 216,
		GNXTIME00006 = 6,
		ICON2 = 218,
		ICON1 = 219,
		GSLINE00047 = 47,
		GSRECT00163 = 163,
		GSRECT00238 = 238,
		GSRECT00239 = 239,
		GSRECT00162 = 162,
		GSRECT00240 = 240,
		GSRECT00236 = 236,
		GSRECT00237 = 237,
		GSRECT00235 = 235,
		GSRECT00234 = 234,
		GSRECT00178 = 178,
		GSRECT00190 = 190,
		MSGBOX = 217,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCSPINDLE_Status();
	virtual ~GCSPINDLE_Status();

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
	#define NO_BTN 3
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
void GCIDeleteGCSPINDLE_Status( GBaseObject *pObject );
short GCINewGCSPINDLE_Status( GBaseObject *pObject );
}
#endif /* _GCSPINDLE_STATUS_HPP_ */


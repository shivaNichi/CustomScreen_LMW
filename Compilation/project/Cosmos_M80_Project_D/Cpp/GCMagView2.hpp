#if !defined _GCMAGVIEW2_HPP_
#define _GCMAGVIEW2_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCMagView2 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 137,
		KEY_BACK = 15,
		GLABEL00003 = 3,
		GLABEL00098 = 98,
		GLABEL00123 = 123,
		GNCDATATEXTBOX00073 = 73,
		GNCDATATEXTBOX00074 = 74,
		GNCDATATEXTBOX00075 = 75,
		GNCDATATEXTBOX00076 = 76,
		GNCDATATEXTBOX00077 = 77,
		GNCDATATEXTBOX00078 = 78,
		GNCDATATEXTBOX00079 = 79,
		GNCDATATEXTBOX00080 = 80,
		GNCDATATEXTBOX00081 = 81,
		GNCDATATEXTBOX00082 = 82,
		GNCDATATEXTBOX00083 = 83,
		GNCDATATEXTBOX00084 = 84,
		GNCDATATEXTBOX00085 = 85,
		GNCDATATEXTBOX00086 = 86,
		GNCDATATEXTBOX00087 = 87,
		GNCDATATEXTBOX00088 = 88,
		GNCDATATEXTBOX00089 = 89,
		GNCDATATEXTBOX00090 = 90,
		GNCDATATEXTBOX00091 = 91,
		GNCDATATEXTBOX00092 = 92,
		GNCDATATEXTBOX00093 = 93,
		GNCDATATEXTBOX00094 = 94,
		GNCDATATEXTBOX00095 = 95,
		GNCDATATEXTBOX00096 = 96,
		GNCDATATEXTBOX00097 = 97,
		GNCPLCBUTTON00125 = 125,
		POT_POS = 124,
		GNXALARMMESSAGE00000 = 0,
		GPICTURE00005 = 5,
		GPICTURE00072 = 72,
		POT1 = 99,
		POT2 = 100,
		POT3 = 101,
		POT4 = 102,
		POT5 = 103,
		POT6 = 104,
		POT7 = 105,
		POT8 = 106,
		POT9 = 107,
		POT10 = 108,
		POT11 = 109,
		POT12 = 110,
		POT13 = 111,
		POT14 = 112,
		POT24 = 113,
		POT21 = 114,
		POT18 = 115,
		POT17 = 116,
		POT16 = 117,
		POT15 = 118,
		POT19 = 119,
		POT22 = 120,
		POT20 = 121,
		POT23 = 122,
		ICON1 = 129,
		ICON2 = 130,
		ICON3 = 131,
		ICON4 = 132,
		ICON5 = 133,
		ICON6 = 134,
		ICON7 = 135,
		GSOVAL00128 = 128,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMagView2();
	virtual ~GCMagView2();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

	void ReadIconStatus();
	//void ReadPotStatus(int k);
	void ReadPotStatus();
	GBaseObject *pPotStatus[24];
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMagView2( GBaseObject *pObject );
short GCINewGCMagView2( GBaseObject *pObject );
}
#endif /* _GCMAGVIEW2_HPP_ */


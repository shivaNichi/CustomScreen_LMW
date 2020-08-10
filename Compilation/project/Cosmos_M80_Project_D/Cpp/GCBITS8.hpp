#if !defined _GCBITS8_HPP_
#define _GCBITS8_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"



class GCBITS8 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00113 = 113,
		KEY_SET_0 = 114,
		KEY_SET_1 = 115,
		GBUTTON00116 = 116,
		GBUTTON00117 = 117,
		GBUTTON00118 = 118,
		GBUTTON00119 = 119,
		GBUTTON00120 = 120,
		KEY_DIAG_SCREEN = 121,
		KEY_BACK = 122,
		T1 = 155,
		T2 = 156,
		T3 = 157,
		T4 = 158,
		T5 = 159,
		T6 = 160,
		T7 = 161,
		T8 = 162,
		GLABEL00003 = 3,
		GLABEL00054 = 54,
		GLABEL00057 = 57,
		GLABEL00061 = 61,
		GLABEL00064 = 64,
		GLABEL00067 = 67,
		GLABEL00070 = 70,
		GLABEL00073 = 73,
		GLABEL00076 = 76,
		GLABEL00079 = 79,
		GLABEL00082 = 82,
		GLABEL00084 = 84,
		GLABEL00086 = 86,
		GLABEL00087 = 87,
		GLABEL00092 = 92,
		GLABEL00094 = 94,
		GLABEL00096 = 96,
		GLABEL00098 = 98,
		GLABEL00100 = 100,
		GLABEL00109 = 109,
		GLABEL00110 = 110,
		GLABEL00111 = 111,
		GLABEL00124 = 124,
		GLABEL00126 = 126,
		GLABEL00128 = 128,
		GLABEL00130 = 130,
		GLABEL00132 = 132,
		GLABEL00134 = 134,
		GLABEL00136 = 136,
		GLABEL00138 = 138,
		GLABEL00139 = 139,
		GNCDATATEXTBOX00055 = 55,
		GNCPLCBUTTON00101 = 101,
		GNCPLCBUTTON00102 = 102,
		GNCPLCBUTTON00103 = 103,
		GNCPLCBUTTON00104 = 104,
		GNCPLCBUTTON00105 = 105,
		GNCPLCBUTTON00106 = 106,
		GNCPLCBUTTON00107 = 107,
		GNCPLCBUTTON00108 = 108,
		GNXALARMMESSAGE00000 = 0,
		GNXMONITORSTATUS00002 = 2,
		GNXTIME00001 = 1,
		GPICTURE00005 = 5,
		ICON1 = 148,
		ICON2 = 149,
		ICON3 = 150,
		ICON4 = 151,
		ICON5 = 152,
		ICON6 = 153,
		ICON7 = 154,
		GSLINE00056 = 56,
		GSLINE00060 = 60,
		GSLINE00063 = 63,
		GSLINE00066 = 66,
		GSLINE00069 = 69,
		GSLINE00072 = 72,
		GSLINE00075 = 75,
		GSLINE00078 = 78,
		GSLINE00089 = 89,
		GSRECT00080 = 80,
		GSRECT00081 = 81,
		GSRECT00083 = 83,
		GSRECT00085 = 85,
		GSRECT00091 = 91,
		GSRECT00093 = 93,
		GSRECT00095 = 95,
		GSRECT00097 = 97,
		GSRECT00123 = 123,
		GSRECT00125 = 125,
		GSRECT00127 = 127,
		GSRECT00129 = 129,
		GSRECT00131 = 131,
		GSRECT00133 = 133,
		GSRECT00135 = 135,
		GSRECT00137 = 137,
		MSGBOX = 4,
		KEYACTION = 99,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCBITS8();
	virtual ~GCBITS8();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAG_SCREENOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_SET_0OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_SET_1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T1OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T2OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T3OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T4OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T5OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T6OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T7OnClick(unsigned short usMessage, long lLParam, long lUParam );
	long T8OnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	union tooldata{				
		 struct {
			unsigned b0:1;
			unsigned b1:1;
			unsigned b2:1;
			unsigned b3:1;
			unsigned b4:1;
			unsigned b5:1;
			unsigned b6:1;
			unsigned b7:1;
			unsigned b8:1;
			unsigned b9:1;
			unsigned b10:1;
			unsigned b11:1;
			unsigned b12:1;
			unsigned b13:1;
			unsigned b14:1;
			unsigned b15:1;
		}bits;
	  unsigned int num;
	}tData;

	short Cursor_Pos;

	void SetCursor(short cur_pos);
	void ClearWarningMessage();
	void ReadIconStatus();
	void SetWarningMessage(int warnnum);
	void DisplayBits();
	void SetValueZero();
	void SetValueOne();
	bool CheckPassword();
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCBITS8( GBaseObject *pObject );
short GCINewGCBITS8( GBaseObject *pObject );
}
#endif /* _GCBITS8_HPP_ */


#if !defined _GCBITS2_HPP_
#define _GCBITS2_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCBITS2 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00138 = 138,
		KEY_SET_0 = 139,
		KEY_SET_1 = 140,
		GBUTTON00141 = 141,
		GBUTTON00142 = 142,
		GBUTTON00143 = 143,
		GBUTTON00144 = 144,
		KEY_NEXT = 145,
		KEY_DIAG_SCREEN = 146,
		KEY_BACK = 147,
		T1 = 156,
		T2 = 157,
		T3 = 158,
		T4 = 159,
		T5 = 160,
		T6 = 161,
		T7 = 162,
		T8 = 163,
		GLABEL00003 = 3,
		GLABEL00054 = 54,
		GLABEL00079 = 79,
		GLABEL00082 = 82,
		GLABEL00084 = 84,
		GLABEL00086 = 86,
		GLABEL00092 = 92,
		GLABEL00094 = 94,
		GLABEL00096 = 96,
		GLABEL00098 = 98,
		GLABEL00100 = 100,
		GLABEL00109 = 109,
		GLABEL00110 = 110,
		GLABEL00111 = 111,
		GLABEL00113 = 113,
		GLABEL00114 = 114,
		GLABEL00115 = 115,
		GLABEL00116 = 116,
		GLABEL00117 = 117,
		GLABEL00118 = 118,
		GLABEL00119 = 119,
		GLABEL00120 = 120,
		GLABEL00121 = 121,
		GLABEL00123 = 123,
		GLABEL00125 = 125,
		GLABEL00127 = 127,
		GLABEL00129 = 129,
		GLABEL00131 = 131,
		GLABEL00133 = 133,
		GLABEL00135 = 135,
		GLABEL00137 = 137,
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
		GSRECT00122 = 122,
		GSRECT00124 = 124,
		GSRECT00126 = 126,
		GSRECT00128 = 128,
		GSRECT00130 = 130,
		GSRECT00132 = 132,
		GSRECT00134 = 134,
		GSRECT00136 = 136,
		MSGBOX = 4,
		KEYACTION = 99,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCBITS2();
	virtual ~GCBITS2();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_DIAG_SCREENOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_NEXTOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
void GCIDeleteGCBITS2( GBaseObject *pObject );
short GCINewGCBITS2( GBaseObject *pObject );
}
#endif /* _GCBITS2_HPP_ */


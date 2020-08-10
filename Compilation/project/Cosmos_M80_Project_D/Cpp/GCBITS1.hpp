#if !defined _GCBITS1_HPP_
#define _GCBITS1_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"



class GCBITS1 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00006 = 6,
		KEY_SET_0 = 7,
		KEY_SET_1 = 8,
		GBUTTON00009 = 9,
		GBUTTON00010 = 10,
		GBUTTON00011 = 11,
		GBUTTON00012 = 12,
		KEY_NEXT = 13,
		KEY_DIAG_SCREEN = 14,
		KEY_BACK = 15,
		T1 = 154,
		T2 = 155,
		T3 = 156,
		T4 = 157,
		T5 = 158,
		T6 = 159,
		T7 = 160,
		T8 = 161,
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
		GLABEL00116 = 116,
		GLABEL00117 = 117,
		GLABEL00121 = 121,
		GLABEL00124 = 124,
		GLABEL00126 = 126,
		GLABEL00129 = 129,
		GLABEL00131 = 131,
		GLABEL00133 = 133,
		GLABEL00135 = 135,
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
		ICON1 = 144,
		ICON2 = 145,
		ICON3 = 146,
		ICON4 = 147,
		ICON5 = 148,
		ICON6 = 149,
		ICON7 = 150,
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
		GSRECT00118 = 118,
		GSRECT00120 = 120,
		GSRECT00123 = 123,
		GSRECT00125 = 125,
		GSRECT00128 = 128,
		GSRECT00130 = 130,
		GSRECT00132 = 132,
		GSRECT00134 = 134,
		MSGBOX = 4,
		KEYACTION = 99,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCBITS1();
	virtual ~GCBITS1();

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
void GCIDeleteGCBITS1( GBaseObject *pObject );
short GCINewGCBITS1( GBaseObject *pObject );
}
#endif /* _GCBITS1_HPP_ */


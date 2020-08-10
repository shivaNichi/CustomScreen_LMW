#if !defined _GCPREVENTIVE_MAINT_HPP_
#define _GCPREVENTIVE_MAINT_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


struct Date 
{ 
    int d, m, y; 
}; 

class GCPreventive_Maint : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00010 = 10,
		GBUTTON00011 = 11,
		GBUTTON00012 = 12,
		GBUTTON00013 = 13,
		GBUTTON00014 = 14,
		GBUTTON00015 = 15,
		GBUTTON00016 = 16,
		BTNRESET = 106,
		BUTTONHOME = 107,
		GBUTTON00117 = 117,
		GBUTTON00118 = 118,
		GBUTTON00119 = 119,
		GBUTTON00120 = 120,
		GBUTTON00121 = 121,
		GBUTTON00122 = 122,
		GBUTTON00123 = 123,
		DATA = 85,
		GLABEL00097 = 97,
		GLABEL00033 = 33,
		GLABEL00034 = 34,
		GLABEL00035 = 35,
		GLABEL00036 = 36,
		GLABEL00037 = 37,
		GLABEL00038 = 38,
		GLABEL00039 = 39,
		GLABEL00040 = 40,
		GLABEL00041 = 41,
		GLABEL00086 = 86,
		GLABEL00087 = 87,
		GLABEL00088 = 88,
		GLABEL00089 = 89,
		GLABEL00090 = 90,
		GLABEL00091 = 91,
		GLABEL00092 = 92,
		GLABEL00093 = 93,
		GLABEL00094 = 94,
		GLABEL00109 = 109,
		GNCDATATEXTBOX00124 = 124,
		GNCEXMENU00070 = 70,
		GNCMETER00009 = 9,
		GNCMETER00026 = 26,
		GNCMETER00027 = 27,
		GNCMETER00028 = 28,
		GNCMETER00029 = 29,
		GNCMETER00030 = 30,
		GNCMETER00031 = 31,
		GNCMETER00032 = 32,
		GNCMETER00042 = 42,
		BUTTONEXIT = 75,
		GNXMONITORSTATUS00071 = 71,
		GNXTIME00108 = 108,
		GSLINE00110 = 110,
		GTEXTBOX00000 = 0,
		GTEXTBOX00001 = 1,
		GTEXTBOX00002 = 2,
		GTEXTBOX00003 = 3,
		GTEXTBOX00004 = 4,
		GTEXTBOX00005 = 5,
		GTEXTBOX00006 = 6,
		GTEXTBOX00007 = 7,
		GTEXTBOX00008 = 8,
		T1 = 17,
		T5 = 18,
		T8 = 19,
		T4 = 20,
		T3 = 21,
		T2 = 22,
		T7 = 23,
		T9 = 24,
		T6 = 25,
		TS1 = 43,
		TS3 = 44,
		TS4 = 45,
		TS5 = 46,
		TS6 = 47,
		TS7 = 48,
		TS8 = 49,
		TS9 = 50,
		C1 = 51,
		C2 = 52,
		C3 = 53,
		C4 = 54,
		C5 = 55,
		C6 = 56,
		C7 = 57,
		C8 = 58,
		C9 = 59,
		P1 = 60,
		P2 = 61,
		P3 = 62,
		P4 = 63,
		P5 = 64,
		P6 = 65,
		P7 = 66,
		P8 = 67,
		P9 = 68,
		TS2 = 69,
		MSGBOX = 84,
		TXTINPUT = 105,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPreventive_Maint();
	virtual ~GCPreventive_Maint();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNRESETOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONEXITOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	short Cursor;
	void SetColor(short cur_pos);
	void SetData(short cur_pos);
	void Startbtn();
	void StorePreventTableData();
	void FetchPreventTableData();
	long SetPowerTime[10];
	long SetPowerDate[10];
	long RemTime[10];
	int nUnit[10];
	void setWarningMessage(int warnnum);
	void SetRemainingTime();
	void SetStatus();
	bool CheckPassword();
	long User(long lLParam, long lUParam);
	bool bResetFlag;
	void clearWarningMessage();
	void clearData();
	bool bReseScreen;
	bool bClearDataFlag;
	
	void ScreenTransition(short ScreenNo);

	bool isLeap(int y);
	int offsetDays(int d, int m, int y);
	void revoffsetDays(int offset, int y, int *d, int *m);
	long addDays( int x) ;
	 int countLeapYears(Date d);
	 int getDifference(Date dt1, Date dt2) ;
	 Date dates[2];
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCPreventive_Maint( GBaseObject *pObject );
short GCINewGCPreventive_Maint( GBaseObject *pObject );
}
#endif /* _GCPREVENTIVE_MAINT_HPP_ */


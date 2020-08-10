#if !defined _GCPOWER_CALC2_HPP_
#define _GCPOWER_CALC2_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCPower_Calc2 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		PBASE = 260,
		BTNCALCUL = 279,
		BTNALLCLEAR = 280,
		BTNMAINTE = 281,
		GBUTTON00282 = 282,
		GBUTTON00283 = 283,
		GBUTTON00284 = 284,
		GBUTTON00285 = 285,
		BTNCALCULSCREEN = 286,
		BTNEOS = 287,
		BTNEXIT = 288,
		DATA = 294,
		GLABEL00025 = 25,
		GLABEL00165 = 165,
		GLABEL00167 = 167,
		GLABEL00172 = 172,
		GLABEL00174 = 174,
		GLABEL00180 = 180,
		GLABEL00189 = 189,
		GLABEL00196 = 196,
		GLABEL00197 = 197,
		GLABEL00205 = 205,
		GLABEL00207 = 207,
		GLABEL00275 = 275,
		GLABEL00293 = 293,
		GNCDATATEXTBOX00295 = 295,
		GNCEXMENU00016 = 16,
		GNXALARMMESSAGE00277 = 277,
		GNXMONITORSTATUS00276 = 276,
		GNXTIME00006 = 6,
		GSLINE00047 = 47,
		GSRECT00162 = 162,
		GSRECT00163 = 163,
		GSRECT00164 = 164,
		GSRECT00169 = 169,
		GSRECT00173 = 173,
		MSGBOX = 278,
		TXT1 = 290,
		TXT2 = 291,
		TXTO1 = 292,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPower_Calc2();
	virtual ~GCPower_Calc2();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNALLCLEAROnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNCALCULOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNCALCULSCREENOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNMAINTEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);
	void AllClear();
	void Calculation();
	short Cursor;
	#define MAX_TXT 2
	void SetColor(short cur_pos);
	void SetWarningMessage(int warnnum);
	void ClearWarningMessage();
	void SetData(short cur_pos);
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCPower_Calc2( GBaseObject *pObject );
short GCINewGCPower_Calc2( GBaseObject *pObject );
}
#endif /* _GCPOWER_CALC2_HPP_ */


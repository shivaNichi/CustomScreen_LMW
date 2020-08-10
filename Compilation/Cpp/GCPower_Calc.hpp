#if !defined _GCPOWER_CALC_HPP_
#define _GCPOWER_CALC_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCPower_Calc : public GCPanel
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
		DATA = 297,
		GLABEL00025 = 25,
		GLABEL00165 = 165,
		GLABEL00167 = 167,
		GLABEL00172 = 172,
		GLABEL00174 = 174,
		GLABEL00180 = 180,
		GLABEL00189 = 189,
		GLABEL00192 = 192,
		GLABEL00197 = 197,
		GLABEL00198 = 198,
		GLABEL00202 = 202,
		GLABEL00206 = 206,
		GLABEL00275 = 275,
		GLABEL00290 = 290,
		GLABEL00296 = 296,
		GNCDATATEXTBOX00298 = 298,
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
		TXT1 = 291,
		TXT3 = 293,
		TXTO1 = 294,
		TXT2 = 295,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCPower_Calc();
	virtual ~GCPower_Calc();

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
	#define MAX_TXT 3
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
void GCIDeleteGCPower_Calc( GBaseObject *pObject );
short GCINewGCPower_Calc( GBaseObject *pObject );
}
#endif /* _GCPOWER_CALC_HPP_ */


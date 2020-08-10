#if !defined _GCEOS_HPP_
#define _GCEOS_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCEOS : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		MAIN = 202,
		KEYACTION = 205,
		DATA = 216,
		BTNGM = 206,
		GBUTTON00207 = 207,
		GBUTTON00208 = 208,
		BTNCANN = 209,
		BTNMAINTE = 210,
		BTNTOOL = 211,
		BTNINIT = 212,
		BTNATC = 213,
		BTNMC = 214,
		BTNEXIT = 215,
		GLABEL00024 = 24,
		GLABEL00025 = 25,
		GLABEL00116 = 116,
		GLABEL00117 = 117,
		GLABEL00118 = 118,
		GLABEL00145 = 145,
		GLABEL00152 = 152,
		GLABEL00163 = 163,
		GLABEL00169 = 169,
		GLABEL00170 = 170,
		GLABEL00171 = 171,
		GLABEL00172 = 172,
		GLABEL00173 = 173,
		GLABEL00179 = 179,
		GLABEL00181 = 181,
		GLABEL00183 = 183,
		GLABEL00185 = 185,
		GNCDATATEXTBOX00223 = 223,
		GNCDATATEXTBOX00224 = 224,
		GNCDATATEXTBOX00226 = 226,
		GNCDATATEXTBOX00227 = 227,
		GNCDATATEXTBOX00228 = 228,
		GNCMETER00107 = 107,
		GNCMETER00108 = 108,
		GNCMETER00109 = 109,
		GNCMETER00142 = 142,
		GNCMETER00147 = 147,
		GNCMETER00157 = 157,
		GNCMETER00158 = 158,
		GNCMETER00159 = 159,
		GNCMETER00160 = 160,
		GNCMETER00161 = 161,
		GNCMETER00168 = 168,
		GNCPLCTEXTBOX00120 = 120,
		GNCPLCTEXTBOX00121 = 121,
		GNCPLCTEXTBOX00122 = 122,
		GNCPLCTEXTBOX00178 = 178,
		GNCPLCTEXTBOX00180 = 180,
		GNXALARMMESSAGE00125 = 125,
		GNXCOUNTER00086 = 86,
		GNXCOUNTER00078 = 78,
		GNXCOUNTER00080 = 80,
		GNXCOUNTER00083 = 83,
		GNXGMODALSIMPLE00140 = 140,
		GNXMONITORSTATUS00123 = 123,
		GNXONB00141 = 141,
		GNXPRGBUFF00138 = 138,
		GNXTIME00006 = 6,
		ICON2 = 176,
		ICON1 = 177,
		GSLINE00074 = 74,
		GSLINE00077 = 77,
		GSLINE00082 = 82,
		GSLINE00085 = 85,
		GSLINE00088 = 88,
		GSLINE00095 = 95,
		GSLINE00102 = 102,
		GSLINE00105 = 105,
		GSLINE00110 = 110,
		GSLINE00111 = 111,
		GSLINE00112 = 112,
		GSLINE00113 = 113,
		GSLINE00114 = 114,
		GSLINE00115 = 115,
		GSLINE00143 = 143,
		GSLINE00144 = 144,
		GSLINE00148 = 148,
		GSLINE00149 = 149,
		GSRECT00225 = 225,
		GSRECT00184 = 184,
		GSRECT00091 = 91,
		GSRECT00092 = 92,
		GSRECT00106 = 106,
		GSRECT00139 = 139,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCEOS();
	virtual ~GCEOS();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNGMOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNINITOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNMAINTEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNMCOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BTNTOOLOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void ScreenTransition(short ScreenNo);

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCEOS( GBaseObject *pObject );
short GCINewGCEOS( GBaseObject *pObject );
}
#endif /* _GCEOS_HPP_ */


#if !defined _GCMTB_SYSINFO_HPP_
#define _GCMTB_SYSINFO_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"

struct SysInfo
{
	char Name[50];
	char Comment[50];
	//char Remedy[60];

};


class GCMTB_SYSINFO : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 58,
		BTNENABLE = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		BTNAXIS = 4,
		BTNSPORIENT = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		BTNHOME = 9,
		GLABEL00025 = 25,
		GLABEL00028 = 28,
		GNCDATATEXTBOX00084 = 84,
		TBLINFO = 83,
		GNXMONITORSTATUS00026 = 26,
		GNXTIME00027 = 27,
		GSLINE00029 = 29,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCMTB_SYSINFO();
	virtual ~GCMTB_SYSINFO();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
	void LoadData();
	void ScreenTransition(short ScreenNo);
	void Fetchdata(long sOffset=0);
	 SysInfo lSysInfo[20];
protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCMTB_SYSINFO( GBaseObject *pObject );
short GCINewGCMTB_SYSINFO( GBaseObject *pObject );
}
#endif /* _GCMTB_SYSINFO_HPP_ */


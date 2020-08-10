#if !defined _GCGCODE_HPP_
#define _GCGCODE_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"

#define	START_POINT					0
#define TABLEROW_SIZE				15

struct GcodeDet
{
	char Adress[6];
	char Comment[60];
	//char Remedy[60];

};



class GCGCODE : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 27,
		BTNMCODE = 0,
		GBUTTON00001 = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		GBUTTON00004 = 4,
		GBUTTON00005 = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		HOMEBTN = 9,
		GLABEL00012 = 12,
		GLABEL00029 = 29,
		GNCDATATEXTBOX00037 = 37,
		HIST_TABLE = 26,
		GNXMONITORSTATUS00021 = 21,
		GNXTIME00028 = 28,
		GSLINE00030 = 30,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCGCODE();
	virtual ~GCGCODE();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNMCODEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

		void UpdateStatus();
	bool Readstatus(char *cInputData);
	void Fetchdata(long sOffset=0);
	void displaydata();
	char* Fetchcomment(char *cAdrss);
	void LoadHtmlFile(char *cAdrss);
	//char sAdress[30][3][60];
		
		void ScreenTransition(short ScreenNo);
		long ulIndex;  
		long ulLineCcount;
	//	long ulLineCcountXL;// Row Col Count
		long ulLineCcountinit;
		long uCommentCount;
		long usRCcount; // Row Col Count
		long lEndCnt;
		void ClearTable();
		char sAdress[20][200];

		GcodeDet SMcodeDet[2060];
		int AlarmOnbit[2060];

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCGCODE( GBaseObject *pObject );
short GCINewGCGCODE( GBaseObject *pObject );
}
#endif /* _GCGCODE_HPP_ */


#if !defined _GCALARMHIST_HPP_
#define _GCALARMHIST_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"

#define	START_POINT					0
#define TABLEROW_SIZE				15

struct AlarmDataHist
{
	char Adress[6];
	char Comment[60];
	//char Remedy[60];

};



class GCALARMHIST : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		DATA = 28,
		PRVNTBTN = 0,
		INTBTN = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		GCODEBTN = 4,
		MCODEBTN = 5,
		LATCHBTN = 6,
		IOLSTBTN = 7,
		GBUTTON00008 = 8,
		HOMEBTN = 9,
		HTMLBROWSER = 27,
		GLABEL00012 = 12,
		GLABEL00031 = 31,
		GLABEL00029 = 29,
		GNCDATATEXTBOX00039 = 39,
		HIST_TABLE = 26,
		GNXMONITORSTATUS00021 = 21,
		GNXTIME00030 = 30,
		GSLINE00032 = 32,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCALARMHIST();
	virtual ~GCALARMHIST();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long GCODEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long INTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long IOLSTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long LATCHBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long MCODEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long PRVNTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
		long ulLineCcountXL;// Row Col Count
		long ulLineCcountinit;
		long uCommentCount;
		long usRCcount; // Row Col Count
		long lEndCnt;
		void ClearTable();
		char sAdress[20][200];

		AlarmDataHist SAlarmDataHist[2060];
		int AlarmOnbit[2060];

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCALARMHIST( GBaseObject *pObject );
short GCINewGCALARMHIST( GBaseObject *pObject );
}
#endif /* _GCALARMHIST_HPP_ */


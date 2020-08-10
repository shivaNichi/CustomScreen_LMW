#if !defined _GCINOUTXY_HPP_
#define _GCINOUTXY_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"

#define	START_POINT					0
#define TABLEROW_SIZE				15

struct CommentsData
{
	char Adress[8];
	char comment[30];
	

};
class GCINOUTXY : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNLATCH = 0,
		BUTTONDELETE = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		GBUTTON00004 = 4,
		GBUTTON00005 = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		BUTTONHOME = 9,
		DATA = 25,
		GLABEL00012 = 12,
		GLABEL00027 = 27,
		GLABEL00029 = 29,
		GNCDATATEXTBOX00037 = 37,
		HIST_TABLE = 26,
		GNXMONITORSTATUS00021 = 21,
		GNXTIME00028 = 28,
		GSLINE00030 = 30,
		MSGBOX = 23,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCINOUTXY();
	virtual ~GCINOUTXY();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNLATCHOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONDELETEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long BUTTONHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD
			long checkRange(char *dat, int cellpos);
		long checkAdress(char *dat);
		void setWarningMessage(int warnnum);
		void clearWarningMessage();
		void Fetchdata();
		void WriteNewBit(char *sAdd);
		void ScreenTransition(short ScreenNo);
		long ulIndex;  
		long ulLineCcount; // Row Col Count
		long uCommentCount;
		long usRCcount; // Row Col Count
		long lEndCnt;
		char sAdress[200][10];
		void displaydata();
		bool Readstatus(char *cInputData);
		CommentsData *sCommentsData;
		void GetSamplingData( CommentsData *sCommentData, long usIdx);
		void SetSamplingData( CommentsData *sCommentData, long usIdx);
		void DeleteAdress(int Cursor);
		void UpdateStatus();
		void ClearTable();


protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCINOUTXY( GBaseObject *pObject );
short GCINewGCINOUTXY( GBaseObject *pObject );
}
#endif /* _GCINOUTXY_HPP_ */


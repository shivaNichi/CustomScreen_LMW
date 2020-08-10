#if !defined _GCINOUTL_HPP_
#define _GCINOUTL_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


#define	START_POINT					0
#define TABLEROW_SIZE				15

struct CommentsDatal
{
	char Adress[8];
	char comment[30];
	

};
class GCINOUTL : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		BTNIOLIST = 0,
		DELETBTN = 1,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		OFFBTN = 4,
		ONBTN = 5,
		CHANGESTATUSBTN = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		HOMEBTN = 9,
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
	GCINOUTL();
	virtual ~GCINOUTL();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long BTNIOLISTOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long CHANGESTATUSBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	long DELETBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long OFFBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
	long ONBTNOnClick(unsigned short usMessage, long lLParam, long lUParam );
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
		CommentsDatal *sCommentsData;
		void GetSamplingData( CommentsDatal *sCommentData, long usIdx);
		void SetSamplingData( CommentsDatal *sCommentData, long usIdx);
		void DeleteAdress(int Cursor);
		bool CheckPassword();
		void changeStatus(long Bit);
		//bool bSetPasswordOn;
	//	bool bSetPasswordOn1;
		void ClearTable();
		void UpdateStatus();
	
		
		

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCINOUTL( GBaseObject *pObject );
short GCINewGCINOUTL( GBaseObject *pObject );
}
#endif /* _GCINOUTL_HPP_ */


#include "GCMTB_PASSWORD.hpp"
#include "GCBasicControl.hpp"
#include "GCButton.hpp"
#include "GCCheckBox.hpp"
#include "GCLabel.hpp"
#include "GCList.hpp"
#include "GCPicture.hpp"
#include "GCProgressBar.hpp"
#include "GCRadioButton.hpp"
#include "GCTextBox.hpp"
#include "GCSampleScreen.hpp"
#include "GEvent.h"
#include "GResource.h"

#include "Common.h"

extern "C"
{

void GCIDeleteGCMTB_PASSWORD( GBaseObject *pObject )
{
	GCMTB_PASSWORD *pPanel = (GCMTB_PASSWORD*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMTB_PASSWORD( GBaseObject *pObject )
{
	GCMTB_PASSWORD *pPanel = new GCMTB_PASSWORD;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMTB_PASSWORD;
	pPanel->SetGBaseObject( pObject );
	return TRUE;
}
}
/*
 *	<summary>		:	コンストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	コンストラクタ
 */
GCMTB_PASSWORD::GCMTB_PASSWORD()
{
}

/*
 *	<summary>		:	デストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	デストラクタ
 */
GCMTB_PASSWORD::~GCMTB_PASSWORD()
{

}

#include "GCMTB_PASSWORD.prc"

short GCMTB_PASSWORD::CreateChildren( )
{
	GBaseObject *pChild;

	unsigned int i;
	for( i = 1; i < sizeof(pProperty)/sizeof(GBaseWindowProperty*); i++ ){
		pChild = GCSCreateInstance( GCSGetScreen( m_pSelf ),
							pProperty[i]->usType, pProperty[i], GetGBaseObject() );
		if( pChild ){
			AddChild( pChild );
			GCSCreate( pChild, GetGBaseObject() );
		}
	}
	return TRUE;
}

GPropertyInfo* GCMTB_PASSWORD::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMTB_PASSWORD::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMTB_PASSWORD::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
		switch(lLParam)
	{
		case GK_F1:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				}
				else
			ScreenTransition(MTB_SYSINFO);
		break;
		case GK_RETURN:
		if(CheckPassword()==0)
			ScreenTransition(MTB_SPSPEED);
		else
				setWarningMessage(5);

			break;
		case GK_F10:
			ScreenTransition(EOS_SCREEN);
		break;

			default:
			break;
		}
	return TRUE;
}

long GCMTB_PASSWORD::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	return TRUE;
}



bool GCMTB_PASSWORD::CheckPassword()
{

	GBaseObject *pChild;
	long lPass=0;
	char operData[WARN_MSG_DATA_SIZE];
	GTCHAR inpBuffPwd[WARN_MSG_DATA_SIZE];
	char lFixedPassword[WARN_MSG_DATA_SIZE]="MPARA";
	


	pChild = GCSGetChild(GetGBaseObject(), DATA);


	GCSTextboxGetString( pChild, inpBuffPwd, sizeof(inpBuffPwd)/sizeof(GTCHAR) );
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), operData, inpBuffPwd, sizeof(operData));


	if(strcmp( lFixedPassword,operData)==0)
	{
		return 0;
	}
	else
	{
	
	return 1;
	}
		

}
void GCMTB_PASSWORD::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Cannot Start. Maintenance item is not defined",	sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 2)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File Access Error", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 3)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File Corrupted", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 4)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Out Of Range Error", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 5)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Enter Correct Password", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 6)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Enter Password", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 7)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Cannot Start. Hours item is not defined", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 8)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Cannot Start. Type item is not defined", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 9)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Maintainence Item Name Should be more than 2 Characters", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 10)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data Out of Range, Data Range is 1 to 32767 hours", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 11)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Edit is Key is OFF, not possible to Reset/Delete", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 12)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Login Succesful", sizeof(szText)/sizeof(GTCHAR));
	


	GCSTextboxSetString( pLbl, szText );
}
void GCMTB_PASSWORD::ScreenTransition(short ScreenNo)
{

	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

long GCMTB_PASSWORD::BTN_PASSWORDOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(CheckPassword()==0)
			ScreenTransition(MTB_SPSPEED);
		else
				setWarningMessage(5);
	return TRUE;
}

long GCMTB_PASSWORD::BTNMAINOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCMTB_PASSWORD::BTNSYSINFOOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MTB_SYSINFO);
	return TRUE;
}

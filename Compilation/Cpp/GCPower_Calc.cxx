#include "GCPower_Calc.hpp"
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

void GCIDeleteGCPower_Calc( GBaseObject *pObject )
{
	GCPower_Calc *pPanel = (GCPower_Calc*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCPower_Calc( GBaseObject *pObject )
{
	GCPower_Calc *pPanel = new GCPower_Calc;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCPower_Calc;
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
GCPower_Calc::GCPower_Calc()
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
GCPower_Calc::~GCPower_Calc()
{

}

#include "GCPower_Calc.prc"

short GCPower_Calc::CreateChildren( )
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

GPropertyInfo* GCPower_Calc::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}




long GCPower_Calc::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=0;
	SetColor(Cursor);
	return TRUE;
}

long GCPower_Calc::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	short sCursorNum = MAX_TXT-1;
	GBaseObject *pLbl,*pHelp,*pData,*pChkBox;
	//pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	pData = GCSGetChild(GetGBaseObject(), DATA);
	switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
			
				else
					Calculation();
					
			break;
		case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			else
				ScreenTransition( POWER_SCREEN2);
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
		/*	else
				ScreenTransition( INOUTXY_SCREEN);*/
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			/*else
				ScreenTransition( POWER_SCREEN);*/
					
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		/*else
			ScreenTransition( ALARM_SCREEN);*/
		
			
		break;
		case GK_F6:			
			AllClear();
			break;
		//case GK_F7:			
		//	
		//		
		//		// Changing the screen to home screen.
		//		ScreenTransition( INIT_SCREEN);
		//	
		//break;
		case GK_F8:			
			
				
				
			ScreenTransition( MAINTAIN_HOME_SCREEN);
			
		break;
		case GK_F9:			
				
			ScreenTransition(EOS_SCREEN);
			
		break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			case GK_DOWN:
			// Down arrow button operation
			
				Cursor++;
				if(Cursor > sCursorNum){
					Cursor = 0;
				
					}

				SetColor(Cursor);
				ClearWarningMessage();
			
			
			break;
		case GK_UP:
			// Up arrow button operation
		
				if(Cursor > 0)
				{
					Cursor--;
				}
				SetColor(Cursor);
				ClearWarningMessage();
				
			break;
		case GK_RETURN:
			SetData(Cursor);
			break;
		default:
			break;
		}
	return TRUE;
}

long GCPower_Calc::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;
		
	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	}


	
	
	return TRUE;
}

void GCPower_Calc::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCPower_Calc::AllClear()
{
		GBaseObject *pTxtB[10],*pPanel,*pData;
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];

	
		pPanel = GetGBaseObject();
		pData = GCSGetChild(pPanel, DATA);
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
		pTxtB[3] = GCSGetChild(pPanel, TXTO1);


		for(int i=0;i<4;i++)
		{
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "0", sizeof(inpBuff)/sizeof(GTCHAR));
		GCSTextboxSetString(pTxtB[i],inpBuff);
		}
	
	
}
void GCPower_Calc::Calculation()
{
	GBaseObject *pTxtB[10],*pPanel,*pData;
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	char cInputData[PREVENTIVE_INPUT_SIZE];
	DOUBLE lOutput=1;
	
	pPanel = GetGBaseObject();
		pData = GCSGetChild(pPanel, DATA);
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
		pTxtB[3] = GCSGetChild(pPanel, TXTO1);

			for(int i=0;i<3;i++)
		{
		
		GCSTextboxGetString(pTxtB[i], inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
		lOutput*=atof(cInputData) ;

		}
		lOutput=lOutput/1000;
		sprintf(cInputData,"%f",lOutput);
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, sizeof(cInputData));
		GCSTextboxSetString(pTxtB[3],inpBuff);
	
}
void GCPower_Calc::SetColor(short cur_pos)
{
	GBaseObject *pTxtB[MAX_TXT],*pPanel,*pHelp;

//	pHelp = GCSGetChild(GetGBaseObject(), HELP);


	short sCursorNum = MAX_TXT;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
	//	pTxtB[3] = GCSGetChild(pPanel, TXT4);
		//pTxtB[4] = GCSGetChild(pPanel, TXT5);
	//	pTxtB[5] = GCSGetChild(pPanel, TXT6);
		//pTxtB[6] = GCSGetChild(pPanel, TXT7);
		//pTxtB[7] = GCSGetChild(pPanel, TXT8);
		//pTxtB[8] = GCSGetChild(pPanel, TXT9);
		//pTxtB[9] = GCSGetChild(pPanel, TXT10);
		
		GCSTextboxSetNormalColor(pTxtB[0] , DEFAULT_COLOR);
		GCSTextboxSetNormalColor(pTxtB[1] , DEFAULT_COLOR);		
		GCSTextboxSetNormalColor(pTxtB[2] , DEFAULT_COLOR);		
	//	GCSNCDataTextboxSetNormalColor(pTxtB[3] , DEFAULT_COLOR);	
	//	GCSTextboxSetNormalColor(pTxtB[4] , DEFAULT_COLOR);		
	//	GCSTextboxSetNormalColor(pTxtB[5] , DEFAULT_COLOR);		
		//GCSTextboxSetNormalColor(pTxtB[6] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[7] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[8] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[9] , DEFAULT_COLOR);	
		GCSTextboxSetNormalColor(pTxtB[cur_pos] , CURSOR_COLOR);

	//	SetRange(DATA_SCRN,Cursor);


}
void GCPower_Calc::SetData(short cur_pos)
{
	GBaseObject *pTxtB[10],*pPanel,*pData;
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	char cInputData[PREVENTIVE_INPUT_SIZE];

	
	pPanel = GetGBaseObject();
		pData = GCSGetChild(pPanel, DATA);
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);


		
		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
		if(atoi(cInputData)>0)
		{
		GCSTextboxSetString(pTxtB[cur_pos],inpBuff);
		GCSTextboxSetString(pData,(GTCHAR *)"");
		ClearWarningMessage();
		}
		else
			SetWarningMessage(1);
	
	
	
}
void GCPower_Calc::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter the value Gretaer than zero",	sizeof(szText)/sizeof(GTCHAR));
		


	GCSTextboxSetString( pLbl, szText );
}
void GCPower_Calc::ClearWarningMessage()
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "", sizeof(szText)/sizeof(GTCHAR));
	


	GCSTextboxSetString( pLbl, szText );

}

long GCPower_Calc::BTNALLCLEAROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	AllClear();
	return TRUE;
}

long GCPower_Calc::BTNCALCULOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Calculation();
	return TRUE;
}

long GCPower_Calc::BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCPower_Calc::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		ScreenTransition( HMI_SCREEN);
	return TRUE;
}

long GCPower_Calc::BTNMAINTEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( MAINTAIN_HOME_SCREEN);
	return TRUE;
}

long GCPower_Calc::BTNCALCULSCREENOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( POWER_SCREEN2);
	return TRUE;
}

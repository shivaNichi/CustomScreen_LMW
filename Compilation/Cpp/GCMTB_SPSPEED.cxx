#include "GCMTB_SPSPEED.hpp"
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

void GCIDeleteGCMTB_SPSPEED( GBaseObject *pObject )
{
	GCMTB_SPSPEED *pPanel = (GCMTB_SPSPEED*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMTB_SPSPEED( GBaseObject *pObject )
{
	GCMTB_SPSPEED *pPanel = new GCMTB_SPSPEED;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMTB_SPSPEED;
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
GCMTB_SPSPEED::GCMTB_SPSPEED()
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
GCMTB_SPSPEED::~GCMTB_SPSPEED()
{

}

#include "GCMTB_SPSPEED.prc"

short GCMTB_SPSPEED::CreateChildren( )
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

GPropertyInfo* GCMTB_SPSPEED::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMTB_SPSPEED::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor=0;
	SetColor(Cursor);
	ucChkStatus=0;
	
	return TRUE;
}

long GCMTB_SPSPEED::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{

		short sCursorNum = MAX_TXT-1;
	GBaseObject *pLbl,*pHelp,*pData,*pChkBox;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	pData = GCSGetChild(GetGBaseObject(), DATA);
		pChkBox = GCSGetChild(GetGBaseObject(), CHKBOX1);
		

	switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				//GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), DIAG_SCREEN, 0), FALSE);
				}
				else
				{
					ucChkStatus=!ucChkStatus;
					GCSCheckboxSetStatus(pChkBox,ucChkStatus);
				}
				break;

		case GK_RETURN:
		/*case GK_F2:*/
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				//GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), DIAG_SCREEN, 0), FALSE);
				}
				else
					if(GetEditKeyProtection()==1)
					{
					if(ucChkStatus==1)
					SetData(Cursor);
					else
					SetWarningMessage(17);
					}
					else
					SetWarningMessage(18);
			break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				}
				else
				ScreenTransition(MTB_SPORIENT);
				break;
		case GK_F5:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				}
				else
			ScreenTransition(MTB_AXIS);
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
		case GK_F10:
			ScreenTransition(MTB_PASSWORD);
		break;
				default:
			break;
	}
	return TRUE;
}

long GCMTB_SPSPEED::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	StoreData();
	return TRUE;
}



void GCMTB_SPSPEED::SetColor(short cur_pos)
{
	GBaseObject *pTxtB[MAX_TXT],*pPanel,*pHelp;

	pHelp = GCSGetChild(GetGBaseObject(), HELP);


	short sCursorNum = MAX_TXT;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
		pTxtB[3] = GCSGetChild(pPanel, TXT4);
		//pTxtB[4] = GCSGetChild(pPanel, TXT5);
	//	pTxtB[5] = GCSGetChild(pPanel, TXT6);
		//pTxtB[6] = GCSGetChild(pPanel, TXT7);
		//pTxtB[7] = GCSGetChild(pPanel, TXT8);
		//pTxtB[8] = GCSGetChild(pPanel, TXT9);
		//pTxtB[9] = GCSGetChild(pPanel, TXT10);
		
		GCSNCDataTextboxSetNormalColor(pTxtB[0] , DEFAULT_COLOR);
		GCSNCDataTextboxSetNormalColor(pTxtB[1] , DEFAULT_COLOR);		
		GCSNCDataTextboxSetNormalColor(pTxtB[2] , DEFAULT_COLOR);		
		GCSNCDataTextboxSetNormalColor(pTxtB[3] , DEFAULT_COLOR);	
	//	GCSTextboxSetNormalColor(pTxtB[4] , DEFAULT_COLOR);		
	//	GCSTextboxSetNormalColor(pTxtB[5] , DEFAULT_COLOR);		
		//GCSTextboxSetNormalColor(pTxtB[6] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[7] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[8] , DEFAULT_COLOR);	
		//GCSTextboxSetNormalColor(pTxtB[9] , DEFAULT_COLOR);	
		GCSNCDataTextboxSetNormalColor(pTxtB[cur_pos] , CURSOR_COLOR);

		SetRange(DATA_SCRN,Cursor);


}


void GCMTB_SPSPEED::SetData(short cur_pos)
{
	GBaseObject *pData,*pLbl;
	short lErrFlag;
	long ldataDUMMY=55;
	//GTCHAR szText[WARNTEXT_SIZE];
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

		pData  = GCSGetChild(GetGBaseObject(), DATA);


		GBaseObject *pTxtB[MAX_TXT],*pPanel;
	

		short sCursorNum = MAX_TXT;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
		pTxtB[3] = GCSGetChild(pPanel, TXT4);
		/*pTxtB[4] = GCSGetChild(pPanel, TXT5);
		pTxtB[5] = GCSGetChild(pPanel, TXT6);*/

	GTCHAR inpBuff[20];
	char cInputData[20];
			GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
			/* Checking for Inpu Data Present or Not */ 
			if(strlen(cInputData))
				{
					//if(oper->iOpenFlag == TYPE_OPEN){
					//GetOperationData(&od);
					//od.iModifyFlag = 1;
					//SetOperationData(&od);
					//}
				lErrFlag = checkRange(cInputData,DATA_SCRN,  cur_pos);
				if(lErrFlag == 0)
				{
					if(Cursor < sCursorNum-1)
					Cursor++;					
				short sUpdate=	GCSNCDataTextboxSetString(pTxtB[cur_pos],inpBuff);
				
					/*melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
		   97,1,1, (void *)&ldataDUMMY, T_LONG);*/ 
					SetColor(Cursor);
					GCSTextboxSetString(pData,(GTCHAR *)"");
					ClearWarningMessage();
					if(sUpdate==1)
					SetWarningMessage(19);

				}
				else
					SetWarningMessage(2);
			}

	
}
void GCMTB_SPSPEED::ScreenTransition(short ScreenNo)
{

	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}


long GCMTB_SPSPEED::BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MTB_PASSWORD);
	return TRUE;
}
long GCMTB_SPSPEED::GetEditKeyProtection()
{
	short ldata8=0,ldata9=0,ldataa=0;
	long lEditKey=0;
	// Fetch Y708 Data	
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,  M_SSEC_PLBIT_Y_1SHOT(1800) ,0, (void *)&ldata8, T_SHORT);
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,  M_SSEC_PLBIT_Y_1SHOT(1801) ,0, (void *)&ldata9, T_SHORT);
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,  M_SSEC_PLBIT_Y_1SHOT(1802) ,0, (void *)&ldataa, T_SHORT);
	
	lEditKey=ldata8&ldata9&ldataa;
	return lEditKey;


}

long GCMTB_SPSPEED::BTNENABLEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChkBox;
	pChkBox = GCSGetChild(GetGBaseObject(), CHKBOX1);
	ucChkStatus=!ucChkStatus;
	GCSCheckboxSetStatus(pChkBox,ucChkStatus);
	return TRUE;
}
void GCMTB_SPSPEED:: ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");
}

void  GCMTB_SPSPEED::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARNTEXT_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Save Data!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 2)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Out of Range Error!!!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 3)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data is Protected!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 4)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data Saved!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 5)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data Modified!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 6)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Save Modified Data!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 7)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Program Memory Over!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 8)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Modify Error!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 9)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Save Completed!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 10)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Program Memory Over!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 11)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data dose not Saved!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 12)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Program is Running! Can't Edit", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 13)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Enter Data", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 14)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Enter Integer Type Data", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 15)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File does not exists", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 16)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Device not found or not ready", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 17)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enable setting to edit", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 18)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enable edit protection", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 19)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data updated succesfully", sizeof(szText)/sizeof(GTCHAR));


	
	

	GCSTextboxSetString( pLbl, szText );
}


void GCMTB_SPSPEED:: SetRange(int ScreenNo,short cur_pos)

{
	Datarange drange1[15][07] = {
	{{0,999999},{0,999999},{1,32767},{1,32767},{0,2500},{0,20}},
	{{-35999,35999},{1,32767},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500},{1,10}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500},{1,10}}
	
};
	GBaseObject *pHelp;
	char cHelpText[HELPTEXT_LEN];
	GTCHAR szText[HELPTEXT_LEN];

	pHelp = GCSGetChild(GetGBaseObject(), HELP);
			sprintf(cHelpText, "Range: %.0f TO %.0f \n", drange1[ScreenNo][cur_pos].minValue, drange1[ScreenNo][cur_pos].maxValue);
			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cHelpText, sizeof(szText)/sizeof(GTCHAR));
			GCSTextboxSetString( pHelp, szText );
			if(ScreenNo==2)
			{
			sprintf(cHelpText, "Range: %.03f TO %.03f \n", drange1[ScreenNo][cur_pos].minValue, drange1[ScreenNo][cur_pos].maxValue);
			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cHelpText, sizeof(szText)/sizeof(GTCHAR));
			GCSTextboxSetString( pHelp, szText );
			}


}

long GCMTB_SPSPEED::checkRange(char *dat,int ScreenNo, int cur_pos)
{
//	GBaseObject *pErr;

//	GTCHAR szText[MAX_PARAM];
Datarange drange1[15][07] = {
	{{0,999999},{0,999999},{1,32767},{1,32767},{0,2500},{0,20}},
	{{-35999,35999},{1,32767},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999},{-99999.999,99999.999}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500},{1,10}},
	{{1,10},{0,2500},{0,4},{0,1},{0,2500},{0,20}},
	{{1,10},{0,2500},{0,4},{0,5},{0,2500},{0,20},{0,40}},
	{{1,10},{0,2500},{1,10}}
	
};

	double ddata;
	short lErr = 0;
	short lAlpha = 0;
	short i;
	short len = strlen(dat);


		for(i = 0; i < len; i++){
					if(! ( ( (dat[i] >= '0') && (dat[i] <= '9') ) ) ){
						lAlpha = 1;
						break;
					}				
					if( (dat[i] == '-') || (dat[i] == '+') || (dat[i] == '.') ){
						if (i != 0){
							lAlpha = 1;
							break;
						}
					}
				}
		for(i = 0; i < len; i++){
									
					if( (dat[i] == '-') || (dat[i] == '+') || (dat[i] == '.') ){
						if (i >= 0){
							lAlpha = 2;
							break;
						}
					}
				}
	if(  (lAlpha == 2) ){
	//	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "1", sizeof(szText)/sizeof(GTCHAR));
	//	GCSTextboxSetString( pErr, szText );
		//return 2;///TEST
	}
	if(lAlpha != 1)
	{
		ddata = atof(dat);
		// Check for range
		if( (ddata < drange1[ScreenNo][cur_pos].minValue) || (ddata > drange1[ScreenNo][cur_pos].maxValue) )
//		if( (ddata < dDipDataRange[0][cellpos]) || (ddata > dDipDataRange[1][cellpos]) )
			lErr = 1;
	}
		

	// Set Error Flag
	if( (lErr == 1) || (lAlpha == 1) ){
	//	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "1", sizeof(szText)/sizeof(GTCHAR));
	//	GCSTextboxSetString( pErr, szText );
		return 1;
	}
	else{
	//	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "0", sizeof(szText)/sizeof(GTCHAR));
	//	GCSTextboxSetString( pErr, szText );
		return 0;
	}
}


long GCMTB_SPSPEED::BTNAXISOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MTB_AXIS);
	return TRUE;
}

long GCMTB_SPSPEED::BTNSPORIENTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MTB_SPORIENT);
	return TRUE;
}
void GCMTB_SPSPEED::StoreData()
{
	GBaseObject *pData,*pTxtB[MAX_TXT],*pPanel;
		GTCHAR inpBuff[20];
	char cInputData[20];
	short lErrFlag;



		pData  = GCSGetChild(GetGBaseObject(), DATA);


		
	

		short sCursorNum = MAX_TXT;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, TXT1);
		pTxtB[1] = GCSGetChild(pPanel, TXT2);
		pTxtB[2] = GCSGetChild(pPanel, TXT3);
		pTxtB[3] = GCSGetChild(pPanel, TXT4);
		/*pTxtB[4] = GCSGetChild(pPanel, TXT5);
		pTxtB[5] = GCSGetChild(pPanel, TXT6);*/
			
			for(int i=0;i<MAX_TXT;i++)
			{
			GCSNCDataTextboxGetString(pTxtB[i], inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
			
			long TempData=atoi(cInputData),Cmpdata=0;

			melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,M_SSEC_PLWRD_R_1SHOT_EXT(28620+i) ,0, (void *)&Cmpdata, T_LONG);
			if(TempData!=Cmpdata)
			melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,M_SSEC_PLWRD_R_1SHOT_EXT(28620+i),0, &TempData, T_LONG);
			}

	
}

long GCMTB_SPSPEED::CHKBOX1OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChkBox;
	pChkBox = GCSGetChild(GetGBaseObject(), CHKBOX1);
	ucChkStatus=!ucChkStatus;
	GCSCheckboxSetStatus(pChkBox,ucChkStatus);
	return TRUE;
}

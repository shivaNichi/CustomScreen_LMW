#include "GCPreventive_Maint.hpp"
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

static  bool bSetPasswordOn=0;

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 
                           31, 31, 30, 31, 30, 31}; 
  

extern "C"
{

void GCIDeleteGCPreventive_Maint( GBaseObject *pObject )
{
	GCPreventive_Maint *pPanel = (GCPreventive_Maint*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCPreventive_Maint( GBaseObject *pObject )
{
	GCPreventive_Maint *pPanel = new GCPreventive_Maint;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCPreventive_Maint;
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
GCPreventive_Maint::GCPreventive_Maint()
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
GCPreventive_Maint::~GCPreventive_Maint()
{

}

#include "GCPreventive_Maint.prc"

short GCPreventive_Maint::CreateChildren( )
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

GPropertyInfo* GCPreventive_Maint::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCPreventive_Maint::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild,*pPass;
	Cursor=0;

		pChild = GCSGetChild(GetGBaseObject(), DATA);
		pPass = GCSGetChild(GetGBaseObject(), TXTINPUT);

			GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Basic object
	}
	SetColor(20);
	bResetFlag=0;
	FetchPreventTableData();
	/*Startbtn();*/
	bReseScreen=0;
	bClearDataFlag=0;
	if(bSetPasswordOn)
	{
	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "INPUT", sizeof(inpBuff));
	GCSTextboxSetString(pPass, inpBuff);
	GCSTextboxSetPasswordStatus(pChild,false);
	}
	else
	{
	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "PASSWORD", sizeof(inpBuff));
	GCSTextboxSetString(pPass, inpBuff);
	GCSTextboxSetPasswordStatus(pChild,true);
	}

	return TRUE;
}

long GCPreventive_Maint::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild,*pWindow,*pPass;
		GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	pPass = GCSGetChild(GetGBaseObject(), TXTINPUT);
	char cInputData[PREVENTIVE_INPUT_SIZE];
	

		pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW + 1);
	
	
	long sCursorNum=9;
	switch(lLParam)
		{
			case GK_F1:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
			
			ScreenTransition(HMI_SCREEN);
			}
			break;
		case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
			
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
		/*	else
				ScreenTransition( INOUTXY_SCREEN);*/
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			else
				if(!bSetPasswordOn)
				{
						bool bCorrectPwd = CheckPassword();
						if(bCorrectPwd)
						{
								bSetPasswordOn = true;
						setWarningMessage(12);
						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "INPUT", sizeof(inpBuff));
						GCSTextboxSetString(pPass, inpBuff);
						GCSTextboxSetPasswordStatus(pChild,false);
						
				
						}
						else
								setWarningMessage(5);
						clearData();
			}
			else
			{
				if(bResetFlag==1)
				{
					
					bReseScreen=1;
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW);
					SetColor(Cursor);
					
					
				}
			}
	/*		if(bResetFlag==1)
			{
				SetData(Cursor);
			}*/
			break;
				case GK_DOWN:
			// Down arrow button operation
			
				Cursor++;
				if(Cursor >= sCursorNum){
					Cursor = 0;
				
					}

				SetColor(Cursor);
				
				//SetRange(Cursor+1);
			
			break;
				case GK_UP:
			// Up arrow button operation
		
				if(Cursor > 0)
				{
					Cursor--;
				}
				SetColor(Cursor);
		
			//	SetRange(Cursor+1);
			break;
				ScreenTransition( INIT_SCREEN);
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
								
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
	
			
		break;
		case GK_RETURN:

			if(!bSetPasswordOn)
				{
						bool bCorrectPwd = CheckPassword();
						if(bCorrectPwd)
						{
								bSetPasswordOn = true;
								setWarningMessage(12);
						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "INPUT", sizeof(inpBuff));
						GCSTextboxSetString(pPass, inpBuff);
						GCSTextboxSetPasswordStatus(pChild,false);
				
						}
						else
								setWarningMessage(5);

					clearData();
			}
			else
			{
				bResetFlag=0;
				GCSCreateGWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW);
			
			}
			/*SetData(Cursor);*/
				break;
		case GK_F7:
			if((lUParam & 11) != 10){
					ScreenTransition(EOS_SCREEN);
			}
					break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			default:
				break;
	}
	return TRUE;
}

long GCPreventive_Maint::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	//GBaseObject *pChild;
	//	pChild = GCSGetChild(GetGBaseObject(), DATA);
	//
	//if(pChild != NULL)
	//{
	//	GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Basic object
	//}
	int c=1;
	if(c==1)
	{
		//FetchPreventTableData();
		SetRemainingTime();
		SetStatus();
	}
	if(	bClearDataFlag==1)
	{
			bClearDataFlag=0;
			clearData();
	}
	
	return TRUE;
}






void GCPreventive_Maint::SetColor(short cur_pos)
{
	GBaseObject *pTxtB[10],*pPanel,*btnRest;
	char cInputData[10][PREVENTIVE_INPUT_SIZE];
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	int i;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, T1);
		pTxtB[1] = GCSGetChild(pPanel, T2);
		pTxtB[2] = GCSGetChild(pPanel, T3);
		pTxtB[3] = GCSGetChild(pPanel, T4);
		pTxtB[4] = GCSGetChild(pPanel, T5);
		pTxtB[5] = GCSGetChild(pPanel, T6);
		pTxtB[6] = GCSGetChild(pPanel, T7);
		pTxtB[7] = GCSGetChild(pPanel, T8);
		pTxtB[8] = GCSGetChild(pPanel, T9);

	btnRest = GCSGetChild(pPanel, BTNRESET);

		
	if(cur_pos==20)
	{
	sprintf(cInputData[0],"%s","CLEAN AC PANEL FILTER");
	sprintf(cInputData[1],"%s","COOLANT TANK/FILTER CLEANING");
	sprintf(cInputData[2],"%s","CLEAN SPINDLE BELT");
	sprintf(cInputData[3],"%s","LUBE PUMP FILTER CLEANING");
	sprintf(cInputData[4],"%s","SPINDLE RUN OUT CHECK");
	sprintf(cInputData[5],"%s","CLEAN MACHINE LAMP");
	sprintf(cInputData[6],"%s","FRL UNIT CLEANING");
	sprintf(cInputData[7],"%s","CHECK ALL PROXY & LIMIT SW");
	sprintf(cInputData[8],"%s","MACHINE LEVEL");

	

		for(i=0;i<9;i++)
		{
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData[i], sizeof(cInputData));
		GCSTextboxSetString(pTxtB[i], inpBuff);
			SetPowerTime[i]=0;
			SetPowerDate[i]=0;
			RemTime[i]=0;
			nUnit[i]=30;
		}
		cur_pos=0;
		nUnit[0]=5,nUnit[1]=5,nUnit[8]=60;
	
	}

	 
	for(i=0;i<9;i++)
	{
	GCSTextboxSetNormalColor(pTxtB[i] , DEFAULT_COLOR);

	}
	
	GCSTextboxSetNormalColor(pTxtB[cur_pos] , CURSOR_COLOR);
		
	
	
		
			
	
}


void GCPreventive_Maint::SetData(short cur_pos)
{
	GBaseObject *pTxtB[10],*pPanel,*pData;
	char cInputData[10][PREVENTIVE_INPUT_SIZE];
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];

	
	pPanel = GetGBaseObject();
		pData = GCSGetChild(pPanel, DATA);
		pTxtB[0] = GCSGetChild(pPanel, P1);
		pTxtB[1] = GCSGetChild(pPanel, P2);
		pTxtB[2] = GCSGetChild(pPanel, P3);
		pTxtB[3] = GCSGetChild(pPanel, P4);
		pTxtB[4] = GCSGetChild(pPanel, P5);
		pTxtB[5] = GCSGetChild(pPanel, P6);
		pTxtB[6] = GCSGetChild(pPanel, P7);
		pTxtB[7] = GCSGetChild(pPanel, P8);
		pTxtB[8] = GCSGetChild(pPanel, P9);

		
		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GCSTextboxSetString(pTxtB[cur_pos],inpBuff);
		if(bResetFlag==1)
		{
		GCSTextboxSetString(pTxtB[cur_pos],(GTCHAR *)"0");
		GCSTextboxSetString(pData,(GTCHAR *)"");
		}
		Startbtn();
	
	
}

void GCPreventive_Maint::Startbtn()
{


	//GBaseObject *pData, *pTbl;
	unsigned short sretErr;
	char cInputData[PREVENTIVE_INPUT_SIZE];
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	char sTime[20];
	char *sTimeData;
	long sHours;
	short sIndx;
	short sAllCutData;
	short sTimeLeft;
	long sCntStrt = 0;


		STRINGTYPE TimeBuff;
		TimeBuff.lBuffSize = sizeof(sTime);
		TimeBuff.lpszBuff = sTime;


		GBaseObject *pTxtB[10],*pData;
		GBaseObject *pPanel;
		pPanel=GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, P1);
		pTxtB[1] = GCSGetChild(pPanel, P2);
		pTxtB[2] = GCSGetChild(pPanel, P3);
		pTxtB[3] = GCSGetChild(pPanel, P4);
		pTxtB[4] = GCSGetChild(pPanel, P5);
		pTxtB[5] = GCSGetChild(pPanel, P6);
		pTxtB[6] = GCSGetChild(pPanel, P7);
		pTxtB[7] = GCSGetChild(pPanel, P8);
		pTxtB[8] = GCSGetChild(pPanel, P9);

	

	//	clearWarningMessage();


		
	
		
				melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
										M_SSEC_RTIME_TIME, 0, &TimeBuff, T_STR); 
	
			sTimeData = strtok (sTime,":");

			char *sminute=strtok (NULL,":");
	
			

			strcat(sTimeData,sminute);

			sHours = atoi(sTimeData);


			

		//	GCSNCTableGetCellString(pTbl, inpBuff, 6, usRow, 1, &sretErr);
			GCSTextboxGetString( pTxtB[Cursor], inpBuff,sizeof(inpBuff)/sizeof(GTCHAR) );
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
			if(atoi(cInputData) > 0)
			{
				sHours += (atoi(cInputData)*100);
				SetPowerTime[Cursor]=sHours%2400;
				SetPowerDate[Cursor]=addDays(sHours/2400);
	
			}
			else
					SetPowerTime[Cursor]=0;


		
		
		
		//	if((lUParam & KEY_BITALL)==0)
			StorePreventTableData();   //STORE ALL DATA IN THE TABLE

	
}
void GCPreventive_Maint::StorePreventTableData()
{
	GBaseObject *pTbl;
	FS_STAT stat;
	unsigned short sretErr, i;
	char cHours [11];
	char cTime [11];
	long lDestFile;
	long lWriteNo;
	char sWriteData[60];
	char cAllData[1000];
	GTCHAR PreventBuff[PREVENTIVE_INPUT_SIZE];
//	char cMaintenanceItem [PREVENTIVE_INPUT_SIZE+1];
	char sDestFile[] = "M01:\\PRG\\MMACRO\\PREVENT"; 
	
		GBaseObject *pTxtB[10],*pData;
		GBaseObject *pPanel;
		pPanel=GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, P1);
		pTxtB[1] = GCSGetChild(pPanel, P2);
		pTxtB[2] = GCSGetChild(pPanel, P3);
		pTxtB[3] = GCSGetChild(pPanel,P4);
		pTxtB[4] = GCSGetChild(pPanel, P5);
		pTxtB[5] = GCSGetChild(pPanel, P6);
		pTxtB[6] = GCSGetChild(pPanel, P7);
		pTxtB[7] = GCSGetChild(pPanel,P8);
		pTxtB[8] = GCSGetChild(pPanel, P9);

	


		
	BUFFTYPE buf;
	buf.lBuffSize = sizeof(cAllData);
	buf.lpBuff = cAllData;
//	pTbl = GCSGetChild(GetGBaseObject(), MAINTENANCETABLE);

	if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) == 0)
	{
		if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, 0, &lDestFile) != 0)
		{
			setWarningMessage(2);
		}
		
	}
	else if(melFSCreateFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, &lDestFile) != 0)
	{
			setWarningMessage(2);
	}
	for(i = 0; i < 9; i++)
	{
		

		memset(cHours,0,sizeof(cHours));
		memset(cTime,0,sizeof(cTime));



		GCSTextboxGetString(pTxtB[i],  PreventBuff,sizeof(PreventBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cTime, PreventBuff, sizeof(cTime));
		
		if(strlen(cTime) <= 0)
		sprintf(cTime, "%d",0);
		
		
		sprintf(sWriteData, "%d\t%d\t%s\n",SetPowerDate[i], SetPowerTime[i],  cTime);
		if(i == 0)
		{
			strcpy(cAllData, sWriteData);
		}
		else
		{
			strcat(cAllData, sWriteData);
		}
		
		long localSetTime=0;
		localSetTime=atoi(cTime);

		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), 111, 
																	(1+i), 0, (void *)& SetPowerTime[i], T_LONG);
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), 111, 
																	(10+i), 0, (void *)&localSetTime, T_LONG);
		
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), 111, 
																	(40+i), 0, (void *)&SetPowerDate[i], T_LONG);

	}
	strcat(cAllData, "\0");
	strcat(cAllData, "%");

	melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile, &buf, &lWriteNo);
	melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile);

}

void GCPreventive_Maint::FetchPreventTableData()
{
	GBaseObject *pTbl;
	FS_STAT stat;
	unsigned short sretErr, i= 0;
	char cMaintenData [PREVENTIVE_INPUT_SIZE];
	GTCHAR PreventBuff[PREVENTIVE_INPUT_SIZE];
	char sDestFile[] = "M01:\\PRG\\MMACRO\\PREVENT";
	char cAllData[1000];
	char *cTblData;
	long lReadNo;
	long lDestFile;
	BUFFTYPE buf;
	buf.lBuffSize = sizeof(cAllData);
	buf.lpBuff = cAllData;

		GBaseObject *pTxtB[10],*pData;
		GBaseObject *pPanel;
		pPanel=GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, P1);
		pTxtB[1] = GCSGetChild(pPanel, P2);
		pTxtB[2] = GCSGetChild(pPanel, P3);
		pTxtB[3] = GCSGetChild(pPanel,P4);
		pTxtB[4] = GCSGetChild(pPanel, P5);
		pTxtB[5] = GCSGetChild(pPanel, P6);
		pTxtB[6] = GCSGetChild(pPanel, P7);
		pTxtB[7] = GCSGetChild(pPanel,P8);
		pTxtB[8] = GCSGetChild(pPanel, P9);


//	pTbl = GCSGetChild(GetGBaseObject(), MAINTENANCETABLE);
	
	if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) == 0)
	{
		melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lDestFile);
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile, &buf, T_BUFF, &lReadNo);
		
	}
	melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile);
	if((long)stat.lFileSize>30)
	{
		cTblData = strtok (cAllData, "\t");
		if(strlen(cTblData) < 60)
		{
			while (cTblData!= NULL && i < 9) 
			{
				
				SetPowerDate[i]=atoi(cTblData);
				cTblData = strtok (NULL, "\t");
				SetPowerTime[i]=atoi(cTblData);
				cTblData = strtok (NULL, "\n");
				sprintf(cMaintenData, "%s", cTblData);
				GRCMultiByteToUnicode(0, PreventBuff, cMaintenData,sizeof(cMaintenData));
				GCSTextboxSetString(pTxtB[i], PreventBuff);	
				i++;
				cTblData = strtok (NULL,"\t");
				

			}
		}
	}
	//else
	//	FileCorruptFlg = 1;
}
void GCPreventive_Maint::setWarningMessage(int warnnum)
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

void GCPreventive_Maint::SetRemainingTime()
{
	GBaseObject *pTxtB[10],*pPROG,*pPanel;
	char cInputData[PREVENTIVE_INPUT_SIZE];
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	int i;
	char sTime[20];
	char *sTimeData;
	char cTimeLeft [10];
	long sLeftTim;

	STRINGTYPE TimeBuff;
	TimeBuff.lBuffSize = sizeof(sTime);
	TimeBuff.lpszBuff = sTime;
		pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, C1);
		pTxtB[1] = GCSGetChild(pPanel, C2);
		pTxtB[2] = GCSGetChild(pPanel, C3);
		pTxtB[3] = GCSGetChild(pPanel, C4);
		pTxtB[4] = GCSGetChild(pPanel, C5);
		pTxtB[5] = GCSGetChild(pPanel, C6);
		pTxtB[6] = GCSGetChild(pPanel, C7);
		pTxtB[7] = GCSGetChild(pPanel, C8);
		pTxtB[8] = GCSGetChild(pPanel, C9);
	

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
												M_SSEC_RTIME_TIME, 0, &TimeBuff, T_STR); 

				sTimeData = strtok (sTime,":");

				char *sminute=strtok (NULL,":");
				strcat(sTimeData,sminute);
				sLeftTim = atoi(sTimeData);


	char strReadCurrentDate[20];
	TimeBuff.lBuffSize = sizeof(strReadCurrentDate);
	TimeBuff.lpszBuff = strReadCurrentDate;

	
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
								M_SSEC_RTIME_DATE, 0, &TimeBuff, T_STR);
	dates[0].y=atoi(strtok(strReadCurrentDate,"."));
	dates[0].m=atoi(strtok(NULL,"."));
	dates[0].d=atoi(strtok(NULL,"."));
	

				
	for(i=0;i<9;i++)
	{
		int NoOfDays=0;
	
		if(SetPowerDate[i]>0)
		{
		dates[1].y=SetPowerDate[i]/10000;
		dates[1].m=(SetPowerDate[i]%10000)/100;
		dates[1].d=SetPowerDate[i]%100;
		 NoOfDays=getDifference(dates[0],dates[1]);
		NoOfDays=NoOfDays*(24*60);
		}
		else
		NoOfDays=0;

			long SettimeMns=0,LeftTimeMins=0;
			SettimeMns=(SetPowerTime[i]/100)*60+(SetPowerTime[i]%100)+NoOfDays;

			LeftTimeMins=(sLeftTim/100)*60+(sLeftTim%100);
			RemTime[i]=SettimeMns-LeftTimeMins;
				if(RemTime[i]<0)
					RemTime[i]=0;

			long lDtime=0;
			if(SetPowerTime[i]>sLeftTim)
			 lDtime =((SetPowerTime[i]+99)-sLeftTim)/100;//99 for one hour extra
			else
				 lDtime =((SetPowerTime[i]-1)-sLeftTim)/100;//99 for one hour extra
		
			lDtime+=NoOfDays/60;
		
			if(lDtime<0)
				lDtime=0;
			sprintf(cInputData,"%d",lDtime);
			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, sizeof(cInputData));
			GCSTextboxSetString(pTxtB[i], inpBuff);
		//}
	}

	
		
	
	
			
	
}



void GCPreventive_Maint::SetStatus()
{
	GBaseObject *pTxtB[10],*pTxtP[10],*pTxtPB[10],*pPanel,*btnRest;
	char cInputData[PREVENTIVE_INPUT_SIZE];
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];
	int i=0;
	double SetTime=0;

	/*	pPanel = GetGBaseObject();
		pTxtB[0] = GCSGetChild(pPanel, C1);
		pTxtB[1] = GCSGetChild(pPanel, C2);
		pTxtB[2] = GCSGetChild(pPanel, C3);
		pTxtB[3] = GCSGetChild(pPanel, C4);
		pTxtB[4] = GCSGetChild(pPanel, C5);
		pTxtB[5] = GCSGetChild(pPanel, C6);
		pTxtB[6] = GCSGetChild(pPanel, C7);
		pTxtB[7] = GCSGetChild(pPanel, C8);
		pTxtB[8] = GCSGetChild(pPanel, C9);*/
		
		pPanel = GetGBaseObject();
		btnRest = GCSGetChild(pPanel, BTNRESET);
		pTxtB[0] = GCSGetChild(pPanel, TS1);
		pTxtB[1] = GCSGetChild(pPanel, TS2);
		pTxtB[2] = GCSGetChild(pPanel, TS3);
		pTxtB[3] = GCSGetChild(pPanel, TS4);
		pTxtB[4] = GCSGetChild(pPanel, TS5);
		pTxtB[5] = GCSGetChild(pPanel, TS6);
		pTxtB[6] = GCSGetChild(pPanel, TS7);
		pTxtB[7] = GCSGetChild(pPanel, TS8);
		pTxtB[8] = GCSGetChild(pPanel, TS9);

		pPanel = GetGBaseObject();
		pTxtP[0] = GCSGetChild(pPanel, P1);
		pTxtP[1] = GCSGetChild(pPanel, P2);
		pTxtP[2] = GCSGetChild(pPanel, P3);
		pTxtP[3] = GCSGetChild(pPanel, P4);
		pTxtP[4] = GCSGetChild(pPanel, P5);
		pTxtP[5] = GCSGetChild(pPanel, P6);
		pTxtP[6] = GCSGetChild(pPanel, P7);
		pTxtP[7] = GCSGetChild(pPanel, P8);
		pTxtP[8] = GCSGetChild(pPanel, P9);

		//pTxtPB[0] = GCSGetChild(pPanel,PB1);
		//pTxtPB[1] = GCSGetChild(pPanel,PB2);
		//pTxtPB[2] = GCSGetChild(pPanel,PB3);
		//pTxtPB[3] = GCSGetChild(pPanel,PB4);
		//pTxtPB[4] = GCSGetChild(pPanel,PB5);
		//pTxtPB[5] = GCSGetChild(pPanel,PB6);
		//pTxtPB[6] = GCSGetChild(pPanel,PB7);
		//pTxtPB[7] = GCSGetChild(pPanel,PB8);
		//pTxtPB[8] = GCSGetChild(pPanel,PB9);
		
	
	int tempUnit=0;


	 for(i=0;i<9;i++)
		{

		GCSTextboxGetString( pTxtP[i], inpBuff,sizeof(inpBuff)/sizeof(GTCHAR) );
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
			SetTime=atof(cInputData);
		/*GCSTextboxGetString( pTxtP[Cursor], inpBuff,sizeof(inpBuff)/sizeof(GTCHAR) );
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
			RemTime=atof(cInputData);*/
			if((SetTime*15.0)<RemTime[i])
			{
				GCSTextboxSetNormalColor(pTxtB[i] , GREEN_COLOR);
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "RUNNING", sizeof(cInputData));
				GCSTextboxSetString(pTxtB[i], inpBuff);
			}
			else if(((SetTime*15.0)>RemTime[i])&&(RemTime[i]!=0))
			{
				GCSTextboxSetNormalColor(pTxtB[i] , YELLOW_COLOR);
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "WARNING", sizeof(cInputData));
				GCSTextboxSetString(pTxtB[i], inpBuff);
			}
			else if(((SetTime*15.0)>0)&&(RemTime[i]==0))
			{
				GCSTextboxSetNormalColor(pTxtB[i] , RED_COLOR);
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "COMPLETED", sizeof(cInputData));
				GCSTextboxSetString(pTxtB[i], inpBuff);
			}
			else
			{
				GCSTextboxSetNormalColor(pTxtB[i] , DEFAULT_COLOR);
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "", sizeof(cInputData));
				GCSTextboxSetString(pTxtB[i], inpBuff);
			}



	/*		int tempRange=(SetTime*60)/nUnit[i];
			GCSProgressbarSetRange(pTxtPB[i],0,tempRange);
			
			if(RemTime[i]>0)
			{
			 tempUnit=tempRange-1-(RemTime[i]/nUnit[i]);
			GCSProgressbarSetValue(pTxtPB[i],tempUnit);
			}
			else if(SetTime>0)
			GCSProgressbarSetValue(pTxtPB[i],tempRange);*/
			int tempRange=(SetTime*60)/nUnit[i];
		//	GCSProgressbarSetRange(pTxtPB[i],0,tempRange);
			
			if(RemTime[i]>0)
			{
			 tempUnit=tempRange-1-(RemTime[i]/nUnit[i]);
			//GCSProgressbarSetValue(pTxtPB[i],tempUnit);
			 if(tempUnit<0)
				 tempUnit=0;

			}
			else if(SetTime>0)
			tempUnit=tempRange;
			
		/*	
			if(tempRange!=0)
			{
			long lbit=tempUnit*(600/tempRange);
	 		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT_EXT(28600+i), 0, (void *)&lbit, T_LONG);
			}
			else
			{
			long lbit=0;
	 		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT_EXT(28600+i), 0, (void *)&lbit, T_LONG);
			}*/
	
	 	

		}
		
		
			if(SetPowerTime[Cursor]>0 & RemTime[Cursor]==0)
			{
			GCSButtonSetStringID(btnRest,ID_STRING00058);
			bResetFlag=1;
			}
			else
			{

			GCSButtonSetStringID(btnRest,ID_STRING00059);
			bResetFlag=0;
			}

			
}
bool GCPreventive_Maint::CheckPassword()
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
		return 1;
	}
	else
	{
	
	return 0;
	}
		

}
//bool GCPreventive_Maint::CheckPassword()
//{	
//	DWORD dwStatus;
//	GBaseObject *pChild;
//	char operData[WARN_MSG_DATA_SIZE];
//	GTCHAR inpBuffPwd[WARN_MSG_DATA_SIZE];
//
//	GTCHAR ReadBuffPwd[WARN_MSG_DATA_SIZE];
//	long ReadPwdData;
//
//	pChild = GCSGetChild(GetGBaseObject(), DATA);
//	
//	GCSTextboxGetString( pChild, inpBuffPwd, sizeof(inpBuffPwd)/sizeof(GTCHAR) );
//	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), operData, inpBuffPwd, sizeof(operData));
//
//
//
//
//	char sPath[] = "M01:\\PRG\\MMACRO\\12345";
//	char *stokAdminPassword;
//	char *stokOperatorPassword;
//	char*s;
//
//	char sAdminPassword[20]="";
//	char sOperatorPassword[20]="";
//	
//	long lReadNo;
//	long lWriteNo;
//	long lFileDesc;	
//	short sError = 0;
//	GTCHAR inpBuff[10];
//	char cInputData[10];
//
//	BUFFTYPE buf;
//	FS_STAT stat;
//
//	GTCHAR szText[WARN_MSG_DATA_SIZE];	
//	char sDatabuf[40];
//	buf.lBuffSize = sizeof(sDatabuf);
//	buf.lpBuff = sDatabuf;
//	
//
//
//	if((melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sPath, &stat) == 0))
//	{
//		if((long)(stat.lFileSize) <= 0)
//		{
//	
//		return false;
//		
//		}
//		else if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sPath, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0)
//			{
//				melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
//				melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
//				
//			
//				char strlocal[10];
//			/*	
//				s=strtok(sDatabuf, "\n");
//				stokOperatorPassword=strtok(NULL, "@");
//				strtok(sDatabuf, "\n");
//				
//				stokAdminPassword=strtok(s, "!");
//				if(stokOperatorPassword!=NULL)*/
//				strcpy(strlocal,sDatabuf);
//		
//		
//				
//					GCSTextboxGetString(pChild, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
//					GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
//					
//
//
//			
//
//					if((strcmp(strlocal, cInputData) == 0) )
//					{
//					//	bloginUser=true;
//						return TRUE;
//					}
//					else
//					{
//						return FALSE;
//					}
//		
//		
//	
//		
//			}
//		
//	}
//	
//	if((long)(stat.lFileSize) <= 0)
//		{
//			dwStatus = melFSCreateFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sPath, M_FSOPEN_WRONLY, &lFileDesc);
//			
//			//File Write
//			GCSTextboxGetString(pChild, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
//			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
//			
//			
//			sprintf(sDatabuf,"%s",cInputData);
//			if (dwStatus == 0){
//			dwStatus = melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, &lWriteNo);
//			melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
//
//			return TRUE;
//			}
//		}
//
//
//
//
//	
//
//}
//
//
//

long GCPreventive_Maint::User(long lLParam, long lUParam)
{

	GBaseObject *pData;
	unsigned short  sretErr;  // error code
	unsigned short i, j;
	GTCHAR szText[10];
	
	pData = GCSGetChild(GetGBaseObject(), DATA);
	
	
	

	switch(lLParam)
	{
		case 0:	
			/*	for(j = 0; j < 4; j++)
				{
					if(j == 0)
					{
						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "NA", sizeof(szText)/sizeof(GTCHAR));
						GCSNCTableSetCellString(pTbl, szText, i, j, &sretErr);	
					}
					else
						GCSNCTableSetCellString(pTbl, (GTCHAR *)"0", i, j, &sretErr);
				}
				SetCountStartColor();*/
			if(bReseScreen==1)
			{
				if(bResetFlag==1)
				{
					SetData(Cursor);
					SetColor(Cursor);
				}
				bReseScreen=0;
			}
			else
			SetData(Cursor);
		break;
		case 1:
				/*GCSNCTableGetCellString(pTbl, szText, 6, i, 3, &sretErr);
				GCSNCTableSetCellString(pTbl, szText, i, 1, &sretErr);
				GCSNCTableSetCellString(pTbl, (GTCHAR *)"0", i, 3, &sretErr);
				SetCountStartColor();*/
		break;
		case 2:	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
				}
		break;
		break;
		default:
		break;
	}
	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
				}
	GCSTextboxSetString(pData, (GTCHAR *)"");
	bClearDataFlag=1;
	return TRUE;
}
void GCPreventive_Maint::clearWarningMessage()
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "", sizeof(szText)/sizeof(GTCHAR));
	


	GCSTextboxSetString( pLbl, szText );

}
void GCPreventive_Maint::clearData()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), DATA);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");	
}


void GCPreventive_Maint::ScreenTransition(short ScreenNo)
{
		StorePreventTableData();

	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

bool GCPreventive_Maint:: isLeap(int y) 
{ 
    if (y%100 != 0 && y%4 == 0 || y %400 == 0) 
        return true; 
  
    return false; 
} 
  
// Given a date, returns number of days elapsed 
// from the  beginning of the current year (1st 
// jan). 
int GCPreventive_Maint:: offsetDays(int d, int m, int y) 
{ 
    int offset = d; 
  
    switch (m - 1) 
    { 
    case 11: 
        offset += 30; 
    case 10: 
        offset += 31; 
    case 9: 
        offset += 30; 
    case 8: 
        offset += 31; 
    case 7: 
        offset += 31; 
    case 6: 
        offset += 30; 
    case 5: 
        offset += 31; 
    case 4: 
        offset += 30; 
    case 3: 
        offset += 31; 
    case 2: 
        offset += 28; 
    case 1: 
        offset += 31; 
    } 
  
    if (isLeap(y) && m > 2) 
        offset += 1; 
  
    return offset; 
} 
  
// Given a year and days elapsed in it, finds 
// date by storing results in d and m. 
void GCPreventive_Maint:: revoffsetDays(int offset, int y, int *d, int *m) 
{ 
    int month[13] = { 0, 31, 28, 31, 30, 31, 30, 
                      31, 31, 30, 31, 30, 31 }; 
  
    if (isLeap(y)) 
        month[2] = 29; 
  
    int i; 
    for (i = 1; i <= 12; i++) 
    { 
        if (offset <= month[i]) 
            break; 
        offset = offset - month[i]; 
    } 
  
    *d = offset; 
    *m = i; 
} 
  
// Add x days to the given date. 
long GCPreventive_Maint:: addDays( int x) 
{ 
	int d1, m1, y1;
	char strReadCurrentDate[20];
	long PrevDate;
	STRINGTYPE TimeBuff;
	TimeBuff.lBuffSize = sizeof(strReadCurrentDate);
	TimeBuff.lpszBuff = strReadCurrentDate;

	
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
								M_SSEC_RTIME_DATE, 0, &TimeBuff, T_STR);
	y1=atoi(strtok(strReadCurrentDate,"."));
	m1=atoi(strtok(NULL,"."));
	d1=atoi(strtok(NULL,"."));

    int offset1 = offsetDays(d1, m1, y1); 
    int remDays = isLeap(y1)?(366-offset1):(365-offset1); 
  
    // y2 is going to store result year and 
    // offset2 is going to store offset days 
    // in result year. 
    int y2, offset2; 
    if (x <= remDays) 
    { 
        y2 = y1; 
        offset2 = offset1 + x; 
    } 
  
    else
    { 
        // x may store thousands of days. 
        // We find correct year and offset 
        // in the year. 
        x -= remDays; 
        y2 = y1 + 1; 
        int y2days = isLeap(y2)?366:365; 
        while (x >= y2days) 
        { 
            x -= y2days; 
            y2++; 
            y2days = isLeap(y2)?366:365; 
        } 
        offset2 = x; 
    } 
  
    // Find values of day and month from 
    // offset of result year. 
    int m2, d2; 
    revoffsetDays(offset2, y2, &d2, &m2); 
  
	PrevDate=y2*10000+m2*100+d2;
	return PrevDate;
   /* cout << "d2 = " << d2 << ", m2 = " << m2 
         << ", y2 = " << y2; */
} 
 int GCPreventive_Maint:: countLeapYears(Date d) 
{ 
    int years = d.y; 
  
    // Check if the current year needs to be considered 
    // for the count of leap years or not 
    if (d.m <= 2) 
        years--; 
  
    // An year is a leap year if it is a multiple of 4, 
    // multiple of 400 and not a multiple of 100. 
    return years / 4 - years / 100 + years / 400; 
} 
  
// This function returns number of days between two given 
// dates 
int GCPreventive_Maint:: getDifference(Date dt1, Date dt2) 
{ 
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 
  
    // initialize count using years and day 
    long int n1 = dt1.y*365 + dt1.d,i=0; 
  
    // Add days for months in given date 
    for ( i=0; i<dt1.m - 1; i++) 
        n1 += monthDays[i]; 
  
    // Since every leap year is of 366 days, 
    // Add a day for every leap year 
    n1 += countLeapYears(dt1); 
  
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 
  
    long int n2 = dt2.y*365 + dt2.d; 
    for ( i=0; i<dt2.m - 1; i++) 
        n2 += monthDays[i]; 
    n2 += countLeapYears(dt2); 
  
    // return difference between two counts 
    return (n2 - n1); 
}

long GCPreventive_Maint::BTNRESETOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild,*pWindow,*pPass;
	GTCHAR inpBuff[PREVENTIVE_INPUT_SIZE];

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	pPass = GCSGetChild(GetGBaseObject(), TXTINPUT);
	char cInputData[PREVENTIVE_INPUT_SIZE];
	

		pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW + 1);
	
	 if(!bSetPasswordOn)
			{
						bool bCorrectPwd = CheckPassword();
						if(bCorrectPwd)
						{
								bSetPasswordOn = true;
						setWarningMessage(12);
						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, "INPUT", sizeof(inpBuff));
						GCSTextboxSetString(pPass, inpBuff);
						GCSTextboxSetPasswordStatus(pChild,false);
						
				
						}
						else
								setWarningMessage(5);
						clearData();
			}
			else
			{
				if(bResetFlag==1)
				{
					
					bReseScreen=1;
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW);
					
					
				}
			}
	return TRUE;
}

long GCPreventive_Maint::BUTTONEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent( GECreateEventMessage( GM_SHOWPANEL, GCSGetScreen( GetGBaseObject() ),  1000, 0 ) , FALSE );
	return TRUE;
}

long GCPreventive_Maint::BUTTONEXITOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent( GECreateEventMessage( GM_SHOWPANEL, GCSGetScreen( GetGBaseObject() ),  1000, 0 ) , FALSE );
	return TRUE;
}

long GCPreventive_Maint::BUTTONHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), EOS_SCREEN, 0), FALSE);
	return TRUE;
}

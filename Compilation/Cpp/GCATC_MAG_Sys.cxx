#include "GCATC_MAG_Sys.hpp"
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

void GCIDeleteGCATC_MAG_Sys( GBaseObject *pObject )
{
	GCATC_MAG_Sys *pPanel = (GCATC_MAG_Sys*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCATC_MAG_Sys( GBaseObject *pObject )
{
	GCATC_MAG_Sys *pPanel = new GCATC_MAG_Sys;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCATC_MAG_Sys;
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
GCATC_MAG_Sys::GCATC_MAG_Sys()
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
GCATC_MAG_Sys::~GCATC_MAG_Sys()
{

}

#include "GCATC_MAG_Sys.prc"

short GCATC_MAG_Sys::CreateChildren( )
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

GPropertyInfo* GCATC_MAG_Sys::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCATC_MAG_Sys::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	Fetchdata();
	
	return TRUE;
}

long GCATC_MAG_Sys::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
				/*else
					CopyFiles("SAMPLINGCOMM.CSV");*/
				else
					ScreenTransition( ATC_ARM_SCREEN);
					
			break;
				case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			
					
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
	
		case GK_F9:			
			
				
				// Changing the screen to MTB 
				ScreenTransition(EOS_SCREEN);
			
		break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			default:
			break;
		}
	return TRUE;
}

long GCATC_MAG_Sys::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	
	}
	displaydata();
	return TRUE;
}

void GCATC_MAG_Sys::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCATC_MAG_Sys::Fetchdata()
{

	DWORD dwStatus;
	FS_STAT stat;
	long lFileDesc;	
	long lReadNo ;
	long lDestFile;
	long lWriteNo;
	BUFFTYPE buf;
	char *sFileData;
	long lCurSize;
	char *s;

		char sDestFile[] = "M01:\\PRG\\MMACRO\\MAG.CSV";
	//	char sDestFile[] = "C:\\lohith\\projects\\LMW\CSV\\ATC.CSV";
			memset(sAdress ,0, sizeof(sAdress));


		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat)== 0)
		{

		lCurSize = (long)stat.lFileSize +10;
		sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));

	
		buf.lBuffSize = (long)stat.lFileSize+10;
		buf.lpBuff = sFileData;

		if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
		}
			int i =0;
			s = strtok(sFileData, "\n");
			while(s!=NULL&i<NO_BTN)
			{
				strcpy(sAdress[i],s);
				s = strtok(NULL, "\n");
				i++;
			}
		/*	ulLineCcount=i;*/
			free(sFileData);
	}
		else
			setWarningMessage(1);
		/*displaydata();*/
		
}
void GCATC_MAG_Sys::displaydata()
{

	GBaseObject *pBtn[20];


	pBtn[0] = GCSGetChild(GetGBaseObject(), BTN1);
	pBtn[1] = GCSGetChild(GetGBaseObject(), BTN2);
	pBtn[2] = GCSGetChild(GetGBaseObject(), BTN3);
	pBtn[3] = GCSGetChild(GetGBaseObject(), BTN4);
	pBtn[4] = GCSGetChild(GetGBaseObject(), BTN5);
	pBtn[5] = GCSGetChild(GetGBaseObject(), BTN6);
	pBtn[6] = GCSGetChild(GetGBaseObject(), BTN7);
	pBtn[7] = GCSGetChild(GetGBaseObject(), BTN8);
	pBtn[8] = GCSGetChild(GetGBaseObject(), BTN9);
	pBtn[9] = GCSGetChild(GetGBaseObject(), BTN10);
	pBtn[10] = GCSGetChild(GetGBaseObject(), BTN11);
	pBtn[11] = GCSGetChild(GetGBaseObject(), BTN12);
	pBtn[12] = GCSGetChild(GetGBaseObject(), BTN13);
	pBtn[13] = GCSGetChild(GetGBaseObject(), BTN14);
	//pBtn[14] = GCSGetChild(GetGBaseObject(), BTN15);
	//pBtn[15] = GCSGetChild(GetGBaseObject(), BTN16);
	//pBtn[16] = GCSGetChild(GetGBaseObject(), BTN17);

		
	for(int i = 0; i < NO_BTN; i++)
	{
		

		bool bit=Readstatus(sAdress[i]);
		GCSButtonSetStatus(pBtn[i], bit);
	
	}
}
bool GCATC_MAG_Sys::Readstatus(char *cInputData)
{
	char prgststatus[20];
	STRINGTYPE str1;
	str1.lBuffSize=20;
	str1.lpszBuff = prgststatus;
	char strlong[40];
	char *s = NULL;
	long Subsection=0;
	char *eptr;
	long ldata=0;

	if(strncmp( cInputData,"X",1)==0)
	{
	s=strtok(cInputData,"X");
	sprintf(strlong,"%s","0x");
	strcat(strlong,s);
	Subsection=strtol( strlong,&eptr,0) ;
	Subsection=Subsection+1;
	}
	else if(strncmp( cInputData,"Y",1)==0)
	{
	s=strtok(cInputData,"Y");
	sprintf(strlong,"%s","0x");
	strcat(strlong,s);
	Subsection=strtol( strlong,&eptr,0) ;
	Subsection=Subsection+10000;
	}
	


melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
		   M_SEC_PLC_DEV_BIT, Subsection ,0, (void *)&ldata, T_LONG);

if(ldata==0)
return 0;
else 
return 1;

}
void GCATC_MAG_Sys::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[60];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "MAG.CSV file not Present", sizeof(szText)/sizeof(GTCHAR));
	GCSTextboxSetString( pLbl, szText );
}

long GCATC_MAG_Sys::BTNARMOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( ATC_ARM_SCREEN);
	return TRUE;
}

long GCATC_MAG_Sys::BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCATC_MAG_Sys::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( HMI_SCREEN);
	return TRUE;
}

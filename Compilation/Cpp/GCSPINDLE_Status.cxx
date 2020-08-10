#include "GCSPINDLE_Status.hpp"
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

void GCIDeleteGCSPINDLE_Status( GBaseObject *pObject )
{
	GCSPINDLE_Status *pPanel = (GCSPINDLE_Status*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCSPINDLE_Status( GBaseObject *pObject )
{
	GCSPINDLE_Status *pPanel = new GCSPINDLE_Status;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCSPINDLE_Status;
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
GCSPINDLE_Status::GCSPINDLE_Status()
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
GCSPINDLE_Status::~GCSPINDLE_Status()
{

}

#include "GCSPINDLE_Status.prc"

short GCSPINDLE_Status::CreateChildren( )
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

GPropertyInfo* GCSPINDLE_Status::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}
long GCSPINDLE_Status::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	Fetchdata();
	
	return TRUE;
}

long GCSPINDLE_Status::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
					ScreenTransition( SUBSYS_SCREEN);
					
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

long GCSPINDLE_Status::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;
		GBaseObject *pIconPicture1,*pIconPicture2;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	
	}
		long lR610=0,lR620=0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10620),0, &lR610, T_LONG); // To get the Data Protection StatusmelGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3224),0, &sIconXC98, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10621),0, &lR620, T_LONG); // To get the Data Protection Status
	

	pIconPicture1 = GCSGetChild(GetGBaseObject(), ICON1);
	pIconPicture2 = GCSGetChild(GetGBaseObject(), ICON2);
	
	if(lR610 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture1,1);
	}
	else
		GCSSetVisibleStatus(pIconPicture1,0);
	if(lR620 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture2,1);
	}
	else
		GCSSetVisibleStatus(pIconPicture2,0);
	displaydata();

	return TRUE;
}

void GCSPINDLE_Status::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCSPINDLE_Status::Fetchdata()
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

		char sDestFile[] = "M01:\\PRG\\MMACRO\\SPINDLE.CSV";
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
void GCSPINDLE_Status::displaydata()
{

	GBaseObject *pBtn[20];


	pBtn[0] = GCSGetChild(GetGBaseObject(), BTN1);
	pBtn[1] = GCSGetChild(GetGBaseObject(), BTN2);
	pBtn[2] = GCSGetChild(GetGBaseObject(), BTN3);
	//pBtn[3] = GCSGetChild(GetGBaseObject(), BTN4);
	//pBtn[4] = GCSGetChild(GetGBaseObject(), BTN5);
	//pBtn[5] = GCSGetChild(GetGBaseObject(), BTN6);
	//pBtn[6] = GCSGetChild(GetGBaseObject(), BTN7);
	//pBtn[7] = GCSGetChild(GetGBaseObject(), BTN8);
	//pBtn[8] = GCSGetChild(GetGBaseObject(), BTN9);
	//pBtn[9] = GCSGetChild(GetGBaseObject(), BTN10);
	//pBtn[10] = GCSGetChild(GetGBaseObject(), BTN11);
	//pBtn[11] = GCSGetChild(GetGBaseObject(), BTN12);
	//pBtn[12] = GCSGetChild(GetGBaseObject(), BTN13);
	//pBtn[13] = GCSGetChild(GetGBaseObject(), BTN14);
	//pBtn[14] = GCSGetChild(GetGBaseObject(), BTN15);
	//pBtn[15] = GCSGetChild(GetGBaseObject(), BTN16);
	//pBtn[16] = GCSGetChild(GetGBaseObject(), BTN17);

		
	for(int i = 0; i < NO_BTN; i++)
	{
		

		bool bit=Readstatus(sAdress[i]);
		GCSButtonSetStatus(pBtn[i], bit);
	
	}
}
bool GCSPINDLE_Status::Readstatus(char *cInputData)
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
void GCSPINDLE_Status::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[60];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "SPINDLE.CSV file not Present", sizeof(szText)/sizeof(GTCHAR));
	GCSTextboxSetString( pLbl, szText );
}



long GCSPINDLE_Status::BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCSPINDLE_Status::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( HMI_SCREEN);
	return TRUE;
}



long GCSPINDLE_Status::BTNMCOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( SUBSYS_SCREEN);
	return TRUE;
}


#include "GCINITSCREEN.hpp"
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

void GCIDeleteGCINITSCREEN( GBaseObject *pObject )
{
	GCINITSCREEN *pPanel = (GCINITSCREEN*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCINITSCREEN( GBaseObject *pObject )
{
	GCINITSCREEN *pPanel = new GCINITSCREEN;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCINITSCREEN;
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
GCINITSCREEN::GCINITSCREEN()
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
GCINITSCREEN::~GCINITSCREEN()
{

}

#include "GCINITSCREEN.prc"

short GCINITSCREEN::CreateChildren( )
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

GPropertyInfo* GCINITSCREEN::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCINITSCREEN::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
short sCursorNum = 12;
long ltemp=0;
long lDowntemp=0;
	switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
				
				/*else
					CopyFiles("IOLIST.CSV");*/
			break;
				case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			/*else
					CopyFiles("IOLISTL.CSV");*/
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			/*else
					CopyFiles("ALARM.CSV");*/
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			/*else
					CopyFiles("MCODE.CSV");*/
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		else
				/*CopyFiles("GCODE.CSV");*/
		/*	else
				sprintf(sDestFile, "%s", "M01:\\PRG\\MMACRO\\MCODE.CSV");
				melFSRemoveFile(0,(ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),sDestFile);*/
		//	case GK_F6:			
		//	if((lUParam & KEY_SHIFT) == KEY_SHIFT){
		//		
		//	
		//	}
		//else
		//		CopyFiles("SYSTEMINFO.CSV");
		//	
		//break;
			case GK_DOWN:
			// Down arrow button operation
				lDowntemp=Cursor;
				if(Cursor<5)
					ltemp=1;
				else
					ltemp=0;
				if(Cursor!=4)
				
				Cursor+=4+ltemp;
				else
					Cursor++;
				
				if(Cursor > sCursorNum){
					Cursor =lDowntemp-8 ;
				
					}

				setColorButton(Cursor);
				clearWarningMessage();
			
			
			break;
		case GK_UP:
			// Up arrow button operation
		
				if(Cursor > 4)
				{
					if(Cursor<9)
					Cursor--;
					Cursor-=4;
				}
				setColorButton(Cursor);
				clearWarningMessage();
				
			break;
			case GK_RIGHT:
				Cursor++;
				if(Cursor > sCursorNum){
					Cursor = 0;
				
					}

				setColorButton(Cursor);
				clearWarningMessage();
				break;
			case GK_LEFT:
					if(Cursor > 0)
				{
					Cursor--;
				}
				setColorButton(Cursor);
				clearWarningMessage();
			break;
		case GK_F10:			
			
				
				// Changing the screen to home screen.
				ScreenTransition( EOS_SCREEN);
			
		break;
		case GK_RETURN:
				CopyFiles(Cursor);
			break;
			default:
			break;
		}
	return TRUE;
}

long GCINITSCREEN::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	setSelectButton();
	return TRUE;
}

void GCINITSCREEN::CopyFiles(int btncursor)
{
	clearWarningMessage();
	char sDestFile[50],sSource[50];
	FS_STAT stat;
	long lFileDesc;	
	int a;

	char name[20][20];
	sprintf(name[0], "%s", "IOLIST.CSV");
	sprintf(name[1], "%s", "IOLISTL.CSV");
	sprintf(name[2], "%s", "GCODE.CSV");
	sprintf(name[3], "%s", "MCODE.CSV");
	sprintf(name[4], "%s", "ALARM.CSV");
	sprintf(name[5], "%s", "SYSTEMINFO.CSV");
	sprintf(name[6], "%s", "COOLANT.CSV");
	sprintf(name[7], "%s", "LUBRICATION.CSV");
	sprintf(name[8], "%s", "HYDRAULIC.CSV");
	sprintf(name[9], "%s", "ARM.CSV");
	sprintf(name[10], "%s", "MAG.CSV");
	sprintf(name[11], "%s", "CHIPCONVEY.CSV");
	sprintf(name[12], "%s", "SPINDLE.CSV");
	//
				
	//	sprintf(sSource, "%s%s", "C:\\MELCNC\\NCT2P\\HD\\MMACRO\\",name);
	////	sprintf(sSource, "%s%s", "M01:\\FMEM\\MMACRO\\",name);
	////	sprintf(sSource, "%s%s", "M01:\\IC1\\MMACRO\\",name);
		sprintf(sDestFile, "%s%s", "M01:\\PRG\\MMACRO\\",name[btncursor]);
	//	if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sSource, M_FSOPEN_RDONLY, 0, &lFileDesc) != 0)
	//	{
	//	
	//		
	//	

	//		setWarningMessage(16,name);
	//	else
	//	{
	//		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) == 0)
	//	
	//		setWarningMessage(17,name);
	//		else
	//		setWarningMessage(18,name);
	//	}

	//	}
	//	

	if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) == 0)
	{
	setWarningMessage(17,name[btncursor]);
	}
	else

	{
		CopyFile1(name[btncursor]);
		
	}

		
	
	
}
void GCINITSCREEN::setWarningMessage(int warnnum,char *name)
{
	GBaseObject *pLbl;
	GTCHAR szText[60];

		char sDestFilename[2][60];

	sprintf(sDestFilename[0], "%s%s%s","File ",name," Copy Completed");
	sprintf(sDestFilename[1], "%s%s%s","File ",name," already Present",name);

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter X,Y,M,F,L adress only", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 18)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File access error.", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 3)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data protected can't edit", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 4)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data saved sucessfully", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 5)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data modified sucessfully", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 6)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please save modified Data", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 7)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Error: Program memory over", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 10)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File access error: Can't open file", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 11)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Error: Data dose not saved", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 12)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Program is running! can't edit", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 2)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "File copy error: File does not exists or improper file", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 16)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, sDestFilename[0], sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 17)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, sDestFilename[1], sizeof(szText)/sizeof(GTCHAR));


	GCSTextboxSetString( pLbl, szText );
}
void GCINITSCREEN::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCINITSCREEN::setSelectButton()
{
	GBaseObject *pBtn[20];
		char sDestFile[20][50],sSource[50];
	FS_STAT stat;
	long lFileDesc;	

	sprintf(sDestFile[0], "%s", "M01:\\PRG\\MMACRO\\IOLIST.CSV");
	sprintf(sDestFile[1], "%s", "M01:\\PRG\\MMACRO\\IOLISTL.CSV");
	sprintf(sDestFile[2], "%s", "M01:\\PRG\\MMACRO\\GCODE.CSV");
	sprintf(sDestFile[3], "%s", "M01:\\PRG\\MMACRO\\MCODE.CSV");
	sprintf(sDestFile[4], "%s", "M01:\\PRG\\MMACRO\\ALARM.CSV");
	sprintf(sDestFile[5], "%s", "M01:\\PRG\\MMACRO\\SYSTEMINFO.CSV");
	sprintf(sDestFile[6], "%s", "M01:\\PRG\\MMACRO\\COOLANT.CSV");
	sprintf(sDestFile[7], "%s", "M01:\\PRG\\MMACRO\\LUBRICATION.CSV");
	sprintf(sDestFile[8], "%s", "M01:\\PRG\\MMACRO\\HYDRAULIC.CSV");
	sprintf(sDestFile[9], "%s", "M01:\\PRG\\MMACRO\\ARM.CSV");
	sprintf(sDestFile[10], "%s", "M01:\\PRG\\MMACRO\\MAG.CSV");
	sprintf(sDestFile[11], "%s", "M01:\\PRG\\MMACRO\\CHIPCONVEY.CSV");
	sprintf(sDestFile[12], "%s", "M01:\\PRG\\MMACRO\\SPINDLE.CSV");
	
	//pBtn[0] = GCSGetChild(GetGBaseObject(), BUTTONIOLIST);
	//pBtn[1] = GCSGetChild(GetGBaseObject(), BUTTONIOLISTL);
	//pBtn[2] = GCSGetChild(GetGBaseObject(), BUTTONALARM);
	//pBtn[3] = GCSGetChild(GetGBaseObject(), BUTTONMCODE);
	//pBtn[4] = GCSGetChild(GetGBaseObject(), BUTTONGCODE);
	//pBtn[5] = GCSGetChild(GetGBaseObject(), BUTTONSYSINFO);

	pBtn[0] = GCSGetChild(GetGBaseObject(), DPBTN1);
	pBtn[1] = GCSGetChild(GetGBaseObject(), DPBTN2);
	pBtn[2] = GCSGetChild(GetGBaseObject(), DPBTN3);
	pBtn[3] = GCSGetChild(GetGBaseObject(), DPBTN4);
	pBtn[4] = GCSGetChild(GetGBaseObject(), DPBTN5);
	pBtn[5] = GCSGetChild(GetGBaseObject(), DPBTN6);
	pBtn[6] = GCSGetChild(GetGBaseObject(), DPBTN7);
	pBtn[7] = GCSGetChild(GetGBaseObject(), DPBTN8);
	pBtn[8] = GCSGetChild(GetGBaseObject(), DPBTN9);
	pBtn[9] = GCSGetChild(GetGBaseObject(), DPBTN10);
	pBtn[10] = GCSGetChild(GetGBaseObject(), DPBTN11);
	pBtn[11] = GCSGetChild(GetGBaseObject(), DPBTN12);
	pBtn[12] = GCSGetChild(GetGBaseObject(), DPBTN13);

	for(int i =0;i<13;i++)
	{
	if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile[i], &stat) == 0)
	{
	GCSButtonSetStatus(pBtn[i], 1);
	}
	else
	{
	GCSButtonSetStatus(pBtn[i], 0);
	}
	}
	
	
	
}
void GCINITSCREEN::setColorButton(int cursor)
{
	GBaseObject *pBtn[20];
		
	
	
	pBtn[0] = GCSGetChild(GetGBaseObject(), BDBTN1);
	pBtn[1] = GCSGetChild(GetGBaseObject(), BDBTN2);
	pBtn[2] = GCSGetChild(GetGBaseObject(), BDBTN3);
	pBtn[3] = GCSGetChild(GetGBaseObject(), BDBTN4);
	pBtn[4] = GCSGetChild(GetGBaseObject(), BDBTN5);
	pBtn[5] = GCSGetChild(GetGBaseObject(), BDBTN6);
	pBtn[6] = GCSGetChild(GetGBaseObject(), BDBTN7);
	pBtn[7] = GCSGetChild(GetGBaseObject(), BDBTN8);
	pBtn[8] = GCSGetChild(GetGBaseObject(), BDBTN9);
	pBtn[9] = GCSGetChild(GetGBaseObject(), BDBTN10);
	pBtn[10] = GCSGetChild(GetGBaseObject(), BDBTN11);
	pBtn[11] = GCSGetChild(GetGBaseObject(), BDBTN12);
	pBtn[12] = GCSGetChild(GetGBaseObject(), BDBTN13);

	for(int i =0;i<13;i++)
	{

	GCSButtonSetStatus(pBtn[i], 0);
	}
	
	
	GCSButtonSetStatus(pBtn[cursor], 1);

	
	
	
}
void GCINITSCREEN::clearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");
}

void GCINITSCREEN::CopyFile1(char *sName)
{
	DWORD dwStatus;
	FS_STAT stat;
	long lFileDesc;	
	long lReadNo = 5, lTotCnt = 0;
	long lDestFile,lDirDesc;;
	long lWriteNo;
	
	char sReadData[1000];
	char sDestFile[50],sSource[50];


	//sprintf(sSource, "%s%s", "M01:\\PRG\\USER\\",sName);
	//	sprintf(sSource, "%s%s", "M01:\\FMEM\\MMACRO\\",name);
		sprintf(sSource, "%s%s", "M01:\\IC1\\MMACRO\\",sName);
		sprintf(sDestFile, "%s%s", "M01:\\PRG\\MMACRO\\",sName);

	
	BUFFTYPE buf;
	dwStatus = melFSOpenDirectory(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)| ADR_OPE_DRIVE(0)), "M01:\\PRG\\USER\\", &lDirDesc);	// "M01:\\PRG\\USER\\"

		dwStatus = melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sSource, &stat); 

	if(dwStatus == 0)
	{
		if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sSource, M_FSOPEN_RDONLY, 0, &lFileDesc) != 0)
		{
			setWarningMessage(2,sName);
		}
	

	 if(melFSCreateFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, &lDestFile) != 0)
	{
			setWarningMessage(2,sName);
			
	}
	
		buf.lBuffSize = sizeof(sReadData);
		buf.lpBuff = sReadData;	
	
		while(lReadNo != 0)
		{
			lReadNo = 0;
			melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
			if(lReadNo != 0)
			{
				buf.lBuffSize = lReadNo;
				melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile, &buf, &lWriteNo);
				lTotCnt += lReadNo;
					
			}
			else
			{
				break;
			}
		}
		
	

	melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile);
	
	setWarningMessage(16,sName);
	}
	else
	{
		setWarningMessage(2,sName);
		lReadNo = 0;
	}
}

long GCINITSCREEN::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor=0;
	setColorButton(Cursor);
	return TRUE;
}

//long GCINITSCREEN::BUTTONALARMOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	
//	CopyFiles("ALARM.CSV");
//	return TRUE;
//}
//
//long GCINITSCREEN::BUTTONGCODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	CopyFiles("GCODE.CSV");
//	return TRUE;
//}
//
//long GCINITSCREEN::BUTTONIOLISTLOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	
//	CopyFiles("IOLISTL.CSV");
//	return TRUE;
//}
//
//long GCINITSCREEN::BUTTONIOLISTOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	CopyFiles("IOLIST.CSV");
//	return TRUE;
//}
//
//long GCINITSCREEN::BUTTONMCODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	CopyFiles("MCODE.CSV");
//	return TRUE;
//}
//

long GCINITSCREEN::HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

//long GCINITSCREEN::BUTTONSYSINFOOnClick(unsigned short usMessage, long lLParam, long lUParam)
//{
//	CopyFiles("SYSTEMINFO.CSV");
//	return TRUE;
//}

long GCINITSCREEN::DPBTN1OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor=0;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN2OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=1;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN3OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=2;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN10OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=9;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN11OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=10;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN12OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=11;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN13OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=12;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN4OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=3;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN5OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=4;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN6OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=5;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN7OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=6;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN8OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=7;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

long GCINITSCREEN::DPBTN9OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		Cursor=8;
	setColorButton(Cursor);
	CopyFiles(Cursor);
	return TRUE;
}

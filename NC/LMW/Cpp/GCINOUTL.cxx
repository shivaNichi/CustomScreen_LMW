#include "GCINOUTL.hpp"
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
static  bool bSetPasswordOn1=0;


extern "C"
{

void GCIDeleteGCINOUTL( GBaseObject *pObject )
{
	GCINOUTL *pPanel = (GCINOUTL*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCINOUTL( GBaseObject *pObject )
{
	GCINOUTL *pPanel = new GCINOUTL;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCINOUTL;
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
GCINOUTL::GCINOUTL()
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
GCINOUTL::~GCINOUTL()
{

}

#include "GCINOUTL.prc"

short GCINOUTL::CreateChildren( )
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

GPropertyInfo* GCINOUTL::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCINOUTL::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{

		
	/*static  bool bSetPasswordOn=0;
	static  bool bSetPasswordOn1=0;*/
	
	if(bSetPasswordOn1==1)
	{
		GBaseObject *pKeyButton[5];

								pKeyButton[0] = GCSGetChild(GetGBaseObject(), CHANGESTATUSBTN);
								pKeyButton[1] = GCSGetChild(GetGBaseObject(), ONBTN);
								pKeyButton[2] = GCSGetChild(GetGBaseObject(), OFFBTN);
			
	

	
								GCSButtonSetStringID(pKeyButton[0], ID_STRING00078);
								GCSButtonSetStringID(pKeyButton[1], ID_STRING00079);	
							GCSButtonSetStringID(pKeyButton[2], ID_STRING00080);
	}
	else
		bSetPasswordOn= 0;
	return TRUE;
}

long GCINOUTL::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild,*pTbl;
	GTCHAR inpBuff[10];
	char InpData[10];
	int Scount = 0;
	char sData[10];
	int i =0;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	unsigned short sretErr, usRow=START_POINT, usCol=START_POINT;
	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);

	switch(lLParam)
	{

			case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
				else
					ScreenTransition(INOUTXY_SCREEN);
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
		
			else
			{
				
				if(!bSetPasswordOn)
				{
					setWarningMessage(16);
					GCSTextboxSetString(pChild, (GTCHAR *)"");
					GCSTextboxSetPasswordStatus(pChild,true);
					bSetPasswordOn = true;
				}	
			}
			break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			else
				if(bSetPasswordOn1==1)
					changeStatus(1);
			
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
			else
				if(bSetPasswordOn1==1)
					changeStatus(0);
		break;
		
		case GK_F6:
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			DeleteAdress(usRow+ulIndex);
				break;
			case GK_F8:
				if((lUParam & KEY_SHIFT) != KEY_SHIFT){
			//ScreenTransition(INOUTXY_SCREEN);
				}
			break;
		case GK_F9:
			if((lUParam & 11) != 10){
			//ScreenTransition(KEY_HIST_SCREEN);
			}
			break;
		case GK_F10:
				ScreenTransition( EOS_SCREEN);
				break;
		case GK_RETURN:
				if(bSetPasswordOn)
				{
						bool bCorrectPwd = CheckPassword();
						if(bCorrectPwd)
						{
							//changeStatus();
							GBaseObject *pKeyButton[5];

								pKeyButton[0] = GCSGetChild(GetGBaseObject(), CHANGESTATUSBTN);
								pKeyButton[1] = GCSGetChild(GetGBaseObject(), ONBTN);
								pKeyButton[2] = GCSGetChild(GetGBaseObject(), OFFBTN);
			
	

	
								GCSButtonSetStringID(pKeyButton[0], ID_STRING00078);
								GCSButtonSetStringID(pKeyButton[1], ID_STRING00079);	
							GCSButtonSetStringID(pKeyButton[2], ID_STRING00080);

							clearWarningMessage();
							bSetPasswordOn1=1;
						}
						GCSTextboxSetString(pChild, (GTCHAR *)"");
						GCSTextboxSetPasswordStatus(pChild,false);
						if(!bCorrectPwd)
						{
							setWarningMessage(15);
							bSetPasswordOn = false;
						}
						bSetPasswordOn = false;
						
				}
				else
				{
				GCSTextboxGetString(pChild, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sData,inpBuff, sizeof(sData));
				clearWarningMessage();
				i=	checkAdress(sData);
				 if(i==0)
					WriteNewBit(sData);
				 else if(i==2)
					setWarningMessage(2);
				 GCSTextboxSetString( pChild, (GTCHAR *)"");
				 Fetchdata();
				 //displaydata();
				}
		
			break;
		case GK_DELETE:
				GCSTextboxGetString(pChild, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sData,inpBuff, sizeof(sData));

				Scount = strlen(sData);

				if(Scount != 0)
				{
					sData[strlen(sData)-1]= '\0';
					GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, sData, sizeof(sData));
					GCSTextboxSetString(pChild, inpBuff);
				}
				break;
			case GK_UP:
					// Up arrow press event
				/*	if(FileCorruptFlg != 1)
					{*/
						GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
						
						if(usRCcount >= 1 )
						{
							usRCcount--;
							if( (usRow == START_POINT) && ulIndex >  START_POINT)
							{
								GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);
								ulIndex = ulIndex - 1;
								displaydata();
								if((ulLineCcount -  ulIndex) >= TABLEROW_SIZE)
									{
										
										lEndCnt =  TABLEROW_SIZE;
										
									}
									else
									{
										
										lEndCnt =  ulLineCcount -  ulIndex;
									
									}
								
							
								
							}
							if(usRow != START_POINT)
							{
								usRow--;
							}
							
						}
						/* Setting Sub Cursor Number to 0th Row and First Col */
						GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);
				/*	}
					else
						SetWarningMessage(4);	*/
					break;
		case GK_DOWN:
					/*Down arrow press event */
					/*if(FileCorruptFlg != 1)
					{*/
					
						GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
						if( usRCcount < (ulLineCcount - 1) )														
						{ 
							usRCcount++;
							usRow ++;	
							
							if(usRow >= TABLEROW_SIZE  )
							{
								usRow--;
								ulIndex =  ulIndex + 1;	
								displaydata();
									if((ulLineCcount - ulIndex) >= TABLEROW_SIZE)
									{
										lEndCnt =  TABLEROW_SIZE;
									}
									else
									{
										lEndCnt = (ulLineCcount - ulIndex);
									}
						
							}
								
						}
						/* Setting Sub Cursor Number to 0th Row and First Col */
						GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);
				
					break;
		default:
			break;
		}
	return TRUE;
}

long GCINOUTL::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild,*pTbl;


	pChild = GCSGetChild(GetGBaseObject(), DATA);

	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}


		

	UpdateStatus();




	return TRUE;
}
void GCINOUTL::Fetchdata()
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

		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOL";
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
			while(s!=NULL)
			{
				strcpy(sAdress[i],s);
				s = strtok(NULL, "\n");
				i++;
			}
			ulLineCcount=i;
			free(sFileData);
	}
		displaydata();
		
	
		
	




}

void GCINOUTL::ScreenTransition(short ScreenNo)
{
	
	free(sCommentsData);
	sCommentsData = NULL;
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}


long GCINOUTL::HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
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
	char alldata[100][80];
	int nline=0;
	CommentsDatal commentdata[100];
	uCommentCount=0;


	usRCcount = START_POINT;
		usRCcount = START_POINT;
		ulIndex = usRCcount;
		ulLineCcount=START_POINT;
		

	sCommentsData = (CommentsDatal *)malloc(120 * sizeof(CommentsDatal) );
	if(sCommentsData == NULL)
	{
		//return -1;
	}
	else{
		memset(sCommentsData ,0, sizeof(CommentsDatal));
	//	return 0;
	}

		memset(alldata,0,sizeof(alldata));
		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOLISTL.CSV";

		dwStatus=melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat);
		if(dwStatus==0)

	{
		lCurSize = (long)stat.lFileSize ;
		sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));

	
		buf.lBuffSize = (long)stat.lFileSize;
		buf.lpBuff = sFileData;




			if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
			melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
			melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
				}
		
		s=strtok(sFileData,"\n");
	//	s=strtok(NULL,"\n");
		while(s!=NULL)
		{
			if(strncmp( s,"L",1)==0)
			{
			strcpy(alldata[nline],s);
			
			nline++;
			}
			s=strtok(NULL,"\n");
		}
		int j=0;
		for(int i=0;i<nline;i++)
		{
			
			s=strtok(alldata[i],",");
			strcpy(commentdata[i].Adress,s);
			s=strtok(NULL,",");
			strcpy(commentdata[i].comment,s);
		/*	j++;*/
			/*s=strtok(NULL,",");
			if(strlen(s)>2)
			{
			strcpy(commentdata[j].Adress,s);
			s=strtok(NULL,",");
			strcpy(commentdata[j].comment,s);
			j++;
			}*/
		}
		
		uCommentCount=nline;
		SetSamplingData(commentdata,uCommentCount);
		free(sFileData);
	}
		else
		{
			
			if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		//	melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
			melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
				}
			}

	if(ulLineCcount >= TABLEROW_SIZE)
			{
				lEndCnt = TABLEROW_SIZE;
			}
			else
			{
				lEndCnt = ulLineCcount;
			}

	Fetchdata();


	//displaydata();
	return TRUE;
}


long GCINOUTL::checkAdress(char *dat)
{
	GBaseObject *pData;
	int i=-1;
	char strlong[40];

	long Subsection=0;
	char *eptr;
	char *s = NULL;
	int error=0;

	pData  = GCSGetChild(GetGBaseObject(), DATA);

	GTCHAR inpBuff[40];
	char cInputData[40];
	GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(cInputData));
	
	if(strncmp( cInputData,"L",1)==0)
	{
		i=4;
	s=strtok(cInputData,"L");
	
		sprintf(strlong,"%s",s);
	}
	
	if(i>=0)
	{
		error=checkRange(strlong,i);
		if(error!=0)
			return 2;
		else
			return 0;

	}
	else
	{
		setWarningMessage(1);
		return 1;
	}
	
}

long GCINOUTL::checkRange(char *dat, int cellpos)
{
//	GBaseObject *pErr;

Datarange drange[05] = {{0,8191},{0,8191},{0,10239},{0,1024},{0,511}};




	GTCHAR szText[20];
	double ddata;
	short lErr = 0;
	short lAlpha = 0;
	short i;
	short len = strlen(dat);


	switch(cellpos)
	{
	case 4:
	case 3:
	case 5:
	// Check for alphabets
	for(i = 0; i < len; i++){
		if(! ( ( (dat[i] >= '0') && (dat[i] <= '9') ) || (dat[i] == '.') || (dat[i] == '-') || (dat[i] == '+') ) ) {
			lAlpha = 1;
			break;
		}			
	
		if( (dat[i] == '-') || (dat[i] == '+') ){
			if (i != 0){
				lAlpha = 1;
				break;
			}
		}
	} 
	break;
	default:
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
		break;
	}
	if(  (lAlpha == 2) ){
	//	GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "1", sizeof(szText)/sizeof(GTCHAR));
	//	GCSTextboxSetString( pErr, szText );
		return 2;
	}
	if(lAlpha != 1)
	{
		ddata = atof(dat);
		// Check for range
		if( (ddata < drange[cellpos].minValue) || (ddata > drange[cellpos].maxValue) )
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
void GCINOUTL::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[60];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter L Adress only", sizeof(szText)/sizeof(GTCHAR));
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
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Incorrect Password",	sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 16)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Input the Password",	sizeof(szText)/sizeof(GTCHAR));
	
	GCSTextboxSetString( pLbl, szText );
}
void GCINOUTL::clearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");
}

void GCINOUTL::WriteNewBit(char *sAdd)
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
	char sAllData[10];
	memset(sAllData,0,sizeof(sAllData));
	bool CheckDup=0;
	int j=0;


	char sDestFile[] = "M01:\\PRG\\MMACRO\\IOL";


		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) != 0)
		{
	
		 if(melFSCreateFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, &lDestFile) == 0)
			 melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile);
		 melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat);
		
		}

		lCurSize = 500;//(long)stat.lFileSize+10 ;
		sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));

	
	/*	buf.lBuffSize = (long)stat.lFileSize+10;
		buf.lpBuff = sFileData;

	if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	}*/

	
	
	//if(ulLineCcount==0)
		goto label;
	/*	 CheckDup=1;
	for(j=0;j<ulLineCcount;j++)
	{
		if(strncmp(sAdd,sAdress[j],10)==0)
		{
			CheckDup=0;
			break;
		}
	}*/
	if(CheckDup)
	{
	label:
		dwStatus = melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, 0, &lFileDesc) ;
		//File Write
			if (dwStatus == 0)
			{
					/*
					sprintf(sAllData,"%s\n",sAdd);
					strcat(sFileData,sAllData);*/
				
						

				char *s;
				char strlong[40];
				long Subsection=0;
				char *eptr;
				for(int i=0;i<32;i++)
				{
						if(strncmp( sAdd,"L",1)==0)
						{
								s=strtok(sAdd,"L");
								Subsection=strtol( s,&eptr,10);
								//Subsection=Subsection+50000;
								sprintf(sAllData,"%s%d\n","L",Subsection+i);
						}
						
						strcat(sFileData,sAllData);
				}
				
	
							buf.lBuffSize =strlen(sFileData)+100;
						buf.lpBuff = sFileData;
				
					dwStatus = melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, &lWriteNo);
					melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
			}
			
	}
	free(sFileData);

}
void GCINOUTL::displaydata()
{

	GBaseObject *pTbl;
	GTCHAR KeyText[KEY_DATA_SIZE];
	char KeyData[KEY_DATA_SIZE];
	
		unsigned short i, ErrCode;
	

	pTbl = GCSGetChild(GetGBaseObject(),HIST_TABLE);
	
	if((ulLineCcount - ulIndex) >= TABLEROW_SIZE)
									{
										lEndCnt =  TABLEROW_SIZE;
									}
									else
									{
										lEndCnt = (ulLineCcount - ulIndex);
									}
		
	for(i = 0; i < lEndCnt; i++)
	{
		sprintf(KeyData, "%s",sAdress[i+ulIndex]  );
		GRCMultiByteToUnicode(0, KeyText, KeyData,  sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 0, &ErrCode);
		CommentsDatal commentdata[100];
		GetSamplingData(commentdata,uCommentCount);
		bool setbit=1;
		int j;
		for( j=0;j<uCommentCount;j++)
		{
			if(strncmp(sCommentsData[j].Adress,KeyData,10)==0)
			{
				setbit=1;
				break;
			}
			else
			setbit=0;

			//	strcpy(KeyData,sCommentsData[j].comment);
			
		}
		if(setbit)
			strcpy(KeyData,sCommentsData[j].comment);
		else

		sprintf(KeyData, "%s","" );
		GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 1, &ErrCode);

		bool bit=Readstatus(sCommentsData[j].Adress);
		sprintf(KeyData,"%d",bit );
		GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 2, &ErrCode);
	}
}
bool GCINOUTL::Readstatus(char *cInputData)
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

	if(strncmp( cInputData,"L",1)==0)
	{
	s=strtok(cInputData,"L");
	Subsection=strtol( s,&eptr,10);
	Subsection=Subsection+50000;
	}
	


melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
		   M_SEC_PLC_DEV_BIT, Subsection ,0, (void *)&ldata, T_LONG);

if(ldata==0)
return 0;
else 
return 1;

}
void GCINOUTL::SetSamplingData( CommentsDatal *sCommentData, long usIdx)
{	
	/*long i = usIdx;


	for( ; i< 119; i++)*/

	for(int i=0;i<usIdx;i++)
	{		
		strncpy(sCommentsData[i].Adress, sCommentData[i].Adress, 10);
		strncpy(sCommentsData[i].comment, sCommentData[i].comment, 30);
	
		
	}
	
	
}

void GCINOUTL::GetSamplingData( CommentsDatal *sCommentData, long usIdx)
{
	//long i = usIdx;
		//for(; i < 120; i++)
		for(int i=0;i<usIdx;i++)
		{
		strncpy(sCommentData[i].Adress, sCommentsData[i].Adress, 10);
		strncpy(sCommentData[i].comment, sCommentsData[i].comment, 30);
	
			
		}

	
}
void GCINOUTL::DeleteAdress(int Cursor)
{
	char *sFileData;
	char *sFileWriteData;
	BUFFTYPE buf;
	DWORD dwStatus;
	FS_STAT stat;
	long lFileDesc;	
	long lReadNo ;
	long lDestFile;
	long lWriteNo;
	long lCurSize;
	char sAllData[100][30];
	
	char *s;


		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOL";
		memset(sAllData,0,sizeof(sAllData));
	//	memset(sFileWriteData,0,sizeof(sFileWriteData));


	if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) == 0)
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
	
	char lsAdress[200][10];
	lCurSize = (long)stat.lFileSize+10 ;
	sFileWriteData = (char *)malloc(lCurSize * sizeof(char) );
	memset(sFileWriteData ,0, sizeof(sFileWriteData));
	s = strtok(sFileData, "\n");
	//for(int i=0;i<lEndCnt;i++)
	for(int i=0;i<ulLineCcount;i++)

	{
		
		//strncpy(sAllData[i],s,20);
		sprintf(lsAdress[i],"%s\n",s);
		if(i!=Cursor)
		{
		strcat(sFileWriteData,lsAdress[i]);
		}
		s = strtok(NULL, "\n");

	}
	free(sFileData);

	//lEndCnt--;
	ulLineCcount--;
	}
		

		buf.lBuffSize = (long)stat.lFileSize+10;
		buf.lpBuff = sFileWriteData;
	if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, 0, &lFileDesc) == 0){
			dwStatus = melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, &lWriteNo);
		melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	}
		free(sFileWriteData);
	if(ulIndex>0)
		ulIndex--;
	ClearTable();
	Fetchdata();

}

//bool GCINOUTL::CheckPassword()
//{	
//	GBaseObject *pChild;
//	char operData[60];
//	GTCHAR inpBuffPwd[60];
//
//	GTCHAR ReadBuffPwd[60];
//	long ReadPwdData;
//
//	pChild = GCSGetChild(GetGBaseObject(), DATA);
//	
//	GCSTextboxGetString( pChild, inpBuffPwd, sizeof(inpBuffPwd)/sizeof(GTCHAR) );
//	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), operData, inpBuffPwd, sizeof(operData));
//
//	//107/130
//	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),M_SEC_MPRM_PLC_CONST, M_SSEC_MP_PLC_CONST(129), 0, &ReadPwdData, T_LONG);
//	//GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), ReadPwdData, ReadBuffPwd, sizeof(ReadPwdData));
//
//	if( atoi(operData) == ReadPwdData && ReadPwdData != 0)
//	{
//		GCSTextboxSetString(pChild, (GTCHAR *)"");
//		return TRUE;
//	}
//	else
//	{
//		/*if(strlen(operData) == 0)
//			SetWarningMessage(2);
//		else*/
//			setWarningMessage(15);
//		GCSTextboxSetString(pChild, (GTCHAR *)"");
//		return FALSE;
//	}
//	
//}

bool GCINOUTL::CheckPassword()
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
//bool GCINOUTL::CheckPassword()
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
//	char sPath[] = "M01:\\PRG\\MMACRO\\1234";
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
//			if (dwStatus == SUCCESS){
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
//

void GCINOUTL::changeStatus(long Bit)
{
	char strlong[40];
	char *s = NULL;
	long Subsection=0;
	char *eptr;
	GBaseObject *pTbl;
	GTCHAR KeyText[KEY_DATA_SIZE];
	char KeyData[KEY_DATA_SIZE];
	unsigned short sretErr, usRow=START_POINT, usCol=START_POINT;
	long ldata=Bit;
	

	pTbl = GCSGetChild(GetGBaseObject(),HIST_TABLE);
	GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
	GCSNCTableGetCellString(pTbl,KeyText,10,usRow,0, &sretErr);
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), KeyData,KeyText, sizeof(KeyData));

	if(strncmp( KeyData,"L",1)==0)
	{
	s=strtok(KeyData,"L");
	Subsection=strtol( s,&eptr,10);
	Subsection=Subsection+50000;
	}
	


//melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
//		   M_SEC_PLC_DEV_BIT, Subsection ,0, &ldata, T_LONG);
//if(ldata==0)
//ldata=1;
//else if(ldata==1)
//ldata=0;
melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
		   M_SEC_PLC_DEV_BIT,Subsection,0, (void *)&ldata, T_LONG); 

displaydata();


}
void GCINOUTL::ClearTable()
{
	unsigned short  sretErr;  // error code
	unsigned short i, j;
	GBaseObject *pTbl;

	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	for(i = 0 ; i < TABLEROW_SIZE; i++)
	{
		for(j = 0; j < 3; j++)
		{
			GCSNCTableSetCellString(pTbl, (GTCHAR *)"", i, j, &sretErr);
		}
	}
	
}

void GCINOUTL::UpdateStatus()
{
	GBaseObject *pTbl;
	GTCHAR inpBuff[10],KeyText[2];
	char InpData[10],KeyData[2];
	unsigned short sretErr;
	
	for(int i=0;i<15;i++)
	{
	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	GCSNCTableGetCellString(pTbl, inpBuff, 10, i, 0, &sretErr);
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), InpData, inpBuff, sizeof(InpData));
	if(strlen(InpData)>1)
	{
	bool bit=Readstatus(InpData);
		sprintf(KeyData,"%d",bit );
		GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 2, &sretErr);
	}
	}
}


long GCINOUTL::CHANGESTATUSBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild,*pTbl;
	

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(!bSetPasswordOn)
	{
		setWarningMessage(16);
		GCSTextboxSetString(pChild, (GTCHAR *)"");
		GCSTextboxSetPasswordStatus(pChild,true);
		bSetPasswordOn = true;
		

	}	
			
	return TRUE;
}


long GCINOUTL::DELETBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pTbl;
	
	unsigned short sretErr, usRow=START_POINT, usCol=START_POINT;
	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	
	GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
	DeleteAdress(usRow+ulIndex);
	return TRUE;
}

long GCINOUTL::HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( EOS_SCREEN);
	return TRUE;
}

long GCINOUTL::OFFBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bSetPasswordOn1==1)
		changeStatus(0);
	return TRUE;
}

long GCINOUTL::ONBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bSetPasswordOn1==1)
				changeStatus(1);
	return TRUE;
}

long GCINOUTL::BTNIOLISTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(INOUTXY_SCREEN);
	return TRUE;
}

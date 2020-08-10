#include "GCINOUTXY.hpp"
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

void GCIDeleteGCINOUTXY( GBaseObject *pObject )
{
	GCINOUTXY *pPanel = (GCINOUTXY*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCINOUTXY( GBaseObject *pObject )
{
	GCINOUTXY *pPanel = new GCINOUTXY;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCINOUTXY;
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
GCINOUTXY::GCINOUTXY()
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
GCINOUTXY::~GCINOUTXY()
{

}

#include "GCINOUTXY.prc"

short GCINOUTXY::CreateChildren( )
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

GPropertyInfo* GCINOUTXY::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCINOUTXY::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
					ScreenTransition(INOUTL_SCREEN);
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
		case GK_F6:
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			DeleteAdress(usRow+ulIndex);
				break;
		case GK_F8:
			if((lUParam & 11) != 10){
			//ScreenTransition(INOUTL_SCREEN);
			}
			break;
		case GK_F9:
			if((lUParam & 11) != 10){
			//ScreenTransition(KEY_HIST_SCREEN);
			}
			break;
		case GK_F10:
			if((lUParam & 11) != 10){
				ScreenTransition( EOS_SCREEN);
			}
				break;
		case GK_RETURN:

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

long GCINOUTXY::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
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
void GCINOUTXY::Fetchdata()
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

		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOXY";
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

void GCINOUTXY::ScreenTransition(short ScreenNo)
{
	free(sCommentsData);
					sCommentsData = NULL;
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}


long GCINOUTXY::HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
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
	CommentsData commentdata[100];
	uCommentCount=0;


	usRCcount = START_POINT;
		usRCcount = START_POINT;
		ulIndex = usRCcount;
		ulLineCcount=START_POINT;
		

	sCommentsData = (CommentsData *)malloc(120 * sizeof(CommentsData) );
	if(sCommentsData == NULL)
	{
		//return -1;
	}
	else{
		memset(sCommentsData ,0, sizeof(CommentsData));
	//	return 0;
	}

		memset(alldata,0,sizeof(alldata));
		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOLIST.CSV";

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
	//	}
			/*long	ldata=4;
					melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
						   55,109504,0, &ldata, T_LONG);*/
		s=strtok(sFileData,"\n");
		s=strtok(NULL,"\n");
		while(s!=NULL)
		{
			strcpy(alldata[nline],s);
			s=strtok(NULL,"\n");
			nline++;
		}
		//ldata=nline;
				/*	melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
						   55,109505,0, &ldata, T_LONG);*/
		int j=0;
		for(int i=0;i<nline-1/*nline*/;i++)
		{
			
			if(strlen(alldata[i])>3)
			{
			s=strtok(alldata[i],",");
			if(s!=NULL)
			{
			strcpy(commentdata[j].Adress,s);
			s=strtok(NULL,",");
			if(s!=NULL)
			{
			strcpy(commentdata[j].comment,s);
			j++;
			}
			}
			s=strtok(NULL,",");
			if(strlen(s)>2)
			{
			if(s!=NULL)
			{
			strcpy(commentdata[j].Adress,s);
			s=strtok(NULL,",");
			if(s!=NULL)
			{
			strcpy(commentdata[j].comment,s);
			j++;
			}
			}
			}
			}
			/*GBaseObject *pTbl;
	GTCHAR KeyText[KEY_DATA_SIZE];
	char KeyData[KEY_DATA_SIZE];
	
		unsigned short ErrCode;
	

	pTbl = GCSGetChild(GetGBaseObject(),HIST_TABLE);
			strcpy(KeyData,commentdata[1].Adress);
		
		GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, 1, 1, &ErrCode);
			strcpy(KeyData,commentdata[1].comment);
		
		GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, 2, 1, &ErrCode);
			ldata=10+j;
			melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
						   55,109505+j,0, &ldata, T_LONG);*/
		}
	/*	ldata=100;
					melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
						   55,109506,0, &ldata, T_LONG);*/
		uCommentCount=j;
	SetSamplingData(commentdata,uCommentCount);
	free(sFileData);
	/*ldata=7;
					melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
						   55,109600,0, &ldata, T_LONG);*/
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


long GCINOUTXY::checkAdress(char *dat)
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
	
	if(strncmp( cInputData,"X",1)==0)
	{
	i=0;
	s=strtok(cInputData,"X");
	sprintf(strlong,"%s","0x");
	strcat(strlong,s);
	Subsection=strtol( strlong,&eptr,0) ;
		sprintf(strlong,"%d",Subsection);
	}
	else if(strncmp( cInputData,"Y",1)==0)
	{
		i=1;
	s=strtok(cInputData,"Y");
	sprintf(strlong,"%s","0x");
	strcat(strlong,s);
	Subsection=strtol( strlong,&eptr,0) ;
	sprintf(strlong,"%d",Subsection);

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

long GCINOUTXY::checkRange(char *dat, int cellpos)
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
void GCINOUTXY::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[60];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter X,Y Adress only", sizeof(szText)/sizeof(GTCHAR));
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

	GCSTextboxSetString( pLbl, szText );
}
void GCINOUTXY::clearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");
}

void GCINOUTXY::WriteNewBit(char *sAdd)
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


	char sDestFile[] = "M01:\\PRG\\MMACRO\\IOXY";


		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat) != 0)
		{
	
		 if(melFSCreateFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_WRONLY, &lDestFile) == 0)
			 melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lDestFile);
		 melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat);
		
		}

		lCurSize = 500;//(long)stat.lFileSize+10 ;
		sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));

	/*
		buf.lBuffSize = (long)stat.lFileSize+10;
		buf.lpBuff = sFileData;*/

	/*if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	}*/

	
	
//	if(ulLineCcount==0)
		goto label;
	/*CheckDup=1;
	for( j=0;j<ulLineCcount;j++)
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
					
					/*sprintf(sAllData,"%s\n",sAdd);
					strcat(sFileData,sAllData);
				*/
				char *s;
				char strlong[40];
				long Subsection=0;
				char *eptr;
				for(int i=0;i<32;i++)
				{
						if(strncmp( sAdd,"X",1)==0)
						{
						s=strtok(sAdd,"X");
						sprintf(strlong,"%s","0x");
						strcat(strlong,s);
						Subsection=strtol( strlong,&eptr,0) ;
						/*Subsection=Subsection+1;*/
						sprintf(sAllData,"%s%X\n","X",Subsection+i);
						}
						else if(strncmp( sAdd,"Y",1)==0)
						{
						s=strtok(sAdd,"Y");
						sprintf(strlong,"%s","0x");
						strcat(strlong,s);
						Subsection=strtol( strlong,&eptr,0) ;
						/*Subsection=Subsection+10000;*/
						sprintf(sAllData,"%s%X\n","Y",Subsection+i);
						}
						strcat(sFileData,sAllData);
				}
						//sprintf(sFileData,"%s",sAdd);//EXTRA LINE

						int c =strlen(sFileData);
						buf.lBuffSize =strlen(sFileData)+100;
						buf.lpBuff = sFileData;
				
					dwStatus = melFSWriteFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, &lWriteNo);
					melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
			}
			
	}
	free(sFileData);

}
void GCINOUTXY::displaydata()
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
		CommentsData commentdata[100];
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
bool GCINOUTXY::Readstatus(char *cInputData)
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
void GCINOUTXY::SetSamplingData( CommentsData *sCommentData, long usIdx)
{	
	/*long i = usIdx;


	for( ; i< 119; i++)*/

	for(int i=0;i<usIdx;i++)
	{		
		strncpy(sCommentsData[i].Adress, sCommentData[i].Adress, 10);
		strncpy(sCommentsData[i].comment, sCommentData[i].comment, 30);
	
		
	}
	
	
}

void GCINOUTXY::GetSamplingData( CommentsData *sCommentData, long usIdx)
{
	//long i = usIdx;
		//for(; i < 120; i++)
		for(int i=0;i<usIdx;i++)
		{
		strncpy(sCommentData[i].Adress, sCommentsData[i].Adress, 10);
		strncpy(sCommentData[i].comment, sCommentsData[i].comment, 30);
	
			
		}

	
}
void GCINOUTXY::DeleteAdress(int Cursor)
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
	char sAllData[200][30];
	
	char *s;


		char sDestFile[] = "M01:\\PRG\\MMACRO\\IOXY";
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

void GCINOUTXY::UpdateStatus()
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

void GCINOUTXY::ClearTable()
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

long GCINOUTXY::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCINOUTXY::BUTTONDELETEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pTbl;


	
	unsigned short sretErr, usRow=START_POINT, usCol=START_POINT;
	
	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
	DeleteAdress(usRow+ulIndex);
	return TRUE;
}

long GCINOUTXY::BUTTONHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	free(sCommentsData);
					sCommentsData = NULL;
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), EOS_SCREEN, 0), FALSE);
	return TRUE;
}

long GCINOUTXY::BTNLATCHOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(INOUTL_SCREEN);
	return TRUE;
}

#include "GCALARMHIST.hpp"
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

void GCIDeleteGCALARMHIST( GBaseObject *pObject )
{
	GCALARMHIST *pPanel = (GCALARMHIST*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCALARMHIST( GBaseObject *pObject )
{
	GCALARMHIST *pPanel = new GCALARMHIST;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCALARMHIST;
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
GCALARMHIST::GCALARMHIST()
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
GCALARMHIST::~GCALARMHIST()
{

}

#include "GCALARMHIST.prc"

short GCALARMHIST::CreateChildren( )
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

GPropertyInfo* GCALARMHIST::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCALARMHIST::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{

	GBaseObject *pChild,*pTbl,*plabel;
	GTCHAR inpBuff[10];
	char InpData[10];
	int Scount = 0;
	char sData[10];
	int i =0;
	GTCHAR KeyText[60];
	char KeyData[60];
	bool bit=0;
	char *Remedy;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	unsigned short sretErr, usRow=START_POINT, usCol=START_POINT;
	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	//plabel = GCSGetChild(GetGBaseObject(), LABELREM);

			

	switch(lLParam)
	{
		
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT)
				{
				
				// Changing the screen to Monitor screen.
					ScreenTransition( HMI_SCREEN);
				}
				else if( ((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC) )
				{
					ScreenTransition( PREV_SCREEN);
				}
				
			break;
				case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			if((lUParam & 11) == 10){
				GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				GCSNCTableGetCellString(pTbl,KeyText,20,usRow,0, &sretErr);
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), KeyData,KeyText, sizeof(KeyData));
				 bit=Readstatus(KeyData);
				 ClearTable();
				if(bit==1)
				{
					ClearTable();
					LoadHtmlFile(KeyData);
					/*Remedy=Fetchcomment(KeyData);
					sprintf(KeyData, "%s", Remedy);
				GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
				GCSTextboxSetString(plabel,KeyText);
		*/	//	GCSNCTableSetCellString(pTbl, KeyText, usRow, 2, &sretErr);
				}

			}
			else if( ((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC) )
			{
				ScreenTransition( INOUTXY_SCREEN);
			}
			
			break;
			case GK_F8:
					if((lUParam & 11) != 10){
				//ScreenTransition(SAMPLING_SCREEN);
					}
			break;
		case GK_F3:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						ScreenTransition(HMI_EDIT_SCREEN);
						
					}
					else
					{
						ScreenTransition( INOUTL_SCREEN);
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
		case GK_F4:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						ScreenTransition(DIAG_SCREEN);

						
					}
					else
					{
						ScreenTransition( MCODE_SCREEN);
					}
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
			case GK_F5:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						ScreenTransition(MAINTENANCE_SCREEN);
						break;
					}
					else
					{
						ScreenTransition(GCODE_SCREEN );
					}
					
					break;
			case GK_F6:			
		
				ScreenTransition(INIT_SCREEN);
			break;
			case GK_F10:
				ScreenTransition( EOS_SCREEN);
				break;
		default:
			break;
		}
	return TRUE;
}

long GCALARMHIST::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
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

long GCALARMHIST::HIST_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

void GCALARMHIST::UpdateStatus()
{
	GBaseObject *pTbl;
	GTCHAR inpBuff[KEY_DATA_SIZE],KeyText[KEY_DATA_SIZE];
	char InpData[KEY_DATA_SIZE],KeyData[KEY_DATA_SIZE];
	unsigned short sretErr;
	int nNoofBit=0;
	
	
	/*AlarmOnbit[0]=1;
	ulLineCcount=1;*/

	pTbl = GCSGetChild(GetGBaseObject(),HIST_TABLE);
	for(int j=0;j<ulLineCcountXL;j++)
	{
		bool bit=Readstatus(SAlarmDataHist[j].Adress);
			if(bit==1)
			{	
				AlarmOnbit[nNoofBit]=j;
				nNoofBit++;
			}
			
	}
	ulLineCcount=nNoofBit;

	/*AlarmOnbit[0]=1;
	AlarmOnbit[1]=3;
	AlarmOnbit[2]=11;
	AlarmOnbit[3]=13;
	AlarmOnbit[4]=21;
	AlarmOnbit[5]=31;
	AlarmOnbit[6]=41;
	AlarmOnbit[7]=43;
	AlarmOnbit[8]=53;*/
	
	for(int i=0;i<15;i++)
	{
	//pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	//GCSNCTableGetCellString(pTbl, inpBuff, 10, i, 0, &sretErr);
	//GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), InpData, inpBuff, sizeof(InpData));
	//	if(strlen(InpData)>1)
	//	{
	if(AlarmOnbit[i]>=0)
	{
		if(strlen(SAlarmDataHist[AlarmOnbit[i]+ulIndex].Adress)>1)
		{

			sprintf(KeyData, "%s",SAlarmDataHist[AlarmOnbit[i]+ulIndex].Adress  );
			GRCMultiByteToUnicode(0, KeyText, KeyData,  sizeof(KeyText)/sizeof(GTCHAR));
			GCSNCTableSetCellString(pTbl, KeyText, i, 0, &sretErr);
	

			sprintf(KeyData, "%s",SAlarmDataHist[AlarmOnbit[i]+ulIndex].Comment );
			GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
			GCSNCTableSetCellString(pTbl, KeyText, i, 1, &sretErr);

			//bool bit=Readstatus(InpData);
			//if(bit==1)
			//{
			GCSNCTableSetCellBackColor(pTbl, CURSOR_COLOR,  i, 0, &sretErr);
			GCSNCTableSetCellBackColor(pTbl, CURSOR_COLOR,  i, 1, &sretErr);
			GCSNCTableSetCellBackColor(pTbl, CURSOR_COLOR,  i, 2, &sretErr);

		/*	}
			if(bit==0)
			{
			GCSNCTableSetCellBackColor(pTbl, DEFAULT_COLOR,  i, 0, &sretErr);
			GCSNCTableSetCellBackColor(pTbl, DEFAULT_COLOR,  i, 1, &sretErr);
			GCSNCTableSetCellBackColor(pTbl, DEFAULT_COLOR,  i, 2, &sretErr);

			}*/
			/*sprintf(KeyData,"%d",bit );
			GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
			GCSNCTableSetCellString(pTbl, KeyText, i, 2, &sretErr);*/
		}
	}
	}
}
bool GCALARMHIST::Readstatus(char *cInputData)
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

	if(strncmp( cInputData,"F",1)==0)
	{
	s=strtok(cInputData,"F");
	Subsection=strtol( s,&eptr,10);
	Subsection=Subsection+40000;
	}
	


melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
		   M_SEC_PLC_DEV_BIT, Subsection ,0, (void *)&ldata, T_LONG);

if(ldata==0)
return 0;
else 
return 1;

}

long GCALARMHIST::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
		usRCcount = START_POINT;
		usRCcount = START_POINT;
		ulIndex = usRCcount;
		ulLineCcount=START_POINT;
		ulLineCcountXL=START_POINT;

		lEndCnt=0;

		GBaseObject *pChildHtml;
	
	pChildHtml= GCSGetChild(GetGBaseObject(), HTMLBROWSER);

	GTCHAR FileName[50];
	char TempData[50];

	
		for(int i=0;i<2050;i++)
			AlarmOnbit[i]=-1;
	Fetchdata();

	long ldata=1;
	//for(int J=0;J<2048;J++)
	//melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
	//	   M_SEC_PLC_DEV_BIT,40000+J,0, (void *)&ldata, T_LONG); 
		
	return TRUE;
	
}


void GCALARMHIST::Fetchdata(long sOffset)
{

	DWORD dwStatus;
	FS_STAT stat;
	long lFileDesc;	
	long lReadNo ;
	long lDestFile;
	long lWriteNo;
	BUFFTYPE buf;
	char sFileData[3000];
	long lCurSize,lReadOff;;
	char *s,*s1;
	long countsize=0;
	
		sOffset=0; 

		char sDestFile[] = "M01:\\PRG\\MMACRO\\ALARM.CSV";
			//memset(sAdress ,0, sizeof(sAdress));


		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat)== 0)
		{

		lCurSize = 3000;//(long)stat.lFileSize ;
		/*sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));*/

	
		buf.lBuffSize = 3000;//(long)stat.lFileSize;
		buf.lpBuff = sFileData;

		if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		melFSLseekFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, sOffset, M_FSLSEEK_TOP, &lReadOff);
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		//melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
		}

		
		bool bInit=1;
		while(/*countsize!=(long)stat.lFileSize&&*/countsize<=((long)stat.lFileSize-1))
		{
			int i =0;
			s = strtok(sFileData, "\n");
			if(bInit==1||i!=0)
			countsize+=strlen(s)+1;
			if(bInit==1)
			{
				s = strtok(NULL, "\n");
				bInit=0;
			}
			while(s!=NULL&i<15)
			{
				if(i!=0)
				s = strtok(NULL, "\n");
				if(s!=NULL)
				{
				countsize+=strlen(s);
				strcpy(sAdress[i],s);
				
				i++;
				}
			}
			countsize+=i;
			ulLineCcountXL+=i;

			int rem =ulLineCcountXL%15;
				if(rem==0)
					rem=(ulLineCcountXL-15);
				else
				rem=ulLineCcountXL-rem;


				for(int j=rem,k=0;j<ulLineCcountXL;j++,k++)
				{
				s1=strtok(sAdress[k],",");
				strcpy(SAlarmDataHist[j].Adress,s1);
				s1=strtok(NULL,",");
				strcpy(SAlarmDataHist[j].Comment,s1);
				
				}
		
		melFSLseekFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, countsize, M_FSLSEEK_TOP, &lReadOff);
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		
		}

melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	
			//int i =0;
			//s = strtok(sFileData, "\n");
			//countsize=strlen(s);
			//while(s!=NULL&i<15)
			//{
			//	
			//	s = strtok(NULL, "\n");
			//	countsize+=strlen(s);
			//	
			//	
			//	i++;
			//}
			//ulLineCcount=i;

	



		/*	int i =0;
			s = strtok(sFileData, "\n");
			s=strtok(NULL,",");
			while(s!=NULL)
			{
				if(strncmp( s,"A",1)==0)
				{
				strcpy(SAlarmDataHist[i].Adress,s);
				s=strtok(NULL,",");
				if(s!=NULL)
				strcpy(SAlarmDataHist[i].Comment,s);
				s=strtok(NULL,"\n");
				if(s!=NULL)
				strcpy(SAlarmDataHist[i].Remedy,s);
					i++;
				}
				s=strtok(NULL,",");*/
				
			
			
			//}
		//	ulLineCcount=i;
		//	free(sFileData);
	}

displaydata();

	




}
void GCALARMHIST::ScreenTransition(short ScreenNo)
{
	
	/*	free(sSamplingData);
		sSamplingData = NULL;*/
	
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

void GCALARMHIST::ClearTable()
{
	unsigned short  sretErr;  // error code
	unsigned short i, j;
	GBaseObject *pTbl;

	pTbl = GCSGetChild(GetGBaseObject(), HIST_TABLE);
	for(i = 0 ; i < TABLEROW_SIZE; i++)
	{
		/*for(j = 0; j < 3; j++)
		{*/
			GCSNCTableSetCellString(pTbl, (GTCHAR *)"", i, 2, &sretErr);
		//}
	}
	
}


void GCALARMHIST::displaydata()
{

	//GBaseObject *pTbl;
	//GTCHAR KeyText[KEY_DATA_SIZE];
	//char KeyData[KEY_DATA_SIZE];
	//
	//	unsigned short i, ErrCode;
	//

	//pTbl = GCSGetChild(GetGBaseObject(),HIST_TABLE);
	//
	//if((ulLineCcount - ulIndex) >= TABLEROW_SIZE)
	//								{
	//									lEndCnt =  TABLEROW_SIZE;
	//								}
	//								else
	//								{
	//									lEndCnt = (ulLineCcount - ulIndex);
	//								}
	//	
	//for(i = 0; i < lEndCnt; i++)
	//{
	//
	//	sprintf(KeyData, "%s",SAlarmDataHist[i+ulIndex].Adress  );
	//	GRCMultiByteToUnicode(0, KeyText, KeyData,  sizeof(KeyText)/sizeof(GTCHAR));
	//	GCSNCTableSetCellString(pTbl, KeyText, i, 0, &ErrCode);
	//

	//	sprintf(KeyData, "%s",SAlarmDataHist[i+ulIndex].Comment );
	//	GRCMultiByteToUnicode(0, KeyText, KeyData, sizeof(KeyText)/sizeof(GTCHAR));
	//	GCSNCTableSetCellString(pTbl, KeyText, i, 1, &ErrCode);

	//}
}

char* GCALARMHIST::Fetchcomment(char *cAdrss)
{

	DWORD dwStatus;
	FS_STAT stat;
	long lFileDesc;	
	long lReadNo ;
	long lDestFile;
	long lWriteNo;
	BUFFTYPE buf;
	char sFileData[2000];
	long lCurSize,lReadOff;;
	char *s,*s1;
	long countsize=0;
	char *Comment ,*end;
	
	long	sOffset=0; 

		char sDestFile[] = "M01:\\PRG\\MMACRO\\ALARM.CSV";
			//memset(sAdress ,0, sizeof(sAdress));


		if(melFSStatFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, &stat)== 0)
		{

		lCurSize = 2000;//(long)stat.lFileSize ;
		/*sFileData = (char *)malloc(lCurSize * sizeof(char) );
		memset(sFileData ,0, sizeof(sFileData));*/

	
		buf.lBuffSize = 2000;//(long)stat.lFileSize;
		buf.lpBuff = sFileData;

		if(melFSOpenFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), sDestFile, M_FSOPEN_RDONLY, 0, &lFileDesc) == 0){
		melFSLseekFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, sOffset, M_FSLSEEK_TOP, &lReadOff);
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		//melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
		}

		while(countsize!=(long)stat.lFileSize&&countsize<=(long)stat.lFileSize)
		{
			int i =0;
			s = strtok(sFileData, "\n");
			countsize+=strlen(s);
			while(s!=NULL&i<15)
			{
				if(i!=0)
				s = strtok(NULL, "\n");
				if(s!=NULL)
				{
				countsize+=strlen(s);

				s = strtok(NULL, ",");
					
				if(strcmp(cAdrss,s)==0)
				{

					
					s = strtok(NULL, ",");
					Comment = strtok(NULL, "\n");
					goto endloop;

				}
				
				i++;
				}
			}
		
		
		melFSLseekFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, countsize, M_FSLSEEK_TOP, &lReadOff);
		melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
		
		}
endloop:
melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	
		}
	
return Comment;




}
void GCALARMHIST::LoadHtmlFile(char *cAdrss)
{
	GBaseObject *pChildHtml;
	
	pChildHtml= GCSGetChild(GetGBaseObject(), HTMLBROWSER);

	GTCHAR FileName[50];
	char TempData[50];

	sprintf(TempData,"%s.html",cAdrss);

	GRCMultiByteToUnicode(0,FileName,TempData,sizeof(TempData));

	GCSHtmlbrowserSetHtmlFileName(pChildHtml,FileName);
}




long GCALARMHIST::GCODEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(GCODE_SCREEN);
	return TRUE;
}

long GCALARMHIST::HOMEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCALARMHIST::INTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(INIT_SCREEN);
	return TRUE;
}

long GCALARMHIST::IOLSTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(INOUTXY_SCREEN);
	return TRUE;
}

long GCALARMHIST::LATCHBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(INOUTL_SCREEN);
	return TRUE;
}

long GCALARMHIST::MCODEBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MCODE_SCREEN);
	return TRUE;
}

long GCALARMHIST::PRVNTBTNOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(PREV_SCREEN);
	return TRUE;
}

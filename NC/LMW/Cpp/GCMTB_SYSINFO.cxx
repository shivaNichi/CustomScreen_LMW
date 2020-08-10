#include "GCMTB_SYSINFO.hpp"
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

void GCIDeleteGCMTB_SYSINFO( GBaseObject *pObject )
{
	GCMTB_SYSINFO *pPanel = (GCMTB_SYSINFO*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMTB_SYSINFO( GBaseObject *pObject )
{
	GCMTB_SYSINFO *pPanel = new GCMTB_SYSINFO;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMTB_SYSINFO;
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
GCMTB_SYSINFO::GCMTB_SYSINFO()
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
GCMTB_SYSINFO::~GCMTB_SYSINFO()
{

}

#include "GCMTB_SYSINFO.prc"

short GCMTB_SYSINFO::CreateChildren( )
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

GPropertyInfo* GCMTB_SYSINFO::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMTB_SYSINFO::BTNHOMEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MTB_PASSWORD);
	return TRUE;
}

long GCMTB_SYSINFO::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	Fetchdata();
	return TRUE;
}

long GCMTB_SYSINFO::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	switch(lLParam)
	{
		
		case GK_F10:
			ScreenTransition(MTB_PASSWORD);
		break;

			default:
			break;
		}
	return TRUE;
}

long GCMTB_SYSINFO::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	return TRUE;
}

void GCMTB_SYSINFO::LoadData()
{



	GBaseObject *pTbl;
	GTCHAR KeyText[KEY_DATA_SIZE];
	char KeyData[KEY_DATA_SIZE];
	
		unsigned short i, ErrCode;
	

	pTbl = GCSGetChild(GetGBaseObject(),TBLINFO);
	

		
	for(i = 0; i < 12; i++)
	{
	
		sprintf(KeyData, "%s",lSysInfo[i].Name );
		GRCMultiByteToUnicode(0, KeyText, KeyData,  sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 0, &ErrCode);

		sprintf(KeyData, "%s",lSysInfo[i].Comment );
		GRCMultiByteToUnicode(0, KeyText, KeyData,  sizeof(KeyText)/sizeof(GTCHAR));
		GCSNCTableSetCellString(pTbl, KeyText, i, 1, &ErrCode);
	


	}

}
void GCMTB_SYSINFO::ScreenTransition(short ScreenNo)
{

	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCMTB_SYSINFO::Fetchdata(long sOffset)
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
	char sDataInfo[20][200];


		sOffset=0; 

		char sDestFile[] = "M01:\\PRG\\MMACRO\\SYSTEMINFO.CSV";
			
	

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
		melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
		}
				s=strtok(sFileData,"\n");
				for(int i=0;i<12;i++)
				{
					
					if(s!=NULL)
					{
					strcpy(sDataInfo[i],s);
					countsize++;
					}
					s=strtok(NULL,"\n");
				}

				for(int j=0;j<countsize;j++)
				{
				s1=strtok(sDataInfo[j],",");
				//s1=strtok(NULL,",");
				if(s1!=NULL)
				{
				strcpy(lSysInfo[j].Name,s1);
				s1=strtok(NULL,",");
				if(s1!=NULL)
				strcpy(lSysInfo[j].Comment,s1);
				}
				
				}
		
		//melFSLseekFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, countsize, M_FSLSEEK_TOP, &lReadOff);
		//melFSReadFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc, &buf, T_BUFF, &lReadNo);
				LoadData();
		
		}

//melFSCloseFile(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), lFileDesc);
	
		



	




}

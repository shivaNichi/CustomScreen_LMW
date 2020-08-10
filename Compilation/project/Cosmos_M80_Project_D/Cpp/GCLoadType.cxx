#include "GCLoadType.hpp"
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

void GCIDeleteGCLoadType( GBaseObject *pObject )
{
	GCLoadType *pPanel = (GCLoadType*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCLoadType( GBaseObject *pObject )
{
	GCLoadType *pPanel = new GCLoadType;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCLoadType;
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
GCLoadType::GCLoadType()
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
GCLoadType::~GCLoadType()
{

}

#include "GCLoadType.prc"

short GCLoadType::CreateChildren( )
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

GPropertyInfo* GCLoadType::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCLoadType::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}


	return TRUE;
}

long GCLoadType::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pData, *pTbl;
	GBaseObject *pMaxLoadRecord,*pMarginInput;
	unsigned short sretErr, usRow, usCol, i;
	unsigned long usSrchNum;
	unsigned short usToolData;
	unsigned short usSWData;
	unsigned short usTemp;
	unsigned short usToolIndex;
	unsigned short usToolFlg=0;
	unsigned short sReadR10620 = 0;//For Reading Spindle TOOl
	char cInputData[PARAM_DATA_SIZE];
	char *ptr;
	GTCHAR inpBuff[PARAM_DATA_SIZE];
	short lErrFlag;
	long lRunProg;
	short permitData;
	unsigned short sIconR69 = 0;

	GTCHAR inpBuffMain[10];
	char sDataMain[10];
	int ScountMain = 0;

	short sTouchFlg = 1;

	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	pMaxLoadRecord = GCSGetChild(GetGBaseObject(), MAX_LOAD_RECORD);
	pMarginInput = GCSGetChild(GetGBaseObject(), MARGIN_INPUT);
	
	clearWarningMessage();   
	switch(lLParam)
	{
		case GK_F1:
				if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC))){
					break;
				}
				if(bTeachModeFlag)
				{
					setWarningMessage(TEACH_MODE_ON_ERR);
					break;
				}
				// Tool Search
				GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
								
				ToolSearch(cInputData);
				break;
		
		case GK_F3:
				if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
				{
					break;
				}
				if(!bTeachModeFlag)
				{
					melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT(10620), 0, (void *)&sReadR10620, T_SHORT); 
					
					if(sReadR10620!=0)
					{
						sprintf(cInputData, "%d",sReadR10620);
						bool bFound = ToolSearch(cInputData);
						if(bFound)
							bTeachModeFlag = TRUE;
						else
							bTeachModeFlag = FALSE;
					}
					else
					{
						setWarningMessage(TOOL_NOT_EXISTS_ERR);
					}

				}
				else
				{
					bTeachModeFlag = FALSE;
					setWarningMessage(TEACH_MODE_OFF_ERR);
				}
				break;
		case GK_F4:
				if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
				{
					break;
				}
				if(bTeachModeFlag)
				{

					GCSInputBoxGetString(pMaxLoadRecord, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
					GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
					
					short sRecordMaxLoad = atoi(cInputData);
					
					GCSInputBoxGetString(pMarginInput, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
					GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
					
					short sMarginInput = atoi(cInputData);

					short sTeachMaxLoad = sMarginInput + sRecordMaxLoad;

					if(sTeachMaxLoad<=100)
					{
						GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);

						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
						GCSNCTableSetCellString(pTbl, inpBuff, usRow, 1, &sretErr);

						short usMaxLoadIndex = usInitIndex[1] + usRow;

						short usToolVal = atoi(cInputData);
						melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT_EXT(usMaxLoadIndex), 0, (void *)&usToolVal, T_SHORT); 

						//GCSTextboxSetString( pMaxLoadRecord, (GTCHAR *)"");	
						//GCSTextboxSetString( pMarginInput, (GTCHAR *)"");
					}
					else{
						setWarningMessage(DATA_OUT_OF_RANGE_ERR);
						//GCSTextboxSetString( pMaxLoadRecord, (GTCHAR *)"");	
						//GCSTextboxSetString( pMarginInput, (GTCHAR *)"");
					}
				}
				else
				{
					setWarningMessage(TEACH_MODE_OFF_ERR);
				}
				break;

		case GK_F5:
				if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
				{
					break;
				}
				if(bTeachModeFlag)
				{
					setWarningMessage(TEACH_MODE_ON_ERR);
					break;
				}
	
				GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), TREND_VIEW_SCREEN, 0), FALSE);
				break;
		case GK_F6:
				if(bTeachModeFlag)
				{
					GCSInputBoxGetString(pMaxLoadRecord, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
					GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
					
					short sRecordMaxLoad = atoi(cInputData);

					if(sRecordMaxLoad<100)
					{
						GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
						GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
						/* Checking for Inpu Data Present or Not */ 
						if(strlen(cInputData))
						{
							short sMarginInput = atoi(cInputData);
							if(sMarginInput<=25)
							{
								GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
								GCSInputBoxSetString(pMarginInput, inpBuff);

								GCSTextboxSetString( pData, (GTCHAR *)"");	
			

							}
							else{
								setWarningMessage(DATA_OUT_OF_RANGE_ERR);

								GCSTextboxSetString( pData, (GTCHAR *)"");	
							}
						}
					}
				}
				break;
	
		case GK_F7:
				if(bTeachModeFlag)
				{
					setWarningMessage(TEACH_MODE_ON_ERR);
					break;
				}
	
				// Edit table data
				GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				/* Checking for Inpu Data Present or Not */ 
				if(strlen(cInputData))
				{
					GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
					lErrFlag = checkInputValue(cInputData, usRow, usCol);							
					if(lErrFlag == TRUE)														// Checking Input value with in range
					{
						clearWarningMessage(); 
						lErrFlag = checkDataRange(usRow, usCol);									
						if(lErrFlag == TRUE)													// Checking Data Range Condition is TRUE
						{
							clearWarningMessage(); 
							/* Set the Data to Cursor Postion  */ 
							ModifyData(cInputData, usRow, usCol);  	 
						}
					}
				}
				else
				{
					setWarningMessage(SETTING_ERR); 
				}
			
				GCSTextboxSetString(pData, (GTCHAR *)"");
				break;

		case GK_F8:
				if(bTeachModeFlag)
				{
					setWarningMessage(TEACH_MODE_ON_ERR);
					break;
				}
	
				// Cancel Button
				GCSTextboxSetString(pData, (GTCHAR *)"");
				clearWarningMessage();  
				break;

		case GK_F9:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
	
					sHelpFlg = 1;
					sTimerFlg = 1;
					DisableButtonName(); 
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),HELP_WINDOW);
					break;
		case GK_NEXT:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
	
					/* Setting Sub Cursor Number to 0th Row and First Col */
					 GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);				
		   			 /* Checking for Next page is Passible or not */
					 if(((usInitIndex[0] - INITTOOL_IDX) + PAGE_TOOLNUM)< usTotTool)
					 {
						usTemp = (usInitIndex[0] - INITTOOL_IDX) + PAGE_TOOLNUM;
						ClearToolTable();					  	
						usPageNo +=  PAGE_PLUS_ONE;
						/* Checking for Next page Contains 12 Tool ro Less */
						if((usTemp + PAGE_TOOLNUM) <    usTotTool)
						{
							usPotsPerPage = PAGE_TOOLNUM;
						}
						else
						{
							usRemainPots = (   usTotTool - usTemp);	
							usPotsPerPage =    usRemainPots;
						}

						usInitIndex[0] += PAGE_TOOLNUM;
						usInitIndex[1] += PAGE_TOOLNUM;
						usInitIndex[2] += PAGE_TOOLNUM;
						usInitIndex[3] += PAGE_TOOLNUM;
						usInitIndex[4] += PAGE_TOOLNUM;

						FetchData();			 														// Fetch Tool data
						PrintToolData();			 													// Printing tool data in to Table
					 }
					 usRCcount = (usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;					// Updating Row Col Count
					 break;
		case GK_PRIOR:

					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
	
					ClearToolTable(); 
					/* Setting Sub Cursor Number to 0th Row and First Col */
					GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);
					if(usPageNo > 1)																	//Comparing page number
					{
						usPageNo = usPageNo - PAGE_PLUS_ONE;
							
						if((usInitIndex[0] - INITTOOL_IDX) < PAGE_TOOLNUM)
						{
							usPotsPerPage = usInitIndex[0] - INITTOOL_IDX;
						}
						else
						{
							usPotsPerPage = PAGE_TOOLNUM;
						}
						if(usPotsPerPage == PAGE_TOOLNUM)
						{
							usInitIndex[0] -= PAGE_TOOLNUM;
							usInitIndex[1] -= PAGE_TOOLNUM;
							usInitIndex[2] -= PAGE_TOOLNUM;
							usInitIndex[3] -= PAGE_TOOLNUM;
							usInitIndex[4] -= PAGE_TOOLNUM;
						}
						else 
						{
							usInitIndex[0] -= usPotsPerPage;
							usInitIndex[1] -= usPotsPerPage;
							usInitIndex[2] -= usPotsPerPage;
							usInitIndex[3] -= usPotsPerPage;
							usInitIndex[4] -= usPotsPerPage;
						}
						usPotsPerPage = PAGE_TOOLNUM;
						FetchData();																	// Fetch Tool data
						PrintToolData();																// Printing tool data in to Table			
						}
					else if(usPageNo  == 1)															//Comparing page number
					{
						usTemp = usInitIndex[0] - INITTOOL_IDX;
						if(usTotTool >= PAGE_TOOLNUM)
						{
							usPotsPerPage = PAGE_TOOLNUM;
						}
						else
						{
							usRemainPots = usTotTool % PAGE_TOOLNUM;
							usPotsPerPage =usRemainPots;
						}

						
						   usInitIndex[0] -= usTemp;
						   usInitIndex[1] -= usTemp;
						   usInitIndex[2] -= usTemp;
						   usInitIndex[3] -= usTemp;
						   usInitIndex[4] -= usTemp;

						FetchData();	 																// Fetch Tool data
						PrintToolData();																// Printing tool data in to Table
					}
					usRCcount = (   usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;					// Updating Row Col Count
					break;
		case GK_F10:
					if( (lUParam & KEY_BITALL) != 0){
						break;
					}
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					else if(sHelpFlg == 0)
					{
						clearWarningMessage();
						GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
					}
					else if(sHelpFlg == 1)
					{
						GBaseObject *pWindow, *pParent;

						pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), HELP_WINDOW + 1);

					
						if(pWindow)								// Closes Window
							GCSClose(pWindow);
						sHelpFlg = 0;
						sTimerFlg = 0;
						EnableButtonName();
					}
					break;
		case GK_DELETE:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					GCSTextboxGetString(pData, inpBuffMain, sizeof(inpBuffMain)/sizeof(GTCHAR));
					GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sDataMain,inpBuffMain, sizeof(sDataMain));

					ScountMain = strlen(sDataMain);

					if(ScountMain != 0)
					{
						sDataMain[strlen(sDataMain)-1]= '\0';
						GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuffMain, sDataMain, sizeof(sDataMain));
						GCSTextboxSetString(pData, inpBuffMain);

					}
					break;
		case GK_DOWN:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					/*Down arrow press event */
					GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
					if(usRCcount < usTotTool)														// Comparing Row Col Count with Total Tool
					{
						usRCcount++;
						usRow++;
						usPageNo = (usRCcount /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
						if(usRow > TABLE_ROW_INDEX_END )												// Comparing Row is Lees tahn 11
						{
							
							usInitIndex[0] += INDEX_PLUS_ONE;
							usInitIndex[1] += INDEX_PLUS_ONE;
							usInitIndex[2] += INDEX_PLUS_ONE;
							usInitIndex[3] += INDEX_PLUS_ONE;
							usInitIndex[4] += INDEX_PLUS_ONE;

							FetchData();																// Fetch Tool data
							PrintToolData();															// Printing tool data in to Table
						}
					}
					/* Setting Sub Cursor Number to 0th Row and First Col */
					GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);			
					break;
		case GK_UP:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					// Up arrow press event
					GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				
					if(usRCcount > 1)
					{
						usRCcount--;
						usPageNo = (usRCcount / PAGE_TOOLNUM) + PAGE_PLUS_ONE;				
						if(	usRow == 0)
						{
							usInitIndex[0] -= INDEX_PLUS_ONE;
							usInitIndex[1] -= INDEX_PLUS_ONE;
							usInitIndex[2] -= INDEX_PLUS_ONE;
							usInitIndex[3] -= INDEX_PLUS_ONE;
							usInitIndex[4] -= INDEX_PLUS_ONE;

							if((usTotTool - usRCcount) < PAGE_TOOLNUM)
							{
								usPotsPerPage = (usTotTool - usRCcount) + 1;
							}

							FetchData();		 														// Fetch Tool data
							PrintToolData();															// Printing tool data in to Table
						}
						usRow--;
					}
					/* Setting Sub Cursor Number to 0th Row and First Col */
					GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);
					break;			
		case GK_TAB:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					// Tab press event
					GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
					if((lUParam & KEY_SHIFT) == KEY_SHIFT){					
						if( usCol > TOOL_COL_NUM )
						{
							usCol--;
							if(usCol != 1)
							{
								//ToolDataHelp(usCol); 
							}
						}
					}
					else{
						if( usCol < COL_SIZE - 1 )															// Comparing Col is less than 10
						{
							usCol++;
							if(usCol != 1)
							{
								//ToolDataHelp(usCol); 
							}
						}
					}
					/* Setting Sub Cursor Number to 0th Row and First Col */
					GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);			
					break;
		case GK_ESCAPE:
					if(bTeachModeFlag)
					{
						setWarningMessage(TEACH_MODE_ON_ERR);
						break;
					}
					GCSTextboxSetString(pData, (GTCHAR *)"");
					clearWarningMessage();
					break;
		default:
			break;
	}
	return TRUE;
}

long GCLoadType::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg == 0)
	{
		clearWarningMessage();
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
	}
	else if(sHelpFlg == 1)
	{
		GBaseObject *pWindow, *pParent;

		pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), HELP_WINDOW + 1);

	
		if(pWindow)								// Closes Window
			GCSClose(pWindow);
		sHelpFlg = 0;
		sTimerFlg = 0;
		EnableButtonName();
	}
	return TRUE;
}

long GCLoadType::KEY_CANCEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg==0)
	{
		GBaseObject *pData;
		
		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		
		// Cancel Button
		GCSTextboxSetString(pData, (GTCHAR *)"");
		clearWarningMessage();  
	}
	return TRUE;
}

long GCLoadType::KEY_HELP_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{	
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg==0)
	{
		sHelpFlg = 1;
		sTimerFlg = 1;
		DisableButtonName(); 
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),HELP_WINDOW);
	}
	return TRUE;
}

long GCLoadType::KEY_SET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg==0)
	{
		GBaseObject *pData, *pTbl;
		unsigned short sretErr, usRow, usCol, i;
		unsigned long usSrchNum;
		unsigned short usToolData;
		unsigned short usSWData;
		unsigned short usTemp;
		unsigned short usToolIndex;
		unsigned short usToolFlg=0;
		char cInputData[PARAM_DATA_SIZE];
		char *ptr;
		GTCHAR inpBuff[PARAM_DATA_SIZE];
		short lErrFlag;
		long lRunProg;
		short permitData;

		GTCHAR inpBuffMain[10];
		char sDataMain[10];
		int ScountMain = 0;

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		clearWarningMessage();   

		// Edit table data
		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		/* Checking for Inpu Data Present or Not */ 
		if(strlen(cInputData))
		{
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			lErrFlag = checkInputValue(cInputData, usRow, usCol);							
			if(lErrFlag == TRUE)														// Checking Input value with in range
			{
				clearWarningMessage(); 
				lErrFlag = checkDataRange(usRow, usCol);									
				if(lErrFlag == TRUE)													// Checking Data Range Condition is TRUE
				{
					clearWarningMessage(); 
					/* Set the Data to Cursor Postion  */ 
					ModifyData(cInputData, usRow, usCol);  	 
				}
			}
		}
		else
		{
			setWarningMessage(SETTING_ERR); 
		}

		GCSTextboxSetString(pData, (GTCHAR *)"");
	}
	return TRUE;
}

long GCLoadType::KEY_TEACHLOAD_SETOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pTbl;
	GBaseObject *pMaxLoadRecord,*pMarginInput;
	unsigned short sretErr, usRow, usCol, i;
		
	char cInputData[PARAM_DATA_SIZE];
	GTCHAR inpBuff[PARAM_DATA_SIZE];
		
	
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	pMaxLoadRecord = GCSGetChild(GetGBaseObject(), MAX_LOAD_RECORD);
	pMarginInput = GCSGetChild(GetGBaseObject(), MARGIN_INPUT);

	if(bTeachModeFlag && sHelpFlg==0)
	{

		GCSInputBoxGetString(pMaxLoadRecord, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		
		short sRecordMaxLoad = atoi(cInputData);
		
		GCSInputBoxGetString(pMarginInput, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		
		short sMarginInput = atoi(cInputData);

		short sTeachMaxLoad = sMarginInput + sRecordMaxLoad;

		if(sTeachMaxLoad<=100)
		{
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);

			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
			GCSNCTableSetCellString(pTbl, inpBuff, usRow, 1, &sretErr);

			short usMaxLoadIndex = usInitIndex[1] + usRow;

			short usToolVal = atoi(cInputData);
			melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
															M_SSEC_PLWRD_R_1SHOT_EXT(usMaxLoadIndex), 0, (void *)&usToolVal, T_SHORT); 

			//GCSTextboxSetString( pMaxLoadRecord, (GTCHAR *)"");	
			//GCSTextboxSetString( pMarginInput, (GTCHAR *)"");
		}
		else{
			setWarningMessage(DATA_OUT_OF_RANGE_ERR);
			//GCSTextboxSetString( pMaxLoadRecord, (GTCHAR *)"");	
			//GCSTextboxSetString( pMarginInput, (GTCHAR *)"");
		}
	}
	return TRUE;
}

long GCLoadType::KEY_TEACH_MODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	unsigned short sReadR10620 = 0;
	char cInputData[PARAM_DATA_SIZE];

	if(!bTeachModeFlag && sHelpFlg==0)
	{
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
														M_SSEC_PLWRD_R_1SHOT(10620), 0, (void *)&sReadR10620, T_SHORT); 
		
		if(sReadR10620!=0)
		{
			sprintf(cInputData, "%d",sReadR10620);
			bool bFound = ToolSearch(cInputData);
			if(bFound)
				bTeachModeFlag = TRUE;
			else
				bTeachModeFlag = FALSE;
		}
		else
		{
			setWarningMessage(TOOL_NOT_EXISTS_ERR);
		}
	}
	else
	{
		bTeachModeFlag = FALSE;
	}
				
	return TRUE;
}

long GCLoadType::KEY_TOOL_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg==0)
	{
		GBaseObject *pData;
		
		char cInputData[PARAM_DATA_SIZE];
		GTCHAR inpBuff[PARAM_DATA_SIZE];

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);

		

		// Tool Search
		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
						
		ToolSearch(cInputData);
	}
	
	return TRUE;
}

long GCLoadType::KEY_TREND_VIEWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(bTeachModeFlag)
	{
		setWarningMessage(TEACH_MODE_ON_ERR);
		return TRUE;
	}
	else if(sHelpFlg==0)
	{
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), TREND_VIEW_SCREEN, 0), FALSE);
	}
	return TRUE;
}



long GCLoadType::TOOL_MANAGE_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pTbl;
	unsigned short sretClr;
	unsigned short i;

	usRCcount = 1;																				// Reinitialize row col count

	unsigned int Color[COL_SIZE] = {0x008000, 0x99CCFF, 0xFF99CC, 0x800080, 0x33CCCC/*, 
											0xFF9900, 0xFFFF99, 0xFF5050, 0x00FFFF, 0xCCCC00*/};  // Color
	
	bTeachModeFlag = FALSE;
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	for(i = 0; i < COL_SIZE; i++)
	{
		GCSNCTableSetRowTitleBackColor(pTbl, Color[i],i,&sretClr);								// Changing Table Title Color
	}

	ReadIconStatus();
	ReadProgressBarStatus();

	sHelpFlg = 0;
	bTeachModeFlag = FALSE;
	//Initlization of tool type 
	
	sToolTypeArray[0] = "Drill";
	sToolTypeArray[1] = "Tap";
	sToolTypeArray[2] = "Bore";
	sToolTypeArray[3] = "EM";
	sToolTypeArray[4] = "Bn";
	sToolTypeArray[5] = "Bull N";
	sToolTypeArray[6] = "Face M";
	sToolTypeArray[7] = "Ream";
	sToolTypeArray[8] = "Charmfer";
	sToolTypeArray[9] = "Engrave";
	sToolTypeArray[10] = "Woodruff";
	sToolTypeArray[11] = "Slit";
	sToolTypeArray[12] = "S & F";
	sToolTypeArray[13] = "Thread M";

	/*	Setting Sub Cursor Number to 0th Row and First Col */
	GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretClr);
			
	InitToolTable(); 																			// Initialize Tool and Pot Info
	FetchData();																				// Fetch Tool Data
	PrintToolData();

	
	return TRUE;
}

long GCLoadType::TOOL_MANAGE_TABLEOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{

	static int iRefreshIconTimer = 0;
	GBaseObject *pChild;
	GBaseObject *pMaxLoadRecord;
	GTCHAR szText[PARAM_DATA_SIZE];
	char *cInputData;

	short sReadM3500 = 0;
	short sReadM3501 = 0;
	short sReadR28541 = 0;
	bool bReadMaxLoad = FALSE;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	
	if(pChild != NULL && sHelpFlg!=1)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}

	iRefreshIconTimer++;
	if(iRefreshIconTimer >=100) {
		ReadIconStatus();
		ReadProgressBarStatus();
		iRefreshIconTimer = 0;
	}

	if(bTeachModeFlag)
		TeachModeProcess();
	
	return TRUE;
}

/****************************************************************************************************/
/* Function - ReadIconStatus																		*/
/*																									*/
/* Purpose - Reads and Updates the Icon Status	for													*/
/*			 Mode,Key,Lube,Manuual/Auto,Caution,SP Icon, & Tool Change Icon							*/
/****************************************************************************************************/
void GCLoadType::ReadIconStatus()
{
	//ICON 1
	GBaseObject *pIconPicture;
	short sIconJogMode = 0;
	short sIconHandleMode = 0;
	short sIconIncMode = 0;
	short sIconZrnMode = 0;
	short sIconMemMode = 0;
	short sIconMdiMode = 0;
	short sIconRpdMode = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3072),0, &sIconJogMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3073),0, &sIconHandleMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3074),0, &sIconIncMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3076),0, &sIconZrnMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3080),0, &sIconMemMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3083),0, &sIconMdiMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(30110),0, &sIconRpdMode, T_SHORT); // To get the Data Protection Status
	
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON1);

	if(sIconJogMode !=0)
	{	
		if(sIconRpdMode!=0)
		{
			GCSPictureSetStatus( pIconPicture,2);
		}
		else
		{
			GCSPictureSetStatus( pIconPicture,3);
		}
	}	
	else if(sIconHandleMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,6);	
	}	
	else if(sIconIncMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,4);	
	}
	else if(sIconZrnMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,5);	
	}	
	else if(sIconMemMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,1);	
	}
	else if(sIconMdiMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,0);	
	}	
	else if(sIconRpdMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,2);	
	}
	/*else
	{	
			GCSPictureSetStatus( pIconPicture,i);
	}	*/


	//ICON 2
	short sIconKey = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(1800),0, &sIconKey, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON2);
	if(sIconKey !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
		GCSPictureSetStatus( pIconPicture,0);	
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	
	//ICON 3
	short sIconLube = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(592),0, &sIconLube, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON3);
	if(sIconLube !=0)
	{	
		GCSPictureSetStatus( pIconPicture,0);	
	}
	else
	{
		GCSPictureSetStatus(pIconPicture,1);
	}

	//ICON 4
	short sIconManual = 0;
	short sIconAuto = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9103),0, &sIconManual, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9104),0, &sIconAuto, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON4);
	GCSSetVisibleStatus(pIconPicture,1);
	if(sIconManual !=0)
	{	
		GCSPictureSetStatus(pIconPicture,0);	
	}
	else if(sIconAuto!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	//ICON 5
	unsigned short sIconR69 = 0;
	short sIconXC98 = 0;
	short sIconXC99 = 0;
	short sIconXC9A = 0;
	short sIconXC9B = 0;
	short sIconXC9C = 0;
	short sIconX1886 = 0;
	short sIconM9101 = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(69),1, &sIconR69, T_SHORT); // To get the Data Protection StatusmelGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3224),0, &sIconXC98, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3225),0, &sIconXC99, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3226),0, &sIconXC9A, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3227),0, &sIconXC9B, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3228),0, &sIconXC9C, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(6278),0, &sIconX1886, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9101),0, &sIconM9101, T_SHORT); // To get the Data Protection Status


	pIconPicture = GCSGetChild(GetGBaseObject(), ICON5);
	
	if(sIconR69 !=65535)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC98!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC99!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9A!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9B!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9C!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconX1886!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconM9101!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	//ICON 6
	short sIconY1898 = 0;
	short sIconY1899 = 0;
	short sIconY189E = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(37123),0, &sIconY1898, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3224),0, &sIconY1899, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3225),0, &sIconY189E, T_SHORT); // To get the Data Protection Status
	

	pIconPicture = GCSGetChild(GetGBaseObject(), ICON6);
	
	if(sIconY1898 !=0)
	{	
		GCSPictureSetStatus(pIconPicture,0);
	}
	else if(sIconY1899!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconY189E!=0)
	{
		GCSPictureSetStatus(pIconPicture,3);
	}
	else
	{
		GCSPictureSetStatus(pIconPicture,2);
	}

	//ICON 7
	short sIconM9102 = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9102),0, &sIconM9102, T_SHORT); // To get the Data Protection Status
	
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON7);
	
	if(sIconM9102 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
}


/****************************************************************************************************/
/* Function - ReadProgressBarStatus																	*/
/*																									*/
/* Purpose - Reads and Updates the Progress bar for													*/
/*			 X,Y,Z, & SP																			*/
/****************************************************************************************************/
void GCLoadType::ReadProgressBarStatus()
{
	GBaseObject *pProgressBar;

	double sXValue = 0;
	double sYValue = 0;
	double sZValue = 0;
	double sSPValue = 0;

	double sProgData;

	
	//for Updating the Progress of X value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,1, &sXValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sXValue);
	sXValue = sProgData;
	if(sXValue>=0 && sXValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=61 && sXValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=81 && sXValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2X);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}

	//for Updating the Progress of Y value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,2, &sYValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sYValue);
	sYValue = sProgData;
	if(sYValue>=0 && sYValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=61 && sYValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=81 && sYValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Y);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}

	//for Updating the Progress of Z value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,3, &sZValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sZValue);
	sZValue = sProgData;
	if(sZValue>=0 && sZValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=61 && sZValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=81 && sZValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Z);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	//for Updating the Progress of SP value
	//63/4/1
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SP, M_SSEC_MSP_LOAD,1, &sSPValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sSPValue);
	sSPValue = sProgData;
	if(sSPValue>=0 && sSPValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=61 && sSPValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=81 && sSPValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2SP);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
}


/*******************************************************************************************/
/* Function - FetchData																	   */
/*																						   */
/* Purpose - Read Tool Data From PLC Device						 						   */
/*******************************************************************************************/
void GCLoadType::FetchData() 
{
	unsigned short i, j, k;


	for(i=0; i<12; i++){
		usTotToolData[i] =0;
		usTotMaxLoadData[i] =0;
		usTotMinLoadData[i] =0;
		usTotONOFFData[i] =0;
		usTotToolTypeData[i] =0;
	}

	for(i = 0, j = 0; i < PAGE_TOOLNUM; i++,j++)
	{
		
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
						M_SSEC_PLWRD_R_1SHOT(usInitIndex[0] + i), 0, &usTotToolData[i], T_SHORT);
		
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
						M_SSEC_PLWRD_R_1SHOT_EXT(usInitIndex[1] + i), 0, &usTotMaxLoadData[i], T_SHORT);

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
						M_SSEC_PLWRD_R_1SHOT_EXT(usInitIndex[2] + i), 0, &usTotMinLoadData[j], T_SHORT);

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
						M_SSEC_PLWRD_R_1SHOT(usInitIndex[3] +  i), 0, &usTotONOFFData[i], T_SHORT);

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_LONG, 
						M_SSEC_PLWRD_R_1SHOT_EXT(usInitIndex[4] + i), 0, &usTotToolTypeData[i], T_SHORT);
				
	}
	//SplitToolData();																			// Spliting Tool Data
}


/*******************************************************************************************/
/* Function - SplitToolData															       */
/*																						   */
/* Purpose - Spliting R10940 Series Device Data					 					       */
/*******************************************************************************************/
void GCLoadType::SplitToolData()
{
	const unsigned short usNbits = SPLIT_DATA_SIZE;
	unsigned short bits = sizeof(short) * 8;
	short i, j;
	/* Spliting Data in to 16 Bits */
	for(i=0; i < usPotsPerPage; i++)
	{
		for(j = usNbits - 1; j >= 0; j--)
		{
			bit_g[i][j].bit = (1 && usTotONOFFData[ i] & ( 1 << (bits - 1)));		// Converting Byte into Bits
			bits--;
		}
		bits = sizeof(short) * 8;																// ReInitializing bits
	}
}

void GCLoadType::InitToolTable()
{
	double fPage;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																				M_SSEC_PLWRD_R_1SHOT(10610), 0, &   usTotTool, T_SHORT);
	usInitIndex[0] = INITTOOL_IDX;
	usInitIndex[1] = INITLD_IDX;
	usInitIndex[2] = INITMINLD_IDX;
	usInitIndex[3] = INITDATA_IDX;
	usInitIndex[4] = INITTYPE_IDX;

	fPage = (double)(usTotTool/12);
	if(fPage > (unsigned short)(fPage) )
		usTotPages = (unsigned short)(fPage + 1);
	else
		usTotPages = (unsigned short)fPage;

	usRemainPots = usTotTool % PAGE_TOOLNUM;
	usPageNo = 1;
	if(usTotPages >= 1)
		usPotsPerPage = PAGE_TOOLNUM;
	else
		usPotsPerPage = usRemainPots;

}

/*******************************************************************************************/
/* Function - PrintToolData															       */
/*																					       */
/* Purpose - Printing Tool Data	, Pot number			 							       */
/*******************************************************************************************/
void GCLoadType :: PrintToolData()
{
	GBaseObject *pTbl;
	unsigned short i, usRow, usCol;
	unsigned short usRetCode;

	
	GTCHAR cellText[PARAM_DATA_SIZE];
	char cellData[PARAM_DATA_SIZE];
	
	pTbl = GCSGetChild(GetGBaseObject() ,TOOL_MANAGE_TABLE);
	/* Printing Tool data Into table */

	
	for(i = 0; i < usPotsPerPage; i++)
	{
		usRow = i;
		usCol = 0;
		if(usTotToolData[i] == CLEAR )
		{
			sprintf(cellData, "%s", "NT");														// No Tool
		}
		else if(usTotToolData[i] == LOCK)
		{
			sprintf(cellData, "%s", "LK");
		}
		else
		{
			sprintf(cellData, "%x", usTotToolData[i]);
		}
		//sprintf(cellData, "%d", usTotToolData[i]);
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);						// Printing Pot Number
		
		usCol = 1;
		sprintf(cellData, "%d", usTotMaxLoadData[i]);
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);

		usCol = 2;
		sprintf(cellData, "%d", usTotMinLoadData[i]);
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);
		

		usCol = 3;
		tData.num = usTotONOFFData[i];

		if(tData.bits.b7 == 1)
			sprintf(cellData, "%s", "ON");
		else
			sprintf(cellData, "%s", "OFF");

		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);


		usCol = 4;
		if(usTotToolTypeData[i]-1 >=0 && usTotToolTypeData[i]-1<=13)
			sprintf(cellData, "%s", sToolTypeArray[usTotToolTypeData[i]-1]);
		else 
			sprintf(cellData, " ");

		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);
	}
	//PrintSplitToolData(bit_g);																	// Print Splited Tool Data 
}

/*******************************************************************************************/
/* Function - PrintSplitToolData													       */
/*																					       */
/* Purpose - To Print Splited Tool Data 				 							       */
/*******************************************************************************************/
void GCLoadType::PrintSplitToolData(Bit dbit_g[][SPLIT_DATA_SIZE])
{
	GBaseObject *pTbl;
	unsigned int i, j, k; 
	unsigned short bit;  
	unsigned short pusErrCode;
	unsigned short usCol, usRow;
	
	GTCHAR bitText[PARAM_DATA_SIZE];
	char bitData[PARAM_DATA_SIZE];

	pTbl = GCSGetChild(GetGBaseObject(),TOOL_MANAGE_TABLE);										//Get TOOLMANAGEMENTTABLE
	
	for(j = 0; j < usPotsPerPage; j++)				
	{
		usRow = j;
		bit = (dbit_g[j][7].bit << 1);								
	

		if(bit == 0)
		{
			GCSNCTableSetCellBackColor(pTbl, 0xFF99CC, usRow, usCol, &pusErrCode );
			sprintf(bitData, "%s", "OFF");
		}
		else if(bit == 1)
		{
			sprintf(bitData, "%s", "ON");
		}
			
		GRCMultiByteToUnicode(0, bitText, bitData, sizeof(bitText));
		GCSNCTableSetCellString(pTbl, bitText, usRow, 3, &pusErrCode);
	}
}


/************************************************************************************/
/* Function - User																	*/
/*																					*/
/* Purpose - Invoked by GCSUser to communicate data/info between panel and window	*/
/************************************************************************************/
long GCLoadType::User(long lLParam, long lUParam)
{
	unsigned short sretErr, usRow, usCol;
	unsigned short usToolIndex, usLkValue = LOCK;

	short sTouchFlg = 0;

	GBaseObject *pData, *pTbl;
	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
	switch(lLParam)
	{
		case 0:	sTimerFlg = 0;
				GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				usToolIndex =  INITTOOL_IDX + (   usInitIndex[0] % INITTOOL_IDX) + usRow;
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																			M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&usLkValue, T_SHORT);
				FetchData();																	// Fetch Tool data
				PrintToolData();																// Printing tool data in to Table
				break;	
		case 1: sTimerFlg = 0;
				GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				usToolIndex = (   usInitIndex[0] % INITTOOL_IDX) + usRow;
				break;
		case 2:	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
					sTimerFlg = 0;
				}
				break;
		case 3:	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
					EnableButtonName();
					sHelpFlg = 0;
					sTimerFlg = 0;
				}
				break;
		default:
				break;
	}
	return TRUE;
}


/************************************************************************************/
/* Function - EnableButtonName														*/
/*																					*/
/* Purpose - Shows Button Name for each button in the screen						*/
/************************************************************************************/
void GCLoadType::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_TOOL_SEARCH);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_TEACH_MODE);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_TEACHLOAD_SET);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_TREND_VIEW);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MARGIN_INPUT);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_SET_BUTTON);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_CANCEL_BUTTON);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_HELP_WINDOW);
	pKeyButton[8] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//ID_STRING00370 = KEY_TOOL_SEARCH
	//ID_STRING01164 = KEY_TEACH_MODE
	//ID_STRING01144 = KEY_TEACHLOAD_SET
	//ID_STRING01161 = KEY_TREND_VIEW
	//ID_STRING01316 = KEY_MARGIN_INPUT
	//ID_STRING00367 = KEY_SET_BUTTON
	//ID_STRING00368 = KEY_CANCEL_BUTTON
	//ID_STRING00101  = KEY_HELP_WINDOW
	//ID_STRING00023 = KEY_BACK

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00370);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING01164);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING01144);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING01161);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING01316);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00367);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00368);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00101);
	GCSButtonSetStringID(pKeyButton[8], ID_STRING00023);
}


/****************************************************************************************************/
/* Function - DisableButtonName																		*/
/*																									*/
/* Purpose - Hides Button Name for each button in the screen Show Button Name Only For Close Button	*/
/****************************************************************************************************/
void GCLoadType::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_TOOL_SEARCH);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_TEACH_MODE);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_TEACHLOAD_SET);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_TREND_VIEW);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MARGIN_INPUT);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_SET_BUTTON);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_CANCEL_BUTTON);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_HELP_WINDOW);
	pKeyButton[8] = GCSGetChild(GetGBaseObject(), KEY_BACK);
	

	//ID_STRING00214 = Close
	//ID_STRING01300 = Empty Spaces
	GCSButtonSetStringID(pKeyButton[0], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[8], ID_STRING00214);
}







void GCLoadType::ModifyData(char *cInputData, unsigned short usRow, unsigned short usCol)
{
	GBaseObject *pTbl;
	
	unsigned short usToolIndex,usMaxLoadIndex,usMinLoadIndex,usOnOfIndex,usToolTypeIndex;
	unsigned short usCurdata;
	unsigned short usToolVal;
	GTCHAR szText[PARAM_DATA_SIZE];
	unsigned short sretErr;
	char *ptr;
		
	
	
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);

	usToolIndex = usInitIndex[0] + usRow;
	usMaxLoadIndex = usInitIndex[1] + usRow;
	usMinLoadIndex = usInitIndex[2] + usRow;
	usOnOfIndex = usInitIndex[3] + usRow;
	usToolTypeIndex = usInitIndex[4] + usRow;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT(usOnOfIndex), 0, &usCurdata, T_SHORT);
	tData.num = usCurdata;

	switch(usCol)
	{
		case 3: tData.bits.b7 = atoi(cInputData);
				if(tData.bits.b7 == 1)
					sprintf(cInputData, "%s", "ON");
				else
					sprintf(cInputData, "%s", "OFF");

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);

				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT_EXT(usOnOfIndex), 0, (void *)&tData.num, T_SHORT); 

				break;
		case 1: GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				usToolVal = atoi(cInputData);
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT_EXT(usMaxLoadIndex), 0, (void *)&usToolVal, T_SHORT); 
				break;
		case 2: GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				usToolVal = atoi(cInputData);
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT_EXT(usMinLoadIndex), 0, (void *)&usToolVal, T_SHORT); 
				break;
		case 4:	
				usToolVal = atoi(cInputData);

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, sToolTypeArray[usToolVal], OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);

				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT_EXT(usToolTypeIndex), 0, (void *)&usToolVal, T_SHORT); 
				break;
		
		default:
			break;
	}
}


/*******************************************************************************************/
/* Function - checkDataRange											        		   */
/*																						   */
/* Purpose - To Check Data Range Conditions				                        		   */
/*******************************************************************************************/
short GCLoadType::checkDataRange(unsigned short usRow, unsigned short usCol)
{
	//short pot, tool;
	//unsigned short NextTool, PrevTool;
	//GBaseObject *pTbl;
	//GTCHAR szText[PARAM_DATA_SIZE];
	//char str[3];
	//unsigned short sretErr;
	//long lRunProg;
	//short permitData;

	//pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	//
	//GCSNCTableGetCellString(pTbl, szText, 3, usRow, 0, &sretErr);
	//GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), str, szText, sizeof(str));
	//pot = atoi(str);

	//GCSNCTableGetCellString(pTbl, szText, 3, usRow, 1, &sretErr);
	//GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), str, szText, sizeof(str));
	//tool = atoi(str);
	//
	//if(pot == 1)																				// Checking for pot is 1
	//{	////Fetch first pot Data
	//	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
	//											M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX + pInfo->usTotTool - 1), 0, &PrevTool, T_SHORT); 
	//}
	//else
	//{
	//	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
	//												M_SSEC_PLWRD_R_1SHOT(pInfo->usInitIndex[0] + usRow -1), 0, &PrevTool, T_SHORT);
	//}
	//
	//if(pot == pInfo->usTotTool)																		// Checking for pot is last pot
	//{	//Fetch last pot Data
	//	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
	//													M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX ), 0, &NextTool, T_SHORT); 
	//}
	//else
	//{
	//	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
	//												M_SSEC_PLWRD_R_1SHOT(pInfo->usInitIndex[0] + usRow + 1 ), 0, &NextTool, T_SHORT);
	//}
	//
	//// Fetch Program Execution State
	//melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
	//																				M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
	//// Fetch Y708 Data
	//melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
	//																				 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
	//// Checking for JOG mode
	//if(lRunProg == 1 && permitData ==1)															
	//{
	//	switch(usCol)
	//	{		
	//		//Checking for Pot and Tool num to less than or equ Zero
	//		case 2:if( (pot <= 0) && (tool < 0) )												
	//			   {
	//				   setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
	//				   return FALSE;
	//				}
	//				else if(PrevTool != CLEAR )														//Checking for Previous Tool NonZero
	//				{
	//					setWarningMessage(MAKE_LOWER_TOOL_ZERO_ERR);
	//					return FALSE;
	//				}
	//				else if(NextTool != CLEAR)														//Checking for Next Tool NonZero
	//				{
	//					setWarningMessage(MAKE_UPPER_TOOL_ZERO_ERR);
	//					return FALSE;
	//				}
	//			break;
	//		case 3: if(pot != tool)																	// Checking for Pot and Tool num not equ 
	//				{
	//					setWarningMessage(POT_AND_TOOL_NOT_EQU_ERR);
	//					return FALSE;
	//				}
	//				else if(tool >= CLEAR)															//Checking for Tool num to less than or  equ Zero																													
	//				{
	//					setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
	//					return FALSE;
	//				}
	//			break;
	//		case 4:
	//		case 5:
	//		case 6:
	//		case 7:
	//		case 8:
	//		case 9://Checking for Pot and Tool num to less than  Zero
	//				if( (pot < 0) && (tool < 0) )												
	//			   {
	//					setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
	//					return FALSE;
	//			   }
	//			break;
	//		default:
	//			break;
	//	}
	//}
	//else
	//{
	//		setWarningMessage(JOG_MODE_ERR);
	//		return FALSE;
	//}

	return TRUE;
}



/*******************************************************************************************/
/* Function - checkInputValue											        		   */
/*																						   */
/* Purpose - To Check Input value 			                        					   */
/*******************************************************************************************/
short GCLoadType::checkInputValue(char *sdata, unsigned short usRow, unsigned short usCol)
{
	short sVal, i;
	unsigned short usToolVal;
	unsigned short usCurToolVal, usToolIndex,usMaxLdDataIndex,usCurMaxLdVal,usMinLdDataIndex,usCurMinLdVal;
	unsigned long usSwData;
	short lAlpha = 0;

	short len = strlen(sdata);
	char *ptr;

	sVal = atoi(sdata);
	
	usToolIndex =     usInitIndex[0] + usRow;
	usMaxLdDataIndex = usInitIndex[1]+usRow;
	usMinLdDataIndex = usInitIndex[2]+usRow;
	//Read data from PLC device
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, &usCurToolVal, T_SHORT);

	

	/* Checking for Data is NT or LK */
	if((usCurToolVal != CLEAR && usCurToolVal != LOCK && usCurToolVal != 0)/* || usCol == 1*/)									
	{
		for(i = 0; i < len; i++)
				if(! ( (sdata[i] >= '0') && (sdata[i] <= '9') ))								// Checking for Alpha
					lAlpha =1;
		if(!lAlpha)																				// Checking for Numaric
		{
			switch(usCol)
			{
				case 1:
						if(! ( (sVal  >= 0) && (sVal <= 120) ) )								// Checking 0 - 120 for LD
						{
							setWarningMessage(DATA_OUT_OF_RANGE_ERR);
							return FALSE;
						}
						break;
				case 2:	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT_EXT(usMaxLdDataIndex), 0, &usCurMaxLdVal, T_SHORT);

						if(! ( (sVal  >= 0) && (sVal <= usCurMaxLdVal) ) )									// Checking 0 - 3 range for CLNT
						{
							setWarningMessage(DATA_OUT_OF_RANGE_ERR);
							return FALSE;
						}
						break;
				case 3: 
						melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT_EXT(usMaxLdDataIndex), 0, &usCurMaxLdVal, T_SHORT);

						melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT_EXT(usMinLdDataIndex), 0, &usCurMinLdVal, T_SHORT);

						if( (sVal != 0) && (sVal != 1) && usCurMinLdVal<usCurMaxLdVal)										// Checking 0 or 1 for LT, FT, etc
						{
							setWarningMessage(ENTER_ZERO_OR_ONE_ERR);
							return FALSE;
						}
						break;
				case 4:
						if(! ( (sVal  >= 0) && (sVal <= 14) ) )									// Checking 0 - 2 range for ATC-SP									
						{
							setWarningMessage(SETTING_ERR);
							return FALSE;
						}
						break;
				
				default:
						break;
			}
		}
		else
		{
			setWarningMessage(PROPER_VALUE_ERR);
			return FALSE;
		}
	}
	else
	{
		if(usCurToolVal == LOCK)
		{
			setWarningMessage(TOOL_LCK_ERR);
		}
		else if(usCurToolVal == CLEAR)
		{
			setWarningMessage(TOOL_CLR_ERR);
		}
		else
		{
			setWarningMessage(TOOL_IS_ZERO_ERR);
		}
		return FALSE;
	}

	return TRUE;
}


/*******************************************************************************************/
/* Function - setWarningMessage														       */
/*																						   */
/* Purpose - To display warning message on screen				 						   */
/*******************************************************************************************/
void GCLoadType::setWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == MAKE_LOWER_TOOL_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Not Possible:Clear Lower Tool ",
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == MAKE_UPPER_TOOL_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting not possible:Clear Upper Tool ",	
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == POT_TOOL_NUM_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Not possible, Invalid Pot or Tool ", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == JOG_MODE_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't be set, Please select Jog Mode", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == LD_RANGE_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Error : Setting Range is 0-120%", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == DATA_OUT_OF_RANGE_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data Out of Range!!!", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == ENTER_ZERO_OR_ONE_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter 0 or 1 !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TOOL_NUM_EXISTS_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Tool Number already exists !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == POT_NOT_EXISTS_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Pot Does Not Exists  !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TOOL_NOT_EXISTS_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Tool Does Not Exists  !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == SETTING_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Error  !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TOOL_CLR_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't  set! No Tool is Assigned", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TOOL_IS_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't  set! Tool Num is 0", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TOOL_LCK_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't  set! Tool is Locked", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == PROPER_VALUE_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Enter Proper Value !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == POT_AND_TOOL_NOT_EQU_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Not Possible:Pot Num != Tool Num", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == MAKE_LOWER_TOOL_BT_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting Not Possible:Make Lower Tool LT to 0", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == MAKE_UPPER_TOOL_BT_ZERO_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Setting not possible:Make Upper Tool LT to 0", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == SPINDLE_TOOL_NUM_MATCH_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Number already exists in Spindle Tool !", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == JOG_MODE_CLEAR_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't be clear, Please select Jog Mode !", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == JOG_MODE_LOCK_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't Lock, Please select Jog Mode !", 
																								sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == MAG_CLEAR_COMPLETE)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Magazine Clear Complete", sizeof(szText)/sizeof(GTCHAR));

	else if(warnnum == CAUTION_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't be clear, Caution Error !", sizeof(szText)/sizeof(GTCHAR));

	else if(warnnum == EDIT_PERMIT_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Can't be clear, Data is protected !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TEACH_MODE_ON_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please Turn OFF Teach Mode !", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == TEACH_MODE_OFF_ERR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Teach Mode Turned OFF !", sizeof(szText)/sizeof(GTCHAR));


	
	GCSTextboxSetString( pLbl, szText );
}


/*******************************************************************************************/
/* Function - ClearToolTable					       									   */
/*																						   */
/* Purpose - Clearing the Table Data		                                 			   */
/*******************************************************************************************/

void GCLoadType::ClearToolTable()
{
	unsigned short  sretErr,i, j;
	GBaseObject *pTbl;

	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	for(i = 0 ; i < PAGE_TOOLNUM; i++)
	{
		for(j = 0; j < COL_SIZE; j++)
		{
			GCSNCTableSetCellString(pTbl, (GTCHAR *)"", i, j, &sretErr);
		}
	}
}

/*******************************************************************************************/
/* Function - clearWarningMessage														   */
/*																						   */
/* Purpose - To clear warning message on screen				 							   */
/*******************************************************************************************/
void GCLoadType::clearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");	
}

/*******************************************************************************************/
/* Function - ClearTable												     			   */
/*																					       */
/* Purpose - Clear Table Data			 												   */
/*******************************************************************************************/

void GCLoadType::ClearTable()
{
	unsigned short  sretErr;  // error code
	unsigned short i, j;
	GBaseObject *pTbl;

	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	for(i = 0 ; i <usPotsPerPage; i++)
	{
		for(j = 1; j < COL_SIZE; j++)
		{
			GCSNCTableSetCellString(pTbl, (GTCHAR *)"0", i, j, &sretErr);
		}
	}
	FetchData();																				// Fetch Tool data
	PrintToolData();																			// Printing tool data in to Table
}

/*******************************************************************************************/
/* Function - TeachModeProcess														   */
/*																						   */
/* Purpose - To Teach the Max Load of Tool				 							   */
/*******************************************************************************************/
void GCLoadType::TeachModeProcess()
{

	GBaseObject *pMaxLoadRecord;
	GTCHAR szText[PARAM_DATA_SIZE];

	char *cInputData;

	short sReadM3500 = 0;
	short sReadM3501 = 0;
	short sReadR28541 = 0;
	bool bReadMaxLoad = FALSE;

	if(bTeachModeFlag && !bReadMaxLoad)
	{

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9103),0, &sReadM3500, T_SHORT); // To get the Data Protection Status

		if(sReadM3500!=0)
			bReadMaxLoad = TRUE;
			
	}

	if(bReadMaxLoad)
	{
		pMaxLoadRecord = GCSGetChild(GetGBaseObject(), MAX_LOAD_RECORD);
		
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT_EXT(28541), 0, (void *)&sReadR28541, T_SHORT); 

		sReadR28541 = abs(sReadR28541);
		if(sReadR28541!=0 && sReadR28541<=100 )
		{
			GCSInputBoxGetString(pMaxLoadRecord, szText,sizeof(szText)/sizeof(GTCHAR));
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, szText, sizeof(szText)/sizeof(GTCHAR));
			
			short sCurLoad = atoi(cInputData);

			if(sReadR28541>sCurLoad){
				sprintf(cInputData, "%d",sReadR28541);

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSInputBoxSetString(pMaxLoadRecord, szText);
			}
		}

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9103),0, &sReadM3501, T_SHORT); // To get the Data Protection Status

		if(sReadM3501!=0)
			bReadMaxLoad = FALSE;
	}
}

bool GCLoadType::ToolSearch(char *cInputData)
{
	/* Checking for Inpu Data Present or Not */
	GBaseObject *pData, *pTbl;
	unsigned short sretErr, usRow, usCol, i;
	unsigned long usSrchNum;
	unsigned short usToolData;
	unsigned short usToolFlg=0;

	char *ptr;
	GTCHAR inpBuff[PARAM_DATA_SIZE];
		

	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);

	if(strlen(cInputData))
	{
		usSrchNum = strtoul(cInputData, &ptr, 16);
		/* Repetedly Reading and Comparing Searching Tool Num*/
		for(i = 0; i < usTotTool; i++)
		{
			melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,
											M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX + i), 0, &usToolData, T_SHORT); 
			/* Comparing Tool num with Search Tool num */
			if(usToolData == usSrchNum)													 
			{
				usToolFlg = 1;
				break;
			}
		}
		/* Checking for Searcing Tool Num with in Total Tool Num and Found or not */ 
		if(usSrchNum > 0 && usToolFlg == 1)
		{
			usSrchNum = i;
			usRemainPots =(   usTotTool - usSrchNum ) % PAGE_TOOLNUM;
			usPageNo = (usSrchNum /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
			/* Checking Searching Tool Number is >= 12 */ 
			if( (usTotTool - usSrchNum)>= PAGE_TOOLNUM )
			{
				usPotsPerPage = PAGE_TOOLNUM;
			}
			else
			{
				usPotsPerPage = usRemainPots;
			}
			
			usInitIndex[0] = INITTOOL_IDX + usSrchNum;
			usInitIndex[1] = INITLD_IDX + usSrchNum;
			usInitIndex[2] = INITMINLD_IDX   + usSrchNum;
			usInitIndex[3] = INITDATA_IDX + usSrchNum;
			usInitIndex[4] = INITTYPE_IDX   + usSrchNum;

			ClearToolTable();														// Clear table data
			FetchData();															// Fetch Tool data
			PrintToolData();														// Printing tool data in to Table
		}
		else
		{
			setWarningMessage(TOOL_NOT_EXISTS_ERR);
		}
	}
	GCSTextboxSetString(pData, (GTCHAR *)"");
	usRCcount = (usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;				// Updating Row Col Count
	/* Setting Sub Cursor Number to 0th Row and First Col */
	GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);

	if(usToolFlg==1)
		return TRUE;
	else
		return FALSE;
}

long GCLoadType::KEY_MARGIN_INPUTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pData, *pTbl;
	GBaseObject *pMaxLoadRecord,*pMarginInput;
	
	char cInputData[PARAM_DATA_SIZE];
	GTCHAR inpBuff[PARAM_DATA_SIZE];
		
	
	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pMaxLoadRecord = GCSGetChild(GetGBaseObject(), MAX_LOAD_RECORD);
	pMarginInput = GCSGetChild(GetGBaseObject(), MARGIN_INPUT);

	if(bTeachModeFlag)
	{
		GCSInputBoxGetString(pMaxLoadRecord, inpBuff,sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		
		short sRecordMaxLoad = atoi(cInputData);

		if(sRecordMaxLoad<100)
		{
			GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
			GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
			/* Checking for Inpu Data Present or Not */ 
			if(strlen(cInputData))
			{
				short sMarginInput = atoi(cInputData);
				if(sMarginInput<=25)
				{
					GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
					GCSInputBoxSetString(pMarginInput, inpBuff);
				}
				else{
					setWarningMessage(DATA_OUT_OF_RANGE_ERR);
				}
			}
		}
	}
	return TRUE;
}

#include "GCMaglist.hpp"
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
#include "CPotManager.hpp"
#include "Common.h"

extern "C"
{

void GCIDeleteGCMaglist( GBaseObject *pObject )
{
	GCMaglist *pPanel = (GCMaglist*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMaglist( GBaseObject *pObject )
{
	GCMaglist *pPanel = new GCMaglist;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMaglist;
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
GCMaglist::GCMaglist()
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
GCMaglist::~GCMaglist()
{

}

#include "GCMaglist.prc"

short GCMaglist::CreateChildren( )
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

GPropertyInfo* GCMaglist::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMaglist::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	int sFlag;

	
	/* Set Focus to DATA InputBox */
	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);
	}
	
	sFlag = InitPotInfo();																		// Initialize Pot Parameters 
	/* Checking for Initialization Success or Not */ 
	if(sFlag != TRUE)																				
		return FALSE;

	// Read Current Status of Spindle Tool and CLNT Type
	ReadSpindleToolStatusClntType();

	ReadIconStatus();
	ReadProgressBarStatus();
	return TRUE;
}

long GCMaglist::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
	struct PotInfo pt;

	GTCHAR inpBuffMain[10];
	char sDataMain[10];
	int ScountMain = 0;

	short sTouchFlg = 1;

	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	
	GetPotInfo(&pt);
	clearWarningMessage();   
	switch(lLParam)
	{
		case GK_F1:
				/*Pot Search */
				GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				/* Checking for Inpu Data Present or Not */ 
				if(strlen(cInputData))																
				{
					usSrchNum = atoi(cInputData);
					/* Checking for Pot number with in Total Tool number */ 
					if((usSrchNum> 0)&&(usSrchNum<= pt.usTotTool))											
					{
						/* Calculating Remaing pots */
						pt.usRemainPots =(pt.usTotTool - usSrchNum + INDEX_PLUS_ONE) % PAGE_TOOLNUM;  
						pt.usPageNo = (usSrchNum /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
						/* Checking Searching Pot Number is >= 12 */ 
						if( (pt.usTotTool - usSrchNum) >= PAGE_TOOLNUM )
						{
							pt.usPotsPerPage = PAGE_TOOLNUM;
						}
						else{
							pt.usPotsPerPage = pt.usRemainPots;
						}

						pt.usInitIndex[0] = INITTOOL_IDX + usSrchNum - INDEX_PLUS_ONE;
						pt.usInitIndex[1] = INITDATA_IDX + usSrchNum - INDEX_PLUS_ONE;
						pt.usInitIndex[2] = INITLD_IDX   + usSrchNum - INDEX_PLUS_ONE;
						
						ClearToolTable();														// Clear table data
						SetPotInfo(&pt);														// Set Screen parameters data structure
						FetchData();															// Fetch Tool data
						PrintToolData();														// Printing tool data in to Table
					}
					else{
						setWarningMessage(POT_NOT_EXISTS_ERR);
					}
				}

				GCSTextboxSetString(pData, (GTCHAR *)"");										// Clearing input box
				
				usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;				// Updating Row Col Count
				/* Setting Sub Cursor Number to 0th Row and First Col */
				GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);									 
		break;
		case GK_F2:
			// Tool Search
				GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
				GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
								
				/* Checking for Inpu Data Present or Not */ 
				if(strlen(cInputData))
				{
					usSrchNum = strtoul(cInputData, &ptr, 16);
					/* Repetedly Reading and Comparing Searching Tool Num*/
					for(i = 0; i < pt.usTotTool; i++)
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
						pt.usRemainPots =(pt.usTotTool - usSrchNum ) % PAGE_TOOLNUM;
						pt.usPageNo = (usSrchNum /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
						/* Checking Searching Tool Number is >= 12 */ 
						if( (pt.usTotTool - usSrchNum)>= PAGE_TOOLNUM )
						{
							pt.usPotsPerPage = PAGE_TOOLNUM;
						}
						else
						{
							pt.usPotsPerPage = pt.usRemainPots;
						}
						
						pt.usInitIndex[0] = INITTOOL_IDX + usSrchNum;
						pt.usInitIndex[1] = INITDATA_IDX + usSrchNum;
						pt.usInitIndex[2] = INITLD_IDX   + usSrchNum;
						ClearToolTable();														// Clear table data
						SetPotInfo(&pt);														// Set Screen parameters data structure
						FetchData();															// Fetch Tool data
						PrintToolData();														// Printing tool data in to Table
					}
					else
					{
						setWarningMessage(TOOL_NOT_EXISTS_ERR);
					}
				}
				GCSTextboxSetString(pData, (GTCHAR *)"");
				usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;				// Updating Row Col Count
				/* Setting Sub Cursor Number to 0th Row and First Col */
				GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);
				break;
		case GK_RETURN:																				
		case GK_F3:
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
		case GK_F4:
				// Cancel Button
				GCSTextboxSetString(pData, (GTCHAR *)"");
				clearWarningMessage();  
				break;
		case GK_F5:
					// Mag Clear Button
					// Fetch Program Execution State
					melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																						M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
					// Fetch Y708 Data
					melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																						 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
					// Checking for JOG mode
					if(lRunProg == 1 && permitData ==1)	
					{
							MagClearData();															// Clear ALL Tool Data
							setWarningMessage(MAG_CLEAR_COMPLETE); 
					}
					else
					{
						setWarningMessage(JOG_MODE_CLEAR_ERR); 
					}
					break;
		case GK_F6:
				// Pot Lock Button
				// Fetch Program Execution State
				melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																					M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
				// Fetch Y708 Data
				melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																					 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
				// Checking for JOG mode
				if(lRunProg == 1 && permitData ==1)	
				{
					sTimerFlg = 1;
					melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()), LOCK_WINDOW);
				}
				else
				{
					setWarningMessage(JOG_MODE_LOCK_ERR); 
				}
				break;
		case GK_F7:
				
				// tool Clear Button
				// Fetch Program Execution State
				melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																					M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
				// Fetch Y708 Data
				melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																					 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
				// Checking for JOG mode
				if(lRunProg == 1 && permitData ==1)	
				{
					GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
					usToolIndex = (pt.usInitIndex[0] % INITTOOL_IDX) + usRow;
					ClearToolData(usToolIndex, CLEAR);		  										// Clear Tool Data For Current Row
				}
				else
				{
					setWarningMessage(JOG_MODE_CLEAR_ERR); 
				}
				
		break;
		case GK_F8:
			sHelpFlg = 1;
			sTimerFlg = 1;
			DisableButtonName(); 
			GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),HELP_WINDOW);
		break;
		case GK_F9:
		//	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), BFW_SCREEN, 0), FALSE);
				
		break;
		case GK_NEXT:
	//	case GK_F8:
			// Next Button
			/* Setting Sub Cursor Number to 0th Row and First Col */
			 GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);				
		   	 /* Checking for Next page is Passible or not */
			 if(((pt.usInitIndex[0] - INITTOOL_IDX) + PAGE_TOOLNUM)< pt.usTotTool)
			 {
				usTemp = (pt.usInitIndex[0] - INITTOOL_IDX) + PAGE_TOOLNUM;
				ClearToolTable();					  	
				pt.usPageNo +=  PAGE_PLUS_ONE;
				/* Checking for Next page Contains 12 Tool ro Less */
				if((usTemp + PAGE_TOOLNUM) < pt.usTotTool)
				{
					pt.usPotsPerPage = PAGE_TOOLNUM;
				}
				else
				{
					pt.usRemainPots = (pt.usTotTool - usTemp);	
					pt.usPotsPerPage = pt.usRemainPots;
				}

				pt.usInitIndex[0] += PAGE_TOOLNUM;
				pt.usInitIndex[1] += PAGE_TOOLNUM;
				pt.usInitIndex[2] += PAGE_TOOLNUM;
				SetPotInfo(&pt);																// Set Screen parameters data structure
				FetchData();			 														// Fetch Tool data
				PrintToolData();			 													// Printing tool data in to Table
			 }
			 usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;					// Updating Row Col Count
		break;
		case GK_PRIOR:
	//	case GK_F9:
			// Back Button
			ClearToolTable(); 
			/* Setting Sub Cursor Number to 0th Row and First Col */
			GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);
			if(pt.usPageNo > 1)																	//Comparing page number
			{
				pt.usPageNo = pt.usPageNo - PAGE_PLUS_ONE;
					
				if((pt.usInitIndex[0] - INITTOOL_IDX) < PAGE_TOOLNUM)
				{
					pt.usPotsPerPage = pt.usInitIndex[0] - INITTOOL_IDX;
				}
				else
				{
					pt.usPotsPerPage = PAGE_TOOLNUM;
				}
				if(pt.usPotsPerPage == PAGE_TOOLNUM)
				{
					pt.usInitIndex[0] -= PAGE_TOOLNUM;
					pt.usInitIndex[1] -= PAGE_TOOLNUM;
					pt.usInitIndex[2] -= PAGE_TOOLNUM;
				}
				else 
				{
					pt.usInitIndex[0] -= pt.usPotsPerPage;
					pt.usInitIndex[1] -= pt.usPotsPerPage;
					pt.usInitIndex[2] -= pt.usPotsPerPage;
				}
				pt.usPotsPerPage = PAGE_TOOLNUM;
				SetPotInfo(&pt);																// Set Screen parameters data structure			
				FetchData();																	// Fetch Tool data
				PrintToolData();																// Printing tool data in to Table			
				}
			else if(pt.usPageNo  == 1)															//Comparing page number
			{
				usTemp = pt.usInitIndex[0] - INITTOOL_IDX;
				if(pt.usTotTool >= PAGE_TOOLNUM)
				{
					pt.usPotsPerPage = PAGE_TOOLNUM;
				}
				else
				{
					pt.usRemainPots = pt.usTotTool % PAGE_TOOLNUM;
					pt.usPotsPerPage = pt.usRemainPots;
				}

				
				pt.usInitIndex[0] -= usTemp;
				pt.usInitIndex[1] -= usTemp;
				pt.usInitIndex[2] -= usTemp;
				SetPotInfo(&pt);																// Set Screen parameters data structure
				FetchData();	 																// Fetch Tool data
				PrintToolData();																// Printing tool data in to Table
			}
			usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;					// Updating Row Col Count
		break;
		case GK_F10:   // F8 and F10 interchanged 18.01.2018 Raghu
			GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
		break;
		case GK_DELETE:
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
			/*Down arrow press event */
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			if(usRCcount < pt.usTotTool)														// Comparing Row Col Count with Total Tool
			{
				usRCcount++;
				usRow++;
				pt.usPageNo = (usRCcount /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
				if(usRow > TABLE_ROW_INDEX_END )												// Comparing Row is Lees tahn 11
				{
					
					pt.usInitIndex[0] += INDEX_PLUS_ONE;
					pt.usInitIndex[1] += INDEX_PLUS_ONE;
					pt.usInitIndex[2] += INDEX_PLUS_ONE;
					SetPotInfo(&pt);															// Set Screen parameters data structure
					FetchData();																// Fetch Tool data
					PrintToolData();															// Printing tool data in to Table
				}
			}
			/* Setting Sub Cursor Number to 0th Row and First Col */
			GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);			
		break;
		case GK_UP:
			// Up arrow press event
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
		
			if(usRCcount > 1)
			{
				usRCcount--;
				pt.usPageNo = (usRCcount / PAGE_TOOLNUM) + PAGE_PLUS_ONE;				
				if(	usRow == 0)
				{
					pt.usInitIndex[0] -= INDEX_PLUS_ONE;
					pt.usInitIndex[1] -= INDEX_PLUS_ONE;
					pt.usInitIndex[2] -= INDEX_PLUS_ONE;
					if((pt.usTotTool - usRCcount) < PAGE_TOOLNUM)
					{
						pt.usPotsPerPage = (pt.usTotTool - usRCcount) + 1;
					}

					SetPotInfo(&pt);															// Set Screen parameters data structure
					FetchData();		 														// Fetch Tool data
					PrintToolData();															// Printing tool data in to Table
				}
				
				usRow--;
			}
			/* Setting Sub Cursor Number to 0th Row and First Col */
			GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);
		break;			
		case GK_TAB:
			// Tab press event
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){					
				if( usCol > TOOL_COL_NUM )
				{
					usCol--;
					clearHelpMessage(); 
					if(usCol != 1)
					{
						ToolDataHelp(usCol); 
					}
				}
			}
			else{
				if( usCol < COL_SIZE - 1 )															// Comparing Col is less than 10
				{
					usCol++;
					clearHelpMessage(); 
					if(usCol != 1)
					{
						ToolDataHelp(usCol); 
					}
				}
			}
			/* Setting Sub Cursor Number to 0th Row and First Col */
			GCSNCTableSetSubCursorNum(pTbl, usRow, usCol, &sretErr);			
		break;
		case GK_ESCAPE:
			GCSTextboxSetString(pData, (GTCHAR *)"");
			clearWarningMessage();
		break;
		default:
			break;
	}
	return TRUE;
}

long GCMaglist::TOOL_MANAGE_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pTbl;
	unsigned short sretClr;
	unsigned short i;
	usRCcount = 1;																				// Reinitialize row col count

	unsigned int Color[COL_SIZE] = {0x008000, 0x99CCFF, 0xFF99CC, 0x800080, 0x33CCCC/*, 
											0xFF9900, 0xFFFF99, 0xFF5050, 0x00FFFF, 0xCCCC00*/};  // Color
	
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	for(i = 0; i < COL_SIZE; i++)
	{
		GCSNCTableSetRowTitleBackColor(pTbl, Color[i],i,&sretClr);								// Changing Table Title Color
	}

	/*	Setting Sub Cursor Number to 0th Row and First Col */
	GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretClr);
			
	InitToolTable(); 																			// Initialize Tool and Pot Info
	FetchData();																				// Fetch Tool Data
	PrintToolData();	
	return TRUE;
}


/*******************************************************************************************/
/* Function - FetchData																	   */
/*																						   */
/* Purpose - Read Tool Data From PLC Device						 						   */
/*******************************************************************************************/
void GCMaglist::FetchData() 
{
	unsigned short i, j, k;

	for(i = 0, j = 0; i < TABLE_ARRAY_SIZE; i++)
	{
		k = i % PAGE_TOOLNUM;																	// To get 0 to 11
		/* Fetching PLC data */
		if(i <= SECOND_PLC_DEVICE_END)
		{
			melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
							M_SSEC_PLWRD_R_1SHOT(pInfo->usInitIndex[j] + k), 0, &usTotToolData[i], T_SHORT);
		}
		else if( i > SECOND_PLC_DEVICE_END)
		{
			melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
							M_SSEC_PLWRD_R_1SHOT_EXT(pInfo->usInitIndex[j] + k), 0, &usTotToolData[i], T_SHORT);
		}
		
		// Changing PLC Device  number
		if( (i == FIRST_PLC_DEVICE_END) || (i == SECOND_PLC_DEVICE_END) )									
		{
			j++;
		}
	}
	setPotNumbers();																			// Setting Pot number
	SplitToolData();																			// Spliting Tool Data
}

/*******************************************************************************************/
/* Function - setPotNumbers																   */
/*																						   */
/* Purpose - Setting Pot Number					 										   */
/*******************************************************************************************/
void GCMaglist::setPotNumbers()
{
	unsigned short i, idx;
	/* Reading Pot number From PLC Device */
	for(i=0; i < pInfo->usPotsPerPage; i++)
	{
		idx = ( (pInfo->usInitIndex[0] + i) % INITTOOL_IDX ) + INDEX_PLUS_ONE;
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_TOL_REG,
									M_SSEC_TOLREG_POT_NO(idx), 0, &usTotToolData[36 + i], T_SHORT);
	}
}

/*******************************************************************************************/
/* Function - SplitToolData															       */
/*																						   */
/* Purpose - Spliting R10940 Series Device Data					 					       */
/*******************************************************************************************/
void GCMaglist::SplitToolData()
{
	const unsigned short usNbits = SPLIT_DATA_SIZE;
	unsigned short bits = sizeof(short) * 8;
	short i, j;
	/* Spliting Data in to 16 Bits */
	for(i=0; i < pInfo->usPotsPerPage; i++)
	{
		for(j = usNbits - 1; j >= 0; j--)
		{
			bit_g[i][j].bit = (1 && usTotToolData[PAGE_TOOLNUM + i] & ( 1 << (bits - 1)));		// Converting Byte into Bits
			bits--;
		}
		bits = sizeof(short) * 8;																// ReInitializing bits
	}
}

void GCMaglist::InitToolTable()
{
	struct PotInfo pt;
	double fPage;

	// Get Initial Pot Information Structure
	GetPotInfo(&pt);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																				M_SSEC_PLWRD_R_1SHOT(10610), 0, &pt.usTotTool, T_SHORT);
	pt.usInitIndex[0] = INITTOOL_IDX;
	pt.usInitIndex[1] = INITDATA_IDX;
	pt.usInitIndex[2] = INITLD_IDX;

	fPage = (double)(pt.usTotTool/12);
	if(fPage > (unsigned short)(fPage) )
		pt.usTotPages = (unsigned short)(fPage + 1);
	else
		pt.usTotPages = (unsigned short)fPage;

	pt.usRemainPots = pt.usTotTool % PAGE_TOOLNUM;
	pt.usPageNo = 1;
	if(pt.usTotPages >= 1)
		pt.usPotsPerPage = PAGE_TOOLNUM;
	else
		pt.usPotsPerPage = pt.usRemainPots;
	
	SetPotInfo(&pt);
}

/*******************************************************************************************/
/* Function - PrintToolData															       */
/*																					       */
/* Purpose - Printing Tool Data	, Pot number			 							       */
/*******************************************************************************************/
void GCMaglist :: PrintToolData()
{
	GBaseObject *pTbl;
	unsigned short i, usRow, usCol;
	unsigned short usRetCode;
	
	GTCHAR cellText[PARAM_DATA_SIZE];
	char cellData[PARAM_DATA_SIZE];
	
	pTbl = GCSGetChild(GetGBaseObject() ,TOOL_MANAGE_TABLE);
	/* Printing Tool data Into table */
	for(i = 0; i < pInfo->usPotsPerPage; i++)
	{
		usRow = i;
		usCol = 0;
		sprintf(cellData, "%d", usTotToolData[TABLE_ARRAY_SIZE + i]);
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);						// Printing Pot Number
		
		usCol = 1;
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
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);						// Printing Tool Number

		usCol = 6;
		sprintf(cellData, "%d", usTotToolData[THIRD_PLC_DEVICE_START + i]);
		GRCMultiByteToUnicode(0, cellText, cellData,sizeof(cellText));
		GCSNCTableSetCellString(pTbl, cellText, usRow, usCol, &usRetCode);						// Printing LD Data
	}
	PrintSplitToolData(bit_g);																	// Print Splited Tool Data 
}

/*******************************************************************************************/
/* Function - PrintSplitToolData													       */
/*																					       */
/* Purpose - To Print Splited Tool Data 				 							       */
/*******************************************************************************************/
void GCMaglist::PrintSplitToolData(Bit dbit_g[][SPLIT_DATA_SIZE])
{
	GBaseObject *pTbl;
	unsigned int i, j, k; 
	unsigned short bit;  
	unsigned short pusErrCode;
	unsigned short usCol, usRow;
	
	GTCHAR bitText[PARAM_DATA_SIZE];
	char bitData[PARAM_DATA_SIZE];

	pTbl = GCSGetChild(GetGBaseObject(),TOOL_MANAGE_TABLE);										//Get TOOLMANAGEMENTTABLE
	
	for(j = 0; j < pInfo->usPotsPerPage; j++)				
	{
		usRow = j;
		for( i = 0, k = 2; i < COL_SIZE ; i++)
		{
			if(i==3)																			// Checking for ACT_SP data											
			{
				bit = (dbit_g[j][i].bit << 1) + dbit_g[j][i+1].bit;								// Adding 3rd and 4th bit
				i++;
				usCol = k;
				k++;

			}
			else if(i==5)																		// Checking for CLNT data	
			{
				bit = (dbit_g[j][i].bit << 1) + dbit_g[j][i+1].bit;								// Adding 5th and 6th bit
				i++;
				k++;
				usCol = k;
				k++;
			}
			else
			{
				bit= dbit_g[j][i].bit;															
				usCol = k;
				k++;
			}
			
			sprintf(bitData, "%d", bit);														
		/* Convering  0 and 1 into orsponding Name */
		switch(i)
		{
			case 0:
					if(bit == 1)
					{
						GCSNCTableSetCellBackColor(pTbl, 0xFF99CC, usRow, usCol, &pusErrCode );
						sprintf(bitData, "%s", "LT");
					}
					else
					{
						GCSNCTableSetCellBackColor(pTbl, 0xFFFFFF, usRow, usCol, &pusErrCode );
					}
			break;
			case 1:
					if(bit == 1)
					{
						sprintf(bitData, "%s", "FT");
					}
			break;
			case 2:
					if(bit == 1)
					{
						sprintf(bitData, "%s", "WoS");
					}
			break;
			case 4:
					if(bit == 0)
					{
						sprintf(bitData, "%s", "Norm");
					}
					else if(bit == 1)
					{
						sprintf(bitData, "%s", "Med");
					}
					else if(bit == 2)
					{
						sprintf(bitData, "%s", "Low");
					}
			break;
			case 6:
					if(bit == 1)
					{
						sprintf(bitData, "%s", "M7");
					}
					else if(bit == 2)
					{
						sprintf(bitData, "%s", "M8");
					}
					else if(bit == 3)
					{
						sprintf(bitData, "%s", "M7&8");
					}
			break;
			case 7:
					if(bit == 1)
					{
						sprintf(bitData, "%s", "ON");
					}
					else 
					{
						sprintf(bitData, "%s", "OFF");
					}
			break;
			case 8:
					if(bit == 1)
					{
						sprintf(bitData, "%s", "ON");
					}
					else 
					{
						sprintf(bitData, "%s", "OFF");
					}
			break;
			default:
			break;
		}
			GRCMultiByteToUnicode(0, bitText, bitData, sizeof(bitText));
			GCSNCTableSetCellString(pTbl, bitText, usRow, usCol, &pusErrCode);
		}
	}
}

long GCMaglist::TOOL_MANAGE_TABLEOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	struct PotInfo pt;
	static int iTableCounter;
	static int iRefreshIconTimer = 0;
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	if(sTimerFlg == 0)
	{
		if(pChild != NULL)
		{
			GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
		}

		iTableCounter++;
		if(iTableCounter > 10)
		{
			// Get Initial Pot Information Structure
			GetPotInfo(&pt);																			// Get Screen parameters data structure
			SetPotInfo(&pt);																			// Set Screen parameters data structure

			FetchData();																				// Fetch Tool data
			PrintToolData();																			// Printing tool data in to Table
					
			// Refresh Current Status of Spindle Tool and CLNT Type
			ReadSpindleToolStatusClntType();																	
			iTableCounter = 0;
		}

		iRefreshIconTimer++;
		if(iRefreshIconTimer >=100) {
			ReadIconStatus();
			ReadProgressBarStatus();
			iRefreshIconTimer = 0;
		}
	}

	
	return TRUE;
}

void GCMaglist::ReadSpindleToolStatusClntType()
{
	GBaseObject *pPanel, *pChild1, *pChild2, *pChild3; 
	//GBaseObject *pClnt;
	unsigned short usCurdata;
	unsigned short usStat;
	GTCHAR szText[PARAM_DATA_SIZE];
	char chData[PARAM_DATA_SIZE];
	// Structure to store the status of the 10670 device, 
	union STATUS{													
	 struct {
		unsigned b0:1;													// To store the status of the LT }
		unsigned b1:1;													// To store the status of the FT }->SPINDLE TOOL STATUS
		unsigned b2:1;													// To store the status of the WoS }
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;													//  CURRENT CLNT TYPE status bit0
		unsigned b6:1;													//  CURRENT CLNT TYPE status bit1
	}bit;
	 unsigned short num;
	}tStat;

	pPanel = GetGBaseObject();
	pChild1 = GCSGetChild(pPanel, STAT1);
	pChild2 = GCSGetChild(pPanel, STAT2);
	pChild3 = GCSGetChild(pPanel, STAT3);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,
																			M_SSEC_PLWRD_R_1SHOT(10670), 0, &usCurdata, T_SHORT);
	tStat.num = usCurdata;
	
	if(tStat.bit.b0 == 1){																		// SPINDLE TOOL STATUS of LT
		GCSSetVisibleStatus(pChild1,TRUE);
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "LT", sizeof(szText)/sizeof(GTCHAR));
		GCSTextboxSetString( pChild1, szText );	
	}
	else{
		GCSSetVisibleStatus(pChild1,FALSE);
	}
	
	if(tStat.bit.b1 == 1){																		// SPINDLE TOOL STATUS of FT		
		GCSSetVisibleStatus(pChild2,TRUE);
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "FT", sizeof(szText)/sizeof(GTCHAR));
		GCSTextboxSetString(pChild2, szText);	 
	}
	else{
		GCSSetVisibleStatus(pChild2,FALSE);
	}
	
	if(tStat.bit.b2 == 1){																		// SPINDLE TOOL STATUS of WoS
		GCSSetVisibleStatus(pChild3,TRUE);
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "WoS", sizeof(szText)/sizeof(GTCHAR));
		GCSTextboxSetString( pChild3, szText );	 
	}
	else{
		GCSSetVisibleStatus(pChild3,FALSE);
	}
	
	usStat = (tStat.bit.b6 << 1) + tStat.bit.b5;												//  CURRENT CLNT TYPE status 
	if(usStat == 1){
		sprintf(chData, "%s", "M7");
	}
	else if(usStat == 2){
		sprintf(chData, "%s", "M8");
	}
	else if(usStat == 3){
		sprintf(chData, "%s", "M7&8");
	}
	else{
		sprintf(chData, "%d", usStat);
	}

	//GRCMultiByteToUnicode(0, szText, chData, sizeof(szText)/sizeof(GTCHAR)); 
	//GCSTextboxSetString( pClnt, szText );
	
}

/************************************************************************************/
/* Function - User																	*/
/*																					*/
/* Purpose - Invoked by GCSUser to communicate data/info between panel and window	*/
/************************************************************************************/
long GCMaglist::User(long lLParam, long lUParam)
{
	unsigned short sretErr, usRow, usCol;
	unsigned short usToolIndex, usLkValue = LOCK;
	struct PotInfo pt;
	short sTouchFlg = 0;

	GBaseObject *pData, *pTbl;
	pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	GetPotInfo(&pt);
	
	switch(lLParam)
	{
		case 0:	sTimerFlg = 0;
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
				GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				usToolIndex =  INITTOOL_IDX + (pt.usInitIndex[0] % INITTOOL_IDX) + usRow;
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																			M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&usLkValue, T_SHORT);
				FetchData();																	// Fetch Tool data
				PrintToolData();																// Printing tool data in to Table
		//		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
		break;	
		case 1: sTimerFlg = 0;
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
				GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
				usToolIndex = (pt.usInitIndex[0] % INITTOOL_IDX) + usRow;
				ClearToolData(usToolIndex, LOCK);
		//		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
		break;
		case 2:	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
						sTimerFlg = 0;
						melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
				}
		break;
		case 3:	if(pData != NULL){
					GCSChangeActiveFocus(GetGBaseObject(), pData);
					EnableButtonName();
						sHelpFlg = 0;
						sTimerFlg = 0;
						melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);

				}
		break;
		default:
		break;
	}
	return TRUE;
}

void GCMaglist::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_POT_SEARCH);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_TOOL_SEARCH);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_SET_BUTTON);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_CANCEL_BUTTON);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MAGAZINE_CLEAR);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_POT_LOCK);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_TOOL_CLEAR);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_HELP_WINDOW);
	pKeyButton[8] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//ID_STRING00145 = KEY_GCODE //ID_STRING00228 = g codes
	//ID_STRING00146 = KEY_MCODE //ID_STRING00229 = M-codes

	//ID_STRING00409 = KEY_POT_SEARCH
	//ID_STRING00410 = KEY_TOOL_SEARCH
	//ID_STRING00367 = KEY_SET_BUTTON
	//ID_STRING00368 = KEY_CANCEL_BUTTON
	//ID_STRING00411 = KEY_MAGAZINE_CLEAR
	//ID_STRING00412 = KEY_POT_LOCK
	//ID_STRING00020A  = KEY_TOOL_CLEAR
	//ID_STRING00101  = KEY_HELP_WINDOW
	//ID_STRING00023 = KEY_BACK

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00409);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING00410);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING00367);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING00368);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING00411);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00412);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00020A);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00101);
	GCSButtonSetStringID(pKeyButton[8], ID_STRING00023);
}

void GCMaglist::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_POT_SEARCH);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_TOOL_SEARCH);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_SET_BUTTON);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_CANCEL_BUTTON);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MAGAZINE_CLEAR);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_POT_LOCK);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_TOOL_CLEAR);
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


/*******************************************************************************************/		
/* Function - ClearToolData												     			   */
/*																						   */
/* Purpose - Clear Current tool data					 								   */
/*******************************************************************************************/

void GCMaglist::ClearToolData(unsigned short usIndex, unsigned short usLkClValue)
{
	GBaseObject *pTbl;
	unsigned short usToolIndex, sretErr;
	unsigned short lRunProg, permitData;
	unsigned short usZero = 0;
	unsigned short i;
	unsigned short usRow, usCol;
	GTCHAR szText[PARAM_DATA_SIZE];

	// Fetch Program Execution State
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																					M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
	// Fetch Y708 Data
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																					 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
	// Checking for JOG mode
	if(lRunProg == 1 && permitData == 1)	
	{
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		usToolIndex =  INITTOOL_IDX + usIndex;
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																			M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&usLkClValue, T_SHORT);

		usToolIndex =  INITDATA_IDX + usIndex;
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																			M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&usZero, T_SHORT);
		
		usToolIndex =  INITLD_IDX + usIndex;
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																			M_SSEC_PLWRD_R_1SHOT_EXT(usToolIndex), 0, (void *)&usZero, T_SHORT);
		
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "0", OUTPUT_BUFFER_SIZE);		// To get the Current RowNum
		GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
		
		for(i = 1; i < COL_SIZE; i++)
		{
			GCSNCTableSetCellString(pTbl, szText, usRow, i, &sretErr);
		}

		FetchData();																			// Fetch Tool data
		PrintToolData();																		// Printing tool data in to Table
	}
}



void GCMaglist::ReadIconStatus()
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
	short sIconR69 = 0;
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
	
	if(sIconR69 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC98!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC99!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9A!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9B!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9C!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconX1886!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconM9101!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
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


/************************************************************************************/
/* Function - ToolDataHelp															*/
/*																					*/
/* Purpose - Help Message and Reange Display										*/
/************************************************************************************/
void GCMaglist::ToolDataHelp(int HlpMsg)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), HELPBOX);	
	
	
	if(HlpMsg == 2)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Large Tool, Range: 0, 1 = LT", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 3)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Fix Tool, Range: 0, 1 = FT", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 4)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Without Spindle Rotation, Range: 0, 1 = WoS", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 5)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "ATC- Speed Range: 0 = Norm, 1 = Med, 2 = Low", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 6)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Load, Range: 0 to 120", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 7)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Coolent, Range: 0, 1 = M7, 2 = M8, 3 = M7&8", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 8)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Special Function 1, Range: 0 = OFF, 1 = ON", sizeof(szText)/sizeof(GTCHAR));
	else if(HlpMsg == 9)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Special Function 2, Range: 0 = OFF, 1 = ON", sizeof(szText)/sizeof(GTCHAR));
	
	GCSTextboxSetString( pLbl, szText );
}

/*******************************************************************************************/
/* Function - clearHelpMessage														   */
/*																						   */
/* Purpose - To clear help message on screen				 							   */
/*******************************************************************************************/
void GCMaglist::clearHelpMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), HELPBOX);

	GCSTextboxSetString( pLbl, (GTCHAR *)"");	
}



/*******************************************************************************************/
/* Function - MagClearData												     			   */
/*																						   */
/* Purpose - Clear all Tool Data			 											   */
/*******************************************************************************************/

void GCMaglist::MagClearData()
{
	unsigned short i, j;
	unsigned short usZero = 0;
	unsigned short usIndex[3];
	usIndex[0] = INITTOOL_IDX;
	usIndex[1] = INITDATA_IDX;
	usIndex[2] = INITLD_IDX;


	for(j = 0; j < 3; j++)
	{
		for(i = 0; i < pInfo->usTotTool; i++)
		{
			if(j < 2)
			{
				if(j == 0)
				{
					usZero = CLEAR;
				}
				else
				{
					usZero = 0;
				}
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT(usIndex[j] + i), 0, (void *)&usZero, T_SHORT);
			}
			else
			{
					melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT_EXT(usIndex[j] + i), 0, (void *)&usZero, T_SHORT);
			}
		}
	}
	melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,
																			M_SSEC_PLWRD_R_1SHOT(10620), 0, (void *)&usZero, T_SHORT);
	ClearTable();
}


void GCMaglist::ModifyData(char *cInputData, unsigned short usRow, unsigned short usCol)
{
	GBaseObject *pTbl;
	
	unsigned short usToolIndex;
	unsigned short usCurdata;
	unsigned short usToolVal;
	GTCHAR szText[PARAM_DATA_SIZE];
	unsigned short sretErr;
	char *ptr;
		
	union ATCLD{
	 struct {
		unsigned b0:1;
		unsigned b1:1;	
	}bit;
	  unsigned short val;
	}tcoldata;
	
	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);

	usToolIndex = pInfo->usInitIndex[1] + usRow;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, &usCurdata, T_SHORT);
	tData.num = usCurdata;

	switch(usCol)
	{
		case 1: 
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				usToolIndex = pInfo->usInitIndex[0] + usRow;
				usToolVal = strtoul(cInputData, &ptr, 16);;
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																	M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&usToolVal, T_SHORT); 
			break;
		case 2:tData.bits.b0 = atoi(cInputData);
				if(tData.bits.b0 == 1)
					sprintf(cInputData, "%s", "LT");

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
			break;
		case 3:tData.bits.b1 = atoi(cInputData);
				if(tData.bits.b1 == 1)
					sprintf(cInputData, "%s", "FT");

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
			break;
		case 4:tData.bits.b2 = atoi(cInputData);
				if(tData.bits.b2 == 1)
					sprintf(cInputData, "%s", "WoS");

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
			break;
		case 5:tcoldata.val = atoi(cInputData);
				tData.bits.b3 = tcoldata.bit.b1;
				tData.bits.b4 = tcoldata.bit.b0;
				if(tData.bits.b4 == 0 && tData.bits.b3 == 0)
					sprintf(cInputData, "%s", "Norm");
				else if(tData.bits.b4 == 1 && tData.bits.b3 == 0)
					sprintf(cInputData, "%s", "Med");
				else if(tData.bits.b4 == 0 && tData.bits.b3 == 1)
					sprintf(cInputData, "%s", "Low");

				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				break;
		case 6: GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				usToolIndex = pInfo->usInitIndex[2] + usRow;
				usToolVal = atoi(cInputData);
				melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT_EXT(usToolIndex), 0, (void *)&usToolVal, T_SHORT); 
		break;
		case 7:tcoldata.val = atoi(cInputData);
				tData.bits.b5 = tcoldata.bit.b1;
				tData.bits.b6 = tcoldata.bit.b0;
				if(tData.bits.b6 == 1 && tData.bits.b5 == 0)
					sprintf(cInputData, "%s", "M7");
				else if(tData.bits.b6 == 0 && tData.bits.b5 == 1)
					sprintf(cInputData, "%s", "M8");
				else if(tData.bits.b6 == 1 && tData.bits.b5 == 1)
					sprintf(cInputData, "%s", "M7&8");
				
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
				break;
		case 8:tData.bits.b7 = atoi(cInputData);
				if(tData.bits.b7 == 1)
					sprintf(cInputData, "%s", "ON");
				else
					sprintf(cInputData, "%s", "OFF");
				
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
			break;
		case 9:tData.bits.b8 = atoi(cInputData);
			if(tData.bits.b8 == 1)
					sprintf(cInputData, "%s", "ON");
				else
					sprintf(cInputData, "%s", "OFF");
				GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, cInputData, OUTPUT_BUFFER_SIZE);
				GCSNCTableSetCellString(pTbl, szText, usRow, usCol, &sretErr);
			break;
		
		default:
			break;
	}
	
	if( (usCol != 1) && (usCol != 6) )
		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, (void *)&tData.num, T_SHORT); 

}


/*******************************************************************************************/
/* Function - checkDataRange											        		   */
/*																						   */
/* Purpose - To Check Data Range Conditions				                        		   */
/*******************************************************************************************/
short GCMaglist::checkDataRange(unsigned short usRow, unsigned short usCol)
{
	short pot, tool;
	unsigned short NextTool, PrevTool;
	GBaseObject *pTbl;
	GTCHAR szText[PARAM_DATA_SIZE];
	char str[3];
	unsigned short sretErr;
	long lRunProg;
	short permitData;

	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	
	GCSNCTableGetCellString(pTbl, szText, 3, usRow, 0, &sretErr);
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), str, szText, sizeof(str));
	pot = atoi(str);

	GCSNCTableGetCellString(pTbl, szText, 3, usRow, 1, &sretErr);
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), str, szText, sizeof(str));
	tool = atoi(str);
	
	if(pot == 1)																				// Checking for pot is 1
	{	////Fetch first pot Data
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
												M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX + pInfo->usTotTool - 1), 0, &PrevTool, T_SHORT); 
	}
	else
	{
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
													M_SSEC_PLWRD_R_1SHOT(pInfo->usInitIndex[0] + usRow -1), 0, &PrevTool, T_SHORT);
	}
	
	if(pot == pInfo->usTotTool)																		// Checking for pot is last pot
	{	//Fetch last pot Data
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
														M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX ), 0, &NextTool, T_SHORT); 
	}
	else
	{
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
													M_SSEC_PLWRD_R_1SHOT(pInfo->usInitIndex[0] + usRow + 1 ), 0, &NextTool, T_SHORT);
	}
	
	// Fetch Program Execution State
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																					M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
	// Fetch Y708 Data
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																					 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
	// Checking for JOG mode
	if(lRunProg == 1 && permitData ==1)															
	{
		switch(usCol)
		{		
			//Checking for Pot and Tool num to less than or equ Zero
			case 2:if( (pot <= 0) && (tool < 0) )												
				   {
					   setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
					   return FALSE;
					}
					else if(PrevTool != CLEAR )														//Checking for Previous Tool NonZero
					{
						setWarningMessage(MAKE_LOWER_TOOL_ZERO_ERR);
						return FALSE;
					}
					else if(NextTool != CLEAR)														//Checking for Next Tool NonZero
					{
						setWarningMessage(MAKE_UPPER_TOOL_ZERO_ERR);
						return FALSE;
					}
				break;
			case 3: if(pot != tool)																	// Checking for Pot and Tool num not equ 
					{
						setWarningMessage(POT_AND_TOOL_NOT_EQU_ERR);
						return FALSE;
					}
					else if(tool >= CLEAR)															//Checking for Tool num to less than or  equ Zero																													
					{
						setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
						return FALSE;
					}
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9://Checking for Pot and Tool num to less than  Zero
					if( (pot < 0) && (tool < 0) )												
				   {
						setWarningMessage(POT_TOOL_NUM_ZERO_ERR);
						return FALSE;
				   }
				break;
			default:
				break;
		}
	}
	else
	{
			setWarningMessage(JOG_MODE_ERR);
			return FALSE;
	}

	return TRUE;
}



/*******************************************************************************************/
/* Function - checkInputValue											        		   */
/*																						   */
/* Purpose - To Check Input value 			                        					   */
/*******************************************************************************************/
short GCMaglist::checkInputValue(char *sdata, unsigned short usRow, unsigned short usCol)
{
	short sVal, i;
	unsigned short usToolVal;
	unsigned short usCurToolVal, usToolIndex;
	unsigned long usSwData;
	short lAlpha = 0;
	struct PotInfo pt;
	short len = strlen(sdata);
	char *ptr;

	sVal = atoi(sdata);
	GetPotInfo(&pt);
	usToolIndex =  pt.usInitIndex[0] + usRow;
	//Read data from PLC device
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT(usToolIndex), 0, &usCurToolVal, T_SHORT);
	/* Checking for Data is NT or LK */
	if((usCurToolVal != CLEAR && usCurToolVal != LOCK && usCurToolVal != 0) || usCol == 1)									
	{
		for(i = 0; i < len; i++)
				if(! ( (sdata[i] >= '0') && (sdata[i] <= '9') ))								// Checking for Alpha
					lAlpha =1;
		if(!lAlpha)																				// Checking for Numaric
		{
			switch(usCol)
			{
				case 1: 
						if(CheckForLargTool(usToolIndex) == FALSE)								// Check For Large Tool
							return FALSE;	
						usSwData = strtoul(sdata, &ptr, 16);
						/* Reading data from PLC Device and checking For Duplicate*/
						for(i=0; i < pInfo->usTotTool; i++)
						{
							melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																		M_SSEC_PLWRD_R_1SHOT(INITTOOL_IDX + i), 0, &usToolVal, T_SHORT);
							if(usSwData == usToolVal)												// Checking for Existing num
							{
								setWarningMessage(TOOL_NUM_EXISTS_ERR	);
								return FALSE;
							}
						}
						// Checking for Existing Spindle  Tool num
						melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD,
																			M_SSEC_PLWRD_R_1SHOT(10620), 0, &usToolVal, T_SHORT);
						
						if(usSwData == usToolVal)													// Checking for Existing Spindle  Tool num
						{
								setWarningMessage(SPINDLE_TOOL_NUM_MATCH_ERR	);
								return FALSE;
						}
						if(sVal > pInfo->usTotTool)												// Checking for Tool num is > Total Tool
						{
							setWarningMessage(DATA_OUT_OF_RANGE_ERR);
							return FALSE;
						}
						
				break;
				case 2:
				case 3:
				case 4:
				case 8:
				case 9: if( (sVal != 0) && (sVal != 1) )										// Checking 0 or 1 for LT, FT, etc
						{
							setWarningMessage(ENTER_ZERO_OR_ONE_ERR);
							return FALSE;
						}
				break;
				case 5:
						if(! ( (sVal  >= 0) && (sVal <= 2) ) )									// Checking 0 - 2 range for ATC-SP									
						{
							setWarningMessage(SETTING_ERR);
							return FALSE;
						}
				break;
				case 6:
						if(! ( (sVal  >= 0) && (sVal <= 120) ) )								// Checking 0 - 120 for LD
						{
							setWarningMessage(DATA_OUT_OF_RANGE_ERR);
							return FALSE;
						}
				break;
				case 7:	if(! ( (sVal  >= 0) && (sVal <= 3) ) )									// Checking 0 - 3 range for CLNT
						{
							setWarningMessage(DATA_OUT_OF_RANGE_ERR);
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
void GCMaglist::setWarningMessage(int warnnum)
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


	GCSTextboxSetString( pLbl, szText );
}


/*******************************************************************************************/
/* Function - ClearToolTable					       									   */
/*																						   */
/* Purpose - Clearing the Table Data		                                 			   */
/*******************************************************************************************/

void GCMaglist::ClearToolTable()
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
void GCMaglist::clearWarningMessage()
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

void GCMaglist::ClearTable()
{
	unsigned short  sretErr;  // error code
	unsigned short i, j;
	GBaseObject *pTbl;

	pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
	for(i = 0 ; i < pInfo->usPotsPerPage; i++)
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
/* Function - CheckForLargTool											     			   */
/*																						   */
/* Purpose - Checking for Large Tool(LT) in Next and previous W.R.T Current tool		   */
/*******************************************************************************************/

short GCMaglist::CheckForLargTool(unsigned short usToolNumIdx)
{
	unsigned short usIndex;
	unsigned short NextLt, PrevLt;
	unsigned short NextIndex, PrevIndex;
	usIndex = usToolNumIdx % INITTOOL_IDX;

	if(	usIndex == 0)
	{
		PrevIndex = INITDATA_IDX + pInfo->usTotTool - INDEX_PLUS_ONE;
		NextIndex = INITDATA_IDX + usIndex + INDEX_PLUS_ONE;
		
	}
	else if(usIndex == pInfo->usTotTool - INDEX_PLUS_ONE)
	{
		PrevIndex = INITDATA_IDX + usIndex - INDEX_PLUS_ONE;
		NextIndex = INITDATA_IDX ;
	}
	else
	{
		PrevIndex = INITDATA_IDX + usIndex - INDEX_PLUS_ONE;
		NextIndex = INITDATA_IDX + usIndex + INDEX_PLUS_ONE;
	}
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																				M_SSEC_PLWRD_R_1SHOT(PrevIndex), 0, &PrevLt, T_SHORT);
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, 
																				M_SSEC_PLWRD_R_1SHOT(NextIndex), 0, &NextLt, T_SHORT);
	if(PrevLt & 1) 
	{
		setWarningMessage(MAKE_LOWER_TOOL_BT_ZERO_ERR);
		return FALSE;
	}
	else if(NextLt & 1)
	{
		setWarningMessage(MAKE_UPPER_TOOL_BT_ZERO_ERR);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

long GCMaglist::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
	}
	else
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

long GCMaglist::KEY_CANCEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
		GBaseObject *pData;


		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);

		GCSTextboxSetString(pData, (GTCHAR *)"");
		clearWarningMessage();
	
	}
	return TRUE;
}

long GCMaglist::KEY_HELP_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
		sHelpFlg = 1;
		sTimerFlg = 1;
		DisableButtonName(); 
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),HELP_WINDOW);
	}
	return TRUE;
}

long GCMaglist::KEY_POT_LOCKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
		long lRunProg;
		short permitData;
		short sTouchFlg = 1;
		// Mag Clear Button
		// Fetch Program Execution State
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																			M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
		// Fetch Y708 Data
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																			 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
		// Checking for JOG mode
		if(lRunProg == 1 && permitData ==1)	
		{
			sTimerFlg = 1;
			melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT_EXT(20480),0, (void *)&sTouchFlg, T_SHORT);
			GCSCreateGWindow(GCSGetScreen(GetGBaseObject()), LOCK_WINDOW);
		}
		else
		{
			setWarningMessage(JOG_MODE_LOCK_ERR); 
		}
	}
	return TRUE;
}

long GCMaglist::KEY_POT_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
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
		struct PotInfo pt;

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		GetPotInfo(&pt);
		clearWarningMessage();   

		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		/* Checking for Inpu Data Present or Not */ 
		if(strlen(cInputData))																
		{
			usSrchNum = atoi(cInputData);
			/* Checking for Pot number with in Total Tool number */ 
			if((usSrchNum> 0)&&(usSrchNum<= pt.usTotTool))											
			{
				/* Calculating Remaing pots */
				pt.usRemainPots =(pt.usTotTool - usSrchNum + INDEX_PLUS_ONE) % PAGE_TOOLNUM;  
				pt.usPageNo = (usSrchNum /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
				/* Checking Searching Pot Number is >= 12 */ 
				if( (pt.usTotTool - usSrchNum) >= PAGE_TOOLNUM )
				{
					pt.usPotsPerPage = PAGE_TOOLNUM;
				}
				else{
					pt.usPotsPerPage = pt.usRemainPots;
				}

				pt.usInitIndex[0] = INITTOOL_IDX + usSrchNum - INDEX_PLUS_ONE;
				pt.usInitIndex[1] = INITDATA_IDX + usSrchNum - INDEX_PLUS_ONE;
				pt.usInitIndex[2] = INITLD_IDX   + usSrchNum - INDEX_PLUS_ONE;
				
				ClearToolTable();														// Clear table data
				SetPotInfo(&pt);														// Set Screen parameters data structure
				FetchData();															// Fetch Tool data
				PrintToolData();														// Printing tool data in to Table
			}
			else{
				setWarningMessage(POT_NOT_EXISTS_ERR);
			}
		}

		GCSTextboxSetString(pData, (GTCHAR *)"");										// Clearing input box
		
		usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;				// Updating Row Col Count
		/* Setting Sub Cursor Number to 0th Row and First Col */
		GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);
	}
	return TRUE;
}

long GCMaglist::KEY_SET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
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
		struct PotInfo pt;

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		GetPotInfo(&pt);
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

long GCMaglist::KEY_TOOL_CLEAROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
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
		struct PotInfo pt;


		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		GetPotInfo(&pt);
		clearWarningMessage();  

		// Mag Clear Button
		// Fetch Program Execution State
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																			M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
		// Fetch Y708 Data
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																			 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
		// Checking for JOG mode
		if(lRunProg == 1 && permitData ==1)	
		{
			GCSNCTableGetSubCursorNum(pTbl, &usRow, &usCol, &sretErr);
			usToolIndex = (pt.usInitIndex[0] % INITTOOL_IDX) + usRow;
			ClearToolData(usToolIndex, CLEAR);		  										// Clear Tool Data For Current Row
		}
		else
		{
			setWarningMessage(JOG_MODE_CLEAR_ERR); 
		}
	}
	return TRUE;
}

long GCMaglist::KEY_TOOL_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(sHelpFlg == 0)
	{
		clearWarningMessage();
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
		struct PotInfo pt;

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		GetPotInfo(&pt);
		clearWarningMessage();   

		GCSTextboxGetString(pData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), cInputData, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
						
		/* Checking for Input Data Present or Not */ 
		if(strlen(cInputData))
		{
			usSrchNum = strtoul(cInputData, &ptr, 16);
			/* Repetedly Reading and Comparing Searching Tool Num*/
			for(i = 0; i < pt.usTotTool; i++)
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
				pt.usRemainPots =(pt.usTotTool - usSrchNum ) % PAGE_TOOLNUM;
				pt.usPageNo = (usSrchNum /PAGE_TOOLNUM) + PAGE_PLUS_ONE;
				/* Checking Searching Tool Number is >= 12 */ 
				if( (pt.usTotTool - usSrchNum)>= PAGE_TOOLNUM )
				{
					pt.usPotsPerPage = PAGE_TOOLNUM;
				}
				else
				{
					pt.usPotsPerPage = pt.usRemainPots;
				}
				
				pt.usInitIndex[0] = INITTOOL_IDX + usSrchNum;
				pt.usInitIndex[1] = INITDATA_IDX + usSrchNum;
				pt.usInitIndex[2] = INITLD_IDX   + usSrchNum;
				ClearToolTable();														// Clear table data
				SetPotInfo(&pt);														// Set Screen parameters data structure
				FetchData();															// Fetch Tool data
				PrintToolData();														// Printing tool data in to Table
			}
			else
			{
				setWarningMessage(TOOL_NOT_EXISTS_ERR);
			}
		}
		GCSTextboxSetString(pData, (GTCHAR *)"");
		usRCcount = (pt.usInitIndex[0] % INITTOOL_IDX) + INDEX_PLUS_ONE;				// Updating Row Col Count
		/* Setting Sub Cursor Number to 0th Row and First Col */
		GCSNCTableSetSubCursorNum(pTbl, 0, 1, &sretErr);
	}
	return TRUE;
}


void GCMaglist::ReadProgressBarStatus()
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

long GCMaglist::KEY_MAGAZINE_CLEAROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
if(sHelpFlg == 0)
	{
		clearWarningMessage();
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
		struct PotInfo pt;

		pData  = GCSGetChild(GetGBaseObject(), KEYACTION);
		pTbl = GCSGetChild(GetGBaseObject(), TOOL_MANAGE_TABLE);
		
		GetPotInfo(&pt);
		clearWarningMessage();   
		
		// Mag Clear Button
		// Fetch Program Execution State
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, 
																			M_SSEC_PLBIT_X_1SHOT(3072),0, &lRunProg, T_LONG);
		// Fetch Y708 Data
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT,
																			 M_SSEC_PLBIT_Y_1SHOT(1800),0, &permitData, T_SHORT);
		// Checking for JOG mode
		if(lRunProg == 1 && permitData ==1)	
		{
				MagClearData();															// Clear ALL Tool Data
				setWarningMessage(MAG_CLEAR_COMPLETE); 
		}
		else
		{
			setWarningMessage(JOG_MODE_CLEAR_ERR); 
		}
	}
	return TRUE;
}

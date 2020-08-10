#include "GCLockWindow.hpp"
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

void GCIDeleteGCLockWindow( GBaseObject *pObject )
{
	GCLockWindow *pPanel = (GCLockWindow*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCLockWindow( GBaseObject *pObject )
{
	GCLockWindow *pPanel = new GCLockWindow;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCLockWindow;
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
GCLockWindow::GCLockWindow()
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
GCLockWindow::~GCLockWindow()
{

}

#include "GCLockWindow.prc"

short GCLockWindow::CreateChildren( )
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

GPropertyInfo* GCLockWindow::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCLockWindow::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	
	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);
	}

	sStringArray[0] = ID_STRING00376;
	sStringArray[1] = ID_STRING01313;
	sStringArray[2] = ID_STRING01314;

	GBaseObject *pStrLbl;
	pStrLbl = GCSGetChild(GetGBaseObject(), GLABEL00000);
	
	GCSLabelSetStringID(pStrLbl, sStringArray[sConfirmWindowNo]);

	return TRUE;
}

long GCLockWindow::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pWindow, *pParent;

	pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), LOCK_WINDOW + 1);
	
	pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));
	switch(lLParam)
	{
		case GK_Y:
				/*Yes*/
				if(sConfirmWindowNo == 1){
					sConfirmWindowNo = 2;
					GBaseObject *pStrLbl;
					pStrLbl = GCSGetChild(GetGBaseObject(), GLABEL00000);
					GCSLabelSetStringID(pStrLbl, sStringArray[sConfirmWindowNo]);
				}
				else if(sConfirmWindowNo == 2){
					GCSUser(pParent, 6, 0);
					if(pWindow)								// Closes Window
						GCSClose(pWindow);
				}
				else{
					GCSUser(pParent, 0, 0);
					if(pWindow)								// Closes Window
						GCSClose(pWindow);
				}					 
				break;
		case GK_N:
				// No
				if(sConfirmWindowNo == 1)
					GCSUser(pParent, 5, 0);
				else if(sConfirmWindowNo == 2)
					GCSUser(pParent, 7, 0);
				else
					GCSUser(pParent, 1, 0);
				if(pWindow)								// Closes Window
					GCSClose(pWindow);	
				break;
		default:
			break;
	}
	return TRUE;
}


long GCLockWindow::KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	static int iTableCounter;
	static int iRefreshIconTimer = 0;
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	

	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	return TRUE;
}

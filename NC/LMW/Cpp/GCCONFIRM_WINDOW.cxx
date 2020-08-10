#include "GCCONFIRM_WINDOW.hpp"
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

void GCIDeleteGCCONFIRM_WINDOW( GBaseObject *pObject )
{
	GCCONFIRM_WINDOW *pPanel = (GCCONFIRM_WINDOW*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCCONFIRM_WINDOW( GBaseObject *pObject )
{
	GCCONFIRM_WINDOW *pPanel = new GCCONFIRM_WINDOW;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCCONFIRM_WINDOW;
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
GCCONFIRM_WINDOW::GCCONFIRM_WINDOW()
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
GCCONFIRM_WINDOW::~GCCONFIRM_WINDOW()
{

}

#include "GCCONFIRM_WINDOW.prc"

short GCCONFIRM_WINDOW::CreateChildren( )
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

GPropertyInfo* GCCONFIRM_WINDOW::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCCONFIRM_WINDOW::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	
	/* Set Focus to KeyAction Basic Object */
	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);
	}
	return TRUE;
}

long GCCONFIRM_WINDOW::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pWindow, *pParent;

	pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), CONFIRM_WINDOW + 1);

	switch(lLParam)
	{
		// Check for YES confirmation
		case GK_Y:pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));
				GCSUser(pParent, 0, 0);					// Send Yes confirmation to delete the file

				if(pWindow)								// Closes Window
					GCSClose(pWindow);
		break;
		// Check for NO confirmation
		case GK_N:pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));
				GCSUser(pParent, 1, 0);					// No Operation

				if(pWindow)								// Closes Window
					GCSClose(pWindow);
		break;
		default:
		break;
	}
	return TRUE;
}

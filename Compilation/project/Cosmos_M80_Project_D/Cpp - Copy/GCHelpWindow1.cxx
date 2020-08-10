#include "GCHelpWindow1.hpp"
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

void GCIDeleteGCHelpWindow1( GBaseObject *pObject )
{
	GCHelpWindow1 *pPanel = (GCHelpWindow1*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCHelpWindow1( GBaseObject *pObject )
{
	GCHelpWindow1 *pPanel = new GCHelpWindow1;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCHelpWindow1;
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
GCHelpWindow1::GCHelpWindow1()
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
GCHelpWindow1::~GCHelpWindow1()
{

}

#include "GCHelpWindow1.prc"

short GCHelpWindow1::CreateChildren( )
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

GPropertyInfo* GCHelpWindow1::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCHelpWindow1::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
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

long GCHelpWindow1::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	static unsigned short iFrameNum = 0;
	GBaseObject *pWindow, *pFrame, *pParent;
	pFrame = GCSGetChild(GetGBaseObject(), HELPFRAME);
	pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), HELP_WINDOW+1);

	pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));

	switch(lLParam)
	{
		case GK_DOWN:
			
			if(iFrameNum < 2)
			{
				iFrameNum++;
				GCSShowPanel(pFrame, iFrameNum);
			}
		break;
		case GK_UP:
			
			if(iFrameNum >= 1)
			{
				iFrameNum--;
				GCSShowPanel(pFrame, iFrameNum); 
			}
		break;
		case GK_F10:
				iFrameNum = 0;
				GCSUser(pParent, 3, 0);	
				if(pWindow)								// Closes Window
					GCSClose(pWindow);
		break;
	}
	
	return TRUE;
}

long GCHelpWindow1::KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
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


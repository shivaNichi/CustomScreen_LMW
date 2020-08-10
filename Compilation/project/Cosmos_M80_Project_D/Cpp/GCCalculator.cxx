#include "GCCalculator.hpp"
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

void GCIDeleteGCCalculator( GBaseObject *pObject )
{
	GCCalculator *pPanel = (GCCalculator*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCCalculator( GBaseObject *pObject )
{
	GCCalculator *pPanel = new GCCalculator;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCCalculator;
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
GCCalculator::GCCalculator()
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
GCCalculator::~GCCalculator()
{

}

#include "GCCalculator.prc"

short GCCalculator::CreateChildren( )
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

GPropertyInfo* GCCalculator::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCCalculator::GSOFTKEY00001OnKeyRelease(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pWindow, *pParent;

	pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), CALCULATOR_WINDOW + 1);

	pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));

	switch(lLParam)
	{
		case GK_F10:
				if( (lUParam & KEY_BITALL) != 0){
					break;
				}
				GCSUser(pParent, 0, 0);	
				if(pWindow)								// Closes Window
					GCSClose(pWindow);

		break;
	}
	return TRUE;
}

long GCCalculator::GSOFTKEY00001OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), GSOFTKEY00001);
		
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);															//Setting active focus to Data object
	}

	return TRUE;
}

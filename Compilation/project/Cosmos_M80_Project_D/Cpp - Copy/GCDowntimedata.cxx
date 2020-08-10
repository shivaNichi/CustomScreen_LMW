#include "GCDowntimedata.hpp"
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

void GCIDeleteGCDowntimedata( GBaseObject *pObject )
{
	GCDowntimedata *pPanel = (GCDowntimedata*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCDowntimedata( GBaseObject *pObject )
{
	GCDowntimedata *pPanel = new GCDowntimedata;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCDowntimedata;
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
GCDowntimedata::GCDowntimedata()
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
GCDowntimedata::~GCDowntimedata()
{

}

#include "GCDowntimedata.prc"

short GCDowntimedata::CreateChildren( )
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

GPropertyInfo* GCDowntimedata::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCDowntimedata::KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);															//Setting active focus to Data object
	}
	return TRUE;
}

long GCDowntimedata::KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pWindow, *pParent;

	pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), DOWNTIME_DATA_WINDOW + 1);

	pParent = GCSGetPanel(GCSGetScreen(GetGBaseObject()));

	switch(lLParam)
	{
		case GK_F10:
				GCSUser(pParent, 0, 0);	
				if(pWindow)								// Closes Window
					GCSClose(pWindow);

		break;
	}
	return TRUE;
}

long GCDowntimedata::KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);															//Setting active focus to Data object
	}
	return TRUE;
}

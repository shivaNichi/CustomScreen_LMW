#include "GCSampleScreen.hpp"
#include "GWin.h"
#include "GCBasicControl.hpp"
#include "GCButton.hpp"
#include "GCLabel.hpp"
#include "GCList.hpp"
#include "GCPicture.hpp"
#include "GCTextBox.hpp"
#include "GCCheckBox.hpp"
#include "GCRadioButton.hpp"
#include "GCProgressBar.hpp"
#include "GCHtmlBrowser.hpp"
#include "GCScrollBarEx.hpp"
#include "GCSLine.hpp"
#include "GCSLines.hpp"
#include "GCSArc.hpp"
#include "GCSRect.hpp"
#include "GCSOval.hpp"
#include "GCSPoly.hpp"
#include "GCSPie.hpp"
#include "GCWindow.hpp"
#include "GEvent.h"
#include "GResource.h"
#include "GCSampleScreen.prc"


#ifdef NO_WINDOWS
/* Locale */
static unsigned char	ucMaxLocale = ID_LOC_LOCALE0 + 1;


/*
 *	<summary>		:	コンストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	コンストラクタ
 */
GCSampleScreenLMW::GCSampleScreenLMW()
{
	m_usType = GSCREEN;

	boScreenLMW.usType = GSCREEN;
	boScreenLMW.pSelf = this;
	boScreenLMW.GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	boScreenLMW.GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	boScreenLMW.pScreen = &boScreenLMW;
	m_pSelf = &boScreenLMW;
	m_boFrame.pScreen = m_pSelf;
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
GCSampleScreenLMW::~GCSampleScreenLMW()
{
	
}

GCClassMP(GCSampleScreenLMW)
GCInheritMP(GCScreen)

GCClassCBMP(GCSampleScreenLMW)
GCEndClassCBMP()

#ifdef __cplusplus
extern "C" {
#endif
extern unsigned char cFillPatternsLMW[][8];
extern unsigned char cLinePatternsLMW[][8];
extern GResource *hResourceLMW;
#ifdef __cplusplus
};
#endif


short GCSampleScreenLMW::Create( GBaseObject *pParent )
{
	hResourceLMW->ucMaxLocale = ucMaxLocale;

	if( GCScreen::Create( pParent ) == FALSE )
		return FALSE;

	short idx;
	for( idx = 0; idx<NUM_FILL_PATS; idx++ ){ 
		GDDefineFillPattern( m_hDraw, idx, (char*)cFillPatternsLMW[idx] );
	}
	for( idx = 0; idx<NUM_DASH_PATS; idx++ ){ 
		GDDefinePenDash( m_hDraw, idx+1, (char*)cLinePatternsLMW[idx] );
	}

	if( m_pScreenManager == NULL ){
		//{{INITIAL_PANEL
	ShowPanel( 0 );
		//}}INITIAL_PANEL
	}
		
	//{{INITIAL_LOCALE
	GRCSetLocale( ID_LOC_LOCALE0 );
	//}}INITIAL_LOCALE
	
	m_hResource = hResourceLMW;

	return TRUE;
}
#else//NO_WINDOWS
/*
 *	<summary>		:	コンストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	コンストラクタ
 */
GCSampleScreen::GCSampleScreen()
{
	m_usType = GSCREEN;

	boScreen.usType = GSCREEN;
	boScreen.pSelf = this;
	boScreen.GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	boScreen.GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	boScreen.pScreen = &boScreen;
	m_pSelf = &boScreen;
	m_boFrame.pScreen = m_pSelf;
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
GCSampleScreen::~GCSampleScreen()
{
	
}

GCClassMP(GCSampleScreen)
GCInheritMP(GCScreen)

GCClassCBMP(GCSampleScreen)
GCEndClassCBMP()

#ifdef __cplusplus
extern "C" {
#endif
extern unsigned char cFillPatterns[][8];
extern unsigned char cLinePatterns[][8];
extern GResource *hResource;
#ifdef __cplusplus
};
#endif


short GCSampleScreen::Create( GBaseObject *pParent )
{
	if( GCScreen::Create( pParent ) == FALSE )
		return FALSE;

	short idx;
	for( idx = 0; idx<NUM_FILL_PATS; idx++ ){ 
		GDDefineFillPattern( m_hDraw, idx, (char*)cFillPatterns[idx] );
	}
	for( idx = 0; idx<NUM_DASH_PATS; idx++ ){ 
		GDDefinePenDash( m_hDraw, idx+1, (char*)cLinePatterns[idx] );
	}

	if( m_pScreenManager == NULL ){
		//{{INITIAL_PANEL
	ShowPanel( 0 );
		//}}INITIAL_PANEL
	}
		
	//{{INITIAL_LOCALE
	GRCSetLocale( ID_LOC_LOCALE0 );
	//}}INITIAL_LOCALE
	
	m_hResource = hResource;

	return TRUE;
}
#endif//NO_WINDOWS

#ifdef NO_WINDOWS
GPropertyInfo* GCSampleScreenLMW::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
#else//NO_WINDOWS
GPropertyInfo* GCSampleScreen::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
#endif//NO_WINDOWS
{
	if (pImport->usType == GWINDOW)
	{
		if (pGPropertyInfoCnt != NULL)
		{
			*pGPropertyInfoCnt = sizeof(pGWindowPropertyInfo) / sizeof(GPropertyInfo);
		}
		return pGWindowPropertyInfo;
	}
	else
	{
		if (pGPropertyInfoCnt != NULL)
		{
			*pGPropertyInfoCnt = sizeof(pGPanelPropertyInfo) / sizeof(GPropertyInfo);
		}
		return pGPanelPropertyInfo;
	}
}


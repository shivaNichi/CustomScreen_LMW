// GCSample.cpp : アプリケーション用のエントリ ポイントの定義
//
#ifdef WIN32
#include "windows.h"
#endif/*WIN32*/
#include "genifa.h"
#include "GEvent.h"
#include "GWin.h"
#include "GResource.h"
#include "version.h"	// ILC-49


GScreenProperty gpSceenLMW={{GSCREEN,0,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,0,0},0},ID_FONT00000,ID_BORDER00002,RGB32(255,255,255),RGB32(212,208,200),RGB32(10,36,106),RGB32(128,128,128),256,ID_PALETTE00006};

#ifdef NO_WINDOWS
extern "C" const GBaseWindowProperty* GCSGetScreenPropertyLMW()
{
	return (const GBaseWindowProperty*)&gpSceenLMW;
}

extern "C" const unsigned long GCSGetVersionLMW()		// ILC-49
{													// ILC-49
	return GMODULE_VERSION;							// ILC-49
}													// ILC-49
#else//NO_WINDOWS
extern "C" const GBaseWindowProperty* GCSGetScreenProperty()
{
	return (const GBaseWindowProperty*)&gpSceenLMW;
}

extern "C" const unsigned long GCSGetVersion()		// ILC-49
{													// ILC-49
	return GMODULE_VERSION;							// ILC-49
}													// ILC-49
#endif//NO_WINDOWS

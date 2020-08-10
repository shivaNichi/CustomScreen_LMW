#if !defined _GCSAMPLESCREEN_HPP_
#define _GCSAMPLESCREEN_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCBaseWindow.hpp"
#include "GCScreen.hpp"
#include "string.h"

//{{OBJECT_TYPE
#define GLOGOSCREEN GUSERWINDOW_BASE+0
#define GCAUTIONSCREEN GUSERWINDOW_BASE+1
#define GEOS GUSERWINDOW_BASE+2
#define GPREVENTIVE_MAINT GUSERWINDOW_BASE+3
#define GCONFIRM_WINDOW GUSERWINDOW_BASE+4
#define GINOUTXY GUSERWINDOW_BASE+5
#define GINOUTL GUSERWINDOW_BASE+6
#define GALARMHIST GUSERWINDOW_BASE+7
#define GMCODE GUSERWINDOW_BASE+8
#define GGCODE GUSERWINDOW_BASE+9
#define GINITSCREEN GUSERWINDOW_BASE+10
#define GMTB_PASSWORD GUSERWINDOW_BASE+11
#define GMTB_SPSPEED GUSERWINDOW_BASE+12
#define GMTB_SPORIENTATION GUSERWINDOW_BASE+13
#define GMTB_AXIS GUSERWINDOW_BASE+14
#define GMTB_SYSINFO GUSERWINDOW_BASE+15
#define GSUB_SYSINFO GUSERWINDOW_BASE+16
#define GCOOLANT_SYS GUSERWINDOW_BASE+17
#define GLUBRICATION_SYS GUSERWINDOW_BASE+18
#define GHYDRAULIC_SYS GUSERWINDOW_BASE+19
#define GATC_ARM_SYS GUSERWINDOW_BASE+20
#define GATC_MAG_SYS GUSERWINDOW_BASE+21
#define GCHIP_CONVY_SYS GUSERWINDOW_BASE+22
#define GPOWER_CALC GUSERWINDOW_BASE+23
#define GSPINDLE_STATUS GUSERWINDOW_BASE+24
#define GMAINT_HOME GUSERWINDOW_BASE+25
#define GPOWER_CALC2 GUSERWINDOW_BASE+26
#define GMAINSCREEN GUSERWINDOW_BASE+27
#define GATC_INFO GUSERWINDOW_BASE+28
//}}OBJECT_TYPE

#ifdef NO_WINDOWS
class GCSampleScreenLMW : public GCScreen
{
public:
	//{{PUBLIC_METHOD
	GCSampleScreenLMW();
	virtual ~GCSampleScreenLMW();

	virtual short Create( GBaseObject *pParent );
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefMP()
	GCDefCBMP()					/* コールバックメッセージ処理　	*/
	GCDefCreateInstance()
	GCDefShowPanel()
	GCDefCreateGWindow()
	GCDefModalGWindow()
	GCDefLoadGWindow()
	//}}PROTECTED_METHOD
	
};

#else//NO_WINDOWS
class GCSampleScreen : public GCScreen
{
public:
	//{{PUBLIC_METHOD
	GCSampleScreen();
	virtual ~GCSampleScreen();

	virtual short Create( GBaseObject *pParent );
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefMP()
	GCDefCBMP()					/* コールバックメッセージ処理　	*/
	GCDefCreateInstance()
	GCDefShowPanel()
	GCDefCreateGWindow()
	GCDefModalGWindow()
	GCDefLoadGWindow()
	//}}PROTECTED_METHOD
	
};

#endif//NO_WINDOWS
#endif /* _GCSAMPLESCREEN_HPP_ */

#include "GCLOGOSCREEN.hpp"
#include "GCCAUTIONSCREEN.hpp"
#include "GCEOS.hpp"
#include "GCPreventive_Maint.hpp"
#include "GCCONFIRM_WINDOW.hpp"
#include "GCINOUTXY.hpp"
#include "GCINOUTL.hpp"
#include "GCALARMHIST.hpp"
#include "GCMCODE.hpp"
#include "GCGCODE.hpp"
#include "GCINITSCREEN.hpp"
#include "GCMTB_PASSWORD.hpp"
#include "GCMTB_SPSPEED.hpp"
#include "GCMTB_SPORIENTATION.hpp"
#include "GCMTB_AXIS.hpp"
#include "GCMTB_SYSINFO.hpp"
#include "GCSUB_SysInfo.hpp"
#include "GCCoolant_Sys.hpp"
#include "GCLubrication_Sys.hpp"
#include "GCHydraulic_Sys.hpp"
#include "GCATC_ARM_Sys.hpp"
#include "GCATC_MAG_Sys.hpp"
#include "GCChip_CONVY_Sys.hpp"
#include "GCPower_Calc.hpp"
#include "GCSPINDLE_Status.hpp"
#include "GCMaint_Home.hpp"
#include "GCPower_Calc2.hpp"
#include "GCMAINSCREEN.hpp"
#include "GCATC_Info.hpp"

#ifdef NO_WINDOWS
GCSampleScreenLMW theScreenLMW;
GBaseObject boScreenLMW;
extern "C" GBaseObject *GCSGetModuleScreenLMW(){ return theScreenLMW.GetGBaseObject(); }

static const GPanelPropertyEx gppPage0={{{GLOGOSCREEN,1,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},0},100,100}};
static const GPanelPropertyEx gppPage1={{{GCAUTIONSCREEN,2,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage2={{{GEOS,3,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,255,255),RGB32(255,255,255)},0},100,100}};
static const GPanelPropertyEx gppPage3={{{GPREVENTIVE_MAINT,4,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage4={{{GCONFIRM_WINDOW,5,0,0,380,40,7,NULL},{{FILL_BACK_COLOR,RGB32(223,112,0),RGB32(223,112,0)},0},100,100}};
static const GPanelPropertyEx gppPage5={{{GINOUTXY,6,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage6={{{GINOUTL,7,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage7={{{GALARMHIST,8,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage8={{{GMCODE,9,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage9={{{GGCODE,10,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage10={{{GINITSCREEN,11,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage11={{{GMTB_PASSWORD,12,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,255,255),RGB32(255,255,255)},0},100,100}};
static const GPanelPropertyEx gppPage12={{{GMTB_SPSPEED,13,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage13={{{GMTB_SPORIENTATION,14,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage14={{{GMTB_AXIS,15,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage15={{{GMTB_SYSINFO,16,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage16={{{GSUB_SYSINFO,17,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage17={{{GCOOLANT_SYS,18,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage18={{{GLUBRICATION_SYS,19,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage19={{{GHYDRAULIC_SYS,20,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage20={{{GATC_ARM_SYS,21,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage21={{{GATC_MAG_SYS,22,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage22={{{GCHIP_CONVY_SYS,23,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage23={{{GPOWER_CALC,24,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage24={{{GSPINDLE_STATUS,25,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage25={{{GMAINT_HOME,26,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage26={{{GPOWER_CALC2,27,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage27={{{GMAINSCREEN,28,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage28={{{GATC_INFO,29,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};

static GPropertyInfo pGPanelPropertyInfo[30] =
{
	{NULL, {0, 0}},
	{(void *)&gppPage0, {4, 44}},
	{(void *)&gppPage1, {4, 44}},
	{(void *)&gppPage2, {4, 44}},
	{(void *)&gppPage3, {4, 44}},
	{(void *)&gppPage4, {4, 44}},
	{(void *)&gppPage5, {4, 44}},
	{(void *)&gppPage6, {4, 44}},
	{(void *)&gppPage7, {4, 44}},
	{(void *)&gppPage8, {4, 44}},
	{(void *)&gppPage9, {4, 44}},
	{(void *)&gppPage10, {4, 44}},
	{(void *)&gppPage11, {4, 44}},
	{(void *)&gppPage12, {4, 44}},
	{(void *)&gppPage13, {4, 44}},
	{(void *)&gppPage14, {4, 44}},
	{(void *)&gppPage15, {4, 44}},
	{(void *)&gppPage16, {4, 44}},
	{(void *)&gppPage17, {4, 44}},
	{(void *)&gppPage18, {4, 44}},
	{(void *)&gppPage19, {4, 44}},
	{(void *)&gppPage20, {4, 44}},
	{(void *)&gppPage21, {4, 44}},
	{(void *)&gppPage22, {4, 44}},
	{(void *)&gppPage23, {4, 44}},
	{(void *)&gppPage24, {4, 44}},
	{(void *)&gppPage25, {4, 44}},
	{(void *)&gppPage26, {4, 44}},
	{(void *)&gppPage27, {4, 44}},
	{(void *)&gppPage28, {4, 44}},
};

static const GWindowPropertyEx gppWindow4={{{GWINDOW,5,145,220,380,40,GWINDOW_STYLE_EDGE|7,NULL},0}};

static GPropertyInfo pGWindowPropertyInfo[2] =
{
	{NULL, {0, 0}},
	{(void *)&gppWindow4, {4, 24}},
};

GCClassCreateInstance( GCSampleScreenLMW )
	GCDefCreateInstanceClass( GLOGOSCREEN, GCINewGCLOGOSCREEN )
	GCDefCreateInstanceClass( GCAUTIONSCREEN, GCINewGCCAUTIONSCREEN )
	GCDefCreateInstanceClass( GEOS, GCINewGCEOS )
	GCDefCreateInstanceClass( GPREVENTIVE_MAINT, GCINewGCPreventive_Maint )
	GCDefCreateInstanceClass( GCONFIRM_WINDOW, GCINewGCCONFIRM_WINDOW )
	GCDefCreateInstanceClass( GINOUTXY, GCINewGCINOUTXY )
	GCDefCreateInstanceClass( GINOUTL, GCINewGCINOUTL )
	GCDefCreateInstanceClass( GALARMHIST, GCINewGCALARMHIST )
	GCDefCreateInstanceClass( GMCODE, GCINewGCMCODE )
	GCDefCreateInstanceClass( GGCODE, GCINewGCGCODE )
	GCDefCreateInstanceClass( GINITSCREEN, GCINewGCINITSCREEN )
	GCDefCreateInstanceClass( GMTB_PASSWORD, GCINewGCMTB_PASSWORD )
	GCDefCreateInstanceClass( GMTB_SPSPEED, GCINewGCMTB_SPSPEED )
	GCDefCreateInstanceClass( GMTB_SPORIENTATION, GCINewGCMTB_SPORIENTATION )
	GCDefCreateInstanceClass( GMTB_AXIS, GCINewGCMTB_AXIS )
	GCDefCreateInstanceClass( GMTB_SYSINFO, GCINewGCMTB_SYSINFO )
	GCDefCreateInstanceClass( GSUB_SYSINFO, GCINewGCSUB_SysInfo )
	GCDefCreateInstanceClass( GCOOLANT_SYS, GCINewGCCoolant_Sys )
	GCDefCreateInstanceClass( GLUBRICATION_SYS, GCINewGCLubrication_Sys )
	GCDefCreateInstanceClass( GHYDRAULIC_SYS, GCINewGCHydraulic_Sys )
	GCDefCreateInstanceClass( GATC_ARM_SYS, GCINewGCATC_ARM_Sys )
	GCDefCreateInstanceClass( GATC_MAG_SYS, GCINewGCATC_MAG_Sys )
	GCDefCreateInstanceClass( GCHIP_CONVY_SYS, GCINewGCChip_CONVY_Sys )
	GCDefCreateInstanceClass( GPOWER_CALC, GCINewGCPower_Calc )
	GCDefCreateInstanceClass( GSPINDLE_STATUS, GCINewGCSPINDLE_Status )
	GCDefCreateInstanceClass( GMAINT_HOME, GCINewGCMaint_Home )
	GCDefCreateInstanceClass( GPOWER_CALC2, GCINewGCPower_Calc2 )
	GCDefCreateInstanceClass( GMAINSCREEN, GCINewGCMAINSCREEN )
	GCDefCreateInstanceClass( GATC_INFO, GCINewGCATC_Info )
GCEndClassCreateInstance()

GCClassShowPanel( GCSampleScreenLMW )
	GCDefPagePanel( 0, GLOGOSCREEN, gppPage0 )
	GCDefPagePanel( 1, GCAUTIONSCREEN, gppPage1 )
	GCDefPagePanel( 2, GEOS, gppPage2 )
	GCDefPagePanel( 3, GPREVENTIVE_MAINT, gppPage3 )
	GCDefPagePanel( 4, GCONFIRM_WINDOW, gppPage4 )
	GCDefPagePanel( 5, GINOUTXY, gppPage5 )
	GCDefPagePanel( 6, GINOUTL, gppPage6 )
	GCDefPagePanel( 7, GALARMHIST, gppPage7 )
	GCDefPagePanel( 8, GMCODE, gppPage8 )
	GCDefPagePanel( 9, GGCODE, gppPage9 )
	GCDefPagePanel( 10, GINITSCREEN, gppPage10 )
	GCDefPagePanel( 11, GMTB_PASSWORD, gppPage11 )
	GCDefPagePanel( 12, GMTB_SPSPEED, gppPage12 )
	GCDefPagePanel( 13, GMTB_SPORIENTATION, gppPage13 )
	GCDefPagePanel( 14, GMTB_AXIS, gppPage14 )
	GCDefPagePanel( 15, GMTB_SYSINFO, gppPage15 )
	GCDefPagePanel( 16, GSUB_SYSINFO, gppPage16 )
	GCDefPagePanel( 17, GCOOLANT_SYS, gppPage17 )
	GCDefPagePanel( 18, GLUBRICATION_SYS, gppPage18 )
	GCDefPagePanel( 19, GHYDRAULIC_SYS, gppPage19 )
	GCDefPagePanel( 20, GATC_ARM_SYS, gppPage20 )
	GCDefPagePanel( 21, GATC_MAG_SYS, gppPage21 )
	GCDefPagePanel( 22, GCHIP_CONVY_SYS, gppPage22 )
	GCDefPagePanel( 23, GPOWER_CALC, gppPage23 )
	GCDefPagePanel( 24, GSPINDLE_STATUS, gppPage24 )
	GCDefPagePanel( 25, GMAINT_HOME, gppPage25 )
	GCDefPagePanel( 26, GPOWER_CALC2, gppPage26 )
	GCDefPagePanel( 27, GMAINSCREEN, gppPage27 )
	GCDefPagePanel( 28, GATC_INFO, gppPage28 )
GCEndClassShowPanel()

GCClassCreateGWindow( GCSampleScreenLMW )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassCreateGWindow()

GCClassModalGWindow( GCSampleScreenLMW )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassModalGWindow()

GCClassLoadGWindow( GCSampleScreenLMW )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassLoadGWindow()
#else//NO_WINDOWS
GCSampleScreen theScreen;
GBaseObject boScreen;
GCScreen *GCWGetScreen(){ return &theScreen; }
extern "C" GBaseObject *GCSGetModuleScreen(){ return theScreen.GetGBaseObject(); }

static const GPanelPropertyEx gppPage0={{{GLOGOSCREEN,1,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},0},100,100}};
static const GPanelPropertyEx gppPage1={{{GCAUTIONSCREEN,2,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage2={{{GEOS,3,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,255,255),RGB32(255,255,255)},0},100,100}};
static const GPanelPropertyEx gppPage3={{{GPREVENTIVE_MAINT,4,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage4={{{GCONFIRM_WINDOW,5,0,0,380,40,7,NULL},{{FILL_BACK_COLOR,RGB32(223,112,0),RGB32(223,112,0)},0},100,100}};
static const GPanelPropertyEx gppPage5={{{GINOUTXY,6,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage6={{{GINOUTL,7,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage7={{{GALARMHIST,8,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage8={{{GMCODE,9,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage9={{{GGCODE,10,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage10={{{GINITSCREEN,11,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage11={{{GMTB_PASSWORD,12,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,255,255),RGB32(255,255,255)},0},100,100}};
static const GPanelPropertyEx gppPage12={{{GMTB_SPSPEED,13,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage13={{{GMTB_SPORIENTATION,14,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage14={{{GMTB_AXIS,15,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage15={{{GMTB_SYSINFO,16,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage16={{{GSUB_SYSINFO,17,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage17={{{GCOOLANT_SYS,18,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage18={{{GLUBRICATION_SYS,19,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage19={{{GHYDRAULIC_SYS,20,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage20={{{GATC_ARM_SYS,21,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage21={{{GATC_MAG_SYS,22,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage22={{{GCHIP_CONVY_SYS,23,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage23={{{GPOWER_CALC,24,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage24={{{GSPINDLE_STATUS,25,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage25={{{GMAINT_HOME,26,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage26={{{GPOWER_CALC2,27,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage27={{{GMAINSCREEN,28,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};
static const GPanelPropertyEx gppPage28={{{GATC_INFO,29,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,108),RGB32(0,0,108)},0},100,100}};

static GPropertyInfo pGPanelPropertyInfo[30] =
{
	{NULL, {0, 0}},
	{(void *)&gppPage0, {4, 44}},
	{(void *)&gppPage1, {4, 44}},
	{(void *)&gppPage2, {4, 44}},
	{(void *)&gppPage3, {4, 44}},
	{(void *)&gppPage4, {4, 44}},
	{(void *)&gppPage5, {4, 44}},
	{(void *)&gppPage6, {4, 44}},
	{(void *)&gppPage7, {4, 44}},
	{(void *)&gppPage8, {4, 44}},
	{(void *)&gppPage9, {4, 44}},
	{(void *)&gppPage10, {4, 44}},
	{(void *)&gppPage11, {4, 44}},
	{(void *)&gppPage12, {4, 44}},
	{(void *)&gppPage13, {4, 44}},
	{(void *)&gppPage14, {4, 44}},
	{(void *)&gppPage15, {4, 44}},
	{(void *)&gppPage16, {4, 44}},
	{(void *)&gppPage17, {4, 44}},
	{(void *)&gppPage18, {4, 44}},
	{(void *)&gppPage19, {4, 44}},
	{(void *)&gppPage20, {4, 44}},
	{(void *)&gppPage21, {4, 44}},
	{(void *)&gppPage22, {4, 44}},
	{(void *)&gppPage23, {4, 44}},
	{(void *)&gppPage24, {4, 44}},
	{(void *)&gppPage25, {4, 44}},
	{(void *)&gppPage26, {4, 44}},
	{(void *)&gppPage27, {4, 44}},
	{(void *)&gppPage28, {4, 44}},
};

static const GWindowPropertyEx gppWindow4={{{GWINDOW,5,145,220,380,40,GWINDOW_STYLE_EDGE|7,NULL},0}};

static GPropertyInfo pGWindowPropertyInfo[2] =
{
	{NULL, {0, 0}},
	{(void *)&gppWindow4, {4, 24}},
};

GCClassCreateInstance( GCSampleScreen )
	GCDefCreateInstanceClass( GLOGOSCREEN, GCINewGCLOGOSCREEN )
	GCDefCreateInstanceClass( GCAUTIONSCREEN, GCINewGCCAUTIONSCREEN )
	GCDefCreateInstanceClass( GEOS, GCINewGCEOS )
	GCDefCreateInstanceClass( GPREVENTIVE_MAINT, GCINewGCPreventive_Maint )
	GCDefCreateInstanceClass( GCONFIRM_WINDOW, GCINewGCCONFIRM_WINDOW )
	GCDefCreateInstanceClass( GINOUTXY, GCINewGCINOUTXY )
	GCDefCreateInstanceClass( GINOUTL, GCINewGCINOUTL )
	GCDefCreateInstanceClass( GALARMHIST, GCINewGCALARMHIST )
	GCDefCreateInstanceClass( GMCODE, GCINewGCMCODE )
	GCDefCreateInstanceClass( GGCODE, GCINewGCGCODE )
	GCDefCreateInstanceClass( GINITSCREEN, GCINewGCINITSCREEN )
	GCDefCreateInstanceClass( GMTB_PASSWORD, GCINewGCMTB_PASSWORD )
	GCDefCreateInstanceClass( GMTB_SPSPEED, GCINewGCMTB_SPSPEED )
	GCDefCreateInstanceClass( GMTB_SPORIENTATION, GCINewGCMTB_SPORIENTATION )
	GCDefCreateInstanceClass( GMTB_AXIS, GCINewGCMTB_AXIS )
	GCDefCreateInstanceClass( GMTB_SYSINFO, GCINewGCMTB_SYSINFO )
	GCDefCreateInstanceClass( GSUB_SYSINFO, GCINewGCSUB_SysInfo )
	GCDefCreateInstanceClass( GCOOLANT_SYS, GCINewGCCoolant_Sys )
	GCDefCreateInstanceClass( GLUBRICATION_SYS, GCINewGCLubrication_Sys )
	GCDefCreateInstanceClass( GHYDRAULIC_SYS, GCINewGCHydraulic_Sys )
	GCDefCreateInstanceClass( GATC_ARM_SYS, GCINewGCATC_ARM_Sys )
	GCDefCreateInstanceClass( GATC_MAG_SYS, GCINewGCATC_MAG_Sys )
	GCDefCreateInstanceClass( GCHIP_CONVY_SYS, GCINewGCChip_CONVY_Sys )
	GCDefCreateInstanceClass( GPOWER_CALC, GCINewGCPower_Calc )
	GCDefCreateInstanceClass( GSPINDLE_STATUS, GCINewGCSPINDLE_Status )
	GCDefCreateInstanceClass( GMAINT_HOME, GCINewGCMaint_Home )
	GCDefCreateInstanceClass( GPOWER_CALC2, GCINewGCPower_Calc2 )
	GCDefCreateInstanceClass( GMAINSCREEN, GCINewGCMAINSCREEN )
	GCDefCreateInstanceClass( GATC_INFO, GCINewGCATC_Info )
GCEndClassCreateInstance()

GCClassShowPanel( GCSampleScreen )
	GCDefPagePanel( 0, GLOGOSCREEN, gppPage0 )
	GCDefPagePanel( 1, GCAUTIONSCREEN, gppPage1 )
	GCDefPagePanel( 2, GEOS, gppPage2 )
	GCDefPagePanel( 3, GPREVENTIVE_MAINT, gppPage3 )
	GCDefPagePanel( 4, GCONFIRM_WINDOW, gppPage4 )
	GCDefPagePanel( 5, GINOUTXY, gppPage5 )
	GCDefPagePanel( 6, GINOUTL, gppPage6 )
	GCDefPagePanel( 7, GALARMHIST, gppPage7 )
	GCDefPagePanel( 8, GMCODE, gppPage8 )
	GCDefPagePanel( 9, GGCODE, gppPage9 )
	GCDefPagePanel( 10, GINITSCREEN, gppPage10 )
	GCDefPagePanel( 11, GMTB_PASSWORD, gppPage11 )
	GCDefPagePanel( 12, GMTB_SPSPEED, gppPage12 )
	GCDefPagePanel( 13, GMTB_SPORIENTATION, gppPage13 )
	GCDefPagePanel( 14, GMTB_AXIS, gppPage14 )
	GCDefPagePanel( 15, GMTB_SYSINFO, gppPage15 )
	GCDefPagePanel( 16, GSUB_SYSINFO, gppPage16 )
	GCDefPagePanel( 17, GCOOLANT_SYS, gppPage17 )
	GCDefPagePanel( 18, GLUBRICATION_SYS, gppPage18 )
	GCDefPagePanel( 19, GHYDRAULIC_SYS, gppPage19 )
	GCDefPagePanel( 20, GATC_ARM_SYS, gppPage20 )
	GCDefPagePanel( 21, GATC_MAG_SYS, gppPage21 )
	GCDefPagePanel( 22, GCHIP_CONVY_SYS, gppPage22 )
	GCDefPagePanel( 23, GPOWER_CALC, gppPage23 )
	GCDefPagePanel( 24, GSPINDLE_STATUS, gppPage24 )
	GCDefPagePanel( 25, GMAINT_HOME, gppPage25 )
	GCDefPagePanel( 26, GPOWER_CALC2, gppPage26 )
	GCDefPagePanel( 27, GMAINSCREEN, gppPage27 )
	GCDefPagePanel( 28, GATC_INFO, gppPage28 )
GCEndClassShowPanel()

GCClassCreateGWindow( GCSampleScreen )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassCreateGWindow()

GCClassModalGWindow( GCSampleScreen )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassModalGWindow()

GCClassLoadGWindow( GCSampleScreen )
	GCDefPageWindow( 4, GWINDOW, gppWindow4, GCONFIRM_WINDOW, gppPage4 )
GCEndClassLoadGWindow()
#endif//NO_WINDOWS

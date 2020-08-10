#include "GCHomeScreen1.hpp"
#include "GCPremach1.hpp"
#include "GCDuringmach.hpp"
#include "GCPostmach.hpp"
#include "GCDiagnosis.hpp"
#include "GCMainte.hpp"
#include "GCGcode.hpp"
#include "GCMcode.hpp"
#include "GCCutPara.hpp"
#include "GCDrillSel.hpp"
#include "GCMagView2.hpp"
#include "GCMaglist.hpp"
#include "GCLoadType.hpp"
#include "GCTREND.hpp"
#include "GCMCCond.hpp"
#include "GCMCCondsel.hpp"
#include "GCdailychk.hpp"
#include "GCmonthlychk.hpp"
#include "GCqutrlychk.hpp"
#include "GCPrevScreen.hpp"
#include "GCversion1.hpp"
#include "GCversion2.hpp"
#include "GCInput1.hpp"
#include "GCInput2.hpp"
#include "GCOutput1.hpp"
#include "GCOutput2.hpp"
#include "GCBITS1.hpp"
#include "GCBITS2.hpp"
#include "GCBITS3.hpp"
#include "GCBITS4.hpp"
#include "GCBITS5.hpp"
#include "GCBITS6.hpp"
#include "GCBITS7.hpp"
#include "GCBITS8.hpp"
#include "GCcycletime.hpp"
#include "GCDwntimeana.hpp"
#include "GCDwntimehis.hpp"
#include "GCdailyuti.hpp"
#include "GCdailutihis.hpp"
#include "GCOeeR.hpp"
#include "GCOeehis.hpp"
#include "GCOperset.hpp"
#include "GCAlarmhelp.hpp"
#include "GCCutOMeter1.hpp"
#include "GCBackup.hpp"
#include "GCCalculator.hpp"
#include "GCDowntimedata.hpp"
#include "GCLockWindow.hpp"
#include "GCHelpWindow1.hpp"
#include "GCDowntimedataM.hpp"
#include "GCHelpWindow1HelpFrame.hpp"
#include "GCHelpWindow1HelpFramePanel000.hpp"
#include "GCHelpWindow1HelpFramePanel001.hpp"

#ifdef NO_WINDOWS
GCSampleScreenCosmos_M80_Project_D theScreenCosmos_M80_Project_D;
GBaseObject boScreenCosmos_M80_Project_D;
extern "C" GBaseObject *GCSGetModuleScreenCosmos_M80_Project_D(){ return theScreenCosmos_M80_Project_D.GetGBaseObject(); }

static const GPanelPropertyEx gppPage0={{{GHOMESCREEN1,1,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,251,240),RGB32(255,251,240)},Background},100,100}};
static const GPanelPropertyEx gppPage1={{{GPREMACH1,2,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(128,128,128),RGB32(128,128,128)},Background},100,100}};
static const GPanelPropertyEx gppPage2={{{GDURINGMACH,3,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage3={{{GPOSTMACH,4,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage4={{{GDIAGNOSIS,5,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage5={{{GMAINTE,6,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage6={{{GGCODE,7,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage7={{{GMCODE,8,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage8={{{GCUTPARA,9,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage9={{{GDRILLSEL,10,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage10={{{GMAGVIEW2,11,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(192,192,192),RGB32(192,192,192)},bkgdf},100,100}};
static const GPanelPropertyEx gppPage11={{{GMAGLIST,12,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(192,192,192),RGB32(192,192,192)},Background},100,100}};
static const GPanelPropertyEx gppPage12={{{GLOADTYPE,13,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage13={{{GTREND,14,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage14={{{GMCCOND,15,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage15={{{GMCCONDSEL,16,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(160,160,164),RGB32(160,160,164)},Background},100,100}};
static const GPanelPropertyEx gppPage16={{{GDAILYCHK,17,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage17={{{GMONTHLYCHK,18,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage18={{{GQUTRLYCHK,19,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage19={{{GPREVSCREEN,20,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage20={{{GVERSION1,21,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage21={{{GVERSION2,22,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage22={{{GINPUT1,23,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage23={{{GINPUT2,24,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage24={{{GOUTPUT1,25,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage25={{{GOUTPUT2,26,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage26={{{GBITS1,27,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage27={{{GBITS2,28,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage28={{{GBITS3,29,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage29={{{GBITS4,30,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage30={{{GBITS5,31,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage31={{{GBITS6,32,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage32={{{GBITS7,33,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage33={{{GBITS8,34,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage34={{{GCYCLETIME,35,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage35={{{GDWNTIMEANA,36,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage36={{{GDWNTIMEHIS,37,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage37={{{GDAILYUTI,38,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage38={{{GDAILUTIHIS,39,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage39={{{GOEER,40,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage40={{{GOEEHIS,41,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage41={{{GOPERSET,42,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage42={{{GALARMHELP,43,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(120,120,120),RGB32(120,120,120)},Background},100,100}};
static const GPanelPropertyEx gppPage43={{{GCUTOMETER1,44,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,0),RGB32(0,0,0)},0},100,100}};
static const GPanelPropertyEx gppPage44={{{GBACKUP,45,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage45={{{GCALCULATOR,46,0,0,278,220,7,NULL},{{FILL_BACK_COLOR,RGB32(183,183,255),RGB32(183,183,255)},0},100,100}};
static const GPanelPropertyEx gppPage46={{{GDOWNTIMEDATA,47,0,0,280,280,7,NULL},{{FILL_BACK_COLOR,RGB32(166,202,240),RGB32(166,202,240)},0},100,100}};
static const GPanelPropertyEx gppPage47={{{GLOCKWINDOW,48,0,0,350,40,7,NULL},{{FILL_BACK_COLOR,RGB32(253,126,0),RGB32(253,126,0)},0},100,100}};
static const GPanelPropertyEx gppPage48={{{GHELPWINDOW1,49,0,0,640,406,7,NULL},{{FILL_BACK_COLOR,RGB32(238,248,250),RGB32(238,248,250)},0},100,100}};
static const GPanelPropertyEx gppPage49={{{GDOWNTIMEDATAM,50,0,0,350,330,7,NULL},{{FILL_BACK_COLOR,RGB32(255,251,240),RGB32(255,251,240)},0},100,100}};

static GPropertyInfo pGPanelPropertyInfo[51] =
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
	{(void *)&gppPage29, {4, 44}},
	{(void *)&gppPage30, {4, 44}},
	{(void *)&gppPage31, {4, 44}},
	{(void *)&gppPage32, {4, 44}},
	{(void *)&gppPage33, {4, 44}},
	{(void *)&gppPage34, {4, 44}},
	{(void *)&gppPage35, {4, 44}},
	{(void *)&gppPage36, {4, 44}},
	{(void *)&gppPage37, {4, 44}},
	{(void *)&gppPage38, {4, 44}},
	{(void *)&gppPage39, {4, 44}},
	{(void *)&gppPage40, {4, 44}},
	{(void *)&gppPage41, {4, 44}},
	{(void *)&gppPage42, {4, 44}},
	{(void *)&gppPage43, {4, 44}},
	{(void *)&gppPage44, {4, 44}},
	{(void *)&gppPage45, {4, 44}},
	{(void *)&gppPage46, {4, 44}},
	{(void *)&gppPage47, {4, 44}},
	{(void *)&gppPage48, {4, 44}},
	{(void *)&gppPage49, {4, 44}},
};

static const GWindowPropertyEx gppWindow45={{{GWINDOW,46,360,216,278,220,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING00164}};
static const GWindowPropertyEx gppWindow46={{{GWINDOW,47,360,156,280,280,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING00215}};
static const GWindowPropertyEx gppWindow47={{{GWINDOW,48,145,221,350,40,GWINDOW_STYLE_EDGE|7,NULL},0}};
static const GWindowPropertyEx gppWindow48={{{GWINDOW,49,0,30,640,406,GWINDOW_STYLE_EDGE|7,NULL},0}};
static const GWindowPropertyEx gppWindow49={{{GWINDOW,50,359,52,350,330,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_CLOSEBUTTON | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING01077}};

static GPropertyInfo pGWindowPropertyInfo[6] =
{
	{NULL, {0, 0}},
	{(void *)&gppWindow45, {4, 24}},
	{(void *)&gppWindow46, {4, 24}},
	{(void *)&gppWindow47, {4, 24}},
	{(void *)&gppWindow48, {4, 24}},
	{(void *)&gppWindow49, {4, 24}},
};

GCClassCreateInstance( GCSampleScreenCosmos_M80_Project_D )
	GCDefCreateInstanceClass( GHOMESCREEN1, GCINewGCHomeScreen1 )
	GCDefCreateInstanceClass( GPREMACH1, GCINewGCPremach1 )
	GCDefCreateInstanceClass( GDURINGMACH, GCINewGCDuringmach )
	GCDefCreateInstanceClass( GPOSTMACH, GCINewGCPostmach )
	GCDefCreateInstanceClass( GDIAGNOSIS, GCINewGCDiagnosis )
	GCDefCreateInstanceClass( GMAINTE, GCINewGCMainte )
	GCDefCreateInstanceClass( GGCODE, GCINewGCGcode )
	GCDefCreateInstanceClass( GMCODE, GCINewGCMcode )
	GCDefCreateInstanceClass( GCUTPARA, GCINewGCCutPara )
	GCDefCreateInstanceClass( GDRILLSEL, GCINewGCDrillSel )
	GCDefCreateInstanceClass( GMAGVIEW2, GCINewGCMagView2 )
	GCDefCreateInstanceClass( GMAGLIST, GCINewGCMaglist )
	GCDefCreateInstanceClass( GLOADTYPE, GCINewGCLoadType )
	GCDefCreateInstanceClass( GTREND, GCINewGCTREND )
	GCDefCreateInstanceClass( GMCCOND, GCINewGCMCCond )
	GCDefCreateInstanceClass( GMCCONDSEL, GCINewGCMCCondsel )
	GCDefCreateInstanceClass( GDAILYCHK, GCINewGCdailychk )
	GCDefCreateInstanceClass( GMONTHLYCHK, GCINewGCmonthlychk )
	GCDefCreateInstanceClass( GQUTRLYCHK, GCINewGCqutrlychk )
	GCDefCreateInstanceClass( GPREVSCREEN, GCINewGCPrevScreen )
	GCDefCreateInstanceClass( GVERSION1, GCINewGCversion1 )
	GCDefCreateInstanceClass( GVERSION2, GCINewGCversion2 )
	GCDefCreateInstanceClass( GINPUT1, GCINewGCInput1 )
	GCDefCreateInstanceClass( GINPUT2, GCINewGCInput2 )
	GCDefCreateInstanceClass( GOUTPUT1, GCINewGCOutput1 )
	GCDefCreateInstanceClass( GOUTPUT2, GCINewGCOutput2 )
	GCDefCreateInstanceClass( GBITS1, GCINewGCBITS1 )
	GCDefCreateInstanceClass( GBITS2, GCINewGCBITS2 )
	GCDefCreateInstanceClass( GBITS3, GCINewGCBITS3 )
	GCDefCreateInstanceClass( GBITS4, GCINewGCBITS4 )
	GCDefCreateInstanceClass( GBITS5, GCINewGCBITS5 )
	GCDefCreateInstanceClass( GBITS6, GCINewGCBITS6 )
	GCDefCreateInstanceClass( GBITS7, GCINewGCBITS7 )
	GCDefCreateInstanceClass( GBITS8, GCINewGCBITS8 )
	GCDefCreateInstanceClass( GCYCLETIME, GCINewGCcycletime )
	GCDefCreateInstanceClass( GDWNTIMEANA, GCINewGCDwntimeana )
	GCDefCreateInstanceClass( GDWNTIMEHIS, GCINewGCDwntimehis )
	GCDefCreateInstanceClass( GDAILYUTI, GCINewGCdailyuti )
	GCDefCreateInstanceClass( GDAILUTIHIS, GCINewGCdailutihis )
	GCDefCreateInstanceClass( GOEER, GCINewGCOeeR )
	GCDefCreateInstanceClass( GOEEHIS, GCINewGCOeehis )
	GCDefCreateInstanceClass( GOPERSET, GCINewGCOperset )
	GCDefCreateInstanceClass( GALARMHELP, GCINewGCAlarmhelp )
	GCDefCreateInstanceClass( GCUTOMETER1, GCINewGCCutOMeter1 )
	GCDefCreateInstanceClass( GBACKUP, GCINewGCBackup )
	GCDefCreateInstanceClass( GCALCULATOR, GCINewGCCalculator )
	GCDefCreateInstanceClass( GDOWNTIMEDATA, GCINewGCDowntimedata )
	GCDefCreateInstanceClass( GLOCKWINDOW, GCINewGCLockWindow )
	GCDefCreateInstanceClass( GHELPWINDOW1, GCINewGCHelpWindow1 )
	GCDefCreateInstanceClass( GDOWNTIMEDATAM, GCINewGCDowntimedataM )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAME, GCINewGCHelpWindow1HelpFrame )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAMEPANEL000, GCINewGCHelpWindow1HelpFramePanel000 )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAMEPANEL001, GCINewGCHelpWindow1HelpFramePanel001 )
GCEndClassCreateInstance()

GCClassShowPanel( GCSampleScreenCosmos_M80_Project_D )
	GCDefPagePanel( 0, GHOMESCREEN1, gppPage0 )
	GCDefPagePanel( 1, GPREMACH1, gppPage1 )
	GCDefPagePanel( 2, GDURINGMACH, gppPage2 )
	GCDefPagePanel( 3, GPOSTMACH, gppPage3 )
	GCDefPagePanel( 4, GDIAGNOSIS, gppPage4 )
	GCDefPagePanel( 5, GMAINTE, gppPage5 )
	GCDefPagePanel( 6, GGCODE, gppPage6 )
	GCDefPagePanel( 7, GMCODE, gppPage7 )
	GCDefPagePanel( 8, GCUTPARA, gppPage8 )
	GCDefPagePanel( 9, GDRILLSEL, gppPage9 )
	GCDefPagePanel( 10, GMAGVIEW2, gppPage10 )
	GCDefPagePanel( 11, GMAGLIST, gppPage11 )
	GCDefPagePanel( 12, GLOADTYPE, gppPage12 )
	GCDefPagePanel( 13, GTREND, gppPage13 )
	GCDefPagePanel( 14, GMCCOND, gppPage14 )
	GCDefPagePanel( 15, GMCCONDSEL, gppPage15 )
	GCDefPagePanel( 16, GDAILYCHK, gppPage16 )
	GCDefPagePanel( 17, GMONTHLYCHK, gppPage17 )
	GCDefPagePanel( 18, GQUTRLYCHK, gppPage18 )
	GCDefPagePanel( 19, GPREVSCREEN, gppPage19 )
	GCDefPagePanel( 20, GVERSION1, gppPage20 )
	GCDefPagePanel( 21, GVERSION2, gppPage21 )
	GCDefPagePanel( 22, GINPUT1, gppPage22 )
	GCDefPagePanel( 23, GINPUT2, gppPage23 )
	GCDefPagePanel( 24, GOUTPUT1, gppPage24 )
	GCDefPagePanel( 25, GOUTPUT2, gppPage25 )
	GCDefPagePanel( 26, GBITS1, gppPage26 )
	GCDefPagePanel( 27, GBITS2, gppPage27 )
	GCDefPagePanel( 28, GBITS3, gppPage28 )
	GCDefPagePanel( 29, GBITS4, gppPage29 )
	GCDefPagePanel( 30, GBITS5, gppPage30 )
	GCDefPagePanel( 31, GBITS6, gppPage31 )
	GCDefPagePanel( 32, GBITS7, gppPage32 )
	GCDefPagePanel( 33, GBITS8, gppPage33 )
	GCDefPagePanel( 34, GCYCLETIME, gppPage34 )
	GCDefPagePanel( 35, GDWNTIMEANA, gppPage35 )
	GCDefPagePanel( 36, GDWNTIMEHIS, gppPage36 )
	GCDefPagePanel( 37, GDAILYUTI, gppPage37 )
	GCDefPagePanel( 38, GDAILUTIHIS, gppPage38 )
	GCDefPagePanel( 39, GOEER, gppPage39 )
	GCDefPagePanel( 40, GOEEHIS, gppPage40 )
	GCDefPagePanel( 41, GOPERSET, gppPage41 )
	GCDefPagePanel( 42, GALARMHELP, gppPage42 )
	GCDefPagePanel( 43, GCUTOMETER1, gppPage43 )
	GCDefPagePanel( 44, GBACKUP, gppPage44 )
	GCDefPagePanel( 45, GCALCULATOR, gppPage45 )
	GCDefPagePanel( 46, GDOWNTIMEDATA, gppPage46 )
	GCDefPagePanel( 47, GLOCKWINDOW, gppPage47 )
	GCDefPagePanel( 48, GHELPWINDOW1, gppPage48 )
	GCDefPagePanel( 49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassShowPanel()

GCClassCreateGWindow( GCSampleScreenCosmos_M80_Project_D )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassCreateGWindow()

GCClassModalGWindow( GCSampleScreenCosmos_M80_Project_D )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassModalGWindow()

GCClassLoadGWindow( GCSampleScreenCosmos_M80_Project_D )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassLoadGWindow()
#else//NO_WINDOWS
GCSampleScreen theScreen;
GBaseObject boScreen;
GCScreen *GCWGetScreen(){ return &theScreen; }
extern "C" GBaseObject *GCSGetModuleScreen(){ return theScreen.GetGBaseObject(); }

static const GPanelPropertyEx gppPage0={{{GHOMESCREEN1,1,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(255,251,240),RGB32(255,251,240)},Background},100,100}};
static const GPanelPropertyEx gppPage1={{{GPREMACH1,2,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(128,128,128),RGB32(128,128,128)},Background},100,100}};
static const GPanelPropertyEx gppPage2={{{GDURINGMACH,3,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage3={{{GPOSTMACH,4,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage4={{{GDIAGNOSIS,5,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage5={{{GMAINTE,6,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage6={{{GGCODE,7,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage7={{{GMCODE,8,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage8={{{GCUTPARA,9,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage9={{{GDRILLSEL,10,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage10={{{GMAGVIEW2,11,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(192,192,192),RGB32(192,192,192)},bkgdf},100,100}};
static const GPanelPropertyEx gppPage11={{{GMAGLIST,12,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(192,192,192),RGB32(192,192,192)},Background},100,100}};
static const GPanelPropertyEx gppPage12={{{GLOADTYPE,13,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage13={{{GTREND,14,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage14={{{GMCCOND,15,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage15={{{GMCCONDSEL,16,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(160,160,164),RGB32(160,160,164)},Background},100,100}};
static const GPanelPropertyEx gppPage16={{{GDAILYCHK,17,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage17={{{GMONTHLYCHK,18,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage18={{{GQUTRLYCHK,19,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage19={{{GPREVSCREEN,20,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage20={{{GVERSION1,21,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage21={{{GVERSION2,22,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage22={{{GINPUT1,23,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage23={{{GINPUT2,24,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage24={{{GOUTPUT1,25,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage25={{{GOUTPUT2,26,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage26={{{GBITS1,27,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage27={{{GBITS2,28,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage28={{{GBITS3,29,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage29={{{GBITS4,30,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage30={{{GBITS5,31,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage31={{{GBITS6,32,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage32={{{GBITS7,33,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage33={{{GBITS8,34,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage34={{{GCYCLETIME,35,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage35={{{GDWNTIMEANA,36,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage36={{{GDWNTIMEHIS,37,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage37={{{GDAILYUTI,38,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage38={{{GDAILUTIHIS,39,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage39={{{GOEER,40,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage40={{{GOEEHIS,41,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage41={{{GOPERSET,42,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage42={{{GALARMHELP,43,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(120,120,120),RGB32(120,120,120)},Background},100,100}};
static const GPanelPropertyEx gppPage43={{{GCUTOMETER1,44,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(0,0,0),RGB32(0,0,0)},0},100,100}};
static const GPanelPropertyEx gppPage44={{{GBACKUP,45,0,0,640,480,7,NULL},{{FILL_BACK_COLOR,RGB32(98,98,98),RGB32(98,98,98)},Background},100,100}};
static const GPanelPropertyEx gppPage45={{{GCALCULATOR,46,0,0,278,220,7,NULL},{{FILL_BACK_COLOR,RGB32(183,183,255),RGB32(183,183,255)},0},100,100}};
static const GPanelPropertyEx gppPage46={{{GDOWNTIMEDATA,47,0,0,280,280,7,NULL},{{FILL_BACK_COLOR,RGB32(166,202,240),RGB32(166,202,240)},0},100,100}};
static const GPanelPropertyEx gppPage47={{{GLOCKWINDOW,48,0,0,350,40,7,NULL},{{FILL_BACK_COLOR,RGB32(253,126,0),RGB32(253,126,0)},0},100,100}};
static const GPanelPropertyEx gppPage48={{{GHELPWINDOW1,49,0,0,640,406,7,NULL},{{FILL_BACK_COLOR,RGB32(238,248,250),RGB32(238,248,250)},0},100,100}};
static const GPanelPropertyEx gppPage49={{{GDOWNTIMEDATAM,50,0,0,350,330,7,NULL},{{FILL_BACK_COLOR,RGB32(255,251,240),RGB32(255,251,240)},0},100,100}};

static GPropertyInfo pGPanelPropertyInfo[51] =
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
	{(void *)&gppPage29, {4, 44}},
	{(void *)&gppPage30, {4, 44}},
	{(void *)&gppPage31, {4, 44}},
	{(void *)&gppPage32, {4, 44}},
	{(void *)&gppPage33, {4, 44}},
	{(void *)&gppPage34, {4, 44}},
	{(void *)&gppPage35, {4, 44}},
	{(void *)&gppPage36, {4, 44}},
	{(void *)&gppPage37, {4, 44}},
	{(void *)&gppPage38, {4, 44}},
	{(void *)&gppPage39, {4, 44}},
	{(void *)&gppPage40, {4, 44}},
	{(void *)&gppPage41, {4, 44}},
	{(void *)&gppPage42, {4, 44}},
	{(void *)&gppPage43, {4, 44}},
	{(void *)&gppPage44, {4, 44}},
	{(void *)&gppPage45, {4, 44}},
	{(void *)&gppPage46, {4, 44}},
	{(void *)&gppPage47, {4, 44}},
	{(void *)&gppPage48, {4, 44}},
	{(void *)&gppPage49, {4, 44}},
};

static const GWindowPropertyEx gppWindow45={{{GWINDOW,46,360,216,278,220,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING00164}};
static const GWindowPropertyEx gppWindow46={{{GWINDOW,47,360,156,280,280,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING00215}};
static const GWindowPropertyEx gppWindow47={{{GWINDOW,48,145,221,350,40,GWINDOW_STYLE_EDGE|7,NULL},0}};
static const GWindowPropertyEx gppWindow48={{{GWINDOW,49,0,30,640,406,GWINDOW_STYLE_EDGE|7,NULL},0}};
static const GWindowPropertyEx gppWindow49={{{GWINDOW,50,359,52,350,330,GWINDOW_STYLE_TITLEBAR | GWINDOW_STYLE_CLOSEBUTTON | GWINDOW_STYLE_EDGE|7,NULL},ID_STRING01077}};

static GPropertyInfo pGWindowPropertyInfo[6] =
{
	{NULL, {0, 0}},
	{(void *)&gppWindow45, {4, 24}},
	{(void *)&gppWindow46, {4, 24}},
	{(void *)&gppWindow47, {4, 24}},
	{(void *)&gppWindow48, {4, 24}},
	{(void *)&gppWindow49, {4, 24}},
};

GCClassCreateInstance( GCSampleScreen )
	GCDefCreateInstanceClass( GHOMESCREEN1, GCINewGCHomeScreen1 )
	GCDefCreateInstanceClass( GPREMACH1, GCINewGCPremach1 )
	GCDefCreateInstanceClass( GDURINGMACH, GCINewGCDuringmach )
	GCDefCreateInstanceClass( GPOSTMACH, GCINewGCPostmach )
	GCDefCreateInstanceClass( GDIAGNOSIS, GCINewGCDiagnosis )
	GCDefCreateInstanceClass( GMAINTE, GCINewGCMainte )
	GCDefCreateInstanceClass( GGCODE, GCINewGCGcode )
	GCDefCreateInstanceClass( GMCODE, GCINewGCMcode )
	GCDefCreateInstanceClass( GCUTPARA, GCINewGCCutPara )
	GCDefCreateInstanceClass( GDRILLSEL, GCINewGCDrillSel )
	GCDefCreateInstanceClass( GMAGVIEW2, GCINewGCMagView2 )
	GCDefCreateInstanceClass( GMAGLIST, GCINewGCMaglist )
	GCDefCreateInstanceClass( GLOADTYPE, GCINewGCLoadType )
	GCDefCreateInstanceClass( GTREND, GCINewGCTREND )
	GCDefCreateInstanceClass( GMCCOND, GCINewGCMCCond )
	GCDefCreateInstanceClass( GMCCONDSEL, GCINewGCMCCondsel )
	GCDefCreateInstanceClass( GDAILYCHK, GCINewGCdailychk )
	GCDefCreateInstanceClass( GMONTHLYCHK, GCINewGCmonthlychk )
	GCDefCreateInstanceClass( GQUTRLYCHK, GCINewGCqutrlychk )
	GCDefCreateInstanceClass( GPREVSCREEN, GCINewGCPrevScreen )
	GCDefCreateInstanceClass( GVERSION1, GCINewGCversion1 )
	GCDefCreateInstanceClass( GVERSION2, GCINewGCversion2 )
	GCDefCreateInstanceClass( GINPUT1, GCINewGCInput1 )
	GCDefCreateInstanceClass( GINPUT2, GCINewGCInput2 )
	GCDefCreateInstanceClass( GOUTPUT1, GCINewGCOutput1 )
	GCDefCreateInstanceClass( GOUTPUT2, GCINewGCOutput2 )
	GCDefCreateInstanceClass( GBITS1, GCINewGCBITS1 )
	GCDefCreateInstanceClass( GBITS2, GCINewGCBITS2 )
	GCDefCreateInstanceClass( GBITS3, GCINewGCBITS3 )
	GCDefCreateInstanceClass( GBITS4, GCINewGCBITS4 )
	GCDefCreateInstanceClass( GBITS5, GCINewGCBITS5 )
	GCDefCreateInstanceClass( GBITS6, GCINewGCBITS6 )
	GCDefCreateInstanceClass( GBITS7, GCINewGCBITS7 )
	GCDefCreateInstanceClass( GBITS8, GCINewGCBITS8 )
	GCDefCreateInstanceClass( GCYCLETIME, GCINewGCcycletime )
	GCDefCreateInstanceClass( GDWNTIMEANA, GCINewGCDwntimeana )
	GCDefCreateInstanceClass( GDWNTIMEHIS, GCINewGCDwntimehis )
	GCDefCreateInstanceClass( GDAILYUTI, GCINewGCdailyuti )
	GCDefCreateInstanceClass( GDAILUTIHIS, GCINewGCdailutihis )
	GCDefCreateInstanceClass( GOEER, GCINewGCOeeR )
	GCDefCreateInstanceClass( GOEEHIS, GCINewGCOeehis )
	GCDefCreateInstanceClass( GOPERSET, GCINewGCOperset )
	GCDefCreateInstanceClass( GALARMHELP, GCINewGCAlarmhelp )
	GCDefCreateInstanceClass( GCUTOMETER1, GCINewGCCutOMeter1 )
	GCDefCreateInstanceClass( GBACKUP, GCINewGCBackup )
	GCDefCreateInstanceClass( GCALCULATOR, GCINewGCCalculator )
	GCDefCreateInstanceClass( GDOWNTIMEDATA, GCINewGCDowntimedata )
	GCDefCreateInstanceClass( GLOCKWINDOW, GCINewGCLockWindow )
	GCDefCreateInstanceClass( GHELPWINDOW1, GCINewGCHelpWindow1 )
	GCDefCreateInstanceClass( GDOWNTIMEDATAM, GCINewGCDowntimedataM )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAME, GCINewGCHelpWindow1HelpFrame )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAMEPANEL000, GCINewGCHelpWindow1HelpFramePanel000 )
	GCDefCreateInstanceClass( GHELPWINDOW1HELPFRAMEPANEL001, GCINewGCHelpWindow1HelpFramePanel001 )
GCEndClassCreateInstance()

GCClassShowPanel( GCSampleScreen )
	GCDefPagePanel( 0, GHOMESCREEN1, gppPage0 )
	GCDefPagePanel( 1, GPREMACH1, gppPage1 )
	GCDefPagePanel( 2, GDURINGMACH, gppPage2 )
	GCDefPagePanel( 3, GPOSTMACH, gppPage3 )
	GCDefPagePanel( 4, GDIAGNOSIS, gppPage4 )
	GCDefPagePanel( 5, GMAINTE, gppPage5 )
	GCDefPagePanel( 6, GGCODE, gppPage6 )
	GCDefPagePanel( 7, GMCODE, gppPage7 )
	GCDefPagePanel( 8, GCUTPARA, gppPage8 )
	GCDefPagePanel( 9, GDRILLSEL, gppPage9 )
	GCDefPagePanel( 10, GMAGVIEW2, gppPage10 )
	GCDefPagePanel( 11, GMAGLIST, gppPage11 )
	GCDefPagePanel( 12, GLOADTYPE, gppPage12 )
	GCDefPagePanel( 13, GTREND, gppPage13 )
	GCDefPagePanel( 14, GMCCOND, gppPage14 )
	GCDefPagePanel( 15, GMCCONDSEL, gppPage15 )
	GCDefPagePanel( 16, GDAILYCHK, gppPage16 )
	GCDefPagePanel( 17, GMONTHLYCHK, gppPage17 )
	GCDefPagePanel( 18, GQUTRLYCHK, gppPage18 )
	GCDefPagePanel( 19, GPREVSCREEN, gppPage19 )
	GCDefPagePanel( 20, GVERSION1, gppPage20 )
	GCDefPagePanel( 21, GVERSION2, gppPage21 )
	GCDefPagePanel( 22, GINPUT1, gppPage22 )
	GCDefPagePanel( 23, GINPUT2, gppPage23 )
	GCDefPagePanel( 24, GOUTPUT1, gppPage24 )
	GCDefPagePanel( 25, GOUTPUT2, gppPage25 )
	GCDefPagePanel( 26, GBITS1, gppPage26 )
	GCDefPagePanel( 27, GBITS2, gppPage27 )
	GCDefPagePanel( 28, GBITS3, gppPage28 )
	GCDefPagePanel( 29, GBITS4, gppPage29 )
	GCDefPagePanel( 30, GBITS5, gppPage30 )
	GCDefPagePanel( 31, GBITS6, gppPage31 )
	GCDefPagePanel( 32, GBITS7, gppPage32 )
	GCDefPagePanel( 33, GBITS8, gppPage33 )
	GCDefPagePanel( 34, GCYCLETIME, gppPage34 )
	GCDefPagePanel( 35, GDWNTIMEANA, gppPage35 )
	GCDefPagePanel( 36, GDWNTIMEHIS, gppPage36 )
	GCDefPagePanel( 37, GDAILYUTI, gppPage37 )
	GCDefPagePanel( 38, GDAILUTIHIS, gppPage38 )
	GCDefPagePanel( 39, GOEER, gppPage39 )
	GCDefPagePanel( 40, GOEEHIS, gppPage40 )
	GCDefPagePanel( 41, GOPERSET, gppPage41 )
	GCDefPagePanel( 42, GALARMHELP, gppPage42 )
	GCDefPagePanel( 43, GCUTOMETER1, gppPage43 )
	GCDefPagePanel( 44, GBACKUP, gppPage44 )
	GCDefPagePanel( 45, GCALCULATOR, gppPage45 )
	GCDefPagePanel( 46, GDOWNTIMEDATA, gppPage46 )
	GCDefPagePanel( 47, GLOCKWINDOW, gppPage47 )
	GCDefPagePanel( 48, GHELPWINDOW1, gppPage48 )
	GCDefPagePanel( 49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassShowPanel()

GCClassCreateGWindow( GCSampleScreen )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassCreateGWindow()

GCClassModalGWindow( GCSampleScreen )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassModalGWindow()

GCClassLoadGWindow( GCSampleScreen )
	GCDefPageWindow( 45, GWINDOW, gppWindow45, GCALCULATOR, gppPage45 )
	GCDefPageWindow( 46, GWINDOW, gppWindow46, GDOWNTIMEDATA, gppPage46 )
	GCDefPageWindow( 47, GWINDOW, gppWindow47, GLOCKWINDOW, gppPage47 )
	GCDefPageWindow( 48, GWINDOW, gppWindow48, GHELPWINDOW1, gppPage48 )
	GCDefPageWindow( 49, GWINDOW, gppWindow49, GDOWNTIMEDATAM, gppPage49 )
GCEndClassLoadGWindow()
#endif//NO_WINDOWS

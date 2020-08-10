
GCClassCBMP(GCCAUTIONSCREEN)
	GCDefCBMsg(GM_CB_ONKEYPRESS, DATA, DATAOnKeyPress )
	GCDefCBMsg(GM_CB_ONTIMER, DATA, DATAOnTimer )
	GCDefCBMsg(GM_CB_ONCREATE, DATA, DATAOnCreate )
	GCDefCBMsg(GM_CB_ONCLICK, BTNPROCEED, BTNPROCEEDOnClick )
GCEndClassCBMP()

static const GFocusInformation pGLabel00000FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGNXMonitorStatus00002FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGNXTime00003FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00004FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00012FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00013FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00014FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00015FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBTNPROCEEDFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGNCDataTextBox00019FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGPicture00021FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pDATAFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGSLine00005FocusInformation =
{
	0,
	NULL
};

static const GBasicControlProperty pGBasicControlpProperty[1] =
{

	{{{GBASICCONTROL, GCCAUTIONSCREEN::DATA, 572, 388, 63, 34, GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pDATAFocusInformation}}}
};
static const GButtonProperty pGButtonpProperty[1] =
{

	{{{GBUTTON, GCCAUTIONSCREEN::BTNPROCEED, 577, 439, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBTNPROCEEDFocusInformation}}, ID_STRING00438,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GLabelProperty pGLabelpProperty[6] =
{

	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00000, 0, 40, 640, 100, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00000FocusInformation}}, ID_STRING00431,{RGB32(255,156,108), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00432,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00004, 3, -1, 80, 28, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00004FocusInformation}}, ID_STRING00525,{RGB32(0,255,255), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00104,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00012, 50, 280, 540, 60, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00012FocusInformation}}, ID_STRING00436,{RGB32(255,255,255), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00434,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00013, 50, 210, 540, 60, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00013FocusInformation}}, ID_STRING00435,{RGB32(255,255,255), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00434,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00014, 50, 140, 540, 60, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00014FocusInformation}}, ID_STRING00433,{RGB32(255,255,255), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00434,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GLABEL, GCCAUTIONSCREEN::GLABEL00015, 0, 360, 640, 60, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00015FocusInformation}}, ID_STRING00437,{RGB32(255,0,0), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00434,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GNCDataTextBoxProperty pGNCDataTextBoxpProperty[1] =
{

	{{{{GNCDATATEXTBOX, GCCAUTIONSCREEN::GNCDATATEXTBOX00019, 483, 1, 102, 22, GW_STYLE_VISIBLE | GW_STYLE_ENABLE | GNCTEXT_STYLE_REFUSE_SML | GNCTEXT_STYLE_ZEROSUPPRESS, (GFocusInformation*)&pGNCDataTextBox00019FocusInformation}}, 1, 1, 0, 0},{RGB32(255,255,255), GCAPTION_POS_RIGHT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, ID_BORDER00185, RGB32(255,255,255), RGB32(0,0,0), RGB32(255,255,255), 32, NO_DRAW, GNCTEXT_TYPE_STRING, GFOCUS_EFFECT_NON, 10, 10, 40, 6, GNCDATA_TYPE_STRING, 1.000000, 0, 0, 6, 4}
};
static const GNXMonitorStatusProperty pGNXMonitorStatuspProperty[1] =
{

	{{{{GNXMONITORSTATUS, GCCAUTIONSCREEN::GNXMONITORSTATUS00002, 425, 4, 40, 20, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGNXMonitorStatus00002FocusInformation}}, 1, 1, 0, 0}, RGB32(0,0,108), GMM_OFF, GNORMAL_BOLD_FONT, 0, 0, RGB32(255,255,255), 0, 4, 3, GPROPERTY_COLOR, 0, 0, 0, 0}
};
static const GNXTimeProperty pGNXTimepProperty[1] =
{

	{{{{GNXTIME, GCCAUTIONSCREEN::GNXTIME00003, 590, 4, 50, 20, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGNXTime00003FocusInformation}}, 1, 1, 0, 0}, RGB32(255,255,255), RGB32(0,0,108), GMM_OFF, GNORMAL_FONT, GPROPERTY_COLOR, 0, 0, 0, 0, 0, 0}
};
static const GDesign pGPicture00021Design[1] = {
	{{ FILL_BACK_COLOR , RGB32(192,192,192), RGB32(0,0,108)} , ID_CAUTION}
};

static const GVector pGPicture00021Vector[1] = {
	{0 , 0, 1, 10000, 100}
};

static const GPicturePropertyEx pGPicturepProperty[1] =
{

	{{{{GPICTURE, GCCAUTIONSCREEN::GPICTURE00021, 197, 75, 50, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGPicture00021FocusInformation}}, 0,{RGB32(0,0,0), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0, GPCTR_DISP_IMAGE, 1, (GDesign*)pGPicture00021Design,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}, (GVector*)pGPicture00021Vector, GPCTR_EFFECT_NONE, GPCTR_EFFECT_NONE, 100, 0}
};
static const GSLinePropertyEx pGSLinepProperty[1] =
{

	{{{{GSLINE, GCCAUTIONSCREEN::GSLINE00005, 0, 29, 641, 1, GW_STYLE_VISIBLE, (GFocusInformation*)&pGSLine00005FocusInformation}, RGB32(255,255,255), 2, 0},{0, 29, 640, 29}}}
};

static GPropertyInfo pGPropertyInfo[14] =
{
	{NULL, {0, 0}},
	{(void *)&pGLabelpProperty[0], {4, 68}},
	{(void *)&pGNXMonitorStatuspProperty[0], {4, 76}},
	{(void *)&pGNXTimepProperty[0], {4, 64}},
	{(void *)&pGLabelpProperty[1], {4, 68}},
	{(void *)&pGSLinepProperty[0], {4, 36}},
	{(void *)&pGLabelpProperty[2], {4, 68}},
	{(void *)&pGLabelpProperty[3], {4, 68}},
	{(void *)&pGLabelpProperty[4], {4, 68}},
	{(void *)&pGLabelpProperty[5], {4, 68}},
	{(void *)&pGBasicControlpProperty[0], {4, 20}},
	{(void *)&pGButtonpProperty[0], {4, 136}},
	{(void *)&pGNCDataTextBoxpProperty[0], {4, 120}},
	{(void *)&pGPicturepProperty[0], {4, 90}},
};

static const GBaseWindowProperty *pProperty[14] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGLabelpProperty[0],
	(const GBaseWindowProperty*) &pGNXMonitorStatuspProperty[0],
	(const GBaseWindowProperty*) &pGNXTimepProperty[0],
	(const GBaseWindowProperty*) &pGLabelpProperty[1],
	(const GBaseWindowProperty*) &pGSLinepProperty[0],
	(const GBaseWindowProperty*) &pGLabelpProperty[2],
	(const GBaseWindowProperty*) &pGLabelpProperty[3],
	(const GBaseWindowProperty*) &pGLabelpProperty[4],
	(const GBaseWindowProperty*) &pGLabelpProperty[5],
	(const GBaseWindowProperty*) &pGButtonpProperty[0],
	(const GBaseWindowProperty*) &pGNCDataTextBoxpProperty[0],
	(const GBaseWindowProperty*) &pGPicturepProperty[0],
	(const GBaseWindowProperty*) &pGBasicControlpProperty[0]
};


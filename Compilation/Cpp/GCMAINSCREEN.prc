
GCClassCBMP(GCMAINSCREEN)
	GCDefCBMsg(GM_CB_ONKEYPRESS, DATA, DATAOnKeyPress )
	GCDefCBMsg(GM_CB_ONTIMER, DATA, DATAOnTimer )
	GCDefCBMsg(GM_CB_ONCREATE, DATA, DATAOnCreate )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONIOLIST, BUTTONIOLISTOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONINITIAL, BUTTONINITIALOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, MTB_SCREEN, MTB_SCREENOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONGCODE, BUTTONGCODEOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONMCODE, BUTTONMCODEOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONALARM, BUTTONALARMOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONLACHRELAY, BUTTONLACHRELAYOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BUTTONPREVNT, BUTTONPREVNTOnClick )
GCEndClassCBMP()

static const GFocusInformation pGPicture00029FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONIOLISTFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONINITIALFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00002FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pMTB_SCREENFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONGCODEFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONMCODEFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONALARMFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONLACHRELAYFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00008FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBUTTONPREVNTFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00030FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pDATAFocusInformation =
{
	0,
	NULL
};


static const GBasicControlProperty pGBasicControlpProperty[1] =
{

	{{{GBASICCONTROL, GCMAINSCREEN::DATA, 572, 375, 63, 57, GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pDATAFocusInformation}}}
};
static const GButtonProperty pGButtonpProperty[10] =
{

	{{{GBUTTON, GCMAINSCREEN::BUTTONIOLIST, 64, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONIOLISTFocusInformation}}, ID_STRING00081,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONINITIAL, 384, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONINITIALFocusInformation}}, ID_STRING00095,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::GBUTTON00002, 512, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00002FocusInformation}}, ID_STRING00879,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::MTB_SCREEN, 448, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pMTB_SCREENFocusInformation}}, ID_STRING00134,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONGCODE, 320, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONGCODEFocusInformation}}, ID_STRING00085,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONMCODE, 256, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONMCODEFocusInformation}}, ID_STRING00084,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONALARM, 192, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONALARMFocusInformation}}, ID_STRING00083,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONLACHRELAY, 128, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONLACHRELAYFocusInformation}}, ID_STRING00100,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::GBUTTON00008, 576, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00008FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMAINSCREEN::BUTTONPREVNT, 0, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBUTTONPREVNTFocusInformation}}, ID_STRING00088,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GLabelProperty pGLabelpProperty[1] =
{

	{{{GLABEL, GCMAINSCREEN::GLABEL00030, 50, 339, 540, 36, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00030FocusInformation}}, ID_STRING00103,{RGB32(0,0,147), GCAPTION_POS_RIGHT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00102,{GCSCROLL_SCROLL_ENABLE, GCSCROLL_REPEAT_SCROLL, 0, 10, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GDesign pGPicture00029Design[1] = {
	{{ FILL_BACK_COLOR , RGB32(192,192,192), RGB32(192,192,192)} , ID_IMAGE00002}
};

static const GVector pGPicture00029Vector[1] = {
	{0 , 0, 1, 10000, 100}
};

static const GPicturePropertyEx pGPicturepProperty[1] =
{

	{{{{GPICTURE, GCMAINSCREEN::GPICTURE00029, 0, 0, 640, 439, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGPicture00029FocusInformation}}, 0,{RGB32(0,0,0), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0, GPCTR_DISP_IMAGE, 1, (GDesign*)pGPicture00029Design,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}, (GVector*)pGPicture00029Vector, GPCTR_EFFECT_NONE, GPCTR_EFFECT_NONE, 100, 0}
};

static GPropertyInfo pGPropertyInfo[14] =
{
	{NULL, {0, 0}},
	{(void *)&pGButtonpProperty[0], {4, 136}},
	{(void *)&pGButtonpProperty[1], {4, 136}},
	{(void *)&pGButtonpProperty[2], {4, 136}},
	{(void *)&pGButtonpProperty[3], {4, 136}},
	{(void *)&pGButtonpProperty[4], {4, 136}},
	{(void *)&pGButtonpProperty[5], {4, 136}},
	{(void *)&pGButtonpProperty[6], {4, 136}},
	{(void *)&pGButtonpProperty[7], {4, 136}},
	{(void *)&pGButtonpProperty[8], {4, 136}},
	{(void *)&pGButtonpProperty[9], {4, 136}},
	{(void *)&pGBasicControlpProperty[0], {4, 20}},
	{(void *)&pGPicturepProperty[0], {4, 90}},
	{(void *)&pGLabelpProperty[0], {4, 68}},
};

static const GBaseWindowProperty *pProperty[14] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGPicturepProperty[0],
	(const GBaseWindowProperty*) &pGButtonpProperty[0],
	(const GBaseWindowProperty*) &pGButtonpProperty[1],
	(const GBaseWindowProperty*) &pGButtonpProperty[2],
	(const GBaseWindowProperty*) &pGButtonpProperty[3],
	(const GBaseWindowProperty*) &pGButtonpProperty[4],
	(const GBaseWindowProperty*) &pGButtonpProperty[5],
	(const GBaseWindowProperty*) &pGButtonpProperty[6],
	(const GBaseWindowProperty*) &pGButtonpProperty[7],
	(const GBaseWindowProperty*) &pGButtonpProperty[8],
	(const GBaseWindowProperty*) &pGButtonpProperty[9],
	(const GBaseWindowProperty*) &pGLabelpProperty[0],
	(const GBaseWindowProperty*) &pGBasicControlpProperty[0]
};


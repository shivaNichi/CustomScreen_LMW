
GCClassCBMP(GCMTB_PASSWORD)
	GCDefCBMsg(GM_CB_ONCLICK, BTNSYSINFO, BTNSYSINFOOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BTNMAIN, BTNMAINOnClick )
	GCDefCBMsg(GM_CB_ONCLICK, BTN_PASSWORD, BTN_PASSWORDOnClick )
	GCDefCBMsg(GM_CB_ONKEYPRESS, DATA, DATAOnKeyPress )
	GCDefCBMsg(GM_CB_ONTIMER, DATA, DATAOnTimer )
	GCDefCBMsg(GM_CB_ONCREATE, DATA, DATAOnCreate )
GCEndClassCBMP()

static const GFocusInformation pBTNSYSINFOFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00001FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00002FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00003FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00004FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00005FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00006FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00007FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGButton00008FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBTNMAINFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00021FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pBTN_PASSWORDFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pMSGBOXFocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pDATAFocusInformation =
{
	0,
	NULL
};


static const GButtonProperty pGButtonpProperty[11] =
{

	{{{GBUTTON, GCMTB_PASSWORD::BTNSYSINFO, 1, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBTNSYSINFOFocusInformation}}, ID_STRING00144,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00001, 321, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00001FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00002, 449, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00002FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00003, 385, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00003FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00004, 257, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00004FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00005, 193, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00005FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00006, 129, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00006FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00007, 65, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00007FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::GBUTTON00008, 513, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGButton00008FocusInformation}}, 0,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::BTNMAIN, 577, 440, 64, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBTNMAINFocusInformation}}, ID_STRING00879,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{NO_DRAW, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00057},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_IMAGE, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}} ,
	{{{GBUTTON, GCMTB_PASSWORD::BTN_PASSWORD, 190, 301, 280, 39, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pBTN_PASSWORDFocusInformation}}, ID_STRING00142,{RGB32(255,255,255), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, ID_BORDER00064,{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(255,255,255)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(0,64,128)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001},{{FILL_BACK_COLOR, RGB32(192,192,192), RGB32(192,192,192)}, ID_IMAGE00001}, GBTN_ACT_MOMENTARY, GBTN_DISP_RECT, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GInputBoxProperty pGInputBoxpProperty[1] =
{

	{{{GINPUTBOX, GCMTB_PASSWORD::DATA, 220, 200, 200, 30, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE | GTEXT_STYLE_PASSWORD, (GFocusInformation*)&pDATAFocusInformation}}, ID_FONT00000, ID_BORDER00003, RGB32(255,255,255), RGB32(0,0,0), RGB32(255,255,255), RGB32(0,0,0), RGB32(192,192,192), 256, FILL_BACK_COLOR, GFOCUS_EFFECT_CURSOR, GCURSOR_TYPE_NORMAL, RGB32(0,0,0), 0, 0, 0, 0, RGB32(99,107,222), RGB32(255,255,255), 0,{RGB32(0,0,0), GCAPTION_POS_RIGHT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
static const GLabelProperty pGLabelpProperty[1] =
{

	{{{GLABEL, GCMTB_PASSWORD::GLABEL00021, 0, 134, 640, 40, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00021FocusInformation}}, ID_STRING00105,{RGB32(0,0,0), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(0,0,0)}}
};
static const GTextBoxProperty pGTextBoxpProperty[1] =
{

	{{{GTEXTBOX, GCMTB_PASSWORD::MSGBOX, 3, 413, 360, 25, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pMSGBOXFocusInformation}}, ID_STRING00048,{RGB32(255,0,0), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0, RGB32(255,255,255), RGB32(255,255,255), RGB32(192,192,192), GTEXT_TYPE_STRING, 256,{0},{0}, NO_DRAW, GFOCUS_EFFECT_NON,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_ENABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};

static GPropertyInfo pGPropertyInfo[15] =
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
	{(void *)&pGLabelpProperty[0], {4, 68}},
	{(void *)&pGInputBoxpProperty[0], {4, 112}},
	{(void *)&pGButtonpProperty[10], {4, 136}},
	{(void *)&pGTextBoxpProperty[0], {4, 100}},
};

static const GBaseWindowProperty *pProperty[15] =
{
	(const GBaseWindowProperty*) NULL,
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
	(const GBaseWindowProperty*) &pGButtonpProperty[10],
	(const GBaseWindowProperty*) &pGTextBoxpProperty[0],
	(const GBaseWindowProperty*) &pGInputBoxpProperty[0]
};


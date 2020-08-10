
GCClassCBMP(GCLockWindow)
	GCDefCBMsg(GM_CB_ONKEYPRESS, KEYACTION, KEYACTIONOnKeyPress )
	GCDefCBMsg(GM_CB_ONCREATE, KEYACTION, KEYACTIONOnCreate )
GCEndClassCBMP()

static const GFocusInformation pGLabel00000FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pKeyActionFocusInformation =
{
	0,
	NULL
};


static const GBasicControlProperty pGBasicControlpProperty[1] =
{

	{{{GBASICCONTROL, GCLockWindow::KEYACTION, 226, 10, 31, 19, GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pKeyActionFocusInformation}}}
};
static const GLabelProperty pGLabelpProperty[1] =
{

	{{{GLABEL, GCLockWindow::GLABEL00000, 2, 3, 345, 29, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00000FocusInformation}}, ID_STRING00376,{RGB32(0,0,0), GCAPTION_POS_LEFT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};

static GPropertyInfo pGPropertyInfo[3] =
{
	{NULL, {0, 0}},
	{(void *)&pGLabelpProperty[0], {4, 68}},
	{(void *)&pGBasicControlpProperty[0], {4, 20}},
};

static const GBaseWindowProperty *pProperty[3] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGLabelpProperty[0],
	(const GBaseWindowProperty*) &pGBasicControlpProperty[0]
};


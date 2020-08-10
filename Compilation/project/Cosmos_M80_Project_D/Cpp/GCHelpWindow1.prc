
GCClassCBMP(GCHelpWindow1)
	GCDefCBMsg(GM_CB_ONKEYPRESS, KEYACTION, KEYACTIONOnKeyPress )
	GCDefCBMsg(GM_CB_ONTIMER, KEYACTION, KEYACTIONOnTimer )
	GCDefCBMsg(GM_CB_ONCREATE, KEYACTION, KEYACTIONOnCreate )
GCEndClassCBMP()

static const GFocusInformation pHelpFrameFocusInformation =
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

	{{{GBASICCONTROL, GCHelpWindow1::KEYACTION, 604, 326, 35, 23, GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pKeyActionFocusInformation}}}
};
static const GSVFramePropertyEx pGHelpFramepProperty[1] =
{

	{{{{{GHELPWINDOW1HELPFRAME, GCHelpWindow1::HELPFRAME, 18, 9, 597, 390, GW_STYLE_ENABLE|GW_STYLE_VISIBLE, (GFocusInformation*)&pHelpFrameFocusInformation},{{NO_DRAW, 0, 0}, 0}, 100, 100}}}}
};

static GPropertyInfo pGPropertyInfo[3] =
{
	{NULL, {0, 0}},
	{(void *)&pGBasicControlpProperty[0], {4, 20}},
	{(void *)&pGHelpFramepProperty[0], {4, 44}},
};

static const GBaseWindowProperty *pProperty[3] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGHelpFramepProperty[0],
	(const GBaseWindowProperty*) &pGBasicControlpProperty[0]
};


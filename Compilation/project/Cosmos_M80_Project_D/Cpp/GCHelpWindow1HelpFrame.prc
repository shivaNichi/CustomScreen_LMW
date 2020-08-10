
static const GPanelPropertyEx pGPanelProperty[] =
{
	{{{GHELPWINDOW1HELPFRAMEPANEL000,GCHelpWindow1HelpFrame::PANEL000,0,0,597,390,GW_STYLE_ENABLE,NULL},{{NO_DRAW,RGB32(128,128,128),RGB32(128,128,128)},0},100,100}},
	{{{GHELPWINDOW1HELPFRAMEPANEL001,GCHelpWindow1HelpFrame::PANEL001,0,0,597,390,GW_STYLE_ENABLE,NULL},{{NO_DRAW,RGB32(128,128,128),RGB32(128,128,128)},0},100,100}},
};

static GPropertyInfo pGPanelPropertyInfo[] =
{
	{NULL, {0, 0}},
	{(void *)&pGPanelProperty[0], {4, 44}},
	{(void *)&pGPanelProperty[1], {4, 44}},
};

static const GBaseWindowProperty *pProperty[] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGPanelProperty[0],
	(const GBaseWindowProperty*) &pGPanelProperty[1],
};


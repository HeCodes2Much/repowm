/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 3;		  /* border pixel of windows */
static const unsigned int snap = 32;		  /* snap pixel */
static const unsigned int startmenusize = 30;		  /* snap pixel */
static const unsigned int systraypinning = 0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;			  /* 0 means no systray */
static const int showbar = 1;				  /* 0 means no bar */
static const int topbar = 1;				  /* 0 means bottom bar */
static const char *fonts[] = {"Cantarell-Regular:size=12", "Fira Code Nerd Font:size=12"};

static int barheight;
static char xresourcesfont[30];

// empty background
static char col_background[] = "#292f3a"; /* top bar dark background*/
// fonts
static char col_white[] = "#ffffff";/*white for fonts*/

// border active and inactive
static char col_pastel_blue[] = "#747c90";/*unsaturated for focused border*/
static char col_light_blue[] = "#4dadd4";/*focused windows d */

// blue window indicator
static char col_blue[] = "#5294E2";/*focused instamenu or topbar d */
static char col_dark_blue[] = "#3579CB";/*focused instamenu or topbar d */

// hover over blue window indicator
static char col_hover_blue[] = "#7CA8DC";/*focused instamenu or topbar d */
static char col_hover_dark_blue[] = "#578BC9";/*focused instamenu or topbar d */

// sticky window indicator
static char col_green[] = "#52E167";/*focused instamenu or topbar d */
static char col_dark_green[] = "#35CB4B";/*focused instamenu or topbar d */

// unfocused sticky indicator
static char col_orange[] = "#E1A052";/*focused instamenu or topbar d */
static char col_dark_orange[] = "#CB8735";/*focused instamenu or topbar d */

// close button
static char col_red[] = "#E1527E";/*focused instamenu or topbar d */
static char col_dark_red[] = "#CB3563";/*focused instamenu or topbar d */

// hover over close button
static char col_hover_red[] = "#D37492";/*focused instamenu or topbar d */
static char col_hover_dark_red[] = "#CE577C";/*focused instamenu or topbar d */

// hover over empty tag
static char col_hover[] = "#596377";/*focused instamenu or topbar d */
static char col_hover_shadow[] = "#475166";/*focused instamenu or topbar d */

static const char *colors[][4] = {
	/*                    fg               bg              border 	           float*/
	[SchemeNorm]      = { col_white,       col_background, col_pastel_blue,    col_green },
	[SchemeSel]       = { col_white,       col_blue,       col_light_blue,     col_green },
	[SchemeHid]       = { col_pastel_blue, col_background, col_pastel_blue,    col_green },
	[SchemeTags]      = { col_white,       col_blue,       col_light_blue,     col_dark_blue },
	[SchemeActive]    = { col_white,       col_green,      col_light_blue,     col_dark_green },
	[SchemeAddActive] = { col_white,       col_orange,     col_light_blue,     col_dark_orange },
	[SchemeEmpty]     = { col_white,       col_red,        col_light_blue,     col_dark_red },
	[SchemeHover]     = { col_white,       col_hover,      col_light_blue,     col_hover_shadow },
	[SchemeClose]     = { col_hover_red,   col_red,        col_hover_dark_red, col_dark_red },
	[SchemeHoverTags] = { col_white,       col_hover_blue, col_light_blue,     col_hover_dark_blue },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "s" };
/* ffox, programming1, term, music, steam, folder, play icon, document, message  */
static const char *tagsalt[] = { "", "{}", "$", "", "", "", "", "", "" };

static const char *upvol[] = {"/usr/share/instantassist/utils/p.sh", "+", NULL};
static const char *downvol[] = {"/usr/share/instantassist/utils/p.sh", "-", NULL};
static const char *mutevol[] = {"/usr/share/instantassist/utils/p.sh", "m", NULL};

static const char *upbright[] = {"/usr/share/instantassist/utils/b.sh", "+", NULL};
static const char *downbright[] = {"/usr/share/instantassist/utils/b.sh", "-", NULL};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance  title  tags mask  isfloating  monitor */
	{"Pavucontrol",                 NULL,     NULL,  0,         1,          -1},
	{"Onboard",                     NULL,     NULL,  0,         1,          -1},
	{"Pamac-installer",             NULL,     NULL,  0,         1,          -1},
};

/* layout(s) */
static const float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;	 /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "+",        tile },    /* first entry is default */
	{ "#",        grid },
	{ "-",        NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      tcl },
	{ "H[]",      deck },
	{ "O",        overviewlayout },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                          \
		{MODKEY, KEY, view, {.ui = 1 << TAG}},                     \
		{MODKEY|ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
		{MODKEY|ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
		{MODKEY|Mod1Mask, KEY, followtag, {.ui = 1 << TAG}},          \
		{MODKEY|ControlMask|ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},


#define SHCMD(cmd)                                           \
	{                                                        \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
	}

/* commands */
static char instamenumon[2] = "0"; /* component of instamenucmd, manipulated in spawn() */
static const char *instamenucmd[] = {"instamenu_run", NULL};
static const char *clipmenucmd[] = {".config/instamenu/scripts/instant-clip-menu.sh", NULL};
static const char *smartcmd[] = {"instamenue_smartrun", NULL};


static const char *terminalcmd[] = {".config/instantos/default/terminal", NULL};
static const char *browsercmd[] = { ".config/instantos/default/browser", NULL };
static const char *editorcmd[] = { ".config/instantos/default/editor", NULL };
static const char *filemanagercmd[] = {".config/instantos/default/filemanager", NULL};
static const char *systemmonitorcmd[] = {".config/instantos/default/systemmonitor", NULL};

static const char *instasettings[] = { "instantsettings", NULL};

static const char *playernext[] = { "playerctl", "next", NULL};
static const char *playerprevious[] = { "playerctl", "previous", NULL};
static const char *playerpause[] = { "playerctl", "play-pause", NULL};

#include "push.c"

ResourcePref resources[] = {

		{ "bgcolor",          STRING,  &col_background },
		{ "hoverbgcolor",     STRING,  &col_hover },
		{ "hovershadowcolor", STRING,  &col_hover_shadow },

		{ "fontcolor",        STRING,  &col_white },

		{ "minimize",         STRING,  &col_orange },
		{ "darkminimize",     STRING,  &col_dark_orange },

		{ "border",           STRING,  &col_pastel_blue },
		{ "activeborder",     STRING,  &col_light_blue },

		{ "activetag",        STRING,  &col_green },
		{ "darkactivetag",    STRING,  &col_dark_green },

		{ "close",            STRING,  &col_red },
		{ "darkclose",        STRING,  &col_dark_red },
		{ "hoverclose",       STRING,  &col_hover_red },
		{ "darkhoverclose",   STRING,  &col_hover_dark_red },

		{ "focus",            STRING,  &col_blue },
		{ "darkfocus",        STRING,  &col_dark_blue },
		{ "hoverfocus",       STRING,  &col_hover_blue },
		{ "darkhoverfocus",   STRING,  &col_hover_dark_blue },

		{ "barheight",        INTEGER, &barheight },
		{ "font",             STRING,  &xresourcesfont },

};

static Xcommand commands[] = {
	/* signum       function        default argument  arg handler*/
    // 0 means off, 1 means toggle, 2 means on
	{ "overlay",                setoverlay,                   {0},         0 },
	{ "tag",                    view,                         { .ui = 2 }, 3 },
	{ "animated",               toggleanimated,               { .ui = 2 }, 1 },
    { "focusfollowsmouse",      togglefocusfollowsmouse,      { .ui = 2 }, 1 },
    { "focusfollowsfloatmouse", togglefocusfollowsfloatmouse, { .ui = 2 }, 1 },
	{ "alttab",                 alttabfree,                   { .ui = 2 }, 1 },
	{ "layout",                 commandlayout,                { .ui = 0 }, 1 },
	{ "prefix",                 commandprefix,                { .ui = 1 }, 1 },
	{ "alttag",                 togglealttag,                 { .ui = 0 }, 1 },
	{ "hidetags",               toggleshowtags,               { .ui = 0 }, 1 },
	{ "specialnext",            setspecialnext,               { .ui = 0 }, 3 },
};

static Key dkeys[] = {
	/* modifier  key        function     argument */
	{0,          XK_e,      spawn,       {.v = editorcmd } },
	{0,          XK_n,      spawn,       {.v = filemanagercmd } },
	{0,          XK_f,      spawn,       {.v = browsercmd} },
	{0,          XK_Return, spawn,       {.v = terminalcmd} },
	{0,          XK_plus,   spawn,       {.v = upvol} },
	{0,          XK_minus,  spawn,       {.v = downvol} },
	{0,          XK_y,      spawn,       {.v = smartcmd} },

	{0,          XK_h,      viewtoleft,  {0}},
	{0,          XK_l,      viewtoright, {0}},
	{0,          XK_k,      shiftview,   {.i = +1 } },
	{0,          XK_j,      shiftview,   {.i = -1 } },

	{0,          XK_Left,   viewtoleft,  {0}},
	{0,          XK_Right,  viewtoright, {0}},
	{0,          XK_Up,     shiftview,   {.i = +1 } },
	{0,          XK_Down,   shiftview,   {.i = -1 } },

	{0,          XK_1,      view,        {.ui = 1 << 0}},
	{0,          XK_2,      view,        {.ui = 1 << 1}},
	{0,          XK_3,      view,        {.ui = 1 << 2}},
	{0,          XK_4,      view,        {.ui = 1 << 3}},
	{0,          XK_5,      view,        {.ui = 1 << 4}},
	{0,          XK_6,      view,        {.ui = 1 << 5}},
	{0,          XK_7,      view,        {.ui = 1 << 6}},
	{0,          XK_8,      view,        {.ui = 1 << 7}},
	{0,          XK_9,      view,        {.ui = 1 << 8}},

};

static Key keys[] = {
	/* modifier                             key                 function              argument */

	{MODKEY|Mod1Mask,                       XK_j,               keyresize,            {.i = 0}},
	{MODKEY|Mod1Mask,                       XK_k,               keyresize,            {.i = 1}},
	{MODKEY|Mod1Mask,                       XK_l,               keyresize,            {.i = 2}},
	{MODKEY|Mod1Mask,                       XK_h,               keyresize,            {.i = 3}},
	{MODKEY|ControlMask,                    XK_d,               distributeclients,    {0}},
	{MODKEY|ShiftMask,                      XK_d,               drawwindow,           {0}},
	{MODKEY|ShiftMask,                      XK_Escape,          spawn,                {.v = systemmonitorcmd}},

	{MODKEY|ControlMask|Mod1Mask,           XK_r,               redrawwin,            {0} },
	{MODKEY,                                XK_n,               spawn,                {.v = filemanagercmd } },
	{MODKEY,                                XK_w,               setoverlay,           {0} },
	{MODKEY|ControlMask,                    XK_w,               createoverlay,        {0} },
	{MODKEY|ControlMask,                    XK_space,           spawn,                {.v = instamenucmd}},
	{MODKEY|ShiftMask,                      XK_v,               spawn,                {.v = clipmenucmd}},
	{MODKEY,                                XK_space,           spawn,                {.v = smartcmd}},
	{MODKEY|Mod1Mask|ControlMask|ShiftMask, XK_Tab,             alttabfree,           {0}},
	{MODKEY|ControlMask,                    XK_h,               hidewin,              {0}},
	{MODKEY|Mod1Mask|ControlMask,           XK_h,               unhideall,            {0}},
	{MODKEY,                                XK_Return,          spawn,                {.v = terminalcmd}},
	{MODKEY,                                XK_b,               togglebar,            {0}},
	{MODKEY,                                XK_j,               focusstack,           {.i = +1}},
	{MODKEY,                                XK_Down,            downkey,              {.i = +1}},
	{MODKEY|ShiftMask,                      XK_Down,            downpress,            {0}},
	{MODKEY,                                XK_k,               focusstack,           {.i = -1}},
	{MODKEY,                                XK_Up,              upkey,                {.i = -1}},
	{MODKEY|ShiftMask,                      XK_Up,              uppress,              {0}},
	{MODKEY|ControlMask,                    XK_j,               pushdown,             {0} },
	{MODKEY|ControlMask,                    XK_k,               pushup,               {0} },
	{MODKEY|Mod1Mask,                       XK_s,               togglealttag,         { .ui = 2 } },
	{MODKEY|ShiftMask|Mod1Mask,             XK_s,               toggleanimated,       { .ui = 2 } },
	{MODKEY|ControlMask,                    XK_s,               togglesticky,         {0} },
	{MODKEY|ShiftMask,                      XK_s,               createscratchpad,     {0}},
	{MODKEY,                                XK_s,               togglescratchpad,     {0}},
	{MODKEY|ShiftMask,                      XK_f,               togglefakefullscreen, {0} },
	{MODKEY|ControlMask,                    XK_f,               tempfullscreen,       {0} },
	{MODKEY|ShiftMask|Mod1Mask,             XK_d,               toggledoubledraw,     {0} },
	{MODKEY|ShiftMask,                      XK_w,               warpfocus,            {0} },
	{MODKEY|Mod1Mask,                       XK_w,               centerwindow,         {0} },
	{MODKEY|ShiftMask|ControlMask,          XK_s,               toggleshowtags,       { .ui = 2 } },
	{MODKEY,                                XK_i,               incnmaster,           {.i = +1}},
	{MODKEY,                                XK_d,               incnmaster,           {.i = -1}},
	{MODKEY,                                XK_h,               setmfact,             {.f = -0.05}},
	{MODKEY,                                XK_l,               setmfact,             {.f = +0.05}},
	{MODKEY|ShiftMask,                      XK_Return,          zoom,                 {0}},
	{MODKEY,                                XK_Tab,             lastview,             {0}},
	{MODKEY|ShiftMask,                      XK_Tab,             focuslastclient,      {0}},
	{MODKEY|Mod1Mask,                       XK_Tab,             followview,           {0}},
	{Mod1Mask,                              XK_F4,              killclient,           {0}},
	{MODKEY,                                XK_F2,              toggleprefix,         {0}},
	{MODKEY,                                XK_t,               setlayout,            {.v = &layouts[0]}},
	{MODKEY,                                XK_f,               setlayout,            {.v = &layouts[2]}},
	{MODKEY,                                XK_m,               setlayout,            {.v = &layouts[3]}},
	{MODKEY|ShiftMask,                      XK_m,               movemouse,            {0}},
	{MODKEY|Mod1Mask,                       XK_m,               resizemouse,          {0}},
	{MODKEY,                                XK_c,               setlayout,            {.v = &layouts[1]}},

	{MODKEY,                                XK_Left,            animleft,             {0}},
	{MODKEY,                                XK_Right,           animright,            {0}},

	{MODKEY,                                XK_e,               overtoggle,           {.ui = ~0}},
	{MODKEY|ShiftMask,                      XK_e,               fullovertoggle,       {.ui = ~0}},

	{MODKEY|ControlMask,                    XK_Left,            directionfocus,            {.ui = 3 }},
	{MODKEY|ControlMask,                    XK_Right,           directionfocus,            {.ui = 1 }},
	{MODKEY|ControlMask,                    XK_Up,              directionfocus,            {.ui = 0 }},
	{MODKEY|ControlMask,                    XK_Down,            directionfocus,            {.ui = 2 }},

	{MODKEY|ShiftMask|ControlMask,                    XK_Right,           shiftview,            {.i = +1 }},
	{MODKEY|ShiftMask|ControlMask,                    XK_Left,           shiftview,            {.i = -1 }},

	{MODKEY|Mod1Mask,                       XK_Left,            moveleft,             {0}},
	{MODKEY|Mod1Mask,                       XK_Right,           moveright,            {0}},

	{MODKEY|ShiftMask,                      XK_Left,            tagtoleft,            {0}},
	{MODKEY|ShiftMask,                      XK_Right,           tagtoright,           {0}},

	{MODKEY|ShiftMask,                      XK_j,               moveresize,           {.i = 0}},
	{MODKEY|ShiftMask,                      XK_k,               moveresize,           {.i = 1}},
	{MODKEY|ShiftMask,                      XK_l,               moveresize,           {.i = 2}},
	{MODKEY|ShiftMask,                      XK_h,               moveresize,           {.i = 3}},


	{MODKEY|ControlMask,                    XK_comma,           cyclelayout,          {.i = -1 } },
	{MODKEY|ControlMask,                    XK_period,          cyclelayout,          {.i = +1 } },
	{MODKEY,                                XK_p,               setlayout,            {0}},
	{MODKEY|ShiftMask,                      XK_space,           spacetoggle,          {0}},
	{MODKEY,                                XK_0,               view,                 {.ui = ~0}},
	{MODKEY|ShiftMask,                      XK_0,               tag,                  {.ui = ~0}},
	{MODKEY,                                XK_comma,           focusmon,             {.i = -1}},
	{MODKEY,                                XK_period,          focusmon,             {.i = +1}},
	{MODKEY|ShiftMask,                      XK_comma,           tagmon,               {.i = -1}},
	{MODKEY|ShiftMask,                      XK_period,          tagmon,               {.i = +1}},
	{MODKEY|Mod1Mask,                       XK_comma,           followmon,            {.i = -1}},
	{MODKEY|Mod1Mask,                       XK_period,                       followmon,  {.i = +1}},

	{MODKEY|ShiftMask|ControlMask|Mod1Mask, XK_period,                       desktopset, {0}},
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
    {MODKEY|ShiftMask|ControlMask, XK_q,                     quit,    {0}},
	{0,                            XF86XK_MonBrightnessUp,   spawn,   {.v = upbright}},
	{0,                            XF86XK_MonBrightnessDown, spawn,   {.v = downbright}},
	{0,                            XF86XK_AudioLowerVolume,  spawn,   {.v = downvol}},
	{0,                            XF86XK_AudioMute,         spawn,   {.v = mutevol}},
	{0,                            XF86XK_AudioRaiseVolume,  spawn,   {.v = upvol}},
	{0,                            XF86XK_AudioPlay,         spawn,   {.v = playerpause}},
	{0,                            XF86XK_AudioPause,        spawn,   {.v = playerpause}},
	{0,                            XF86XK_AudioNext,         spawn,   {.v = playernext}},
	{0,                            XF86XK_AudioPrev,         spawn,   {.v = playerprevious}},

	// {MODKEY|ShiftMask,             XK_Print,                 spawn,   {.v = fscrotcmd}},
	// {MODKEY,                       XK_Print,                 spawn,   {.v = scrotcmd}},
	// {MODKEY|ControlMask,           XK_Print,                 spawn,   {.v = clipscrotcmd}},
	// {MODKEY|Mod1Mask,              XK_Print,                 spawn,   {.v = fclipscrotcmd}},

	{ MODKEY,                      XK_o,                     winview, {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click          event mask          button   function           argument */
	{ ClkLtSymbol,    0,                  Button1, cyclelayout,       {.i = -1 } },
	{ ClkLtSymbol,    0,                  Button3, cyclelayout,       {.i = +1 } },
	{ ClkLtSymbol,    MODKEY,             Button1, createoverlay,     {0} },
	{ ClkLtSymbol,    0,                  Button2, setlayout,         {.v = &layouts[0]} },
	{ ClkWinTitle,    0,                  Button1, dragmouse,         {0} },
	{ ClkWinTitle,    MODKEY,             Button1, setoverlay,        {0} },
	{ ClkWinTitle,    0,                  Button2, closewin,          {0} },
	{ ClkCloseButton, 0,                  Button1, killclient,        {0} },
	{ ClkCloseButton, 0,                  Button3, togglelocked,      {0} },
	{ ClkWinTitle,    0,                  Button3, dragrightmouse,    {0} },
	{ ClkWinTitle,    0,                  Button5, focusstack,        {.i = +1} },
	{ ClkWinTitle,    0,                  Button4, focusstack,        {.i = -1} },
	{ ClkWinTitle,    ShiftMask,          Button5, pushdown,          {0} },
	{ ClkWinTitle,    ShiftMask,          Button4, pushup,            {0} },
	{ ClkWinTitle,    ControlMask,        Button5, downscaleclient,   {0} },
	{ ClkWinTitle,    ControlMask,        Button4, upscaleclient,     {0} },
	{ ClkStatusText,  0,                  Button2, spawn,             {.v = terminalcmd } },
	{ ClkStatusText,  0,                  Button4, spawn,             {.v = upvol } },
	{ ClkStatusText,  0,                  Button5, spawn,             {.v = downvol } },
	{ ClkStatusText,  MODKEY,             Button2, spawn,             {.v = mutevol } },
	{ ClkStatusText,  MODKEY,             Button1, spawn,             {.v = instasettings } },
	{ ClkStatusText,  MODKEY,             Button4, spawn,             {.v = upbright } },
	{ ClkStatusText,  MODKEY,             Button5, spawn,             {.v = downbright } },
	{ ClkRootWin,     MODKEY,             Button1, setoverlay,        {0} },
	{ ClkRootWin,     0,                  Button3, spawn,             {.v = smartcmd } },
	{ ClkRootWin,     0,                  Button5, showoverlay,       {0} },
	{ ClkRootWin,     0,                  Button4, hideoverlay,       {0} },
	{ ClkClientWin,   MODKEY,             Button1, movemouse,         {0} },
	{ ClkClientWin,   MODKEY,             Button2, togglefloating,    {0} },
	{ ClkClientWin,   MODKEY,             Button3, resizemouse,       {0} },
	{ ClkClientWin,   MODKEY|Mod1Mask,    Button3, forceresizemouse,  {0} },
	{ ClkClientWin,   MODKEY|ShiftMask,   Button3, resizeaspectmouse, {0} },
	{ ClkTagBar,      0,                  Button1, dragtag,           {0} },
	{ ClkTagBar,      0,                  Button5, viewtoright,       {0} },
	{ ClkTagBar,      MODKEY,             Button4, shiftview,         {.i = -1 } },
	{ ClkTagBar,      MODKEY,             Button5, shiftview,         {.i = +1 } },
	{ ClkTagBar,      0,                  Button4, viewtoleft,        {0} },
	{ ClkTagBar,      0,                  Button3, toggleview,        {0} },
	{ ClkTagBar,      MODKEY,             Button1, tag,               {0} },
	{ ClkTagBar,      Mod1Mask,           Button1, followtag,         {0} },
	{ ClkTagBar,      MODKEY,             Button3, toggletag,         {0} },
	{ ClkSideBar,     0,                  Button1, gesturemouse,      {0} },
	{ ClkStartMenu,   ShiftMask,          Button1, toggleprefix,      {0}},
};

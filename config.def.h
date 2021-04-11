/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int useinstabar 		= 1;  		/* 0 means don't use instabar script */
static const char *fonts[] = {
    "Misc Termsyn:size=12",
    "Cantarell-Regular:size=12",
    "FiraCode Nerd Font:size=14",
    "Siji:size=14",
    "JoyPixels:pixelsize=20:antialias=true:autohint=true",
    "MaterialIcons:size=10",
    "xos4 Terminus:size=12"};


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
};

/* tagging */
static const char *tags[] = { " 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: VirtualBox", " 9: Chat" , " 10: Settings" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance  		title  			tags mask  		isfloating  	monitor */
	{ "Pavucontrol",                NULL,     		NULL,  			0,         		1,          	-1},
	{ "Onboard",                    NULL,     		NULL,  			0,         		1,          	-1},
	{ "Pamac-installer",            NULL,     		NULL,  			0,         		1,          	-1},
	{ "floatmenu",		            NULL,     		NULL,  			0,         		1,          	-1},
	{ "Firefox",					NULL,     		NULL,  			1,         		0,          	-1},
	{ "Chromium-browser",			NULL,	  		NULL,  			1,         		0,				-1},
	{ "Brave-browser",				NULL,	  		NULL,  			1,         		0,				-1},
	{ "dissenter-browser",			NULL,	  		NULL,  			1,         		0,				-1},
	{ "Waterfox",					NULL,     		NULL,	 		1,         		0,				-1},
	//
	{ "Dragon",						NULL,     		NULL,  			0,         		1,        		-1},
	{ "St",							NULL,     		NULL,  			  0,      		0,        		-1},
	{ "Pcmanfm",					NULL,     		NULL,  			1 << 2,    		0,        		-1},
	// Development
	{ "Subl",						NULL,     		NULL, 			1 << 3,    		0,        		-1},
	// Messaging
	{ "walc",						NULL,     		NULL, 			1 << 4,    		0, 				-1},
	{ "TelegramDesktop",			NULL,			NULL, 			1 << 4,    		0, 				-1},
	{ "Element",					NULL,     		NULL, 			1 << 4,    		0, 				-1},
	{ "discord",					NULL,     		NULL, 			1 << 4,    		0, 				-1},
	{ "mirage",						NULL,     		NULL, 			1 << 4,    		0, 				-1},
	{ "Spectral",					NULL,     		NULL, 			1 << 4,    		0, 				-1},
	// Game
	{ "Lutris",						NULL,     		NULL, 			1 << 5,    		0, 				-1},
	// Utils
	{ "stacer",						NULL,     		NULL, 			1 << 6,    		0, 				-1},
	{ "St",							NULL,   		"htop", 		1 << 6,    		0, 				-1},
	{ "St",							NULL, 			"AlsaMixer",	1 << 6,	 		0, 				-1},
	{ "St",							NULL,   		"nmTUI",		1 << 6,    		0, 				-1},
	// Edit
	{ NULL,							"libreoffice",	NULL, 			1 << 7,    		0, 				-1}, // LibreOffice
	{ "kdenlive",					"kdenlive",		NULL, 			1 << 7,    		0, 				-1},
	{ "Gimp",						NULL,			NULL, 			1 << 8,    		1, 				-1},
	{ "Ld-linux-x86-64.so.2",		NULL,			NULL, 			1 << 8,    		1, 				-1}, // Inkscape
	//
	{ "trayer",						NULL,			NULL, 			0,         		1, 				-1},
	{ NULL,							NULL,     		"Event Tester", 0,  			1,      		-1}, /* xev */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre instawm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* instawm commands */
static char instamenumon[2] = "0"; /* component of instamenucmd, manipulated in spawn() */
static const char *instamenucmd[] = {"instamenu_run", NULL};
static const char *systemmonitorcmd[] = { "instawm-schemas", "systemmonitorcmd", NULL};
static const char *instasettings[] = { "instawm-schemas", "instasettingscmd", NULL};
static const char *startmenucmd[] = { "instawm-schemas", "startmenucmd", NULL};
static const char *clipmenucmd[] = { "instawm-schemas", "clipmenucmd", NULL};
static const char *smartcmd[] = { "instawm-schemas", "smartmenucmd", NULL};

 /* Do not remove */
static const char *powermenucmd[] = { "instawm-schemas", "powermenucmd", NULL};

/* instamenu commands */
static const char *filemanagercmd[] = { "instawm-schemas", "filemanager", NULL};
static const char *hypervisorcmd[] = { "instawm-schemas", "hypervisor", NULL};
static const char *terminalcmd[] = { "instawm-schemas", "terminal", NULL};
static const char *browsercmd[] = { "instawm-schemas", "webbrowser", NULL};
static const char *editorcmd[] = { "instawm-schemas", "texteditor", NULL};
static const char *mailcmd[] = { "instawm-schemas", "mailreader", NULL};
static const char *gitcmd[] = { "instawm-schemas", "gitbrowser", NULL};

/* genreal commands*/
static const char *playernext[] = { "playerctl", "next", NULL};
static const char *playerprevious[] = { "playerctl", "previous", NULL};
static const char *playerpause[] = { "playerctl", "play-pause", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = startmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = terminalcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminalcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


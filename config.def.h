/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  			= 1;        /* border pixel of windows */
static const unsigned int snap      			= 32;       /* snap pixel */
static const unsigned int gappih    			= 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    			= 10;       /* vert inner gap between windows */
static const unsigned int gappoh    			= 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    			= 30;       /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning 		= 0;   		/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft 		= 0;   		/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing 		= 2;   		/* systray spacing */
static const int swallowfloating    			= 0;        /* 1 means swallow floating windows by default */
static const int smartgaps          			= 0;        /* 1 means no outer gap when there is only one window */
static const int systraypinningfailfirst 		= 1;   		/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        			= 1;     	/* 0 means no systray */
static const int showbar            			= 1;        /* 0 means no bar */
static const int topbar             			= 1;        /* 0 means bottom bar */
static const int useinstabar 					= 0;  		/* 0 means don't use instabar script */
static const int user_bh            			= 28;       /* 0 means that instawm will calculate bar height, >= 1 means instawm will user_bh as bar height */
static const char *fonts[] = {
    "Misc Termsyn:size=12",
    "Siji:size=14",
    "FiraCode Nerd Font:size=14",
    "MaterialIcons:size=10",
    "xos4 Terminus:size=12"};


// instawm bar colors
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_green[] 		= "#52E167";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][4] = {
	/*               fg              	bg              	border 	           	 float*/
	[SchemeNorm] = { col_gray3, 		col_gray1, 			col_gray2, 			col_green },
	[SchemeInv]  = { col_gray1, 		col_gray3, 			col_gray2, 			col_green },
	[SchemeSel]  = { col_gray4, 		col_cyan,  			col_cyan, 			col_green },
};

static const unsigned int alphas[][3]      = {
	[SchemeNorm] = { OPAQUE, 			baralpha, 			borderalpha },
	[SchemeSel]  = { OPAQUE, 			baralpha, 			borderalpha },
};

static const char *const autostart[] = {
	"kitty", NULL,
	// "hsetroot", "-center", "/usr/home/bit6tream/pic/wallapper.png", NULL,
	// "xrdb", "/usr/home/bit6tream/.config/X/Xresources", NULL,
	// "sh", "-c", "while :; do instawmstatus.sh -; sleep 60; done", NULL,
	// "dunst", NULL,
	// "picom", NULL,
	NULL
};

/* tagging */
static const char *tags[] = { " 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: VirtualBox", " 9: Chat" , " 10: Settings" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	
	/* class     				instance  			title           	tags mask  		isfloating  	isterminal  	noswallow  		monitor */
	//Workspace 1 Monator 0
	{ "kitty", 		  			NULL,     			NULL,         		1 << 0,         0,          	1,          	-1,        		0 },
	
	//Workspace 2 Monator 0
	{ "code-oss", 		  		NULL,     			NULL,         		1 << 1,         0,          	0,          	-1,        		0 },
	{ "Emacs", 		  			NULL,     			NULL,         		1 << 1,         0,          	0,          	-1,        		0 },

	//Workspace 3 Monator 0
	{ "Nemo", 		  			NULL,     			NULL,         		1 << 2,         0,          	0,          	-1,        		0 },

	//Workspace 4 Monator 0
	{ "Ld-linux-x86-64.so.2",	NULL,    			NULL,   			1 << 3,    		1,          	0,          	-1,        		0 }, // Inkscape
	{ "Gimp",    				NULL,				NULL,         		1 << 3,    		1,          	0,          	-1,        		0 },

	//Workspace 5 Monator 0

	//Workspace 6 Monator 1
	{ "Firefox", 		  		NULL,     			NULL,         		1 << 5,        	0,          	0,          	-1,        		1 },
	{ "Vivaldi-stable",			NULL, 				NULL,         		1 << 5,        	0,          	0,          	-1,        		1 },

	//Workspace 7 Monator 1

	//Workspace 8 Monator 1
	{ "Steam",					NULL,     			NULL,         		1 << 7,    		0,          	0,          	-1,        		1 },

	//Workspace 9 Monator 1
	{ "TelegramDesktop",		NULL,   			NULL,         		1 << 8,    		0,          	0,          	-1,        		1 },
	{ "Element",				NULL,     			NULL,         		1 << 8,    		0,          	0,          	-1,        		1 },

	//Workspace 10 Monator 1
	{ NULL,      				NULL,     			"Event Tester", 	1 << 9,        	0,          	1,          	1,        		1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
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

static const char *upvol[] = {"amixer", "sset", "Master", "5%+", NULL};
static const char *downvol[] = {"amixer", "sset", "Master", "5%-", NULL};
static const char *mutevol[] = {"amixer", "sset", "Master", "toggle", NULL};

static const char *upbright[] = {"xbacklight", "+10", NULL};
static const char *downbright[] = {"xbacklight", "-10", NULL};

#include "movestack.c"
#include "selfrestart.c"
static Key keys[] = {
	/* modifier                     key        					function        		argument */
	{ MODKEY,                       XK_p,      					spawn,          		{.v = instamenucmd } },
	{ MODKEY,						XK_Return, 					spawn,          		{.v = terminalcmd } },
	{ MODKEY,                       XK_b,      					togglebar,      		{0} },
	{ MODKEY,                       XK_j,      					focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_k,      					focusstack,     		{.i = -1 } },
	{ MODKEY,                       XK_i,      					incnmaster,     		{.i = +1 } },
	{ MODKEY,                       XK_d,      					incnmaster,     		{.i = -1 } },
	{ MODKEY,                       XK_h,      					setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_l,      					setmfact,       		{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      					movestack,      		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      					movestack,      		{.i = -1 } },
	{ MODKEY,                       XK_Return, 					zoom,           		{0} },
	{ MODKEY,						XK_z,						incrgaps,				{.i = +3 } },
	{ MODKEY,						XK_x,						incrgaps,				{.i = -3 } },
	{ MODKEY,						XK_a,      					togglegaps,     		{0} },
	{ MODKEY|ShiftMask,				XK_a,      					defaultgaps,    		{0} },
	{ MODKEY,                       XK_Tab,    					view,           		{0} },
	{ MODKEY,             			XK_q,      					killclient,     		{0} },
	{ MODKEY,						XK_t,						setlayout,				{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,				XK_t,						setlayout,				{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,						XK_y,						setlayout,				{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,				XK_y,						setlayout,				{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,						XK_u,						setlayout,				{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,				XK_u,						setlayout,				{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,						XK_i,						setlayout,				{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,				XK_i,						setlayout,				{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ControlMask,			XK_comma,					cyclelayout,			{.i = -1 } },
	{ MODKEY|ControlMask,			XK_period,					cyclelayout,			{.i = +1 } },
	{ MODKEY,                       XK_space,  					setlayout,      		{0} },
	{ MODKEY|ShiftMask,             XK_space,  					togglefloating, 		{0} },
	{ MODKEY|ShiftMask,             XK_f,      					togglefullscr,  		{0} },
	{ MODKEY,                       XK_0,      					view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      					tag,            		{.ui = ~0 } },
	{ MODKEY,                       XK_comma, 					focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_period, 					focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  					tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 					tagmon,         		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,      					self_restart,   		{0} },
	{ MODKEY|ShiftMask,             XK_q,     					quit,           		{0} },
	TAGKEYS(						XK_1,                      	0)
	TAGKEYS(						XK_2,                      	1)
	TAGKEYS(						XK_3,                      	2)
	TAGKEYS(						XK_4,                      	3)
	TAGKEYS(						XK_5,                      	4)
	TAGKEYS(						XK_6,                      	5)
	TAGKEYS(						XK_7,                      	6)
	TAGKEYS(						XK_8,                      	7)
	TAGKEYS(						XK_9,                      	8)
	TAGKEYS(						XK_0,                      	9)
	// { 0,                            XF86XK_MonBrightnessUp,   	spawn,   				{.v = upbright}},
	// { 0,                            XF86XK_MonBrightnessDown, 	spawn,   				{.v = downbright}},
	// { 0,                            XF86XK_AudioLowerVolume,  	spawn,   				{.v = downvol}},
	// { 0,                            XF86XK_AudioMute,         	spawn,   				{.v = mutevol}},
	// { 0,                            XF86XK_AudioRaiseVolume,  	spawn,   				{.v = upvol}},
	// { 0,                            XF86XK_AudioPlay,         	spawn,   				{.v = playerpause}},
	// { 0,                            XF86XK_AudioPause,        	spawn,   				{.v = playerpause}},
	// { 0,                            XF86XK_AudioNext,         	spawn,   				{.v = playernext}},
	// { 0,                            XF86XK_AudioPrev,         	spawn,   				{.v = playerprevious}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        	argument */
	{ ClkLtSymbol,    		0,				Button1, 		cyclelayout,       	{.i = -1 } },
	{ ClkLtSymbol,    		0,				Button3, 		cyclelayout,       	{.i = +1 } },
	{ ClkLtSymbol,    		0,				Button2, 		setlayout,         	{.v = &layouts[0]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           	{0} },
	{ ClkStatusText,        0,              Button2,        spawn,          	{.v = terminalcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      	{0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, 	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    	{0} },
	{ ClkTagBar,            0,              Button1,        view,           	{0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     	{0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            	{0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      	{0} },
};


/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

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
static const double defaultopacity  			= 0.80;		/* 0 being full transparent 1 being non-transparent */
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
	"autorandr", "--force", "--load", "instawm", NULL,
	"setxkbmap", "-option", "caps:escape", NULL,
	"instamenue_youtube_subs", "-d", NULL,
	"polkit-dumb-agent", NULL,
	"touchpad-indicator", NULL,
	"blueman-applet", NULL,
	"numlockx", "on", NULL,
	"xsettingsd", NULL,
	"pamac-tray", NULL,
	"nm-applet", NULL,
	"pasystray", NULL,
	"clipmenud", NULL,
	NULL
};

/* tagging */
static const char *tags[] = { " 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: VirtualBox", " 9: Chat" , " 10: Settings" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	
	/* class     				instance  	title           	tags mask  		iscentered		isfloating  	isterminal  	noswallow  		monitor */
	//All workspaces 
	{ "floatmenu",		        NULL,     	NULL,  				0,         		1,          	1,          	0,          	-1,				-1},

	//Workspace 1 Monator 0
	{ "kitty", 		  			NULL,     	NULL,         		1 << 0,         0,          	0,          	1,          	-1,        		0 },
	
	//Workspace 2 Monator 0
	{ "code-oss", 		  		NULL,     	NULL,         		1 << 1,         0,          	0,          	0,          	-1,        		0 },
	{ "Emacs", 		  			NULL,     	NULL,         		1 << 1,         0,          	0,          	0,          	-1,        		0 },

	//Workspace 3 Monator 0
	{ "Nemo", 		  			NULL,     	NULL,         		1 << 2,         0,          	0,          	0,          	-1,        		0 },

	//Workspace 4 Monator 0
	{ "Ld-linux-x86-64.so.2",	NULL,    	NULL,   			1 << 3,    		0,          	1,          	0,          	-1,        		0 }, // Inkscape
	{ "Gimp",    				NULL,		NULL,         		1 << 3,    		0,          	1,          	0,          	-1,        		0 },

	//Workspace 5 Monator 0

	//Workspace 6 Monator 1
	{ "Firefox", 		  		NULL,     	NULL,         		1 << 5,        	0,          	0,          	0,          	-1,        		1 },
	{ "Vivaldi-stable",			NULL, 		NULL,         		1 << 5,        	0,          	0,          	0,          	-1,        		1 },

	//Workspace 7 Monator 1

	//Workspace 8 Monator 1
	{ "Steam",					NULL,     	NULL,         		1 << 7,    		0,          	0,          	0,          	-1,        		1 },

	//Workspace 9 Monator 1
	{ "TelegramDesktop",		NULL,   	NULL,         		1 << 8,    		0,          	0,          	0,          	-1,        		1 },
	{ "Element",				NULL,     	NULL,         		1 << 8,    		0,          	0,          	0,          	-1,        		1 },

	//Workspace 10 Monator 1
	{ NULL,      				NULL,     	"Event Tester", 	1 << 9,        	0,          	0,          	1,          	-1,        		1 }, /* xev */
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
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,		KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,		KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,		KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,		KEY,      toggletag,      {.ui = 1 << TAG} },

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
	/* modifier                     chain key			key        					function        		argument */
	{ Mod1Mask,          			-1,         		XK_space,  					spawn,       			{.v = instamenucmd } },
	{ MODKEY,                       -1,         		XK_p,      					spawn,          		{.v = instamenucmd } },
	{ MODKEY,						-1,         		XK_Return, 					spawn,          		{.v = terminalcmd } },
	{ MODKEY,                       -1,         		XK_b,      					togglebar,      		{0} },
	{ MODKEY,                       -1,         		XK_j,      					focusstack,     		{.i = +1 } },
	{ MODKEY,                       -1,         		XK_k,      					focusstack,     		{.i = -1 } },
	{ MODKEY,                       -1,         		XK_i,      					incnmaster,     		{.i = +1 } },
	{ MODKEY,                       -1,         		XK_d,      					incnmaster,     		{.i = -1 } },
	{ MODKEY,                       -1,         		XK_h,      					setmfact,       		{.f = -0.05} },
	{ MODKEY,                       -1,         		XK_l,      					setmfact,       		{.f = +0.05} },
	{ MODKEY|ShiftMask,             -1,         		XK_j,      					movestack,      		{.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         		XK_k,      					movestack,      		{.i = -1 } },
	{ MODKEY,                       -1,         		XK_Return, 					zoom,           		{0} },
	{ MODKEY,						-1,         		XK_z,						incrgaps,				{.i = +3 } },
	{ MODKEY,						-1,         		XK_x,						incrgaps,				{.i = -3 } },
	{ MODKEY,						-1,         		XK_a,      					togglegaps,     		{0} },
	{ MODKEY|ShiftMask,				-1,         		XK_a,      					defaultgaps,    		{0} },
	{ MODKEY,                       -1,         		XK_Tab,    					view,           		{0} },
	{ MODKEY,             			-1,         		XK_q,      					killclient,     		{0} },
	{ MODKEY,						-1,         		XK_t,						setlayout,				{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,				-1,         		XK_t,						setlayout,				{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,						-1,         		XK_y,						setlayout,				{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,				-1,         		XK_y,						setlayout,				{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,						-1,         		XK_u,						setlayout,				{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,				-1,         		XK_u,						setlayout,				{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,						-1,         		XK_i,						setlayout,				{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,				-1,         		XK_i,						setlayout,				{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|Mod1Mask,				-1,         		XK_s,	   					spawn,	   				SHCMD("transset-df -a --dec .1") },
	{ MODKEY|Mod1Mask,				-1,         		XK_d,	   					spawn,	   				SHCMD("transset-df -a --inc .1") },
	{ MODKEY|Mod1Mask,				-1,         		XK_f,	   					spawn,	   				SHCMD("transset-df -a .75") },
	{ MODKEY|ControlMask,			-1,         		XK_comma,					cyclelayout,			{.i = -1 } },
	{ MODKEY|ControlMask,			-1,         		XK_period,					cyclelayout,			{.i = +1 } },
	{ MODKEY,                       -1,         		XK_space,  					setlayout,      		{0} },
	{ MODKEY|ShiftMask,             -1,         		XK_space,  					togglefloating, 		{0} },
	{ MODKEY|ShiftMask,             -1,         		XK_f,      					togglefullscr,  		{0} },
	{ MODKEY,                       -1,         		XK_0,      					view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         		XK_0,      					tag,            		{.ui = ~0 } },
	{ MODKEY,                       -1,         		XK_comma, 					focusmon,       		{.i = -1 } },
	{ MODKEY,                       -1,         		XK_period, 					focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         		XK_comma,  					tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         		XK_period, 					tagmon,         		{.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         		XK_r,      					self_restart,   		{0} },
	{ MODKEY|ShiftMask,             -1,         		XK_q,     					quit,           		{0} },
	TAGKEYS(						-1,         		XK_1,                      	0)
	TAGKEYS(						-1,         		XK_2,                      	1)
	TAGKEYS(						-1,         		XK_3,                      	2)
	TAGKEYS(						-1,         		XK_4,                      	3)
	TAGKEYS(						-1,         		XK_5,                      	4)
	TAGKEYS(						-1,         		XK_6,                      	5)
	TAGKEYS(						-1,         		XK_7,                      	6)
	TAGKEYS(						-1,         		XK_8,                      	7)
	TAGKEYS(						-1,         		XK_9,                      	8)
	TAGKEYS(						-1,         		XK_0,                      	9)
	{ 0,                            -1,         		XF86XK_MonBrightnessUp,   	spawn,   				{.v = upbright}},
	{ 0,                            -1,         		XF86XK_MonBrightnessDown, 	spawn,   				{.v = downbright}},
	{ 0,                            -1,         		XF86XK_AudioLowerVolume,  	spawn,   				{.v = downvol}},
	{ 0,                            -1,         		XF86XK_AudioMute,         	spawn,   				{.v = mutevol}},
	{ 0,                            -1,         		XF86XK_AudioRaiseVolume,  	spawn,   				{.v = upvol}},
	{ 0,                            -1,         		XF86XK_AudioPlay,         	spawn,   				{.v = playerpause}},
	{ 0,                            -1,         		XF86XK_AudioPause,        	spawn,   				{.v = playerpause}},
	{ 0,                            -1,         		XF86XK_AudioNext,         	spawn,   				{.v = playernext}},
	{ 0,                            -1,         		XF86XK_AudioPrev,         	spawn,   				{.v = playerprevious}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkShutDown, or ClkRootWin */
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
	{ ClkShutDown,    		0,				Button1,		spawn,				{.v = powermenucmd } },
	// { ClkStartMenu,   		0,				Button1, 		spawn,				{.v = startmenucmd}},
};


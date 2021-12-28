/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static int showsystray        		            = 1;     	        /* 0 means no systray */
static const unsigned int borderpx  		    = 1;        	    /* border pixel of windows */
static const unsigned int snap      		    = 32;       	    /* snap pixel */
static const unsigned int gappih    		    = 10;       	    /* horiz inner gap between windows */
static const unsigned int gappiv    		    = 10;       	    /* vert inner gap between windows */
static const unsigned int gappoh    		    = 10;       	    /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    		    = 10;       	    /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning 	    = 2;   		        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing 	    = 2;   		        /* systray spacing */
static const unsigned int iconsizes 	        = 30;		        /* snap pixel */
static const int swallowfloating    		    = 0;        	    /* 1 means swallow floating windows by default */
static const int smartgaps          		    = 0;        	    /* 1 means no outer gap when there is only one window */
static const int systraypinningfailfirst 	    = 1;   		        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showbar            		    = 1;        	    /* 0 means no bar */
static const int topbar             		    = 1;        	    /* 0 means bottom bar */
static const int vertpad                        = 10;               /* vertical padding of bar */
static const int sidepad                        = 10;               /* horizontal padding of bar */
static const int viewontag         		        = 1;     	        /* 0 means don't view on tag switch */
static const int userepobar 			        = 1;  		        /* 0 means don't use repobar script */
static const int user_bh            		    = 28;               /* 0 means that repowm will calculate bar height, >= 1 means repowm will user_bh as bar height */
static const char *fonts[] = {
    "Source Code Pro:size=10",
    "FiraCode Nerd Font:size=12",
    "remixicon:size=12",
    "Siji:size=12",
    "MaterialIcons:size=10",
    "SourceCodePro Nerd Font:size=10",};

// repowm bar colors
static const char col_bg[]          = "#282a36";
static const char col_fg[]          = "#f8f8f2";
static const char col_red[]         = "#ff5555";
static const char col_cyan[]        = "#8be9fd";
static const char col_pink[]        = "#ff79c6";
static const char col_purple[]      = "#bd93f9";
static const char col_yellow[]      = "#f1fa8c";
static const char col_orange[]      = "#ffb86c";
static const char col_green[] 	    = "#50fa7b";

static const char *colors[][4] = {
    /*                  fg                  bg                  border 	        float*/
    [SchemeNorm]=   {   col_purple, 	    col_bg, 	        col_pink, 		col_green },
    [SchemeInv] =   {   col_bg, 	        col_purple, 		col_pink, 		col_green },
    [SchemeSel] =   {   col_fg, 	        col_purple,  	    col_purple, 	col_green },
    [SchemeTitle] = {   col_fg,             col_pink,           col_pink, 		col_green },
};

static const char *const autostart[] = {
    "autorandr", "--force", "--load", "repowm", NULL,
    "setxkbmap", "-option", "caps:escape", NULL,
    "repomenue_youtube_subs", "-d", NULL,
    "ckb-next", "--background", NULL,
    "touchpad-indicator", NULL,
    "clipmenu-daemon", NULL,
    "blueman-applet", NULL,
    "numlockx", "on", NULL,
    "xsettingsd", NULL,
    "volumeicon", NULL,
    "nm-applet", NULL,
    "audiolock", NULL,
    NULL
};

/* tagging */
static const char *tags[] = { " 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: Games", " 9: Chat" , " 10: Settings" };

static const char *tagsel[][2] = {
	{ "#282a36", "#ff5555" },
	{ "#282a36", "#8be9fd" },
	{ "#282a36", "#ff79c6" },
	{ "#282a36", "#bd93f9" },
	{ "#282a36", "#f1fa8c" },
	{ "#282a36", "#ffb86c" },
	{ "#282a36", "#50fa7b" },
	{ "#282a36", "#ff5555" },
	{ "#282a36", "#8be9fd" },
    { "#282a36", "#ff79c6" },
};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */

    /* class     		            instance  	    title               tags mask  	    iscentered		    switchtotag	        isfloating  	isterminal  	noswallow  	    	monitor */
    //All workspaces
    { "Multimonitorlock-gui.py",	NULL,     	    NULL,  		        0,         	    1,          	    1,          	    1,          	0,          	-1,		        	-1},
    { "Pavucontrol",		        NULL,           NULL,  		        0,         	    1,          	    1,          	    1,          	0,          	-1,			        -1},
    { "floatmenu",		            NULL,     	    NULL,  		        0,         	    1,          	    1,          	    1,          	0,          	-1,			        -1},
    { "Yad",		                NULL,     	    NULL,  		        0,         	    1,          	    1,          	    1,          	0,          	-1,			        -1},
    { "Peek",                       NULL,     	    NULL,  		        0,         	    1,          	    1,          	    1,          	0,          	-1,			        -1},
    { "Snapper",                    NULL,     	    NULL,  		        0,         	    1,          	    1,          	    1,          	1,          	-1,			        -1},

    //Workspace 1 Monitor 0
    { "Alacritty", 		  	        NULL,     	    NULL,         	    1 << 0,         0,          	    1,          	    0,          	1,          	-1,        	    	0},
    { "kitty", 		  	            NULL,     	    NULL,         	    1 << 0,         0,          	    1,          	    0,          	1,          	-1,        	    	0},

    //Workspace 2 Monitor 0
    { "Code", 		  	            NULL,     	    NULL,         	    1 << 1,         0,          	    1,          	    0,          	0,          	-1,        		    0},
    { "Emacs", 		  	            NULL,     	    NULL,         	    1 << 1,         0,          	    1,              	0,          	0,          	-1,        		    0},
    { "nvim-qt", 		  	        NULL,     	    NULL,         	    1 << 1,         0,          	    1,              	0,          	0,          	-1,        		    0},

    //Workspace 3 Monitor 0
    { "Nemo", 		  	            NULL,     	    NULL,         	    1 << 2,         0,          	    1,              	0,          	0,          	-1,        	    	0},

    //Workspace 4 Monitor 0
    { "Ld-linux-x86-64.so.2",	    NULL,           NULL,   		    1 << 3,    	    0,          	    1,              	0,          	0,          	-1,        	    	0}, // Inkscape
    { "Gimp",    		            NULL,	        NULL,         	    1 << 3,    	    0,          	    1,                  0,          	0,          	-1,        	        0},

    //Workspace 0 Monitor 0
    { "PkgBrowser", 		  	    NULL,     	    NULL,         	    1 << 9,         0,          	    1,              	0,          	0,          	-1,        	    	0},

    //Workspace 6 Monitor 1
    { "Google-chrome",		        NULL, 	        NULL,         	    1 << 5,        	0,              	1,              	0,          	0,          	-1,        	    	1},

    //Workspace 7 Monitor 1

    //Workspace 8 Monitor 1
    { "gdlauncher",	                NULL,     	    NULL,         	    1 << 7,    	    0,              	1,              	0,          	0,          	-1,        	    	1},
    { "RuneScape",	                NULL,     	    NULL,         	    1 << 7,    	    0,              	1,              	0,          	0,          	-1,        	    	1},
    { "Steam",			            NULL,     	    NULL,         	    1 << 7,    	    0,              	1,              	0,          	0,          	-1,        	    	1},

    //Workspace 9 Monitor 1
    { "TelegramDesktop",	        NULL,   	    NULL,         	    1 << 8,    	    0,          	    1,              	0,          	0,          	-1,        	    	1},
    { "Element",		            NULL,     	    NULL,         	    1 << 8,    	    0,          	    1,              	0,          	0,          	-1,        	    	1},

    //Workspace 10 Monitor
    { "Vmplayer",		            NULL,     	    NULL,         	    1 << 9,    	    0,          	    1,              	0,          	0,          	-1,        	    	1},
    { NULL,      		            NULL,           "Event Tester", 	1 << 9,        	0,          	    1,              	0,          	1,          	-1,        	    	1}, /* xev */
    { NULL,      		            NULL,           "lazygit", 	        1 << 9,        	0,          	    1,              	0,          	1,          	-1,        	    	1}, /* lazygit */
    { NULL,      		            NULL,           "bpytop", 	        1 << 9,        	0,          	    1,              	0,          	1,          	-1,        	    	1}, /* bpytop */
    { NULL,      		            NULL,           "btop", 	        1 << 9,        	0,          	    1,              	0,          	1,          	-1,        	    	1}, /* btop */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol arrange		function */
    { "[]=",				tile },				            /* Default: Master on left, slaves on right */
    { "TTT",				bstack },			            /* Master on top, slaves on bottom */
    { "[@]",				spiral },		            	/* Fibonacci spiral */
    { "[\\]",				dwindle },			            /* Decreasing in size right and leftward */
    { "[D]",				deck },			            	/* Master on left, slaves in monocle-like mode on right */
    { "[M]",				monocle },		            	/* All windows on top of eachother */
    { "|M|",				centeredmaster },	        	/* Master in middle, slaves on sides */
    { ">M>",				centeredfloatingmaster },   	/* Same but master floats */
    { "><>",				NULL },				            /* no layout function means floating behavior */
    { NULL,				    NULL },
};

static const Taglayout taglayouts[] = {
    /*  tag		layout */
    {   1,		{.v = &layouts[6]} },
    {   2,		{.v = &layouts[0]} },
    {   3,		{.v = &layouts[0]} },
    {   4,		{.v = &layouts[0]} },
    {   5,		{.v = &layouts[0]} },
    {   6,		{.v = &layouts[0]} },
    {   7,		{.v = &layouts[0]} },
    {   8,		{.v = &layouts[0]} },
    {   9,		{.v = &layouts[0]} },
    {   10,		{.v = &layouts[0]} },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
{ MODKEY,                       CHAIN,		KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           CHAIN,		KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             CHAIN,		KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, CHAIN,		KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre repowm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* repowm commands */
static char repomenumon[2] = "0"; /* component of repomenucmd, manipulated in spawn() */
static const char *layoutmenucmd = "layoutmenu";
static const char *repomenucmd[] = {"repomenu_run", NULL};
static const char *systemmonitorcmd[] = { "repowm-schemas", "systemmonitorcmd", NULL};
static const char *instasettings[] = { "repowm-schemas", "instasettingscmd", NULL};
static const char *startmenucmd[] = { "repowm-schemas", "startmenucmd", NULL};
static const char *passmenucmd[] = { "repowm-schemas", "passmenucmd", NULL};
static const char *clipmenucmd[] = { "repowm-schemas", "clipmenucmd", NULL};
static const char *smartcmd[] = { "repowm-schemas", "smartmenucmd", NULL};

/* Do not remove */
static const char *powermenucmd[] = { "repowm-schemas", "powermenucmd", NULL};

/* repomenu commands */
static const char *filemanagercmd[] = { "repowm-schemas", "filemanager", NULL};
static const char *hypervisorcmd[] = { "repowm-schemas", "hypervisor", NULL};
static const char *terminalcmd[] = { "repowm-schemas", "terminal", NULL};
static const char *browsercmd[] = { "repowm-schemas", "webbrowser", NULL};
static const char *editorcmd[] = { "repowm-schemas", "texteditor", NULL};
static const char *mailcmd[] = { "repowm-schemas", "mailreader", NULL};
static const char *gitcmd[] = { "repowm-schemas", "gitbrowser", NULL};

/* genreal commands*/
static const char *playernext[] = { "playerctl", "next", NULL};
static const char *playerprevious[] = { "playerctl", "previous", NULL};
static const char *playerpause[] = { "playerctl", "play-pause", NULL};

static const char *upvol[] = {"amixer", "set", "Master", "5%+", NULL};
static const char *downvol[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *mutevol[] = {"amixer", "set", "Master", "toggle", NULL};

static const char *upbright[] = {"xbacklight", "+10", NULL};
static const char *downbright[] = {"xbacklight", "-10", NULL};

static const char scratchpadname[] = "dropdown_alacritty";
static const char *scratchpadcmd[] = { "alacritty", "--title", "dropdown_alacritty", "--class", "dropdown_alacritty,dropdown_alacritty", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier                             chain key			  key        			                function        		argument */
    // Keybinds for XFKeys
    { 0,                            	    -1,         		XF86XK_MonBrightnessUp,   			    spawn,   			    {.v = upbright}},
    { 0,                            	    -1,         		XF86XK_MonBrightnessDown, 			    spawn,   			    {.v = downbright}},
    { 0,                            	    -1,         		XF86XK_AudioLowerVolume,  			    spawn,   			    {.v = downvol}},
    { 0,                            	    -1,         		XF86XK_AudioMute,         			    spawn,   		    	{.v = mutevol}},
    { 0,                            	    -1,         		XF86XK_AudioRaiseVolume,  			    spawn,   		    	{.v = upvol}},
    { 0,                            	    -1,         		XF86XK_AudioPlay,         			    spawn,   		    	{.v = playerpause}},
    { 0,                            	    -1,         		XF86XK_AudioPause,        			    spawn,   		    	{.v = playerpause}},
    { 0,                            	    -1,         		XF86XK_AudioNext,         			    spawn,   		    	{.v = playernext}},
    { 0,                            	    -1,         		XF86XK_AudioPrev,         			    spawn,   		    	{.v = playerprevious}},
    //TheRepoClub Custom Keybinds.
    { ControlMask|Mod1Mask,				    -1,         		XK_v,					                spawn,       			SHCMD("fourmon") },
    { MODKEY,				                -1,         		XK_o,						            spawn,       			{.v = systemmonitorcmd } },
    { MODKEY,				                -1,         		XK_F1,					                spawn,       			{.v = smartcmd } },
    { MODKEY,				                -1,         		XK_F2,			                        spawn,       			{.v = clipmenucmd } },
    { MODKEY,				                -1,         		XK_F3,					                spawn,       			{.v = instasettings } },
    { MODKEY,				                -1,         		XK_F4,					                spawn,       			SHCMD("repomenue_pacman") },
    { MODKEY,				                -1,         		XK_F5,					                spawn,       			SHCMD("repomenue_network") },
    { MODKEY,				                -1,         		XK_F6,					                spawn,       			SHCMD("repomenue_music") },
    { MODKEY,				                -1,         		XK_F7,					                spawn,       			SHCMD("repomenue_youtube_subs") },
    { MODKEY,				                -1,         		XK_F8,					                spawn,       			SHCMD("repomenue_kill") },
    { MODKEY|ShiftMask,          	        -1,         	    XK_Return,  		                    spawn,       			{.v = filemanagercmd } },
    { MODKEY|ControlMask,		            -1,         		XK_h,						            spawn,       			{.v = hypervisorcmd } },
    { MODKEY|ControlMask,		            -1,         		XK_f,						            spawn,       			{.v = browsercmd } },
    { MODKEY|ControlMask,		            -1,         		XK_c,						            spawn,       			{.v = editorcmd } },
    { MODKEY|ControlMask,		            -1,         		XK_m,						            spawn,       			{.v = mailcmd } },
    { MODKEY|ControlMask,		            -1,         		XK_g,						            spawn,       			{.v = gitcmd } },
    { MODKEY|ShiftMask,          	        -1,         		XK_e,  					                spawn,       			SHCMD("repomenue_powermenu") },
    { MODKEY|ControlMask,		            -1,         		XK_i,					            	spawn,       			SHCMD("inkscape") },
    { MODKEY|ControlMask,		            -1,         		XK_k,					            	spawn,       			SHCMD("krita") },
    { MODKEY|ControlMask,		            -1,         		XK_v,					            	spawn,       			SHCMD("vlc") },
    { MODKEY|ControlMask,	                XK_g,         		XK_s,					            	spawn,       			SHCMD("prime-run steam") },
    { MODKEY|ControlMask,		            XK_g,         		XK_m,					            	spawn,       			SHCMD("prime-run minecraft-launcher") },
    { MODKEY|ControlMask,		            XK_g,         		XK_r,					            	spawn,       			SHCMD("prime-run runescape-launcher") },
    { MODKEY|ControlMask,	                -1,         		XK_e,					            	spawn,       			SHCMD("element-desktop") },
    { MODKEY|ControlMask,		            -1,         		XK_t,					            	spawn,       			SHCMD("telegram-desktop") },
    { MODKEY|ControlMask,		            -1,         		XK_p,					            	spawn,       			SHCMD("pkgbrowser") },
    { MODKEY|ControlMask,		            -1,         		XK_u,					            	spawn,       			SHCMD("pavucontrol") },
    { MODKEY|ShiftMask,			            -1,         		XK_z,					            	spawn,       		    SHCMD("multimonitorlock-gui") },
    { MODKEY|Mod1Mask,			            -1,         		XK_p,					            	spawn,       			SHCMD("piper") },
    { MODKEY,				                XK_Print,           XK_w,						            spawn,       			SHCMD("win-shot -w" ) },
    { MODKEY,				                XK_Print,           XK_s,						            spawn,       			SHCMD("win-shot -s" ) },
    { MODKEY,				                XK_Print,           XK_f,						            spawn,       			SHCMD("win-shot -f" ) },

    //Keybinds you may need to customise.
    { Mod1Mask,          		            -1,         		XK_space,  			                    spawn,       			{.v = repomenucmd } },
    { MODKEY,                       	    -1,         		XK_m,      		                        spawn,          		{.v = repomenucmd } },
    { MODKEY,                       	    -1,         		XK_p,      		                        spawn,          		{.v = passmenucmd } },
    { MODKEY,				                -1,         		XK_Return, 			                    spawn,          		{.v = terminalcmd } },
    { ControlMask,                  	    -1,         		XK_Return,  		                    togglescratch,  		{.v = scratchpadcmd } },
    { MODKEY,                       	    -1,         		XK_b,      			                    togglebar,      		{0} },
    { MODKEY,                               -1,                 XK_s,                                   togglesystray,          {0} },
    { MODKEY,                       	    -1,         		XK_j,      			                    focusstack,     		{.i = +1 } },
    { MODKEY,                       	    -1,         		XK_k,      			                    focusstack,     		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_i,      			                    incnmaster,     		{.i = +1 } },
    { MODKEY,                       	    -1,         		XK_d,      			                    incnmaster,     		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_h,      			                    setmfact,       		{.f = -0.05} },
    { MODKEY,                       	    -1,         		XK_l,      			                    setmfact,       		{.f = +0.05} },
    { MODKEY|ShiftMask,             	    -1,         		XK_j,      			                    movestack,      		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_k,      			                    movestack,      		{.i = -1 } },
    { MODKEY|Mod1Mask, 			            -1, 			    XK_Return, 			                    zoom, 				    {0} },
    { MODKEY,				                -1,         		XK_z,					            	incrgaps,			    {.i = +3 } },
    { MODKEY,				                -1,         		XK_x,					            	incrgaps,			    {.i = -3 } },
    { MODKEY,				                -1,         		XK_a,      			                    togglegaps,     		{0} },
    { MODKEY|ShiftMask,			            -1,         		XK_a,      			                    defaultgaps,    		{0} },
    { MODKEY,				                -1,         		XK_Tab,    			                    view,           		{0} },
    { MODKEY,             		            -1,         		XK_q,      			                    killclient,     		{0} },
    { MODKEY,		                        -1,         		XK_c,					            	spawn,       			SHCMD("killall xkill 2>/dev/null || xkill") },
    { MODKEY,				                -1,         		XK_t,						            setlayout,		    	{.v = &layouts[0]} }, /* tile */
    { MODKEY|ShiftMask,			            -1,         		XK_t,					            	setlayout,		    	{.v = &layouts[1]} }, /* bstack */
    { MODKEY,				                -1,         		XK_y,					            	setlayout,		    	{.v = &layouts[2]} }, /* spiral */
    { MODKEY|ShiftMask,			            -1,         		XK_y,					            	setlayout,		    	{.v = &layouts[3]} }, /* dwindle */
    { MODKEY,				                -1,         		XK_u,					            	setlayout,		    	{.v = &layouts[4]} }, /* deck */
    { MODKEY|ShiftMask,			            -1,         		XK_u,					            	setlayout,		    	{.v = &layouts[5]} }, /* monocle */
    { MODKEY,				                -1,         		XK_i,					            	setlayout,		    	{.v = &layouts[6]} }, /* centeredmaster */
    { MODKEY|ShiftMask,			            -1,         		XK_i,					            	setlayout,		    	{.v = &layouts[7]} }, /* centeredfloatingmaster */
    { MODKEY|Mod1Mask,			            -1,         		XK_s,	   				                spawn,	   		    	SHCMD("transset-df -a --dec .1") },
    { MODKEY|Mod1Mask,			            -1,         		XK_d,	   				                spawn,	   		    	SHCMD("transset-df -a --inc .1") },
    { MODKEY|Mod1Mask,			            -1,         		XK_f,	   				                spawn,	   		    	SHCMD("transset-df -a .75") },
    { MODKEY|ControlMask,		            -1,         		XK_comma,				                cyclelayout,		    {.i = -1 } },
    { MODKEY|ControlMask,		            -1,         		XK_period,			                    cyclelayout,		    {.i = +1 } },
    { MODKEY,                      	        -1,         		XK_space,  			                    setlayout,      		{0} },
    { MODKEY|ShiftMask,             	    -1,         		XK_space,  			                    togglefloating, 		{0} },
    { MODKEY|ShiftMask,             	    -1,         		XK_f,      			                    togglefullscr,  		{0} },
    { MODKEY,                       	    -1,         		XK_comma, 			                    focusmon,       		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_period, 			                    focusmon,       		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_comma,  			                    tagmon,         		{.i = -1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_period, 			                    tagmon,         		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_r,      			                    quit,   			    {1} },
    { MODKEY|ShiftMask,             	    -1,         		XK_q,     			                    quit,           		{0} },
    TAGKEYS(				                -1,         		XK_1,                                   0)
    TAGKEYS(				                -1,         		XK_2,                                   1)
    TAGKEYS(				                -1,         		XK_3,                                   2)
    TAGKEYS(				                -1,         		XK_4,                                   3)
    TAGKEYS(				                -1,         		XK_5,                                   4)
    TAGKEYS(				                -1,         		XK_6,                                   5)
    TAGKEYS(				                -1,         		XK_7,                                   6)
    TAGKEYS(				                -1,         		XK_8,                                   7)
    TAGKEYS(				                -1,         		XK_9,                                   8)
    TAGKEYS(				                -1,         		XK_0,                                   9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkShutDown, or ClkRootWin */
static Button buttons[] = {
    /* click               	event mask      button          function        	    argument */
    { ClkStartMenu,		    0,		        Button1,	    spawn,			        {.v = startmenucmd } },
    { ClkLtSymbol,    		0,		        Button1, 	    cyclelayout,       	    {.i = -1 } },
    { ClkLtSymbol,          0,              Button3,        layoutmenu,             {0} },
    { ClkLtSymbol,    		0,		        Button2, 	    setlayout,              {.v = &layouts[0]} },
    { ClkWinTitle,          0,              Button2,        zoom,           	    {0} },
    { ClkStatusText,        0,              Button2,        spawn,          	    {.v = terminalcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      	    {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, 	    {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    	    {0} },
    { ClkTagBar,            0,              Button1,        view,           	    {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     	    {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            	    {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      	    {0} },
    { ClkShutDown,    		0,		        Button1,	    spawn,			        {.v = powermenucmd } },
};

/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  		    = 3;        	    /* border pixel of windows */
static const unsigned int snap      		    = 32;       	    /* snap pixel */
static const unsigned int gappih    		    = 10;       	    /* horiz inner gap between windows */
static const unsigned int gappiv    		    = 10;       	    /* vert inner gap between windows */
static const unsigned int gappoh    		    = 10;       	    /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    		    = 10;       	    /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning 	    = 2;   		    /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft 	    = 0;   		    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing 	    = 2;   		    /* systray spacing */
static const unsigned int iconsizes 	            = 30;		    /* snap pixel */
static const int swallowfloating    		    = 0;        	    /* 1 means swallow floating windows by default */
static const int smartgaps          		    = 0;        	    /* 1 means no outer gap when there is only one window */
static const int systraypinningfailfirst 	    = 1;   		    /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        		    = 1;     	            /* 0 means no systray */
static const int showbar            		    = 1;        	    /* 0 means no bar */
static const int topbar             		    = 1;        	    /* 0 means bottom bar */
static const int viewontag         		    = 1;     	            /* 0 means don't view on tag switch */
static const int useinstabar 			    = 1;  		    /* 0 means don't use instabar script */
static const int user_bh            		    = 28;                   /* 0 means that instawm will calculate bar height, >= 1 means instawm will user_bh as bar height */
static const char *fonts[] = {
    "Source Code Pro:size=10",
    "remixicon:size=12",
    "Siji:size=12",
    "MaterialIcons:size=10",
    "FiraCode Nerd Font:size=12",};


// instawm bar colors
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#ff79c6";
static const char col_gray3[]       = "#bd93f9";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#bd93f9";
static const char col_green[] 	    = "#61C766";

static const char *colors[][4] = {
    /*                  fg              bg                      border 	                float*/
    [SchemeNorm]=   {   col_gray3, 	col_gray1, 		col_gray2, 		col_green },
    [SchemeInv] =   {   col_gray1, 	col_gray3, 		col_gray2, 		col_green },
    [SchemeSel] =   {   col_gray4, 	col_cyan,  		col_cyan, 		col_green },
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
    "nm-applet", NULL,
    "pasystray", NULL,
    "clipmenud", NULL,
    NULL
};

/* tagging */
static const char *tags[] = { " 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: Games", " 9: Chat" , " 10: Settings" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */

    /* class     		    instance  	    title               tags mask  	    iscentered		    switchtotag	        isfloating  	isterminal  	noswallow  	    	monitor */
    //All workspaces
    { "MultiMonitorLock-GUI",	    NULL,     	    NULL,  		0,         	    1,          	    1,          	1,          	0,          	-1,			-1},
    { "Pavucontrol",		    NULL,           NULL,  		0,         	    1,          	    1,          	1,          	0,          	-1,			-1},
    { "floatmenu",		    NULL,     	    NULL,  		0,         	    1,          	    1,          	1,          	0,          	-1,			-1},
    { "Yad",		            NULL,     	    NULL,  		0,         	    1,          	    1,          	1,          	0,          	-1,			-1},
    { "Timeshift-gtk",              NULL,     	    NULL,  		0,         	    1,          	    1,          	1,          	0,          	-1,			-1},

    //Workspace 1 Monitor 0
    { "kitty", 		  	    NULL,     	    NULL,         	1 << 0,             0,          	    1,          	0,          	1,          	-1,        		0},

    //Workspace 2 Monitor 0
    { "Code", 		  	    NULL,     	    NULL,         	1 << 1,             0,          	    1,          	0,          	0,          	-1,        		0},
    { "Emacs", 		  	    NULL,     	    NULL,         	1 << 1,             0,          	    1,              	0,          	0,          	-1,        		0},
    { "Gvim", 		  	    NULL,     	    NULL,         	1 << 1,             0,          	    1,              	0,          	0,          	-1,        		0},

    //Workspace 3 Monitor 0
    { "Nemo", 		  	    NULL,     	    NULL,         	1 << 2,             0,          	    1,              	0,          	0,          	-1,        		0},

    //Workspace 4 Monitor 0
    { "Ld-linux-x86-64.so.2",	    NULL,           NULL,   		1 << 3,    	    0,          	    1,              	1,          	0,          	-1,        		0}, // Inkscape
    { "Gimp",    		    NULL,	    NULL,         	1 << 3,    	    0,          	    1,                  1,          	0,          	-1,        	        0},

    //Workspace 5 Monitor 0

    //Workspace 6 Monitor 1
    { "Firefox", 		    NULL,     	    NULL,         	1 << 5,        	    0,          	    1,                  0,          	0,          	-1,        		1},
    { "Vivaldi-stable",		    NULL, 	    NULL,         	1 << 5,        	    0,              	    1,              	0,          	0,          	-1,        		1},

    //Workspace 7 Monitor 1

    //Workspace 8 Monitor 1
    { "Steam",			    NULL,     	    NULL,         	1 << 7,    	    0,              	    1,              	0,          	0,          	-1,        		1},
    { "Minecraft Launcher",	    NULL,     	    NULL,         	1 << 7,    	    0,              	    1,              	0,          	0,          	-1,        		1},

    //Workspace 9 Monitor 1
    { "TelegramDesktop",	    NULL,   	    NULL,         	1 << 8,    	    0,          	    1,              	0,          	0,          	-1,        		1},
    { "Element",		    NULL,     	    NULL,         	1 << 8,    	    0,          	    1,              	0,          	0,          	-1,        		1},

    //Workspace 10 Monitor 1
    { NULL,      		    NULL,           "Event Tester", 	1 << 9,        	    0,          	    1,              	0,          	1,          	-1,        		1}, /* xev */
    { NULL,      		    NULL,           "lazygit", 	        1 << 9,        	    0,          	    1,              	0,          	1,          	-1,        		1}, /* lazygit */
};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol arrange			function */
    { "[]=",				tile },				/* Default: Master on left, slaves on right */
    { "TTT",				bstack },			/* Master on top, slaves on bottom */
    { "[@]",				spiral },			/* Fibonacci spiral */
    { "[\\]",				dwindle },			/* Decreasing in size right and leftward */
    { "[D]",				deck },				/* Master on left, slaves in monocle-like mode on right */
    { "[M]",				monocle },			/* All windows on top of eachother */
    { "|M|",				centeredmaster },		/* Master in middle, slaves on sides */
    { ">M>",				centeredfloatingmaster },	/* Same but master floats */
    { "><>",				NULL },				/* no layout function means floating behavior */
    { NULL,				NULL },
};

static const Taglayout taglayouts[] = {
    /* tag		    layout */
    { 1,		    {.v = &layouts[6]} },
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

static const char *upvol[] = {"amixer", "set", "Master", "5%+", NULL};
static const char *downvol[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *mutevol[] = {"amixer", "set", "Master", "toggle", NULL};

static const char *upbright[] = {"xbacklight", "+10", NULL};
static const char *downbright[] = {"xbacklight", "-10", NULL};

static const char scratchpadname[] = "dropdown_kitty";
static const char *scratchpadcmd[] = { "kitty", "--title=dropdown_kitty", "--name=dropdown_kitty", "--class=dropdown_kitty", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier                             chain key			  key        			                function        		argument */
    // Keybinds for XFKeys
    { 0,                            	    -1,         		XF86XK_MonBrightnessUp,   			spawn,   			{.v = upbright}},
    { 0,                            	    -1,         		XF86XK_MonBrightnessDown, 			spawn,   			{.v = downbright}},
    { 0,                            	    -1,         		XF86XK_AudioLowerVolume,  			spawn,   			{.v = downvol}},
    { 0,                            	     -1,         		XF86XK_AudioMute,         			spawn,   			{.v = mutevol}},
    { 0,                            	    -1,         		XF86XK_AudioRaiseVolume,  			spawn,   			{.v = upvol}},
    { 0,                            	    -1,         		XF86XK_AudioPlay,         			spawn,   			{.v = playerpause}},
    { 0,                            	    -1,         		XF86XK_AudioPause,        			spawn,   			{.v = playerpause}},
    { 0,                            	    -1,         		XF86XK_AudioNext,         			spawn,   			{.v = playernext}},
    { 0,                            	    -1,         		XF86XK_AudioPrev,         			spawn,   			{.v = playerprevious}},
    //TheRepoClub Custom Keybinds.
    { MODKEY,				    -1,         		XK_o,						spawn,       			{.v = systemmonitorcmd } },
    { MODKEY,				    -1,         		XK_F1,					        spawn,       			{.v = smartcmd } },
    { MODKEY,				    -1,         		XK_F2,			                        spawn,       			{.v = clipmenucmd } },
    { MODKEY,				    -1,         		XK_F3,					        spawn,       			{.v = instasettings } },
    { MODKEY|ShiftMask,          	    -1,         		XK_Return,  		                        spawn,       			{.v = filemanagercmd } },
    { MODKEY|ControlMask,		    -1,         		XK_h,						spawn,       			{.v = hypervisorcmd } },
    { MODKEY|ControlMask,		    -1,         		XK_f,						spawn,       			{.v = browsercmd } },
    { MODKEY|ControlMask,		    -1,         		XK_c,						spawn,       			{.v = editorcmd } },
    { MODKEY|ControlMask,		    -1,         		XK_m,						spawn,       			{.v = mailcmd } },
    { MODKEY|ControlMask,		    -1,         		XK_g,						spawn,       			{.v = gitcmd } },
    { MODKEY|ShiftMask,          	    -1,         		XK_e,  					        spawn,       			SHCMD("qt-logout") },
    { MODKEY|ControlMask,		    -1,         		XK_i,						spawn,       			SHCMD("inkscape") },
    { MODKEY|ControlMask,		    -1,         		XK_k,						spawn,       			SHCMD("krita") },
    { MODKEY|ControlMask,		    -1,         		XK_v,						spawn,       			SHCMD("vlc") },
    { MODKEY|ControlMask,	            XK_g,         		XK_s,						spawn,       			SHCMD("prime-run steam") },
    { MODKEY|ControlMask,		    XK_g,         		XK_m,						spawn,       			SHCMD("prime-run minecraft-launcher") },
    { MODKEY|ControlMask,	            -1,         		XK_e,						spawn,       			SHCMD("element-desktop") },
    { MODKEY|ControlMask,		    -1,         		XK_t,						spawn,       			SHCMD("telegram-desktop") },
    { MODKEY|ControlMask,		    -1,         		XK_p,						spawn,       			SHCMD("piper") },
    { MODKEY|ControlMask,		    -1,         		XK_u,						spawn,       			SHCMD("pavucontrol") },
    { MODKEY|ShiftMask,			    -1,         		XK_z,						spawn,       		        SHCMD("multimonitorlock-gui") },
    { MODKEY|Mod1Mask,			    -1,         		XK_p,						spawn,       			SHCMD("pamac-manager") },
    { MODKEY|Mod1Mask,			    -1,         		XK_t,						spawn,       			SHCMD("telegram-desktop") },

    { MODKEY,				    XK_Print,                   XK_w,						spawn,       			SHCMD("wm-maim -w" ) },
    { MODKEY,				    XK_Print,                   XK_s,						spawn,       			SHCMD("wm-maim -s" ) },
    { MODKEY,				    XK_Print,                   XK_f,						spawn,       			SHCMD("wm-maim -f" ) },

    //Keybinds you may need to customise.
    { Mod1Mask,          		    -1,         		XK_space,  			                spawn,       			{.v = instamenucmd } },
    { MODKEY,                       	    -1,         		XK_p,      		                        spawn,          		{.v = instamenucmd } },
    { MODKEY,				    -1,         		XK_Return, 			                spawn,          		{.v = terminalcmd } },
    { ControlMask,                  	    -1,         		XK_Return,  		                        togglescratch,  		{.v = scratchpadcmd } },
    { MODKEY,                       	    -1,         		XK_b,      			                togglebar,      		{0} },
    { MODKEY,                       	    -1,         		XK_j,      			                focusstack,     		{.i = +1 } },
    { MODKEY,                       	    -1,         		XK_k,      			                focusstack,     		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_i,      			                incnmaster,     		{.i = +1 } },
    { MODKEY,                       	    -1,         		XK_d,      			                incnmaster,     		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_h,      			                setmfact,       		{.f = -0.05} },
    { MODKEY,                       	    -1,         		XK_l,      			                setmfact,       		{.f = +0.05} },
    { MODKEY|ShiftMask,             	    -1,         		XK_j,      			                movestack,      		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_k,      			                movestack,      		{.i = -1 } },
    { MODKEY|Mod1Mask, 			    -1, 			XK_Return, 			                zoom, 				{0} },
    { MODKEY,				    -1,         		XK_z,						incrgaps,			{.i = +3 } },
    { MODKEY,				    -1,         		XK_x,						incrgaps,			{.i = -3 } },
    { MODKEY,				    -1,         		XK_a,      			                togglegaps,     		{0} },
    { MODKEY|ShiftMask,			    -1,         		XK_a,      			                defaultgaps,    		{0} },
    { MODKEY,				    -1,         		XK_Tab,    			                view,           		{0} },
    { MODKEY,             		    -1,         		XK_q,      			                killclient,     		{0} },
    { MODKEY,				    -1,         		XK_t,						setlayout,			{.v = &layouts[0]} }, /* tile */
    { MODKEY|ShiftMask,			    -1,         		XK_t,						setlayout,			{.v = &layouts[1]} }, /* bstack */
    { MODKEY,				    -1,         		XK_y,						setlayout,			{.v = &layouts[2]} }, /* spiral */
    { MODKEY|ShiftMask,			    -1,         		XK_y,						setlayout,			{.v = &layouts[3]} }, /* dwindle */
    { MODKEY,				    -1,         		XK_u,						setlayout,			{.v = &layouts[4]} }, /* deck */
    { MODKEY|ShiftMask,			    -1,         		XK_u,						setlayout,			{.v = &layouts[5]} }, /* monocle */
    { MODKEY,				    -1,         		XK_i,						setlayout,			{.v = &layouts[6]} }, /* centeredmaster */
    { MODKEY|ShiftMask,			    -1,         		XK_i,						setlayout,			{.v = &layouts[7]} }, /* centeredfloatingmaster */
    { MODKEY|Mod1Mask,			    -1,         		XK_s,	   				        spawn,	   			SHCMD("transset-df -a --dec .1") },
    { MODKEY|Mod1Mask,			    -1,         		XK_d,	   				        spawn,	   			SHCMD("transset-df -a --inc .1") },
    { MODKEY|Mod1Mask,			    -1,         		XK_f,	   				        spawn,	   			SHCMD("transset-df -a .75") },
    { MODKEY|ControlMask,		    -1,         		XK_comma,				        cyclelayout,		        {.i = -1 } },
    { MODKEY|ControlMask,		    -1,         		XK_period,			                cyclelayout,		        {.i = +1 } },
    { MODKEY,                      	    -1,         		XK_space,  			                setlayout,      		{0} },
    { MODKEY|ShiftMask,             	    -1,         		XK_space,  			                togglefloating, 		{0} },
    { MODKEY|ShiftMask,             	    -1,         		XK_f,      			                togglefullscr,  		{0} },
    { MODKEY,                       	    -1,         		XK_0,      			                view,           		{.ui = ~0 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_0,      			                tag,            		{.ui = ~0 } },
    { MODKEY,                       	    -1,         		XK_comma, 			                focusmon,       		{.i = -1 } },
    { MODKEY,                       	    -1,         		XK_period, 			                focusmon,       		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_comma,  			                tagmon,         		{.i = -1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_period, 			                tagmon,         		{.i = +1 } },
    { MODKEY|ShiftMask,             	    -1,         		XK_r,      			                quit,   			{1} },
    { MODKEY|ShiftMask,             	    -1,         		XK_q,     			                quit,           		{0} },
    TAGKEYS(				    -1,         		XK_1,                                           0)
    TAGKEYS(				    -1,         		XK_2,                                           1)
    TAGKEYS(				    -1,         		XK_3,                                           2)
    TAGKEYS(				    -1,         		XK_4,                                           3)
    TAGKEYS(				    -1,         		XK_5,                                           4)
    TAGKEYS(				    -1,         		XK_6,                                           5)
    TAGKEYS(				    -1,         		XK_7,                                           6)
    TAGKEYS(				    -1,         		XK_8,                                           7)
    TAGKEYS(				    -1,         		XK_9,                                           8)
    TAGKEYS(				    -1,         		XK_0,                                           9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkShutDown, or ClkRootWin */
static Button buttons[] = {
    /* click               	event mask      button          function        	    argument */
    { ClkStartMenu,		0,		Button1,	spawn,			    {.v = startmenucmd } },
    { ClkLtSymbol,    		0,		Button1, 	cyclelayout,       	    {.i = -1 } },
    { ClkLtSymbol,    		0,		Button3, 	cyclelayout,       	    {.i = +1 } },
    { ClkLtSymbol,    		0,		Button2, 	setlayout,                  {.v = &layouts[0]} },
    { ClkWinTitle,              0,              Button2,        zoom,           	    {0} },
    { ClkStatusText,            0,              Button2,        spawn,          	    {.v = terminalcmd } },
    { ClkClientWin,             MODKEY,         Button1,        movemouse,      	    {0} },
    { ClkClientWin,             MODKEY,         Button2,        togglefloating, 	    {0} },
    { ClkClientWin,             MODKEY,         Button3,        resizemouse,    	    {0} },
    { ClkTagBar,                0,              Button1,        view,           	    {0} },
    { ClkTagBar,                0,              Button3,        toggleview,     	    {0} },
    { ClkTagBar,                MODKEY,         Button1,        tag,            	    {0} },
    { ClkTagBar,                MODKEY,         Button3,        toggletag,      	    {0} },
    { ClkShutDown,    		0,		Button1,	spawn,			    {.v = powermenucmd } },
};

/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int default_border = 0;   /* to switch back to default border after dynamic border resizing via keybinds */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails,display systray on the 1st monitor,False: display systray on last monitor*/
static int showsystray              = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int usedbar 			      = 1;  		  /* 0 means don't use repobar script */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 means bottom tab */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;
static const int vertpadbar         = 11;
static const int vertpadtab         = 33;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
static const int scalepreview       = 4;
static const int tag_preview        = 1;        /* 1 means enable, 0 is off */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */

static const char *fonts[] = {
  "Source Code Pro:size=10",
  "FiraCode Nerd Font:size=12",
  "remixicon:size=12",
  "Siji:size=12",
  "MaterialIcons:size=10",
  "SourceCodePro Nerd Font:size=10",
};

// theme
#include "themes/minimal-mistakes.h"

static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeTag6]       = { blue,    black,  black },
    [SchemeTag7]       = { red,     black,  black },
    [SchemeTag8]       = { orange,  black,  black },
    [SchemeTag9]       = { green,   black,  black },
    [SchemeTag0]       = { pink,    black,  black },
    [SchemeLayout]     = { gray1,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

static const char *const autostart[] = {
    "autorandr", "--force", "--load", "repowm", NULL,
    "setxkbmap", "-option", "caps:escape", NULL,
    "repomenue_youtube_subs", "-d", NULL,
    "xroot", "-r", "xmenu_desktop", NULL,
    "ckb-next", "--background", NULL,
    "touchpad-indicator", NULL,
    "clipmenu-daemon", NULL,
    "blueman-applet", NULL,
    "numlockx", "on", NULL,
    "xsettingsd", NULL,
    "volumeicon", NULL,
    "nm-applet", NULL,
    // "repobar", NULL,
    NULL
};

/* tagging */
static char *tags[] = {" 1: Terminal", " 2: Editor", " 3: Files", " 4: Graphics", " 5: Music", " 6: WebBrowser", " 7: Mail", " 8: Games", " 9: Chat" , " 10: Settings"};

static const int tagschemes[] = {
    SchemeTag1,
    SchemeTag2,
    SchemeTag3,
    SchemeTag4,
    SchemeTag5,
    SchemeTag6,
    SchemeTag7,
    SchemeTag8,
    SchemeTag9,
    SchemeTag0
};

static const unsigned int ulinepad      = 5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2; /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                        instance      title                 tags mask       switchtotag       iscentered       isfloating   monitor   scratch key */
    //All workspaces
    { "Multimonitorlock-gui.py",	  NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "Pavucontrol",		            NULL,         NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "floatmenu",		              NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "Yad",		                    NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "Peek",                       NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "Snapper",                    NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       0 },
    { "scratchpad_terminal",        NULL,     	  NULL,  		            0,         	    0,          	    1,          	   1,          	-1,       'S' },

    //Workspace 1 Monitor 0
    { "Alacritty",                  NULL,         NULL,                 1 << 0,         1,                0,               0,           0,       0 },
    { "kitty",                      NULL,         NULL,                 1 << 0,         1,                0,               0,           0,       0 },

    //Workspace 2 Monitor 0
    { "Code",                       NULL,         NULL,                 1 << 1,         1,                0,               0,           0,       0 },
    { "nvim",                       NULL,         NULL,                 1 << 1,         1,                0,               0,           0,       0 },

    //Workspace 3 Monitor 0
    { "Nemo",                       NULL,         NULL,                 1 << 2,         1,                0,               0,           0,       0 },

    //Workspace 4 Monitor 0
    { "Ld-linux-x86-64.so.2",       NULL,         NULL,                 1 << 3,         1,                0,               0,           0,       0 }, // inkscape
    { "Gimp",                       NULL,         NULL,                 1 << 3,         1,                0,               0,           0,       0 },

    //Workspace 5 Monitor 0

    //Workspace 6 Monitor 1
    { "firefox",                    NULL,         NULL,                 1 << 5,         1,                0,               0,           1,       0 },

    //Workspace 7 Monitor 1

    //Workspace 8 Monitor 1
    { "Steam",                      NULL,         NULL,                 1 << 7,         1,                0,               0,           1,       0 },
    { "RuneScape",                  NULL,         NULL,                 1 << 7,         1,                0,               0,           1,       0 },

    //Workspace 9 Monitor 1
    { "discord",                    NULL,         NULL,                 1 << 8,         1,                0,               0,           1,       0 },

    //Workspace 10 Monitor 1
    { "PkgBrowser",                 NULL,         NULL,                 1 << 9,         1,                0,               0,           1,       0 },
    { NULL,                         NULL,         "Event Tester",       1 << 9,         1,                0,               0,           1,       0 }, // xev
    { NULL,                         NULL,         "lazygit",            1 << 9,         1,                0,               0,           1,       0 }, // lazygit
    { NULL,                         NULL,         "btop",               1 << 9,         1,                0,               0,           1,       0 }, // btop

};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 4;/* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "functions.h"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[D]",      dwindle },
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

static const Taglayout taglayouts[] = {
    /*  tag		layout */
    {   1,		{.v = &layouts[11]} },
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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL} }

/* repowm commands */
static char repomenumon[2] = "0"; /* component of repomenucmd, manipulated in spawn() */
static const char *layoutmenucmd = "layoutmenu";
static const char *repomenucmd[] = { "repowm-schemas", "repomenucmd", NULL};
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

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "S", "kitty", "--title=scratchpad_terminal", "--class=scratchpad_terminal","--name=scratchpad_terminal", NULL };

static const Launcher launchers[] = {
    /* command     name to display */
    { startmenucmd,        "" },
    { powermenucmd,        "⏻" },
};

/* commands */
static Key keys[] = {
    /* modifier                         chain         key                                function           argument */

    // Keybinds for XFKeys
    { 0,                                -1,           XF86XK_MonBrightnessUp,   			    spawn,   			    {.v = upbright}},
    { 0,                                -1,           XF86XK_MonBrightnessDown, 			    spawn,   			    {.v = downbright}},
    { 0,                                -1,           XF86XK_AudioLowerVolume,  			    spawn,   			    {.v = downvol}},
    { 0,                                -1,           XF86XK_AudioMute,         			    spawn,   		    	{.v = mutevol}},
    { 0,                                -1,           XF86XK_AudioRaiseVolume,  			    spawn,   		    	{.v = upvol}},
    { 0,                                -1,           XF86XK_AudioPlay,         			    spawn,   		    	{.v = playerpause}},
    { 0,                                -1,           XF86XK_AudioPause,        			    spawn,   		    	{.v = playerpause}},
    { 0,                                -1,           XF86XK_AudioNext,         			    spawn,   		    	{.v = playernext}},
    { 0,                                -1,           XF86XK_AudioPrev,         			    spawn,   		    	{.v = playerprevious}},

    //TheRepoClub Custom Keybinds.
    { ControlMask|Mod1Mask,				      -1,         		XK_v,					                    spawn,       			SHCMD("fourmon") },
    { MODKEY,				                    -1,         		XK_o,						                  spawn,       			{.v = systemmonitorcmd} },
    { MODKEY,				                    -1,         		XK_F1,					                  spawn,       			{.v = smartcmd} },
    { MODKEY,				                    -1,         		XK_F2,			                      spawn,       			{.v = clipmenucmd} },
    { MODKEY,				                    -1,         		XK_F3,					                  spawn,       			{.v = instasettings} },
    { MODKEY,				                    -1,         		XK_F4,					                  spawn,       			SHCMD("repomenue_pacman") },
    { MODKEY,				                    -1,         		XK_F5,					                  spawn,       			SHCMD("repomenue_network") },
    { MODKEY,				                    -1,         		XK_F6,					                  spawn,       			SHCMD("repomenue_music") },
    { MODKEY,				                    -1,         		XK_F7,					                  spawn,       			SHCMD("repomenue_youtube_subs") },
    { MODKEY,				                    -1,         		XK_F8,					                  spawn,       			SHCMD("repomenue_kill") },
    { MODKEY|ShiftMask,          	      -1,         	  XK_Return,  		                  spawn,       			{.v = filemanagercmd} },
    { MODKEY|ControlMask,		            -1,         		XK_h,						                  spawn,       			{.v = hypervisorcmd} },
    { MODKEY|ControlMask,		            -1,         		XK_f,						                  spawn,       			{.v = browsercmd} },
    { MODKEY|ControlMask,		            -1,         		XK_e,						                  spawn,       			{.v = editorcmd} },
    { MODKEY|ControlMask,		            -1,         		XK_m,						                  spawn,       			{.v = mailcmd} },
    { MODKEY|ControlMask,		            -1,         		XK_g,						                  spawn,       			{.v = gitcmd} },
    { MODKEY,                           -1,             XK_p,                             spawn,            {.v = passmenucmd} },
    { MODKEY,                           -1,             XK_m,                             spawn,            {.v = repomenucmd} },
    { MODKEY,                           -1,             XK_Return,                        spawn,            {.v = terminalcmd} },
    { ControlMask,                  	  -1,             XK_Return,                        togglescratch,    {.v = scratchpadcmd} },
    { MODKEY|ShiftMask,          	      -1,             XK_e,  					                  spawn,       		  {.v = powermenucmd} },
    { MODKEY|ControlMask,			          -1,         		XK_c,					            	      spawn,       			SHCMD("discord") },
    { MODKEY|ControlMask,		            -1,         		XK_i,					            	      spawn,       			SHCMD("inkscape") },
    { MODKEY|ControlMask,		            -1,         		XK_k,					            	      spawn,       			SHCMD("krita") },
    { MODKEY|ControlMask,		            -1,         		XK_v,					            	      spawn,       			SHCMD("vlc") },
    { MODKEY|ControlMask,	              XK_g,           XK_s,					            	      spawn,       			SHCMD("prime-run steam") },
    { MODKEY|ControlMask,		            XK_g,         	XK_m,					            	      spawn,       			SHCMD("prime-run minecraft-launcher") },
    { MODKEY|ControlMask,		            XK_g,         	XK_r,					            	      spawn,       			SHCMD("prime-run runescape-launcher") },
    { MODKEY|ControlMask,		            -1,         		XK_p,					            	      spawn,       			SHCMD("pkgbrowser") },
    { MODKEY|ControlMask,		            -1,         		XK_u,					            	      spawn,       			SHCMD("pavucontrol") },
    { MODKEY|ShiftMask,			            -1,         		XK_z,					            	      spawn,       		  SHCMD("multimonitorlock-gui") },
    { MODKEY|Mod1Mask,			            -1,         		XK_p,					            	      spawn,       			SHCMD("piper") },

    // screenshot fullscreen and cropped
    { MODKEY,				                    XK_Print,       XK_w,						                  spawn,       			SHCMD("win-shot -w" ) },
    { MODKEY,				                    XK_Print,       XK_s,						                  spawn,       			SHCMD("win-shot -s" ) },
    { MODKEY,				                    XK_Print,       XK_f,						                  spawn,       			SHCMD("win-shot -f" ) },

    // toggle stuff
    { MODKEY,                           -1,             XK_b,                             togglebar,        {0} },
    { MODKEY,                           -1,             XK_s,                             togglesystray,    {0} },
    { MODKEY|ControlMask,               -1,             XK_t,                             togglegaps,       {0} },

    { MODKEY|ShiftMask,                 -1,             XK_space,                         togglefloating,   {0} },
    { MODKEY,                           -1,             XK_f,                             togglefullscr,    {0} },

    { MODKEY|ControlMask,               -1,             XK_w,                             tabmode,          {-1} },
    { MODKEY,                           -1,             XK_j,                             focusstack,       {.i = +1} },
    { MODKEY,                           -1,             XK_k,                             focusstack,       {.i = -1} },
    { MODKEY,                           -1,             XK_i,                             incnmaster,       {.i = +1} },
    { MODKEY,                           -1,             XK_d,                             incnmaster,       {.i = -1} },

    // change m,cfact sizes
    { MODKEY,                           -1,             XK_h,                             setmfact,         {.f = -0.05} },
    { MODKEY,                           -1,             XK_l,                             setmfact,         {.f = +0.05} },
    { MODKEY|ShiftMask,                 -1,             XK_h,                             setcfact,         {.f = +0.25} },
    { MODKEY|ShiftMask,                 -1,             XK_l,                             setcfact,         {.f = -0.25} },
    { MODKEY|ShiftMask,                 -1,             XK_o,                             setcfact,         {.f =  0.00} },

    { MODKEY|ShiftMask,                 -1,             XK_j,                             movestack,        {.i = +1} },
    { MODKEY|ShiftMask,                 -1,             XK_k,                             movestack,        {.i = -1} },
    { MODKEY|ShiftMask,                 -1,             XK_Return,                        zoom,             {0} },
    { MODKEY,                           -1,             XK_Tab,                           view,             {0} },

    // overall gaps
    { MODKEY|ControlMask,               -1,             XK_i,                             incrgaps,         {.i = +1} },
    { MODKEY|ControlMask,               -1,             XK_d,                             incrgaps,         {.i = -1} },

    // inner gaps
    { MODKEY|ShiftMask,                 -1,             XK_i,                             incrigaps,        {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_i,                             incrigaps,        {.i = -1} },

    // outer gaps
    { MODKEY|ControlMask,               -1,             XK_o,                             incrogaps,        {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_o,                             incrogaps,        {.i = -1} },

    // inner+outer hori, vert gaps
    { MODKEY|ControlMask,               -1,             XK_6,                             incrihgaps,       {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_6,                             incrihgaps,       {.i = -1} },
    { MODKEY|ControlMask,               -1,             XK_7,                             incrivgaps,       {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_7,                             incrivgaps,       {.i = -1} },
    { MODKEY|ControlMask,               -1,             XK_8,                             incrohgaps,       {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_8,                             incrohgaps,       {.i = -1} },
    { MODKEY|ControlMask,               -1,             XK_9,                             incrovgaps,       {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,     -1,             XK_9,                             incrovgaps,       {.i = -1} },

    { MODKEY|ControlMask|ShiftMask,     -1,             XK_d,                             defaultgaps,      {0} },

    // layout
    { MODKEY,                           -1,             XK_space,                         setlayout,        {0} },
    { MODKEY|ControlMask,               -1,             XK_comma,                         cyclelayout,      {.i = -1} },
    { MODKEY|ControlMask,               -1,             XK_period,                        cyclelayout,      {.i = +1} },
    { MODKEY,                           -1,             XK_0,                             view,             {.ui = ~0} },
    { MODKEY|ShiftMask,                 -1,             XK_0,                             tag,              {.ui = ~0} },
    { MODKEY,                           -1,             XK_comma,                         focusmon,         {.i = -1} },
    { MODKEY,                           -1,             XK_period,                        focusmon,         {.i = +1} },
    { MODKEY|ShiftMask,                 -1,             XK_comma,                         tagmon,           {.i = -1} },
    { MODKEY|ShiftMask,                 -1,             XK_period,                        tagmon,           {.i = +1} },

    // change border size
    { MODKEY|ShiftMask,                 -1,             XK_minus,                         setborderpx,      {.i = -1} },
    { MODKEY|ShiftMask,                 -1,             XK_p,                             setborderpx,      {.i = +1} },
    { MODKEY|ShiftMask,                 -1,             XK_d,                             setborderpx,      {.i = default_border} },

    // kill window
    { MODKEY,                           -1,             XK_q,                             killclient,       {0} },

    // restart
    { MODKEY|ShiftMask,             	  -1,             XK_r,      	                      quit,   			    {1} },
    { MODKEY|ShiftMask,             	  -1,             XK_q,     	                      quit,             {0} },

    // hide & restore windows
    { MODKEY,                           -1,             XK_w,                             hidewin,          {0} },
    { MODKEY|ShiftMask,                 -1,             XK_w,                             restorewin,       {0} },

    TAGKEYS(                            -1,             XK_1,                             0)
    TAGKEYS(                            -1,             XK_2,                             1)
    TAGKEYS(                            -1,             XK_3,                             2)
    TAGKEYS(                            -1,             XK_4,                             3)
    TAGKEYS(                            -1,             XK_5,                             4)
    TAGKEYS(                            -1,             XK_6,                             5)
    TAGKEYS(                            -1,             XK_7,                             6)
    TAGKEYS(                            -1,             XK_8,                             7)
    TAGKEYS(                            -1,             XK_9,                             8)
    TAGKEYS(                            -1,             XK_0,                             9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkLtSymbol,          0,              Button2,        layoutmenu,     {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = terminalcmd} },

    /* Keep movemouse? */
    /* { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, */

    /* placemouse options, choose which feels more natural:
    *    0 - tiled position is relative to mouse cursor
    *    1 - tiled position is relative to window center
    *    2 - mouse pointer warps to window center
    *
    * The moveorplace uses movemouse or placemouse depending on the floating state
    * of the selected client. Set up individual keybindings for the two if you want
    * to control these separately (i.e. to retain the feature to move a tiled window
    * into a floating position).
    */
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         ControlMask,    Button1,        dragmfact,      {0} },
    { ClkClientWin,         ControlMask,    Button3,        dragcfact,      {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1} },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1} },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};

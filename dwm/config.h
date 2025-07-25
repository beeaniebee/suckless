/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int gappx              = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 17;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Fantasque Sans Mono:size=10", "FantasqueSansMono Nerd Font:size=10" };
static const char dmenufont[]       = "Fantasque Sans Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#3f3b5b";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                   instance  title           tags mask  isfloating  isterminal  noswallow  monitor   float x,y,w,h        floatborderpx */
	{ NULL,                    NULL,     NULL,           0,         0,          0,           0,        -1,       0, 0, 500,500,       0  },
	{ "Qalculate-gtk",         NULL,     NULL,           0,         1,          0,           0,        -1,       50,50,250,150,       3  },
	{ "st",                    NULL,     NULL,           0,         0,          1,           0,        -1,       50,50,500,500,       3  },
	{ "xpad",                  NULL,     NULL,           0,         1,          0,           0,        -1,       100,100,500,300,     3  },
	{ "thunderbird",           NULL,     NULL,           1 << 8,    0,          1,           0,        -1,       50,50,500,500,       3  },
	{ "Cisco AnyConnect Secure Mobility Client",NULL,NULL,0,        1,          1,           0,        -1,       0, 0, 1,  1,         3  },
	{ NULL,                    NULL,     "Event Tester", 0,         0,          0,           1,        -1,       50,50,500,500,       3  }, /* xev */

};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[\\]",     dwindle },
	{ "[@]",      spiral },
	{ "><>",      NULL },	/* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const char *dunstclose[] = { "dunstctl", "close", NULL };
static const char *dunstcloseall[] = { "dunstctl", "close-all", NULL };
static const char *dunstcontext[] = { "dunstctl", "context", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "90x25", "-f", "FantasqueSansMono Nerd Font:size=18", NULL };

static const char *qalccmd[] = { "qalculate-gtk", NULL};
static const char *obsidiancmd[] = { "obsidian", NULL};

static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static const char *upvol[]   = { "/bin/sh", "/etc/scripts/volume", "+", NULL };
static const char *downvol[] = { "/bin/sh", "/etc/scripts/volume", "-", NULL };
static const char *mutevol[] = { "/bin/sh", "/etc/scripts/volume", "m", NULL };

static const char *brightu[] = { "/etc/scripts/bright", "+", NULL };
static const char *brightd[] = { "/etc/scripts/bright", "-", NULL };
static const char *lockcmd[] = { "/usr/local/bin/slock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },        // Launch dmenu (program launcher)
	{ MODKEY,                       XK_n,      spawn,          {.v = dunstclose } },      // Close the most recent dunst notification
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = dunstcloseall } },   // Close all dunst notifications
	{ MODKEY|ShiftMask,             XK_period, spawn,          {.v = dunstcontext } },    // Show context menu for dunst notifications
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },         // Launch terminal
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },   // Toggle the scratchpad terminal
	{ MODKEY,                       XK_q,      spawn,          {.v = qalccmd } },         // Launch Qalculate (calculator)
	{ MODKEY,                       XK_o,      spawn,          {.v = obsidiancmd } },     // Launch Obsidian (note-taking app)
	{ 0,            XF86XK_MonBrightnessUp,    spawn,          {.v = brightu } },         // Increase monitor brightness
	{ 0,            XF86XK_MonBrightnessDown,  spawn,          {.v = brightd } },         // Decrease monitor brightness
	{ 0,            XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },         // Decrease system volume
	{ 0,            XF86XK_AudioMute,          spawn,          {.v = mutevol } },         // Mute/unmute system volume
	{ 0,            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },         // Increase system volume
	{ MODKEY|ControlMask|ShiftMask, XK_l,      spawn,          {.v = lockcmd } },         // Lock the screen
	{ MODKEY,                       XK_b,      togglebar,      {0} },                     // Toggle the visibility of the status bar
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },              // Focus next window in the stack
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },              // Focus previous window in the stack
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },              // Increase number of master windows
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },              // Decrease number of master windows
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },            // Decrease master area size
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },            // Increase master area size
	{ MODKEY,                       XK_Return, zoom,           {0} },                     // Promote focused window to master
	{ MODKEY,                       XK_Tab,    view,           {0} },                     // Switch to previously selected tag
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },                     // Close the focused window
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },      // Set tiling layout
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },      // Set floating layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },      // Set monocle layout
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[3]} },      // Set alternative floating layout
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[4]} },      // Set alternative monocle layout
	{ MODKEY,                       XK_space,  setlayout,      {0} },                     // Toggle between layouts
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                     // Toggle floating mode for focused window
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },             // View all tags
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },             // Tag current window with all tags
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },              // Focus previous monitor
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },              // Focus next monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },              // Move focused window to previous monitor
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },              // Move focused window to next monitor
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },              // Decrease gaps between windows
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },              // Increase gaps between windows
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },              // Reset gaps to zero
	TAGKEYS(                        XK_1,                      0)                          // View/tag windows on tag 1
	TAGKEYS(                        XK_2,                      1)                          // View/tag windows on tag 2
	TAGKEYS(                        XK_3,                      2)                          // View/tag windows on tag 3
	TAGKEYS(                        XK_4,                      3)                          // View/tag windows on tag 4
	TAGKEYS(                        XK_5,                      4)                          // View/tag windows on tag 5
	TAGKEYS(                        XK_6,                      5)                          // View/tag windows on tag 6
	TAGKEYS(                        XK_7,                      6)                          // View/tag windows on tag 7
	TAGKEYS(                        XK_8,                      7)                          // View/tag windows on tag 8
	TAGKEYS(                        XK_9,                      8)                          // View/tag windows on tag 9
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },                     // Quit dwm (clean exit)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },                     // Force quit dwm (quick exit)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CozetteVector:size=9" };
static const char dmenufont[]       = "monospace:size=10";
static const int horizpadbar = 10;
static const int vertpadbar = 5;

static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */

static const char col_gray1[]       = "#121212"; //  1d2021 050505 161616 100914 prev #00020e
static const unsigned int gappx     = 10;        /* gaps between windows */

static const char col_gray2[]       = "#665c54"; // 6272a4 504945 ab7ac0 prev a45a30 df4418  c5cce1 #4f10d6 #ffb86c #fabd2f
static const char col_gray3[]       = "#bdae93"; // prev d5c4a1 #ff79c6 % prev #808080
static const char col_gray4[]       = "#d5c4a1"; // 6272a4 427b58 d65d0e ab7ac0 a45a30 4eb500 prev f72504 #ffb86c & prev #6ccc8f & 4b78ff
static const char col_gray5[]           = "#181818";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, // prev col_cyan
    [SchemeSel]  = { col_gray4, col_gray5,  col_gray2  },
	
	[SchemeWarn] =   { "#83a598", col_gray1, col_gray2 },
	[SchemeUrgent]=  { "#8ec07c", col_gray1,    col_gray2 },
	{ "#fb7e14", col_gray1, col_gray2},
	{ "#b8bb26", col_gray1, col_gray2},
	{ "#8ec07c", col_gray1, col_gray2},
	{ "#fabd2f", col_gray1, col_gray2},
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st","zsh" ,NULL };

static const char *upvol[]   = { "amixer", "set", "Master", "5%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "5%-",     NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle",  NULL };
static const char *lock[] = {"slock" , NULL };
static const char *sstool[] = {"/home/enginar/git-repos/dwmginar/dmenu/scripts/screenshot", NULL};
static const char *ranger[] = {"st", "-e", "ranger", "/home/enginar/", NULL};
static const char *ytmenu[] = {"ytfzf", "-D", NULL};
static const char *playpause[] = { "playerctl", "--player=cmus,spotify" ,"play-pause", NULL };
static const char *next[] = { "playerctl", "--player=cmus,spotify" ,"next", NULL};
static const char *prev[] = { "playerctl", "--player=cmus,spotify" , "previous", NULL};
static const char *j4dmenu[] = {"j4-dmenu-desktop", NULL};
static const char *brup[] = {"lxqt-backlight_backend", "--inc", "25", NULL};
static const char *brdown[] = {"lxqt-backlight_backend", "--dec", "25", NULL};
static const char *cmdprintscreen[]  = {  "/usr/local/bin/scrall", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
	        // { MODKEY|ShiftMask,                          XK_s,      spawn                   { .v = sstool } },
        // { MODKEY|ShiftMask,                             XK_c,           spawn,                  { .v = clipmenucmd} },
        { MODKEY|ShiftMask,                     XK_p,      spawn,                  { .v = j4dmenu } },
        { MODKEY|ShiftMask,                             XK_l,      spawn,                  { .v = lock    } },

        { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = sstool   } },
        { MODKEY|ShiftMask,                             XK_y,      spawn,                  {.v = ytmenu   } },
        { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,             XK_F4,      killclient,     {0} },
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
	    { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
        { 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
        { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
        { 0,                       XF86XK_AudioPlay, spawn, {.v = playpause} },
        { 0,                       XF86XK_AudioNext, spawn, {.v = next } },
        { 0,                       XF86XK_AudioPrev, spawn, {.v = prev } },
        { 0,                       XF86XK_MonBrightnessDown, spawn, {.v = brdown } },
        { 0,                       XF86XK_MonBrightnessUp, spawn, {.v = brup   } }

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	// { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


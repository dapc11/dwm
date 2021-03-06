/* appearance */
static const unsigned int borderpx  = 1;            /* border pixel of windows */
static const unsigned int snap      = 32;           /* snap pixel */
static const unsigned int gappih    = 5;            /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;           /* vert inner gap between windows */
static const unsigned int gappoh    = 10;           /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;           /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;            /* 1 means swallow floating windows by default */
static const int smartgaps          = 1;            /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;            /* 0 means no bar */
static const int topbar             = 1;            /* 0 means bottom bar */

/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab      = showtab_auto;       /* Default tab bar show mode */
static const int toptab       = False;              /* False means bottom tab bar */

static const char *fonts[]    = { "DejaVu Sans:size=12" };
static char dmenufont[]       = "DejaVu Sans Mono:size=11";
/* fallback colors */
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#770000";
static char selbgcolor[]      = "#005577";
static char statbgcolor[]     = "#eeeeee";
static char statbordercolor[] = "#770000";
static char statfgcolor[]     = "#005577";
static char *colors[][3] = {
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { statfgcolor, statbgcolor, statbordercolor },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "spterm", "-d", "120", "34", NULL };
const char *spcmd2[] = {"alacritty", "--class", "spcalc", "-d", "50", "20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spranger",    spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/*  class                        instance   title  tags mask  isfloating  isterminal  noswallow  monitor  */
{   "Gimp",                      NULL,      NULL,  1 << 8,    0,          0,          0,         -1  },
{   "firefox",                   NULL,      NULL,  1 << 1,    0,          0,          0,         -1  },
{   "Firefox",                   NULL,      NULL,  1 << 1,    0,          0,          0,         -1  },
{   "google-chrome",             NULL,      NULL,  1 << 1,    0,          0,          0,         -1  },
{   "Google-chrome",             NULL,      NULL,  1 << 1,    0,          0,          0,         -1  },
{   "code-oss",                  NULL,      NULL,  1 << 3,    0,          0,          0,         -1  },
{   "Code",                      NULL,      NULL,  1 << 3,    0,          0,          0,         -1  },
{   "Thunderbird",               NULL,      NULL,  1 << 1,    0,          0,          0,         0   },
{   "Evolution",                 NULL,      NULL,  1 << 1,    0,          0,          0,         0   },
{   "Evolution-alarm-notify",    NULL,      NULL,  1,         0,          0,          0,         0   },
{   "Microsoft Teams - Preview", NULL,      NULL,  1,         0,          0,          0,         0   },
{   "PulseUi",                   NULL,      NULL,  1 << 2,    0,          0,          0,         0   },
{   "Spotify",                   NULL,      NULL,  1 << 3,    0,          0,          0,         0   },
{   "Nautilus",                  NULL,      NULL,  0,         0,          0,          0,         -1  },
{   "Thunar",                    NULL,      NULL,  0,         0,          0,          0,         -1  },
{   NULL,                        "spterm",  NULL,  SPTAG(0),  1,          1,          0,         -1  },
{   NULL,                        "spterm",  NULL,  SPTAG(0),  1,          1,          0,         -1  },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1               /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    { "[]=",  tile },                   /* Default: Master on left, slaves on right */
    { "[M]",  monocle },                /* All windows on top of eachother */
    { "TTT",  bstack },                 /* Master on top, slaves on bottom */
    { "[@]",  spiral },                 /* Fibonacci spiral */
    { "[\\]", dwindle },                /* Decreasing in size right and leftward */
    { "H[]",  deck },                   /* Master on left, slaves in monocle-like mode on right */
    { "|M|",  centeredmaster },         /* Master in middle, slaves on sides */
    { ">M>",  centeredfloatingmaster }, /* Same but master floats */
    { "><>",  NULL },                   /* no layout function means floating behavior */
    { NULL,   NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, XK_Left,    ACTION##stack,    {.i = INC(+1) } }, \
    { MOD, XK_Right,   ACTION##stack,    {.i = INC(-1) } }, \
    { MOD, XK_j,       ACTION##stack,    {.i = INC(+1) } }, \
    { MOD, XK_k,       ACTION##stack,    {.i = INC(-1) } }, \
    { MOD, XK_v,       ACTION##stack,    {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
/*static const char *termcmd[]  = { "st", NULL };*/
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
    /* modifier                 key                       function        argument */
    STACKKEYS(MODKEY,                                     focus)
    STACKKEYS(MODKEY|ShiftMask,                           push)
    TAGKEYS(                    XK_1,                     0)
    TAGKEYS(                    XK_2,                     1)
    TAGKEYS(                    XK_3,                     2)
    TAGKEYS(                    XK_4,                     3)
    TAGKEYS(                    XK_5,                     4)
    TAGKEYS(                    XK_6,                     5)
    TAGKEYS(                    XK_7,                     6)
    TAGKEYS(                    XK_8,                     7)
    TAGKEYS(                    XK_9,                     8)
    { MODKEY,                   XK_0,                     view,           {.ui = ~0} },
    { MODKEY,                   XK_BackSpace,             spawn,          SHCMD("sysact") },
    { MODKEY|ShiftMask,         XK_BackSpace,             spawn,          SHCMD("sysact") },
    { MODKEY,                   XK_Tab,                   view,           {0} },
    { MODKEY,                   XK_q,                     killclient,     {0} },
    { MODKEY,                   XK_w,                     spawn,          SHCMD("google-chrome") },
    { MODKEY,                   XK_r,                     spawn,          SHCMD("nautilus") },
    { MODKEY,                   XK_t,                     setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,         XK_t,                     setlayout,      {.v = &layouts[1]} },
    { MODKEY,                   XK_y,                     setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,         XK_y,                     setlayout,      {.v = &layouts[3]} },
    { MODKEY,                   XK_u,                     setlayout,      {.v = &layouts[4]} },
    { MODKEY|ShiftMask,         XK_u,                     setlayout,      {.v = &layouts[5]} },
    { MODKEY,                   XK_i,                     setlayout,      {.v = &layouts[6]} },
    { MODKEY|ShiftMask,         XK_i,                     setlayout,      {.v = &layouts[7]} },
    { MODKEY|ShiftMask,         XK_f,                     setlayout,      {.v = &layouts[8]} },
    { MODKEY,                   XK_o,                     incnmaster,     {.i = +1} },
    { MODKEY|ShiftMask,         XK_o,                     incnmaster,     {.i = -1} },
    { MODKEY,                   XK_a,                     togglegaps,     {0} },
    { MODKEY|ShiftMask,         XK_a,                     defaultgaps,    {0} },
    { MODKEY,                   XK_s,                     togglesticky,   {0} },
    { MODKEY,                   XK_f,                     togglefullscr,  {0} },
    { MODKEY,                   XK_h,                     setmfact,       {.f = -0.05} },
    { MODKEY,                   XK_l,                     setmfact,       {.f = +0.05} },
    { MODKEY,                   XK_apostrophe,            togglescratch,  {.ui = 1} },
    { MODKEY,                   XK_Return,                spawn,          {.v = termcmd} },
    { MODKEY|ShiftMask,         XK_Return,                togglescratch,  {.ui = 0} },
    { MODKEY,                   XK_z,                     incrgaps,       {.i = +2} },
    { MODKEY,                   XK_x,                     incrgaps,       {.i = -2} },
    { MODKEY,                   XK_s,                     spawn,          SHCMD("rofi -show window") },
    { MODKEY,                   XK_d,                     spawn,          SHCMD("rofi -show drun -display-drun "" -modi drun") },
    { MODKEY|ControlMask,       XK_Left,                  focusmon,       {.i = -1} },
    { MODKEY|ShiftMask,         XK_Left,                  tagmon,         {.i = -1} },
    { MODKEY|ControlMask,       XK_Right,                 focusmon,       {.i = +1} },
    { MODKEY|ShiftMask,         XK_Right,                 tagmon,         {.i = +1} },
    { MODKEY,                   XK_space,                 zoom,           {0} },
    { MODKEY|ShiftMask,         XK_space,                 togglefloating, {0} },
    { 0,                        XF86XK_DOS,               spawn,          SHCMD("alacritty") },
    { 0,                        XF86XK_PowerOff,          spawn,          SHCMD("sysact") },
    { MODKEY,                   XK_n,                     spawn,          SHCMD("nightmode") },
    { 0,                        XF86XK_AudioMute,         spawn,          SHCMD("pactl set-sink-mute 0 toggle") },
    { 0,                        XF86XK_AudioLowerVolume,  spawn,          SHCMD("pactl -- set-sink-volume 0 -10%") },
    { 0,                        XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pactl -- set-sink-volume 0 +10%") },
    { 0,                        XF86XK_AudioPrev,         spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
    { 0,                        XF86XK_AudioPlay,         spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
    { 0,                        XF86XK_AudioNext,         spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },
    { 0,                        XF86XK_MonBrightnessUp,   spawn,          SHCMD("dimmer -i") },
    { 0,                        XF86XK_MonBrightnessDown, spawn,          SHCMD("dimmer -d") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         MODKEY,         Button4,        incrgaps,       {.i = +1} },
    { ClkClientWin,         MODKEY,         Button5,        incrgaps,       {.i = -1} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,            0,              Button4,        shiftview,      {.i = -1} },
    { ClkTagBar,            0,              Button5,        shiftview,      {.i = 1} },
    { ClkRootWin,           0,              Button2,        togglebar,      {0} },
};

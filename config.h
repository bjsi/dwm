/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 17;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 17;       /* vert inner gap between windows */
static const unsigned int gappoh    = 17;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 17;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Mono:size=14:antialias=true"  };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char pink[]            = "#ff1493";
static const char blue[]            = "#0000FF";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2  },
    [SchemeSel]  = { col_gray4, col_cyan,  blue   },

};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"  };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "discord",     NULL,       NULL,       1 << 3,            0,           -1  },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile  },    /* first entry is default */
    { "[M]",      monocle  },
    { "[D]",      deck  },
    { ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG}  }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG}  }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG}  }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG}  },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL  }  }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL  };
static const char *termcmd[]  = { "st", NULL  };

#include <X11/XF86keysym.h>
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd }  },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd }  },
    { MODKEY,                       XK_w,      spawn,          SHCMD("qutebrowser")  },
    { MODKEY,                       XK_b,      togglebar,      {0}  },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 }  },
    { MODKEY|ShiftMask,             XK_j,      pushdown,       {0}  },
    { MODKEY|ShiftMask,             XK_k,      pushup,         {0}  },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 }  },
    { MODKEY,                       XK_h,      focusmaster,    {0}  },
    { MODKEY,                       XK_y,      setmfact,       {.f = -0.05}  },
    { MODKEY,                       XK_o,      setmfact,       {.f = +0.05}  },
    { MODKEY|ShiftMask,             XK_h,      zoom,           {0}  },
    { MODKEY,                       XK_Tab,    view,           {0}  },
    { MODKEY,                       XK_c,      killclient,     {0}  },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]}  },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]}  },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[2]}  },
    { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[3]}  },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 }  },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 }  },
    { 0, XF86XK_AudioMute,      spawn,      SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")   },
    { 0, XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)")   },
    { 0, XF86XK_AudioLowerVolume,   spawn,      SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)")   },
    { 0, XF86XK_AudioPrev,      spawn,      SHCMD("mpc prev")   },
    { 0, XF86XK_AudioNext,      spawn,      SHCMD("mpc next")   },
    { 0, XF86XK_AudioPause,     spawn,      SHCMD("mpc pause")   },
    { 0, XF86XK_AudioPlay,      spawn,      SHCMD("mpc play")   },
    { 0, XF86XK_AudioStop,      spawn,      SHCMD("mpc stop")   },
    { 0, XF86XK_AudioRewind,    spawn,      SHCMD("mpc seek -10")   },
    { 0, XF86XK_AudioForward,   spawn,      SHCMD("mpc seek +10")   },
    { 0, XF86XK_MonBrightnessUp,    spawn,      SHCMD("light -A 5")  },
    { 0, XF86XK_MonBrightnessDown,  spawn,      SHCMD("light -U 5")  },
    TAGKEYS(                        XK_1,                      0 )
        TAGKEYS(                        XK_2,                      1 )
        TAGKEYS(                        XK_3,                      2 )
        TAGKEYS(                        XK_4,                      3 )
        TAGKEYS(                        XK_5,                      4 )
        TAGKEYS(                        XK_6,                      5 )
        TAGKEYS(                        XK_7,                      6 )
        TAGKEYS(                        XK_8,                      7 )
        TAGKEYS(                        XK_9,                      8 )
        { MODKEY|ShiftMask,             XK_q,      quit,           {0}  },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0}  },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]}  },
    { ClkWinTitle,          0,              Button2,        zoom,           {0}  },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd }  },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0}  },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0}  },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0}  },
    { ClkTagBar,            0,              Button1,        view,           {0}  },
    { ClkTagBar,            0,              Button3,        toggleview,     {0}  },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0}  },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0}  },

};


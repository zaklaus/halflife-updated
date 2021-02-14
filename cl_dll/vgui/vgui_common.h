/***
*
* Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
* This product contains software technology licensed from Id
* Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
* All Rights Reserved.
*
* Use, distribution, and modification of this source code and/or resulting
* object code is restricted to non-commercial enhancements to products from
* Valve LLC.All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/
#pragma once

#include <VGUI_BitmapTGA.h>

#define PC_RANDOM     10
#define PC_LASTCLASS  10
#define PC_UNDEFINED   0
#define MENU_DEFAULT				1
#define MENU_TEAM 					2

#define MENU_MAPBRIEFING			4
#define MENU_INTRO 					5
#define MENU_SPECHELP				9

//#define MAX_TEAMNAME_SIZE		64
#define MAX_BUTTON_SIZE			32
#define MAX_COMMAND_SIZE	256


// Command Menu positions 
#define MAX_MENUS				80
#define MAX_BUTTONS				100

#define BUTTON_SIZE_Y			YRES(30)
#define CMENU_SIZE_X			XRES(160)

#define SUBMENU_SIZE_X			(CMENU_SIZE_X / 8)
#define SUBMENU_SIZE_Y			(BUTTON_SIZE_Y / 6)

#define CMENU_TOP				(BUTTON_SIZE_Y * 4)

// Map Briefing Window
#define MAPBRIEF_INDENT			30

// Team Menu
#define TMENU_INDENT_X			(30 * ((float)ScreenHeight / 640))
#define TMENU_HEADER			100
#define TMENU_SIZE_X			(ScreenWidth - (TMENU_INDENT_X * 2))
#define TMENU_SIZE_Y			(TMENU_HEADER + BUTTON_SIZE_Y * 7)
#define TMENU_PLAYER_INDENT		(((float)TMENU_SIZE_X / 3) * 2)
#define TMENU_INDENT_Y			(((float)ScreenHeight - TMENU_SIZE_Y) / 2)

// Class Menu
#define CLMENU_INDENT_X			(30 * ((float)ScreenHeight / 640))
#define CLMENU_HEADER			100
#define CLMENU_SIZE_X			(ScreenWidth - (CLMENU_INDENT_X * 2))
#define CLMENU_SIZE_Y			(CLMENU_HEADER + BUTTON_SIZE_Y * 11)
#define CLMENU_PLAYER_INDENT	(((float)CLMENU_SIZE_X / 3) * 2)
#define CLMENU_INDENT_Y			(((float)ScreenHeight - CLMENU_SIZE_Y) / 2)


#define HIDE_TEXTWINDOW		0
#define SHOW_MAPBRIEFING	1
#define SHOW_MOTD			3
#define SHOW_SPECHELP		4

// Arrows
enum
{
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
};

vgui::BitmapTGA* LoadTGAForRes(const char* pImageName);

extern int iTeamColors[5][3];
extern int iNumberOfTeamColors;


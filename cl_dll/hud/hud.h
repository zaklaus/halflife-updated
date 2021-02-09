/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once

#define FOG_LIMIT 30000
#define RGB_YELLOWISH 0x00FFA000 //255,160,0
#define RGB_REDISH 0x00FF1010 //255,160,0
#define RGB_GREENISH 0x0000A000 //0,160,0

#include "cl_dll.h"

#define DHN_DRAWZERO 1
#define DHN_2DIGITS  2
#define DHN_3DIGITS  4
#define MIN_ALPHA	 100	

#define		HUDELEM_ACTIVE	1


#include "global_consts.h"

typedef struct cvar_s cvar_t;

#define	MAX_MOTD_LENGTH				1536

#define FADE_TIME 100


struct extra_player_info_t 
{
	short frags;
	short deaths;
	short playerclass;
	short health; // UNUSED currently, spectator UI would like this
	bool dead; // UNUSED currently, spectator UI would like this
	short teamnumber;
	char teamname[MAX_TEAM_NAME];
};

struct team_info_t 
{
	char name[MAX_TEAM_NAME];
	short frags;
	short deaths;
	short ping;
	short packetloss;
	short ownteam;
	short players;
	int already_drawn;
	int scores_overriden;
	int teamnumber;
};

#include "player_info.h"


//LRC - for the moment, skymode has only two settings
#define SKY_OFF 0
#define SKY_ON_DRAWING  2
#define SKY_ON  1


extern int g_iPlayerClass;
extern int g_iTeamNumber;
extern int g_iInventory[MAX_ITEMS];	//AJH Inventory system
extern int g_iUser1;
extern int g_iUser2;
extern int g_iUser3;

struct FogSettings
{
	float fogColor[3];
	float startDist;
	float endDist;
};
extern FogSettings g_fog;
extern FogSettings g_fogPreFade;
extern FogSettings g_fogPostFade;
extern float g_fFogFadeDuration;
extern float g_fFogFadeFraction;

//========= Copyright � 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
#pragma once

#include "hud/hud.h"
#include "hud/CHud.h"
#include "pm_defs.h"
#include "cl_util.h"
#include "event_api.h"
#include "r_studioint.h"
#include "in_defs.h"

// defaults for clientinfo messages
#define	DEFAULT_VIEWHEIGHT	28
#define VEC_DUCK_VIEW 12

#define FTENT_FADEOUT			0x00000080

#define DMG_GENERIC			0			// generic damage was done
#define DMG_CRUSH			(1 << 0)	// crushed by falling or moving object
#define DMG_BULLET			(1 << 1)	// shot
#define DMG_SLASH			(1 << 2)	// cut, clawed, stabbed
#define DMG_BURN			(1 << 3)	// heat burned
#define DMG_FREEZE			(1 << 4)	// frozen
#define DMG_FALL			(1 << 5)	// fell too far
#define DMG_BLAST			(1 << 6)	// explosive blast damage
#define DMG_CLUB			(1 << 7)	// crowbar, punch, headbutt
#define DMG_SHOCK			(1 << 8)	// electric shock
#define DMG_SONIC			(1 << 9)	// sound pulse shockwave
#define DMG_ENERGYBEAM		(1 << 10)	// laser or other high energy beam 
#define DMG_NEVERGIB		(1 << 12)	// with this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB		(1 << 13)	// with this bit OR'd in, any damage type can be made to gib victims upon death.

// time-based damage
//mask off TF-specific stuff too
#define DMG_TIMEBASED		(~(0xff003fff))	// mask for time-based damage

#define DMG_DROWN			(1 << 14)	// Drowning
#define DMG_FIRSTTIMEBASED  DMG_DROWN

#define DMG_PARALYZE		(1 << 15)	// slows affected creature down
#define DMG_NERVEGAS		(1 << 16)	// nerve toxins, very bad
#define DMG_POISON			(1 << 17)	// blood poisioning
#define DMG_RADIATION		(1 << 18)	// radiation exposure
#define DMG_DROWNRECOVER	(1 << 19)	// drowning recovery
#define DMG_ACID			(1 << 20)	// toxic chemicals or acid burns
#define DMG_SLOWBURN		(1 << 21)	// in an oven
#define DMG_SLOWFREEZE		(1 << 22)	// in a subzero freezer
#define DMG_MORTAR			(1 << 23)	// Hit by air raid (done to distinguish grenade from mortar)

//TF ADDITIONS
#define DMG_IGNITE			(1 << 24)	// Players hit by this begin to burn
#define DMG_RADIUS_MAX		(1 << 25)	// Radius damage with this flag doesn't decrease over distance
#define DMG_RADIUS_QUAKE	(1 << 26)	// Radius damage is done like Quake. 1/2 damage at 1/2 radius.
#define DMG_IGNOREARMOR		(1 << 27)	// Damage ignores target's armor
#define DMG_AIMED			(1 << 28)   // Does Hit location damage
#define DMG_WALLPIERCING	(1 << 29)	// Blast Damages ents through walls

#define DMG_CALTROP				(1<<30)
#define DMG_HALLUC				(1<<31)

extern engine_studio_api_t IEngineStudio;
extern cvar_t* cl_lw;
extern int tracerCount[32];

#define SND_CHANGE_PITCH	(1<<7)		// duplicated in protocol.h change sound pitch

// bullet types
typedef	enum
{
	BULLET_NONE = 0,
	BULLET_PLAYER_9MM, // glock
	BULLET_PLAYER_MP5, // mp5
	BULLET_PLAYER_357, // python
	BULLET_PLAYER_BUCKSHOT, // shotgun
	BULLET_PLAYER_CROWBAR, // crowbar swipe

	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
} Bullet;

// Some of these are HL/TFC specific?
struct cl_entity_s* GetEntity(int idx);
struct cl_entity_s* GetViewEntity();

void EV_CreateTracer(float* start, float* end);
qboolean EV_IsPlayer(int idx);
qboolean EV_IsLocal(int idx);
void EV_GetGunPosition(struct event_args_s* args, float* pos, float* origin);
void EV_EjectBrass(float* origin, float* velocity, float rotation, int model, int soundtype);
void EV_GetDefaultShellInfo(struct event_args_s* args, float* origin, float* velocity, float* ShellVelocity, float* ShellOrigin, float* forward, float* right, 
                            float* up, float forwardScale, float upScale, float rightScale);
void EV_MuzzleFlash();

void EV_HLDM_GunshotDecalTrace(pmtrace_t* pTrace, char* decalName);
void EV_HLDM_DecalGunshot(pmtrace_t* pTrace, int iBulletType);
int EV_HLDM_CheckTracer(int idx, float* vecSrc, float* end, float* forward, float* right, int iBulletType, int iTracerFreq, int* tracerCount);
void EV_HLDM_FireBullets(int idx, float* forward, float* right, float* up, int cShots, float* vecSrc, float* vecDirShooting, float flDistance, int iBulletType, int iTracerFreq, int* tracerCount, float flSpreadX, float flSpreadY);

void V_PunchAxis(int axis, float punch);
void VectorAngles(const float* forward, float* angles);
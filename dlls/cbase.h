/***
*
*    Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*    
*    This product contains software technology licensed from Id 
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*    All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once

#include "saverestore.h"
#include "Platform.h"

// C functions for external declarations that call the appropriate C++ methods

#define EXPORT DLLEXPORT

extern "C" DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS* pFunctionTable, int interfaceVersion);
extern "C" DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion);

extern int DispatchSpawn(edict_t* pent);
extern void DispatchKeyValue(edict_t* pentKeyvalue, KeyValueData* pkvd);
extern void DispatchTouch(edict_t* pentTouched, edict_t* pentOther);
extern void DispatchUse(edict_t* pentUsed, edict_t* pentOther);
extern void DispatchThink(edict_t* pent);
extern void DispatchBlocked(edict_t* pentBlocked, edict_t* pentOther);
extern void DispatchSave(edict_t* pent, SAVERESTOREDATA* pSaveData);
extern int DispatchRestore(edict_t* pent, SAVERESTOREDATA* pSaveData, int globalEntity);
extern void DispatchObjectCollsionBox(edict_t* pent);
extern void SaveWriteFields(SAVERESTOREDATA* pSaveData, const char* pname, void* pBaseData, TYPEDESCRIPTION* pFields, int fieldCount);
extern void SaveReadFields(SAVERESTOREDATA* pSaveData, const char* pname, void* pBaseData, TYPEDESCRIPTION* pFields, int fieldCount);
extern void SaveGlobalState(SAVERESTOREDATA* pSaveData);
extern void RestoreGlobalState(SAVERESTOREDATA* pSaveData);
extern void ResetGlobalState(void);

#define    SF_NORESPAWN    ( 1 << 30 )// !!!set this bit on guns and stuff that should never respawn.


// Ugly technique to override base member functions
// Normally it's illegal to cast a pointer to a member function of a derived class to a pointer to a
// member function of a base class.  static_cast is a sleezy way around that problem.

#ifdef _DEBUG

#define SetThink( a ) ThinkSet( static_cast <void (CBaseEntity::*)(void)> (a), #a )
#define SetTouch( a ) TouchSet( static_cast <void (CBaseEntity::*)(CBaseEntity *)> (a), #a )
#define SetUse( a ) UseSet( static_cast <void (CBaseEntity::*)(    CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )> (a), #a )
#define SetBlocked( a ) BlockedSet( static_cast <void (CBaseEntity::*)(CBaseEntity *)> (a), #a )

#else

#define SetThink( a ) m_pfnThink = static_cast <void (CBaseEntity::*)(void)> (a)
#define SetTouch( a ) m_pfnTouch = static_cast <void (CBaseEntity::*)(CBaseEntity *)> (a)
#define SetUse( a ) m_pfnUse = static_cast <void (CBaseEntity::*)( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )> (a)
#define SetBlocked( a ) m_pfnBlocked = static_cast <void (CBaseEntity::*)(CBaseEntity *)> (a)

#endif

typedef struct locksounds // sounds that doors and buttons make when locked/unlocked
{
    string_t sLockedSound; // sound a door makes when it's locked
    string_t sLockedSentence; // sentence group played when door is locked
    string_t sUnlockedSound; // sound a door makes when it's unlocked
    string_t sUnlockedSentence; // sentence group played when door is unlocked

    int iLockedSentence; // which sentence in sentence group to play next
    int iUnlockedSentence; // which sentence in sentence group to play next

    float flwaitSound; // time delay between playing consecutive 'locked/unlocked' sounds
    float flwaitSentence; // time delay between playing consecutive sentences
    BYTE bEOFLocked; // true if hit end of list of locked sentences
    BYTE bEOFUnlocked; // true if hit end of list of unlocked sentences
} locksound_t;

void PlayLockSounds(entvars_t* pev, locksound_t* pls, int flocked, int fbutton);

// todo: constants
#define MAX_MULTI_TARGETS    16 // maximum number of targets a single multi_manager entity may be assigned.
#define MS_MAX_TARGETS 32


// people gib if their health is <= this at the time of death
#define    GIB_HEALTH_VALUE    -30


#define bits_CAP_DUCK             ( 1 << 0  )  // crouch
#define bits_CAP_JUMP             ( 1 << 1  )  // jump/leap
#define bits_CAP_STRAFE           ( 1 << 2  )  // strafe ( walk/run sideways)
#define bits_CAP_SQUAD            ( 1 << 3  )  // can form squads
#define bits_CAP_SWIM             ( 1 << 4  )  // proficiently navigate in water
#define bits_CAP_CLIMB            ( 1 << 5  )  // climb ladders/ropes
#define bits_CAP_USE              ( 1 << 6  )  // open doors/push buttons/pull levers
#define bits_CAP_HEAR             ( 1 << 7  )  // can hear forced sounds
#define bits_CAP_AUTO_DOORS       ( 1 << 8  )  // can trigger auto doors
#define bits_CAP_OPEN_DOORS       ( 1 << 9  )  // can open manual doors
#define bits_CAP_TURN_HEAD        ( 1 << 10 )  // can turn head, always bone controller 0

#define bits_CAP_RANGE_ATTACK1    ( 1 << 11 )  // can do a range attack 1
#define bits_CAP_RANGE_ATTACK2    ( 1 << 12 )  // can do a range attack 2
#define bits_CAP_MELEE_ATTACK1    ( 1 << 13 )  // can do a melee attack 1
#define bits_CAP_MELEE_ATTACK2    ( 1 << 14 )  // can do a melee attack 2

#define bits_CAP_FLY              ( 1 << 15 )  // can fly, move all around

#define bits_CAP_DOORS_GROUP      (bits_CAP_USE | bits_CAP_AUTO_DOORS | bits_CAP_OPEN_DOORS)

// used by suit voice to indicate damage sustained and repaired type to player

// instant damage

#define DMG_GENERIC                     0      // generic damage was done
#define DMG_CRUSH                 ( 1 << 0  )  // crushed by falling or moving object
#define DMG_BULLET                ( 1 << 1  )  // shot
#define DMG_SLASH                 ( 1 << 2  )  // cut, clawed, stabbed
#define DMG_BURN                  ( 1 << 3  )  // heat burned
#define DMG_FREEZE                ( 1 << 4  )  // frozen
#define DMG_FALL                  ( 1 << 5  )  // fell too far
#define DMG_BLAST                 ( 1 << 6  )  // explosive blast damage
#define DMG_CLUB                  ( 1 << 7  )  // crowbar, punch, headbutt
#define DMG_SHOCK                 ( 1 << 8  )  // electric shock
#define DMG_SONIC                 ( 1 << 9  )  // sound pulse shockwave
#define DMG_ENERGYBEAM            ( 1 << 10 )  // laser or other high energy beam
#define DMG_NEVERGIB              ( 1 << 12 )  // with this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB             ( 1 << 13 )  // with this bit OR'd in, any damage type can be made to gib victims upon death.
#define DMG_DROWN                 ( 1 << 14 )  // Drowning
// time-based damage
#define DMG_TIMEBASED             (~(0x3fff))  // mask for time-based damage

#define DMG_PARALYZE              ( 1 << 15 )  // slows affected creature down
#define DMG_NERVEGAS              ( 1 << 16 )  // nerve toxins, very bad
#define DMG_POISON                ( 1 << 17 )  // blood poisioning
#define DMG_RADIATION             ( 1 << 18 )  // radiation exposure
#define DMG_DROWNRECOVER          ( 1 << 19 )  // drowning recovery
#define DMG_ACID                  ( 1 << 20 )  // toxic chemicals or acid burns
#define DMG_SLOWBURN              ( 1 << 21 )  // in an oven
#define DMG_SLOWFREEZE            ( 1 << 22 )  // in a subzero freezer
#define DMG_MORTAR                ( 1 << 23 )  // Hit by air raid (done to distinguish grenade from mortar)

// these are the damage types that are allowed to gib corpses
#define DMG_GIB_CORPSE            ( DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB )

// these are the damage types that have client hud art
#define DMG_SHOWNHUD              (DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK)

// NOTE: tweak these values based on gameplay feedback:

#define PARALYZE_DURATION     2        // number of 2 second intervals to take damage
#define PARALYZE_DAMAGE       1.0        // damage to take each 2 second interval

#define NERVEGAS_DURATION     2
#define NERVEGAS_DAMAGE       5.0

#define POISON_DURATION       5
#define POISON_DAMAGE         2.0

#define RADIATION_DURATION    10
#define RADIATION_DAMAGE      1.0

#define ACID_DURATION         2
#define ACID_DAMAGE           5.0

#define SLOWBURN_DURATION     2
#define SLOWBURN_DAMAGE       1.0

#define SLOWFREEZE_DURATION   2
#define SLOWFREEZE_DAMAGE     1.0

// when calling KILLED(), a value that governs gib behavior is expected to be
// one of these three values
#define GIB_NORMAL            0  // gib if entity was overkilled
#define GIB_NEVER             1  // never gib, no matter how much death damage is done ( freezing, etc )
#define GIB_ALWAYS            2  // always gib ( Houndeye Shock, Barnacle Bite )

const char* ButtonSound(int sound); // get string of button sound number

void DoSpark(entvars_t* pev, const Vector& location);

//
// Converts a entvars_t * to a class pointer
// It will allocate the class and entity if necessary
//
template <class T>
T* GetClassPtr(T* a)
{
    entvars_t* pev = (entvars_t*)a;

    // allocate entity if necessary
    if (pev == NULL)
        pev = VARS(CREATE_ENTITY());

    // get the private data
    a = (T*)GET_PRIVATE(ENT(pev));

    if (a == NULL)
    {
        // allocate private data
        a = new(pev) T;
        a->pev = pev;
    }
    return a;
}

typedef struct _SelAmmo
{
    BYTE Ammo1Type;
    BYTE Ammo1;
    BYTE Ammo2Type;
    BYTE Ammo2;
} SelAmmo;

//LRC- much as I hate to add new globals, I can't see how to read data from the World entity.
extern BOOL g_startSuit;

extern BOOL g_allowGJump; //AJH SP Gaussjump

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

#include "entities/CBaseToggle.h"
#include "util/locksounds.h"

// doors
#define SF_DOOR_ROTATE_Y            0
#define SF_DOOR_START_OPEN          1
#define SF_DOOR_ROTATE_BACKWARDS    2
#define SF_DOOR_PASSABLE            8
#define SF_DOOR_ONEWAY              16
#define SF_DOOR_NO_AUTO_RETURN      32
#define SF_DOOR_ROTATE_Z            64
#define SF_DOOR_ROTATE_X            128
#define SF_DOOR_USE_ONLY            256    // door must be opened by player's use button.
#define SF_DOOR_NOMONSTERS          512    // Monster can't open
#define SF_DOOR_FORCETOUCHABLE      1024   //LRC- Opens when touched, even though it's named and/or "use only"
//LRC - clashes with 'not in deathmatch'. Replaced with 'Target mode' and 'On/Off Mode' fields.
//#define SF_DOOR_SYNCHED                2048 //LRC- sends USE_ON/OFF when it starts to open/close (instead of sending
                                              // USE_TOGGLE when fully open/closed); also responds to USE_ON and USE_OFF
                                              // 'correctly'.
#define SF_DOOR_SILENT                0x80000000

#define DOOR_SENTENCEWAIT     6
#define DOOR_SOUNDWAIT        3
#define BUTTON_SOUNDWAIT    0.5

#define noiseMoving noise1
#define noiseArrived noise2

class CBaseDoor : public CBaseToggle
{
public:
    void Spawn() override;
    void Precache() override;
    void PostSpawn() override;
    void KeyValue(KeyValueData* pkvd) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    void Blocked(CBaseEntity* pOther) override;

    int ObjectCaps() override;
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

    void SetToggleState(int state) override;

    // used to selectivly override defaults
    void DLLEXPORT DoorTouch(CBaseEntity* pOther);

    // local functions
    int DoorActivate();
    void DLLEXPORT DoorGoUp();
    void DLLEXPORT DoorGoDown();
    void DLLEXPORT DoorHitTop();
    void DLLEXPORT DoorHitBottom();

    BYTE m_bHealthValue; // some doors are medi-kit doors, they give players health

    BYTE m_bMoveSnd; // sound a door makes while moving
    BYTE m_bStopSnd; // sound a door makes when it stops

    locksound_t m_ls; // door lock sounds

    BYTE m_bLockedSound; // ordinals from entity selection
    BYTE m_bLockedSentence;
    BYTE m_bUnlockedSound;
    BYTE m_bUnlockedSentence;

    BOOL m_iOnOffMode;
    BOOL m_iImmediateMode;

    BOOL m_iDirectUse;

    float m_fAcceleration; //AJH
    float m_fDeceleration; //AJH
    BOOL m_iSpeedMode; //AJH for changing door speeds
};

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
    void EXPORT DoorTouch(CBaseEntity* pOther);

    // local functions
    int DoorActivate();
    void EXPORT DoorGoUp();
    void EXPORT DoorGoDown();
    void EXPORT DoorHitTop();
    void EXPORT DoorHitBottom();

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

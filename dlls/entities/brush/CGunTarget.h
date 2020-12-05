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

#include "entities/CBaseMonster.h"

// ----------------------------------------------------------
//
//
// pev->speed is the travel speed
// pev->health is current health
// pev->max_health is the amount to reset to each time it starts

#define FGUNTARGET_START_ON            0x0001

class CGunTarget : public CBaseMonster
{
public:
    void Spawn() override;
    void Activate() override;
    void EXPORT Next();
    void EXPORT Start();
    void EXPORT Wait();
    void Stop() override;

    int BloodColor() override;
    int Classify() override;
    int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    Vector BodyTarget(const Vector& posSrc) override;

    int ObjectCaps() override;
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

private:
    BOOL m_on;
};

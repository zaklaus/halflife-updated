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

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "basemonster.h"

class CEnvExplosion : public CBaseMonster
{
public:
    void Spawn();
    void EXPORT Smoke(void);
    void KeyValue(KeyValueData* pkvd);
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    int m_iMagnitude; // how large is the fireball? how much damage?
    int m_spriteScale; // what's the exact fireball sprite scale? 
};

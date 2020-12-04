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

#include "entities/weapons/CGrenade.h"

class CAirtank : public CGrenade
{
    void Spawn(void) override;
    void Precache(void) override;
    void EXPORT TankThink(void);
    void EXPORT TankTouch(CBaseEntity* pOther);
    int BloodColor(void) override { return DONT_BLEED; };
    void Killed(entvars_t* pevAttacker, int iGib) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

    int m_state;
};

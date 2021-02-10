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

#include "CActAnimating.h"
#include "entities/effects/CSprite.h"

#define XEN_PLANT_GLOW_SPRITE  "sprites/flare3.spr"
#define XEN_PLANT_HIDE_TIME    5

class CXenPLight : public CActAnimating
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    void Touch(CBaseEntity* pOther) override;
    void Think(void) override;

    void LightOn(void);
    void LightOff(void);

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

private:
    CSprite* m_pGlow;
};
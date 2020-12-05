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

#include "entities/base/CPointEntity.h"

#define SF_RENDER_MASKFX     (1<<0)
#define SF_RENDER_MASKAMT    (1<<1)
#define SF_RENDER_MASKMODE   (1<<2)
#define SF_RENDER_MASKCOLOR  (1<<3)
//LRC
#define SF_RENDER_KILLTARGET (1<<5)
#define SF_RENDER_ONLYONCE   (1<<6)

// Render parameters trigger
//
// This entity will copy its render parameters (renderfx, rendermode, rendercolor, renderamt)
// to its targets when triggered.
//
class CRenderFxManager : public CPointEntity
{
public:
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    void Affect(CBaseEntity* pEntity, BOOL bIsLocus, CBaseEntity* pActivator);

    void KeyValue(KeyValueData* pkvd) override;
};

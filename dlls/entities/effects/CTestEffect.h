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

class CBeam;

class CTestEffect : public CBaseDelay
{
public:
    void Spawn() override;
    void Precache() override;
    // void    KeyValue( KeyValueData *pkvd );
    void EXPORT TestThink();
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;

    int m_iLoop;
    int m_iBeam;
    CBeam* m_pBeam[24];
    float m_flBeamTime[24];
    float m_flStartTime;
};

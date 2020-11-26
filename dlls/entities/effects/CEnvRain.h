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

#define MAX_RAIN_BEAMS 32

#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 0

#define EXTENT_OBSTRUCTED 1
#define EXTENT_ARCING 2
#define EXTENT_OBSTRUCTED_REVERSE 3
#define EXTENT_ARCING_REVERSE 4
#define EXTENT_ARCING_THROUGH 5 //AJH

//=========================================================
//LRC- the long-awaited effect. (Rain, in the desert? :)
//
//FIXME: give designers a _lot_ more control.
//=========================================================
class CEnvRain : public CBaseEntity
{
public:
    void Spawn(void) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    void Think(void) override;
    void Precache(void) override;
    void KeyValue(KeyValueData* pkvd) override;
    int ObjectCaps(void) override { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    STATE m_iState;
    int m_spriteTexture;
    int m_iszSpriteName; // have to saverestore this, the beams keep a link to it
    int m_dripSize;
    int m_minDripSpeed;
    int m_maxDripSpeed;
    int m_burstSize;
    int m_brightness;
    int m_pitch; // don't saverestore this
    float m_flUpdateTime;
    float m_flMaxUpdateTime;
    //    CBeam*    m_pBeams[MAX_RAIN_BEAMS];
    int m_axis;
    int m_iExtent;
    float m_fLifeTime;
    int m_iNoise;

    STATE GetState(void) override { return m_iState; };
};

/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once

#include "hud/hud.h"
#include "particle.h"
#include "RandomRange.h"

#define MAX_TYPENAME 30

class ParticleSystem;

class ParticleType
{
public:
    ParticleType(ParticleType* pNext = NULL);

    bool m_bIsDefined; // is this ParticleType just a placeholder?

    int m_iRenderMode;
    int m_iDrawCond;
    //	int m_iCollision;
    RandomRange m_Bounce;
    RandomRange m_BounceFriction;
    bool m_bBouncing;

    RandomRange m_Life;

    RandomRange m_StartAlpha;
    RandomRange m_EndAlpha;
    RandomRange m_StartRed;
    RandomRange m_EndRed;
    RandomRange m_StartGreen;
    RandomRange m_EndGreen;
    RandomRange m_StartBlue;
    RandomRange m_EndBlue;

    RandomRange m_StartSize;
    RandomRange m_SizeDelta;
    RandomRange m_EndSize;

    RandomRange m_StartFrame;
    RandomRange m_EndFrame;
    RandomRange m_FrameRate; // incompatible with EndFrame
    bool m_bEndFrame;

    RandomRange m_StartAngle;
    RandomRange m_AngleDelta;

    RandomRange m_SprayRate;
    RandomRange m_SprayForce;
    RandomRange m_SprayPitch;
    RandomRange m_SprayYaw;
    RandomRange m_SprayRoll;
    ParticleType* m_pSprayType;

    RandomRange m_Gravity;
    RandomRange m_WindStrength;
    RandomRange m_WindYaw;

    HSPRITE m_hSprite;
    ParticleType* m_pOverlayType;

    RandomRange m_Drag;

    ParticleType* m_pNext;

    char m_szName[MAX_TYPENAME];

    // here is a particle system. Add a (set of) particles according to this type, and initialise their values.
    particle* CreateParticle(ParticleSystem* pSys); //particle *pPart);

    // initialise this particle. Does not define velocity or age.
    void InitParticle(particle* pPart, ParticleSystem* pSys);
};

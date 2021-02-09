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

#include "ParticleType.h"
#include "ParticleSystem.h"

ParticleType::ParticleType(ParticleType* pNext)
{
    m_pSprayType = m_pOverlayType = NULL;
    m_StartAngle = RandomRange(45);
    m_hSprite = 0;
    m_pNext = pNext;
    m_szName[0] = 0;
    m_StartRed = m_StartGreen = m_StartBlue = m_StartAlpha = RandomRange(1);
    m_EndRed = m_EndGreen = m_EndBlue = m_EndAlpha = RandomRange(1);
    m_iRenderMode = kRenderTransAdd;
    m_iDrawCond = 0;
    m_bEndFrame = false;

    m_bIsDefined = false;
    //	m_iCollision = 0;
}

particle* ParticleType::CreateParticle(ParticleSystem* pSys) //particle *pPart)
{
    if (!pSys) return NULL;

    particle* pPart = pSys->ActivateParticle();
    if (!pPart) return NULL;

    pPart->age = 0.0;
    pPart->age_death = m_Life.GetInstance();

    InitParticle(pPart, pSys);

    return pPart;
}

void ParticleType::InitParticle(particle* pPart, ParticleSystem* pSys)
{
    float fLifeRecip = 1 / pPart->age_death;

    pPart->pType = this;

    pPart->velocity[0] = pPart->velocity[1] = pPart->velocity[2] = 0;
    pPart->accel[0] = pPart->accel[1] = 0;
    pPart->accel[2] = m_Gravity.GetInstance();
    pPart->m_iEntIndex = 0;

    particle* pOverlay = NULL;
    if (m_pOverlayType)
    {
        // create an overlay for this particle
        pOverlay = pSys->ActivateParticle(); //m_pOverlayType->InitParticle(pSys);
        if (pOverlay)
        {
            pOverlay->age = pPart->age;
            pOverlay->age_death = pPart->age_death;
            m_pOverlayType->InitParticle(pOverlay, pSys);
        }
    }
    pPart->m_pOverlay = pOverlay;

    if (m_pSprayType)
    {
        pPart->age_spray = 1 / m_SprayRate.GetInstance();
    }
    else
    {
        pPart->age_spray = 0.0f;
    }

    pPart->m_fSize = m_StartSize.GetInstance();
    if (m_EndSize.IsDefined())
        pPart->m_fSizeStep = m_EndSize.GetOffset(pPart->m_fSize) * fLifeRecip;
    else
        pPart->m_fSizeStep = m_SizeDelta.GetInstance();
    //pPart->m_fSizeStep = m_EndSize.GetOffset(pPart->m_fSize) * fLifeRecip;

    pPart->frame = m_StartFrame.GetInstance();
    if (m_EndFrame.IsDefined())
        pPart->m_fFrameStep = m_EndFrame.GetOffset(pPart->frame) * fLifeRecip;
    else
        pPart->m_fFrameStep = m_FrameRate.GetInstance();

    pPart->m_fAlpha = m_StartAlpha.GetInstance();
    pPart->m_fAlphaStep = m_EndAlpha.GetOffset(pPart->m_fAlpha) * fLifeRecip;
    pPart->m_fRed = m_StartRed.GetInstance();
    pPart->m_fRedStep = m_EndRed.GetOffset(pPart->m_fRed) * fLifeRecip;
    pPart->m_fGreen = m_StartGreen.GetInstance();
    pPart->m_fGreenStep = m_EndGreen.GetOffset(pPart->m_fGreen) * fLifeRecip;
    pPart->m_fBlue = m_StartBlue.GetInstance();
    pPart->m_fBlueStep = m_EndBlue.GetOffset(pPart->m_fBlue) * fLifeRecip;

    pPart->m_fAngle = m_StartAngle.GetInstance();
    pPart->m_fAngleStep = m_AngleDelta.GetInstance();

    pPart->m_fDrag = m_Drag.GetInstance();

    float fWindStrength = m_WindStrength.GetInstance();
    float fWindYaw = m_WindYaw.GetInstance();
    pPart->m_vecWind.x = fWindStrength * ParticleSystem::CosLookup(fWindYaw);
    pPart->m_vecWind.y = fWindStrength * ParticleSystem::SinLookup(fWindYaw);
    pPart->m_vecWind.z = 0;
}

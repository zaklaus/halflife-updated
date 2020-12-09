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
* Valve LLC.  All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/

#include "CRenderFxManager.h"
#include "CRenderFxFader.h"
#include "util/findentity.h"
#include "util/locus.h"

LINK_ENTITY_TO_CLASS(env_render, CRenderFxManager);

void CRenderFxManager::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "m_fScale"))
    {
        pev->noise = ALLOC_STRING(pkvd->szValue); //AJH Allows LR scale (Thanks Mike)
        pkvd->fHandled = TRUE;
    }
    else
        CPointEntity::KeyValue(pkvd);
}

void CRenderFxManager::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    if (!FStringNull(pev->target))
    {
        CBaseEntity* pTarget = UTIL_FindEntityByTargetname(NULL, STRING(pev->target), pActivator);
        BOOL first = TRUE;
        while (pTarget != NULL)
        {
            Affect(pTarget, first, pActivator);
            first = FALSE;
            pTarget = UTIL_FindEntityByTargetname(pTarget, STRING(pev->target), pActivator);
        }
    }

    if (pev->spawnflags & SF_RENDER_ONLYONCE)
    {
        SetThink(&CRenderFxManager::SUB_Remove);
        SetNextThink(0.1);
    }
}

void CRenderFxManager::Affect(CBaseEntity* pTarget, BOOL bIsFirst, CBaseEntity* pActivator)
{
    entvars_t* pevTarget = pTarget->pev;

    float fAmtFactor = 1;
    if (pev->message && !FBitSet(pev->spawnflags, SF_RENDER_MASKAMT))
        fAmtFactor = CalcLocus_Number(pActivator, STRING(pev->message));

    if (!FBitSet(pev->spawnflags, SF_RENDER_MASKFX))
        pevTarget->renderfx = pev->renderfx;
    if (!FBitSet(pev->spawnflags, SF_RENDER_MASKMODE))
    {
        //LRC - amt is often 0 when mode is normal. Set it to be fully visible, for fade purposes.
        if (pev->frags && pevTarget->renderamt == 0 && pevTarget->rendermode == kRenderNormal)
            pevTarget->renderamt = 255;
        pevTarget->rendermode = pev->rendermode;
    }
    if (pev->frags == 0) // not fading?
    {
        if (!FBitSet(pev->spawnflags, SF_RENDER_MASKAMT))
            pevTarget->renderamt = pev->renderamt * fAmtFactor;
        if (!FBitSet(pev->spawnflags, SF_RENDER_MASKCOLOR))
            pevTarget->rendercolor = pev->rendercolor;
        if (pev->noise)
        {
            pevTarget->scale = CalcLocus_Number(pActivator, STRING(pev->noise)); //AJH Allows LR scale
            ALERT(at_debug, "Setting scale from %s, to %f\n", STRING(pev->noise), pevTarget->scale);
        }

        if (bIsFirst)
            FireTargets(STRING(pev->netname), pTarget, this, USE_TOGGLE, 0);
    }
    else
    {
        //LRC - fade the entity in/out!
        // (We create seperate fader entities to do this, one for each entity that needs fading.)
        CRenderFxFader* pFader = GetClassPtr((CRenderFxFader*)NULL);
        pFader->m_hTarget = pTarget;
        pFader->m_iStartAmt = pevTarget->renderamt;
        pFader->m_vecStartColor = pevTarget->rendercolor;
        pFader->m_fStartScale = pevTarget->scale;
        if (pFader->m_fStartScale == 0)
            pFader->m_fStartScale = 1; // When we're scaling, 0 is treated as 1. Use 1 as the number to fade from.
        pFader->pev->spawnflags = pev->spawnflags;

        if (bIsFirst)
            pFader->pev->target = pev->netname;

        if (!FBitSet(pev->spawnflags, SF_RENDER_MASKAMT))
            pFader->m_iOffsetAmt = (pev->renderamt * fAmtFactor) - pevTarget->renderamt;
        else
            pFader->m_iOffsetAmt = 0;

        if (!FBitSet(pev->spawnflags, SF_RENDER_MASKCOLOR))
        {
            pFader->m_vecOffsetColor.x = pev->rendercolor.x - pevTarget->rendercolor.x;
            pFader->m_vecOffsetColor.y = pev->rendercolor.y - pevTarget->rendercolor.y;
            pFader->m_vecOffsetColor.z = pev->rendercolor.z - pevTarget->rendercolor.z;
        }
        else
        {
            pFader->m_vecOffsetColor = g_vecZero;
        }

        if (pev->noise)
            pFader->m_fOffsetScale = CalcLocus_Number(pActivator, STRING(pev->noise)) - pevTarget->scale; //AJH Allows LR scale
        else
            pFader->m_fOffsetScale = 0;

        pFader->m_flStartTime = gpGlobals->time;
        pFader->m_flDuration = pev->frags;
        pFader->m_flCoarseness = pev->armorvalue;
        pFader->SetNextThink(0);
        pFader->Spawn();
    }
}

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

#include "CTargetCDAudio.h"

LINK_ENTITY_TO_CLASS(target_cdaudio, CTargetCDAudio);

void CTargetCDAudio::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "radius"))
    {
        pev->scale = atof(pkvd->szValue);
        pkvd->fHandled = TRUE;
    }
    else
        CPointEntity::KeyValue(pkvd);
}

void CTargetCDAudio::Spawn(void)
{
    pev->solid = SOLID_NOT;
    pev->movetype = MOVETYPE_NONE;

    if (pev->scale > 0)
        SetNextThink(1.0);
}

void CTargetCDAudio::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    Play();
}

// only plays for ONE client, so only use in single play!
void CTargetCDAudio::Think(void)
{
    edict_t* pClient;

    // manually find the single player.
    pClient = g_engfuncs.pfnPEntityOfEntIndex(1);

    // Can't play if the client is not connected!
    if (!pClient)
        return;

    SetNextThink(0.5);

    if ((pClient->v.origin - pev->origin).Length() <= pev->scale)
        Play();
}

void CTargetCDAudio::Play(void)
{
    PlayCDTrack((int)pev->health, (int)pev->message);
    UTIL_Remove(this);
}
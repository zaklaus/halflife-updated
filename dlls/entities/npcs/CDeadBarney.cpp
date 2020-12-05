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

#include "CDeadBarney.h"

LINK_ENTITY_TO_CLASS(monster_barney_dead, CDeadBarney);

const char* CDeadBarney::m_szPoses[] = {"lying_on_back", "lying_on_side", "lying_on_stomach"};

void CDeadBarney::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "pose"))
    {
        m_iPose = atoi(pkvd->szValue);
        pkvd->fHandled = TRUE;
    }
    else
        CBaseMonster::KeyValue(pkvd);
}

//=========================================================
// ********** DeadBarney SPAWN **********
//=========================================================
void CDeadBarney::Spawn()
{
    PRECACHE_MODEL("models/barney.mdl");
    SET_MODEL(ENT(pev), "models/barney.mdl");

    pev->effects = 0;
    pev->yaw_speed = 8;
    pev->sequence = 0;
    m_bloodColor = BLOOD_COLOR_RED;

    pev->sequence = LookupSequence(m_szPoses[m_iPose]);
    if (pev->sequence == -1)
    {
        ALERT(at_debug, "Dead barney with bad pose\n");
    }
    // Corpses have less health
    pev->health = 8; //gSkillData.barneyHealth;

    MonsterInitDead();
}

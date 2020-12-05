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

#include "CDeadScientist.h"
#include "CScientist.h"

LINK_ENTITY_TO_CLASS(monster_scientist_dead, CDeadScientist);

const char* CDeadScientist::m_szPoses[] = {"lying_on_back", "lying_on_stomach", "dead_sitting", "dead_hang", "dead_table1", "dead_table2", "dead_table3"};

void CDeadScientist::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "pose"))
    {
        m_iPose = atoi(pkvd->szValue);
        pkvd->fHandled = TRUE;
    }
    else
        CBaseMonster::KeyValue(pkvd);
}

//
// ********** DeadScientist SPAWN **********
//
void CDeadScientist::Spawn()
{
    PRECACHE_MODEL("models/scientist.mdl");
    SET_MODEL(ENT(pev), "models/scientist.mdl");

    pev->effects = 0;
    pev->sequence = 0;
    // Corpses have less health
    pev->health = 8; //gSkillData.scientistHealth;

    m_bloodColor = BLOOD_COLOR_RED;

    if (pev->body == -1)
    {
        // -1 chooses a random head
        pev->body = RANDOM_LONG(0, NUM_SCIENTIST_HEADS - 1); // pick a head, any head
    }
    // Luther is black, make his hands black
    if (pev->body == HEAD_LUTHER)
        pev->skin = 1;
    else
        pev->skin = 0;

    pev->sequence = LookupSequence(m_szPoses[m_iPose]);
    if (pev->sequence == -1)
    {
        ALERT(at_debug, "Dead scientist with bad pose\n");
    }

    //    pev->skin += 2; // use bloody skin -- UNDONE: Turn this back on when we have a bloody skin again!
    MonsterInitDead();
}

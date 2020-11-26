/***
*
*    Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*    
*    This product contains software technology licensed from Id 
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*    All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "CPlatTrigger.h"

int CPlatTrigger::ObjectCaps()
{
    return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_DONT_SAVE;
}

//
// Create a trigger entity for a platform.
//
void CPlatTrigger::SpawnInsideTrigger(CFuncPlat* pPlatform)
{
    m_pPlatform = pPlatform;
    // Create trigger entity, "point" it at the owning platform, give it a touch method
    pev->solid = SOLID_TRIGGER;
    pev->movetype = MOVETYPE_NONE;
    pev->origin = pPlatform->pev->origin;

    // Establish the trigger field's size
    Vector vecTMin = m_pPlatform->pev->mins + Vector(25, 25, 0);
    Vector vecTMax = m_pPlatform->pev->maxs + Vector(25, 25, 8);
    vecTMin.z = vecTMax.z - (m_pPlatform->m_vecPosition1.z - m_pPlatform->m_vecPosition2.z + 8);
    if (m_pPlatform->pev->size.x <= 50)
    {
        vecTMin.x = (m_pPlatform->pev->mins.x + m_pPlatform->pev->maxs.x) / 2;
        vecTMax.x = vecTMin.x + 1;
    }
    if (m_pPlatform->pev->size.y <= 50)
    {
        vecTMin.y = (m_pPlatform->pev->mins.y + m_pPlatform->pev->maxs.y) / 2;
        vecTMax.y = vecTMin.y + 1;
    }
    UTIL_SetSize(pev, vecTMin, vecTMax);
}


//
// When the platform's trigger field is touched, the platform ???
//
void CPlatTrigger::Touch(CBaseEntity* pOther)
{
    // Ignore touches by non-players
    entvars_t* pevToucher = pOther->pev;
    if (!FClassnameIs(pevToucher, "player"))
        return;

    // Ignore touches by corpses
    if (!pOther->IsAlive() || !m_pPlatform || !m_pPlatform->pev)
        return;

    // Make linked platform go up/down.
    if (m_pPlatform->m_toggle_state == TS_AT_BOTTOM)
        m_pPlatform->GoUp();
    else if (m_pPlatform->m_toggle_state == TS_AT_TOP)
        m_pPlatform->SetNextThink(1);// delay going down
}


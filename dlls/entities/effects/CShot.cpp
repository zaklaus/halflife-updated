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

#include "CShot.h"
#include "entities/world/CWorld.h"

void CShot::Touch(CBaseEntity* pOther)
{
    if (pev->teleport_time > gpGlobals->time)
        return;
    // don't fire too often in collisions!
    // teleport_time is the soonest this can be touched again.
    pev->teleport_time = gpGlobals->time + 0.1;

    if (pev->netname)
        FireTargets(STRING(pev->netname), this, this, USE_TOGGLE, 0);
    if (pev->message && pOther && pOther != g_pWorld)
        FireTargets(STRING(pev->message), pOther, this, USE_TOGGLE, 0);
}

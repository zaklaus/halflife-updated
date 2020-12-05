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

#include "CTentacleMaw.h"

LINK_ENTITY_TO_CLASS(monster_tentaclemaw, CTentacleMaw);

//
// Tentacle Spawn
//
void CTentacleMaw::Spawn()
{
    Precache();
    SET_MODEL(ENT(pev), "models/maw.mdl");
    UTIL_SetSize(pev, Vector(-32, -32, 0), Vector(32, 32, 64));

    pev->solid = SOLID_NOT;
    pev->movetype = MOVETYPE_STEP;
    pev->effects = 0;
    pev->health = 75;
    pev->yaw_speed = 8;
    pev->sequence = 0;

    pev->angles.x = 90;
    // ResetSequenceInfo( );
}

void CTentacleMaw::Precache()
{
    PRECACHE_MODEL("models/maw.mdl");
}

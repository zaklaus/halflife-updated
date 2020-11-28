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

#include "CCyclerProbe.h"

LINK_ENTITY_TO_CLASS(cycler_prdroid, CCyclerProbe);

void CCyclerProbe::Spawn()
{
    pev->origin = pev->origin + Vector(0, 0, 16);
    GenericCyclerSpawn("models/prdroid.mdl", Vector(-16, -16, -16), Vector(16, 16, 16));
}

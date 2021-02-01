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

#include "CPointEntity.h"

// These are the new entry points to entities. 
LINK_ENTITY_TO_CLASS(info_player_start, CPointEntity);
LINK_ENTITY_TO_CLASS(info_landmark, CPointEntity);
LINK_ENTITY_TO_CLASS(info_teleport_destination, CPointEntity);

// Landmark class
void CPointEntity::Spawn(void)
{
    pev->solid = SOLID_NOT;
}
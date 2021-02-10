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

#include "CItemSecurity.h"
#include "entities/player/CBasePlayer.h"

LINK_ENTITY_TO_CLASS(item_security, CItemSecurity);

void CItemSecurity::Spawn()
{
    Precache();
    SET_MODEL(ENT(pev), "models/w_security.mdl");
    CItem::Spawn();
}

void CItemSecurity::Precache()
{
    PRECACHE_MODEL("models/w_security.mdl");
}

BOOL CItemSecurity::MyTouch(CBasePlayer* pPlayer)
{
    pPlayer->m_rgItems[ITEM_SECURITY] += 1;

    if (pev->noise) //AJH
        EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, STRING(pev->noise), 1, ATTN_NORM);
    else
        EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM);

    return TRUE;
}

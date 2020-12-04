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
* Valve LLC.All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/
#pragma once

#include "CItem.h"

#define CHARGE_IN_MEDKIT    50 // Possibly implement skill system
#define MAX_MEDKIT         200 // possibly allow mapper to change, say in worldspawn

#define ITEM_NOTPICKEDUP  0
#define ITEM_PICKEDUP     1
#define ITEM_DRAINED      2 //The item has had some 'charge' removed but remains in existence

class CItemMedicalKit : public CItem //AJH new inventory based manual use medkit
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int MyTouch(CBasePlayer* pPlayer) override;
    void EXPORT ItemTouch(CBaseEntity* pOther);
    void CItemMedicalKit::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

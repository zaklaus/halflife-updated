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

#include "CBasePlayerItem.h"

class CBasePlayerAmmo : public CBasePlayerItem //AJH
{
public:
    void Spawn(void) override;
    void EXPORT DefaultTouch(CBaseEntity* pOther); // default weapon touch
    virtual BOOL AddAmmo(CBaseEntity* pOther) { return TRUE; };

    CBaseEntity* Respawn(void) override;
    void EXPORT Materialize(void);
};

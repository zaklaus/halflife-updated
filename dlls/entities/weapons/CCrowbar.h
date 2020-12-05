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

#include "CBasePlayerWeapon.h"

#define CROWBAR_BODYHIT_VOLUME 128
#define CROWBAR_WALLHIT_VOLUME 512

class CCrowbar : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    void DLLEXPORT SwingAgain(void);
    void DLLEXPORT Smack(void);
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    int Swing(int fFirst);
    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;
    int m_iSwing;
    TraceResult m_trHit;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
        return FALSE;
#endif
    }
};

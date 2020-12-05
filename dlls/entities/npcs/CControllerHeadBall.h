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

#include "extdll.h"
#include "util.h"
#include "cbase.h"

//=========================================================
// Controller bouncy ball attack
//=========================================================
class CControllerHeadBall : public CBaseMonster
{
    void Spawn(void) override;
    void Precache(void) override;
    void EXPORT HuntThink(void);
    void EXPORT DieThink(void);
    void EXPORT BounceTouch(CBaseEntity* pOther);
    void MovetoTarget(Vector vecTarget);
    void Crawl(void);
    int m_iTrail;
    int m_flNextAttack;
    Vector m_vecIdeal;
    EHANDLE m_hOwner;
};

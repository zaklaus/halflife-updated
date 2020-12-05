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

#include "entities/CBaseMonster.h"
#include "CNihilanth.h"

//=========================================================
// Controller bouncy ball attack
//=========================================================
class CNihilanthHVR : public CBaseMonster
{
public:
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    void Spawn(void) override;
    void Precache(void) override;

    void CircleInit(CBaseEntity* pTarget);
    void AbsorbInit(void);
    void TeleportInit(CNihilanth* pOwner, CBaseEntity* pEnemy, CBaseEntity* pTarget, CBaseEntity* pTouch);
    void GreenBallInit(void);
    void ZapInit(CBaseEntity* pEnemy);

    void EXPORT HoverThink(void);
    BOOL CircleTarget(Vector vecTarget);
    void EXPORT DissipateThink(void);

    void EXPORT ZapThink(void);
    void EXPORT TeleportThink(void);
    void EXPORT TeleportTouch(CBaseEntity* pOther);

    void EXPORT RemoveTouch(CBaseEntity* pOther);
    void EXPORT BounceTouch(CBaseEntity* pOther);
    void EXPORT ZapTouch(CBaseEntity* pOther);

    CBaseEntity* RandomClassname(const char* szName);

    // void EXPORT SphereUse( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );

    void MovetoTarget(Vector vecTarget);
    virtual void Crawl(void);

    void Zap(void);
    void Teleport(void);

    float m_flIdealVel;
    Vector m_vecIdeal;
    CNihilanth* m_pNihilanth;
    EHANDLE m_hTouch;
    int m_nFrames;
};

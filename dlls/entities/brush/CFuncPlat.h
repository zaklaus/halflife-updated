/***
*
*    Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once

#include "CBasePlatTrain.h"

class CFuncPlat : public CBasePlatTrain
{
public:
    void Spawn() override;
    void Precache() override;
    void Setup();

    void Blocked(CBaseEntity* pOther) override;

    void EXPORT PlatUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);

    void EXPORT CallGoUp();
    void EXPORT CallGoDown();
    void EXPORT CallHitTop();
    void EXPORT CallHitBottom();

    virtual void GoUp();
    virtual void GoDown();
    virtual void HitTop();
    virtual void HitBottom();
};

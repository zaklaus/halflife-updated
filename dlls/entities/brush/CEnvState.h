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

//==================================================
//LRC- a simple entity, just maintains a state
//==================================================

#include "extdll.h"
#include "util.h"
#include "cbase.h"

#define SF_ENVSTATE_START_ON 1
#define SF_ENVSTATE_DEBUG    2

class CEnvState : public CPointEntity
{
public:
    void Spawn() override;
    void Think() override;
    void KeyValue(KeyValueData* pkvd) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;

    BOOL IsLockedByMaster();

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    STATE GetState() override;

    static TYPEDESCRIPTION m_SaveData[];

    STATE m_iState;
    float m_fTurnOnTime;
    float m_fTurnOffTime;
    int m_sMaster;
};

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

#include "entities/base/CPointEntity.h"

//===========================================================
//LRC- trigger_motion
//===========================================================
class CTriggerMotion : public CPointEntity
{
public:
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    void KeyValue(KeyValueData* pkvd) override;

    int m_iszPosition;
    int m_iPosMode;
    int m_iszAngles;
    int m_iAngMode;
    int m_iszVelocity;
    int m_iVelMode;
    int m_iszAVelocity;
    int m_iAVelMode;
};

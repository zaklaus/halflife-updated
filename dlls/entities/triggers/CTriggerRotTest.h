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

#include "entities/CBaseDelay.h"

//===========================================
//LRC - trigger_rottest, temporary new entity
//===========================================
class CTriggerRotTest : public CBaseDelay
{
public:
    void PostSpawn(void) override;
    //    void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
    void Think(void) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

private:
    CBaseEntity* m_pMarker;
    CBaseEntity* m_pReference;
    CBaseEntity* m_pBridge;
    CBaseEntity* m_pHinge;
};
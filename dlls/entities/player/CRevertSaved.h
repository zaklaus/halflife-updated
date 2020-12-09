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

#include "entities/base/CPointEntity.h"

class CRevertSaved : public CPointEntity
{
public:
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    void DLLEXPORT MessageThink(void);
    void DLLEXPORT LoadThink(void);
    void KeyValue(KeyValueData* pkvd) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    inline float Duration(void) { return pev->dmg_take; }
    inline float HoldTime(void) { return pev->dmg_save; }
    inline float MessageTime(void) { return m_messageTime; }
    inline float LoadTime(void) { return m_loadTime; }

    inline void SetDuration(float duration) { pev->dmg_take = duration; }
    inline void SetHoldTime(float hold) { pev->dmg_save = hold; }
    inline void SetMessageTime(float time) { m_messageTime = time; }
    inline void SetLoadTime(float time) { m_loadTime = time; }

private:
    float m_messageTime;
    float m_loadTime;
};

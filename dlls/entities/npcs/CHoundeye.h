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
#include "monsters.h"
#include "squadmonster.h"

class CHoundeye : public CSquadMonster
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int Classify(void) override;
    void HandleAnimEvent(MonsterEvent_t* pEvent) override;
    void SetYawSpeed(void) override;
    void WarmUpSound(void);
    void AlertSound(void) override;
    void DeathSound(void) override;
    void WarnSound(void);
    void PainSound(void) override;
    void IdleSound(void) override;
    void StartTask(Task_t* pTask) override;
    void RunTask(Task_t* pTask) override;
    void SonicAttack(void);
    void PrescheduleThink(void) override;
    void SetActivity(Activity NewActivity) override;
    void WriteBeamColor(void);
    BOOL CheckRangeAttack1(float flDot, float flDist) override;
    BOOL FValidateHintType(short sHint) override;
    BOOL FCanActiveIdle(void) override;
    Schedule_t* GetScheduleOfType(int Type) override;
    Schedule_t* GetSchedule(void) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    CUSTOM_SCHEDULES;
    static TYPEDESCRIPTION m_SaveData[];

    int m_iSpriteTexture;
    BOOL m_fAsleep; // some houndeyes sleep in idle mode if this is set, the houndeye is lying down
    BOOL m_fDontBlink; // don't try to open/close eye if this bit is set!
    Vector m_vecPackCenter; // the center of the pack. The leader maintains this by averaging the origins of all pack members.
};

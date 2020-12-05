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

#include "entities/base/CTalkMonster.h"

// UNDONE: Holster weapon?
class CBarney : public CTalkMonster
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    void SetYawSpeed(void) override;
    int ISoundMask(void) override;
    void BarneyFirePistol(void);
    void AlertSound(void) override;
    int Classify(void) override;
    void HandleAnimEvent(MonsterEvent_t* pEvent) override;

    void RunTask(Task_t* pTask) override;
    void StartTask(Task_t* pTask) override;
    int ObjectCaps(void) override { return CTalkMonster::ObjectCaps() | FCAP_IMPULSE_USE; }
    int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
    BOOL CheckRangeAttack1(float flDot, float flDist) override;

    void DeclineFollowing(void) override;

    // Override these to set behavior
    Schedule_t* GetScheduleOfType(int Type) override;
    Schedule_t* GetSchedule(void) override;
    MONSTERSTATE GetIdealState(void) override;

    void DeathSound(void) override;
    void PainSound(void) override;

    void TalkInit(void);

    void TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) override;
    void Killed(entvars_t* pevAttacker, int iGib) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    int m_iBaseBody; //LRC - for barneys with different bodies
    BOOL m_fGunDrawn;
    float m_painTime;
    float m_checkAttackTime;
    BOOL m_lastAttackCheck;

    // UNDONE: What is this for?  It isn't used?
    float m_flPlayerDamage; // how much pain has the player inflicted on me?

    CUSTOM_SCHEDULES;
};

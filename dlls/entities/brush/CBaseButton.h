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

#include "entities/CBaseToggle.h"

//
// Generic Button
//
class CBaseButton : public CBaseToggle
{
public:
    void Spawn() override;
    void PostSpawn() override; //LRC
    void Precache() override;
    void RotSpawn();
    void KeyValue(KeyValueData* pkvd) override;

    void ButtonActivate();
    void SparkSoundCache();

    void EXPORT ButtonShot();
    void EXPORT ButtonTouch(CBaseEntity* pOther);
    void EXPORT ButtonSpark();
    void EXPORT TriggerAndWait();
    void EXPORT ButtonReturn();
    void EXPORT ButtonBackHome();
    void EXPORT ButtonUse_IgnorePlayer(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
    void EXPORT ButtonUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
    int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    enum BUTTON_CODE { BUTTON_NOTHING, BUTTON_ACTIVATE, BUTTON_RETURN };

    BUTTON_CODE ButtonResponseToTouch(void);

    static TYPEDESCRIPTION m_SaveData[];
    int ObjectCaps() override;

    BOOL m_fStayPushed; // button stays pushed in until touched again?
    BOOL m_fRotating; // a rotating button?  default is a sliding button.

    string_t m_strChangeTarget; // if this field is not null, this is an index into the engine string array.
    // when this button is touched, it's target entity's TARGET field will be set
    // to the button's ChangeTarget. This allows you to make a func_train switch paths, etc.

    locksound_t m_ls; // door lock sounds

    BYTE m_bLockedSound; // ordinals from entity selection
    BYTE m_bLockedSentence;
    BYTE m_bUnlockedSound;
    BYTE m_bUnlockedSentence;
    int m_sounds;
};

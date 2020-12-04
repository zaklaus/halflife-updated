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

#include "CItem.h"

#define SF_CAMERA_PLAYER_POSITION      1
#define SF_CAMERA_PLAYER_TARGET        2
#define SF_CAMERA_PLAYER_TAKECONTROL   4
#define SF_CAMERA_DRAWHUD             16

//Dont Change these values, they are assumed in the client.
#define ITEM_CAMERA_ACTIVE             5
#define CAMERA_DRAWPLAYER              8

#define MAX_CAMERAS                    4

class CItemCamera : public CItem //AJH new inventory camera (can be placed anywhere in a level by the player)
{
public:
    void Spawn(void) override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    //void Think( void );
    void Precache(void) override;
    void EXPORT ItemTouch(CBaseEntity* pOther);
    int MyTouch(CBasePlayer* pPlayer) override;
    //CBaseEntity* Respawn(void);
    //void Materialize(void);
    void StripFromPlayer(void);
    int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;


    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    int ObjectCaps(void) override { return m_iobjectcaps; }
    static TYPEDESCRIPTION m_SaveData[];

    //EHANDLE m_hPlayer;
    int m_state;
    int m_iobjectcaps;
    CItemCamera* m_pNextCamera;
    CItemCamera* m_pLastCamera;
};

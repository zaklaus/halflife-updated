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

#include "CHudBase.h"
#include "WeaponsResource.h"
#include "HistoryResource.h"

class CHudAmmo : public CHudBase
{
public:
    int Init() override;
    int VidInit() override;
    int Draw(float flTime) override;
    void Think() override;
    void Reset() override;
    int DrawWList(float flTime);
    int MsgFunc_CurWeapon(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_WeaponList(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_AmmoX(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_AmmoPickup(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_WeapPickup(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_ItemPickup(const char* pszName, int iSize, void* pbuf);
    int MsgFunc_HideWeapon(const char* pszName, int iSize, void* pbuf);

    void SlotInput(int iSlot);
    void _cdecl UserCmd_Slot1();
    void _cdecl UserCmd_Slot2();
    void _cdecl UserCmd_Slot3();
    void _cdecl UserCmd_Slot4();
    void _cdecl UserCmd_Slot5();
    void _cdecl UserCmd_Slot6();
    void _cdecl UserCmd_Slot7();
    void _cdecl UserCmd_Slot8();
    void _cdecl UserCmd_Slot9();
    void _cdecl UserCmd_Slot10();
    void _cdecl UserCmd_Close();
    void _cdecl UserCmd_NextWeapon();
    void _cdecl UserCmd_PrevWeapon();

private:
    float m_fFade;
    rgba_t m_rgba;
    WEAPON* m_pWeapon;
    int m_HUD_bucket0;
    int m_HUD_selection;
};

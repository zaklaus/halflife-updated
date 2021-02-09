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

class CHudSayText : public CHudBase
{
public:
    int Init() override;
    void InitHUDData() override;
    int VidInit() override;
    int Draw(float flTime) override;
    int MsgFunc_SayText(const char* pszName, int iSize, void* pbuf);
    void SayTextPrint(const char* pszBuf, int iBufSize, int clientIndex = -1);
    void EnsureTextFitsInOneLineAndWrapIfHaveTo(int line);
    friend class CHudSpectator;

private:
    struct cvar_s* m_HUD_saytext;
    struct cvar_s* m_HUD_saytext_time;
};

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

#define MAX_SPRITE_NAME_LENGTH	24

class CHudStatusIcons : public CHudBase
{
public:
    int Init() override;
    int VidInit() override;
    void Reset() override;
    int Draw(float flTime) override;
    int MsgFunc_StatusIcon(const char* pszName, int iSize, void* pbuf);

    enum
    {
        MAX_ICONSPRITENAME_LENGTH = MAX_SPRITE_NAME_LENGTH,
        MAX_ICONSPRITES = 4,
    };


    //had to make these public so CHud could access them (to enable concussion icon)
    //could use a friend declaration instead...
    void EnableIcon(const char* pszIconName, unsigned char red, unsigned char green, unsigned char blue);
    void DisableIcon(const char* pszIconName);

private:

    typedef struct
    {
        char szSpriteName[MAX_ICONSPRITENAME_LENGTH];
        HSPRITE spr;
        wrect_t rc;
        unsigned char r, g, b;
    } icon_sprite_t;

    icon_sprite_t m_IconList[MAX_ICONSPRITES];
};

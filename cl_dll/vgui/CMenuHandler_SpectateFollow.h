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

#include <VGUI_ActionSignal.h>

#include "hud/CHud.h"
#include "vgui_common.h"

class CMenuHandler_SpectateFollow : public vgui::ActionSignal
{
public:
    CMenuHandler_SpectateFollow(char* player)
    {
        strncpy(m_szplayer, player, MAX_COMMAND_SIZE);
        m_szplayer[MAX_COMMAND_SIZE - 1] = '\0';
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        gHUD.m_Spectator.FindPlayer(m_szplayer);
        gViewPort->HideCommandMenu();
    }

protected:
    char m_szplayer[MAX_COMMAND_SIZE];
};

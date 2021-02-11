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

#include "IVoiceStatusHelper.h"
#include "hud/CHud.h"
#include "vgui/TeamFortressViewport.h"
#include "vgui/ScorePanel.h"

class CHLVoiceStatusHelper : public IVoiceStatusHelper
{
public:
    void GetPlayerTextColor(int entindex, int color[3]) override
    {
        color[0] = color[1] = color[2] = 255;

        if (entindex >= 0 && entindex < sizeof(g_PlayerExtraInfo) / sizeof(g_PlayerExtraInfo[0]))
        {
            int iTeam = g_PlayerExtraInfo[entindex].teamnumber;

            if (iTeam < 0)
            {
                iTeam = 0;
            }

            iTeam = iTeam % iNumberOfTeamColors;

            color[0] = iTeamColors[iTeam][0];
            color[1] = iTeamColors[iTeam][1];
            color[2] = iTeamColors[iTeam][2];
        }
    }

    void UpdateCursorState() override
    {
        gViewPort->UpdateCursorState();
    }

    int GetAckIconHeight() override
    {
        return ScreenHeight - gHUD.m_iFontHeight * 3 - 6;
    }

    bool CanShowSpeakerLabels() override
    {
        if (gViewPort && gViewPort->m_pScoreBoard)
            return !gViewPort->m_pScoreBoard->isVisible();
        else
            return false;
    }
};

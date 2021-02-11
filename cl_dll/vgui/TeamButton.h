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

#include "CommandButton.h"
#include "hud/hud.h"

class TeamButton : public CommandButton
{
public:
    TeamButton(int iTeam, const char* text, int x, int y, int wide, int tall) : CommandButton(text, x, y, wide, tall)
    {
        m_iTeamNumber = iTeam;
    }

    int IsNotValid() override
    {
        int iTeams = gViewPort->GetNumberOfTeams();
        // Never valid if there's only 1 team
        if (iTeams == 1)
            return true;

        // Auto Team's always visible
        if (m_iTeamNumber == 5)
            return false;

        if (iTeams >= m_iTeamNumber && m_iTeamNumber != g_iTeamNumber)
            return false;

        return true;
    }

private:
    int m_iTeamNumber;
};

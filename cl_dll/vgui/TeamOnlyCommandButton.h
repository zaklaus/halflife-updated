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

// Purpose: CommandButton which is only displayed if the player is on team X
class TeamOnlyCommandButton : public CommandButton
{
public:
    TeamOnlyCommandButton(int iTeamNum, const char* text, int x, int y, int wide, int tall, bool flat) :
        CommandButton(text, x, y, wide, tall, false, flat), m_iTeamNum(iTeamNum)
    {
    }

    int IsNotValid() override
    {
        if (g_iTeamNumber != m_iTeamNum)
            return true;

        return CommandButton::IsNotValid();
    }

private:
    int m_iTeamNum;
};

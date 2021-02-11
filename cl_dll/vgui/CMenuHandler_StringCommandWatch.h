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

#include <VGUI_Panel.h>

#include "CMenuHandler_StringCommand.h"

// This works the same as CMenuHandler_StringCommand, except it watches the string command 
// for specific commands, and modifies client vars based upon them.
class CMenuHandler_StringCommandWatch : public CMenuHandler_StringCommand
{
public:
    CMenuHandler_StringCommandWatch(const char* pszCommand) : CMenuHandler_StringCommand(pszCommand)
    {
    }

    CMenuHandler_StringCommandWatch(const char* pszCommand, int iClose) : CMenuHandler_StringCommand(pszCommand, iClose)
    {
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        CMenuHandler_StringCommand::actionPerformed(panel);

        // Try to guess the player's new team (it'll be corrected if it's wrong)
        if (!strcmp(m_pszCommand, "jointeam 1"))
            g_iTeamNumber = 1;
        else if (!strcmp(m_pszCommand, "jointeam 2"))
            g_iTeamNumber = 2;
        else if (!strcmp(m_pszCommand, "jointeam 3"))
            g_iTeamNumber = 3;
        else if (!strcmp(m_pszCommand, "jointeam 4"))
            g_iTeamNumber = 4;
    }
};

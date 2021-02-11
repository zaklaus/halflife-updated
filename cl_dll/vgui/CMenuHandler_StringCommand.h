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


#include "hud/hud.h"
#include "TeamFortressViewport.h"

class CMenuHandler_StringCommand : public vgui::ActionSignal
{
public:
    CMenuHandler_StringCommand(const char* pszCommand)
    {
        strncpy(m_pszCommand, pszCommand, MAX_COMMAND_SIZE);
        m_pszCommand[MAX_COMMAND_SIZE - 1] = '\0';
        m_iCloseVGUIMenu = false;
    }

    CMenuHandler_StringCommand(const char* pszCommand, int iClose)
    {
        strncpy(m_pszCommand, pszCommand, MAX_COMMAND_SIZE);
        m_pszCommand[MAX_COMMAND_SIZE - 1] = '\0';
        m_iCloseVGUIMenu = true;
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        gEngfuncs.pfnClientCmd(m_pszCommand);

        if (m_iCloseVGUIMenu)
            gViewPort->HideTopMenu();
        else
            gViewPort->HideCommandMenu();
    }

protected:
    char m_pszCommand[MAX_COMMAND_SIZE];
    int m_iCloseVGUIMenu;
};

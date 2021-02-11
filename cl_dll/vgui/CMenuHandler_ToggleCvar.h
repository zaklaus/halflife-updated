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
#include "cl_util.h"
#include "vgui_common.h"

class CMenuHandler_ToggleCvar : public vgui::ActionSignal
{
public:
    CMenuHandler_ToggleCvar(char* cvarname)
    {
        m_cvar = gEngfuncs.pfnGetCvarPointer(cvarname);
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        if (m_cvar->value)
            m_cvar->value = 0.0f;
        else
            m_cvar->value = 1.0f;

        // hide the menu 
        gViewPort->HideCommandMenu();

        gViewPort->UpdateSpectatorPanel();
    }

private:
    struct cvar_s* m_cvar;
};

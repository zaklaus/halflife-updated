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

#include "SpectatorPanel.h"


class CSpectatorHandler_Command : public vgui::ActionSignal
{
public:
    CSpectatorHandler_Command(SpectatorPanel* panel, int cmd)
    {
        m_pFather = panel;
        m_cmd = cmd;
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        m_pFather->ActionSignal(m_cmd);
    }
private:
    SpectatorPanel* m_pFather;
    int m_cmd;
};

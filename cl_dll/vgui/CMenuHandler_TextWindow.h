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
#include "TeamFortressViewport.h"
#include "vgui_common.h"

class CMenuHandler_TextWindow : public vgui::ActionSignal
{
public:
    CMenuHandler_TextWindow(int iState)
    {
        m_iState = iState;
    }

    void actionPerformed(vgui::Panel* panel) override
    {
        if (m_iState == HIDE_TEXTWINDOW)
        {
            gViewPort->HideTopMenu();
        }
        else
        {
            gViewPort->HideCommandMenu();
            gViewPort->ShowVGUIMenu(m_iState);
        }
    }

private:
    int m_iState;
};

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

#include <VGUI_Label.h>

// Command Label
// Overridden label so we can darken it when submenus open
class CommandLabel : public vgui::Label
{
public:
    CommandLabel(const char* text, int x, int y, int wide, int tall) : Label(text, x, y, wide, tall)
    {
        m_iState = false;
    }

    void PushUp()
    {
        m_iState = false;
        repaint();
    }

    void PushDown()
    {
        m_iState = true;
        repaint();
    }

private:
    int m_iState;
};

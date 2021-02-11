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

#include <VGUI_InputSignal.h>

#include "CMenuPanel.h"

class CHandler_MenuButtonOver : public vgui::InputSignal
{
public:
    CHandler_MenuButtonOver(CMenuPanel* pPanel, int iButton)
    {
        m_iButton = iButton;
        m_pMenuPanel = pPanel;
    }

    void cursorEntered(vgui::Panel* panel) override;

    void cursorMoved(int x, int y, vgui::Panel* panel) override { return; }
    void mousePressed(vgui::MouseCode code, vgui::Panel* panel) override { return; }
    void mouseReleased(vgui::MouseCode code, vgui::Panel* panel) override { return; }
    void mouseDoublePressed(vgui::MouseCode code, vgui::Panel* panel) override { return; }
    void cursorExited(vgui::Panel* panel) override { return; }
    void mouseWheeled(int delta, vgui::Panel* panel) override { return; }
    void keyPressed(vgui::KeyCode code, vgui::Panel* panel) override { return; }
    void keyTyped(vgui::KeyCode code, vgui::Panel* panel) override { return; }
    void keyReleased(vgui::KeyCode code, vgui::Panel* panel) override { return; }
    void keyFocusTicked(vgui::Panel* panel) override { return; }

private:
    int m_iButton;
    CMenuPanel* m_pMenuPanel;
};

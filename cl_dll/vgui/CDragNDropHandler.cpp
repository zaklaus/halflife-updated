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
* Valve LLC.  All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/

#include <VGUI_App.h>

#include "CDragNDropHandler.h"

using namespace vgui;

CDragNDropHandler::CDragNDropHandler(DragNDropPanel* pPanel)
{
    m_pPanel = pPanel;
    m_bDragging = false;
}

void CDragNDropHandler::cursorMoved(int x, int y, Panel* panel)
{
    if (m_bDragging)
    {
        App::getInstance()->getCursorPos(x, y);
        m_pPanel->setPos(m_iaDragOrgPos[0] + (x - m_iaDragStart[0]), m_iaDragOrgPos[1] + (y - m_iaDragStart[1]));

        if (m_pPanel->getParent() != null)
        {
            m_pPanel->getParent()->repaint();
        }
    }
}

void CDragNDropHandler::mousePressed(MouseCode code, Panel* panel)
{
    int x, y;
    App::getInstance()->getCursorPos(x, y);
    m_bDragging = true;
    m_iaDragStart[0] = x;
    m_iaDragStart[1] = y;
    m_pPanel->getPos(m_iaDragOrgPos[0], m_iaDragOrgPos[1]);
    App::getInstance()->setMouseCapture(panel);

    m_pPanel->setDragged(m_bDragging);
    m_pPanel->requestFocus();
}

void CDragNDropHandler::mouseReleased(MouseCode code, Panel* panel)
{
    m_bDragging = false;
    m_pPanel->setDragged(m_bDragging);
    vgui::App::getInstance()->setMouseCapture(null);
}

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

#include "DragNDropPanel.h"
#include "CDragNDropHandler.h"

DragNDropPanel::DragNDropPanel(int x, int y, int wide, int tall): Panel(x, y, wide, tall)
{
    m_bBeingDragged = false;

    // Create the Drag Handler
    addInputSignal(new CDragNDropHandler(this));

    // Create the border (for dragging)
    m_pBorder = new vgui::LineBorder();
}

void DragNDropPanel::setDragged(bool bState)
{
    m_bBeingDragged = bState;

    if (m_bBeingDragged)
        setBorder(m_pBorder);
    else
        setBorder(NULL);
}

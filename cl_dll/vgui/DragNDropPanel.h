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

#include <VGUI_LineBorder.h>
#include <VGUI_Panel.h>

// Panel that can be dragged around
class DragNDropPanel : public vgui::Panel
{
public:
    DragNDropPanel(int x, int y, int wide, int tall);

    virtual void setDragged(bool bState);

private:
    bool m_bBeingDragged;
    vgui::LineBorder* m_pBorder;
};

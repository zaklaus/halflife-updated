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

#include <VGUI_BitmapTGA.h>
#include <VGUI_Label.h>

#include "DragNDropPanel.h"

class CHealthPanel : public DragNDropPanel
{
public:
    CHealthPanel(int x, int y, int wide, int tall);

    void paintBackground() override { return; }
    void paint();
private:
    vgui::BitmapTGA* m_pHealthTGA;
    vgui::Label* m_pHealthLabel;
};

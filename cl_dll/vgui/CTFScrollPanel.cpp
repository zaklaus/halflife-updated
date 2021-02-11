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

#include <VGUI_ScrollBar.h>

#include "CTFScrollPanel.h"
#include "CTFScrollButton.h"
#include "CTFSlider.h"

using namespace vgui;

CTFScrollPanel::CTFScrollPanel(int x, int y, int wide, int tall) : ScrollPanel(x, y, wide, tall)
{
    ScrollBar* pScrollBar = getVerticalScrollBar();
    pScrollBar->setButton(new CTFScrollButton(ARROW_UP, "", 0, 0, 16, 16), 0);
    pScrollBar->setButton(new CTFScrollButton(ARROW_DOWN, "", 0, 0, 16, 16), 1);
    pScrollBar->setSlider(new CTFSlider(0, wide - 1, wide, (tall - (wide * 2)) + 2, true));
    pScrollBar->setPaintBorderEnabled(false);
    pScrollBar->setPaintBackgroundEnabled(false);
    pScrollBar->setPaintEnabled(false);

    pScrollBar = getHorizontalScrollBar();
    pScrollBar->setButton(new CTFScrollButton(ARROW_LEFT, "", 0, 0, 16, 16), 0);
    pScrollBar->setButton(new CTFScrollButton(ARROW_RIGHT, "", 0, 0, 16, 16), 1);
    pScrollBar->setSlider(new CTFSlider(tall, 0, wide - (tall * 2), tall, false));
    pScrollBar->setPaintBorderEnabled(false);
    pScrollBar->setPaintBackgroundEnabled(false);
    pScrollBar->setPaintEnabled(false);
}

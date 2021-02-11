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

#include "SpectToggleButton.h"

SpectToggleButton::SpectToggleButton(const char* cvarname, const char* text, int x, int y, int wide, int tall, bool flat):
    CommandButton(text, x, y, wide, tall, false, flat)
{
    m_cvar = gEngfuncs.pfnGetCvarPointer(cvarname);

    // Put a > to show it's a submenu
    pLabelOn = new CImageLabel("checked", 0, 0);
    pLabelOn->setParent(this);
    pLabelOn->addInputSignal(this);


    int textwide, texttall;
    getTextSize(textwide, texttall);

    // Reposition
    pLabelOn->setPos(textwide, (tall - pLabelOn->getTall()) / 2);
}

void SpectToggleButton::cursorEntered(Panel* panel)
{
    CommandButton::cursorEntered();
}

void SpectToggleButton::cursorExited(Panel* panel)
{
    CommandButton::cursorExited();
}

void SpectToggleButton::mousePressed(vgui::MouseCode code, Panel* panel)
{
    doClick();
}

void SpectToggleButton::paintBackground()
{
    if (isArmed())
    {
        drawSetColor(143, 143, 54, 125);
        drawFilledRect(5, 0, _size[0] - 5, _size[1]);
    }
}

void SpectToggleButton::paint()
{
    if (isArmed())
    {
        setFgColor(194, 202, 54, 0);
    }
    else
    {
        setFgColor(143, 143, 54, 15);
    }

    if (!m_cvar)
    {
        pLabelOn->setVisible(false);
    }
    else if (m_cvar->value)
    {
        pLabelOn->setVisible(true);
    }
    else
    {
        pLabelOn->setVisible(false);
    }

    Button::paint();
}

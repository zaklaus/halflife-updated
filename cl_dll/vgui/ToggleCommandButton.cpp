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

#include "ToggleCommandButton.h"

ToggleCommandButton::ToggleCommandButton(const char* cvarname, const char* text, int x, int y, int wide, int tall, bool flat):
    CommandButton(text, x, y, wide, tall, false, flat)
{
    m_cvar = gEngfuncs.pfnGetCvarPointer(cvarname);

    // Put a > to show it's a submenu
    pLabelOn = new CImageLabel("checked", 0, 0);
    pLabelOn->setParent(this);
    pLabelOn->addInputSignal(this);

    pLabelOff = new CImageLabel("unchecked", 0, 0);
    pLabelOff->setParent(this);
    pLabelOff->setEnabled(true);
    pLabelOff->addInputSignal(this);

    int textwide, texttall;
    getTextSize(textwide, texttall);

    // Reposition
    pLabelOn->setPos(textwide, (tall - pLabelOn->getTall()) / 2);

    pLabelOff->setPos(textwide, (tall - pLabelOff->getTall()) / 2);

    // Set text color to orange
    setFgColor(vgui::Scheme::sc_primary1);
}

void ToggleCommandButton::paint()
{
    if (!m_cvar)
    {
        pLabelOff->setVisible(false);
        pLabelOn->setVisible(false);
    }
    else if (m_cvar->value)
    {
        pLabelOff->setVisible(false);
        pLabelOn->setVisible(true);
    }
    else
    {
        pLabelOff->setVisible(true);
        pLabelOn->setVisible(false);
    }

    CommandButton::paint();
}

void ToggleCommandButton::cursorEntered(Panel* panel)
{
    CommandButton::cursorEntered();
}

void ToggleCommandButton::cursorExited(Panel* panel)
{
    CommandButton::cursorExited();
}

void ToggleCommandButton::mousePressed(vgui::MouseCode code, Panel* panel)
{
    doClick();
}

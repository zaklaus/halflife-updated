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

#include "CImageLabel.h"
#include "hud/CHud.h"
#include "ColorButton.h"

// Command menu root button (drop down box style)
class DropDownButton : public ColorButton
{
public:

    DropDownButton(const char* text, int x, int y, int wide, int tall, bool bNoHighlight, bool bFlat) :
        ColorButton(text, x, y, wide, tall, bNoHighlight, bFlat)
    {
        // Put a > to show it's a submenu
        m_pOpenButton = new CImageLabel("arrowup", XRES(CMENU_SIZE_X-2), YRES(BUTTON_SIZE_Y-2));
        m_pOpenButton->setParent(this);

        int textwide, texttall;
        getSize(textwide, texttall);

        // Reposition
        m_pOpenButton->setPos(textwide - (m_pOpenButton->getImageWide() + 6), -2 /*(tall - m_pOpenButton->getImageTall()*2) / 2*/);
        m_pOpenButton->setVisible(true);
    }

    void setVisible(bool state) override
    {
        m_pOpenButton->setVisible(state);
        ColorButton::setVisible(state);
    }

private:
    CImageLabel* m_pOpenButton;
};

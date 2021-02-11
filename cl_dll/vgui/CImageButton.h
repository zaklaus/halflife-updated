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
#include "ColorButton.h"

// Button with image instead of text
class CImageButton : public ColorButton
{
public:

    CImageButton(const char* text, int x, int y, int wide, int tall, bool bNoHighlight, bool bFlat) :
        ColorButton(" ", x, y, wide, tall, bNoHighlight, bFlat)
    {
        m_pOpenButton = new CImageLabel(text, 1, 1, wide - 2, tall - 2);
        m_pOpenButton->setParent(this);

        // Reposition
        //	m_pOpenButton->setPos( x+1,y+1 );
        //	m_pOpenButton->setSize(wide-2,tall-2);

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

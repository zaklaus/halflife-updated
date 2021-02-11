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

#include "CommandButton.h"

class SpectButton : public CommandButton
{
public:
    SpectButton(int iPlayerClass, const char* text, int x, int y, int wide, int tall) :
        CommandButton(text, x, y, wide, tall, false)
    {
        Init();

        setText(text);
    }

    void paintBackground() override
    {
        if (isArmed())
        {
            drawSetColor(143, 143, 54, 125);
            drawFilledRect(5, 0, _size[0] - 5, _size[1]);
        }
    }

    void paint() override
    {
        if (isArmed())
        {
            setFgColor(194, 202, 54, 0);
        }
        else
        {
            setFgColor(143, 143, 54, 15);
        }

        Button::paint();
    }
};

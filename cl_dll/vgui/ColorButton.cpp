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

#include "ColorButton.h"

ColorButton::ColorButton(const char* text, int x, int y, int wide, int tall, bool bNoHighlight, bool bFlat):
    CommandButton(text, x, y, wide, tall, bNoHighlight, bFlat)
{
    ArmedColor = NULL;
    UnArmedColor = NULL;
    ArmedBorderColor = NULL;
    UnArmedBorderColor = NULL;
}

void ColorButton::paintBackground()
{
    int r, g, b, a;
    vgui::Color bgcolor;

    if (isArmed())
    {
        // Highlight background
        /*	getBgColor(bgcolor);
            bgcolor.getColor(r, g, b, a);
            drawSetColor( r,g,b,a );
            drawFilledRect(0,0,_size[0],_size[1]);*/

        if (ArmedBorderColor)
        {
            ArmedBorderColor->getColor(r, g, b, a);
            drawSetColor(r, g, b, a);
            drawOutlinedRect(0, 0, _size[0], _size[1]);
        }
    }
    else
    {
        if (UnArmedBorderColor)
        {
            UnArmedBorderColor->getColor(r, g, b, a);
            drawSetColor(r, g, b, a);
            drawOutlinedRect(0, 0, _size[0], _size[1]);
        }
    }
}

void ColorButton::paint()
{
    int r, g, b, a;
    if (isArmed())
    {
        if (ArmedColor)
        {
            ArmedColor->getColor(r, g, b, a);
            setFgColor(r, g, b, a);
        }
        else
            setFgColor(vgui::Scheme::sc_secondary2);
    }
    else
    {
        if (UnArmedColor)
        {
            UnArmedColor->getColor(r, g, b, a);
            setFgColor(r, g, b, a);
        }
        else
            setFgColor(vgui::Scheme::sc_primary1);
    }

    Button::paint();
}

void ColorButton::setArmedColor(int r, int g, int b, int a)
{
    ArmedColor = new vgui::Color(r, g, b, a);
}

void ColorButton::setUnArmedColor(int r, int g, int b, int a)
{
    UnArmedColor = new vgui::Color(r, g, b, a);
}

void ColorButton::setArmedBorderColor(int r, int g, int b, int a)
{
    ArmedBorderColor = new vgui::Color(r, g, b, a);
}

void ColorButton::SetUnArmedBorderColor(int r, int g, int b, int a)
{
    UnArmedBorderColor = new vgui::Color(r, g, b, a);
}

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

class ColorButton : public CommandButton
{
public:
    ColorButton(const char* text, int x, int y, int wide, int tall, bool bNoHighlight, bool bFlat);

    void paintBackground() override;
    void paint() override;
    void setArmedColor(int r, int g, int b, int a);
    void setUnArmedColor(int r, int g, int b, int a);
    void setArmedBorderColor(int r, int g, int b, int a);
    void SetUnArmedBorderColor(int r, int g, int b, int a);

private:
    vgui::Color* ArmedColor;
    vgui::Color* UnArmedColor;

    vgui::Color* ArmedBorderColor;
    vgui::Color* UnArmedBorderColor;
};

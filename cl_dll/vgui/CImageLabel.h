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

// Wrapper for an Image Label without a background
class CImageLabel : public vgui::Label
{
public:
    vgui::BitmapTGA* m_pTGA;

public:
    void LoadImage(const char* pImageName);
    CImageLabel(const char* pImageName, int x, int y);
    CImageLabel(const char* pImageName, int x, int y, int wide, int tall);

    virtual int getImageTall();
    virtual int getImageWide();

    void paintBackground() override
    {
        // Do nothing, so the background's left transparent.
    }
};

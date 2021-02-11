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

#include <VGUI_FileInputStream.h>

#include "CHealthPanel.h"
#include "vgui_common.h"
#include "hud/CHud.h"

CHealthPanel::CHealthPanel(int x, int y, int wide, int tall): DragNDropPanel(x, y, wide, tall)
{
    // Load the Health icon
    vgui::FileInputStream* fis = new vgui::FileInputStream(GetVGUITGAName("%d_hud_health"), false);
    m_pHealthTGA = new vgui::BitmapTGA(fis, true);
    fis->close();

    // Create the Health Label
    int iXSize, iYSize;
    m_pHealthTGA->getSize(iXSize, iYSize);
    m_pHealthLabel = new vgui::Label("", 0, 0, iXSize, iYSize);
    m_pHealthLabel->setImage(m_pHealthTGA);
    m_pHealthLabel->setParent(this);

    // Set panel dimension
    // Shouldn't be needed once Billy's fized setImage not recalculating the size
    //setSize( iXSize + 100, gHUD.m_iFontHeight + 10 );
    //m_pHealthLabel->setPos( 10, (getTall() - iYSize) / 2 );
}

void CHealthPanel::paint()
{
    // Get the paint color
    int r, g, b, a;
    // Has health changed? Flash the health #
    if (gHUD.m_Health.m_fFade)
    {
        gHUD.m_Health.m_fFade -= (gHUD.m_flTimeDelta * 20);
        if (gHUD.m_Health.m_fFade <= 0)
        {
            a = MIN_ALPHA;
            gHUD.m_Health.m_fFade = 0;
        }

        // Fade the health number back to dim
        a = MIN_ALPHA + (gHUD.m_Health.m_fFade / FADE_TIME) * 128;
    }
    else
        a = MIN_ALPHA;

    gHUD.m_Health.GetPainColor(r, g, b);
    ScaleColors(r, g, b, a);

    // If health is getting low, make it bright red
    if (gHUD.m_Health.m_iHealth <= 15)
        a = 255;

    int iXSize, iYSize, iXPos, iYPos;
    m_pHealthTGA->getSize(iXSize, iYSize);
    m_pHealthTGA->getPos(iXPos, iYPos);

    // Paint the player's health
    int x = gHUD.DrawHudNumber(iXPos + iXSize + 5, iYPos + 5, DHN_3DIGITS | DHN_DRAWZERO, gHUD.m_Health.m_iHealth, r, g, b);

    // Draw the vertical line
    int HealthWidth = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).right - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).left;
    x += HealthWidth / 2;
    FillRGBA(x, iYPos + 5, HealthWidth / 10, gHUD.m_iFontHeight, 255, 160, 0, a);
}

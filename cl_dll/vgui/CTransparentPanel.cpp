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

#include "CTransparentPanel.h"

CTransparentPanel::CTransparentPanel(int iTrans, int x, int y, int wide, int tall): Panel(x, y, wide, tall)
{
    m_iTransparency = iTrans;
}

void CTransparentPanel::paintBackground()
{
    if (m_iTransparency)
    {
        // Transparent black background
        drawSetColor(0, 0, 0, m_iTransparency);
        drawFilledRect(0, 0, _size[0], _size[1]);
    }
}

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

#include "CMenuPanel.h"
#include "hud/CHud.h"
#include "TeamFortressViewport.h"

CMenuPanel::CMenuPanel(int iRemoveMe, int x, int y, int wide, int tall): CTransparentPanel(100, x, y, wide, tall)
{
    Reset();
    m_iRemoveMe = iRemoveMe;
}

CMenuPanel::CMenuPanel(int iTrans, int iRemoveMe, int x, int y, int wide, int tall): CTransparentPanel(iTrans, x, y, wide, tall)
{
    Reset();
    m_iRemoveMe = iRemoveMe;
}

void CMenuPanel::Reset()
{
    m_pNextMenu = NULL;
    m_iIsActive = false;
    m_flOpenTime = 0;
}

void CMenuPanel::SetNextMenu(CMenuPanel* pNextPanel)
{
    if (m_pNextMenu)
        m_pNextMenu->SetNextMenu(pNextPanel);
    else
        m_pNextMenu = pNextPanel;
}

void CMenuPanel::SetMenuID(int iID)
{
    m_iMenuID = iID;
}

void CMenuPanel::SetActive(int iState)
{
    m_iIsActive = iState;
}

void CMenuPanel::Open()
{
    setVisible(true);

    // Note the open time, so we can delay input for a bit
    m_flOpenTime = gHUD.m_flTime;
}

void CMenuPanel::Close()
{
    setVisible(false);
    m_iIsActive = false;

    if (m_iRemoveMe)
        gViewPort->removeChild(this);

    // This MenuPanel has now been deleted. Don't append code here.
}

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

#include <VGUI_LineBorder.h>

#include "hud/CHud.h"
#include "cl_util.h"
#include "CClassMenuPanel.h"

#include "CMenuHandler_TextWindow.h"
#include "CTFScrollPanel.h"
#include "TeamFortressViewport.h"

using namespace vgui;

// Creation
CClassMenuPanel::CClassMenuPanel(int iTrans, int iRemoveMe, int x, int y, int wide, int tall) : CMenuPanel(iTrans, iRemoveMe, x, y, wide, tall)
{
    // don't show class graphics at below 640x480 resolution
    bool bShowClassGraphic = true;
    if (ScreenWidth < 640)
    {
        bShowClassGraphic = false;
    }

    memset(m_pClassImages, 0, sizeof(m_pClassImages));

    // Get the scheme used for the Titles
    CSchemeManager* pSchemes = gViewPort->GetSchemeManager();

    // schemes
    SchemeHandle_t hTitleScheme = pSchemes->getSchemeHandle("Title Font");
    SchemeHandle_t hClassWindowText = pSchemes->getSchemeHandle("Briefing Text");

    // color schemes
    int r, g, b, a;

    // Create the title
    Label* pLabel = new Label("", CLASSMENU_TITLE_X, CLASSMENU_TITLE_Y);
    pLabel->setParent(this);
    pLabel->setFont(pSchemes->getFont(hTitleScheme));
    pSchemes->getFgColor(hTitleScheme, r, g, b, a);
    pLabel->setFgColor(r, g, b, a);
    pSchemes->getBgColor(hTitleScheme, r, g, b, a);
    pLabel->setBgColor(r, g, b, a);
    pLabel->setContentAlignment(vgui::Label::a_west);
    pLabel->setText(gHUD.m_TextMessage.BufferedLocaliseTextString("#Title_SelectYourClass"));

    // Create the Scroll panel
    m_pScrollPanel = new CTFScrollPanel(CLASSMENU_WINDOW_X, CLASSMENU_WINDOW_Y, CLASSMENU_WINDOW_SIZE_X, CLASSMENU_WINDOW_SIZE_Y);
    m_pScrollPanel->setParent(this);
    //force the scrollbars on, so after the validate clientClip will be smaller
    m_pScrollPanel->setScrollBarAutoVisible(false, false);
    m_pScrollPanel->setScrollBarVisible(true, true);
    m_pScrollPanel->setBorder(new LineBorder(Color(255 * 0.7, 170 * 0.7, 0, 0)));
    m_pScrollPanel->validate();

    int clientWide = m_pScrollPanel->getClient()->getWide();

    //turn scrollpanel back into auto show scrollbar mode and validate
    m_pScrollPanel->setScrollBarAutoVisible(false, true);
    m_pScrollPanel->setScrollBarVisible(false, false);
    m_pScrollPanel->validate();

    // Create the Cancel button
    m_pCancelButton = new CommandButton(gHUD.m_TextMessage.BufferedLocaliseTextString("#Menu_Cancel"), CLASSMENU_TOPLEFT_BUTTON_X, 0, CLASSMENU_BUTTON_SIZE_X,
                                        CLASSMENU_BUTTON_SIZE_Y);
    m_pCancelButton->setParent(this);
    m_pCancelButton->addActionSignal(new CMenuHandler_TextWindow(HIDE_TEXTWINDOW));

    m_iCurrentInfo = 0;
}


// Update
void CClassMenuPanel::Update()
{
    // Don't allow the player to join a team if they're not in a team
    if (!g_iTeamNumber)
        return;

    int iYPos = CLASSMENU_TOPLEFT_BUTTON_Y;

    // If the player already has a class, make the cancel button visible
    if (g_iPlayerClass)
    {
        m_pCancelButton->setPos(CLASSMENU_TOPLEFT_BUTTON_X, iYPos);
        m_pCancelButton->setVisible(true);
    }
    else
    {
        m_pCancelButton->setVisible(false);
    }
}

//======================================
// Key inputs for the Class Menu
bool CClassMenuPanel::SlotInput(int iSlot)
{
    if ((iSlot < 0) || (iSlot > 9))
        return false;
    if (!m_pButtons[iSlot])
        return false;

    // Is the button pushable? (0 is special case)
    if (iSlot == 0)
    {
        // Selects Civilian and RandomPC
        if (gViewPort->GetValidClasses(g_iTeamNumber) == -1)
        {
            m_pButtons[0]->fireActionSignal();
            return true;
        }

        // Select RandomPC
        iSlot = 10;
    }

    if (!(m_pButtons[iSlot]->IsNotValid()))
    {
        m_pButtons[iSlot]->fireActionSignal();
        return true;
    }

    return false;
}

//======================================
// Update the Class menu before opening it
void CClassMenuPanel::Open(void)
{
    Update();
    CMenuPanel::Open();
}

//-----------------------------------------------------------------------------
// Purpose: Called each time a new level is started.
//-----------------------------------------------------------------------------
void CClassMenuPanel::Initialize(void)
{
    setVisible(false);
    m_pScrollPanel->setScrollValue(0, 0);
}

void CClassMenuPanel::Reset()
{
    CMenuPanel::Reset();
    m_iCurrentInfo = 0;
}

//======================================
// Mouse is over a class button, bring up the class info
void CClassMenuPanel::SetActiveInfo(int iInput)
{
    // Remove all the Info panels and bring up the specified one
#ifdef _TFC
	for (int i = 0; i <= PC_RANDOM; i++)
	{
		m_pButtons[i]->setArmed(false);
		m_pClassInfoPanel[i]->setVisible(false);
	}

	if (iInput > PC_RANDOM || iInput < 0)
#endif
    iInput = 0;

    m_pButtons[iInput]->setArmed(true);
    m_pClassInfoPanel[iInput]->setVisible(true);
    m_iCurrentInfo = iInput;

    m_pScrollPanel->setScrollValue(0, 0);
    m_pScrollPanel->validate();
}

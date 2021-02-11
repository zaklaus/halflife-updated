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

#include <global_consts.h>
#include <VGUI_Label.h>
#include <VGUI_ScrollPanel.h>

#include "CImageLabel.h"
#include "ClassButton.h"
#include "CMenuPanel.h"
#include "CommandButton.h"
#include "CTransparentPanel.h"

// Class Menu Dimensions
#define CLASSMENU_TITLE_X				XRES(40)
#define CLASSMENU_TITLE_Y				YRES(32)
#define CLASSMENU_TOPLEFT_BUTTON_X		XRES(40)
#define CLASSMENU_TOPLEFT_BUTTON_Y		YRES(80)
#define CLASSMENU_BUTTON_SIZE_X			XRES(124)
#define CLASSMENU_BUTTON_SIZE_Y			YRES(24)
#define CLASSMENU_BUTTON_SPACER_Y		YRES(8)
#define CLASSMENU_WINDOW_X				XRES(176)
#define CLASSMENU_WINDOW_Y				YRES(80)
#define CLASSMENU_WINDOW_SIZE_X			XRES(424)
#define CLASSMENU_WINDOW_SIZE_Y			YRES(312)
#define CLASSMENU_WINDOW_TEXT_X			XRES(150)
#define CLASSMENU_WINDOW_TEXT_Y			YRES(80)
#define CLASSMENU_WINDOW_NAME_X			XRES(150)
#define CLASSMENU_WINDOW_NAME_Y			YRES(8)
#define CLASSMENU_WINDOW_PLAYERS_Y		YRES(42)

class CClassMenuPanel : public CMenuPanel
{
public:
    CClassMenuPanel(int iTrans, int iRemoveMe, int x, int y, int wide, int tall);

    bool SlotInput(int iSlot) override;
    void Open(void) override;
    virtual void Update(void);
    void SetActiveInfo(int iInput) override;
    virtual void Initialize(void);
    void Reset(void) override;

private:
    CTransparentPanel* m_pClassInfoPanel[PC_LASTCLASS];
    vgui::Label* m_pPlayers[PC_LASTCLASS];
    ClassButton* m_pButtons[PC_LASTCLASS];
    CommandButton* m_pCancelButton;
    vgui::ScrollPanel* m_pScrollPanel;

    CImageLabel* m_pClassImages[MAX_TEAMS][PC_LASTCLASS];

    int m_iCurrentInfo;

    enum { STRLENMAX_PLAYERSONTEAM = 128 };

    char m_sPlayersOnTeamString[STRLENMAX_PLAYERSONTEAM];
};

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

#include <VGUI_Panel.h>
#include <VGUI_Button.h>

#include "CImageButton.h"
#include "DropDownButton.h"

#define SPECTATOR_PANEL_CMD_NONE				0

#define SPECTATOR_PANEL_CMD_OPTIONS				1
#define	SPECTATOR_PANEL_CMD_PREVPLAYER			2
#define SPECTATOR_PANEL_CMD_NEXTPLAYER			3
#define	SPECTATOR_PANEL_CMD_HIDEMENU			4
#define	SPECTATOR_PANEL_CMD_TOGGLE_INSET		5
#define SPECTATOR_PANEL_CMD_CAMERA				6
#define SPECTATOR_PANEL_CMD_PLAYERS				7

// spectator panel sizes
#define PANEL_HEIGHT 64

#define BANNER_WIDTH	256
#define BANNER_HEIGHT	64

#define OPTIONS_BUTTON_X 96
#define CAMOPTIONS_BUTTON_X 200

#define SEPERATOR_WIDTH 15
#define SEPERATOR_HEIGHT 15

#define TEAM_NUMBER 2

class SpectatorPanel : public vgui::Panel //, public vgui::CDefaultInputSignal
{
public:
    SpectatorPanel(int x, int y, int wide, int tall);
    virtual ~SpectatorPanel();

    void ActionSignal(int cmd);

    // InputSignal overrides.
    void Initialize();
    void Update();

    void EnableInsetView(bool isEnabled);
    void ShowMenu(bool isVisible);

public:
    DropDownButton* m_OptionButton;
    //	CommandButton     *	m_HideButton;
    //ColorButton	  *	m_PrevPlayerButton;
    //ColorButton	  *	m_NextPlayerButton;
    CImageButton* m_PrevPlayerButton;
    CImageButton* m_NextPlayerButton;
    DropDownButton* m_CamButton;

    CTransparentPanel* m_TopBorder;
    CTransparentPanel* m_BottomBorder;

    ColorButton* m_InsetViewButton;

    DropDownButton* m_BottomMainButton;
    CImageLabel* m_TimerImage;
    vgui::Label* m_BottomMainLabel;
    vgui::Label* m_CurrentTime;
    vgui::Label* m_ExtraInfo;
    Panel* m_Separator;

    vgui::Label* m_TeamScores[TEAM_NUMBER];

    CImageLabel* m_TopBanner;

    bool m_menuVisible;
    bool m_insetVisible;
};

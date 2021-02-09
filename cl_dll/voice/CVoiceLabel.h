//========= Copyright © 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
#pragma once

#include "VGUI_ImagePanel.h"
#include "VGUI_Button.h"

class CVoiceLabel
{
public:
    vgui::Label* m_pLabel;
    vgui::Label* m_pBackground;
    vgui::ImagePanel* m_pIcon; // Voice icon next to player name.
    int m_clientindex; // Client index of the speaker. -1 if this label isn't being used.
};

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

#include "CHandler_ButtonHighlight.h"
#include "CommandButton.h"

class CHandler_CommandButtonHighlight : public CHandler_ButtonHighlight
{
public:
    CHandler_CommandButtonHighlight(CommandButton* pButton) : CHandler_ButtonHighlight(pButton)
    {
        m_pCommandButton = pButton;
    }

    void cursorEntered(vgui::Panel* panel) override
    {
        m_pCommandButton->cursorEntered();
    }

    void cursorExited(vgui::Panel* panel) override
    {
        m_pCommandButton->cursorExited();
    }

private:
    CommandButton* m_pCommandButton;
};

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

#include "CHandler_MenuButtonOver.h"
#include "TeamFortressViewport.h"

using namespace vgui;

void CHandler_MenuButtonOver::cursorEntered(Panel* panel)
{
    if (gViewPort && m_pMenuPanel)
    {
        m_pMenuPanel->SetActiveInfo(m_iButton);
    }
}

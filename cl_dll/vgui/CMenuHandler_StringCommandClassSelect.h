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

#include "CMenuHandler_StringCommand.h"

using namespace vgui;

// Used instead of CMenuHandler_StringCommand for Class Selection buttons.
// Checks the state of hud_classautokill and kills the player if set
class CMenuHandler_StringCommandClassSelect : public CMenuHandler_StringCommand
{
public:
    CMenuHandler_StringCommandClassSelect(const char* pszCommand) : CMenuHandler_StringCommand(pszCommand)
    {
    }

    CMenuHandler_StringCommandClassSelect(const char* pszCommand, int iClose) : CMenuHandler_StringCommand(pszCommand, iClose)
    {
    }

    void actionPerformed(Panel* panel) override;
};

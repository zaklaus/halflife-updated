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

#include "CommandButton.h"

extern int iBuildingCosts[];

#define BUILDSTATE_HASBUILDING		(1<<0)		// Data is building ID (1 = Dispenser, 2 = Sentry, 3 = Entry Teleporter, 4 = Exit Teleporter)
#define BUILDSTATE_BUILDING			(1<<1)
#define BUILDSTATE_BASE				(1<<2)
#define BUILDSTATE_CANBUILD			(1<<3)		// Data is building ID (1 = Dispenser, 2 = Sentry, 3 = Entry Teleporter, 4 = Exit Teleporter)

class BuildButton : public CommandButton
{
public:
    BuildButton(int iState, int iData, const char* text, int x, int y, int wide, int tall) : CommandButton(text, x, y, wide, tall)
    {
        m_iBuildState = iState;
        m_iBuildData = iData;
    }

    int IsNotValid() override { return false; }

private:
    int m_iBuildState;
    int m_iBuildData;
};

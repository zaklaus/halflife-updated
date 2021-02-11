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

#define		DISGUISE_TEAM1		(1<<0)
#define		DISGUISE_TEAM2		(1<<1)
#define		DISGUISE_TEAM3		(1<<2)
#define		DISGUISE_TEAM4		(1<<3)

class DisguiseButton : public CommandButton
{
public:
    DisguiseButton(int iValidTeamNumsBits, const char* text, int x, int y, int wide, int tall) : CommandButton(text, x, y, wide, tall, false)
    {
        m_iValidTeamsBits = iValidTeamNumsBits;
    }

    int IsNotValid() override
    {
#ifdef _TFC
		// Only visible for spies
		if ( g_iPlayerClass != PC_SPY )
			return true;
#endif

        // if it's not tied to a specific team, then always show (for spies)
        if (!m_iValidTeamsBits)
            return false;

        // if we're tied to a team make sure we can change to that team
        int iTmp = 1 << (gViewPort->GetNumberOfTeams() - 1);
        if (m_iValidTeamsBits & iTmp)
            return false;
        return true;
    }

private:
    int m_iValidTeamsBits;
    int m_iThisTeam;
};

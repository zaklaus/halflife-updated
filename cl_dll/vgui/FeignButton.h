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

class FeignButton : public CommandButton
{
public:
    FeignButton(int iState, const char* text, int x, int y, int wide, int tall) : CommandButton(text, x, y, wide, tall)
    {
        m_iFeignState = iState;
    }

    int IsNotValid() override
    {
        // Only visible for spies
#ifdef _TFC
		if (g_iPlayerClass != PC_SPY)
			return true;
#endif

        if (m_iFeignState == gViewPort->GetIsFeigning())
            return false;
        return true;
    }

private:
    int m_iFeignState;
};

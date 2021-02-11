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

#include "ClassButton.h"
#include "TeamFortressViewport.h"
#include "hud/hud.h"

ClassButton::ClassButton(int iClass, const char* text, int x, int y, int wide, int tall, bool bNoHighlight): CommandButton(text, x, y, wide, tall, bNoHighlight)
{
    m_iPlayerClass = iClass;
}

int ClassButton::IsNotValid()
{
    // If this is the main ChangeClass button, remove it if the player's only able to be civilians
    if (m_iPlayerClass == -1)
    {
        if (gViewPort->GetValidClasses(g_iTeamNumber) == -1)
            return true;

        return false;
    }

    // Is it an illegal class?
#ifdef _TFC
    if ((gViewPort->GetValidClasses(0) & sTFValidClassInts[m_iPlayerClass]) || (gViewPort->GetValidClasses(g_iTeamNumber) & sTFValidClassInts[m_iPlayerClass]))
        return true;
#endif

    // Only check current class if they've got autokill on
    bool bAutoKill = CVAR_GET_FLOAT("hud_classautokill") != 0;
    if (bAutoKill)
    {
        // Is it the player's current class?
        if (
#ifdef _TFC
        (gViewPort->IsRandomPC() && m_iPlayerClass == PC_RANDOM) ||
#endif
            (!gViewPort->IsRandomPC() && (m_iPlayerClass == g_iPlayerClass)))
            return true;
    }

    return false;
}

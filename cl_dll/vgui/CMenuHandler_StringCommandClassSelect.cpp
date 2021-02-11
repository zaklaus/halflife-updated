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

#include "CMenuHandler_StringCommandClassSelect.h"
#include "hud/CHud.h"

using namespace vgui;

void CMenuHandler_StringCommandClassSelect::actionPerformed(Panel* panel)
{
    CMenuHandler_StringCommand::actionPerformed(panel);

    // THIS IS NOW BEING DONE ON THE TFC SERVER TO AVOID KILLING SOMEONE THEN 
    // HAVE THE SERVER SAY "SORRY...YOU CAN'T BE THAT CLASS".

#if !defined _TFC
    bool bAutoKill = CVAR_GET_FLOAT("hud_classautokill") != 0;
    if (bAutoKill && g_iPlayerClass != 0)
        gEngfuncs.pfnClientCmd("kill");
#endif
}

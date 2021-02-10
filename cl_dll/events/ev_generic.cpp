/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "ev_common.h"

extern "C" {
void EV_GenericFire1(struct event_args_s* args);
void EV_GenericFire2(struct event_args_s* args);
void EV_GenericFire3(struct event_args_s* args);
}

enum generic_e
{
    GENERIC_IDLE1 = 0,
    GENERIC_IDLE2,
    GENERIC_IDLE3,
    GENERIC_SHOOT,
    GENERIC_SHOOT2,
    GENERIC_RELOAD,
    GENERIC_RELOAD2,
    GENERIC_DRAW,
    GENERIC_HOLSTER,
    GENERIC_SPECIAL
};

void EV_GenericFire1(struct event_args_s* args)
{
    //NULL EVENT
}

void EV_GenericFire2(struct event_args_s* args)
{
    //NULL EVENT
}

void EV_GenericFire3(struct event_args_s* args)
{
    //NULL EVENT
}

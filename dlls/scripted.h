/***
*
*    Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*    
*    This product contains software technology licensed from Id 
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*    All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/
#ifndef SCRIPTED_H
#define SCRIPTED_H

#ifndef SCRIPTEVENT_H
#include "scriptevent.h"
#endif

#define SF_SCRIPT_WAITTILLSEEN        1
#define SF_SCRIPT_EXITAGITATED        2
#define SF_SCRIPT_REPEATABLE        4
#define SF_SCRIPT_LEAVECORPSE        8
//#define SF_SCRIPT_INTERPOLATE        16 // don't use, old bug
#define SF_SCRIPT_NOINTERRUPT        32
#define SF_SCRIPT_OVERRIDESTATE        64
#define SF_SCRIPT_NOSCRIPTMOVEMENT    128
#define SF_SCRIPT_STAYDEAD            256 // LRC- signifies that the animation kills the monster
                                        // (needed because the monster animations don't use AnimEvent 1000 properly)

#define SCRIPT_BREAK_CONDITIONS        (bits_COND_LIGHT_DAMAGE|bits_COND_HEAVY_DAMAGE)

//LRC - rearranged into flags
#define SS_INTERRUPT_IDLE        0x0
#define SS_INTERRUPT_ALERT        0x1
#define SS_INTERRUPT_ANYSTATE    0x2
#define SS_INTERRUPT_SCRIPTS    0x4

// when a monster finishes an AI scripted sequence, we can choose
// a schedule to place them in. These defines are the aliases to
// resolve worldcraft input to real schedules (sjb)
#define SCRIPT_FINISHSCHED_DEFAULT    0
#define SCRIPT_FINISHSCHED_AMBUSH    1

#endif        //SCRIPTED_H

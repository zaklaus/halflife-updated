/***
*
*    Copyright (c) 1999, 2000 Valve LLC. All rights reserved.
*    
*    This product contains software technology licensed from Id 
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*    All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "customentity.h"
#include "effects.h"
#include "weapons.h"
#include "decals.h"
#include "entities/brush/CBreakable.h"
#include "shake.h"
#include "player.h" //LRC - footstep stuff
#include "locus.h" //LRC - locus utilities
#include "movewith.h" //LRC - the DesiredThink system

#define    SF_GIBSHOOTER_REPEATABLE    1 // allows a gibshooter to be refired













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
#pragma once

/*
 * This header should be included in all client files.
 */

#include "Platform.h"

// Shared headers between the client DLL and the game DLLs
#include "../shared/types.h"
#include "../shared/Vector.h"
#include "../shared/common_defs.h"

// Compatibility mathlib since the client project doesn't (yet?) make proper use of the vector class
#include "../shared/compat_mathlib.h"

// Client DLL interface
#include "../engine/cdll_int.h"
#include "cvardef.h"

// Global engine functions
extern cl_enginefunc_t gEngfuncs;

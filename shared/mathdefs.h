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

#define M_PI 3.14159265358979323846	// matches value in gcc v2 math.h

constexpr int NANMASK = 255 << 23;
#define	IS_NAN(x) (((*(int *)&x)&NANMASK)==NANMASK)

// up / down
#define PITCH 0

// left / right
#define YAW   1

// fall over
#define ROLL  2

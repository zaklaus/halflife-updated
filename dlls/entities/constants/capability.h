/***
*
* Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
* This product contains software technology licensed from Id
* Software, Inc. (Id Technology").  Id Technology (c) 1996 Id Software, Inc.
* All Rights Reserved.
*
* Use, distribution, and modification of this source code and/or resulting
* object code is restricted to non-commercial enhancements to products from
* Valve LLC.All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/
#pragma once

#define bits_CAP_DUCK             ( 1 << 0  )  // crouch
#define bits_CAP_JUMP             ( 1 << 1  )  // jump/leap
#define bits_CAP_STRAFE           ( 1 << 2  )  // strafe ( walk/run sideways)
#define bits_CAP_SQUAD            ( 1 << 3  )  // can form squads
#define bits_CAP_SWIM             ( 1 << 4  )  // proficiently navigate in water
#define bits_CAP_CLIMB            ( 1 << 5  )  // climb ladders/ropes
#define bits_CAP_USE              ( 1 << 6  )  // open doors/push buttons/pull levers
#define bits_CAP_HEAR             ( 1 << 7  )  // can hear forced sounds
#define bits_CAP_AUTO_DOORS       ( 1 << 8  )  // can trigger auto doors
#define bits_CAP_OPEN_DOORS       ( 1 << 9  )  // can open manual doors
#define bits_CAP_TURN_HEAD        ( 1 << 10 )  // can turn head, always bone controller 0

#define bits_CAP_RANGE_ATTACK1    ( 1 << 11 )  // can do a range attack 1
#define bits_CAP_RANGE_ATTACK2    ( 1 << 12 )  // can do a range attack 2
#define bits_CAP_MELEE_ATTACK1    ( 1 << 13 )  // can do a melee attack 1
#define bits_CAP_MELEE_ATTACK2    ( 1 << 14 )  // can do a melee attack 2

#define bits_CAP_FLY              ( 1 << 15 )  // can fly, move all around

#define bits_CAP_DOORS_GROUP      (bits_CAP_USE | bits_CAP_AUTO_DOORS | bits_CAP_OPEN_DOORS)

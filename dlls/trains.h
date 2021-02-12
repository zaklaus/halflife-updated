/***
*
*    Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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
#pragma once
#ifndef TRAINS_H
#define TRAINS_H

// Tracktrain spawn flags
#define SF_TRACKTRAIN_NOPITCH        0x0001
#define SF_TRACKTRAIN_NOCONTROL        0x0002
#define SF_TRACKTRAIN_FORWARDONLY    0x0004
#define SF_TRACKTRAIN_PASSABLE        0x0008
#define SF_TRACKTRAIN_NOYAW            0x0010        //LRC
#define SF_TRACKTRAIN_AVELOCITY        0x800000    //LRC - avelocity has been set manually, don't turn.
#define SF_TRACKTRAIN_AVEL_GEARS    0x400000    //LRC - avelocity should be scaled up/down when the train changes gear.

// Spawnflag for CPathTrack
#define SF_PATH_DISABLED        0x00000001
#define SF_PATH_FIREONCE        0x00000002
#define SF_PATH_ALTREVERSE        0x00000004
#define SF_PATH_DISABLE_TRAIN    0x00000008
#define SF_PATH_ALTERNATE        0x00008000
#define SF_PATH_AVELOCITY        0x00080000 //LRC

// Spawnflags of CPathCorner
#define SF_CORNER_WAITFORTRIG    0x001
#define SF_CORNER_TELEPORT        0x002
#define SF_CORNER_FIREONCE        0x004
#define SF_CORNER_AVELOCITY     0x800000

//LRC - values in 'armortype'
#define PATHSPEED_SET            0
#define PATHSPEED_ACCEL            1
#define PATHSPEED_TIME            2
#define PATHSPEED_SET_MASTER    3

//LRC - values in 'frags'
#define PATHTURN_SET            0
#define PATHTURN_SET_MASTER        1
#define PATHTURN_RESET            2

//LRC - values in 'armorvalue'
#define PATHMATCH_NO            0
#define PATHMATCH_YES            1
#define PATHMATCH_TRACK            2

static void FixupAngles(Vector &v);


#define noiseMovement noise
#define noiseStopMoving noise1

static float Fix(float angle)
{
    if (IS_NAN(angle))
    {
        ALERT(at_debug, "NaN error during Fix!\n");
        return angle;
    }
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;

    return angle;
}

static void FixupAngles(Vector& v)
{
    v.x = Fix(v.x);
    v.y = Fix(v.y);
    v.z = Fix(v.z);
}

#endif

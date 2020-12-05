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
#ifndef DOORS_H
#define DOORS_H

// doors
#define SF_DOOR_ROTATE_Y            0
#define SF_DOOR_START_OPEN          1
#define SF_DOOR_ROTATE_BACKWARDS    2
#define SF_DOOR_PASSABLE            8
#define SF_DOOR_ONEWAY              16
#define SF_DOOR_NO_AUTO_RETURN      32
#define SF_DOOR_ROTATE_Z            64
#define SF_DOOR_ROTATE_X            128
#define SF_DOOR_USE_ONLY            256    // door must be opened by player's use button.
#define SF_DOOR_NOMONSTERS          512    // Monster can't open
#define SF_DOOR_FORCETOUCHABLE      1024   //LRC- Opens when touched, even though it's named and/or "use only"
//LRC - clashes with 'not in deathmatch'. Replaced with 'Target mode' and 'On/Off Mode' fields.
//#define SF_DOOR_SYNCHED                2048 //LRC- sends USE_ON/OFF when it starts to open/close (instead of sending
                                              // USE_TOGGLE when fully open/closed); also responds to USE_ON and USE_OFF
                                              // 'correctly'.
#define SF_DOOR_SILENT                0x80000000


#define DOOR_SENTENCEWAIT    6
#define DOOR_SOUNDWAIT        3
#define BUTTON_SOUNDWAIT    0.5


#define noiseMoving noise1
#define noiseArrived noise2


#define SF_BUTTON_DONTMOVE        1
#define SF_ROTBUTTON_NOTSOLID    1
#define SF_BUTTON_ONLYDIRECT    16  //LRC - button can't be used through walls.
#define    SF_BUTTON_TOGGLE        32    // button stays pushed until reactivated
#define    SF_BUTTON_SPARK_IF_OFF    64    // button sparks in OFF state
#define SF_BUTTON_NOT_SOLID        128    // button isn't solid
#define SF_BUTTON_TOUCH_ONLY    256    // button must be touched to be used.
#define SF_BUTTON_USEKEY        512 // change the reaction of the button to the USE key.
                                    // (i.e. if it's meant to be ignored, don't ignore it; otherwise ignore it.)


typedef struct locksounds // sounds that doors and buttons make when locked/unlocked
{
    string_t sLockedSound; // sound a door makes when it's locked
    string_t sLockedSentence; // sentence group played when door is locked
    string_t sUnlockedSound; // sound a door makes when it's unlocked
    string_t sUnlockedSentence; // sentence group played when door is unlocked

    int iLockedSentence; // which sentence in sentence group to play next
    int iUnlockedSentence; // which sentence in sentence group to play next

    float flwaitSound; // time delay between playing consecutive 'locked/unlocked' sounds
    float flwaitSentence; // time delay between playing consecutive sentences
    BYTE bEOFLocked; // true if hit end of list of locked sentences
    BYTE bEOFUnlocked; // true if hit end of list of unlocked sentences
} locksound_t;

void PlayLockSounds(entvars_t* pev, locksound_t* pls, int flocked, int fbutton);



#endif        //DOORS_H

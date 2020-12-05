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

//Last Modifed 9 August 2004 By Andrew Hamilton (AJH)
//  :- Added support for acceleration of doors 

/*

===== doors.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "doors.h"

// play door or button locked or unlocked sounds. 
// pass in pointer to valid locksound struct. 
// if flocked is true, play 'door is locked' sound,
// otherwise play 'door is unlocked' sound
// NOTE: this routine is shared by doors and buttons
void PlayLockSounds(entvars_t *pev, locksound_t *pls, int flocked, int fbutton)
{
    // LOCKED SOUND
    
    // CONSIDER: consolidate the locksound_t struct (all entries are duplicates for lock/unlock)
    // CONSIDER: and condense this code.
    float flsoundwait;

    if (fbutton)
        flsoundwait = BUTTON_SOUNDWAIT;
    else
        flsoundwait = DOOR_SOUNDWAIT;

    if (flocked)
    {
        int fplaysound = (pls->sLockedSound && gpGlobals->time > pls->flwaitSound);
        int fplaysentence = (pls->sLockedSentence && !pls->bEOFLocked && gpGlobals->time > pls->flwaitSentence);
        float fvol;

        if (fplaysound && fplaysentence)
            fvol = 0.25;
        else
            fvol = 1.0;

        // if there is a locked sound, and we've debounced, play sound
        if (fplaysound)
        {
            // play 'door locked' sound
            EMIT_SOUND(ENT(pev), CHAN_ITEM, (char*)STRING(pls->sLockedSound), fvol, ATTN_NORM);
            pls->flwaitSound = gpGlobals->time + flsoundwait;
        }

        // if there is a sentence, we've not played all in list, and we've debounced, play sound
        if (fplaysentence)
        {
            // play next 'door locked' sentence in group
            int iprev = pls->iLockedSentence;
            
            pls->iLockedSentence = SENTENCEG_PlaySequentialSz(ENT(pev), STRING(pls->sLockedSentence), 
                      0.85, ATTN_NORM, 0, 100, pls->iLockedSentence, FALSE);
            pls->iUnlockedSentence = 0;

            // make sure we don't keep calling last sentence in list
            pls->bEOFLocked = (iprev == pls->iLockedSentence);
        
            pls->flwaitSentence = gpGlobals->time + DOOR_SENTENCEWAIT;
        }
    }
    else
    {
        // UNLOCKED SOUND

        int fplaysound = (pls->sUnlockedSound && gpGlobals->time > pls->flwaitSound);
        int fplaysentence = (pls->sUnlockedSentence && !pls->bEOFUnlocked && gpGlobals->time > pls->flwaitSentence);
        float fvol;

        // if playing both sentence and sound, lower sound volume so we hear sentence
        if (fplaysound && fplaysentence)
            fvol = 0.25;
        else
            fvol = 1.0;

        // play 'door unlocked' sound if set
        if (fplaysound)
        {
            EMIT_SOUND(ENT(pev), CHAN_ITEM, (char*)STRING(pls->sUnlockedSound), fvol, ATTN_NORM);
            pls->flwaitSound = gpGlobals->time + flsoundwait;
        }

        // play next 'door unlocked' sentence in group
        if (fplaysentence)
        {
            int iprev = pls->iUnlockedSentence;
            
            pls->iUnlockedSentence = SENTENCEG_PlaySequentialSz(ENT(pev), STRING(pls->sUnlockedSentence), 
                      0.85, ATTN_NORM, 0, 100, pls->iUnlockedSentence, FALSE);
            pls->iLockedSentence = 0;

            // make sure we don't keep calling last sentence in list
            pls->bEOFUnlocked = (iprev == pls->iUnlockedSentence);
            pls->flwaitSentence = gpGlobals->time + DOOR_SENTENCEWAIT;
        }
    }
}



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
/*

===== buttons.cpp ========================================================

  button-related code

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"

// Button sound table. 
// Also used by CBaseDoor to get 'touched' door lock/unlock sounds

const char* ButtonSound(int sound)
{
    const char* pszSound;

    switch (sound)
    {
        case 0: pszSound = "common/null.wav"; break;
        case 1: pszSound = "buttons/button1.wav"; break;
        case 2: pszSound = "buttons/button2.wav"; break;
        case 3: pszSound = "buttons/button3.wav"; break;
        case 4: pszSound = "buttons/button4.wav"; break;
        case 5: pszSound = "buttons/button5.wav"; break;
        case 6: pszSound = "buttons/button6.wav"; break;
        case 7: pszSound = "buttons/button7.wav"; break;
        case 8: pszSound = "buttons/button8.wav"; break;
        case 9: pszSound = "buttons/button9.wav"; break;
        case 10: pszSound = "buttons/button10.wav"; break;
        case 11: pszSound = "buttons/button11.wav"; break;
        case 12: pszSound = "buttons/latchlocked1.wav"; break;
        case 13: pszSound = "buttons/latchunlocked1.wav"; break;
        case 14: pszSound = "buttons/lightswitch2.wav"; break;
        // next 6 slots reserved for any additional sliding button sounds we may add
        case 21: pszSound = "buttons/lever1.wav"; break;
        case 22: pszSound = "buttons/lever2.wav"; break;
        case 23: pszSound = "buttons/lever3.wav"; break;
        case 24: pszSound = "buttons/lever4.wav"; break;
        case 25: pszSound = "buttons/lever5.wav"; break;     
        default: pszSound = "buttons/button9.wav"; break;
    }

    return pszSound;
}

//
// Makes flagged buttons spark when turned off
//

void DoSpark(entvars_t* pev, const Vector& location)
{
    Vector tmp = location + pev->size * 0.5;
    UTIL_Sparks(tmp);

    float flVolume = RANDOM_FLOAT(0.25, 0.75) * 0.4; //random volume range
    switch ((int)(RANDOM_FLOAT(0, 1) * 6))
    {
        case 0: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark1.wav", flVolume, ATTN_NORM); break;
        case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark2.wav", flVolume, ATTN_NORM); break;
        case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark3.wav", flVolume, ATTN_NORM); break;
        case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark4.wav", flVolume, ATTN_NORM); break;
        case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark5.wav", flVolume, ATTN_NORM); break;
        case 5: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark6.wav", flVolume, ATTN_NORM); break;
    }
}
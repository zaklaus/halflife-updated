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
void EV_EgonFire(struct event_args_s* args);
void EV_EgonStop(struct event_args_s* args);
}

enum egon_e
{
    EGON_IDLE1 = 0,
    EGON_FIDGET1,
    EGON_ALTFIREON,
    EGON_ALTFIRECYCLE,
    EGON_ALTFIREOFF,
    EGON_FIRE1,
    EGON_FIRE2,
    EGON_FIRE3,
    EGON_FIRE4,
    EGON_DRAW,
    EGON_HOLSTER
};

int g_fireAnims1[] = {EGON_FIRE1, EGON_FIRE2, EGON_FIRE3, EGON_FIRE4};
int g_fireAnims2[] = {EGON_ALTFIRECYCLE};

enum EGON_FIRESTATE { FIRE_OFF, FIRE_CHARGE };

enum EGON_FIREMODE { FIRE_NARROW, FIRE_WIDE };

#define	EGON_PRIMARY_VOLUME		450
#define EGON_BEAM_SPRITE		"sprites/xbeam1.spr"
#define EGON_FLARE_SPRITE		"sprites/XSpark1.spr"
#define EGON_SOUND_OFF			"weapons/egon_off1.wav"
#define EGON_SOUND_RUN			"weapons/egon_run3.wav"
#define EGON_SOUND_STARTUP		"weapons/egon_windup2.wav"

#define ARRAYSIZE(p)		(sizeof(p)/sizeof(p[0]))

BEAM* pBeam;
BEAM* pBeam2;

void EV_EgonFire(event_args_t* args)
{
    int idx, iFireState, iFireMode;
    vec3_t origin;

    idx = args->entindex;
    VectorCopy(args->origin, origin);
    iFireState = args->iparam1;
    iFireMode = args->iparam2;
    int iStartup = args->bparam1;


    if (iStartup)
    {
        if (iFireMode == FIRE_WIDE)
            gEngfuncs.pEventAPI->EV_PlaySound(idx, origin, CHAN_WEAPON, EGON_SOUND_STARTUP, 0.98, ATTN_NORM, 0, 125);
        else
            gEngfuncs.pEventAPI->EV_PlaySound(idx, origin, CHAN_WEAPON, EGON_SOUND_STARTUP, 0.9, ATTN_NORM, 0, 100);
    }
    else
    {
        //If there is any sound playing already, kill it.
        //This is necessary because multiple sounds can play on the same channel at the same time.
        //In some cases, more than 1 run sound plays when the egon stops firing, in which case only the earliest entry in the list is stopped.
        //This ensures no more than 1 of those is ever active at the same time.
        gEngfuncs.pEventAPI->EV_StopSound(idx, CHAN_STATIC, EGON_SOUND_RUN);

        if (iFireMode == FIRE_WIDE)
            gEngfuncs.pEventAPI->EV_PlaySound(idx, origin, CHAN_STATIC, EGON_SOUND_RUN, 0.98, ATTN_NORM, 0, 125);
        else
            gEngfuncs.pEventAPI->EV_PlaySound(idx, origin, CHAN_STATIC, EGON_SOUND_RUN, 0.9, ATTN_NORM, 0, 100);
    }

    //Only play the weapon anims if I shot it.
    if (EV_IsLocal(idx))
        gEngfuncs.pEventAPI->EV_WeaponAnimation(g_fireAnims1[gEngfuncs.pfnRandomLong(0, 3)], 1);

    if (iStartup == 1 && EV_IsLocal(idx) && !pBeam && !pBeam2 && cl_lw->value)
        //Adrian: Added the cl_lw check for those lital people that hate weapon prediction.
    {
        vec3_t vecSrc, vecEnd, origin, angles, forward, right, up;
        pmtrace_t tr;

        cl_entity_t* pl = gEngfuncs.GetEntityByIndex(idx);

        if (pl)
        {
            VectorCopy(gHUD.m_vecAngles, angles);

            AngleVectors(angles, forward, right, up);

            EV_GetGunPosition(args, vecSrc, pl->origin);

            VectorMA(vecSrc, 2048, forward, vecEnd);

            gEngfuncs.pEventAPI->EV_SetUpPlayerPrediction(false, true);

            // Store off the old count
            gEngfuncs.pEventAPI->EV_PushPMStates();

            // Now add in all of the players.
            gEngfuncs.pEventAPI->EV_SetSolidPlayers(idx - 1);

            gEngfuncs.pEventAPI->EV_SetTraceHull(2);
            gEngfuncs.pEventAPI->EV_PlayerTrace(vecSrc, vecEnd, PM_STUDIO_BOX, -1, &tr);

            gEngfuncs.pEventAPI->EV_PopPMStates();

            int iBeamModelIndex = gEngfuncs.pEventAPI->EV_FindModelIndex(EGON_BEAM_SPRITE);

            float r = 50.0f;
            float g = 50.0f;
            float b = 125.0f;

            //if ( IEngineStudio.IsHardware() )
            {
                r /= 255.0f;
                g /= 255.0f;
                b /= 255.0f;
            }


            pBeam = gEngfuncs.pEfxAPI->R_BeamEntPoint(idx | 0x1000, tr.endpos, iBeamModelIndex, 99999, 3.5, 0.2, 0.7, 55, 0, 0, r, g, b);

            if (pBeam)
                pBeam->flags |= (FBEAM_SINENOISE);

            pBeam2 = gEngfuncs.pEfxAPI->R_BeamEntPoint(idx | 0x1000, tr.endpos, iBeamModelIndex, 99999, 5.0, 0.08, 0.7, 25, 0, 0, r, g, b);
        }
    }
}

void EV_EgonStop(event_args_t* args)
{
    int idx;
    vec3_t origin;

    idx = args->entindex;
    VectorCopy(args->origin, origin);

    gEngfuncs.pEventAPI->EV_StopSound(idx, CHAN_STATIC, EGON_SOUND_RUN);

    if (args->iparam1)
        gEngfuncs.pEventAPI->EV_PlaySound(idx, origin, CHAN_WEAPON, EGON_SOUND_OFF, 0.98, ATTN_NORM, 0, 100);

    if (EV_IsLocal(idx))
    {
        if (pBeam)
        {
            pBeam->die = 0.0;
            pBeam = NULL;
        }


        if (pBeam2)
        {
            pBeam2->die = 0.0;
            pBeam2 = NULL;
        }
    }
}

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
void EV_Mirror(struct event_args_s* args);
}

void EV_Mirror(event_args_t* args)
{
    vec3_t org;
    bool bNew = true;

    VectorCopy(args->origin, org);
    float dist = (float)args->iparam1;
    int type = args->iparam2;
    int bEnabled = args->bparam1;

    //we have mirror
    if (gHUD.numMirrors)
    {
        for (int ic = 0; ic < 32; ic++)
        {
            if (gHUD.Mirrors[ic].origin[0] == org[0] && gHUD.Mirrors[ic].origin[1] == org[1] && gHUD.Mirrors[ic].origin[2] == org[2])
            {
                if (bEnabled && !gHUD.Mirrors[ic].enabled) gHUD.numMirrors++;

                else if (!bEnabled && gHUD.Mirrors[ic].enabled) gHUD.numMirrors--;

                gHUD.Mirrors[ic].enabled = bEnabled;
                bNew = false;
                break;
            }
        }
    }

    if (bNew)
    {
        if (gHUD.numMirrors >= 32)
            CONPRINT("ERROR: Can't register mirror, maximum 32 allowed!\n");

        else
        {
            VectorCopy(org, gHUD.Mirrors[gHUD.numMirrors].origin);
            gHUD.Mirrors[gHUD.numMirrors].type = type;
            gHUD.Mirrors[gHUD.numMirrors].enabled = bEnabled;
            gHUD.Mirrors[gHUD.numMirrors].radius = dist;
            gHUD.numMirrors++;
        }
    }
}

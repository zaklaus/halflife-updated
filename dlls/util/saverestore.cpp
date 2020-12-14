/***
*
* Copyright (c) 1996-2001, Valve LLC. All rights reserved.
* 
* This product contains software technology licensed from Id
* Software, Inc. ("Id Technology).  Id Technology (c) 1996 Id Software, Inc.
* All Rights Reserved.
*
* Use, distribution, and modification of this source code and/or resulting
* object code is restricted to non-commercial enhancements to products from
* Valve LLC.  All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/

#include "util/saverestore.h"

int gSizes[FIELD_TYPECOUNT] =
{
    sizeof(float), // FIELD_FLOAT
    sizeof(int), // FIELD_STRING
    sizeof(int), // FIELD_ENTITY
    sizeof(int), // FIELD_CLASSPTR
    sizeof(int), // FIELD_EHANDLE
    sizeof(int), // FIELD_entvars_t
    sizeof(int), // FIELD_EDICT
    sizeof(float) * 3, // FIELD_VECTOR
    sizeof(float) * 3, // FIELD_POSITION_VECTOR
    sizeof(int*), // FIELD_POINTER
    sizeof(int), // FIELD_INTEGER
#ifdef GNUC
    sizeof(int*) * 2,        // FIELD_FUNCTION
#else
    sizeof(int*), // FIELD_FUNCTION    
#endif
    sizeof(int), // FIELD_BOOLEAN
    sizeof(short), // FIELD_SHORT
    sizeof(char), // FIELD_CHARACTER
    sizeof(float), // FIELD_TIME
    sizeof(int), // FIELD_MODELNAME
    sizeof(int), // FIELD_SOUNDNAME
};

TYPEDESCRIPTION gEntvarsDescription[] =
{
    DEFINE_ENTITY_FIELD(classname, FIELD_STRING),
    DEFINE_ENTITY_GLOBAL_FIELD(globalname, FIELD_STRING),

    DEFINE_ENTITY_FIELD(origin, FIELD_POSITION_VECTOR),
    DEFINE_ENTITY_FIELD(oldorigin, FIELD_POSITION_VECTOR),
    DEFINE_ENTITY_FIELD(velocity, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(basevelocity, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(movedir, FIELD_VECTOR),

    DEFINE_ENTITY_FIELD(angles, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(avelocity, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(punchangle, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(v_angle, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(fixangle, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(idealpitch, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(pitch_speed, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(ideal_yaw, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(yaw_speed, FIELD_FLOAT),

    DEFINE_ENTITY_FIELD(modelindex, FIELD_INTEGER),
    DEFINE_ENTITY_GLOBAL_FIELD(model, FIELD_MODELNAME),

    DEFINE_ENTITY_FIELD(viewmodel, FIELD_MODELNAME),
    DEFINE_ENTITY_FIELD(weaponmodel, FIELD_MODELNAME),

    DEFINE_ENTITY_FIELD(absmin, FIELD_POSITION_VECTOR),
    DEFINE_ENTITY_FIELD(absmax, FIELD_POSITION_VECTOR),
    DEFINE_ENTITY_GLOBAL_FIELD(mins, FIELD_VECTOR),
    DEFINE_ENTITY_GLOBAL_FIELD(maxs, FIELD_VECTOR),
    DEFINE_ENTITY_GLOBAL_FIELD(size, FIELD_VECTOR),

    DEFINE_ENTITY_FIELD(ltime, FIELD_TIME),
    DEFINE_ENTITY_FIELD(nextthink, FIELD_TIME),

    DEFINE_ENTITY_FIELD(solid, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(movetype, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(skin, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(body, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(effects, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(gravity, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(friction, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(light_level, FIELD_FLOAT),

    DEFINE_ENTITY_FIELD(frame, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(scale, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(sequence, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(animtime, FIELD_TIME),
    DEFINE_ENTITY_FIELD(framerate, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(controller, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(blending, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(rendermode, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(renderamt, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(rendercolor, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(renderfx, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(health, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(frags, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(weapons, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(takedamage, FIELD_FLOAT),

    DEFINE_ENTITY_FIELD(deadflag, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(view_ofs, FIELD_VECTOR),
    DEFINE_ENTITY_FIELD(button, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(impulse, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(chain, FIELD_EDICT),
    DEFINE_ENTITY_FIELD(dmg_inflictor, FIELD_EDICT),
    DEFINE_ENTITY_FIELD(enemy, FIELD_EDICT),
    DEFINE_ENTITY_FIELD(aiment, FIELD_EDICT),
    DEFINE_ENTITY_FIELD(owner, FIELD_EDICT),
    DEFINE_ENTITY_FIELD(groundentity, FIELD_EDICT),

    DEFINE_ENTITY_FIELD(spawnflags, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(flags, FIELD_FLOAT),

    DEFINE_ENTITY_FIELD(colormap, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(team, FIELD_INTEGER),

    DEFINE_ENTITY_FIELD(max_health, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(teleport_time, FIELD_TIME),
    DEFINE_ENTITY_FIELD(armortype, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(armorvalue, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(waterlevel, FIELD_INTEGER),
    DEFINE_ENTITY_FIELD(watertype, FIELD_INTEGER),

    // Having these fields be local to the individual levels makes it easier to test those levels individually.
    DEFINE_ENTITY_GLOBAL_FIELD(target, FIELD_STRING),
    DEFINE_ENTITY_GLOBAL_FIELD(targetname, FIELD_STRING),
    DEFINE_ENTITY_FIELD(netname, FIELD_STRING),
    DEFINE_ENTITY_FIELD(message, FIELD_STRING),

    DEFINE_ENTITY_FIELD(dmg_take, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(dmg_save, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(dmg, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(dmgtime, FIELD_TIME),

    DEFINE_ENTITY_FIELD(noise, FIELD_SOUNDNAME),
    DEFINE_ENTITY_FIELD(noise1, FIELD_SOUNDNAME),
    DEFINE_ENTITY_FIELD(noise2, FIELD_SOUNDNAME),
    DEFINE_ENTITY_FIELD(noise3, FIELD_SOUNDNAME),
    DEFINE_ENTITY_FIELD(speed, FIELD_FLOAT),
    DEFINE_ENTITY_FIELD(air_finished, FIELD_TIME),
    DEFINE_ENTITY_FIELD(pain_finished, FIELD_TIME),
    DEFINE_ENTITY_FIELD(radsuit_finished, FIELD_TIME),
};

int gEntvarsCount = sizeof gEntvarsDescription / sizeof gEntvarsDescription[0];

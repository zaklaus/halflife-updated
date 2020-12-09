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

#include "extdll.h"
#include "enginecallback.h"

// More explicit than "int"
typedef int EOFFSET;

// This is the glue that hooks .MAP entity class names to our CPP classes
// The _declspec forces them to be exported by name so we can do a lookup with GetProcAddress()
// The function is used to intialize / allocate the object for the entity
#define LINK_ENTITY_TO_CLASS(mapClassName,DLLClassName) \
    extern "C" DLLEXPORT void mapClassName( entvars_t *pev ); \
    void mapClassName( entvars_t *pev ) { GetClassPtr( (DLLClassName *)pev ); }

//
// Conversion among the three types of "entity", including identity-conversions.
//

// Convert to edict_t
#ifdef DEBUG

extern edict_t* DBG_EntOfVars(const entvars_t* pev);

inline edict_t* ENT(const entvars_t* pev)
{
    return DBG_EntOfVars(pev);
}

#else

inline edict_t* ENT(const entvars_t* pev)
{
    return pev->pContainingEntity;
}

#endif

inline edict_t* ENT(edict_t* pent)
{
    return pent;
}

inline edict_t* ENT(EOFFSET eoffset)
{
    return (*g_engfuncs.pfnPEntityOfEntOffset)(eoffset);
}

// Convert to EOFFSET
inline EOFFSET OFFSET(EOFFSET eoffset)
{
    return eoffset;
}

inline EOFFSET OFFSET(const edict_t* pent)
{
#if _DEBUG
    if (!pent) ALERT(at_error, "Bad ent in OFFSET()\n");
#endif
    return (*g_engfuncs.pfnEntOffsetOfPEntity)(pent);
}

inline EOFFSET OFFSET(entvars_t* pev)
{
#if _DEBUG
    if (!pev) ALERT(at_error, "Bad pev in OFFSET()\n");
#endif
    return OFFSET(ENT(pev));
}

// Convert to entvars_t
inline entvars_t* VARS(entvars_t* pev)
{
    return pev;
}

inline entvars_t* VARS(edict_t* pent)
{
    if (!pent)
        return NULL;

    return &pent->v;
}

inline entvars_t* VARS(EOFFSET eoffset)
{
    return VARS(ENT(eoffset));
}

inline int ENTINDEX(edict_t* pEdict)
{
    return (*g_engfuncs.pfnIndexOfEdict)(pEdict);
}

inline edict_t* INDEXENT(int iEdictNum)
{
    return (*g_engfuncs.pfnPEntityOfEntIndex)(iEdictNum);
}

// Testing the three types of "entity" for nullity
//LRC- four types, rather; see cbase.h
#define eoNullEntity 0

inline BOOL FNullEnt(EOFFSET eoffset)
{
    return eoffset == 0;
}

inline BOOL FNullEnt(const edict_t* pent)
{
    return pent == NULL || FNullEnt(OFFSET(pent));
}

inline BOOL FNullEnt(entvars_t* pev)
{
    return pev == NULL || FNullEnt(OFFSET(pev));
}

Vector VecBModelOrigin(entvars_t* pevBModel);

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

#include "entities/CBaseEntity.h"

inline edict_t* FIND_ENTITY_BY_CLASSNAME(edict_t* entStart, const char* pszName)
{
    return FIND_ENTITY_BY_STRING(entStart, "classname", pszName);
}

inline edict_t* FIND_ENTITY_BY_TARGETNAME(edict_t* entStart, const char* pszName)
{
    return FIND_ENTITY_BY_STRING(entStart, "targetname", pszName);
}

// for doing a reverse lookup. Say you have a door, and want to find its button.
inline edict_t* FIND_ENTITY_BY_TARGET(edict_t* entStart, const char* pszName)
{
    return FIND_ENTITY_BY_STRING(entStart, "target", pszName);
}

extern CBaseEntity* UTIL_FindEntityInSphere(CBaseEntity* pStartEntity, const Vector& vecCenter, float flRadius);
extern CBaseEntity* UTIL_FindEntityByString(CBaseEntity* pStartEntity, const char* szKeyword, const char* szValue);
extern CBaseEntity* UTIL_FindEntityByClassname(CBaseEntity* pStartEntity, const char* szName);
extern CBaseEntity* UTIL_FindEntityByTargetname(CBaseEntity* pStartEntity, const char* szName);
extern CBaseEntity* UTIL_FindEntityByTargetname(CBaseEntity* pStartEntity, const char* szName, CBaseEntity* pActivator); //LRC - for $locus references
extern CBaseEntity* UTIL_FindEntityByTarget(CBaseEntity* pStartEntity, const char* szName);
extern CBaseEntity* UTIL_FindEntityGeneric(const char* szName, Vector& vecSrc, float flRadius);

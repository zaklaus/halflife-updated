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

#include "findentity.h"

CBaseEntity* UTIL_FindEntityInSphere(CBaseEntity* pStartEntity, const Vector& vecCenter, float flRadius)
{
    edict_t* pentEntity;

    if (pStartEntity)
        pentEntity = pStartEntity->edict();
    else
        pentEntity = NULL;

    pentEntity = FIND_ENTITY_IN_SPHERE(pentEntity, vecCenter, flRadius);

    if (!FNullEnt(pentEntity))
        return CBaseEntity::Instance(pentEntity);
    return NULL;
}

CBaseEntity* UTIL_FindEntityByString(CBaseEntity* pStartEntity, const char* szKeyword, const char* szValue)
{
    edict_t* pentEntity;
    CBaseEntity* pEntity;

    if (pStartEntity)
        pentEntity = pStartEntity->edict();
    else
        pentEntity = NULL;

    for (;;)
    {
        // Don't change this to use UTIL_FindEntityByString!
        pentEntity = FIND_ENTITY_BY_STRING(pentEntity, szKeyword, szValue);

        // if pentEntity (the edict) is null, we're at the end of the entities. Give up.
        if (FNullEnt(pentEntity))
        {
            return NULL;
        }
        else
        {
            // ...but if only pEntity (the classptr) is null, we've just got one dud, so we try again.
            pEntity = CBaseEntity::Instance(pentEntity);
            if (pEntity)
                return pEntity;
        }
    }
}

CBaseEntity* UTIL_FindEntityByClassname(CBaseEntity* pStartEntity, const char* szName)
{
    return UTIL_FindEntityByString(pStartEntity, "classname", szName);
}

CBaseEntity* UTIL_FindEntityByTargetname(CBaseEntity* pStartEntity, const char* szName)
{
    CBaseEntity* pFound = UTIL_FollowReference(pStartEntity, szName);
    if (pFound)
        return pFound;
    else
        return UTIL_FindEntityByString(pStartEntity, "targetname", szName);
}

CBaseEntity* UTIL_FindEntityByTargetname(CBaseEntity* pStartEntity, const char* szName, CBaseEntity* pActivator)
{
    if (FStrEq(szName, "*locus"))
    {
        if (pActivator && (pStartEntity == NULL || pActivator->eoffset() > pStartEntity->eoffset()))
            return pActivator;
        else
            return NULL;
    }
    else
        return UTIL_FindEntityByTargetname(pStartEntity, szName);
}

CBaseEntity* UTIL_FindEntityByTarget(CBaseEntity* pStartEntity, const char* szName)
{
    return UTIL_FindEntityByString(pStartEntity, "target", szName);
}

CBaseEntity* UTIL_FindEntityGeneric(const char* szWhatever, Vector& vecSrc, float flRadius)
{
    CBaseEntity* pEntity = NULL;

    pEntity = UTIL_FindEntityByTargetname(NULL, szWhatever);
    if (pEntity)
        return pEntity;

    CBaseEntity* pSearch = NULL;
    float flMaxDist2 = flRadius * flRadius;
    while ((pSearch = UTIL_FindEntityByClassname(pSearch, szWhatever)) != NULL)
    {
        float flDist2 = (pSearch->pev->origin - vecSrc).Length();
        flDist2 = flDist2 * flDist2;
        if (flMaxDist2 > flDist2)
        {
            pEntity = pSearch;
            flMaxDist2 = flDist2;
        }
    }
    return pEntity;
}

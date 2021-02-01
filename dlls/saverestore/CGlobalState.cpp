/***
*
* Copyright (c) 1996-2001, Valve LLC. All rights reserved.
* 
* This product contains software technology licensed from Id
* Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
* All Rights Reserved.
*
* Use, distribution, and modification of this source code and/or resulting
* object code is restricted to non-commercial enhancements to products from
* Valve LLC.  All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/

#include "CGlobalState.h"

CGlobalState gGlobalState;

CGlobalState::CGlobalState(void)
{
    Reset();
}

void CGlobalState::Reset(void)
{
    m_pList = NULL;
    m_listCount = 0;
}

globalentity_t* CGlobalState::Find(string_t globalname)
{
    if (!globalname)
        return NULL;

    globalentity_t* pTest;
    const char* pEntityName = STRING(globalname);


    pTest = m_pList;
    while (pTest)
    {
        if (FStrEq(pEntityName, pTest->name))
            break;

        pTest = pTest->pNext;
    }

    return pTest;
}

void CGlobalState::DumpGlobals(void)
{
    static const char* estates[] = {"Off", "On", "Dead"};
    globalentity_t* pTest;

    ALERT(at_debug, "-- Globals --\n");
    pTest = m_pList;
    while (pTest)
    {
        ALERT(at_debug, "%s: %s (%s)\n", pTest->name, pTest->levelName, estates[pTest->state]);
        pTest = pTest->pNext;
    }
}

void CGlobalState::EntityAdd(string_t globalname, string_t mapName, GLOBALESTATE state)
{
    ASSERT(!Find(globalname));

    globalentity_t* pNewEntity = (globalentity_t*)calloc(sizeof(globalentity_t), 1);
    ASSERT(pNewEntity != NULL);
    pNewEntity->pNext = m_pList;
    m_pList = pNewEntity;
    strcpy(pNewEntity->name, STRING(globalname));
    strcpy(pNewEntity->levelName, STRING(mapName));
    pNewEntity->state = state;
    m_listCount++;
}

void CGlobalState::EntitySetState(string_t globalname, GLOBALESTATE state)
{
    globalentity_t* pEnt = Find(globalname);

    if (pEnt)
        pEnt->state = state;
}

const globalentity_t* CGlobalState::EntityFromTable(string_t globalname)
{
    globalentity_t* pEnt = Find(globalname);

    return pEnt;
}

GLOBALESTATE CGlobalState::EntityGetState(string_t globalname)
{
    globalentity_t* pEnt = Find(globalname);
    if (pEnt)
        return pEnt->state;

    return GLOBAL_OFF;
}

// Global Savedata for Delay
TYPEDESCRIPTION CGlobalState::m_SaveData[] =
{
    DEFINE_FIELD(CGlobalState, m_listCount, FIELD_INTEGER),
};

// Global Savedata for Delay
TYPEDESCRIPTION gGlobalEntitySaveData[] =
{
    DEFINE_ARRAY(globalentity_t, name, FIELD_CHARACTER, 64),
    DEFINE_ARRAY(globalentity_t, levelName, FIELD_CHARACTER, 32),
    DEFINE_FIELD(globalentity_t, state, FIELD_INTEGER),
};

int CGlobalState::Save(CSave& save)
{
    int i;
    globalentity_t* pEntity;

    if (!save.WriteFields("cGLOBAL", "GLOBAL", this, m_SaveData, ARRAYSIZE(m_SaveData)))
        return 0;

    pEntity = m_pList;
    for (i = 0; i < m_listCount && pEntity; i++)
    {
        if (!save.WriteFields("cGENT", "GENT", pEntity, gGlobalEntitySaveData, ARRAYSIZE(gGlobalEntitySaveData)))
            return 0;

        pEntity = pEntity->pNext;
    }

    return 1;
}

int CGlobalState::Restore(CRestore& restore)
{
    int i, listCount;
    globalentity_t tmpEntity;

    ClearStates();
    if (!restore.ReadFields("GLOBAL", this, m_SaveData, ARRAYSIZE(m_SaveData)))
        return 0;

    listCount = m_listCount; // Get new list count
    m_listCount = 0; // Clear loaded data

    for (i = 0; i < listCount; i++)
    {
        if (!restore.ReadFields("GENT", &tmpEntity, gGlobalEntitySaveData, ARRAYSIZE(gGlobalEntitySaveData)))
            return 0;
        EntityAdd(MAKE_STRING(tmpEntity.name), MAKE_STRING(tmpEntity.levelName), tmpEntity.state);
    }
    return 1;
}

void CGlobalState::EntityUpdate(string_t globalname, string_t mapname)
{
    globalentity_t* pEnt = Find(globalname);

    if (pEnt)
        strcpy(pEnt->levelName, STRING(mapname));
}

void CGlobalState::ClearStates(void)
{
    globalentity_t* pFree = m_pList;
    while (pFree)
    {
        globalentity_t* pNext = pFree->pNext;
        free(pFree);
        pFree = pNext;
    }
    Reset();
}
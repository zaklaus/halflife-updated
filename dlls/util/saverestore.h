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

#include "extdll.h"
#include "saverestore/CSave.h"
#include "saverestore/CRestore.h"

extern int gSizes[FIELD_TYPECOUNT];
extern TYPEDESCRIPTION gEntvarsDescription[];
extern int gEntvarsCount;

#define ENTVARS_COUNT gEntvarsCount

#define IMPLEMENT_SAVERESTORE(derivedClass,baseClass) \
    int derivedClass::Save( CSave &save )\
    {\
        if ( !baseClass::Save(save) )\
            return 0;\
        if (pev->targetname)\
            return save.WriteFields( STRING(pev->targetname), #derivedClass, this, m_SaveData, ARRAYSIZE(m_SaveData) );\
        else\
            return save.WriteFields( STRING(pev->classname), #derivedClass, this, m_SaveData, ARRAYSIZE(m_SaveData) );\
    }\
    int derivedClass::Restore( CRestore &restore )\
    {\
        if ( !baseClass::Restore(restore) )\
            return 0;\
        return restore.ReadFields( #derivedClass, this, m_SaveData, ARRAYSIZE(m_SaveData) );\
    }

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
* Valve LLC.All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/
#pragma once

#include "CHudBase.h"

typedef struct cl_mirror_s
{
    vec3_t origin;
    int enabled;
    float radius;
    int type;
} cl_mirror_t;

class CShinySurface
{
    float m_fMinX, m_fMinY, m_fMaxX, m_fMaxY, m_fZ;
    char m_fScale;
    float m_fAlpha; // texture scale and brighness
    HSPRITE m_hsprSprite;
    char m_szSprite[128];

public:
    CShinySurface* m_pNext;

    CShinySurface(float fScale, float fAlpha, float fMinX, float fMaxX, float fMinY, float fMaxY, float fZ, char* szSprite);
    ~CShinySurface();

    // draw the surface as seen from the given position
    void Draw(const vec3_t& org);

    void DrawAll(const vec3_t& org);
};

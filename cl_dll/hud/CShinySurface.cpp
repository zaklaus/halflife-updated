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

#include "CShinySurface.h"
#include "triangleapi.h"

CShinySurface::CShinySurface(float fScale, float fAlpha, float fMinX, float fMaxX, float fMinY, float fMaxY, float fZ, char* szSprite)
{
    m_fScale = fScale;
    m_fAlpha = fAlpha;
    m_fMinX = fMinX;
    m_fMinY = fMinY;
    m_fMaxX = fMaxX;
    m_fMaxY = fMaxY;
    m_fZ = fZ;
    m_hsprSprite = 0;
    sprintf(m_szSprite, szSprite);
    m_pNext = NULL;
}

CShinySurface::~CShinySurface()
{
    if (m_pNext)
        delete m_pNext;
}

void CShinySurface::DrawAll(const vec3_t& org)
{
    gEngfuncs.pTriAPI->RenderMode(kRenderTransAdd); //kRenderTransTexture );
    gEngfuncs.pTriAPI->CullFace(TRI_NONE);

    for (CShinySurface* pCurrent = this; pCurrent; pCurrent = pCurrent->m_pNext)
    {
        pCurrent->Draw(org);
    }

    gEngfuncs.pTriAPI->RenderMode(kRenderNormal);
}


int UseTexture(HSPRITE& hsprSpr, char* str)
{
    if (hsprSpr == 0)
    {
        char sz[256];
        sprintf(sz, str);
        hsprSpr = SPR_Load(sz);
    }

    return gEngfuncs.pTriAPI->SpriteTexture((struct model_s*)gEngfuncs.GetSpritePointer(hsprSpr), 0);
}

void CShinySurface::Draw(const vec3_t& org)
{
    // add 5 to the view height, so that we don't get an ugly repeating texture as it approaches 0.
    float fHeight = org.z - m_fZ + 5;

    // only visible from above
    //	if (fHeight < 0) return;
    if (fHeight < 5) return;

    // fade out if we're really close to the surface, so they don't see an ugly repeating texture
    //	if (fHeight < 15)
    //		gEngfuncs.pTriAPI->Color4f( 1.0, 1.0, 1.0, (fHeight - 5)*0.1*m_fAlpha );
    //	else
    gEngfuncs.pTriAPI->Color4f(1.0, 1.0, 1.0, m_fAlpha);

    // check whether the texture is valid
    if (!UseTexture(m_hsprSprite, m_szSprite)) return;

    //	gEngfuncs.Con_Printf("minx %f, maxx %f, miny %f, maxy %f\n", m_fMinX, m_fMaxX, m_fMinY, m_fMaxY);

    float fFactor = 1 / (m_fScale * fHeight);
    float fMinTX = (org.x - m_fMinX) * fFactor;
    float fMaxTX = (org.x - m_fMaxX) * fFactor;
    float fMinTY = (org.y - m_fMinY) * fFactor;
    float fMaxTY = (org.y - m_fMaxY) * fFactor;
    //	gEngfuncs.pTriAPI->Color4f( 1.0, 1.0, 1.0, m_fAlpha );
    gEngfuncs.pTriAPI->Begin(TRI_QUADS);
    gEngfuncs.pTriAPI->TexCoord2f(fMinTX, fMinTY);
    gEngfuncs.pTriAPI->Vertex3f(m_fMinX, m_fMinY, m_fZ + 0.02); // add 0.02 to avoid z-buffer problems
    gEngfuncs.pTriAPI->TexCoord2f(fMinTX, fMaxTY);
    gEngfuncs.pTriAPI->Vertex3f(m_fMinX, m_fMaxY, m_fZ + 0.02);
    gEngfuncs.pTriAPI->TexCoord2f(fMaxTX, fMaxTY);
    gEngfuncs.pTriAPI->Vertex3f(m_fMaxX, m_fMaxY, m_fZ + 0.02);
    gEngfuncs.pTriAPI->TexCoord2f(fMaxTX, fMinTY);
    gEngfuncs.pTriAPI->Vertex3f(m_fMaxX, m_fMinY, m_fZ + 0.02);
    gEngfuncs.pTriAPI->End();
}

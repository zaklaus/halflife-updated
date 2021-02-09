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
#pragma once

#include "hud.h"

class RandomRange
{
public:
    RandomRange()
    {
        m_fMin = m_fMax = 0;
        m_bDefined = false;
    }

    RandomRange(float fValue)
    {
        m_fMin = m_fMax = fValue;
        m_bDefined = true;
    }

    RandomRange(float fMin, float fMax)
    {
        m_fMin = fMin;
        m_fMax = fMax;
        m_bDefined = true;
    }

    RandomRange(char* szToken);

    float m_fMax;
    float m_fMin;
    bool m_bDefined;

    float GetInstance() const
    {
        return gEngfuncs.pfnRandomFloat(m_fMin, m_fMax);
    }

    float GetOffset(float fBasis) const
    {
        return GetInstance() - fBasis;
    }

    bool IsDefined() const
    {
        return m_bDefined;
    } //(m_fMin == 0 && m_fMax == 0); }
};

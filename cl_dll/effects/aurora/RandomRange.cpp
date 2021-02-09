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

#include "RandomRange.h"

RandomRange::RandomRange(char* szToken)
{
    char* cOneDot = NULL;
    m_bDefined = true;

    for (char* c = szToken; *c; c++)
    {
        if (*c == '.')
        {
            if (cOneDot != NULL)
            {
                // found two dots in a row - it's a range

                *cOneDot = 0; // null terminate the first number
                m_fMin = atof(szToken); // parse the first number
                *cOneDot = '.'; // change it back, just in case
                c++;
                m_fMax = atof(c); // parse the second number
                return;
            }
            else
            {
                cOneDot = c;
            }
        }
        else
        {
            cOneDot = NULL;
        }
    }

    // no range, just record the number
    m_fMin = m_fMax = atof(szToken);
}

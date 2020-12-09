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

#include "NodeConstants.h"

//=========================================================
// CStack - last in, first out.
//=========================================================
class CStack
{
public:
    CStack(void);
    void Push(int value);
    int Pop(void);
    int Top(void);
    int Empty(void) { return m_level == 0; }
    int Size(void) { return m_level; }
    void CopyToArray(int* piArray);

private:
    int m_stack[MAX_STACK_NODES];
    int m_level;
};

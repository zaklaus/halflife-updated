//=========== (C) Copyright 1999 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: Contains implementation of various VGUI-derived objects
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================

#include "hud/CHud.h"
#include "cl_util.h"
#include "vgui/controls/vgui_loadtga.h"

using namespace vgui;

// Get the name of TGA file, without a gamedir
char* GetTGANameForRes(const char* pszName)
{
    int i;
    char sz[256];
    static char gd[256];
    if (ScreenWidth < 640)
        i = 320;
    else
        i = 640;
    sprintf(sz, pszName, i);
    sprintf(gd, "gfx/vgui/%s.tga", sz);
    return gd;
}

//-----------------------------------------------------------------------------
// Purpose: Loads a .tga file and returns a pointer to the VGUI tga object
//-----------------------------------------------------------------------------
BitmapTGA* LoadTGAForRes(const char* pImageName)
{
    BitmapTGA* pTGA;

    char sz[256];
    sprintf(sz, "%%d_%s", pImageName);
    pTGA = vgui_LoadTGA(GetTGANameForRes(sz));

    return pTGA;
}

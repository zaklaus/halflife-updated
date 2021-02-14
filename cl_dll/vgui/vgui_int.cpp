//========= Copyright © 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <VGUI_BorderLayout.h>

#include "vgui_int.h"
#include "hud/hud.h"
#include "vgui_common.h"
#include "TeamFortressViewport.h"

using namespace vgui;

void VGui_ViewportPaintBackground(int extents[4])
{
    gEngfuncs.VGui_ViewportPaintBackground(extents);
}

void* VGui_GetPanel()
{
    return (Panel*)gEngfuncs.VGui_GetPanel();
}

void VGui_Startup()
{
    Panel* root = (Panel*)VGui_GetPanel();
    root->setBgColor(128, 128, 0, 0);
    root->setLayout(new BorderLayout(0));

    if (gViewPort != NULL)
    {
        gViewPort->Initialize();
    }
    else
    {
        gViewPort = new TeamFortressViewport(0, 0, root->getWide(), root->getTall());
        gViewPort->setParent(root);
    }
}

void VGui_Shutdown()
{
    delete gViewPort;
    gViewPort = NULL;
}

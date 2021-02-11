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

#include <VGUI_Image.h>
#include <VGUI_TextImage.h>

#include "hud/hud.h"

class CTextImage2 : public vgui::Image
{
public:
    CTextImage2()
    {
        _image[0] = new vgui::TextImage("");
        _image[1] = new vgui::TextImage("");
    }

    ~CTextImage2()
    {
        delete _image[0];
        delete _image[1];
    }

    vgui::TextImage* GetImage(int image)
    {
        return _image[image];
    }

    void getSize(int& wide, int& tall) override
    {
        int w1, w2, t1, t2;
        _image[0]->getTextSize(w1, t1);
        _image[1]->getTextSize(w2, t2);

        wide = w1 + w2;
        tall = V_max(t1, t2);
        setSize(wide, tall);
    }

    void doPaint(vgui::Panel* panel) override
    {
        _image[0]->doPaint(panel);
        _image[1]->doPaint(panel);
    }

    void setPos(int x, int y) override
    {
        _image[0]->setPos(x, y);

        int swide, stall;
        _image[0]->getSize(swide, stall);

        int wide, tall;
        _image[1]->getSize(wide, tall);
        _image[1]->setPos(x + wide, y + (stall * 0.9) - tall);
    }

    void setColor(vgui::Color color) override
    {
        _image[0]->setColor(color);
    }

    void setColor2(vgui::Color color)
    {
        _image[1]->setColor(color);
    }

private:
    vgui::TextImage* _image[2];
};

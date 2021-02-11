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

#include <VGUI_Font.h>
#include <VGUI_Label.h>

#include "hud/CHud.h"
#include "CTextImage2.h"

// Purpose: Custom label for cells in the Scoreboard's Table Header
class CLabelHeader : public vgui::Label
{
public:
    CLabelHeader() : Label("")
    {
        _dualImage = new CTextImage2();
        _dualImage->setColor2(vgui::Color(255, 170, 0, 0));
        _row = -2;
        _useFgColorAsImageColor = true;
        _offset[0] = 0;
        _offset[1] = 0;
    }

    ~CLabelHeader()
    {
        delete _dualImage;
    }

    void setRow(int row)
    {
        _row = row;
    }

    void setFgColorAsImageColor(bool state)
    {
        _useFgColorAsImageColor = state;
    }

    void setText(int textBufferLen, const char* text) override
    {
        _dualImage->GetImage(0)->setText(text);

        // calculate the text size
        vgui::Font* font = _dualImage->GetImage(0)->getFont();
        _gap = 0;
        for (const char* ch = text; *ch != 0; ch++)
        {
            int a, b, c;
            font->getCharABCwide(*ch, a, b, c);
            _gap += (a + b + c);
        }

        _gap += XRES(5);
    }

    virtual void setText(const char* text)
    {
        // strip any non-alnum characters from the end
        char buf[512];
        strcpy(buf, text);

        int len = strlen(buf);
        while (len && isspace(buf[--len]))
        {
            buf[len] = 0;
        }

        CLabelHeader::setText(0, buf);
    }

    void setText2(const char* text)
    {
        _dualImage->GetImage(1)->setText(text);
    }

    void getTextSize(int& wide, int& tall) override
    {
        _dualImage->getSize(wide, tall);
    }

    void setFgColor(int r, int g, int b, int a) override
    {
        Label::setFgColor(r, g, b, a);
        vgui::Color color(r, g, b, a);
        _dualImage->setColor(color);
        _dualImage->setColor2(color);
        repaint();
    }

    void setFgColor(vgui::Scheme::SchemeColor sc) override
    {
        int r, g, b, a;
        Label::setFgColor(sc);
        Label::getFgColor(r, g, b, a);

        // Call the r,g,b,a version so it sets the color in the dualImage..
        setFgColor(r, g, b, a);
    }

    void setFont(vgui::Font* font) override
    {
        _dualImage->GetImage(0)->setFont(font);
    }

    void setFont2(vgui::Font* font)
    {
        _dualImage->GetImage(1)->setFont(font);
    }

    // this adjust the absolute position of the text after alignment is calculated
    void setTextOffset(int x, int y)
    {
        _offset[0] = x;
        _offset[1] = y;
    }

    void paint() override;
    void paintBackground() override;
    void calcAlignment(int iwide, int itall, int& x, int& y);

private:
    CTextImage2* _dualImage;
    int _row;
    int _gap;
    int _offset[2];
    bool _useFgColorAsImageColor;
};

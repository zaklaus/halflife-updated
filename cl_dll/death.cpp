/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
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
//
// death notice
//
#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"

float g_ColorBlue[3] = { 0.6, 0.8, 1.0 };
float g_ColorRed[3] = { 1.0, 0.25, 0.25 };
float g_ColorGreen[3] = { 0.6, 1.0, 0.6 };
float g_ColorYellow[3] = { 1.0, 0.7, 0.0 };
float g_ColorGrey[3] = { 0.8, 0.8, 0.8 };

float* GetClientColor(int clientIndex)
{
	switch (g_PlayerExtraInfo[clientIndex].teamnumber)
	{
	case 1:    return g_ColorBlue;
	case 2: return g_ColorRed;
	case 3: return g_ColorYellow;
	case 4: return g_ColorGreen;
	case 0: return g_ColorYellow;

	default: return g_ColorGrey;
	}

	return NULL;
}

DECLARE_MESSAGE( m_DeathNotice, DeathMsg );

int CHudDeathNotice :: Init( void )
{
	gHUD.AddHudElem( this );

	HOOK_MESSAGE( DeathMsg );

	return 1;
}

int CHudDeathNotice :: VidInit( void )
{
	m_hDeathSprite = SPR_Load("sprites/youdied.spr");

	m_fStartTime = -1;

	return 1;
}

int CHudDeathNotice :: Draw( float flTime )
{
	const int m_iFrameRate = 30;
	int frames = SPR_Frames(m_hDeathSprite);

	if (m_fStartTime > 0 && m_fStartTime <= gHUD.m_flTime)
	{
		float localTime = gHUD.m_flTime - m_fStartTime;
		int cFrame = (int)(m_iFrameRate * localTime);

		if (cFrame >= frames)
		{
			m_fStartTime = -1;
			m_iFlags &= ~HUD_ACTIVE;
			return 1;
		}

		// Find the center point based on the sprite alignment, and then put the center of the sprite at that center point
		int halfWidth = SPR_Width(m_hDeathSprite, 0) / 2;
		int halfHeight = SPR_Height(m_hDeathSprite, 0) / 2;

		// m_f[Horizontal|Vertical] are percentage of the screen [width|height] between 0 and 1
		int x = (ScreenWidth - SPR_Width(m_hDeathSprite, 0)) / 2;
		int y = (ScreenHeight - SPR_Height(m_hDeathSprite, 0)) / 2;

		SPR_Set(m_hDeathSprite, 255, 255, 255);
		SPR_DrawAdditive(cFrame, x, y, NULL);
	}

	return 1;
}

// This message handler may be better off elsewhere
int CHudDeathNotice :: MsgFunc_DeathMsg( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );

	// we don't actually care about these parameters
	int killer = READ_BYTE();
	int victim = READ_BYTE();
	char* weapon = READ_STRING();

	m_iFlags |= HUD_ACTIVE;
	m_fStartTime = gHUD.m_flTime + 2; // wait 2 seconds before starting the animation

	PlaySound("youdied.wav", 1);

	return 1;
}

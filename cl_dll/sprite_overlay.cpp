
#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"

DECLARE_MESSAGE( m_SpriteOverlay, SprOverlay)

int CHudSpriteOverlay::Init(void)
{
	HOOK_MESSAGE (SprOverlay);

	gHUD.AddHudElem(this);

	return 1;
};

int CHudSpriteOverlay::VidInit(void)
{
	m_fOverlayStartTime = -1;
	m_fOverlayStopTime = -1;
	m_iFrameRate = 15;
	m_fVerticalAlign = 0.5f;
	m_fHorizontalAlign = 0.5f;

	return 1;
};

int CHudSpriteOverlay::Draw (float flTime)
{
	if (m_fOverlayStartTime > 0)
	{
		if (m_fOverlayStopTime <= flTime)
		{
			m_fOverlayStartTime = m_fOverlayStopTime = -1;
			m_iFlags &= ~HUD_ACTIVE;
			return 1;
		}

		int frames = SPR_Frames(m_hOverlaySprite);
		float localTime = flTime - m_fOverlayStartTime;
		int cFrame = ((int) (m_iFrameRate * localTime)) % frames;

		// Find the center point based on the sprite alignment, and then put the center of the sprite at that center point
		int halfWidth = SPR_Width(m_hOverlaySprite, 0) / 2;
		int halfHeight = SPR_Height(m_hOverlaySprite, 0) / 2;

		// m_f[Horizontal|Vertical] are percentage of the screen [width|height] between 0 and 1
		int x = (ScreenWidth * m_fHorizontalAlign) - halfWidth;
		int y = (ScreenHeight * m_fVerticalAlign) - halfHeight;

		SPR_Set(m_hOverlaySprite, 255, 255, 255);
		SPR_DrawAdditive(cFrame, x, y, NULL);
	}
	return 1;
}

int CHudSpriteOverlay::MsgFunc_SprOverlay( const char *pszName,  int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );

	int fRate = READ_SHORT();
	int ha = READ_SHORT();
	int va = READ_SHORT();
	float time = READ_SHORT();
	char *pString = READ_STRING();

	m_hOverlaySprite = SPR_Load( pString );
	m_iFrameRate = fRate;
	m_fHorizontalAlign = ha / 100.0f;
	m_fVerticalAlign = va / 100.0f;
	m_fOverlayStartTime = gHUD.m_flTime;
	if (time < 0 && fRate > 0) time = SPR_Frames(m_hOverlaySprite) / (float) fRate;
	m_fOverlayStopTime = gHUD.m_flTime + time;

	// Turn on drawing
	if ( !(m_iFlags & HUD_ACTIVE) )
		m_iFlags |= HUD_ACTIVE;

	return 1;
}

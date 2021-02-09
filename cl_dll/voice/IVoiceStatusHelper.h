//========= Copyright © 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
#pragma once

// This is provided by each mod to access data that may not be the same across mods.
class IVoiceStatusHelper
{
public:
    virtual ~IVoiceStatusHelper()
    {
    }

    // Get RGB color for voice status text about this player.
    virtual void GetPlayerTextColor(int entindex, int color[3]) = 0;

    // Force it to update the cursor state.
    virtual void UpdateCursorState() = 0;

    // Return the height above the bottom that the voice ack icons should be drawn at.
    virtual int GetAckIconHeight() = 0;

    // Return true if the voice manager is allowed to show speaker labels
    // (mods usually return false when the scoreboard is up).
    virtual bool CanShowSpeakerLabels() = 0;
};

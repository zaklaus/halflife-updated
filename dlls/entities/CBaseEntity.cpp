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
* Valve LLC.  All other use, distribution, or modification is prohibited
* without written permission from Valve LLC.
*
****/

#include "CBaseEntity.h"
#include "base/CWorld.h"
#include "decals.h"
#include "movewith.h"
#include "nodes.h"
#include "skill.h"
#include "weapons.h"

// This updates global tables that need to know about entities being removed
void CBaseEntity::UpdateOnRemove(void)
{
    int i;
    CBaseEntity* pTemp;

    if (!g_pWorld)
    {
        ALERT(at_debug, "UpdateOnRemove has no AssistList!\n");
        return;
    }

    //LRC - remove this from the AssistList.
    for (pTemp = g_pWorld; pTemp->m_pAssistLink != NULL; pTemp = pTemp->m_pAssistLink)
    {
        if (this == pTemp->m_pAssistLink)
        {
            //            ALERT(at_console,"REMOVE: %s removed from the Assist List.\n", STRING(pev->classname));
            pTemp->m_pAssistLink = this->m_pAssistLink;
            this->m_pAssistLink = NULL;
            break;
        }
    }

    //LRC
    if (m_pMoveWith)
    {
        // if I'm moving with another entity, take me out of the list. (otherwise things crash!)
        pTemp = m_pMoveWith->m_pChildMoveWith;
        if (pTemp == this)
        {
            m_pMoveWith->m_pChildMoveWith = this->m_pSiblingMoveWith;
        }
        else
        {
            while (pTemp->m_pSiblingMoveWith)
            {
                if (pTemp->m_pSiblingMoveWith == this)
                {
                    pTemp->m_pSiblingMoveWith = this->m_pSiblingMoveWith;
                    break;
                }
                pTemp = pTemp->m_pSiblingMoveWith;
            }
        }
        //        ALERT(at_console,"REMOVE: %s removed from the %s ChildMoveWith list.\n", STRING(pev->classname), STRING(m_pMoveWith->pev->targetname));
    }

    //LRC - do the same thing if another entity is moving with _me_.
    if (m_pChildMoveWith)
    {
        CBaseEntity* pCur = m_pChildMoveWith;
        CBaseEntity* pNext;
        while (pCur != NULL)
        {
            pNext = pCur->m_pSiblingMoveWith;
            // bring children to a stop
            UTIL_SetMoveWithVelocity(pCur, g_vecZero, 100);
            UTIL_SetMoveWithAvelocity(pCur, g_vecZero, 100);
            pCur->m_pMoveWith = NULL;
            pCur->m_pSiblingMoveWith = NULL;
            pCur = pNext;
        }
    }

    if (FBitSet(pev->flags, FL_GRAPHED))
    {
        // this entity was a LinkEnt in the world node graph, so we must remove it from
        // the graph since we are removing it from the world.
        for (i = 0; i < WorldGraph.m_cLinks; i++)
        {
            if (WorldGraph.m_pLinkPool[i].m_pLinkEnt == pev)
            {
                // if this link has a link ent which is the same ent that is removing itself, remove it!
                WorldGraph.m_pLinkPool[i].m_pLinkEnt = NULL;
            }
        }
    }
    if (pev->globalname)
        gGlobalState.EntitySetState(pev->globalname, GLOBAL_DEAD);
}

// Convenient way to delay removing oneself
void CBaseEntity::SUB_Remove(void)
{
    UpdateOnRemove();
    if (pev->health > 0)
    {
        // this situation can screw up monsters who can't tell their entity pointers are invalid.
        pev->health = 0;
        ALERT(at_aiconsole, "SUB_Remove called on entity with health > 0\n");
    }

    REMOVE_ENTITY(ENT(pev));
}


// Convenient way to explicitly do nothing (passed to functions that require a method)
void CBaseEntity::SUB_DoNothing(void)
{
    //    if (pev->ltime)
    //        ALERT(at_console, "Doing Nothing %f\n", pev->ltime);
    //    else
    //        ALERT(at_console, "Doing Nothing %f\n", gpGlobals->time);
}


/*
==============================
SUB_UseTargets

If self.delay is set, a DelayedUse entity will be created that will actually
do the SUB_UseTargets after that many seconds have passed.

Removes all entities with a targetname that match self.killtarget,
and removes them, so some events can remove other triggers.

Search for (string)targetname in all entities that
match (string)self.target and call their .use function (if they have one)

==============================
*/
void CBaseEntity::SUB_UseTargets(CBaseEntity* pActivator, USE_TYPE useType, float value)
{
    //
    // fire targets
    //
    if (!FStringNull(pev->target))
    {
        FireTargets(STRING(pev->target), pActivator, this, useType, value);
    }
}


//
// fade out - slowly fades a entity out, then removes it.
//
// DON'T USE ME FOR GIBS AND STUFF IN MULTIPLAYER! 
// SET A FUTURE THINK AND A RENDERMODE!!
void CBaseEntity::SUB_StartFadeOut(void)
{
    if (pev->rendermode == kRenderNormal)
    {
        pev->renderamt = 255;
        pev->rendermode = kRenderTransTexture;
    }

    pev->solid = SOLID_NOT;
    pev->avelocity = g_vecZero;

    SetNextThink(0.1);
    SetThink(&CBaseEntity::SUB_FadeOut);
}

void CBaseEntity::SUB_FadeOut(void)
{
    if (pev->renderamt > 7)
    {
        pev->renderamt -= 7;
        SetNextThink(0.1);
    }
    else
    {
        pev->renderamt = 0;
        SetNextThink(0.2);
        SetThink(&CBaseEntity::SUB_Remove);
    }
}


//=========================================================
// FVisible - returns true if a line can be traced from
// the caller's eyes to the target
//=========================================================
BOOL CBaseEntity::FVisible(CBaseEntity* pEntity)
{
    TraceResult tr;
    Vector vecLookerOrigin;
    Vector vecTargetOrigin;

    if (FBitSet(pEntity->pev->flags, FL_NOTARGET))
        return FALSE;

    // don't look through water
    if ((pev->waterlevel != 3 && pEntity->pev->waterlevel == 3)
        || (pev->waterlevel == 3 && pEntity->pev->waterlevel == 0))
        return FALSE;

    vecLookerOrigin = pev->origin + pev->view_ofs; //look through the caller's 'eyes'
    vecTargetOrigin = pEntity->EyePosition();

    UTIL_TraceLine(vecLookerOrigin, vecTargetOrigin, ignore_monsters, ignore_glass, ENT(pev)/*pentIgnore*/, &tr);

    if (tr.flFraction != 1.0 && tr.pHit != ENT(pEntity->pev)) //LRC - added so that monsters can "see" some bsp objects
    {
        //        ALERT(at_console, "can't see \"%s\"\n", STRING(pEntity->pev->classname));
        return FALSE; // Line of sight is not established
    }
    else
    {
        //        ALERT(at_console, "Seen ok\n");
        return TRUE; // line of sight is valid.
    }
}

//=========================================================
// FVisible - returns true if a line can be traced from
// the caller's eyes to the target vector
//=========================================================
BOOL CBaseEntity::FVisible(const Vector& vecOrigin)
{
    TraceResult tr;
    Vector vecLookerOrigin;

    vecLookerOrigin = EyePosition(); //look through the caller's 'eyes'

    UTIL_TraceLine(vecLookerOrigin, vecOrigin, ignore_monsters, ignore_glass, ENT(pev)/*pentIgnore*/, &tr);

    if (tr.flFraction != 1.0)
    {
        return FALSE; // Line of sight is not established
    }
    else
    {
        return TRUE; // line of sight is valid.
    }
}

/*
================
TraceAttack
================
*/
void CBaseEntity::TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType)
{
    Vector vecOrigin = ptr->vecEndPos - vecDir * 4;

    if (pev->takedamage)
    {
        AddMultiDamage(pevAttacker, this, flDamage, bitsDamageType);

        int blood = BloodColor();

        if (blood != DONT_BLEED)
        {
            SpawnBlood(vecOrigin, blood, flDamage); // a little surface blood.
            TraceBleed(flDamage, vecDir, ptr, bitsDamageType);
        }
    }
}

/*
================
FireBullets

Go to the trouble of combining multiple pellets into a single damage call.

This version is used by Monsters.
================
*/
void CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq,
                              int iDamage, entvars_t* pevAttacker)
{
    static int tracerCount;
    int tracer;
    TraceResult tr;
    Vector vecRight = gpGlobals->v_right;
    Vector vecUp = gpGlobals->v_up;

    if (pevAttacker == NULL)
        pevAttacker = pev; // the default attacker is ourselves

    ClearMultiDamage();
    gMultiDamage.type = DMG_BULLET | DMG_NEVERGIB;

    for (ULONG iShot = 1; iShot <= cShots; iShot++)
    {
        // get circular gaussian spread
        float x, y, z;
        do
        {
            x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
            y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
            z = x * x + y * y;
        }
        while (z > 1);

        Vector vecDir = vecDirShooting +
            x * vecSpread.x * vecRight +
            y * vecSpread.y * vecUp;
        Vector vecEnd;

        vecEnd = vecSrc + vecDir * flDistance;
        UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev)/*pentIgnore*/, &tr);

        tracer = 0;
        if (iTracerFreq != 0 && (tracerCount++ % iTracerFreq) == 0)
        {
            Vector vecTracerSrc;

            if (IsPlayer())
            {
                // adjust tracer position for player
                vecTracerSrc = vecSrc + Vector(0, 0, -4) + gpGlobals->v_right * 2 + gpGlobals->v_forward * 16;
            }
            else
            {
                vecTracerSrc = vecSrc;
            }

            if (iTracerFreq != 1) // guns that always trace also always decal
                tracer = 1;
            switch (iBulletType)
            {
            case BULLET_MONSTER_MP5:
            case BULLET_MONSTER_9MM:
            case BULLET_MONSTER_12MM:
            default:
                MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, vecTracerSrc);
                WRITE_BYTE(TE_TRACER);
                WRITE_COORD(vecTracerSrc.x);
                WRITE_COORD(vecTracerSrc.y);
                WRITE_COORD(vecTracerSrc.z);
                WRITE_COORD(tr.vecEndPos.x);
                WRITE_COORD(tr.vecEndPos.y);
                WRITE_COORD(tr.vecEndPos.z);
                MESSAGE_END();
                break;
            }
        }
        // do damage, paint decals
        if (tr.flFraction != 1.0)
        {
            CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);

            if (iDamage)
            {
                pEntity->TraceAttack(pevAttacker, iDamage, vecDir, &tr, DMG_BULLET | ((iDamage > 16) ? DMG_ALWAYSGIB : DMG_NEVERGIB));

                TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                DecalGunshot(&tr, iBulletType);
            }
            else
                switch (iBulletType)
                {
                default:
                case BULLET_MONSTER_9MM:
                    pEntity->TraceAttack(pevAttacker, gSkillData.monDmg9MM, vecDir, &tr, DMG_BULLET);

                    TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                    DecalGunshot(&tr, iBulletType);

                    break;

                case BULLET_MONSTER_MP5:
                    pEntity->TraceAttack(pevAttacker, gSkillData.monDmgMP5, vecDir, &tr, DMG_BULLET);

                    TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                    DecalGunshot(&tr, iBulletType);

                    break;

                case BULLET_MONSTER_12MM:
                    pEntity->TraceAttack(pevAttacker, gSkillData.monDmg12MM, vecDir, &tr, DMG_BULLET);
                    if (!tracer)
                    {
                        TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                        DecalGunshot(&tr, iBulletType);
                    }
                    break;

                case BULLET_PLAYER_357:
                    pEntity->TraceAttack(pevAttacker, gSkillData.plrDmg357, vecDir, &tr, DMG_BULLET);
                    if (!tracer)
                    {
                        TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                        DecalGunshot(&tr, iBulletType);
                    }
                    break;

                case BULLET_NONE: // FIX 
                    pEntity->TraceAttack(pevAttacker, 50, vecDir, &tr, DMG_CLUB);
                    TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                    // only decal glass
                    if (!FNullEnt(tr.pHit) && VARS(tr.pHit)->rendermode != 0)
                    {
                        UTIL_DecalTrace(&tr, DECAL_GLASSBREAK1 + RANDOM_LONG(0, 2));
                    }

                    break;
                }
        }
        // make bullet trails
        UTIL_BubbleTrail(vecSrc, tr.vecEndPos, (flDistance * tr.flFraction) / 64.0);
    }
    ApplyMultiDamage(pev, pevAttacker);
}


/*
================
FireBullets

Go to the trouble of combining multiple pellets into a single damage call.

This version is used by Players, uses the random seed generator to sync client and server side shots.
================
*/
Vector CBaseEntity::FireBulletsPlayer(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq,
                                      int iDamage, entvars_t* pevAttacker, int shared_rand)
{
    static int tracerCount;
    TraceResult tr;
    Vector vecRight = gpGlobals->v_right;
    Vector vecUp = gpGlobals->v_up;
    float x, y, z;

    if (pevAttacker == NULL)
        pevAttacker = pev; // the default attacker is ourselves

    ClearMultiDamage();
    gMultiDamage.type = DMG_BULLET | DMG_NEVERGIB;

    for (ULONG iShot = 1; iShot <= cShots; iShot++)
    {
        //Use player's random seed.
        // get circular gaussian spread
        x = UTIL_SharedRandomFloat(shared_rand + iShot, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + (1 + iShot), -0.5, 0.5);
        y = UTIL_SharedRandomFloat(shared_rand + (2 + iShot), -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + (3 + iShot), -0.5, 0.5);
        z = x * x + y * y;

        Vector vecDir = vecDirShooting +
            x * vecSpread.x * vecRight +
            y * vecSpread.y * vecUp;
        Vector vecEnd;

        vecEnd = vecSrc + vecDir * flDistance;
        UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev)/*pentIgnore*/, &tr);

        // do damage, paint decals
        if (tr.flFraction != 1.0)
        {
            CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);

            if (iDamage)
            {
                pEntity->TraceAttack(pevAttacker, iDamage, vecDir, &tr, DMG_BULLET | ((iDamage > 16) ? DMG_ALWAYSGIB : DMG_NEVERGIB));

                TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                DecalGunshot(&tr, iBulletType);
            }
            else
                switch (iBulletType)
                {
                default:
                case BULLET_PLAYER_9MM:
                    pEntity->TraceAttack(pevAttacker, gSkillData.plrDmg9MM, vecDir, &tr, DMG_BULLET);
                    break;

                case BULLET_PLAYER_MP5:
                    pEntity->TraceAttack(pevAttacker, gSkillData.plrDmgMP5, vecDir, &tr, DMG_BULLET);
                    break;

                case BULLET_PLAYER_BUCKSHOT:
                    // make distance based!
                    pEntity->TraceAttack(pevAttacker, gSkillData.plrDmgBuckshot, vecDir, &tr, DMG_BULLET);
                    break;

                case BULLET_PLAYER_357:
                    pEntity->TraceAttack(pevAttacker, gSkillData.plrDmg357, vecDir, &tr, DMG_BULLET);
                    break;

                case BULLET_NONE: // FIX 
                    pEntity->TraceAttack(pevAttacker, 50, vecDir, &tr, DMG_CLUB);
                    TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
                    // only decal glass
                    if (!FNullEnt(tr.pHit) && VARS(tr.pHit)->rendermode != 0)
                    {
                        UTIL_DecalTrace(&tr, DECAL_GLASSBREAK1 + RANDOM_LONG(0, 2));
                    }

                    break;
                }
        }
        // make bullet trails
        UTIL_BubbleTrail(vecSrc, tr.vecEndPos, (flDistance * tr.flFraction) / 64.0);
    }
    ApplyMultiDamage(pev, pevAttacker);

    return Vector(x * vecSpread.x, y * vecSpread.y, 0.0);
}

void CBaseEntity::TraceBleed(float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType)
{
    if (BloodColor() == DONT_BLEED)
        return;

    if (flDamage == 0)
        return;

    if (!(bitsDamageType & (DMG_CRUSH | DMG_BULLET | DMG_SLASH | DMG_BLAST | DMG_CLUB | DMG_MORTAR)))
        return;

    // make blood decal on the wall! 
    TraceResult Bloodtr;
    Vector vecTraceDir;
    float flNoise;
    int cCount;
    int i;

    /*
        if ( !IsAlive() )
        {
            // dealing with a dead monster.
            if ( pev->max_health <= 0 )
            {
                // no blood decal for a monster that has already decalled its limit.
                return;
            }
            else
            {
                pev->max_health--;
            }
        }
    */

    if (flDamage < 10)
    {
        flNoise = 0.1;
        cCount = 1;
    }
    else if (flDamage < 25)
    {
        flNoise = 0.2;
        cCount = 2;
    }
    else
    {
        flNoise = 0.3;
        cCount = 4;
    }

    for (i = 0; i < cCount; i++)
    {
        vecTraceDir = vecDir * -1; // trace in the opposite direction the shot came from (the direction the shot is going)

        vecTraceDir.x += RANDOM_FLOAT(-flNoise, flNoise);
        vecTraceDir.y += RANDOM_FLOAT(-flNoise, flNoise);
        vecTraceDir.z += RANDOM_FLOAT(-flNoise, flNoise);

        UTIL_TraceLine(ptr->vecEndPos, ptr->vecEndPos + vecTraceDir * -172, ignore_monsters, ENT(pev), &Bloodtr);

        if (Bloodtr.flFraction != 1.0)
        {
            UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
        }
    }
}

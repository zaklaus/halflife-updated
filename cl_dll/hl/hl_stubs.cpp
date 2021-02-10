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

/*
==========================
This file contains "stubs" of class member implementations so that we can predict certain
 weapons client side.  From time to time you might find that you need to implement part of the
 these functions.  If so, cut it from here, paste it in hl_weapons.cpp or somewhere else and
 add in the functionality you need.
==========================
*/
#include "extdll.h"
#include "util.h"
#include "entities/player/CBasePlayer.h"
#include "weapons.h"
#include "nodes/NodeConstants.h"
#include "entities/effects/CSoundEnt.h"
#include "entities/player/CBasePlayerItem.h"
#include "entities/weapons/CBasePlayerWeapon.h"
#include "entities/ammo/CBasePlayerAmmo.h"
#include "entities/weapons/CGrenade.h"
#include "util/skill.h"

// Globals used by game logic
const Vector g_vecZero = Vector(0, 0, 0);
int gmsgWeapPickup = 0;
enginefuncs_t g_engfuncs;
globalvars_t* gpGlobals;
struct skilldata_t gSkillData;

void EMIT_SOUND_DYN(edict_t* entity, int channel, const char* sample, float volume, float attenuation, int flags, int pitch) { return; }

// CBaseEntity Stubs
int CBaseEntity::TakeHealth(float flHealth, int bitsDamageType) { return 1; }
int CBaseEntity::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) { return 1; }
CBaseEntity* CBaseEntity::GetNextTarget(void) { return NULL; }
int CBaseEntity::Save(CSave& save) { return 1; }
int CBaseEntity::Restore(CRestore& restore) { return 1; }
void CBaseEntity::SetObjectCollisionBox(void) { return; }
int CBaseEntity::Intersects(CBaseEntity* pOther) { return 0; }
void CBaseEntity::MakeDormant(void) { return; }
int CBaseEntity::IsDormant(void) { return 0; }
BOOL CBaseEntity::IsInWorld(void) { return TRUE; }
int CBaseEntity::ShouldToggle(USE_TYPE useType, BOOL currentState) { return 0; }
int CBaseEntity::DamageDecal(int bitsDamageType) { return -1; }
CBaseEntity* CBaseEntity::Create(const char* szName, const Vector& vecOrigin, const Vector& vecAngles, edict_t* pentOwner) { return NULL; }
void CBaseEntity::SUB_Remove(void) { return; }
void CBaseEntity::Activate(void) { return; } //LRC
void CBaseEntity::InitMoveWith(void) { return; } //LRC
void CBaseEntity::SetNextThink(float delay, BOOL correctSpeed) { return; } //LRC
void CBaseEntity::AbsoluteNextThink(float time, BOOL correctSpeed) { return; } //LRC
void CBaseEntity::ThinkCorrection() { return; } //LRC
BOOL CBaseEntity::FVisible(CBaseEntity* pEntity) { return FALSE; }
BOOL CBaseEntity::FVisible(const Vector& vecOrigin) { return FALSE; }
void CBaseEntity::TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) { return; }
void CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t* pevAttacker) { return; }
void CBaseEntity::TraceBleed(float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) { return; }

// CBaseDelay Stubs
void CBaseDelay::KeyValue(struct KeyValueData_s*) { return; }
int CBaseDelay::Restore(class CRestore&) { return 1; }
int CBaseDelay::Save(class CSave&) { return 1; }

// CBaseAnimating Stubs
int CBaseAnimating::Restore(class CRestore&) { return 1; }
int CBaseAnimating::Save(class CSave&) { return 1; }
float CBaseAnimating::StudioFrameAdvance(float flInterval) { return 0.0; }
int CBaseAnimating::LookupActivity(int activity) { return 0; }
int CBaseAnimating::LookupActivityHeaviest(int activity) { return 0; }
int CBaseAnimating::LookupSequence(const char* label) { return 0; }
void CBaseAnimating::ResetSequenceInfo() { return; }
BOOL CBaseAnimating::GetSequenceFlags() { return FALSE; }
void CBaseAnimating::DispatchAnimEvents(float flInterval) { return; }
float CBaseAnimating::SetBoneController(int iController, float flValue) { return 0.0; }
void CBaseAnimating::InitBoneControllers(void) { return; }
float CBaseAnimating::SetBlending(int iBlender, float flValue) { return 0; }
void CBaseAnimating::GetBonePosition(int iBone, Vector& origin, Vector& angles) { return; }
void CBaseAnimating::GetAttachment(int iAttachment, Vector& origin, Vector& angles) { return; }
int CBaseAnimating::FindTransition(int iEndingSequence, int iGoalSequence, int* piDir) { return -1; }
void CBaseAnimating::GetAutomovement(Vector& origin, Vector& angles, float flInterval) { return; }
void CBaseAnimating::SetBodygroup(int iGroup, int iValue) { return; }
int CBaseAnimating::GetBodygroup(int iGroup) { return 0; }

// CBaseToggle Stubs
int CBaseToggle::Restore(class CRestore&) { return 1; }
int CBaseToggle::Save(class CSave&) { return 1; }
void CBaseToggle::KeyValue(struct KeyValueData_s*) { return; }
STATE CBaseToggle::GetState(void) { return STATE_ON; } //LRC

// CGrenade Stubs
void CGrenade::BounceSound(void) { return; }
void CGrenade::Explode(Vector, Vector) { return; }
void CGrenade::Explode(TraceResult*, int) { return; }
void CGrenade::Killed(entvars_t*, int) { return; }
void CGrenade::Spawn(void) { return; }
CGrenade* CGrenade::ShootTimed(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time) { return 0; }
CGrenade* CGrenade::ShootContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity) { return 0; }
void CGrenade::DetonateUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) { return; }

// CBaseMonster Stubs
CBaseEntity* CBaseMonster::CheckTraceHullAttack(float flDist, int iDamage, int iDmgType) { return NULL; }
void CBaseMonster::Eat(float flFullDuration) { return; }
BOOL CBaseMonster::FShouldEat(void) { return TRUE; }
void CBaseMonster::BarnacleVictimBitten(entvars_t* pevBarnacle) { return; }
void CBaseMonster::BarnacleVictimReleased(void) { return; }
void CBaseMonster::Listen(void) { return; }
float CBaseMonster::FLSoundVolume(CSound* pSound) { return 0.0; }
BOOL CBaseMonster::FValidateHintType(short sHint) { return FALSE; }
void CBaseMonster::Look(int iDistance) { return; }
int CBaseMonster::ISoundMask(void) { return 0; }
CSound* CBaseMonster::PBestSound(void) { return NULL; }
CSound* CBaseMonster::PBestScent(void) { return NULL; }
void CBaseMonster::MonsterThink(void) { return; }
void CBaseMonster::MonsterUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) { return; }
int CBaseMonster::IgnoreConditions(void) { return 0; }
void CBaseMonster::RouteClear(void) { return; }
void CBaseMonster::RouteNew(void) { return; }
BOOL CBaseMonster::FRouteClear(void) { return FALSE; }
BOOL CBaseMonster::FRefreshRoute(void) { return 0; }
BOOL CBaseMonster::MoveToEnemy(Activity movementAct, float waitTime) { return FALSE; }
BOOL CBaseMonster::MoveToLocation(Activity movementAct, float waitTime, const Vector& goal) { return FALSE; }
BOOL CBaseMonster::MoveToTarget(Activity movementAct, float waitTime) { return FALSE; }
BOOL CBaseMonster::MoveToNode(Activity movementAct, float waitTime, const Vector& goal) { return FALSE; }
void CBaseMonster::RouteSimplify(CBaseEntity* pTargetEnt) { return; }
BOOL CBaseMonster::FBecomeProne(void) { return TRUE; }
BOOL CBaseMonster::CheckRangeAttack1(float flDot, float flDist) { return FALSE; }
BOOL CBaseMonster::CheckRangeAttack2(float flDot, float flDist) { return FALSE; }
BOOL CBaseMonster::CheckMeleeAttack1(float flDot, float flDist) { return FALSE; }
BOOL CBaseMonster::CheckMeleeAttack2(float flDot, float flDist) { return FALSE; }
void CBaseMonster::CheckAttacks(CBaseEntity* pTarget, float flDist) { return; }
BOOL CBaseMonster::FCanCheckAttacks(void) { return FALSE; }
int CBaseMonster::CheckEnemy(CBaseEntity* pEnemy) { return 0; }
void CBaseMonster::PushEnemy(CBaseEntity* pEnemy, Vector& vecLastKnownPos) { return; }
BOOL CBaseMonster::PopEnemy() { return FALSE; }
void CBaseMonster::SetActivity(Activity NewActivity) { return; }
void CBaseMonster::SetSequenceByName(const char* szSequence) { return; }
int CBaseMonster::CheckLocalMove(const Vector& vecStart, const Vector& vecEnd, CBaseEntity* pTarget, float* pflDist) { return 0; }
float CBaseMonster::OpenDoorAndWait(entvars_t* pevDoor) { return 0.0; }
void CBaseMonster::AdvanceRoute(float distance) { return; }
int CBaseMonster::RouteClassify(int iMoveFlag) { return 0; }
BOOL CBaseMonster::BuildRoute(const Vector& vecGoal, int iMoveFlag, CBaseEntity* pTarget) { return FALSE; }
void CBaseMonster::InsertWaypoint(Vector vecLocation, int afMoveFlags) { return; }
BOOL CBaseMonster::FTriangulate(const Vector& vecStart, const Vector& vecEnd, float flDist, CBaseEntity* pTargetEnt, Vector* pApex) { return FALSE; }
void CBaseMonster::Move(float flInterval) { return; }
BOOL CBaseMonster::ShouldAdvanceRoute(float flWaypointDist) { return FALSE; }
void CBaseMonster::MoveExecute(CBaseEntity* pTargetEnt, const Vector& vecDir, float flInterval) { return; }
void CBaseMonster::MonsterInit(void) { return; }
void CBaseMonster::MonsterInitThink(void) { return; }
void CBaseMonster::StartMonster(void) { return; }
void CBaseMonster::MovementComplete(void) { return; }
int CBaseMonster::TaskIsRunning(void) { return 0; }
int CBaseMonster::IRelationship(CBaseEntity* pTarget) { return 0; }
BOOL CBaseMonster::FindCover(Vector vecThreat, Vector vecViewOffset, float flMinDist, float flMaxDist) { return FALSE; }
BOOL CBaseMonster::BuildNearestRoute(Vector vecThreat, Vector vecViewOffset, float flMinDist, float flMaxDist) { return FALSE; }
CBaseEntity* CBaseMonster::BestVisibleEnemy(void) { return NULL; }
BOOL CBaseMonster::FInViewCone(CBaseEntity* pEntity) { return FALSE; }
BOOL CBaseMonster::FInViewCone(Vector* pOrigin) { return FALSE; }
void CBaseMonster::MakeIdealYaw(Vector vecTarget) { return; }
float CBaseMonster::FlYawDiff(void) { return 0.0; }
float CBaseMonster::ChangeYaw(int yawSpeed) { return 0; }
float CBaseMonster::VecToYaw(Vector vecDir) { return 0.0; }
void CBaseMonster::SetEyePosition(void) { return; }
void CBaseMonster::HandleAnimEvent(MonsterEvent_t* pEvent) { return; }
Vector CBaseMonster::GetGunPosition(void) { return g_vecZero; }
void CBaseMonster::MakeDamageBloodDecal(int cCount, float flNoise, TraceResult* ptr, const Vector& vecDir) { return; }
BOOL CBaseMonster::FGetNodeRoute(Vector vecDest) { return TRUE; }
int CBaseMonster::FindHintNode(void) { return NO_NODE; }
void CBaseMonster::ReportAIState(void) { return; }
void CBaseMonster::KeyValue(KeyValueData* pkvd) { return; }
BOOL CBaseMonster::FCheckAITrigger(void) { return FALSE; }
int CBaseMonster::CanPlaySequence(int interruptLevel) { return FALSE; } //LRC - prototype changed
BOOL CBaseMonster::FindLateralCover(const Vector& vecThreat, const Vector& vecViewOffset) { return FALSE; }
Vector CBaseMonster::ShootAtEnemy(const Vector& shootOrigin) { return g_vecZero; }
BOOL CBaseMonster::FacingIdeal(void) { return FALSE; }
BOOL CBaseMonster::FCanActiveIdle(void) { return FALSE; }
void CBaseMonster::PlaySentence(const char* pszSentence, float duration, float volume, float attenuation) { return; }
void CBaseMonster::PlayScriptedSentence(const char* pszSentence, float duration, float volume, float attenuation, BOOL bConcurrent, CBaseEntity* pListener) { return; }
void CBaseMonster::SentenceStop(void) { return; }
void CBaseMonster::CorpseFallThink(void) { return; }
void CBaseMonster::MonsterInitDead(void) { return; }
BOOL CBaseMonster::BBoxFlat(void) { return TRUE; }
BOOL CBaseMonster::GetEnemy(void) { return FALSE; }
void CBaseMonster::TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) { return; }
CBaseEntity* CBaseMonster::DropItem(const char* pszItemName, const Vector& vecPos, const Vector& vecAng) { return NULL; }
BOOL CBaseMonster::ShouldFadeOnDeath(void) { return FALSE; }
void CBaseMonster::RadiusDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType) { return; }
void CBaseMonster::RadiusDamage(Vector vecSrc, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType) { return; }
void CBaseMonster::FadeMonster(void) { return; }
void CBaseMonster::GibMonster(void) { return; }
BOOL CBaseMonster::HasHumanGibs(void) { return FALSE; }
BOOL CBaseMonster::HasAlienGibs(void) { return FALSE; }
Activity CBaseMonster::GetDeathActivity(void) { return ACT_DIE_HEADSHOT; }
MONSTERSTATE CBaseMonster::GetIdealState(void) { return MONSTERSTATE_ALERT; }
Schedule_t* CBaseMonster::GetScheduleOfType(int Type) { return NULL; }
Schedule_t* CBaseMonster::GetSchedule(void) { return NULL; }
void CBaseMonster::RunTask(Task_t* pTask) { return; }
void CBaseMonster::StartTask(Task_t* pTask) { return; }
Schedule_t* CBaseMonster::ScheduleFromName(const char* pName) { return NULL; }
void CBaseMonster::BecomeDead(void) { return; }
void CBaseMonster::RunAI(void) { return; }
void CBaseMonster::Killed(entvars_t* pevAttacker, int iGib) { return; }
int CBaseMonster::TakeHealth(float flHealth, int bitsDamageType) { return 0; }
int CBaseMonster::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) { return 0; }
int CBaseMonster::Restore(class CRestore&) { return 1; }
int CBaseMonster::Save(class CSave&) { return 1; }

// CBasePlayer Stubs
void CBasePlayer::DeathSound(void) { return; }
int CBasePlayer::TakeHealth(float flHealth, int bitsDamageType) { return 0; }
void CBasePlayer::TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) { return; }
int CBasePlayer::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) { return 0; }
void CBasePlayer::PackDeadPlayerItems(void) { return; }
void CBasePlayer::RemoveAllItems(BOOL removeSuit) { return; }
void CBasePlayer::SetAnimation(PLAYER_ANIM playerAnim) { return; }
void CBasePlayer::WaterMove() { return; }
BOOL CBasePlayer::IsOnLadder(void) { return FALSE; }
void CBasePlayer::PlayerDeathThink(void) { return; }
void CBasePlayer::StartDeathCam(void) { return; }
void CBasePlayer::StartObserver(Vector vecPosition, Vector vecViewAngle) { return; }
void CBasePlayer::PlayerUse(void) { return; }
void CBasePlayer::Jump() { return; }
void CBasePlayer::Duck() { return; }
int CBasePlayer::Classify(void) { return 0; }
void CBasePlayer::PreThink(void) { return; }
void CBasePlayer::CheckTimeBasedDamage() { return; }
void CBasePlayer::UpdateGeigerCounter(void) { return; }
void CBasePlayer::CheckSuitUpdate() { return; }
void CBasePlayer::SetSuitUpdate(const char* name, int fgroup, int iNoRepeatTime) { return; }
void CBasePlayer::UpdatePlayerSound(void) { return; }
void CBasePlayer::PostThink() { return; }
void CBasePlayer::Precache(void) { return; }
int CBasePlayer::Save(CSave& save) { return 0; }
void CBasePlayer::RenewItems(void) { return; }
int CBasePlayer::Restore(CRestore& restore) { return 0; }
BOOL CBasePlayer::HasWeapons(void) { return FALSE; }
void CBasePlayer::SelectPrevItem(int iItem) { return; }
BOOL CBasePlayer::FlashlightIsOn(void) { return FALSE; }
void CBasePlayer::FlashlightTurnOn(void) { return; }
void CBasePlayer::FlashlightTurnOff(void) { return; }
void CBasePlayer::ForceClientDllUpdate(void) { return; }
void CBasePlayer::ImpulseCommands() { return; }
void CBasePlayer::CheatImpulseCommands(int iImpulse) { return; }
int CBasePlayer::AddPlayerItem(CBasePlayerItem* pItem) { return FALSE; }
int CBasePlayer::RemovePlayerItem(CBasePlayerItem* pItem) { return FALSE; }
void CBasePlayer::ItemPostFrame() { return; }
int CBasePlayer::AmmoInventory(int iAmmoIndex) { return -1; }
int CBasePlayer::GetAmmoIndex(const char* psz) { return -1; }
void CBasePlayer::SendAmmoUpdate(void) { return; }
void CBasePlayer::UpdateClientData(void) { return; }
BOOL CBasePlayer::FBecomeProne(void) { return TRUE; }
void CBasePlayer::BarnacleVictimBitten(entvars_t* pevBarnacle) { return; }
void CBasePlayer::BarnacleVictimReleased(void) { return; }
int CBasePlayer::Illumination(void) { return 0; }
void CBasePlayer::EnableControl(BOOL fControl) { return; }
Vector CBasePlayer::GetAutoaimVector(float flDelta) { return g_vecZero; }
Vector CBasePlayer::AutoaimDeflection(Vector& vecSrc, float flDist, float flDelta) { return g_vecZero; }
void CBasePlayer::ResetAutoaim() { return; }
void CBasePlayer::SetCustomDecalFrames(int nFrames) { return; }
int CBasePlayer::GetCustomDecalFrames(void) { return -1; }
void CBasePlayer::DropPlayerItem(char* pszItemName) { return; }
BOOL CBasePlayer::HasPlayerItem(CBasePlayerItem* pCheckItem) { return FALSE; }
Vector CBasePlayer::GetGunPosition(void) { return g_vecZero; }
const char* CBasePlayer::TeamID(void) { return ""; }
int CBasePlayer::GiveAmmo(int iCount, const char* szName, int iMax) { return 0; }
void CBasePlayer::AddPoints(int score, BOOL bAllowNegativeScore) { return; }
void CBasePlayer::AddPointsToTeam(int score, BOOL bAllowNegativeScore) { return; }

// CBasePlayerItem Stubs
ItemInfo CBasePlayerItem::ItemInfoArray[MAX_WEAPONS];
int CBasePlayerItem::Restore(class CRestore&) { return 1; }
int CBasePlayerItem::Save(class CSave&) { return 1; }
void CBasePlayerItem::SetObjectCollisionBox(void) { return; }
void CBasePlayerItem::FallInit(void) { return; }
void CBasePlayerItem::FallThink(void) { return; }
void CBasePlayerItem::Materialize(void) { return; }
void CBasePlayerItem::AttemptToMaterialize(void) { return; }
void CBasePlayerItem::CheckRespawn(void) { return; }
CBaseEntity* CBasePlayerItem::Respawn(void) { return NULL; }
void CBasePlayerItem::DefaultTouch(CBaseEntity* pOther) { return; }
void CBasePlayerItem::DestroyItem(void) { return; }
int CBasePlayerItem::AddToPlayer(CBasePlayer* pPlayer) { return TRUE; }
void CBasePlayerItem::Drop(void) { return; }
void CBasePlayerItem::Kill(void) { return; }
void CBasePlayerItem::Holster(int skiplocal) { return; }
void CBasePlayerItem::AttachToPlayer(CBasePlayer* pPlayer) { return; }

// CBasePlayerWeapon Stubs
int CBasePlayerWeapon::Restore(class CRestore&) { return 1; }
int CBasePlayerWeapon::Save(class CSave&) { return 1; }
float CBasePlayerWeapon::GetNextAttackDelay(float flTime) { return flTime; }
int CBasePlayerWeapon::AddDuplicate(CBasePlayerItem* pOriginal) { return 0; }
int CBasePlayerWeapon::AddToPlayer(CBasePlayer* pPlayer) { return FALSE; }
int CBasePlayerWeapon::UpdateClientData(CBasePlayer* pPlayer) { return 0; }
BOOL CBasePlayerWeapon::AddPrimaryAmmo(int iCount, char* szName, int iMaxClip, int iMaxCarry) { return TRUE; }
BOOL CBasePlayerWeapon::AddSecondaryAmmo(int iCount, char* szName, int iMax) { return TRUE; }
BOOL CBasePlayerWeapon::IsUseable(void) { return TRUE; }
int CBasePlayerWeapon::PrimaryAmmoIndex(void) { return -1; }
int CBasePlayerWeapon::SecondaryAmmoIndex(void) { return -1; }
int CBasePlayerWeapon::ExtractAmmo(CBasePlayerWeapon* pWeapon) { return 0; }
int CBasePlayerWeapon::ExtractClipAmmo(CBasePlayerWeapon* pWeapon) { return 0; }
void CBasePlayerWeapon::RetireWeapon(void) { return; }

// CBasePlayerAmmo Stubs
void CBasePlayerAmmo::Spawn(void) { return; }
CBaseEntity* CBasePlayerAmmo::Respawn(void) { return this; }
void CBasePlayerAmmo::Materialize(void) { return; }
void CBasePlayerAmmo::DefaultTouch(CBaseEntity* pOther) { return; }

// CSoundEnt Stubs
void CSoundEnt::InsertSound(int iType, const Vector& vecOrigin, int iVolume, float flDuration) { return; }

// CSprite Stubs
CSprite* CSprite::SpriteCreate(const char* pSpriteName, const Vector& origin, BOOL animate) { return 0; }
void CSprite::Expand(float scaleSpeed, float fadeSpeed) { return; }

// CBeam Stubs
void CBeam::PointEntInit(const Vector& start, int endIndex) { return; }
CBeam* CBeam::BeamCreate(const char* pSpriteName, int width) { return NULL; }

// DEBUG Stubs
edict_t* DBG_EntOfVars(const entvars_t* pev) { return NULL; }
void DBG_AssertFunction(BOOL fExpr, const char* szExpr, const char* szFile, int szLine, const char* szMessage) { return; }

// UTIL_* Stubs
void UTIL_PrecacheOther(const char* szClassname) { return; }
void UTIL_BloodDrips(const Vector& origin, const Vector& direction, int color, int amount) { return; }
void UTIL_DecalTrace(TraceResult* pTrace, int decalNumber) { return; }
void UTIL_GunshotDecalTrace(TraceResult* pTrace, int decalNumber) { return; }
void UTIL_MakeVectors(const Vector& vecAngles) { return; }
BOOL UTIL_IsValidEntity(edict_t* pent) { return TRUE; }
void UTIL_SetOrigin(CBaseEntity*, const Vector& org) { return; }
BOOL UTIL_GetNextBestWeapon(CBasePlayer* pPlayer, CBasePlayerItem* pCurrentWeapon) { return TRUE; }
void UTIL_LogPrintf(char*, ...) { return; }
void UTIL_ClientPrintAll(int, char const*, char const*, char const*, char const*, char const*) { return; }
void UTIL_Remove(CBaseEntity* pEntity) { return; }
void UTIL_SetSize(entvars_t* pev, const Vector& vecMin, const Vector& vecMax) { return; }
CBaseEntity* UTIL_FindEntityInSphere(CBaseEntity* pStartEntity, const Vector& vecCenter, float flRadius) { return 0; }
Vector UTIL_VecToAngles(const Vector& vec) { return 0; }

// Misc stubs
void ClientPrint(entvars_t* client, int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4) { return; }
int ShouldSimplify(int routeType) { return TRUE; }
int TrainSpeed(int iSpeed, int iMax) { return 0; }
CBaseEntity* FindEntityForward(CBaseEntity* pMe) { return NULL; }
void AddAmmoNameToAmmoRegistry(const char* szAmmoname) { return; }

void ClearMultiDamage(void) { return; }
void ApplyMultiDamage(entvars_t* pevInflictor, entvars_t* pevAttacker) { return; }
void AddMultiDamage(entvars_t* pevInflictor, CBaseEntity* pEntity, float flDamage, int bitsDamageType) { return; }
void RadiusDamage(Vector vecSrc, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType) { return; }

int DamageDecal(CBaseEntity* pEntity, int bitsDamageType) { return 0; }
void DecalGunshot(TraceResult* pTrace, int iBulletType) { return; }
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage) { return; }
void EjectBrass(const Vector& vecOrigin, const Vector& vecVelocity, float rotation, int model, int soundtype) { return; }
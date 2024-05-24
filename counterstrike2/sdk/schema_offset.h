#pragma once

#ifndef SCHEMAOFFSET
#define SCHEMAOFFSET

#include "sdk.hpp"

class xored_schema
{
public:
	struct alignas(16) utl_xor_hash
	{
		std::uint64_t key;
		char pad[0x8];
		std::uint64_t hash_key;
		char pad2[0x15];
		std::uint64_t xored;
		void* naebka;
		std::uint64_t xored_hash;
	};
	xored_schema() = default;
	xored_schema(const std::uint64_t offset)
	{
		map.key = get_hash<0x8936721837>(0x673521098);
		map.hash_key = get_hash<0x89732193213>(map.key);
		map.xored = offset ^ map.key;
		map.xored_hash = map.xored ^ get_hash(get_hash<0x4562321983721>(map.hash_key));
	}

	xored_schema(const std::uint64_t offset_, const std::uint64_t key_, const std::uint64_t hash_key_)
	{
		key = key_;
		hash_key = hash_key_;
		xored_key = offset_;
	}

	std::uint64_t get() {
		return xored_key ^ key ^ get_hash(hash_key ^ 0x4562321983721);
	}

	__forceinline operator size_t() {
		return get();
	}
private:
	template<std::uint64_t key = 0x9863217634217321>
	std::size_t constexpr get_hash(const std::size_t& value)
	{
		return std::integral_constant<uint64_t, key>::value^ value;
	}
public:
	utl_xor_hash map;
	std::uint64_t key;
	std::uint64_t hash_key;
	std::uint64_t xored_key;
};

class CSchemaOffset {
public:
	void init();
public:
	xored_schema m_flNextAttack;
	xored_schema m_hMyWeapons;
	xored_schema m_hActiveWeapon;
	xored_schema m_hViewModel;
	xored_schema m_hPlayerPing;
	xored_schema m_bForcedObserverMode;
	xored_schema m_iObserverLastMode;
	xored_schema m_hObserverTarget;
	xored_schema m_iObserverMode;
	xored_schema m_flSurfaceFriction;
	xored_schema m_flDuckAmount;
	xored_schema m_bOldJumpPressed;
	xored_schema m_flLeftMove;
	xored_schema m_flForwardMove;
	xored_schema m_flMaxspeed;
	xored_schema m_bHasHeavyArmor;
	xored_schema m_bHasHelmet;
	xored_schema m_bHasDefuser;
	xored_schema m_nPersonaDataPublicLevel;
	xored_schema m_PostProcessingVolumes;
	xored_schema m_hViewEntity;
	xored_schema m_flDeathCamTilt;
	xored_schema m_flLastShotFOV;
	xored_schema m_fOverrideFogEnd;
	xored_schema m_fOverrideFogStart;
	xored_schema m_bOverrideFogStartEnd;
	xored_schema m_OverrideFogColor;
	xored_schema m_bOverrideFogColor;
	xored_schema m_hOldFogController;
	xored_schema m_CurrentFog;
	xored_schema m_hTonemapController;
	xored_schema m_hZoomOwner;
	xored_schema m_iFOVStart;
	xored_schema m_iFOV;
	xored_schema m_hCtrl;
	xored_schema m_totalHitsOnServer;
	xored_schema m_bIsRescuing;
	xored_schema m_nNumBullets;
	xored_schema m_flRangeModifier;
	xored_schema m_flRange;
	xored_schema m_flPenetration;
	xored_schema m_flArmorRatio;
	xored_schema m_flHeadshotMultiplier;
	xored_schema m_nDamage;
	xored_schema m_nSpreadSeed;
	xored_schema m_nRecoilSeed;
	xored_schema m_flSpread;
	xored_schema m_flMaxSpeed;
	xored_schema m_bHasBurstMode;
	xored_schema m_szName;
	xored_schema m_bIsRevolver;
	xored_schema m_WeaponType;
	xored_schema m_flPostponeFireReadyFrac;
	xored_schema m_nPostponeFireReadyTicks;
	xored_schema m_iOriginalTeamNumber;
	xored_schema m_nFallbackPaintKit;
	xored_schema m_OriginalOwnerXuidHigh;
	xored_schema m_OriginalOwnerXuidLow;
	xored_schema m_seqFireSecondary;
	xored_schema m_seqFirePrimary;
	xored_schema m_seqIdle;
	xored_schema m_iRecoilIndex;
	xored_schema m_modelState;
	xored_schema m_hPlayer;
	xored_schema m_hBombDefuser;
	xored_schema m_bBombDefused;
	xored_schema m_flDefuseCountDown;
	xored_schema m_flDefuseLength;
	xored_schema m_flTimerLength;
	xored_schema m_flC4Blow;
	xored_schema m_nBombSite;
	xored_schema m_bBombTicking;
	xored_schema m_MeshGroupMask;
	xored_schema m_hModel;
	xored_schema m_pOwner;
	xored_schema m_pParent;
	xored_schema m_bDormant;
	xored_schema m_vecAbsOrigin;
	xored_schema m_vecOrigin;
	xored_schema m_iAccountID;
	xored_schema m_iItemIDHigh;
	xored_schema m_iItemIDLow;
	xored_schema m_iItemID;
	xored_schema m_iItemDefinitionIndex;
	xored_schema m_AttributeManager;
	xored_schema m_hWeapon;
	xored_schema m_iShotsFired;
	xored_schema m_flLastSmokeOverlayAlpha;
	xored_schema m_flFlashDuration;
	xored_schema m_hOriginalController;
	xored_schema m_aimPunchAngle;
	xored_schema m_bGunGameImmunity;
	xored_schema m_ArmorValue;
	xored_schema m_bIsWalking;
	xored_schema m_bIsScoped;
	xored_schema m_pViewModelServices;
	xored_schema m_pPingServices;
	xored_schema m_pActionTrackingServices;
	xored_schema m_aimPunchCache;
	xored_schema m_pBulletServices;
	xored_schema m_pInventoryServices;
	xored_schema m_sSanitizedPlayerName;
	xored_schema m_hObserverPawn;
	xored_schema m_hPlayerPawn;
	xored_schema m_usSolidFlags;
	xored_schema m_vecMaxs;
	xored_schema m_vecMins;
	xored_schema m_nAlpha;
	xored_schema m_iClip2;
	xored_schema m_iClip1;
	xored_schema m_flNextSecondaryAttackTickRatio;
	xored_schema m_nNextSecondaryAttackTick;
	xored_schema m_flNextPrimaryAttackTickRatio;
	xored_schema m_nNextPrimaryAttackTick;
	xored_schema m_pMovementServices;
	xored_schema m_pCameraServices;
	xored_schema m_pObserverServices;
	xored_schema m_pItemServices;
	xored_schema m_pWeaponServices;
	xored_schema m_iDesiredFOV;
	xored_schema m_nTickBase;
	xored_schema m_bIsLocalPlayerController;
	xored_schema m_steamID;
	xored_schema m_pClientAlphaProperty;
	xored_schema m_vecViewOffset;
	xored_schema m_nRenderFX;
	xored_schema m_hThrower;
	xored_schema m_flSimulationTime;
	xored_schema m_hGroundEntity;
	xored_schema m_hOwnerEntity;
	xored_schema m_pCollision;
	xored_schema m_pGameSceneNode;
	xored_schema m_nActualMoveType;
	xored_schema m_MoveType;
	xored_schema m_vecAbsVelocity;
	xored_schema m_vecVelocity;
	xored_schema m_flSpeed;
	xored_schema m_fFlags;
	xored_schema m_iTeamNum;
	xored_schema m_iEFlags;
	xored_schema m_lifeState;
	xored_schema m_iHealth;
	xored_schema m_flThrowStrength;
	xored_schema m_bThrowAnimating;
	xored_schema m_fDropTime;
	xored_schema m_bRedraw;
	xored_schema m_bJumpThrow;
	xored_schema m_bPinPulled;
	xored_schema m_eThrowStatus;
	xored_schema m_fThrowTime;
	xored_schema m_bSequenceFinished;
	xored_schema m_baseLayer;
	xored_schema m_flPrevCycleForAnimEventDetection;
	xored_schema m_flPrevCycleFromDiscontinuity;
	xored_schema m_bDiscontinuity;
	xored_schema m_bSequenceChangeNetworked;
	xored_schema m_flWeight;
	xored_schema m_flCycle;
	xored_schema m_flPrevCycle;
	xored_schema m_hSequence;
	xored_schema m_PlayerFog;
	xored_schema m_Item;
	xored_schema m_bWaitForNoAttack;
	xored_schema m_nSubclassID;
	xored_schema m_flThrowVelocity;
};

inline auto g_pSchemaOffset = std::make_unique<CSchemaOffset>();

#endif
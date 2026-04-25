// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cstdint>

namespace sculk::protocol::inline abi_v944 {

enum class ActorEvent : std::uint8_t {
    None                             = 0,
    Jump                             = 1,
    Hurt                             = 2,
    Death                            = 3,
    StartAttacking                   = 4,
    StopAttacking                    = 5,
    TamingFailed                     = 6,
    TamingSucceeded                  = 7,
    ShakeWetness                     = 8,
    EatGrass                         = 9,
    FishhookBubble                   = 10,
    FishhookFishpos                  = 11,
    FishhookHooktime                 = 12,
    FishhookTease                    = 13,
    SquidFleeing                     = 14,
    ZombieConverting                 = 15,
    PlayAmbient                      = 16,
    SpawnAlive                       = 17,
    StartOfferFlower                 = 18,
    StopOfferFlower                  = 19,
    LoveHearts                       = 20,
    VillagerAngry                    = 21,
    VillagerHappy                    = 22,
    WitchHatMagic                    = 23,
    FireworksExplode                 = 24,
    InLoveHearts                     = 25,
    SilverfishMergeAnim              = 26,
    GuardianAttackSound              = 27,
    DrinkPotion                      = 28,
    ThrowPotion                      = 29,
    PrimeTntcart                     = 30,
    PrimeCreeper                     = 31,
    AirSupply                        = 32,
    DeprecatedAddPlayerLevels        = 33,
    GuardianMiningFatigue            = 34,
    AgentSwingArm                    = 35,
    DragonStartDeathAnim             = 36,
    GroundDust                       = 37,
    Shake                            = 38,
    Feed                             = 39,
    BabyAge                          = 40,
    InstantDeath                     = 41,
    NotifyTrade                      = 42,
    LeashDestroyed                   = 43,
    CaravanUpdated                   = 44,
    TalismanActivate                 = 45,
    DeprecatedUpdateStructureFeature = 46,
    PlayerSpawnedMob                 = 47,
    Puke                             = 48,
    UpdateStackSize                  = 49,
    StartSwimming                    = 50,
    BalloonPop                       = 51,
    TreasureHunt                     = 52,
    SummonAgent                      = 53,
    FinishedChargingItem             = 54,
    ActorGrowUp                      = 55,
    VibrationDetected                = 56,
    DrinkMilk                        = 57,
    ShakeWetnessStop                 = 58,
    KineticDamageDealt               = 59,
};

} // namespace sculk::protocol::inline abi_v944

// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/item/ItemStackRequest.hpp"

namespace sculk::protocol::inline abi_v944 {

void ItemStackRequestSlotInfo::write(BinaryStream& stream) const {
    mFullContainerName.write(stream);
    stream.writeByte(mSlot);
    stream.writeVarInt(mNetId);
}

Result<> ItemStackRequestSlotInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mFullContainerName.read(stream); !status) return status;
    if (auto status = stream.readByte(mSlot); !status) return status;
    return stream.readVarInt(mNetId);
}

void ItemStackRequestAction::write(BinaryStream& stream) const {
    stream.writeEnum(mActionType, &BinaryStream::writeByte);
    std::visit(
        Overload{
            [&](const TransferBase& data) {
                stream.writeByte(data.mAmount);
                data.mSource.write(stream);
                data.mDestination.write(stream);
            },
            [&](const Swap& data) {
                data.mSource.write(stream);
                data.mDestination.write(stream);
            },
            [&](const Drop& data) {
                stream.writeByte(data.mAmount);
                data.mSource.write(stream);
                stream.writeBool(data.mRandomly);
            },
            [&](const DestroyConsume& data) {
                stream.writeByte(data.mAmount);
                data.mSource.write(stream);
            },
            [&](const Create& data) { stream.writeByte(data.mResultsIndex); },
            [&](const BeaconPayment& data) {
                stream.writeVarInt(data.mPrimaryEffectId);
                stream.writeVarInt(data.mSecondaryEffectId);
            },
            [&](const MineBlock& data) {
                stream.writeVarInt(data.mSlot);
                stream.writeVarInt(data.mPredictedDurability);
                if (data.mPreValidationStatus == MineBlock::PreValidationStatus::Valid && data.mItemStackNetId != 0) {
                    stream.writeVarInt(data.mItemStackNetId);
                }
            },
            [&](const CraftRecipe& data) {
                stream.writeUnsignedVarInt(data.mRecipeNetworkIdOrCreativeId);
                stream.writeUnsignedVarInt(data.mTimesCrafted);
            },
            [&](const CraftRecipeAuto& data) {
                stream.writeUnsignedVarInt(data.mRecipeNetworkId);
                stream.writeByte(data.mNumberOfRequestedCrafts);
                stream.writeByte(data.mTimesCrafted);
                stream.writeByte(static_cast<std::uint8_t>(data.mIngredients.size()));
                for (const RecipeIngredient& ingredient : data.mIngredients) {
                    ingredient.write(stream);
                }
            },
            [&](const CraftRecipeOptional& data) {
                stream.writeUnsignedVarInt(data.mRecipeNetId);
                stream.writeUnsignedInt(data.mFilteredStringIndex);
            },
            [&](const CraftGrindStone& data) {
                stream.writeUnsignedVarInt(data.mItemStackNetId);
                stream.writeByte(data.mTimesCrafted);
                stream.writeVarInt(data.mRepairCost);
            },
            [&](const CraftLoom& data) {
                stream.writeString(data.mPatternNameId);
                stream.writeByte(data.mTimesCrafted);
            },
            [&](const CraftResult& data) {
                stream.writeUnsignedVarInt(static_cast<std::uint32_t>(data.mCraftResults.size()));
                for (const NetworkItemInstanceDescriptor& result : data.mCraftResults) {
                    result.write(stream);
                }
                stream.writeByte(data.mTimesCrafted);
            },
            [&](const OnlyType&) {}
        },
        mVariant
    );
}

Result<> ItemStackRequestAction::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mActionType, &ReadOnlyBinaryStream::readByte); !status) return status;
    switch (mActionType) {
    case Type::Take:
    case Type::Place: {
        TransferBase data{};
        if (auto status = stream.readByte(data.mAmount); !status) return status;
        if (auto status = data.mSource.read(stream); !status) return status;
        if (auto status = data.mDestination.read(stream); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::Swap: {
        Swap data{};
        if (auto status = data.mSource.read(stream); !status) return status;
        if (auto status = data.mDestination.read(stream); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::Drop: {
        Drop data{};
        if (auto status = stream.readByte(data.mAmount); !status) return status;
        if (auto status = data.mSource.read(stream); !status) return status;
        if (auto status = stream.readBool(data.mRandomly); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::Destroy:
    case Type::Consume: {
        DestroyConsume data{};
        if (auto status = stream.readByte(data.mAmount); !status) return status;
        if (auto status = data.mSource.read(stream); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::Create: {
        Create data{};
        if (auto status = stream.readByte(data.mResultsIndex); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::BeaconPayment: {
        BeaconPayment data{};
        if (auto status = stream.readVarInt(data.mPrimaryEffectId); !status) return status;
        if (auto status = stream.readVarInt(data.mSecondaryEffectId); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::MineBlock: {
        MineBlock data{};
        if (auto status = stream.readVarInt(data.mSlot); !status) return status;
        if (auto status = stream.readVarInt(data.mPredictedDurability); !status) return status;
        if (auto status = stream.readVarInt(data.mItemStackNetId); !status) return status;
        data.mPreValidationStatus =
            data.mItemStackNetId == 0 ? MineBlock::PreValidationStatus::Invalid : MineBlock::PreValidationStatus::Valid;
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftRecipe:
    case Type::CraftCreative: {
        CraftRecipe data{};
        if (auto status = stream.readUnsignedVarInt(data.mRecipeNetworkIdOrCreativeId); !status) return status;
        if (auto status = stream.readUnsignedVarInt(data.mTimesCrafted); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftRecipeAuto: {
        CraftRecipeAuto data{};
        if (auto status = stream.readUnsignedVarInt(data.mRecipeNetworkId); !status) return status;
        if (auto status = stream.readByte(data.mNumberOfRequestedCrafts); !status) return status;
        if (auto status = stream.readByte(data.mTimesCrafted); !status) return status;
        std::uint8_t ingredientCount{};
        if (auto status = stream.readByte(ingredientCount); !status) return status;
        data.mIngredients.resize(ingredientCount);
        for (RecipeIngredient& ingredient : data.mIngredients) {
            if (auto status = ingredient.read(stream); !status) return status;
        }
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftRecipeOptional: {
        CraftRecipeOptional data{};
        if (auto status = stream.readUnsignedVarInt(data.mRecipeNetId); !status) return status;
        if (auto status = stream.readUnsignedInt(data.mFilteredStringIndex); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftGrindStone: {
        CraftGrindStone data{};
        if (auto status = stream.readUnsignedVarInt(data.mItemStackNetId); !status) return status;
        if (auto status = stream.readByte(data.mTimesCrafted); !status) return status;
        if (auto status = stream.readVarInt(data.mRepairCost); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftLoom: {
        CraftLoom data{};
        if (auto status = stream.readString(data.mPatternNameId); !status) return status;
        if (auto status = stream.readByte(data.mTimesCrafted); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    case Type::CraftResults: {
        CraftResult   data{};
        std::uint32_t resultCount{};
        if (auto status = stream.readUnsignedVarInt(resultCount); !status) return status;
        data.mCraftResults.resize(resultCount);
        for (NetworkItemInstanceDescriptor& result : data.mCraftResults) {
            if (auto status = result.read(stream); !status) return status;
        }
        if (auto status = stream.readByte(data.mTimesCrafted); !status) return status;
        mVariant = std::move(data);
        return {};
    }
    default:
        mVariant = OnlyType{};
        return {};
    }
}

void ItemStackRequestData::write(BinaryStream& stream) const {
    stream.writeVarInt(mClientRequestId);
    stream.writeArray(mActions, &ItemStackRequestAction::write);
    stream.writeArray(mStringsToFilter, &BinaryStream::writeString);
    stream.writeSignedInt(mStringsToFilterOrigin);
}

Result<> ItemStackRequestData::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mClientRequestId); !status) return status;
    if (auto status = stream.readArray(mActions, &ItemStackRequestAction::read); !status) return status;
    if (auto status = stream.readArray(mStringsToFilter, &ReadOnlyBinaryStream::readString); !status) return status;
    return stream.readSignedInt(mStringsToFilterOrigin);
}

void ItemStackRequest::write(BinaryStream& stream) const { stream.writeArray(mRequests, &ItemStackRequestData::write); }

Result<> ItemStackRequest::read(ReadOnlyBinaryStream& stream) {
    return stream.readArray(mRequests, &ItemStackRequestData::read);
}

} // namespace sculk::protocol::inline abi_v944

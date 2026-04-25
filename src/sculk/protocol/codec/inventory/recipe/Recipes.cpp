// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/recipe/Recipes.hpp"

namespace sculk::protocol::inline abi_v944 {

void RecipeUnlockingRequirement::write(BinaryStream& stream) const {
    stream.writeEnum(mUnlockingContext, &BinaryStream::writeByte);
    if (mUnlockingContext == UnlockingContext::None) {
        stream.writeArray(mUnlockingIngredients, &RecipeIngredient::write);
    }
}

Result<> RecipeUnlockingRequirement::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readEnum(mUnlockingContext, &ReadOnlyBinaryStream::readByte); !status) return status;
    if (mUnlockingContext == UnlockingContext::None) {
        return stream.readArray(mUnlockingIngredients, &RecipeIngredient::read);
    }
    return {};
}

void ShapelessRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    stream.writeArray(mIngredientList, &RecipeIngredient::write);
    stream.writeArray(mProductionList, &NetworkItemInstanceDescriptor::write);
    mRecipeId.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeVarInt(mPriority);
    mUnlockingRequirement.write(stream);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> ShapelessRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = stream.readArray(mIngredientList, &RecipeIngredient::read); !status) return status;
    if (auto status = stream.readArray(mProductionList, &NetworkItemInstanceDescriptor::read); !status) return status;
    if (auto status = mRecipeId.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    if (auto status = stream.readVarInt(mPriority); !status) return status;
    if (auto status = mUnlockingRequirement.read(stream); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void ShapedRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    stream.writeVarInt(mGridWidth);
    stream.writeVarInt(mGridHeight);
    for (const RecipeIngredient& ingredient : mIngredientList) {
        ingredient.write(stream);
    }
    stream.writeArray(mProductionList, &NetworkItemInstanceDescriptor::write);
    mRecipeId.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeVarInt(mPriority);
    stream.writeBool(mAssumeSymmetry);
    mUnlockingRequirement.write(stream);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> ShapedRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = stream.readVarInt(mGridWidth); !status) return status;
    if (auto status = stream.readVarInt(mGridHeight); !status) return status;
    mIngredientList.resize(static_cast<std::size_t>(mGridWidth * mGridHeight));
    for (RecipeIngredient& ingredient : mIngredientList) {
        if (auto status = ingredient.read(stream); !status) return status;
    }
    if (auto status = stream.readArray(mProductionList, &NetworkItemInstanceDescriptor::read); !status) return status;
    if (auto status = mRecipeId.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    if (auto status = stream.readVarInt(mPriority); !status) return status;
    if (auto status = stream.readBool(mAssumeSymmetry); !status) return status;
    if (auto status = mUnlockingRequirement.read(stream); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void FurnaceRecipe::write(BinaryStream& stream) const {
    stream.writeVarInt(mItemData);
    mResultItem.write(stream);
    stream.writeString(mRecipeTag);
}

Result<> FurnaceRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mItemData); !status) return status;
    if (auto status = mResultItem.read(stream); !status) return status;
    return stream.readString(mRecipeTag);
}

void FurnaceAuxRecipe::write(BinaryStream& stream) const {
    stream.writeVarInt(mItemData);
    stream.writeVarInt(mAux);
    mResultItem.write(stream);
    stream.writeString(mRecipeTag);
}

Result<> FurnaceAuxRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mItemData); !status) return status;
    if (auto status = stream.readVarInt(mAux); !status) return status;
    if (auto status = mResultItem.read(stream); !status) return status;
    return stream.readString(mRecipeTag);
}

void MultiRecipe::write(BinaryStream& stream) const {
    mMultiRecipe.write(stream);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> MultiRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = mMultiRecipe.read(stream); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void UserDataShapelessRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    stream.writeArray(mIngredientList, &RecipeIngredient::write);
    stream.writeArray(mProductionList, &NetworkItemInstanceDescriptor::write);
    mRecipeId.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeVarInt(mPriority);
    mUnlockingRequirement.write(stream);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> UserDataShapelessRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = stream.readArray(mIngredientList, &RecipeIngredient::read); !status) return status;
    if (auto status = stream.readArray(mProductionList, &NetworkItemInstanceDescriptor::read); !status) return status;
    if (auto status = mRecipeId.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    if (auto status = stream.readVarInt(mPriority); !status) return status;
    if (auto status = mUnlockingRequirement.read(stream); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void ShapelessChemistryRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    stream.writeArray(mIngredientList, &RecipeIngredient::write);
    stream.writeArray(mProductionList, &NetworkItemInstanceDescriptor::write);
    mRecipeId.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeVarInt(mPriority);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> ShapelessChemistryRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = stream.readArray(mIngredientList, &RecipeIngredient::read); !status) return status;
    if (auto status = stream.readArray(mProductionList, &NetworkItemInstanceDescriptor::read); !status) return status;
    if (auto status = mRecipeId.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    if (auto status = stream.readVarInt(mPriority); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void ShapedChemistryRecipe::write(BinaryStream& stream) const { mChemistryRecipe.write(stream); }

Result<> ShapedChemistryRecipe::read(ReadOnlyBinaryStream& stream) { return mChemistryRecipe.read(stream); }

void SmithingTransformRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    mTemplate.write(stream);
    mBase.write(stream);
    mAddition.write(stream);
    mResult.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> SmithingTransformRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = mTemplate.read(stream); !status) return status;
    if (auto status = mBase.read(stream); !status) return status;
    if (auto status = mAddition.read(stream); !status) return status;
    if (auto status = mResult.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void SmithingTrimRecipe::write(BinaryStream& stream) const {
    stream.writeString(mRecipeUniqueId);
    mTemplate.write(stream);
    mBase.write(stream);
    mAddition.write(stream);
    stream.writeString(mRecipeTag);
    stream.writeUnsignedVarInt(mNetId);
}

Result<> SmithingTrimRecipe::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mRecipeUniqueId); !status) return status;
    if (auto status = mTemplate.read(stream); !status) return status;
    if (auto status = mBase.read(stream); !status) return status;
    if (auto status = mAddition.read(stream); !status) return status;
    if (auto status = stream.readString(mRecipeTag); !status) return status;
    return stream.readUnsignedVarInt(mNetId);
}

void CraftingDataEntry::write(BinaryStream& stream) const {
    stream.writeVariantIndex<std::int32_t>(mRecipe, &BinaryStream::writeVarInt);
    std::visit([&](auto&& recipe) { recipe.write(stream); }, mRecipe);
}

Result<> CraftingDataEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVariantIndex<std::int32_t>(mRecipe, &ReadOnlyBinaryStream::readVarInt); !status)
        return status;
    return std::visit([&](auto&& recipe) { return recipe.read(stream); }, mRecipe);
}

void PotionMixDataEntry::write(BinaryStream& stream) const {
    stream.writeVarInt(mFromPotionId);
    stream.writeVarInt(mFromPotionAux);
    stream.writeVarInt(mReagentItemId);
    stream.writeVarInt(mReagentItemAux);
    stream.writeVarInt(mToPotionId);
    stream.writeVarInt(mToPotionAux);
}

Result<> PotionMixDataEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mFromPotionId); !status) return status;
    if (auto status = stream.readVarInt(mFromPotionAux); !status) return status;
    if (auto status = stream.readVarInt(mReagentItemId); !status) return status;
    if (auto status = stream.readVarInt(mReagentItemAux); !status) return status;
    if (auto status = stream.readVarInt(mToPotionId); !status) return status;
    return stream.readVarInt(mToPotionAux);
}

void ContainerMixDataEntry::write(BinaryStream& stream) const {
    stream.writeVarInt(mInputItemId);
    stream.writeVarInt(mReagentItemId);
    stream.writeVarInt(mToItemId);
}

Result<> ContainerMixDataEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mInputItemId); !status) return status;
    if (auto status = stream.readVarInt(mReagentItemId); !status) return status;
    return stream.readVarInt(mToItemId);
}

void MaterialReducerDataEntry::ItemInfo::write(BinaryStream& stream) const {
    stream.writeVarInt(mItemId);
    stream.writeVarInt(mItemCount);
}

Result<> MaterialReducerDataEntry::ItemInfo::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mItemId); !status) return status;
    return stream.readVarInt(mItemCount);
}

void MaterialReducerDataEntry::write(BinaryStream& stream) const {
    stream.writeVarInt(mInput);
    stream.writeArray(mItems, &ItemInfo::write);
}

Result<> MaterialReducerDataEntry::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readVarInt(mInput); !status) return status;
    return stream.readArray(mItems, &ItemInfo::read);
}

} // namespace sculk::protocol::inline abi_v944

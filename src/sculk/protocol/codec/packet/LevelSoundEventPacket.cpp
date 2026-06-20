// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/LevelSoundEventPacket.hpp"
#include <cctype>
#include <magic_enum/magic_enum.hpp>
#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
#include "../utility/Format.hpp"
#endif

namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE {

namespace {

std::string serializeLevelSoundImpl(LevelSoundEvent event) {
    auto        rawName = magic_enum::enum_name(event);
    std::string serializedName{};
    serializedName.reserve(rawName.size());

    // Convert to lower case and map double underscore to dot.
    for (size_t i = 0; i < rawName.size(); ++i) {
        char ch = static_cast<char>(std::tolower(static_cast<std::uint8_t>(rawName[i])));
        if (ch == '_' && i + 1 < rawName.size() && rawName[i + 1] == '_') {
            serializedName.push_back('.');
            ++i;
            continue;
        }
        serializedName.push_back(ch);
    }

    return serializedName;
}

std::optional<LevelSoundEvent> deserializeLevelSoundImpl(std::string_view name) {
    std::string enumName{};
    enumName.reserve(name.size() * 2);

    // Map dot back to double underscore; keep single underscore unchanged.
    for (char ch : name) {
        if (ch == '.') {
            enumName += "__";
        } else {
            enumName.push_back(ch);
        }
    }

    return magic_enum::enum_cast<LevelSoundEvent>(enumName, magic_enum::case_insensitive);
}

std::string serializeLevelSound(std::variant<LevelSoundEvent, std::string> const& event) {
    return std::visit(
        Overload{
            [](LevelSoundEvent event) { return serializeLevelSoundImpl(event); },
            [](std::string const& str) { return str; }
        },
        event
    );
}

std::variant<LevelSoundEvent, std::string> deserializeLevelSound(std::string_view name) {
    if (auto eventOpt = deserializeLevelSoundImpl(name)) {
        return *eventOpt;
    }
    return std::string(name);
}

} // namespace

MinecraftPacketIds LevelSoundEventPacket::getId() const noexcept { return MinecraftPacketIds::LevelSoundEvent; }

std::string_view LevelSoundEventPacket::getName() const noexcept { return "LevelSoundEventPacket"; }

void LevelSoundEventPacket::write(BinaryStream& stream) const {
    stream.writeString(serializeLevelSound(mSoundEvent));
    mPosition.write(stream);
    stream.writeVarInt(mData);
    stream.writeString(mActorIdentifier);
    stream.writeBool(mIsBabyMob);
    stream.writeBool(mIsGlobal);
    stream.writeSignedInt64(mActorUniqueId);
    stream.writeOptional(mFireAtPosition, &Vec3::write);
}

Result<> LevelSoundEventPacket::read(ReadOnlyBinaryStream& stream) {
    std::string soundEventName{};
    _SCULK_READ(stream.readString(soundEventName));
    mSoundEvent = deserializeLevelSound(soundEventName);
    _SCULK_READ(mPosition.read(stream));
    _SCULK_READ(stream.readVarInt(mData));
    _SCULK_READ(stream.readString(mActorIdentifier));
    _SCULK_READ(stream.readBool(mIsBabyMob));
    _SCULK_READ(stream.readBool(mIsGlobal));
    _SCULK_READ(stream.readSignedInt64(mActorUniqueId));
    return stream.readOptional(mFireAtPosition, &Vec3::read);
}

#ifdef SCULK_PROTOCOL_ENABLE_FORMATTING
std::string LevelSoundEventPacket::toString() const {
    return SCULK_FORMAT_PACKET(
        SCULK_FORMAT_FIELD(mSoundEvent),
        SCULK_FORMAT_FIELD(mPosition),
        SCULK_FORMAT_FIELD(mData),
        SCULK_FORMAT_FIELD(mActorIdentifier),
        SCULK_FORMAT_FIELD(mIsBabyMob),
        SCULK_FORMAT_FIELD(mIsGlobal),
        SCULK_FORMAT_FIELD(mFireAtPosition)
    );
}
#endif

} // namespace sculk::protocol::SCULK_ABI_INLINE_NAMESPACE

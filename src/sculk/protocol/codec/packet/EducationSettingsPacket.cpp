// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/EducationSettingsPacket.hpp"

namespace sculk::protocol::inline abi_v944 {

void EducationSettingsPacket::AgentCapabilities::write(BinaryStream& stream) const {
    stream.writeOptional(mCanModifyBlocks, &BinaryStream::writeBool);
}

Result<> EducationSettingsPacket::AgentCapabilities::read(ReadOnlyBinaryStream& stream) {
    return stream.readOptional(mCanModifyBlocks, &ReadOnlyBinaryStream::readBool);
}

void EducationSettingsPacket::ExternalLinkSettings::write(BinaryStream& stream) const {
    stream.writeString(mUrl);
    stream.writeString(mDisplayName);
}

Result<> EducationSettingsPacket::ExternalLinkSettings::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mUrl); !status) return status;
    return stream.readString(mDisplayName);
}

MinecraftPacketIds EducationSettingsPacket::getId() const noexcept { return MinecraftPacketIds::EducationSettings; }

std::string_view EducationSettingsPacket::getName() const noexcept { return "EducationSettingsPacket"; }

void EducationSettingsPacket::write(BinaryStream& stream) const {
    stream.writeString(mCodeBuilderDefaultUrl);
    stream.writeString(mCodeBuilderTitle);
    stream.writeBool(mCanResizeCodeBuilder);
    stream.writeBool(mDisableLegacyTitleBar);
    stream.writeString(mPostProcessFilter);
    stream.writeString(mScreenshotBorderResourcePath);
    stream.writeOptional(mAgentCapabilities, &AgentCapabilities::write);
    stream.writeOptional(mCodeBuilderOverrideUrl, &BinaryStream::writeString);
    stream.writeBool(mAlwaysFalse);
    stream.writeOptional(mExternalLinkSettings, &ExternalLinkSettings::write);
}

Result<> EducationSettingsPacket::read(ReadOnlyBinaryStream& stream) {
    if (auto status = stream.readString(mCodeBuilderDefaultUrl); !status) return status;
    if (auto status = stream.readString(mCodeBuilderTitle); !status) return status;
    if (auto status = stream.readBool(mCanResizeCodeBuilder); !status) return status;
    if (auto status = stream.readBool(mDisableLegacyTitleBar); !status) return status;
    if (auto status = stream.readString(mPostProcessFilter); !status) return status;
    if (auto status = stream.readString(mScreenshotBorderResourcePath); !status) return status;
    if (auto status = stream.readOptional(mAgentCapabilities, &AgentCapabilities::read); !status) return status;
    if (auto status = stream.readOptional(mCodeBuilderOverrideUrl, &ReadOnlyBinaryStream::readString); !status)
        return status;
    if (auto status = stream.readBool(mAlwaysFalse); !status) return status;
    return stream.readOptional(mExternalLinkSettings, &ExternalLinkSettings::read);
}

} // namespace sculk::protocol::inline abi_v944

/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "SystemFontDatabase.h"

namespace WebCore {

SystemFontDatabase::SystemFontDatabase() = default;

auto SystemFontDatabase::systemFontShorthandInfo(FontShorthand fontShorthand) -> const SystemFontShorthandInfo& {
    auto index = static_cast<FontShorthandUnderlyingType>(fontShorthand);
    if (auto& entry = m_systemFontShorthandCache[index])
        return *entry;

    m_systemFontShorthandCache[index] = platformSystemFontShorthandInfo(fontShorthand);
    return *m_systemFontShorthandCache[index];
}

const AtomString& SystemFontDatabase::systemFontShorthandFamily(FontShorthand fontShorthand)
{
    return systemFontShorthandInfo(fontShorthand).family;
}

float SystemFontDatabase::systemFontShorthandSize(FontShorthand fontShorthand)
{
    return systemFontShorthandInfo(fontShorthand).size;
}

FontSelectionValue SystemFontDatabase::systemFontShorthandWeight(FontShorthand fontShorthand)
{
    return systemFontShorthandInfo(fontShorthand).weight;
}

void SystemFontDatabase::clear()
{
    for (auto& item : m_systemFontShorthandCache)
        item.reset();
}

} // namespace WebCore

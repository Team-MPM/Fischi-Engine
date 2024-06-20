#pragma once

#include <locale>
#include <codecvt>
#include <string>

namespace Utils {
    std::string ToUTF8(const std::wstring& input) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);
    }
}
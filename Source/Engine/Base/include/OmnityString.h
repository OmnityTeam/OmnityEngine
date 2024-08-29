#pragma once
#pragma warning(disable:4514)
#include <string>

namespace Omnity {
    using Utf8String = std::string;
    using Utf16String = std::u16string;
    using Utf32String = std::u32string;
    class String;
	namespace StringUtils {
        Utf16String FromUtf8Ptr(const char8_t* str);
        Utf16String FromUtf8Ptr(const char* str, size_t len);
        inline Utf16String FromUtf8Ptr(const char* str) {
            return FromUtf8Ptr(str, strlen(str));
        }
        Utf16String FromUtf32Ptr(const char32_t* str);
        inline Utf16String FromWidePtr(const wchar_t* str) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return Utf16String(reinterpret_cast<const char16_t*>(str));
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return FromUtf32Ptr(reinterpret_cast<const char32_t*>(str));
        }
        Utf16String FromUtf8(const Utf8String& str);
        Utf8String ToUtf8(const Utf16String& str);
	}
    class String {
        Utf16String _data;
    public:
        inline String() : _data() {}
        inline String(size_t len, char16_t ch) : _data(len, ch) {}
        inline String(const char16_t* str) : _data(str) {}
        inline String(const char32_t* str) : _data(StringUtils::FromUtf32Ptr(str)) {}
        inline String(const wchar_t* str) : _data(StringUtils::FromWidePtr(str)) {}
        inline String(const char* str) : _data(StringUtils::FromUtf8Ptr(str)) {}

        inline const wchar_t* GetCStr() const {
            return reinterpret_cast<const wchar_t*>(_data.c_str());
        }
        inline size_t Length() const {
            return _data.length();
        }
    };
}
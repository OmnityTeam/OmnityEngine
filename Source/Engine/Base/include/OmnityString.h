#pragma once
#include <string>
#include <memory>
#include <concepts>
#include <variant>
#include <stdexcept>

namespace Omnity {
    using Utf8String = std::string;
    using Utf16String = std::u16string;
    using Utf32String = std::u32string;
    using Char = char16_t;
    class String;
    class StringRef;
	namespace StringUtils {
        Utf16String FromUtf8Ptr(const char8_t* str, size_t len);
        inline Utf16String FromUtf8Ptr(const char8_t* str) {
            return FromUtf8Ptr(str, std::char_traits<char8_t>::length(str));
        }
        Utf16String FromUtf32Ptr(const char32_t* str, size_t len);

        inline Utf16String FromUtf8Ptr(const char* str, size_t len) {
            return FromUtf8Ptr(reinterpret_cast<const char8_t*>(str), len);
        }
        inline Utf16String FromUtf8Ptr(const char* str) {
            return FromUtf8Ptr(reinterpret_cast<const char8_t*>(str));
        }
        inline Utf16String FromWidePtr(const wchar_t* str, size_t len) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return Utf16String(reinterpret_cast<const char16_t*>(str));
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return FromUtf32Ptr(reinterpret_cast<const char32_t*>(str), len);
        }
        inline Utf16String FromWidePtr(const wchar_t* str) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return Utf16String(reinterpret_cast<const char16_t*>(str));
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return FromUtf32Ptr(reinterpret_cast<const char32_t*>(str), std::char_traits<wchar_t>::length(str));
        }
        Utf16String FromUtf8(const Utf8String& str);
        Utf8String ToUtf8(const Utf16String& str);
	}
    template <typename TChar16Iterator>
    struct WordIterator {
        WordIterator(TChar16Iterator strBeg, TChar16Iterator strEnd) :
            _strIter(strBeg), _strEnd(strEnd) {}
        const char32_t operator*() const;
        WordIterator& operator++();
        bool operator==(const WordIterator& b) const {
            return _strIter == b._strIter && _strEnd == b._strEnd;
        }
    private:
        TChar16Iterator _strIter;
        TChar16Iterator _strEnd;
    };
    class String : public std::basic_string<Char> {
    public:
        template<typename... TArgs>
        inline String(TArgs... args) : std::basic_string<Char>(args...) {}
        inline String(const char* ptr, size_t len) : std::basic_string<Char>(StringUtils::FromUtf8Ptr(ptr, len)) {}
        inline String(const wchar_t* ptr, size_t len) : std::basic_string<Char>(StringUtils::FromWidePtr(ptr, len)) {}
        inline String(const char32_t* ptr, size_t len) : std::basic_string<Char>(StringUtils::FromUtf32Ptr(ptr, len)) {}
        template<typename TBaseChar>
        inline String(const TBaseChar* ptr) : String(ptr, std::char_traits<TBaseChar>::length(ptr)) {}
        inline String(const String& str) : std::basic_string<Char>(str) {}
        inline String(String&& str) noexcept : std::basic_string<Char>(std::forward<std::basic_string<Char>>(str)) {}

        const WordIterator<String::iterator> WordBegin() {
            return WordIterator<String::iterator>(begin(), end());
        }
        const WordIterator<String::iterator> WordEnd() {
            return WordIterator<String::iterator>(end(), end());
        }
        inline StringRef substr(size_t off, size_t len);
    };
    class StringRef : public std::basic_string_view<Char> {
    public:
        inline StringRef(const String& str) : std::basic_string_view<Char>(str.data(), str.length()) {}
        inline StringRef(const Char* ptr) : std::basic_string_view<Char>(ptr, std::char_traits<Char>::length(ptr)) {}
        inline StringRef(const Char* ptr, size_t len) : std::basic_string_view<Char>(ptr, len) {}
        const WordIterator<StringRef::iterator> WordBegin() {
            return WordIterator<StringRef::iterator>(begin(), end());
        }
        const WordIterator<StringRef::iterator> WordEnd() {
            return WordIterator<StringRef::iterator>(end(), end());
        }
    };
    inline StringRef String::substr(size_t off, size_t len) {
        return StringRef(this->data() + off, len);
    }
}
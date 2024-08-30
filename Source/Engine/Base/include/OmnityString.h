#pragma once
#include <string>
#include <memory>
#include <concepts>

namespace Omnity {
    using Utf8String = std::string;
    using Utf16String = std::u16string;
    using Utf32String = std::u32string;
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
    class DynamicString {
        Utf16String _data;
    public:
        inline DynamicString() {}
        inline DynamicString(const char16_t* ptr, size_t len) : _data(ptr, len) {}
        inline DynamicString(const char16_t* ptr) : _data(ptr) {}
        inline DynamicString(const char* ptr) : _data(StringUtils::FromUtf8Ptr(ptr)) {}
        inline DynamicString(const wchar_t* ptr) : _data(StringUtils::FromWidePtr(ptr)) {}
        inline const char16_t* CStr() const noexcept {
            return _data.c_str();
        }
        inline size_t Length() const noexcept {
            return _data.length();
        }
    };
    class ImmutableString {
    protected:
        std::u16string_view _view;
    public:
        inline ImmutableString() : ImmutableString(nullptr, 0) {};
        inline ImmutableString(const char16_t* ptr, size_t len) : _view(ptr, len) {}
        inline ImmutableString(const char16_t* ptr) : ImmutableString(ptr, std::char_traits<char16_t>::length(ptr)) {}
        inline const char16_t* Ptr() const noexcept {
            return _view.data();
        }
        inline size_t Length() const noexcept {
            return _view.length();
        }
        inline DynamicString ToDynamic() {
            return DynamicString(Ptr(), Length());
        }
        virtual ~ImmutableString() {}
    };
    class String : public ImmutableString {
        std::shared_ptr<DynamicString> _ref;
        String() {}
    public:
        String(String& str) noexcept {
            _ref = str._ref;
        }
        String(String&& str) noexcept {
            _ref = std::move(str._ref);
            str._ref = nullptr;
        }
        template<typename... Args>
        inline String(Args... args) {
            _ref = std::make_shared<DynamicString>(args...);
            _view = std::u16string_view(_ref->CStr(), _ref->Length());
        }
        template<typename... Args>
        String(const DynamicString& str, Args... args) {
            _ref = std::make_shared<DynamicString>(args...);
            _view = std::u16string_view(_ref->CStr(), _ref->Length());
        }
        template<typename... Args>
        String(const DynamicString&& str, Args... args) {
            _ref = std::make_shared<DynamicString>(args...);
            _view = std::u16string_view(_ref->CStr(), _ref->Length());
        }
        ~String();
        inline String SubString(size_t startPos, size_t length) {
            String str;
            str._ref = _ref;
            str._view = _view.substr(startPos, length);
            return str;
        }
    };
}
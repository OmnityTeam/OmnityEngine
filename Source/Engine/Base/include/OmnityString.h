#pragma once
#include <string>
#include <memory>
#include <concepts>
#include <variant>

namespace Omnity {
    using Utf8String = std::string;
    using Utf16String = std::u16string;
    using Utf32String = std::u32string;
    using Char = char16_t;
    class String;
    class StringRef;
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
    class SharedStringContainer : public std::basic_string<Char>, std::enable_shared_from_this<SharedStringContainer>
    {
    public:
        friend class StringRef;
        friend class StringRef;
        using Ptr = std::shared_ptr<SharedStringContainer>;
        using WeakPtr = std::shared_ptr<SharedStringContainer>;
        SharedStringContainer(const SharedStringContainer& str) = delete;
        SharedStringContainer(const SharedStringContainer&& str) = delete;
        SharedStringContainer& operator=(SharedStringContainer&) = delete;
        SharedStringContainer(const char16_t* ptr, size_t len) noexcept : std::basic_string<Char>(ptr, len) {}
        SharedStringContainer(const char* ptr, size_t len) noexcept : std::basic_string<Char>(StringUtils::FromUtf8Ptr(ptr, len)) {}
    };
    class String {
        SharedStringContainer::Ptr _container;
        inline String(SharedStringContainer::Ptr container) : _container(container) {}
    public:
        friend class StringRef;
        friend class StringRef;
        inline String(const String& str) : _container(std::make_shared<SharedStringContainer>(str._container->c_str(), str._container->length())) {}
        inline String(String&& str) noexcept : _container(std::move(str._container)) {}
        template <typename TBaseChar>
        inline String(const TBaseChar* ptr, size_t len) noexcept : _container(std::make_shared<SharedStringContainer>(ptr, len)) {}
        template <typename TBaseChar>
        inline String(const TBaseChar* ptr) noexcept : _container(std::make_shared<SharedStringContainer>(ptr, std::char_traits<TBaseChar>::length(ptr))) {}
        inline Char* operator[](size_t i) noexcept {
            return &_container->at(i);
        }
        inline const Char* operator[](size_t i) const noexcept {
            return &_container->at(i);
        }
        inline StringRef SubString(size_t offset, size_t len) const noexcept;
        inline size_t Length() const noexcept {
            return _container->length();
        }
        inline const char16_t* CStr() const noexcept {
            return _container->c_str();
        }
        inline ~String();
    };

    class ScopedString {
        std::basic_string<Char> _data;
    public:
        ScopedString(const char16_t* ptr, size_t len) noexcept : _data(ptr, len) {}
        ScopedString(const char* ptr, size_t len) noexcept : _data(StringUtils::FromUtf8Ptr(ptr, len)) {}
        template <typename TBaseChar>
        ScopedString(const TBaseChar* ptr) noexcept : ScopedString(ptr, std::char_traits<TBaseChar>::length(ptr)) {}
    };

    class StringRef {
        String _sharedStr;
        size_t _len;
        size_t _offset;
    public:
        template <typename TBaseChar>
        inline StringRef(const TBaseChar* ptr, size_t len) noexcept : _sharedStr(ptr, len), _offset(0), _len(len) {}
        template <typename TBaseChar>
        inline StringRef(const TBaseChar* ptr) noexcept : StringRef(ptr, std::char_traits<TBaseChar>::length(ptr)) {}
        inline StringRef(StringRef&& strRef) noexcept
            : _sharedStr(std::move(strRef._sharedStr)), _offset(strRef._offset), _len(strRef._len) {}
        inline StringRef(const StringRef& strRef)
            : _sharedStr(strRef._sharedStr._container), _offset(strRef._offset), _len(strRef._len) {}
        inline StringRef(const String& str, size_t offset, size_t len)
            : _sharedStr(str._container), _offset(offset), _len(len) {}
        inline StringRef(const String& str)
            : StringRef(str, 0, str.Length()) {}
        inline const Char* operator[](size_t i) const noexcept {
            return _sharedStr[i + _offset];
        }
        inline const String AsString() const {
            if (_sharedStr.Length() == _len && _offset == 0)
                return _sharedStr;
            return String(_sharedStr[_offset], _len);
        }
        inline ~StringRef();
    };
    inline StringRef::~StringRef() = default;
    inline String::~String() = default;
    inline StringRef String::SubString(size_t offset, size_t len) const noexcept {
        return StringRef(*this, offset, len);
    }
    inline StringRef operator ""_s(const char16_t* ptr, size_t len) noexcept {
        return String(ptr, len);
    }
}
#pragma once
#include <string>
#include <memory>
#include <concepts>
#include <variant>
#include <stdexcept>
#include <fmt/xchar.h>

namespace Omnity {
	namespace StringUtils {
        std::u16string FromUtf8Ptr(const char8_t* str, size_t len);
        inline std::u16string FromUtf8Ptr(const char8_t* str) {
            return FromUtf8Ptr(str, std::char_traits<char8_t>::length(str));
        }
        std::u16string FromUtf32Ptr(const char32_t* str, size_t len);

        inline std::u16string FromUtf8Ptr(const char* str, size_t len) {
            return FromUtf8Ptr(reinterpret_cast<const char8_t*>(str), len);
        }
        inline std::u16string FromUtf8Ptr(const char* str) {
            return FromUtf8Ptr(reinterpret_cast<const char8_t*>(str));
        }
        inline std::u16string FromWidePtr(const wchar_t* str, size_t len) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return std::u16string(reinterpret_cast<const char16_t*>(str));
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return FromUtf32Ptr(reinterpret_cast<const char32_t*>(str), len);
        }
        inline std::u16string FromWidePtr(const wchar_t* str) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return std::u16string(reinterpret_cast<const char16_t*>(str));
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return FromUtf32Ptr(reinterpret_cast<const char32_t*>(str), std::char_traits<wchar_t>::length(str));
        }
        std::u16string FromUtf8(const std::string& str);
        std::string ToUtf8(const std::u16string& str);
        char32_t NextChar(std::u16string_view::const_iterator& iter, std::u16string_view::const_iterator end);
        char32_t NextChar(std::u16string::const_iterator& iter, std::u16string::const_iterator end);
	}
    template <typename TChar16Iterator>
    class WordIterator{
        TChar16Iterator _strIter;
        TChar16Iterator _strEnd;
    public:
        WordIterator(TChar16Iterator strBeg, TChar16Iterator strEnd) :
            _strIter(strBeg), _strEnd(strEnd) {}
        WordIterator<TChar16Iterator>& operator++() {
            StringUtils::NextChar(_strIter, _strEnd);
            return *this;
        }
        char32_t operator*() const {
            if (_strIter == _strEnd)
                throw std::out_of_range{
                  "Parties can only have 3 players" };
            auto copyIter = _strIter;
            return StringUtils::NextChar(copyIter, _strEnd);
        }
        bool operator==(const WordIterator& b) const {
            return _strIter == b._strIter && _strEnd == b._strEnd;
        }
    };

    class Words {
        std::u16string_view _view;
    public:
        inline Words(std::u16string_view view) : _view(view) {}
        inline auto begin() {
            return WordIterator<std::u16string_view::const_iterator>(_view.begin(), _view.end());
        }
        inline auto end() {
            return WordIterator<std::u16string_view::const_iterator>(_view.end(), _view.end());
        }
    };
}
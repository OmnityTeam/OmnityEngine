#pragma once
#include <string>
#include <memory>
#include <concepts>
#include <variant>
#include <stdexcept>
#include <fmt/xchar.h>

namespace omnity {
    namespace string_utils {
        std::u16string from_utf8_ptr(const char8_t* str, size_t len);
        inline std::u16string from_utf8_ptr(const char8_t* str) {
            return from_utf8_ptr(str, std::char_traits<char8_t>::length(str));
        }
        std::u16string from_utf32_ptr(const char32_t* str, size_t len);

        inline std::u16string from_utf8_ptr(const char* str, size_t len) {
            return from_utf8_ptr(reinterpret_cast<const char8_t*>(str), len);
        }
        inline std::u16string from_utf8_ptr(const char* str) {
            return from_utf8_ptr(reinterpret_cast<const char8_t*>(str));
        }
        inline std::u16string from_wide_ptr(const wchar_t* str, size_t len) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
				return { reinterpret_cast<const char16_t*>(str) };
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return from_utf32_ptr(reinterpret_cast<const char32_t*>(str), len);
        }
        inline std::u16string from_wide_ptr(const wchar_t* str) {
            if constexpr (sizeof(wchar_t) == sizeof(char16_t))
                return { reinterpret_cast<const char16_t*>(str) };
            if constexpr (sizeof(wchar_t) == sizeof(char32_t))
                return from_utf32_ptr(reinterpret_cast<const char32_t*>(str), std::char_traits<wchar_t>::length(str));
        }
        std::u16string from_utf8(const std::string_view& str);
		std::string to_utf8(const std::u16string_view& str);
        char32_t next_char(std::u16string_view::const_iterator& iter, std::u16string_view::const_iterator end);
        char32_t next_char(std::u16string::const_iterator& iter, std::u16string::const_iterator end);
    }
    template <typename TChar16Iterator>
    class word_iterator {
        TChar16Iterator str_iter_;
        TChar16Iterator str_end_;
    public:
        word_iterator(TChar16Iterator str_beg, TChar16Iterator str_end) :
            str_iter_(str_beg), str_end_(str_end) {}
        word_iterator<TChar16Iterator>& operator++() {
            string_utils::next_char(str_iter_, str_end_);
            return *this;
        }
        char32_t operator*() const {
            if (str_iter_ == str_end_)
                throw std::out_of_range{
                  "Parties can only have 3 players" };
            auto copyIter = str_iter_;
            return string_utils::next_char(copyIter, str_end_);
        }
        bool operator==(const word_iterator& b) const {
            return str_iter_ == b.str_iter_ && str_end_ == b.str_end_;
        }
    };

    class words {
        std::u16string_view view_;
    public:
        explicit inline words(const std::u16string_view view) : view_(view) {}
        inline auto begin() {
            return word_iterator<std::u16string_view::const_iterator>(view_.begin(), view_.end());
        }
        inline auto end() {
            return word_iterator<std::u16string_view::const_iterator>(view_.end(), view_.end());
        }
    };
}
#ifdef WIN32
#include <Windows.h>
#endif
#include <base/omnity_string.h>
#include <utf8.h>
#include <iterator>

namespace omnity::string_utils
{
    std::u16string from_utf8_ptr(const char8_t* str, size_t len) {
        std::u16string ret;
        utf8::utf8to16(str, str + len, std::back_inserter(ret));
        return ret;
    }
    std::u16string from_utf32_ptr(const char32_t* str, size_t len) {
        std::u16string ret;
        while (len-- != 0) {
            utf8::append16(*(str++), std::back_inserter(ret));
        }
        return ret;
    }
    std::u16string from_utf8(const std::string& str) {
        std::u16string ret;
        utf8::utf8to16(str.begin(), str.end(), std::back_inserter(ret));
        return ret;
    }
    std::string to_utf8(const std::u16string& str) {
        std::string ret;
        utf8::utf16to8(str.begin(), str.end(), std::back_inserter(ret));
        return ret;
    }
    template <typename TIter>
    inline char32_t next_char(TIter& iter, TIter end) {
        return utf8::next16(iter, end);
    }
    char32_t next_char(std::u16string_view::const_iterator& iter, std::u16string_view::const_iterator end) {
        return next_char<std::u16string_view::const_iterator>(iter, end);
    }
    char32_t next_char(std::u16string::const_iterator& iter, std::u16string::const_iterator end) {
        return next_char<std::u16string::const_iterator>(iter, end);
    }
}

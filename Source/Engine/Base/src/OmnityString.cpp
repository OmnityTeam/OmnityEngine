#ifdef WIN32
#include <Windows.h>
#endif
#include <Base/OmnityString.h>
#include <utf8.h>
#include <iterator>

namespace Omnity {
	namespace StringUtils {
		std::u16string FromUtf8Ptr(const char8_t* str, size_t len) {
			std::u16string ret;
			utf8::utf8to16(str, str + len, std::back_inserter(ret));
			return ret;
		}
		std::u16string FromUtf32Ptr(const char32_t* str, size_t len) {
			std::u16string ret;
			while (len-- != 0) {
				utf8::append16(*(str++), std::back_inserter(ret));
			}
			return ret;
		}
		std::u16string FromUtf8(const std::string& str) {
			std::u16string ret;
			utf8::utf8to16(str.begin(), str.end(), std::back_inserter(ret));
			return ret;
		}
		std::string ToUtf8(const std::u16string& str) {
			std::string ret;
			utf8::utf16to8(str.begin(), str.end(), std::back_inserter(ret));
			return ret;
		}
		template <typename TIter>
		inline char32_t NextChar(TIter& iter, TIter end) {
			return utf8::next16(iter, end);
		}
		char32_t NextChar(std::u16string_view::const_iterator& iter, std::u16string_view::const_iterator end) {
			return NextChar<std::u16string_view::const_iterator>(iter, end);
		}
		char32_t NextChar(std::u16string::const_iterator& iter, std::u16string::const_iterator end) {
			return NextChar<std::u16string::const_iterator>(iter, end);
		}
	}
}

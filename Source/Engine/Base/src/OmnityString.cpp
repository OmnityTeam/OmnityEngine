#ifdef WIN32
#include <Windows.h>
#endif
#include "OmnityString.h"
#include <utf8.h>
#include <iterator>

namespace Omnity {
	namespace StringUtils {
		Utf16String FromUtf8Ptr(const char8_t* str, size_t len) {
			Utf16String ret;
			utf8::utf8to16(str, str + len, std::back_inserter(ret));
			return ret;
		}
		Utf16String FromUtf32Ptr(const char32_t* str, size_t len) {
			Utf16String ret;
			while (len-- != 0) {
				utf8::append16(*(str++), std::back_inserter(ret));
			}
			return ret;
		}
		Utf16String FromUtf8(const Utf8String& str) {
			Utf16String ret;
			utf8::utf8to16(str.begin(), str.end(), std::back_inserter(ret));
			return ret;
		}
		Utf8String ToUtf8(const Utf16String& str) {
			Utf8String ret;
			utf8::utf16to8(str.begin(), str.end(), std::back_inserter(ret));
			return ret;
		}
		template <typename TIter>
		inline char32_t NextChar(TIter& iter, TIter end) {
			return utf8::next16(iter, end);
		}
		char32_t NextChar(StringRef::const_iterator& iter, StringRef::const_iterator end) {
			return NextChar<StringRef::const_iterator>(iter, end);
		}
		char32_t NextChar(String::const_iterator& iter, String::const_iterator end) {
			return NextChar<String::const_iterator>(iter, end);
		}
	}
}

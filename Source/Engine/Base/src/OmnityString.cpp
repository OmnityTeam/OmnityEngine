#ifdef WIN32
#include <Windows.h>
#endif
#include "OmnityString.h"
#include <utf8.h>
#include <iterator>

namespace Omnity {
	namespace StringUtils {
		template <typename T>
		size_t UtfStrLen(const T* str) {
			size_t ret = 0;
			while (*str != '\0') ++ret;
			return ret;
		}
		Utf16String FromUtf8Ptr(const char* str, size_t len) {
			Utf16String ret;
			utf8::utf8to16(str, str + len, std::back_inserter(ret));
			return ret;
		}
		Utf16String FromUtf8Ptr(const char8_t* str) {
			Utf16String ret;
			utf8::utf8to16(str, str + UtfStrLen(str), std::back_inserter(ret));
			return ret;
		}
		Utf16String FromUtf32Ptr(const char32_t* str) {
			Utf16String ret;
			Utf8String u8Str;
			// TODO fix duplicate conversion
			utf8::utf32to8(str, str + UtfStrLen(str), std::back_inserter(u8Str));
			utf8::utf8to16(u8Str.begin(), u8Str.end(), std::back_inserter(ret));
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
	}
}

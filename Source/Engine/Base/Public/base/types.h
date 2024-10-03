#pragma once
#include <base/string_utils.h>
#include <base/object.h>
#include <source_location>

namespace omnity {
	class noncopyable
	{
	protected:
		constexpr noncopyable() = default;
		~noncopyable() = default;
		noncopyable(const noncopyable&) = delete;
		const noncopyable& operator=(const noncopyable&) = delete;
	};
}
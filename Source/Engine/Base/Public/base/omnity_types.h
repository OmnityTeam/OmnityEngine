#pragma once
#include <base/omnity_string.h>
#include <base/internal_types.h>
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
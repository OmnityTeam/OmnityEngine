#pragma once

namespace omnity {
	template <typename T>
	void resource_binary_serializer(std::ostream& os, T&& value)
	{
		// iterate over the members of T
		for_each(refl::reflect(value).members, [&](auto member)
			{
				// is_readable checks if the member is a non-const field
				// or a 0-arg const-qualified function marked with property attribute
				if constexpr (is_readable(member) && refl::descriptor::has_attribute<serializable>(member))
				{
					// get_display_name prefers the friendly_name of the property over the function name
					os << get_display_name(member) << "=";
					// member(value) returns a reference to the field or calls the property accessor
					os << member(value) << ";";
				}
			});
	}

	template <typename T>
	void resource_binary_deserializer(std::ostream& os, T&& value)
	{
		// iterate over the members of T
		for_each(refl::reflect(value).members, [&](auto member)
			{
				// is_readable checks if the member is a non-const field
				// or a 0-arg const-qualified function marked with property attribute
				if constexpr (is_readable(member) && refl::descriptor::has_attribute<serializable>(member))
				{
					// get_display_name prefers the friendly_name of the property over the function name
					os << get_display_name(member) << "=";
					// member(value) returns a reference to the field or calls the property accessor
					os << member(value) << ";";
				}
			});
	}
}
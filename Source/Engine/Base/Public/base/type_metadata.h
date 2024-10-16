#pragma once
#include <assert.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <ranges>

namespace omnity {
	// Metaserialize options
	struct serialize_ctx;
	using serializer_serialize_f = void(*)(serialize_ctx* ctx, void* ptr);
	struct serializer_t {
		serializer_serialize_f serialize;
		explicit constexpr serializer_t(serializer_serialize_f s) : serialize(s) {}
	};
	using vector_get_element = void*(*)(void* ptr, size_t i);
	using vector_get_size = size_t(*)(void* ptr);
	using vector_add = void(*)(void* ptr, void* elem);
	using vector_remove = void(*)(void* ptr, size_t i);
	using vector_insert = void(*)(void* ptr, size_t i, void* elem);
	using vector_clear = void(*)(void* ptr);
	struct vector_impl_t {
		vector_get_element get_element;
		vector_get_size get_size;
		vector_add add;
		vector_add emplace_add;
		vector_remove remove;
		vector_insert insert;
		vector_insert emplace_insert;
		vector_clear clear;
	};
	template <typename T>
	vector_impl_t create_vector_impl() {
		if constexpr (std::is_same_v<T, bool>)
			return {};
		else {
			using vector = std::vector<T>;
			vector_impl_t impl;
			impl.get_element = [](void* ptr, size_t i) { return static_cast<void*>(&(*static_cast<vector*>(ptr))[i]); };
			impl.get_size = [](void* ptr) { return static_cast<vector*>(ptr)->size(); };
			impl.add = [](void* ptr, void* elem) { static_cast<vector*>(ptr)->push_back(*static_cast<typename vector::value_type*>(elem)); };
			impl.emplace_add = [](void* ptr, void* elem) { static_cast<vector*>(ptr)->push_back(std::move(*static_cast<typename vector::value_type*>(elem))); };
			impl.remove = [](void* ptr, size_t i) { static_cast<vector*>(ptr)->erase(static_cast<vector*>(ptr)->begin() + i); };
			impl.insert = [](void* ptr, size_t i, void* elem) { static_cast<vector*>(ptr)->insert(static_cast<vector*>(ptr)->begin() + i, *static_cast<typename vector::value_type*>(elem)); };
			impl.emplace_insert = [](void* ptr, size_t i, void* elem) { static_cast<vector*>(ptr)->insert(static_cast<vector*>(ptr)->begin() + i, std::move(*static_cast<typename vector::value_type*>(elem))); };
			impl.clear = [](void* ptr) { static_cast<vector*>(ptr)->clear(); };
			return impl;
		}
	}

	// Type metadata
	using field_id_t = uint32_t;
	using type_id_t = uint32_t;
	class field_metadata;
	class type_metadata;
	class field_metadata {
		friend class type_metadata;
	public:
		const std::u16string_view name;
		const type_id_t field_type_id;
		const size_t field_type_index;
		const size_t offset;
		const bool is_array;
		constexpr field_metadata(const std::u16string_view n, const type_id_t type_id, const size_t type_index, const bool is_array, const size_t off)
			: name(n), field_type_id(type_id), field_type_index(type_index), offset(off), is_array(is_array) {}
		[[nodiscard]] const type_metadata* get_type_metadata() const;
	};
	class type_metadata {
		std::vector<field_metadata> fields_;
		std::map<std::u16string_view, field_id_t> field_map_;
	public:
		using field_foreach_action_t = void(*)(void* ctx, field_id_t i, field_metadata meta);
		using field_foreach_f = void(*)(void* ctx, field_foreach_action_t action);
		const std::u16string_view name;
		const size_t runtime_type_index;
		const type_id_t type_id;
		const serializer_t serializer;
		const vector_impl_t vector_impl;
		field_foreach_f foreach;
		type_metadata(const std::u16string_view n, const size_t type_index, const type_id_t id, const serializer_t& s, const vector_impl_t& vector_impl, field_foreach_f field_foreach)
			: name(n), runtime_type_index(type_index), type_id(id), serializer(s), vector_impl(vector_impl), foreach(field_foreach) {
			if (foreach != nullptr)
				foreach(this, [](void* ctx, field_id_t i, field_metadata meta) {
					static_cast<type_metadata*>(ctx)->fields_.emplace_back(meta);
					static_cast<type_metadata*>(ctx)->field_map_[meta.name] = i;
				});
		}
		const field_metadata* get_field(const field_id_t field_id) const {
			return &fields_[field_id];
		}
		const field_metadata* try_get_field(const std::u16string_view field_name) const {
			const auto ret = field_map_.find(field_name);
			assert(ret != field_map_.end());
			return &fields_[ret->second];
		}
		const std::vector<field_metadata>& get_fields() const {
			return fields_;
		}
		template<typename Capture>
		void fields_foreach(Capture cap, void(*action)(Capture cap, field_id_t i, field_metadata meta)) const {
			using specialize_action = void(*)(Capture, field_id_t, field_metadata);
			struct ctx_t {
				Capture c;
				specialize_action act;
				ctx_t(Capture c, specialize_action act) : c(c), act(act) {}
			};
			ctx_t ctx(cap, action);
			if (foreach == nullptr) return;
			foreach(&ctx, [](void* ctx, field_id_t i, field_metadata meta)
				{
					static_cast<ctx_t*>(ctx)->act(static_cast<ctx_t*>(ctx)->c, i, meta);
				});
		}
	};
}
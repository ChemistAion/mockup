#include "gltf_pch.hpp"

#include "accessor.hpp"

namespace Mockup::glTF
{
	Accessors GetAccessors(const simdjson::dom::element& element)
	{
		Accessors accessors;

		const auto& items = Get<simdjson::dom::array>(element);
		accessors.reserve(items.size());

		for (const auto item : items)
		{
			const auto object = Get<simdjson::dom::object>(item);
			auto& accessor = accessors.emplace_back();

			for (const auto [key, value] : object)
			{
				if (key == "bufferView")
				{
					accessor.buffer_view_ = Get<std::uint64_t>(value);
					continue;
				}

				if (key == "byteOffset")
				{
					accessor.offset_ = Get<std::uint64_t>(value);
					continue;
				}

				if (key == "count")
				{
					accessor.count_ = Get<std::uint64_t>(value);
					continue;
				}

				if (key == "componentType")
				{
					//TODO: check it...
					auto component_type = Get<std::uint64_t>(value);
					accessor.component_type_ = static_cast<Accessor::ComponentType>(component_type);
					continue;
				}

				if (key == "normalized")
				{
					//TODO: check it...
					assert(false);
					continue;
				}

				if (key == "type")
				{
					auto type = Get<std::string_view>(value);

					if (type == "SCALAR")
					{
						accessor.type_ = Accessor::Type::Scalar;
						continue;
					}

					if (type == "VEC2")
					{
						accessor.type_ = Accessor::Type::Vec2;
						continue;
					}

					if (type == "VEC3")
					{
						accessor.type_ = Accessor::Type::Vec3;
						continue;
					}

					if (type == "VEC4")
					{
						accessor.type_ = Accessor::Type::Vec4;
						continue;
					}

					if (type == "MAT2")
					{
						accessor.type_ = Accessor::Type::Mat2;
						continue;
					}

					if (type == "MAT3")
					{
						accessor.type_ = Accessor::Type::Mat3;
						continue;
					}

					if (type == "MAT4")
					{
						accessor.type_ = Accessor::Type::Mat4;
						continue;
					}

					assert(false);
				}

				if (key == "min")
				{
					accessor.min_= GetVector<double>(value);
					continue;
				}

				if (key == "max")
				{
					accessor.max_ = GetVector<double>(value);
					continue;
				}

				if (key == "sparse")
				{
					//TODO: check it...
					assert(false);
					continue;
				}

				////////////////////////////////////////////////////////////////////////////////

				if (key == "name")
				{
					accessor.name_ = Get<std::string_view>(value);
					continue;
				}

				if (key == "extensions")
				{
					continue;
				}

				if (key == "extras")
				{
					accessor.extras_ = std::move(GetExtras(value));
					continue;
				}

				assert(false);
			}
		}

		//TODO: checks...
		//min/max size equal?

		return accessors;
	}
}
#include "gltf_pch.hpp"

#include "skin.hpp"

namespace Mockup::glTF
{
	Skins GetSkins(const simdjson::dom::element& element)
	{
		Skins skins;

		const auto& items = Get<simdjson::dom::array>(element);
		skins.reserve(items.size());

		for (const auto item : items)
		{
			const auto object = Get<simdjson::dom::object>(item);
			auto& skin = skins.emplace_back();

			for (const auto [key, value] : object)
			{
				if (key == "inverseBindMatrices")
				{
					skin.ibm_ = std::move(Get<std::uint64_t>(value));
					continue;
				}

				if (key == "skeleton")
				{
					skin.skeleton_ = std::move(Get<std::uint64_t>(value));
					continue;
				}

				if (key == "joints")
				{
					const auto array = Get<simdjson::dom::array>(value);

					for (const auto item : array)
					{
						skin.joints_.push_back(Get<std::uint64_t>(item));
					}
					continue;
				}

				////////////////////////////////////////////////////////////////////////////////

				if (key == "name")
				{
					skin.name_ = Get<std::string_view>(value);
					continue;
				}

				if (key == "extensions")
				{
					continue;
				}

				if (key == "extras")
				{
					skin.extras_ = std::move(GetExtras(value));
					continue;
				}

				assert(false);
			}
		}

		return skins;
	}
}

#pragma once

#include "indexer.hpp"
#include "system.hpp"

#include <memory>
#include <vector>

namespace Mockup::Director
{
	class Registry;
	
	class Feature final
	{
		std::vector<std::unique_ptr<System<>>> systems_;
//		bool enabled_ = true;
	public:
		Feature() = default;
	
		Feature(const Feature&) = delete;
		Feature& operator=(const Feature&) = delete;
	
		Feature(Feature&&) noexcept = default;
		Feature& operator=(Feature&&) noexcept = default;
	
		////////////////////////////////////////////////////////////////////////////////
	
		template <typename Type, typename... Arguments>
		void MountSystem(Arguments&&... arguments)
		{
			systems_.push_back(std::make_unique<Type>(std::forward<Arguments>(arguments)...));
		}
	
		template <typename Event>
		void Process(Registry& owner, const Event& event)
		{
			const auto processor = [this, &owner](const auto& event)
			{
				for (const auto& base_system : systems_)
				{
					using SystemType = System<std::decay_t<decltype(event)>>;

					if (auto system = dynamic_cast<SystemType*>(base_system.get()))
					{
						system->Process(owner, event);
					}
				}
			};
			
			processor(event);
		}
	};
}
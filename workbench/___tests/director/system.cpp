#include "director.hpp"
#include "system.hpp"

TEST_F(Director, System_Basics)
{
	using namespace Primitives;

	////////////////////////////////////////////////////////////////////////////////

	Registry registry;

	ASSERT_FALSE(registry.Has<Physics>());

	registry.Emplace<Physics>();
	auto& feature = registry.Get<Physics>();

	ASSERT_TRUE(registry.Has<Physics>());

	feature.MountSystem<GravitySystem>(9);
	feature.MountSystem<MovementSystem>();
	
	auto entity = registry.Create();
	
	registry.Emplace<Position>(entity, 1, 2);
	registry.Emplace<Velocity>(entity, 3, 4);

	registry.Process(UpdateEvent { 2 });

	return;
}
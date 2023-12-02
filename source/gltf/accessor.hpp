#pragma once

namespace Mockup::glTF
{
	struct Accessor
	{
		enum class ComponentType : std::uint32_t
		{
			None = 0,
			Byte = 5120,
			UnsignedByte = 5121, 
			Short = 5122,
			UnsignedShort = 5123,
			UnsignedInt = 5125,
			Float = 5126
		};

		enum class Type
		{
			None,
			Scalar,
			Vec2,
			Vec3,
			Vec4,
			Mat2,
			Mat3,
			Mat4
		};

		std::optional<Index> buffer_view_;
		std::uint64_t offset_ = 0;
		std::uint64_t count_ = 0;
		ComponentType component_type_ = ComponentType::None;
		Type type_ = Type::None;

		std::vector<double> min_;
		std::vector<double> max_;

		Name name_;
		Extras extras_;
	};

	using Accessors = std::vector<Accessor>;
	Accessors GetAccessors(const simdjson::dom::element& element);

}
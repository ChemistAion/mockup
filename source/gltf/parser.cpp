#include "gltf_pch.hpp"

#include "parser.hpp"

//https://stackoverflow.com/questions/61969316/is-it-possible-to-put-lambda-expressions-into-a-map-or-list-in-c

namespace Mockup::glTF
{
    bool Parser::Load(const std::string& file)
    {
		simdjson::dom::element element;

		if (auto error = parser_.load(file).get(element); error)
		{
			return false;
		}

		////////////////////////////////////////////////////////////////////////////////

		return true;
    }
}

//		if (auto error = element.at_key("accessors").get(accessors_); error)
//		{
//			return false;
//		}
//		
//		if (auto error = element.at_key("bufferViews").get(views_); error)
//		{
//			return false;
//		}
//		
//		Object test;
//		
//		simdjson::dom::array meshes;
//		if (auto error = element.at_key("meshes").get(meshes); error)
//		{
//			return false;
//		}
//		
//		test.meshes_.reserve(meshes.size());
//		
//		for (const auto& mesh : meshes)
//		{
//			simdjson::dom::array primitives;
//			if (auto error = mesh.at_key("primitives").get(primitives); error)
//			{
//				continue;
//			}
//		
//			std::vector<Concepts::Primitives> result;
//			result.reserve(primitives.size());
//		
//			for (const auto& primitive : primitives)
//			{
//				const auto position = primitive.at_pointer("/attributes/POSITION");
//				const auto& accessor = accessors_.at(position);
//		
//				auto max = GetVector(accessor.at_key("max"));
//				continue;
//			}
//		}

//		std::map<std::string, std::function<void()>> test;
//		
//		test.emplace("first", []() { std::cout << "TEST" << std::endl; });
//		
//		for (auto& x : test)
//		{
//			x.second();
//		}

//	for (const simdjson::dom::key_value_pair& field : object)
//	{
//		auto name = field.key;
//		auto element = field.value;
//		std::cout << std::endl << name << "::";
//	
//		switch (element.type())
//		{
//		case simdjson::dom::element_type::ARRAY:
//		{
//			for (simdjson::dom::element child : simdjson::dom::array(element))
//			{
//				//print_json(child);
//			}
//			break;
//		}
//		case simdjson::dom::element_type::OBJECT:
//		{
//			for (const simdjson::dom::key_value_pair& field : simdjson::dom::object(element))
//			{
//				//print_json(field.value);
//			}
//			break;
//		}
//		case simdjson::dom::element_type::INT64:
//		{
//			//std::cout << int64_t(element) << std::endl;
//			break;
//		}
//		case simdjson::dom::element_type::UINT64:
//		{
//			//std::cout << uint64_t(element) << std::endl;
//			break;
//		}
//		case simdjson::dom::element_type::DOUBLE:
//		{
//			//std::cout << double(element) << std::endl;
//			break;
//		}
//		case simdjson::dom::element_type::STRING:
//		{
//			//std::cout << std::string_view(element) << std::endl;
//			break;
//		}
//		case simdjson::dom::element_type::BOOL:
//		{
//			//std::cout << bool(element) << std::endl;
//			break;
//		}
//		case simdjson::dom::element_type::NULL_VALUE:
//		{
//			//std::cout << "NULL" << std::endl;
//			break;
//		}
//		}
//	}
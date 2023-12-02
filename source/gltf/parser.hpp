#pragma once

//https://github.com/KhronosGroup/glTF/blob/master/specification/2.0/README.md
//https://simdjson.org/api/0.8.0/index.html

namespace Mockup::glTF
{
	class Parser
	{
	private:
		simdjson::dom::parser parser_;

		////////////////////////////////////////////////////////////////////////////////
		
	public:
		bool Load(const std::string& file);
	};
}
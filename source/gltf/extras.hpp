#pragma once

namespace Mockup::glTF
{
	using Extras = Value;

	Extras GetExtras(const simdjson::dom::element& element);
}
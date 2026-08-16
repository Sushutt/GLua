#include "sol_custom.hpp"
#include "godot_cpp/variant/variant.hpp"

godot::Variant to_gd_variant(sol::object obj)
{
	sol::type type = obj.get_type();

	// Find the type
	// TODO: Add more, non trivial types
	switch (type) {
		case sol::type::string:
			return godot::Variant(obj.as<std::string>().c_str());
			break;
		case sol::type::number:
			return godot::Variant(obj.as<double>());
			break;
		case sol::type::boolean:
			return godot::Variant(obj.as<bool>());
			break;
		default:
			return godot::Variant();
			break;
	}
}

// In theory this isn't actually needed but the addon doesn't load if this is left out.
godot::Variant sol_lua_get(sol::types<godot::Variant>, lua_State* L, int index, sol::stack::record& tracking) 
{
	int absolute_index = lua_absindex(L, index);
	tracking.use(1);

	sol::object object = sol::stack::get<sol::object>(L, absolute_index);
    
	return to_gd_variant(object);
}
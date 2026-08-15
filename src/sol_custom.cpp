#include "godot_cpp/variant/variant.hpp"
#include <sol_custom.hpp>
#include <string>

// Why does this work?
godot::Variant sol_lua_get(sol::types<godot::Variant>, lua_State* L, int index, sol::stack::record& tracking) {
	int absolute_index = lua_absindex(L, index);
	tracking.use(1);

	sol::type type = sol::type_of(L, absolute_index);
    
	// Find the type
	// TODO: Add more 
	switch (type) {
		case sol::type::string:
			return godot::Variant(sol::stack::get<std::string>(L, absolute_index ).c_str());
		case sol::type::number:
			return godot::Variant(sol::stack::get<double>(L, absolute_index ));
		default:
			return godot::Variant(); // Returns Nil by default
    }
}
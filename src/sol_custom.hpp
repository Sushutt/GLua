#include "godot_cpp/variant/variant.hpp"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

godot::Variant to_gd_variant(sol::object);

godot::Variant sol_lua_get(sol::types<godot::Variant>, lua_State* L, int index, sol::stack::record& tracking);
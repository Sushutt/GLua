#include "luascript.h"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <sol/sol.hpp>

#define SOL_ALL_SAFETIES_ON 1

using namespace godot;

void LuaScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("run"), &LuaScript::run);

	ClassDB::bind_method(D_METHOD("get_luacode"), &LuaScript::get_luacode);
	ClassDB::bind_method(D_METHOD("set_luacode", "p_luacode"), &LuaScript::set_luacode);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "luacode", PROPERTY_HINT_MULTILINE_TEXT), "set_luacode", "get_luacode");
}

LuaScript::LuaScript() {

}

LuaScript::~LuaScript() {
	// Add your cleanup here.
}

void LuaScript::_ready() {
	godot::print_line("hiiiiiiii :3");
}

void LuaScript::run()
{
	godot::print_line(luacode);
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	lua.safe_script(luacode.utf8().get_data());
}

void LuaScript::set_luacode(const String p_luacode) {
	luacode = p_luacode;
}

String LuaScript::get_luacode() const {
	return luacode;
}
#include "luascript.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <sol/sol.hpp>
#include <string>

#define SOL_ALL_SAFETIES_ON 1

using namespace godot;

void LuaScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("run"), &LuaScript::run);
	ClassDB::bind_method(D_METHOD("create_lua_state"), &LuaScript::create_lua_state);

	ClassDB::bind_method(D_METHOD("get_lua_code"), &LuaScript::get_lua_code);
	ClassDB::bind_method(D_METHOD("set_lua_code", "p_lua_code"), &LuaScript::set_lua_code);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "lua_code", PROPERTY_HINT_MULTILINE_TEXT), "set_lua_code", "get_lua_code");
}

// Bullshit happens if I remove the constructor/destructor so just leave them here
LuaScript::LuaScript() {

}
LuaScript::~LuaScript() {
	// Add your cleanup here.
}


void LuaScript::_ready() {
	//godot::print_line("hiiiiiiii :3");
}

// Little functions
void print(std::string content)
{
	String godot_string(content.c_str());
	godot::print_line(godot_string);
}

// BIG stuff
void LuaScript::run()
{
	lua_state.safe_script(lua_code.utf8().get_data());
}

void LuaScript::set_lua_code(const String p_lua_code) 
{
	lua_code = p_lua_code;
}

String LuaScript::get_lua_code() const 
{
	return lua_code;
}

void LuaScript::create_lua_state()
{
	lua_state = sol::state();
	// Add built-in functions
	lua_state.set_function("log", print);
	// Just expose most libraries to each script
	lua_state.open_libraries(sol::lib::base, sol::lib::math);
}
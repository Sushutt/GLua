#include "luascript.hpp"

#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/callable.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>

#include <sol_custom.hpp>

#include <string>

#include "callable_binding.hpp"
#include "node_binding.hpp"

using namespace godot;

void LuaScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_callable", "callable"), &LuaScript::add_callable);
	ClassDB::bind_method(D_METHOD("create_lua_state"), &LuaScript::create_lua_state);
	ClassDB::bind_method(D_METHOD("run"), &LuaScript::run);

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
	//godot::print_line(get_name());
}

// Little functions
void print(std::string content)
{
	String godot_string(content.c_str());
	godot::print_line(godot_string);
}

/*
	Adds a godot callable as a function to the script
*/
void LuaScript::add_callable(Callable callable)
{
	//godot::print_line(callable.get_bound_arguments());
	//lua_state.set_function(
	//	((String)callable.get_method()).utf8().get_data(),
	//	[callable] (Variant v) {callable.call(v);});

	lua_state[((String)callable.get_method()).utf8().get_data()] = CallableBinding(callable);
}

void LuaScript::create_lua_state()
{
	lua_state = sol::state();
	// Add built-in functions
	lua_state.set_function("log", print);

	// OUR OWN "callable" proxy
	lua_state.new_usertype<CallableBinding>("Callable",
		"Call", &CallableBinding::Call);

	lua_state.new_usertype<NodeBinding>("Node",
		"GetName", &NodeBinding::GetName);
	
	// Create a reference to the script node
	lua_state["Self"] = NodeBinding(this);

	// Just expose most libraries to each script
	lua_state.open_libraries(sol::lib::base, sol::lib::math);
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
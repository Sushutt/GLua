extends LuaScript

func _ready() -> void:
	create_lua_state()
	run()

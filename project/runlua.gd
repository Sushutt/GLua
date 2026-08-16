extends LuaScript

func piss(var0, var1):
	print(var0 + var1)

func _ready() -> void:
	create_lua_state()
	add_callable(Callable(self, "piss"))
	run()

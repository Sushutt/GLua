extends LuaScript

func piss(arg):
	print(arg)

func _ready() -> void:
	#print(Callable(self, "piss").get_method())
	create_lua_state()
	#add_callable(Callable(self, "piss"))
	run()

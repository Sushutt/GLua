extends LuaScript

func piss(x, y, z):
	print("mesh added");
	var mesh = MeshInstance3D.new();
	add_child(mesh);
	mesh.mesh = BoxMesh.new();
	mesh.position = Vector3(x,y,z);

func _ready() -> void:
	create_lua_state()
	add_callable(Callable(self, "piss"))
	run()

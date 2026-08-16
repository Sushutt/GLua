#include "callable_binding.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/variant.hpp"


CallableBinding::CallableBinding(godot::Callable c)
{
    callable = c;
}
CallableBinding::~CallableBinding(){}

void CallableBinding::Call(sol::variadic_args va)
{
    godot::Array arr = godot::Array();
    for (auto v : va) {
        // Have to directly convert here because sol doesn't wanna do it and I don't know enough about c++ programming to bother fixing it properly.
        godot::Variant var = to_gd_variant(v);
        arr.append(var);
    }

    callable.callv(arr);
}
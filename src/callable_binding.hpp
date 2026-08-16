#include "sol_custom.hpp"

/* 
    BIG STUPID HACK !!
    A proxy for Godot's "callable" because it crashes when called from sol otherwise.
*/
class CallableBinding
{
    private:
        godot::Callable callable;

    public:
        CallableBinding(godot::Callable);
        ~CallableBinding();
        
        void Call(sol::variadic_args);
};
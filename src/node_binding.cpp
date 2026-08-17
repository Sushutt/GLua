#include "node_binding.hpp"

/*
    I don't know enough about C++ to explain what the hell was going on here.

    Something about references or pointers or whathaveyou, just know that doing
    godot::Node* node = &n doesn't work but having the little * inside the function itself does.

    I don't know if that conveyed what I wanted to say. In summary, this works. And I don't know why.
*/
NodeBinding::NodeBinding(godot::Node* n)
{
    node = n;
}
NodeBinding::~NodeBinding(){}

std::string NodeBinding::GetName()
{
    return ((godot::String)node->get_name()).utf8().get_data();
}
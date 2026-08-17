#include "godot_cpp/classes/node.hpp"
#include "sol_custom.hpp"

/* 
    A proxy because I don't want to deal with sol and godot bickering with eachother.
*/
class NodeBinding
{
    private:
        godot::Node* node;

    public:
        NodeBinding(godot::Node*);
        ~NodeBinding();

        std::string GetName();
};

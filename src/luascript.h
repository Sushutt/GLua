#pragma once

#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    class LuaScript : public Node {
        GDCLASS(LuaScript, Node)

        private:
            String luacode;

        protected:
            static void _bind_methods();

        public:
            LuaScript();
            ~LuaScript();

            void run();

            void set_luacode(const String p_luacode);
            String get_luacode() const;


        void _ready() override;
    };

} // namespace godot
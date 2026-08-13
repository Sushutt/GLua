#pragma once

#include "godot_cpp/variant/string.hpp"
#include "sol/sol.hpp"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    class LuaScript : public Node {
        GDCLASS(LuaScript, Node)

        private:
            String lua_code;
            sol::state lua_state;

        protected:
            static void _bind_methods();

        public:
            LuaScript();
            ~LuaScript();

            void run();

            void set_lua_code(const String p_lua_code);
            String get_lua_code() const;

            void create_lua_state();

        void _ready() override;
    };

} // namespace godot
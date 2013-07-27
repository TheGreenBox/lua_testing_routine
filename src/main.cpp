#include <iostream>
#include "cardsDeck.h"
#include "luaIncludes.h"


class HeliumLuaException
{
public:
    HeliumLuaException(const char* name);
    const char* getName(){ return name; };
    
private:
    const char* name;
};

int main (int argsNumber, char** argAr)
{
    std::cout << "Hello!\n";
    std::cout << "Lets go...\n\n";
    int rez = 0;
    Lua::lua_State* luaSt = Lua::luaL_newstate();
    Lua::luaopen_base(luaSt);
    Lua::luaopen_io(luaSt);
    Lua::luaopen_table(luaSt);
    
    rez = Lua::luaL_loadfile(luaSt, "scripts/cardsDeckCreate.lua");
    std::cout << "load file: " << rez << '\n';
    if (rez != 0) {
        std::cout << "Error while loading script file!\n" 
                  << "Error: " << Lua::lua_tostring(luaSt, -1) << '\n';
    }

    rez = Lua::lua_pcall(luaSt, 0, LUA_MULTRET, 0);
    std::cout << "lua pcall: " << rez << '\n';
    if (rez != 0) {
        std::cout << "Error exucute script file!\n" 
                  << "Error: " << Lua::lua_tostring(luaSt, -1) << '\n';
    }
    std::cout << "end of second exec\n";   
    Lua::lua_close(luaSt);
    
    return 0;
}


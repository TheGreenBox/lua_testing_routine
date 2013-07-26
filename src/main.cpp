#include <iostream>
#include "cardsDeck.h"

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

class HeliumLuaException
{
public:
    HeliumLuaException(const char* name);
    const char* getName(){ return name; };
    
private:
    const char* name;
};

CardsDeck gCardsDeck;

int addCardToGDeck (lua_State* luaVM)
{
    int argc = lua_gettop(luaVM);
    if ( argc != 2 ) {
        //throw HeliumLuaException("must have 2 arguments");
        return 0;
    }
    
    if (!lua_isstring(luaVM,1) || !lua_isnumber(luaVM,2)) {
        lua_pushnumber(luaVM, 0);
        //throw HeliumLuaException("Arguments must have string and number type");
        return 0;
    }
    
    gCardsDeck.addCard( Card(lua_tostring(luaVM, 1),
                             lua_tonumber(luaVM, 2) ) );
    //lua_pushnumber(luaVM, nResult);
    return 1;
}

int main (int argsNumber, char** argAr)
{
    std::cout << "Hello!\n";
    std::cout << "Lets go...\n";
    int rez = 0;
    lua_State* luaSt = luaL_newstate();
    lua_register(luaSt, "add_card_to_deck", addCardToGDeck);
    
    rez = luaL_loadfile(luaSt, "scripts/cardsDeckCreator.lua");
    std::cout << "load file: " << rez << '\n';
    if (rez != 0) {
        std::cout << "Error while loading script file!\n" 
                  << "Error: " << lua_tostring(luaSt, -1) << '\n';
    }

    rez = lua_pcall(luaSt, 0, LUA_MULTRET, 0);
    std::cout << "lua pcall: " << rez << '\n';
    if (rez != 0) {
        std::cout << "Error exucute script file!\n" 
                  << "Error: " << lua_tostring(luaSt, -1) << '\n';
    }
    
    gCardsDeck.showAll();
    
    lua_close(luaSt);
    return 0;
}

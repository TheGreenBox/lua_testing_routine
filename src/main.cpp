#include <iostream>

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

class Card
{
public:
    Card(std::string _name, int _level);
    const char* getTitle() {return name; };
private:
    const char* name;
    int level;
};

class CardsDeck
{
public:
    CardsDeck();
        
    addCard( Card& _card ){
        cards.push_back(_card);
    };
    
    showMeAll();

private:
    std::list<Card> cards;
};

CardsDeck gCardsDeck();

void addCardToGDeck (lua_State* luaVM)
{
    int argc = lua_gettop(luaVM);
    if ( argc != 2 ) {
        throw HeliumLuaException("must have 2 arguments");
    }
    
    if (!lua_isstring(luaVM,1) || !lua_isnumber(luaVM,2)) {
        lua_pushnumber(luaVM, 0);
        throw HeliumLuaException("Arguments must have string and number type");
    }
    
    gCardsDeck.addCard( Card(lua_tostring(luaVM, 1),
                             lua_tonumber(luaVM, 2) ) );
    lua_pushnumber(luaVM, nResult);
    return;
}

int main (int argsNumber, char** argAr)
{
    std::cout << "Hello!\n";
    std::cout << "Lets go...\n";
    lua_State* luaSt = luaL_newstate();
    lua_register(luaSt, "add_card_to_deck", addCardToGDeck);

    gCardsDeck.showMeAll();
    lua_close(luaSt);
    return 0;
}

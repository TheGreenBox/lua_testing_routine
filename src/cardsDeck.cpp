/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Helium
 * File name:  cardsDeck.cpp 
 * Description:
 * Author:  AKindyakov 
 * ========================================================
 */
#include <iostream>
#include <list>
#include "cardsDeck.h"

Card::Card(const char* _name, int _level)
    : name(_name), level(_level)
{}

const char* Card::getTitle() const {
    return name; 
}

CardsDeck::CardsDeck() 
{}
        
void CardsDeck::addCard( const char* _name, int _level  ) {
    cards.push_back( Card(_name,_level) );
}
    
void CardsDeck::showAll() {
    for ( std::list<Card>::const_iterator it = cards.begin();
          it != cards.end(); ++it ) {
        std::cout << it->getTitle() << '\n';
    }
}
static int luaNewCardsDeck(Lua::lua_State* LState) {
    using namespace Lua;
    int argn = lua_gettop(LState);
    if ( argn != 1 ) {
        return luaL_error(LState, "Got %d arguments, expected 1 ( class ) ", argn);
    }
    
    luaL_checktype(LState, 1, LUA_TTABLE); 
    // Create table to rrepresent instance
//    lua_newtable(LState);
//    lua_pushvalue(LState, 1);
//    lua_setfield(LState, 1, "__index");
    CardsDeck** pp_cd = (CardsDeck**)lua_newuserdata(LState, sizeof(CardsDeck*));
    *pp_cd = new CardsDeck();
    
    luaL_getmetatable(LState, "_CardsDeck");
    lua_setmetatable(LState, -2);
//    lua_setfield(LState, -2, "__self");
    return 1;
}

static int luaAddCard( Lua::lua_State* LState ) {
    using namespace Lua;
    int argn = lua_gettop(LState);
    
    if ( argn!=2  && argn!=3 ) {
        return luaL_error(LState, "Got %d arguments, expected 2 or 3 ( class, string, int ) ", argn);
    }
    
    const char* _name = luaL_checkstring(LState, 2);
    int _priority = 0;
    if ( argn == 3 ) {
        _priority = luaL_checknumber(LState, 3);
    }
    
    CardsDeck* p_cd = NULL;
    luaL_checkudata(LState, 1, "CardsDeck");
    p_cd->addCard(_name, _priority);
    return 1;
}

static int luaShowAllCards( Lua::lua_State* LState ) {
    using namespace Lua;

    CardsDeck* p_cd = NULL;
    luaL_checkudata(LState, 1, "CardsDeck");
    p_cd->showAll();
    return 1;
}


void CardsDeck::luaRegisterCardsDeck(Lua::lua_State* LState) {
    using namespace Lua;

    const Lua::luaL_Reg gCardsDeckFunctions[] = {
        { "new",          luaNewCardsDeck },
        { "addCard",      luaAddCard },
        { "showAllCards", luaShowAllCards },
        { NULL, NULL }
    };
    // luaL_register(LState, "CardsDeck", gCardsDeckFunctions);
    // lua_pushvalue(LState, -1);
    // lua_setfield(LState, -2, "__index");
   
    luaL_newmetatable(LState, "_CardsDeck");
    luaL_setfuncs(LState, gCardsDeckFunctions, 0);
    lua_pushvalue(LState, -1);
    lua_setfield(LState, -1, "__index");
    lua_setglobal(LState, "CardsDeck");
}


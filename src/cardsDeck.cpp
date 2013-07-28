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
{
    std::cout << "Card is born!\n";
}

const char* Card::getTitle() const {
    return name; 
}

CardsDeck::CardsDeck() 
{
    std::cout << "CardDeck is born!\n";
}
        
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
    //// create a new empty table and pushes it onto the stack
    lua_newtable(LState);
    //// pushes a copy of element at given valid index onto the stack
    lua_pushvalue(LState, 1);

    lua_setmetatable(LState, -2);
    lua_pushvalue(LState, 1);
    lua_setfield(LState, 1, "__index");
    
    CardsDeck** pp_cd = (CardsDeck**)lua_newuserdata(LState, sizeof(CardsDeck*));
    *pp_cd = new CardsDeck();
    // push onto the stack the metatable associated with name    
    luaL_getmetatable(LState, "CardsDeck");
    // pops a table from the stack and sets it 
    // as the new metatble for the value at given acceptable index
    lua_setmetatable(LState, -2);
    // Does the equivalent to t[k] = v, where t is the value at given at given valid index and v is
    // the value at the top of the stack    
    lua_setfield(LState, -2, "__self");
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
   
    luaL_newmetatable(LState, "CardsDeck");
    luaL_register(LState, 0, gCardsDeckFunctions);
    //luaL_setfuncs(LState, gCardsDeckFunctions, 0);
    lua_pushvalue(LState, -1);
    lua_setfield(LState, -2, "__index");
    //lua_setglobal(LState, "CardsDeck");
    luaL_register(LState, "CardsDeck", gCardsDeckFunctions);
}


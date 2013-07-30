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
int Card::getPriority() const {
    return level;
}

CardsDeck::CardsDeck() 
{
    std::cout << "CardDeck is born!\n";
}
        
void CardsDeck::addCard( const char* _name, int _priority ) {
    cards.push_back( Card(_name,_priority) );
    std::cout << "Added card ->\t{ name: " << _name << "\tpriority: " << _priority << "}\n";
}
    
void CardsDeck::showAll() {
    for ( std::list<Card>::const_iterator it = cards.begin();
          it != cards.end(); ++it ) {
        std::cout << it->getTitle() << " \t; " << it-> getPriority() <<'\n';
    }
}

static int luaNewCardsDeck(Lua::lua_State* LState) {
    using namespace Lua;
    
    int argn = lua_gettop(LState);
    if ( argn != 1 ) {
        return luaL_error(LState, "Got %d arguments, expected 1 ( class ) ", argn);
    }
    
    CardsDeck** p_cd = (CardsDeck**)lua_newuserdata(LState, sizeof(CardsDeck*));
    *p_cd = new CardsDeck();
    
    luaL_getmetatable(LState, "Helium.CardsDeck"); 
    lua_setmetatable(LState, -2);

    return 1;
}

static int luaAddCard( Lua::lua_State* LState ) {
    using namespace Lua;
    int argn = lua_gettop(LState);
    if ( argn!=3  && argn!=4 ) {
        return luaL_error(LState, "Got %d arguments, expected 2 or 3 ( CardsDeckClass, string, int ) ", argn);
    }
    
    const char* _name = luaL_checkstring(LState, 3);
    int _priority = 0;
    
    if ( argn == 4 ) {
        _priority = luaL_checknumber(LState, 4);
    }
    
    CardsDeck** p_cd = (CardsDeck**)luaL_checkudata(LState, 2, "Helium.CardsDeck");
    
    if ( p_cd == NULL && *p_cd == NULL )
        throw "null pointer";  
    
    (*p_cd)->addCard(_name, _priority);
    return 1;
}

static int luaShowAllCards( Lua::lua_State* LState ) {
    using namespace Lua;

    CardsDeck** p_cd = (CardsDeck**)luaL_checkudata(LState, 2, "Helium.CardsDeck");
    
    if ( p_cd == NULL && *p_cd == NULL )
        throw "null pointer";  
    
    (*p_cd)->showAll();
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
    
    luaL_newmetatable(LState, "Helium.CardsDeck");
    luaL_register(LState, "CardsDeck", gCardsDeckFunctions);
    
    return;
}


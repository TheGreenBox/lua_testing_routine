/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Helium
 * File name:  cardsDeck.h 
 * Description:
 * Author:  AKindyakov 
 * ========================================================
 */
#include <list>
#include "luaIncludes.h"

class Card
{
public:
    Card(const char* _name, int _level);
    const char* getTitle()const;
private:
    const char* name;
    int level;
};

class CardsDeck
{
public:
    CardsDeck();
        
    void addCard( const char* _name, int _level );
    
    void showAll();
    static void luaRegisterCardsDeck(Lua::lua_State*); 

private:
    std::list<Card> cards;
};


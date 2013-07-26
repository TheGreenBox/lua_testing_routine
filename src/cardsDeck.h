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
        
    void addCard( Card _card );
    
    void showAll();

private:
    std::list<Card> cards;
};


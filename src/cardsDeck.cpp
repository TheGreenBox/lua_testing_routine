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
        
void CardsDeck::addCard( Card _card ) {
    cards.push_back(_card);
}
    
void CardsDeck::showAll() {
    for ( std::list<Card>::const_iterator it = cards.begin();
          it != cards.end(); ++it ) {
        std::cout << it->getTitle() << '\n';
    }
}


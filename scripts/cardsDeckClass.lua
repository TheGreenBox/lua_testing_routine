--require "CardsDeck"

local deck = CardsDeck:new();

print ("\nLua: cardDeck");
for k,v in pairs(CardsDeck) do
    print(k);
end

CardsDeck:addCard(deck, "Jocker", 100);
CardsDeck:addCard(deck, "Diamonds King", 19);
CardsDeck:showAllCards(deck);

return deck;


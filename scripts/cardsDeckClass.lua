--require "CardsDeck"

local deck = CardsDeck:new();

for k,v in pairs(deck) do
    print(k);
end

deck:addCard("Jocker", 100);
deck:addCard("Diamonds King", 19);
deck:showAllCards();

return deck;


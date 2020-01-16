#ifndef _LOOTOBJECT_HPP
#define _LOOTOBJECT_HPP

#include "memory"
#include "character.hpp"
#include "objectStorage.hpp"
#include "gameObject.hpp"

class lootObject : public gameObject {
private:
    std::shared_ptr<gameObject> loot;
    character mainCharacter;
    std::map<std::string, sf::Texture> fakeTextureMap;
public:
    lootObject(const sf::Vector2f& position, character& mainCharacter, std::shared_ptr<gameObject> containedLoot):
        gameObject{position, sf::Vector2f(1,1), fakeTextureMap},
        loot{containedLoot},
        mainCharacter{mainCharacter}
    {
        sprite = loot.get()->getSprite();
    }

    void interact() override{
        mainCharacter.playerInventory.itemList->push_back(loot);
    }
};


#endif
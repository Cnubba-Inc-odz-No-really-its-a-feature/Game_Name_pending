#ifndef _LOOTOBJECT_HPP
#define _LOOTOBJECT_HPP

#include "memory"
#include "character.hpp"
#include "objectStorage.hpp"
#include "gameObject.hpp"
#include "inventory.hpp"

class lootObject : public gameObject {
private:
    std::shared_ptr<gameObject> loot;
    std::shared_ptr<gameObject> playerPointer;
    std::map<std::string, sf::Texture> fakeTextureMap;
    bool pickedUp = false;
public:
    lootObject(const sf::Vector2f& position, std::shared_ptr<gameObject> playerPointer, std::shared_ptr<gameObject> containedLoot):
        gameObject{position, sf::Vector2f(1,1), fakeTextureMap},
        loot{containedLoot},
        playerPointer{playerPointer}
    {
        sprite = loot.get()->getSprite();
    }

    void interact() override{
        playerPointer->addToInventory(loot);
        pickedUp = true;
    }

    bool isPickedUp(){
        return pickedUp;
    }

    void draw(sf::RenderWindow& window) override{
        window.draw(sprite);
    }
};


#endif
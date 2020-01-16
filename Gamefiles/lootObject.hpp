#ifndef _LOOTOBJECT_HPP
#define _LOOTOBJECT_HPP

#include "gameObject.hpp"
#include "memory"
#include "objectStorage.hpp"

class lootObject : public gameObject{
private:
    std::shared_ptr<gameObject> loot;
    std::map<std::string, sf::Texture> placeholderMap;
    objectStorage& storage;
public:
    lootObject(std::shared_ptr<gameObject> lootObject, const sf::Vector2f& position, objectStorage& storage):
        gameObject(position, sf::Vector2f(1,1), placeholderMap),
        storage{storage}
    {
        interactable = true;
        objectSprite = lootObject->objectSprite;
        lootObject->position = position;
    }

    void interact() override{
        storage.inventory->push_back(loot);
    }

    void draw(sf::RenderWindow& window) override{
        loot->draw(window);
    }

    void move(sf::Vector2f delta) override {}
    void update() override {};
};


#endif
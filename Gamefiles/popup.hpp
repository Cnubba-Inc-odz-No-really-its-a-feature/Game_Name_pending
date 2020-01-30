#include "random"
#include "vector"
#include "card.hpp"

class popup{
private:
    const sf::Vector2f & anker;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<std::shared_ptr<card>> Options;

public:
    popup(const sf::Vector2f & anker, std::string textureString, int prio);
    int update();
    void interact();
    void draw(sf::RenderWindow& gameWindow);
};
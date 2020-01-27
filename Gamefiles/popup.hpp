#include "gameObject.hpp"

class popup : public gameObject{
private:
    const sf::Vector2f & anker;
    //cards?

public:
    popup(const sf::Vector2f & anker);
    void interact();
    void draw(sf::RenderWindow& gameWindow);
    void move(sf::Vector2f moveDirection);
    virtual void setFrame(int maxFrame, int textureRow);
    void update();
};
#include "random"
#include "vector"
#include "card.hpp"

///\brief
/// popup reward choice from the chest
///\details
/// does not inheret from gameobject because its contained within the chest and does not need to be in the storage on its own
class popup{
private:
    const sf::Vector2f & anker;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<std::shared_ptr<card>> Options;

public:
    ///\brief
    /// Needs prio for knowing type of reward
    popup(const sf::Vector2f & anker, std::string textureString, int prio);

    ///\brief
    /// called every frame by chest, checks if the player has clicked on a card
    int update();

    ///\brief
    /// Does nothing, since interact cant be called by the comands
    void interact();

    ///\brief
    /// called every frame by chest, draws the 3 options of cards
    void draw(sf::RenderWindow& gameWindow);
};
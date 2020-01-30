#ifndef _UI_HPP
#define _UI_HPP
#include <SFML/Graphics.hpp>


class UI{
private:
    sf::Font mana_healthFont;
    sf::Text playerManaText;
    sf::Text playerHealthText;
    sf::Texture manaBarTexture;
    sf::Texture healthBarTexture;
    sf::Texture statsUITexture;
    sf::Texture enemyHPTexture;
    sf::Sprite manaBarSprite;
    sf::Sprite healthBarSprite;
    sf::Sprite statsUISprite;
    sf::Sprite enemyHPSprite;

    int_fast8_t & playerHP;
    int_fast8_t & enemyHP;
    int & playerMana;

public:

    UI(int_fast8_t & playerHP, int_fast8_t & enemyHP, int & playerMana):
    playerHP(playerHP),
    enemyHP(enemyHP),
    playerMana(playerMana){

        mana_healthFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        playerManaText.setFont(mana_healthFont);
        playerHealthText.setFont(mana_healthFont);
        playerManaText.setPosition(30, 600);
        playerHealthText.setPosition(30, 700);
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
        playerHealthText.setString("HP: " + std::to_string(playerHP));
        playerManaText.setFillColor(sf::Color::Blue);
        playerHealthText.setFillColor(sf::Color::Red);

        manaBarTexture.loadFromFile("gameAssets/manaBar.png");
        healthBarTexture.loadFromFile("gameAssets/hpBar.png");
        statsUITexture.loadFromFile("gameAssets/statsUI.png");
        enemyHPTexture.loadFromFile("gameAssets/enemyHP.png");

        manaBarSprite.setTexture(manaBarTexture);
        healthBarSprite.setTexture(healthBarTexture);
        statsUISprite.setTexture(statsUITexture);
        enemyHPSprite.setTexture(enemyHPTexture);

        manaBarSprite.setPosition(sf::Vector2f(20, 25));
        healthBarSprite.setPosition(sf::Vector2f(20, 22));
        statsUISprite.setPosition(sf::Vector2f(10, 20));
        enemyHPSprite.setPosition(sf::Vector2f(1000, 20));
        enemyHPSprite.setScale(sf::Vector2f(-1, 1));
    
    }

    void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(statsUISprite);
        gameWindow.draw(healthBarSprite);
        gameWindow.draw(manaBarSprite);
        gameWindow.draw(enemyHPSprite);
    }

    void updateUI(){
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
    }

};

#endif
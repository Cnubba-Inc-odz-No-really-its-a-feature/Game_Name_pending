#ifndef _UI_HPP
#define _UI_HPP
#include <SFML/Graphics.hpp>

#define HEALTH_BAR_OFFSET  105
#define MANA_BAR_OFFSET  170
#define MAX_HP 15
#define MAX_MANA 10

class UI{
private:
    sf::Font mana_healthFont;
    sf::Text playerManaText;
    sf::Text playerHealthText;
    sf::Text enemyHealthText;
    sf::Texture manaBarTexture;
    sf::Texture healthBarTexture;
    sf::Texture statsUITexture;
    sf::Texture enemyHPTexture;
    sf::Texture UIOverlayTexture;
    sf::Sprite manaBarSprite;
    sf::Sprite healthBarSprite;
    sf::Sprite statsUISprite;
    sf::Sprite enemyHPSprite;
    sf::Sprite enemyStatsUISprite;
    sf::Sprite enemyUIOverlaySprite;
    sf::Sprite UIOverlaySprite;

    sf::IntRect manaBarMaxBounds;
    sf::IntRect healthBarMaxBounds;

    int & playerHP;
    int & enemyHP;
    int & playerMana;

public:

    UI(int & playerHP, int & enemyHP, int & playerMana):
    playerHP(playerHP),
    enemyHP(enemyHP),
    playerMana(playerMana){

        mana_healthFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        playerManaText.setFont(mana_healthFont);
        playerHealthText.setFont(mana_healthFont);
        enemyHealthText.setFont(mana_healthFont);
        playerManaText.setPosition(25, 62);
        playerHealthText.setPosition(25, 20);
        enemyHealthText.setPosition(1850, 20);
        playerManaText.setString(std::to_string(playerMana));
        playerHealthText.setString(std::to_string(playerHP));
        enemyHealthText.setString(std::to_string(enemyHP));

        manaBarTexture.loadFromFile("gameAssets/manaBar.png");
        healthBarTexture.loadFromFile("gameAssets/hpBar.png");
        statsUITexture.loadFromFile("gameAssets/statsUI.png");
        enemyHPTexture.loadFromFile("gameAssets/hpBar.png");
        UIOverlayTexture.loadFromFile("gameAssets/UIOverlay.png");

        manaBarSprite.setTexture(manaBarTexture);
        healthBarSprite.setTexture(healthBarTexture);
        statsUISprite.setTexture(statsUITexture);
        enemyHPSprite.setTexture(enemyHPTexture);
        enemyUIOverlaySprite.setTexture(UIOverlayTexture);
        UIOverlaySprite.setTexture(UIOverlayTexture);
        enemyStatsUISprite.setTexture(statsUITexture);

        manaBarSprite.setPosition(sf::Vector2f(10, 63));
        healthBarSprite.setPosition(sf::Vector2f(10, 18));
        statsUISprite.setPosition(sf::Vector2f(10, 20));
        enemyHPSprite.setPosition(sf::Vector2f(1900, 19));
        enemyStatsUISprite.setPosition(sf::Vector2f(1900, 20));
        enemyUIOverlaySprite.setPosition(sf::Vector2f(1902, 13));
        UIOverlaySprite.setPosition(sf::Vector2f(8,13));
        enemyHPSprite.setScale(sf::Vector2f(-1, 1));
        enemyStatsUISprite.setScale(sf::Vector2f(-1,1));
        enemyUIOverlaySprite.setScale(sf::Vector2f(-1,1));
        auto manaBarBounds = manaBarSprite.getLocalBounds();
        manaBarMaxBounds = (sf::IntRect((int(manaBarBounds.left) + MANA_BAR_OFFSET ), int(manaBarBounds.top), (int(manaBarBounds.width) - MANA_BAR_OFFSET),  int(manaBarBounds.height)));
        manaBarSprite.setTextureRect(manaBarMaxBounds);

        auto healthBarBounds = healthBarSprite.getLocalBounds();
        healthBarMaxBounds = sf::IntRect(int(healthBarBounds.left) + HEALTH_BAR_OFFSET , int(healthBarBounds.top), (int(healthBarBounds.width) - HEALTH_BAR_OFFSET), int(healthBarBounds.height));
        healthBarSprite.setTextureRect(healthBarMaxBounds);
        enemyHPSprite.setTextureRect(healthBarMaxBounds);
    }

    void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(statsUISprite);
        gameWindow.draw(healthBarSprite);
        gameWindow.draw(manaBarSprite);
        gameWindow.draw(enemyStatsUISprite);
        gameWindow.draw(enemyHPSprite);
        gameWindow.draw(UIOverlaySprite);
        gameWindow.draw(enemyUIOverlaySprite);
        gameWindow.draw(playerManaText);
        gameWindow.draw(playerHealthText);
        gameWindow.draw(enemyHealthText);
    }

    void updateUI(){
        playerManaText.setString(std::to_string(playerMana));
        playerHealthText.setString(std::to_string(playerHP));
        enemyHealthText.setString(std::to_string(enemyHP));
        manaBarSprite.setTextureRect(sf::IntRect(manaBarMaxBounds.left, manaBarMaxBounds.top, 0 + (float)manaBarMaxBounds.width * (float)playerMana/MAX_MANA, manaBarMaxBounds.height));
        healthBarSprite.setTextureRect(sf::IntRect(healthBarMaxBounds.left, healthBarMaxBounds.top, 0 + (float)healthBarMaxBounds.width *(float)playerHP/MAX_HP, healthBarMaxBounds.height));
        enemyHPSprite.setTextureRect(sf::IntRect(healthBarMaxBounds.left, healthBarMaxBounds.top, 0 + (float)healthBarMaxBounds.width *(float)enemyHP/MAX_HP, healthBarMaxBounds.height));

    }

};

#endif
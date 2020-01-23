#ifndef _LANE_STRUCTS_HPP
#define _LANE_STRUCTS_HPP

#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"
#include "laneArrayContainer.hpp"

enum E_lane{
  skyLane, groundLane, trapLane  
};

struct unitUpdateResult{
    int selfPosition;
    int opponentPosition;

    bool openentKilled;
    bool selfKilled;
    bool valid;

    unitUpdateResult(bool valid, int selfPosition = 1, int opponentPosition = 1, bool oponentKilled = 1, bool selfKilled = 1):
        valid{valid},
        selfPosition{selfPosition},
        opponentPosition{opponentPosition},
        openentKilled{oponentKilled},
        selfKilled{selfKilled}
    {}


};

struct drawSprite{
    sf::Sprite sprite;
    sf::Vector2f position;

    drawSprite(){
        sprite = sf::Sprite();
        position = sf::Vector2f();
    }

    drawSprite(sf::Sprite sprite, const sf::Vector2f& position):
        sprite{sprite},
        position{position}
    {
        sprite.setPosition(position);
    }

    void update(sf::Sprite sprite, const sf::Vector2f& position){
        sprite = sprite;
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }
};


#endif
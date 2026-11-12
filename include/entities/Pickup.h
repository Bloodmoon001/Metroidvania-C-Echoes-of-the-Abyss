#pragma once
#include <SFML/Graphics.hpp>
#include "core/Vector2.h"

namespace game {
    class Pickup {
    public:
        Pickup(float x, float y);
        void Update(float dt, const std::vector<sf::FloatRect>& colliders);
        void Draw(sf::RenderWindow& window);
        sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
        bool IsCollected() const { return collected; }
        void Collect() { collected = true; }
        int GetValue() const { return value; }
    private:
        sf::Sprite sprite;
        bool collected = false;
        int value = 10;
        float velocityY = 0.0f;
    };
}

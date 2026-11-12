#include "entities/Pickup.h"

namespace game {
    sf::Texture& GetDropCoinTex() {
        static sf::Texture tex;
        static bool loaded = false;
        if (!loaded) {
            sf::Image img({16, 16}, sf::Color::Transparent);
            for (int y = 3; y < 13; ++y) for (int x = 5; x < 11; ++x) img.setPixel({(unsigned)x, (unsigned)y}, sf::Color(255, 215, 0));
            for (int x = 6; x < 10; ++x) { img.setPixel({(unsigned)x, 2}, sf::Color(200, 150, 0)); img.setPixel({(unsigned)x, 13}, sf::Color(200, 150, 0)); }
            for (int y = 3; y < 13; ++y) { img.setPixel({4, (unsigned)y}, sf::Color(200, 150, 0)); img.setPixel({11, (unsigned)y}, sf::Color(200, 150, 0)); }
            img.setPixel({6, 4}, sf::Color::White); img.setPixel({7, 4}, sf::Color::White);
            tex.loadFromImage(img); loaded = true;
        }
        return tex;
    }

    Pickup::Pickup(float x, float y) : sprite(GetDropCoinTex()) {
        sprite.setOrigin({8.0f, 8.0f});
        sprite.setScale({1.5f, 1.5f});
        sprite.setPosition({x, y});
    }

    void Pickup::Update(float dt, const std::vector<sf::FloatRect>& colliders) {
        if (collected) return;
        velocityY += 1800.0f * dt;
        sf::Vector2f pos = sprite.getPosition();
        pos.y += velocityY * dt;

        sf::FloatRect bounds = sprite.getGlobalBounds();
        bounds.position.y = pos.y;
        for (const auto& col : colliders) {
            if (bounds.findIntersection(col)) {
                if (velocityY > 0) {
                    pos.y = col.position.y - sprite.getGlobalBounds().size.y / 2.0f;
                    velocityY = 0;
                }
            }
        }
        sprite.setPosition(pos);
    }

    void Pickup::Draw(sf::RenderWindow& window) { 
        if (!collected) window.draw(sprite); 
    }
}

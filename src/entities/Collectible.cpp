#include "entities/Collectible.h"

namespace game {
    sf::Texture& Collectible::GetCoinTex() {
        static sf::Texture tex; static bool loaded = false;
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

    sf::Texture& Collectible::GetHerbTex() {
        static sf::Texture tex; static bool loaded = false;
        if (!loaded) {
            sf::Image img({16, 16}, sf::Color::Transparent);
            for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
                img.setPixel({(unsigned)(6 + i), (unsigned)(4 + j)}, sf::Color(50, 200, 50));
                img.setPixel({(unsigned)(3 + i), (unsigned)(2 + j)}, sf::Color(50, 200, 50));
                img.setPixel({(unsigned)(9 + i), (unsigned)(8 + j)}, sf::Color(50, 200, 50));
            }
            for (int y = 10; y < 15; ++y) img.setPixel({7, (unsigned)y}, sf::Color(139, 69, 19));
            tex.loadFromImage(img); loaded = true;
        }
        return tex;
    }

    sf::Texture& Collectible::GetOreTex() {
        static sf::Texture tex; static bool loaded = false;
        if (!loaded) {
            sf::Image img({16, 16}, sf::Color::Transparent);
            for (int y = 3; y < 13; ++y) for (int x = 3; x < 13; ++x) img.setPixel({(unsigned)x, (unsigned)y}, sf::Color(100, 100, 110));
            img.setPixel({5, 5}, sf::Color(0, 255, 255)); img.setPixel({6, 5}, sf::Color(0, 255, 255));
            img.setPixel({5, 6}, sf::Color(0, 255, 255)); img.setPixel({6, 6}, sf::Color(0, 255, 255));
            img.setPixel({9, 9}, sf::Color(0, 255, 255)); img.setPixel({10, 9}, sf::Color(0, 255, 255));
            img.setPixel({10, 10}, sf::Color(0, 255, 255));
            tex.loadFromImage(img); loaded = true;
        }
        return tex;
    }

    Collectible::Collectible(float x, float y, ItemType t) 
        : type(t), 
          sprite(t == ItemType::Coin ? GetCoinTex() : (t == ItemType::Herb ? GetHerbTex() : GetOreTex())) 
    {
        sprite.setOrigin({8.0f, 8.0f}); sprite.setScale({2.0f, 2.0f}); sprite.setPosition({x, y});
    }
    void Collectible::Draw(sf::RenderWindow& window) { if (!collected) window.draw(sprite); }
}

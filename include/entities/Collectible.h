#pragma once
#include <SFML/Graphics.hpp>
#include "core/Vector2.h"

namespace game {
    enum class ItemType { Coin, Herb, Ore };

    class Collectible {
    public:
        Collectible(float x, float y, ItemType type);
        void Draw(sf::RenderWindow& window);
        sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
        bool IsCollected() const { return collected; }
        void Collect() { collected = true; }
        ItemType GetType() const { return type; }

        // Статические методы для получения текстур (нужны для UI)
        static sf::Texture& GetCoinTex();
        static sf::Texture& GetHerbTex();
        static sf::Texture& GetOreTex();
    private:
        sf::Sprite sprite;
        bool collected = false;
        ItemType type;
    };
}

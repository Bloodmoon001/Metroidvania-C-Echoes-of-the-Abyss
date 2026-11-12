#pragma once
#include <SFML/Graphics.hpp>
#include "core/Vector2.h"
#include <vector>

namespace game {
    enum class EnemyType { Crawler, Bee, Bat, Slime, Shooter, Bomber, LaserShooter, IceShooter, VoidHorror };

    class Enemy {
    public:
        Enemy(float x, float y, sf::Texture& tex, EnemyType type = EnemyType::Crawler);
        void Update(float dt, const Vector2& playerPos, const std::vector<sf::FloatRect>& colliders);
        void Draw(sf::RenderWindow& window);
        void TakeDamage(float amount);
        bool IsAlive() const { return health > 0.0f && !isDead; }
        sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
        Vector2 GetPosition() const { return position; }
        EnemyType GetType() const { return type; }
        void Reset(float x, float y);

        bool justShot = false;
        bool isCharging = false;
        bool isFiring = false;
        Vector2 laserDir;
        float laserDistance = 800.0f;
        bool isDead = false;

    private:
        Vector2 position;
        Vector2 spawnPosition; // НОВОЕ: точка появления для привязки
        sf::Sprite sprite;
        EnemyType type;
        float health = 50.0f;
        float speed = 120.0f;
        float timeAlive = 0.0f;
        float shootTimer = 0.0f;
        float laserChargeTimer = 0.0f;
        float laserFireTimer = 0.0f;
        float damageFlashTimer = 0.0f;
    };
}
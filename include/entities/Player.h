#pragma once
#include <SFML/Graphics.hpp>
#include "core/Vector2.h"
#include <vector>

namespace game {
    enum class PlayerState { Idle, Run, Jump, Fall, Attack, Dash, WallSlide };

    class Player {
    public:
        Player(sf::Texture& tex);
        void Update(float dt, const std::vector<sf::FloatRect>& colliders);
        void Draw(sf::RenderWindow& window);

        // Полный сброс (новая игра) — сбрасывает HP и прокачку
        void Reset(float spawnX = 640.0f, float spawnY = 1800.0f);

        // Мягкий респавн с чекпоинта — сбрасывает HP, сохраняет прокачку
        void Respawn(float spawnX, float spawnY);

        // Просто перенос позиции без сброса HP/прокачки (для порталов)
        void Teleport(float x, float y);

        void SetLowGravity(bool enabled);
        void SetOnIce(bool onIce) { isOnIce = onIce; }

        float GetHealth() const { return health; }
        float GetMaxHealth() const { return maxHealth; }
        PlayerState GetState() const { return state; }
        Vector2 GetPosition() const { return position; }
        void SetPosition(Vector2 pos) { position = pos; }
        void SetHealth(float h) { health = h; }
        sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
        sf::FloatRect GetAttackBounds() const;
        void TakeDamage(float amount, bool ignoreInvuln = false);
        void Heal(float amount) { health += amount; if (health > maxHealth) health = maxHealth; }
        void Bounce() { velocity.y = -1100.0f; }
        void UpgradeWeapon() { weaponLevel++; attackDamage += 10.0f; }
        float GetAttackDamage() const { return attackDamage; }
        int GetWeaponLevel() const { return weaponLevel; }

        // true ровно один кадр в момент запуска нового взмаха
        bool JustStartedAttack() const { return justStartedAttack; }

    private:
        Vector2 position;
        Vector2 velocity;
        sf::Sprite sprite;

        float health = 100.0f;
        float maxHealth = 100.0f;
        float attackDamage = 10.0f;
        int weaponLevel = 1;
        float invulnTimer = 0.0f;
        PlayerState state = PlayerState::Idle;
        float facingRight = 1.0f;
        float attackTimer = 0.0f;

        float dashTimer = 0.0f;
        float dashCooldown = 0.0f;
        float dashDir = 1.0f;

        bool isWallSliding = false;
        float wallJumpLockout = 0.0f;
        float wallJumpDir = 1.0f;
        int jumpCount = 0;

        bool isOnIce = false;
        bool justStartedAttack = false;

        float speed = 350.0f;
        float currentGravity = 1800.0f;
        float currentJumpForce = -700.0f;
        bool isOnGround = false;
    };
}
#include "entities/Player.h"
#include "core/Input.h"
#include <cmath>
#include <algorithm>

namespace game {
    Player::Player(sf::Texture& tex) : sprite(tex) {
        Reset();
    }

    void Player::SetLowGravity(bool enabled) {
        if (enabled) {
            currentGravity = 600.0f;
            currentJumpForce = -650.0f;
        }
        else {
            currentGravity = 1800.0f;
            currentJumpForce = -700.0f;
        }
    }

    void Player::Reset(float spawnX, float spawnY) {
        position = { spawnX, spawnY };
        velocity = { 0.0f, 0.0f };
        health = 100.0f;
        attackDamage = 10.0f;
        weaponLevel = 1;
        invulnTimer = 0.0f;
        attackTimer = 0.0f;
        dashTimer = 0.0f;
        dashCooldown = 0.0f;
        wallJumpLockout = 0.0f;
        isWallSliding = false;
        isOnIce = false;
        justStartedAttack = false;
        state = PlayerState::Idle;
        isOnGround = false;
        jumpCount = 0;

        sprite.setTextureRect(sf::IntRect({ 48, 0 }, { 24, 24 }));
        sprite.setOrigin({ 12.0f, 12.0f });
        sprite.setScale({ 1.5f, 1.5f });
        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
        sprite.setColor(sf::Color::White);
    }

    void Player::Respawn(float spawnX, float spawnY) {
        position = { spawnX, spawnY };
        velocity = { 0.0f, 0.0f };
        health = maxHealth;                 // HP восстанавливается
        invulnTimer = 0.0f;
        attackTimer = 0.0f;
        dashTimer = 0.0f;
        dashCooldown = 0.0f;
        wallJumpLockout = 0.0f;
        isWallSliding = false;
        isOnIce = false;
        justStartedAttack = false;
        state = PlayerState::Idle;
        isOnGround = false;
        jumpCount = 0;
        // weaponLevel и attackDamage сохраняются
        sprite.setColor(sf::Color::White);
        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
    }

    void Player::Teleport(float x, float y) {
        position = { x, y };
        velocity = { 0.0f, 0.0f };
        state = PlayerState::Idle;
        isOnGround = false;
        jumpCount = 0;
        dashTimer = 0.0f;
        attackTimer = 0.0f;
        isWallSliding = false;
        justStartedAttack = false;
        // health, weaponLevel, attackDamage, invulnTimer НЕ трогаются
        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
    }

    sf::FloatRect Player::GetAttackBounds() const {
        if (state != PlayerState::Attack) return sf::FloatRect({ 0, 0 }, { 0, 0 });
        if (facingRight > 0) return sf::FloatRect({ position.x + 36.0f, position.y }, { 50.0f, 36.0f });
        else return sf::FloatRect({ position.x - 50.0f, position.y }, { 50.0f, 36.0f });
    }

    void Player::TakeDamage(float amount, bool ignoreInvuln) {
        if (!ignoreInvuln && (invulnTimer > 0.0f || state == PlayerState::Dash)) return;
        health -= amount;
        if (!ignoreInvuln) invulnTimer = 0.5f;
        if (health < 0) health = 0;
    }

    void Player::Update(float dt, const std::vector<sf::FloatRect>& colliders) {
        if (invulnTimer > 0.0f) invulnTimer -= dt;
        if (dashCooldown > 0.0f) dashCooldown -= dt;
        if (wallJumpLockout > 0.0f) wallJumpLockout -= dt;

        float dir = 0.0f;
        if (Input::IsLeft()) { dir -= 1.0f; facingRight = -1.0f; }
        if (Input::IsRight()) { dir += 1.0f; facingRight = 1.0f; }

        isWallSliding = false;
        if (!isOnGround && wallJumpLockout <= 0.0f && dashTimer <= 0.0f) {
            sf::FloatRect leftWall({ position.x - 4.0f, position.y + 5.0f }, { 4.0f, 26.0f });
            sf::FloatRect rightWall({ position.x + 36.0f, position.y + 5.0f }, { 4.0f, 26.0f });

            bool hitLeft = false, hitRight = false;
            for (const auto& col : colliders) {
                if (leftWall.findIntersection(col)) hitLeft = true;
                if (rightWall.findIntersection(col)) hitRight = true;
            }

            if (velocity.y > 0.0f) {
                if (hitLeft && dir < 0) { isWallSliding = true; wallJumpDir = 1.0f; }
                else if (hitRight && dir > 0) { isWallSliding = true; wallJumpDir = -1.0f; }
            }
        }

        if (Input::dashJustPressed && dashCooldown <= 0.0f && dashTimer <= 0.0f && !isWallSliding) {
            dashTimer = 0.15f; dashCooldown = 0.6f; dashDir = facingRight;
        }

        if (dashTimer > 0.0f) {
            dashTimer -= dt;
            velocity.x = dashDir * speed * 3.0f;
            velocity.y = 0.0f;
            state = PlayerState::Dash;
        }
        else {
            if (isOnIce && isOnGround) {
                if (dir != 0.0f) {
                    velocity.x += dir * speed * 4.0f * dt;
                    if (std::abs(velocity.x) > speed) velocity.x = dir * speed;
                }
                else {
                    if (velocity.x > 0) velocity.x -= 600.0f * dt;
                    else if (velocity.x < 0) velocity.x += 600.0f * dt;
                    if (std::abs(velocity.x) < 10.0f) velocity.x = 0;
                }
            }
            else {
                velocity.x = dir * speed;
            }

            if (Input::jumpJustPressed) {
                if (isOnGround) {
                    velocity.y = currentJumpForce;
                    isOnGround = false;
                    jumpCount = 1;
                }
                else if (isWallSliding) {
                    velocity.y = currentJumpForce;
                    velocity.x = wallJumpDir * speed * 1.5f;
                    wallJumpLockout = 0.2f;
                    isWallSliding = false;
                    facingRight = wallJumpDir;
                    jumpCount = 1;
                }
                else if (jumpCount < 2) {
                    velocity.y = currentJumpForce * 0.85f;
                    jumpCount = 2;
                }
            }

            if (isWallSliding) velocity.y = std::min(velocity.y + currentGravity * dt, 80.0f);
            else velocity.y += currentGravity * dt;
        }

        // Атака — фиксируем момент старта взмаха
        if (attackTimer > 0.0f) attackTimer -= dt;
        if (Input::IsAttack() && attackTimer <= 0.0f && state != PlayerState::Dash) {
            attackTimer = 0.3f;
            justStartedAttack = true;
        }
        else {
            justStartedAttack = false;
        }

        position.x += velocity.x * dt;
        sf::FloatRect bounds({ position.x, position.y }, { 36.0f, 36.0f });
        for (const auto& col : colliders) {
            if (bounds.findIntersection(col)) {
                if (velocity.x > 0) position.x = col.position.x - 36.0f;
                else if (velocity.x < 0) position.x = col.position.x + col.size.x;
                bounds.position.x = position.x;
            }
        }

        isOnGround = false;
        position.y += velocity.y * dt;
        bounds.position.y = position.y;
        for (const auto& col : colliders) {
            if (bounds.findIntersection(col)) {
                if (velocity.y > 0) {
                    position.y = col.position.y - 36.0f;
                    velocity.y = 0;
                    isOnGround = true;
                    jumpCount = 0;
                }
                else if (velocity.y < 0) {
                    position.y = col.position.y + col.size.y;
                    velocity.y = 0.0f;
                }
                bounds.position.y = position.y;
            }
        }

        if (dashTimer > 0.0f) state = PlayerState::Dash;
        else if (attackTimer > 0.0f) state = PlayerState::Attack;
        else if (isWallSliding) state = PlayerState::WallSlide;
        else if (!isOnGround) state = (velocity.y < 0) ? PlayerState::Jump : PlayerState::Fall;
        else if (dir != 0.0f) state = PlayerState::Run;
        else state = PlayerState::Idle;

        if (invulnTimer > 0.0f && (int)(invulnTimer * 20) % 2 == 0) sprite.setColor(sf::Color(255, 255, 255, 100));
        else sprite.setColor(sf::Color::White);

        if (state == PlayerState::Dash) sprite.setColor(sf::Color(0, 255, 255, 150));
        if (state == PlayerState::Attack) sprite.setColor(sf::Color(255, 100, 100));
        if (state == PlayerState::WallSlide) sprite.setColor(sf::Color(255, 255, 100));

        if (facingRight < 0) sprite.setScale({ -1.5f, 1.5f });
        else sprite.setScale({ 1.5f, 1.5f });

        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
    }

    void Player::Draw(sf::RenderWindow& window) {
        window.draw(sprite);
        if (state == PlayerState::Attack) {
            sf::RectangleShape sword({ 40.0f, 6.0f });
            sword.setFillColor(sf::Color::White);
            float xOffset = (facingRight > 0) ? 36.0f : -40.0f;
            sword.setPosition({ position.x + xOffset, position.y + 15.0f });
            window.draw(sword);
        }
    }
}
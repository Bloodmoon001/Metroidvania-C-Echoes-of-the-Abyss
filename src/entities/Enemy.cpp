#include "entities/Enemy.h"
#include <cmath>

namespace game {
    sf::Texture& GetIceWizardTex() {
        static sf::Texture tex;
        static bool loaded = false;
        if (!loaded) {
            sf::Image img({ 24, 24 }, sf::Color::Transparent);
            for (int y = 12; y < 22; ++y) { for (int x = 6; x < 18; ++x) { if (y == 21 && (x < 8 || x > 15)) continue; img.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(20, 40, 100)); } }
            for (int y = 2; y < 10; ++y) { for (int x = 8; x < 16; ++x) { if (y < 6 && (x < 10 || x > 13)) continue; img.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(30, 60, 140)); } }
            for (int y = 8; y < 12; ++y) { for (int x = 9; x < 15; ++x) { img.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(150, 220, 255)); } }
            img.setPixel({ 10, 9 }, sf::Color::Black); img.setPixel({ 13, 9 }, sf::Color::Black);
            for (int y = 4; y < 22; ++y) { img.setPixel({ 19, (unsigned)y }, sf::Color(80, 50, 30)); }
            for (int y = 2; y < 5; ++y) { for (int x = 18; x < 21; ++x) { img.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(0, 255, 255)); } }
            for (int x = 8; x < 16; ++x) img.setPixel({ (unsigned)x, 22 }, sf::Color(100, 200, 255));
            for (int x = 10; x < 14; ++x) img.setPixel({ (unsigned)x, 23 }, sf::Color(150, 220, 255));
            tex.loadFromImage(img);
            loaded = true;
        }
        return tex;
    }

    sf::Texture& GetVoidHorrorTex() {
        static sf::Texture tex;
        static bool loaded = false;
        if (!loaded) {
            sf::Image img({ 32, 32 }, sf::Color::Transparent);
            sf::Color bone(80, 80, 85);
            sf::Color darkBone(40, 40, 45);
            sf::Color eye(220, 220, 255);

            auto drawHead = [&](int hx, int hy) {
                for (int y = 0; y < 8; ++y)
                    for (int x = 0; x < 8; ++x)
                        img.setPixel({ (unsigned)(hx + x), (unsigned)(hy + y) }, (x == 0 || y == 0 || x == 7 || y == 7) ? darkBone : bone);
                img.setPixel({ (unsigned)(hx + 1), (unsigned)(hy + 3) }, eye);
                img.setPixel({ (unsigned)(hx + 2), (unsigned)(hy + 3) }, eye);
                img.setPixel({ (unsigned)(hx + 5), (unsigned)(hy + 3) }, eye);
                img.setPixel({ (unsigned)(hx + 6), (unsigned)(hy + 3) }, eye);
                for (int x = 1; x < 7; ++x)
                    img.setPixel({ (unsigned)(hx + x), (unsigned)(hy + 6) }, eye);
                };

            drawHead(2, 8);
            drawHead(12, 2);
            drawHead(22, 8);

            for (int y = 14; y < 30; ++y) {
                for (int x = 14; x < 18; ++x) {
                    img.setPixel({ (unsigned)x, (unsigned)y }, darkBone);
                }
            }
            for (int i = 0; i < 3; ++i) {
                int ry = 16 + i * 4;
                for (int x = 10; x < 22; ++x) {
                    if (x < 14 || x >= 18) {
                        img.setPixel({ (unsigned)x, (unsigned)ry }, bone);
                        img.setPixel({ (unsigned)x, (unsigned)(ry + 1) }, darkBone);
                    }
                }
            }
            for (int y = 30; y < 32; ++y) {
                for (int x = 12; x < 20; ++x) {
                    if (y == 30 || (y == 31 && x > 13 && x < 18)) {
                        img.setPixel({ (unsigned)x, (unsigned)y }, darkBone);
                    }
                }
            }
            tex.loadFromImage(img);
            loaded = true;
        }
        return tex;
    }

    Enemy::Enemy(float x, float y, sf::Texture& tex, EnemyType t) : sprite(tex), type(t) {
        if (type == EnemyType::Bee || type == EnemyType::Bat) {
            sprite.setTextureRect(sf::IntRect({ 96, 0 }, { 24, 24 }));
        }
        else if (type == EnemyType::Slime) {
            sprite.setTextureRect(sf::IntRect({ 144, 0 }, { 24, 24 }));
        }
        else if (type == EnemyType::Shooter) {
            sprite.setTextureRect(sf::IntRect({ 168, 48 }, { 24, 24 }));
        }
        else if (type == EnemyType::Bomber) {
            sprite.setTextureRect(sf::IntRect({ 192, 48 }, { 24, 24 }));
        }
        else if (type == EnemyType::LaserShooter) {
            sprite.setTextureRect(sf::IntRect({ 168, 48 }, { 24, 24 }));
            sprite.setColor(sf::Color(255, 100, 255));
            sprite.setScale({ 2.5f, 2.5f });
        }
        else if (type == EnemyType::IceShooter) {
            sprite.setTexture(GetIceWizardTex());
            sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 24, 24 }));
            sprite.setScale({ 1.5f, 1.5f });
        }
        else if (type == EnemyType::VoidHorror) {
            sprite.setTexture(GetVoidHorrorTex());
            sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
            sprite.setScale({ 1.5f, 1.5f });
            sprite.setOrigin({ 16.0f, 16.0f });
        }
        else {
            sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 24, 24 }));
        }

        if (type != EnemyType::LaserShooter && type != EnemyType::IceShooter && type != EnemyType::VoidHorror) {
            sprite.setOrigin({ 12.0f, 12.0f });
            sprite.setScale({ 1.5f, 1.5f });
        }
        else if (type == EnemyType::IceShooter) {
            sprite.setOrigin({ 12.0f, 12.0f });
        }
        else if (type == EnemyType::VoidHorror) {
            // Origin уже установлен
        }
        else {
            sprite.setOrigin({ 12.0f, 12.0f });
        }
        Reset(x, y);
    }

    void Enemy::Reset(float x, float y) {
        isDead = false;
        damageFlashTimer = 0.0f;
        position = { x, y };
        spawnPosition = { x, y }; // Запоминаем точку спавна
        justShot = false;
        shootTimer = 0.0f;
        timeAlive = 0.0f;
        isCharging = false;
        isFiring = false;
        laserDistance = 800.0f;

        if (type == EnemyType::Bee) { health = 10.0f; speed = 180.0f; }
        else if (type == EnemyType::Bat) { health = 15.0f; speed = 250.0f; }
        else if (type == EnemyType::Slime) { health = 30.0f; speed = 80.0f; }
        else if (type == EnemyType::Shooter) { health = 40.0f; speed = 0.0f; }
        else if (type == EnemyType::Bomber) { health = 20.0f; speed = 280.0f; }
        else if (type == EnemyType::LaserShooter) { health = 70.0f; speed = 0.0f; }
        else if (type == EnemyType::IceShooter) { health = 20.0f; speed = 0.0f; }
        else if (type == EnemyType::VoidHorror) { health = 30.0f; speed = 120.0f; } // УМЕНЬШЕНО HP
        else { health = 25.0f; speed = 120.0f; }

        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
        if (type != EnemyType::LaserShooter && type != EnemyType::IceShooter) sprite.setColor(sf::Color::White);
    }

    void Enemy::Update(float dt, const Vector2& playerPos, const std::vector<sf::FloatRect>& colliders) {
        if (damageFlashTimer > 0.0f) {
            damageFlashTimer -= dt;
            if (damageFlashTimer <= 0.0f && type != EnemyType::LaserShooter && type != EnemyType::IceShooter) {
                sprite.setColor(sf::Color::White);
            }
        }

        timeAlive += dt;
        Vector2 dir = playerPos - position;
        float dist = dir.length();

        if (type == EnemyType::IceShooter) {
            float hover = std::sin(timeAlive * 5.0f) * 8.0f;
            if (dist < 800.0f) {
                shootTimer += dt;
                if (shootTimer > 2.0f) { justShot = true; shootTimer = 0.0f; }
                if (dir.x < 0) sprite.setScale({ -1.5f, 1.5f });
                else sprite.setScale({ 1.5f, 1.5f });
            }
            sprite.setPosition({ position.x + 18.0f, position.y + 18.0f + hover });
            return;
        }

        if (type == EnemyType::VoidHorror) {
            float distToSpawn = Vector2::distance(position, spawnPosition);

            // Стрельба: только если игрок в радиусе видимости
            if (dist < 800.0f) {
                shootTimer += dt;
                if (shootTimer > 2.5f) { justShot = true; shootTimer = 0.0f; }
                if (dir.x < 0) sprite.setScale({ -1.5f, 1.5f });
                else sprite.setScale({ 1.5f, 1.5f });
            }
            else {
                shootTimer = 0.0f;
            }

            // Движение: привязка к точке спавна
            Vector2 moveTarget;
            bool shouldMove = false;

            if (distToSpawn > 400.0f) {
                // Если улетел слишком далеко от дома — возвращаемся
                moveTarget = spawnPosition;
                shouldMove = true;
            }
            else if (dist > 200.0f && dist < 1000.0f) {
                // Если игрок рядом — летим к нему
                moveTarget = playerPos;
                shouldMove = true;
            }

            if (shouldMove) {
                Vector2 moveDir = moveTarget - position;
                if (moveDir.length() > 20.0f) {
                    Vector2 norm = moveDir.normalized();
                    position.x += norm.x * speed * dt;
                    position.y += norm.y * speed * dt;
                    position.y += std::sin(timeAlive * 3.0f) * 50.0f * dt; // Эффект парения
                }
            }
            else {
                // Просто покачиваемся на месте
                position.y += std::sin(timeAlive * 3.0f) * 20.0f * dt;
            }

            sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
            return;
        }

        if (type == EnemyType::LaserShooter) {
            if (dist < 800.0f) {
                laserDir = dir.normalized();
                laserDistance = 800.0f;
                for (float d = 0; d < 800.0f; d += 20.0f) {
                    sf::Vector2f checkPos = { position.x + 18.0f + laserDir.x * d, position.y + 18.0f + laserDir.y * d };
                    bool hitWall = false;
                    for (const auto& col : colliders) {
                        if (col.contains(checkPos)) { hitWall = true; break; }
                    }
                    if (hitWall) { laserDistance = d; break; }
                }

                if (laserDistance < 50.0f) {
                    isCharging = false; isFiring = false; shootTimer = 0.0f;
                }
                else {
                    if (!isCharging && !isFiring) {
                        shootTimer += dt;
                        if (shootTimer > 2.0f) { isCharging = true; laserChargeTimer = 0.8f; shootTimer = 0.0f; }
                    }
                    else if (isCharging) {
                        laserChargeTimer -= dt;
                        if (laserChargeTimer <= 0) { isCharging = false; isFiring = true; laserFireTimer = 0.25f; }
                    }
                    else if (isFiring) {
                        laserFireTimer -= dt;
                        if (laserFireTimer <= 0) isFiring = false;
                    }
                }
                if (dir.x < 0) sprite.setScale({ -2.5f, 2.5f }); else sprite.setScale({ 2.5f, 2.5f });
            }
            else { isCharging = false; isFiring = false; shootTimer = 0.0f; }
        }
        else if (type == EnemyType::Shooter) {
            if (dist < 800.0f) {
                shootTimer += dt;
                if (shootTimer > 2.0f) { justShot = true; shootTimer = 0.0f; }
                if (dir.x < 0) sprite.setScale({ -1.5f, 1.5f }); else sprite.setScale({ 1.5f, 1.5f });
            }
        }
        else if (type == EnemyType::Bomber) {
            if (dist > 40.0f) { Vector2 norm = dir.normalized(); position += norm * speed * dt; if (norm.x < 0) sprite.setScale({ -1.5f, 1.5f }); else sprite.setScale({ 1.5f, 1.5f }); }
        }
        else if (type == EnemyType::Bee || type == EnemyType::Bat) {
            if (dist < 800.0f && dist > 20.0f) { Vector2 norm = dir.normalized(); float wave = (type == EnemyType::Bat) ? std::cos(timeAlive * 15.0f) * 150.0f * dt : std::sin(timeAlive * 10.0f) * 100.0f * dt; position.x += norm.x * speed * dt; position.y += norm.y * speed * dt + wave; if (norm.x < 0) sprite.setScale({ -1.5f, 1.5f }); else sprite.setScale({ 1.5f, 1.5f }); }
        }
        else if (type == EnemyType::Slime) {
            if (dist < 600.0f && timeAlive > 1.5f) { timeAlive = 0.0f; if (dir.x < 0) { position.x -= 100.0f; sprite.setScale({ -1.5f, 1.5f }); } else { position.x += 100.0f; sprite.setScale({ 1.5f, 1.5f }); } }
        }
        else {
            if (dist < 500.0f && dist > 40.0f) { Vector2 norm = dir.normalized(); position += norm * speed * dt; if (norm.x < 0) sprite.setScale({ -1.5f, 1.5f }); else sprite.setScale({ 1.5f, 1.5f }); }
        }

        sprite.setPosition({ position.x + 18.0f, position.y + 18.0f });
    }

    void Enemy::Draw(sf::RenderWindow& window) {
        window.draw(sprite);

        if (type == EnemyType::LaserShooter) {
            float angle = std::atan2(laserDir.y, laserDir.x) * 180.0f / 3.14159f;
            sf::Vector2f origin = { position.x + 18.0f, position.y + 18.0f };
            if (isCharging) { float alpha = (std::sin(timeAlive * 30.0f) + 1.0f) * 127.0f; sf::RectangleShape warn({ laserDistance, 2.0f }); warn.setOrigin({ 0, 1 }); warn.setPosition(origin); warn.setRotation(sf::degrees(angle)); warn.setFillColor(sf::Color(255, 0, 0, static_cast<std::uint8_t>(alpha))); window.draw(warn); }
            else if (isFiring) {
                sf::RectangleShape outerLaser({ laserDistance, 20.0f }); outerLaser.setOrigin({ 0, 10 }); outerLaser.setPosition(origin); outerLaser.setRotation(sf::degrees(angle)); outerLaser.setFillColor(sf::Color(255, 50, 150, 200)); window.draw(outerLaser);
                sf::RectangleShape coreLaser({ laserDistance, 6.0f }); coreLaser.setOrigin({ 0, 3 }); coreLaser.setPosition(origin); coreLaser.setRotation(sf::degrees(angle)); coreLaser.setFillColor(sf::Color::White); window.draw(coreLaser);
            }
        }

        sf::RectangleShape hpBg({ 36.0f, 4.0f });
        float hoverY = (type == EnemyType::IceShooter) ? std::sin(timeAlive * 5.0f) * 8.0f : 0.0f;
        hpBg.setPosition({ position.x, position.y - 10.0f + hoverY });
        hpBg.setFillColor(sf::Color(100, 0, 0)); window.draw(hpBg);

        float maxHp = 25.0f;
        if (type == EnemyType::Bee) maxHp = 10.0f;
        else if (type == EnemyType::Bat) maxHp = 15.0f;
        else if (type == EnemyType::Slime) maxHp = 30.0f;
        else if (type == EnemyType::Shooter) maxHp = 40.0f;
        else if (type == EnemyType::Bomber) maxHp = 20.0f;
        else if (type == EnemyType::LaserShooter) maxHp = 70.0f;
        else if (type == EnemyType::IceShooter) maxHp = 20.0f;
        else if (type == EnemyType::VoidHorror) maxHp = 30.0f; // Полоска здоровья тоже обновлена

        float hpPercent = health / maxHp; if (hpPercent < 0) hpPercent = 0;
        sf::RectangleShape hpBar({ 36.0f * hpPercent, 4.0f });
        hpBar.setPosition({ position.x, position.y - 10.0f + hoverY });
        hpBar.setFillColor(sf::Color(0, 255, 0)); window.draw(hpBar);
    }

    void Enemy::TakeDamage(float amount) {
        if (isDead) return;
        health -= amount;
        if (health < 0.0f) health = 0.0f;
        if (health <= 0.0f) return;

        damageFlashTimer = 0.1f;
        if (type != EnemyType::LaserShooter && type != EnemyType::IceShooter) {
            sprite.setColor(sf::Color(255, 100, 100));
        }
    }
}
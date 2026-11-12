#include "core/Game.h"
#include "core/Input.h"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace game {
    bool Input::jumpJustPressed = false;
    bool Input::dashJustPressed = false;
    bool Input::interactJustPressed = false;

    Game::Game(sf::Texture& pTex, sf::Texture& eTex, sf::Texture& bTex, sf::Texture& batT, sf::Texture& slTex, sf::Texture& tTex, sf::Texture& fTex)
        : window(sf::VideoMode({ 1280, 720 }), "Metroidvania C++"),
        playerTex(pTex), enemyTex(eTex), beeTex(bTex), batTex(batT), slimeTex(slTex), tileTex(tTex), forestTex(fTex),
        player(pTex), level(tTex, fTex)
    {
        window.setFramerateLimit(60);
        camera = sf::View(sf::FloatRect({ 0, 0 }, { 1280, 720 }));
        fontLoaded = font.openFromFile("assets/pixel_font.ttf");
        if (!fontLoaded) fontLoaded = font.openFromFile("C:/Windows/Fonts/consola.ttf");
        Restart();
    }

    void Game::SpawnEnemies() {
        enemies.clear();
        bullets.clear();

        if (level.GetCurrentType() == LevelType::Caves) {
            for (int i = 0; i < 12; ++i) {
                float rx = (i % 4) * 3840.f;
                float ry = (i / 4) * 2160.f;
                enemies.emplace_back(rx + 500, ry + 1800, enemyTex);
                enemies.emplace_back(rx + 1500, ry + 1800, batTex, EnemyType::Bat);
                if (i % 3 == 0) enemies.emplace_back(rx + 1000, ry + 1800, enemyTex, EnemyType::Shooter);
                if (i % 3 == 1) enemies.emplace_back(rx + 2500, ry + 1800, enemyTex, EnemyType::Bomber);
            }
        }
        else if (level.GetCurrentType() == LevelType::Forest) {
            for (int i = 0; i < 10; ++i) {
                float rx = (i % 5) * 3840.f;
                float ry = (i / 5) * 2160.f;
                enemies.emplace_back(rx + 800, ry + 1800, slimeTex, EnemyType::Slime);
                enemies.emplace_back(rx + 2000, ry + 1800, beeTex, EnemyType::Bee);
                if (i % 3 == 0) enemies.emplace_back(rx + 1500, ry + 1800, enemyTex, EnemyType::Shooter);
                if (i % 3 == 2) enemies.emplace_back(rx + 2500, ry + 1800, enemyTex, EnemyType::Bomber);
            }
        }
        else if (level.GetCurrentType() == LevelType::Moon) {
            for (int i = 0; i < 9; ++i) {
                float rx = (i % 3) * 3840.f;
                float ry = (i / 3) * 2160.f;
                enemies.emplace_back(rx + 800, ry + 1800, enemyTex, EnemyType::LaserShooter);
                enemies.emplace_back(rx + 2500, ry + 1800, enemyTex, EnemyType::LaserShooter);
                enemies.emplace_back(rx + 1500, ry + 1000, batTex, EnemyType::Bat);
            }
        }
        else if (level.GetCurrentType() == LevelType::IceCaves) {
            for (int i = 0; i < 8; ++i) {
                float rx = (i % 4) * 3840.f;
                float ry = (i / 4) * 2160.f;
                enemies.emplace_back(rx + 800, ry + 1800, enemyTex, EnemyType::IceShooter);
                enemies.emplace_back(rx + 2200, ry + 1800, enemyTex, EnemyType::IceShooter);
                if (i % 2 == 0) enemies.emplace_back(rx + 1500, ry + 1000, enemyTex, EnemyType::IceShooter);
            }
        }
        else if (level.GetCurrentType() == LevelType::Void) {
            for (int i = 0; i < 8; ++i) {
                float rx = (i % 4) * 3840.f;
                float ry = (i / 4) * 2160.f;
                // В бездне обитают Трехглавые ужасы
                enemies.emplace_back(rx + 1000, ry + 1800, enemyTex, EnemyType::VoidHorror);
                enemies.emplace_back(rx + 1800, ry + 1000, enemyTex, EnemyType::VoidHorror);
                enemies.emplace_back(rx + 2500, ry + 1800, enemyTex);   // Crawler
                if (i % 2 == 0) enemies.emplace_back(rx + 3200, ry + 1800, enemyTex, EnemyType::VoidHorror);
            }
        }
    }

    void Game::Restart() {
        player.Reset(respawnPos.x, respawnPos.y);
        collectibles.clear();
        pickups.clear();
        score = 0; coins = 0; herbs = 0; ores = 0;
        isGameOver = false; showFullMap = false; showInventory = false;
        teleportCooldown = 0.0f;

        level.LoadLevel(respawnLevel);
        player.SetLowGravity(respawnLevel == LevelType::Moon);
        SpawnEnemies();
        cameraPos = player.GetPosition();

        if (respawnLevel == LevelType::Caves) locationText = "Sinister Caves";
        else if (respawnLevel == LevelType::Forest) locationText = "Green Glade";
        else if (respawnLevel == LevelType::Moon) locationText = "Moonlight";
        else if (respawnLevel == LevelType::IceCaves) locationText = "Frozen Caves";
        else if (respawnLevel == LevelType::Void) locationText = "Distorted Abyss";
        locationTextTimer = 4.0f;

        if (respawnLevel == LevelType::Caves) {
            collectibles.emplace_back(1200, 1950, ItemType::Herb);
            collectibles.emplace_back(2100, 1550, ItemType::Ore);
        }
        else if (respawnLevel == LevelType::Forest) {
            collectibles.emplace_back(800, 1950, ItemType::Herb);
            collectibles.emplace_back(5000, 1950, ItemType::Herb);
        }
    }

    void Game::Respawn() {
        player.Respawn(respawnPos.x, respawnPos.y);
        collectibles.clear();
        pickups.clear();
        isGameOver = false;
        showFullMap = false;
        showInventory = false;
        teleportCooldown = 0.0f;

        level.LoadLevel(respawnLevel);
        player.SetLowGravity(respawnLevel == LevelType::Moon);
        SpawnEnemies();
        cameraPos = player.GetPosition();

        if (respawnLevel == LevelType::Caves) locationText = "Sinister Caves";
        else if (respawnLevel == LevelType::Forest) locationText = "Green Glade";
        else if (respawnLevel == LevelType::Moon) locationText = "Moonlight";
        else if (respawnLevel == LevelType::IceCaves) locationText = "Frozen Caves";
        else if (respawnLevel == LevelType::Void) locationText = "Distorted Abyss";
        locationTextTimer = 4.0f;
    }

    void Game::Run() {
        sf::Clock clock;
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;
            ProcessEvents();
            if (!isGameOver && !showFullMap && !showInventory) Update(dt);
            Render();
        }
    }

    void Game::ProcessEvents() {
        Input::Reset();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            Input::ProcessEvent(*event);

            if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) Respawn();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::M || key->code == sf::Keyboard::Key::Tab) showFullMap = !showFullMap;
                if (key->code == sf::Keyboard::Key::I) showInventory = !showInventory;
                if (key->code == sf::Keyboard::Key::H) {
                    if (herbs > 0 && player.GetHealth() < player.GetMaxHealth()) {
                        herbs--;
                        player.Heal(40.0f);
                    }
                }
                if (key->code == sf::Keyboard::Key::U) {
                    if (ores >= 3) {
                        ores -= 3;
                        player.UpgradeWeapon();
                    }
                }
            }
        }
    }

    void Game::UpdateCamera(float dt) {
        Vector2 pPos = player.GetPosition();
        const auto& rooms = level.GetRooms();
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i].bounds.contains({ pPos.x, pPos.y })) {
                currentRoomIndex = i;
                break;
            }
        }
        float smoothSpeed = 5.0f;
        cameraPos.x += (pPos.x - cameraPos.x) * smoothSpeed * dt;
        cameraPos.y += (pPos.y - cameraPos.y) * smoothSpeed * dt;
        camera.setCenter({ cameraPos.x, cameraPos.y });
    }

    void Game::Update(float dt) {
        player.SetOnIce(level.GetCurrentType() == LevelType::IceCaves);
        player.Update(dt, level.GetColliders());

        if (teleportCooldown > 0.0f) teleportCooldown -= dt;
        if (teleportCooldown <= 0.0f) {
            for (const auto& pad : level.GetTeleportPads()) {
                if (pad.trigger.findIntersection(player.GetBounds())) {
                    player.Teleport(pad.destination.x, pad.destination.y);
                    cameraPos = player.GetPosition();
                    camera.setCenter({ cameraPos.x, cameraPos.y });
                    teleportCooldown = 0.6f;
                    break;
                }
            }
        }

        level.Update(dt, player.GetPosition());
        UpdateCamera(dt);

        if (player.GetHealth() <= 0) {
            isGameOver = true;
            return;
        }
        sf::FloatRect pBounds = player.GetBounds();

        if (locationTextTimer > 0.0f) locationTextTimer -= dt;

        // 3. ТЕЛЕПОРТЫ МЕЖДУ ЛОКАЦИЯМИ (y = 1964.0f — безопасная высота спавна)
        if (level.GetCurrentType() == LevelType::Caves && pBounds.findIntersection(level.GetMoonPortalBounds())) {
            level.LoadLevel(LevelType::Moon); player.Teleport(400.0f, 1964.0f); player.SetLowGravity(true);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Moonlight"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::Moon && pBounds.findIntersection(level.GetPortalBounds())) {
            level.LoadLevel(LevelType::Caves); player.Teleport(400.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Sinister Caves"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::Forest && pBounds.findIntersection(level.GetPortalBounds())) {
            level.LoadLevel(LevelType::Caves); player.Teleport(14300.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Sinister Caves"; locationTextTimer = 4.0f; return;
        }
        // НОВЫЙ ПЕРЕХОД: Из Леса в Ледяные Пещеры
        else if (level.GetCurrentType() == LevelType::Forest && pBounds.findIntersection(level.GetIcePortalBounds())) {
            level.LoadLevel(LevelType::IceCaves); player.Teleport(400.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Frozen Caves"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::IceCaves && pBounds.findIntersection(level.GetPortalBounds())) {
            level.LoadLevel(LevelType::Caves); player.Teleport(1000.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Sinister Caves"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::IceCaves && pBounds.findIntersection(level.GetVoidPortalBounds())) {
            level.LoadLevel(LevelType::Void); player.Teleport(400.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Distorted Abyss"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::Void && pBounds.findIntersection(level.GetVoidPortalBounds())) {
            level.LoadLevel(LevelType::Caves); player.Teleport(1500.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Sinister Caves"; locationTextTimer = 4.0f; return;
        }
        else if (level.GetCurrentType() == LevelType::Caves && pBounds.findIntersection(level.GetPortalBounds())) {
            level.LoadLevel(LevelType::Forest); player.Teleport(400.0f, 1964.0f); player.SetLowGravity(false);
            SpawnEnemies(); collectibles.clear(); pickups.clear(); cameraPos = player.GetPosition();
            locationText = "Green Glade"; locationTextTimer = 4.0f; return;
        }

        const auto& fallingSpikes = level.GetFallingSpikes();
        for (size_t i = 0; i < fallingSpikes.size(); ++i) {
            if (fallingSpikes[i].isFalling && !fallingSpikes[i].isBroken) {
                if (fallingSpikes[i].bounds.findIntersection(player.GetBounds())) {
                    player.TakeDamage(20.0f);
                    level.BreakFallingSpike(i);
                }
            }
        }

        if (Input::interactJustPressed) {
            for (auto& cp : level.GetCheckpoints()) {
                if (!cp.isActivated && cp.bounds.findIntersection(player.GetBounds())) {
                    cp.isActivated = true;
                    cp.crystal.setFillColor(sf::Color(200, 50, 255));
                    cp.glow.setFillColor(sf::Color(200, 50, 255, 100));
                    respawnPos = sf::Vector2f(cp.bounds.position.x + 30.0f, cp.bounds.position.y + 120.0f - 36.0f);
                    respawnLevel = level.GetCurrentType();
                }
            }
            for (auto& chest : level.GetChests()) {
                if (!chest.isOpen && chest.bounds.findIntersection(player.GetBounds())) {
                    chest.isOpen = true; chest.shape.setFillColor(sf::Color(80, 40, 10));
                    collectibles.emplace_back(chest.bounds.position.x - 30.0f, chest.bounds.position.y - 50.0f, ItemType::Coin);
                    collectibles.emplace_back(chest.bounds.position.x + 30.0f, chest.bounds.position.y - 50.0f, ItemType::Herb);
                    collectibles.emplace_back(chest.bounds.position.x, chest.bounds.position.y - 80.0f, ItemType::Ore);
                }
            }
        }

        for (const auto& hazard : level.GetHazards()) {
            if (player.GetBounds().findIntersection(hazard)) player.TakeDamage(200.0f * dt, true);
        }
        for (const auto& spring : level.GetSprings()) {
            if (pBounds.findIntersection(spring)) player.Bounce();
        }
        for (const auto& spike : level.GetSpikes()) {
            if (pBounds.findIntersection(spike)) player.TakeDamage(20.0f);
        }

        for (size_t i = 0; i < enemies.size(); ++i) {
            auto& enemy = enemies[i];

            if (!enemy.IsAlive()) {
                if (!enemy.isDead) {
                    enemy.isDead = true;
                    pickups.emplace_back(enemy.GetPosition().x, enemy.GetPosition().y);
                }
                continue;
            }

            float dist = Vector2::distance(enemy.GetPosition(), player.GetPosition());
            if (dist > 1500.0f) continue;

            enemy.Update(dt, player.GetPosition(), level.GetColliders());

            if (enemy.isFiring) {
                sf::Vector2f ePos = { enemy.GetPosition().x + 18.0f, enemy.GetPosition().y + 18.0f };
                sf::Vector2f pPos = { player.GetPosition().x + 18.0f, player.GetPosition().y + 18.0f };
                sf::Vector2f d = pPos - ePos;
                float dot = d.x * enemy.laserDir.x + d.y * enemy.laserDir.y;
                if (dot > 0 && dot < enemy.laserDistance) {
                    float cross = std::abs(d.x * enemy.laserDir.y - d.y * enemy.laserDir.x);
                    if (cross < 15.0f) player.TakeDamage(15.0f);
                }
            }

            // СТРЕЛЬБА ВРАГОВ
            if (enemy.justShot) {
                enemy.justShot = false;

                if (enemy.GetType() == EnemyType::VoidHorror) {
                    // Трехглавый ужас стреляет тремя фиолетовыми снарядами веером
                    Vector2 dirToPlayer = player.GetPosition() - enemy.GetPosition();
                    float baseAngle = std::atan2(dirToPlayer.y, dirToPlayer.x);
                    for (int j = -1; j <= 1; ++j) {
                        Bullet b;
                        b.shape.setRadius(8.0f);
                        b.shape.setFillColor(sf::Color(200, 50, 255));
                        b.shape.setPosition({ enemy.GetPosition().x + 12.0f, enemy.GetPosition().y + 12.0f });
                        float angle = baseAngle + j * 15.0f * 3.14159f / 180.0f;
                        b.velocity = Vector2{ std::cos(angle), std::sin(angle) } * 400.0f;
                        bullets.push_back(b);
                    }
                }
                else {
                    Bullet b;
                    b.shape.setRadius(8.0f);
                    if (enemy.GetType() == EnemyType::IceShooter) b.shape.setFillColor(sf::Color(0, 255, 255));
                    else b.shape.setFillColor(sf::Color::Red);
                    b.shape.setPosition({ enemy.GetPosition().x + 12.0f, enemy.GetPosition().y + 12.0f });
                    Vector2 dirToPlayer = player.GetPosition() - enemy.GetPosition();
                    b.velocity = dirToPlayer.normalized() * 400.0f;
                    bullets.push_back(b);
                }
            }

            if (player.JustStartedAttack() && player.GetAttackBounds().findIntersection(enemy.GetBounds())) {
                enemy.TakeDamage(player.GetAttackDamage());
            }

            if (enemy.GetBounds().findIntersection(player.GetBounds())) {
                player.TakeDamage(20.0f);
            }
        }

        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->shape.move(sf::Vector2f(it->velocity.x * dt, it->velocity.y * dt));

            bool hitWall = false;
            for (const auto& col : level.GetColliders()) {
                if (it->shape.getGlobalBounds().findIntersection(col)) { hitWall = true; break; }
            }
            if (hitWall) { it = bullets.erase(it); continue; }

            if (it->shape.getGlobalBounds().findIntersection(player.GetBounds())) {
                player.TakeDamage(10.0f);
                it = bullets.erase(it);
                continue;
            }

            float distToPlayer = Vector2::distance(
                { it->shape.getPosition().x, it->shape.getPosition().y },
                player.GetPosition());
            if (distToPlayer > 2000.0f) { it = bullets.erase(it); continue; }

            ++it;
        }

        for (auto& item : collectibles) {
            if (!item.IsCollected() && item.GetBounds().findIntersection(player.GetBounds())) {
                item.Collect();
                if (item.GetType() == ItemType::Coin) { coins++; score += 50; }
                else if (item.GetType() == ItemType::Herb) herbs += 1;
                else if (item.GetType() == ItemType::Ore) ores += 1;
            }
        }
        for (auto& pickup : pickups) {
            pickup.Update(dt, level.GetColliders());
            if (!pickup.IsCollected() && pickup.GetBounds().findIntersection(player.GetBounds())) {
                pickup.Collect();
                score += pickup.GetValue();
                coins++;
            }
        }
    }

    void Game::DrawMinimap() {
        float mapW = 320.0f, mapH = 240.0f; float startX = 1280.0f - mapW - 20.0f, startY = 20.0f;
        sf::RectangleShape mapBg({ mapW, mapH }); mapBg.setPosition({ startX, startY }); mapBg.setFillColor(sf::Color(0, 0, 0, 180)); mapBg.setOutlineColor(sf::Color::White); mapBg.setOutlineThickness(3.0f); window.draw(mapBg);

        float worldW = (level.GetCurrentType() == LevelType::Caves || level.GetCurrentType() == LevelType::IceCaves || level.GetCurrentType() == LevelType::Void) ? 3840.f * 4.f : (level.GetCurrentType() == LevelType::Forest ? 3840.f * 5.f : 3840.f * 3.f);
        float worldH = (level.GetCurrentType() == LevelType::Caves || level.GetCurrentType() == LevelType::Moon) ? 2160.f * 3.f : 2160.f * 2.f;
        float scaleX = mapW / worldW, scaleY = mapH / worldH;

        const auto& rooms = level.GetRooms();
        for (const auto& room : rooms) {
            sf::RectangleShape r({ room.bounds.size.x * scaleX, room.bounds.size.y * scaleY });
            r.setPosition({ startX + room.bounds.position.x * scaleX, startY + room.bounds.position.y * scaleY });
            r.setFillColor(sf::Color(40, 40, 50)); r.setOutlineColor(sf::Color(80, 80, 80)); r.setOutlineThickness(1.0f); window.draw(r);
        }
        sf::CircleShape playerDot(4.0f);
        playerDot.setPosition({ startX + player.GetPosition().x * scaleX - 4.0f, startY + player.GetPosition().y * scaleY - 4.0f });
        playerDot.setFillColor(sf::Color::Red); window.draw(playerDot);
    }

    void Game::DrawFullMap() {
        sf::RectangleShape overlay({ 1280.0f, 720.0f }); overlay.setFillColor(sf::Color(0, 0, 0, 220)); window.draw(overlay);
        float mapW = 1000.0f, mapH = 600.0f; float startX = 140.0f, startY = 100.0f;
        sf::RectangleShape bg({ mapW, mapH }); bg.setPosition({ startX, startY }); bg.setFillColor(sf::Color(10, 10, 15, 100)); bg.setOutlineColor(sf::Color(50, 50, 50)); bg.setOutlineThickness(2.0f); window.draw(bg);

        float worldW = (level.GetCurrentType() == LevelType::Caves || level.GetCurrentType() == LevelType::IceCaves || level.GetCurrentType() == LevelType::Void) ? 3840.f * 4.f : (level.GetCurrentType() == LevelType::Forest ? 3840.f * 5.f : 3840.f * 3.f);
        float worldH = (level.GetCurrentType() == LevelType::Caves || level.GetCurrentType() == LevelType::Moon) ? 2160.f * 3.f : 2160.f * 2.f;
        float scaleX = mapW / worldW, scaleY = mapH / worldH;

        const auto& rooms = level.GetRooms();
        for (size_t i = 0; i < rooms.size(); ++i) {
            const auto& room = rooms[i];
            sf::RectangleShape r({ room.bounds.size.x * scaleX, room.bounds.size.y * scaleY });
            r.setPosition({ startX + room.bounds.position.x * scaleX, startY + room.bounds.position.y * scaleY });
            r.setFillColor(sf::Color(40, 40, 50)); r.setOutlineColor(sf::Color(80, 80, 80)); r.setOutlineThickness(2.0f); window.draw(r);
            if ((int)i == currentRoomIndex) {
                sf::RectangleShape current({ room.bounds.size.x * scaleX, room.bounds.size.y * scaleY });
                current.setPosition({ startX + room.bounds.position.x * scaleX, startY + room.bounds.position.y * scaleY });
                current.setFillColor(sf::Color::Transparent); current.setOutlineColor(sf::Color::Green); current.setOutlineThickness(5.0f); window.draw(current);
            }
        }
        sf::CircleShape playerDot(8.0f);
        playerDot.setPosition({ startX + player.GetPosition().x * scaleX - 8.0f, startY + player.GetPosition().y * scaleY - 8.0f });
        playerDot.setFillColor(sf::Color::Red); window.draw(playerDot);
    }

    void Game::Render() {
        sf::Color bgColor(20, 20, 30);
        if (level.GetCurrentType() == LevelType::Caves) bgColor = sf::Color(25, 22, 25);
        else if (level.GetCurrentType() == LevelType::Forest) bgColor = sf::Color(15, 30, 20);
        else if (level.GetCurrentType() == LevelType::Moon) bgColor = sf::Color(15, 15, 20);
        else if (level.GetCurrentType() == LevelType::IceCaves) bgColor = sf::Color(5, 15, 35);
        else if (level.GetCurrentType() == LevelType::Void) bgColor = sf::Color(10, 3, 20);

        window.clear(bgColor);
        window.setView(camera);
        level.Draw(window);

        for (auto& enemy : enemies) if (enemy.IsAlive()) enemy.Draw(window);
        for (const auto& b : bullets) window.draw(b.shape);
        for (auto& item : collectibles) item.Draw(window);
        for (auto& pickup : pickups) pickup.Draw(window);
        player.Draw(window);

        window.setView(window.getDefaultView());

        if (locationTextTimer > 0.0f && fontLoaded) {
            sf::Text locText(font, locationText, 64);
            locText.setStyle(sf::Text::Bold);
            locText.setOutlineThickness(4.0f);
            sf::FloatRect bounds = locText.getLocalBounds();
            locText.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
            locText.setPosition({ 640.0f, 360.0f });
            float alpha = 255.0f;
            if (locationTextTimer > 3.0f) alpha = 255.0f * (4.0f - locationTextTimer);
            else if (locationTextTimer < 1.0f) alpha = 255.0f * locationTextTimer;
            locText.setFillColor(sf::Color(255, 240, 200, static_cast<std::uint8_t>(alpha)));
            locText.setOutlineColor(sf::Color(50, 30, 10, static_cast<std::uint8_t>(alpha)));
            window.draw(locText);
        }

        for (int i = 0; i < 5; ++i) {
            float heartX = 20.0f + i * 35.0f; float heartY = 20.0f; float targetHealth = (i + 1) * 20.0f;
            sf::Color heartColor = sf::Color(50, 50, 50);
            if (player.GetHealth() >= targetHealth) heartColor = sf::Color(255, 50, 50);
            else if (player.GetHealth() > targetHealth - 20.0f) heartColor = sf::Color(255, 100, 100);
            sf::CircleShape c1(8.0f), c2(8.0f); c1.setFillColor(heartColor); c2.setFillColor(heartColor);
            c1.setPosition({ heartX, heartY }); c2.setPosition({ heartX + 10.0f, heartY }); window.draw(c1); window.draw(c2);
            sf::RectangleShape r({ 18.0f, 10.0f }); r.setFillColor(heartColor); r.setPosition({ heartX + 1.0f, heartY + 8.0f }); window.draw(r);
            sf::RectangleShape diamond({ 11.0f, 11.0f }); diamond.setFillColor(heartColor); diamond.setRotation(sf::degrees(45.0f)); diamond.setPosition({ heartX + 4.0f, heartY + 13.0f }); window.draw(diamond);
        }

        if (fontLoaded) {
            sf::Text scoreText(font, "Score: " + std::to_string(score), 24); scoreText.setPosition({ 20.0f, 50.0f }); scoreText.setFillColor(sf::Color::White); window.draw(scoreText);
            sf::Text wpnText(font, "Wpn Lvl: " + std::to_string(player.GetWeaponLevel()), 20); wpnText.setPosition({ 20.0f, 80.0f }); wpnText.setFillColor(sf::Color(200, 100, 100)); window.draw(wpnText);
        }

        if (!showFullMap) DrawMinimap();
        if (showFullMap) DrawFullMap();

        if (showInventory && fontLoaded) {
            sf::RectangleShape overlay({ 1280.0f, 720.0f }); overlay.setFillColor(sf::Color(0, 0, 0, 150)); window.draw(overlay);
            sf::RectangleShape invBg({ 600.0f, 300.0f }); invBg.setPosition({ 340.0f, 210.0f }); invBg.setFillColor(sf::Color(40, 40, 50, 240)); invBg.setOutlineColor(sf::Color::White); invBg.setOutlineThickness(3.0f); window.draw(invBg);

            sf::Text invTitle(font, "INVENTORY", 32);
            sf::FloatRect invBounds = invTitle.getLocalBounds();
            invTitle.setOrigin({ invBounds.position.x + invBounds.size.x / 2.0f, invBounds.position.y + invBounds.size.y / 2.0f });
            invTitle.setPosition({ 640.0f, 240.0f });
            invTitle.setFillColor(sf::Color::White); window.draw(invTitle);

            auto drawSlot = [&](float x, float y, sf::Texture& tex, int amount, const std::string& label) {
                sf::RectangleShape slot({ 80.0f, 80.0f }); slot.setPosition({ x, y }); slot.setFillColor(sf::Color(80, 80, 90)); slot.setOutlineColor(sf::Color(120, 120, 130)); slot.setOutlineThickness(2.0f); window.draw(slot);
                sf::Sprite icon(tex); icon.setOrigin({ 8.0f, 8.0f }); icon.setScale({ 2.5f, 2.5f }); icon.setPosition({ x + 40.0f, y + 35.0f }); window.draw(icon);
                sf::Text countText(font, std::to_string(amount), 20); countText.setPosition({ x + 55.0f, y + 55.0f }); countText.setFillColor(sf::Color::White); window.draw(countText);
                sf::Text labelText(font, label, 16); labelText.setPosition({ x - 10.0f, y + 85.0f }); labelText.setFillColor(sf::Color(180, 180, 180)); window.draw(labelText);
                };

            drawSlot(400.0f, 280.0f, Collectible::GetCoinTex(), coins, "Coins");
            drawSlot(500.0f, 280.0f, Collectible::GetHerbTex(), herbs, "Herbs");
            drawSlot(600.0f, 280.0f, Collectible::GetOreTex(), ores, "Ore");

            sf::Text actText1(font, "Press H to heal (Herbs)", 18); actText1.setPosition({ 400.0f, 400.0f }); actText1.setFillColor(sf::Color::Yellow); window.draw(actText1);
            sf::Text actText2(font, "Press U to upgrade (Cost: 3 Ore). You have: " + std::to_string(ores), 18); actText2.setPosition({ 400.0f, 425.0f }); actText2.setFillColor(sf::Color::Yellow); window.draw(actText2);
            sf::Text statText(font, "Weapon Lvl: " + std::to_string(player.GetWeaponLevel()) + " (DMG: " + std::to_string((int)player.GetAttackDamage()) + ")", 18); statText.setPosition({ 400.0f, 455.0f }); statText.setFillColor(sf::Color(200, 100, 100)); window.draw(statText);
        }

        if (isGameOver && fontLoaded) {
            sf::RectangleShape overlay({ 1280.0f, 720.0f }); overlay.setFillColor(sf::Color(0, 0, 0, 200)); window.draw(overlay);
            sf::Text gameOverText(font, "GAME OVER", 72);
            sf::FloatRect goBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin({ goBounds.position.x + goBounds.size.x / 2.0f, goBounds.position.y + goBounds.size.y / 2.0f });
            gameOverText.setPosition({ 640.0f, 320.0f });
            gameOverText.setFillColor(sf::Color::Red); window.draw(gameOverText);

            sf::Text restartText(font, "Press R to Respawn", 32);
            sf::FloatRect rBounds = restartText.getLocalBounds();
            restartText.setOrigin({ rBounds.position.x + rBounds.size.x / 2.0f, rBounds.position.y + rBounds.size.y / 2.0f });
            restartText.setPosition({ 640.0f, 420.0f });
            restartText.setFillColor(sf::Color::White); window.draw(restartText);
        }
        window.display();
    }
}
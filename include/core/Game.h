#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "entities/Player.h"
#include "entities/Level.h"
#include "entities/Enemy.h"
#include "entities/Pickup.h"
#include "entities/Collectible.h"

namespace game {
    struct Bullet { sf::CircleShape shape; Vector2 velocity; };

    class Game {
    public:
        Game(sf::Texture& pTex, sf::Texture& eTex, sf::Texture& bTex, sf::Texture& batT, sf::Texture& slTex, sf::Texture& tTex, sf::Texture& fTex);
        void Run();
    private:
        void ProcessEvents();
        void Update(float dt);
        void Render();
        void Restart();
        void Respawn();
        void SpawnEnemies();
        void UpdateCamera(float dt);
        void DrawMinimap();
        void DrawFullMap();

        sf::RenderWindow window;
        sf::View camera;
        Vector2 cameraPos;
        sf::Font font;
        bool fontLoaded = false;

        sf::Texture& playerTex;
        sf::Texture& enemyTex;
        sf::Texture& beeTex;
        sf::Texture& batTex;
        sf::Texture& slimeTex;
        sf::Texture& tileTex;
        sf::Texture& forestTex;

        Player player;
        Level level;
        std::vector<Enemy> enemies;
        std::vector<Bullet> bullets;
        std::vector<Pickup> pickups;
        std::vector<Collectible> collectibles;

        int score = 0;
        int coins = 0;
        int herbs = 0;
        int ores = 0;
        bool isGameOver = false;
        bool showFullMap = false;
        bool showInventory = false;
        int currentRoomIndex = -1;

        float teleportCooldown = 0.0f;   // анти-повторное срабатывание пада

        sf::Vector2f respawnPos = { 640.0f, 1800.0f };
        LevelType respawnLevel = LevelType::Caves;

        std::string locationText;
        float locationTextTimer = 0.0f;
    };
}
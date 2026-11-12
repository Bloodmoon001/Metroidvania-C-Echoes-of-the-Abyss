#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "core/Vector2.h"

namespace game {
    struct Room { sf::FloatRect bounds; bool explored = false; };
    struct Chest { sf::FloatRect bounds; bool isOpen = false; sf::RectangleShape shape; };
    struct Checkpoint { sf::FloatRect bounds; bool isActivated = false; sf::RectangleShape pillar; sf::ConvexShape crystal; sf::CircleShape glow; };
    struct FallingSpike { sf::FloatRect bounds; sf::FloatRect trigger; bool isFalling = false; bool isBroken = false; float speed = 800.0f; };

    // Парная телепорт-площадка: наступил на trigger → переместился в destination
    struct TeleportPad {
        sf::FloatRect trigger;
        sf::Vector2f destination;
        sf::RectangleShape shape;
    };

    enum class LevelType { Caves, Forest, Moon, IceCaves, Void };

    class Level {
    public:
        Level(sf::Texture& texCaves, sf::Texture& texForest);
        void LoadLevel(LevelType type);
        void Update(float dt, const Vector2& playerPos);
        void Draw(sf::RenderWindow& window);

        const std::vector<sf::FloatRect>& GetColliders() const { return colliders; }
        const std::vector<sf::FloatRect>& GetHazards() const { return hazards; }
        const std::vector<sf::FloatRect>& GetSprings() const { return springs; }
        const std::vector<sf::FloatRect>& GetSpikes() const { return spikes; }
        const std::vector<FallingSpike>& GetFallingSpikes() const { return fallingSpikes; }
        const std::vector<TeleportPad>& GetTeleportPads() const { return teleportPads; }

        void BreakFallingSpike(int index);

        std::vector<Chest>& GetChests() { return chests; }
        std::vector<Checkpoint>& GetCheckpoints() { return checkpoints; }
        const std::vector<Room>& GetRooms() const { return rooms; }
        sf::FloatRect GetPortalBounds() const { return portalBounds; }
        sf::FloatRect GetMoonPortalBounds() const { return moonPortalBounds; }
        sf::FloatRect GetIcePortalBounds() const { return icePortalBounds; }
        sf::FloatRect GetVoidPortalBounds() const { return voidPortalBounds; }
        LevelType GetCurrentType() const { return currentType; }
    private:
        std::vector<sf::FloatRect> colliders; std::vector<sf::FloatRect> hazards; std::vector<sf::FloatRect> springs; std::vector<sf::FloatRect> spikes;
        std::vector<FallingSpike> fallingSpikes;
        std::vector<TeleportPad> teleportPads;
        std::vector<Chest> chests;
        std::vector<Checkpoint> checkpoints;
        std::vector<sf::RectangleShape> shapes; std::vector<sf::RectangleShape> hazardShapes; std::vector<sf::RectangleShape> springShapes; std::vector<sf::RectangleShape> spikeShapes;
        std::vector<Room> rooms;

        sf::RectangleShape portalShape; sf::FloatRect portalBounds;
        sf::RectangleShape moonPortalShape; sf::FloatRect moonPortalBounds;
        sf::RectangleShape icePortalShape; sf::FloatRect icePortalBounds;
        sf::RectangleShape voidPortalShape; sf::FloatRect voidPortalBounds;

        sf::Texture& tileTexCaves; sf::Texture& tileTexForest;
        sf::Texture moonTex;
        sf::Texture spikeTex;
        sf::Texture springTex;
        sf::Texture iceTex;
        sf::Texture voidTex;

        LevelType currentType;

        void AddPlatform(float x, float y, float w, float h);
        void AddHazard(float x, float y, float w, float h);
        void AddSpring(float x, float y, float w, float h);
        void AddSpikes(float x, float y, float w, float h);
        void AddFallingSpike(float x, float y);
        void AddPortal(float x, float y);
        void AddMoonPortal(float x, float y);
        void AddIcePortal(float x, float y);
        void AddVoidPortal(float x, float y);
        void AddStairs(float startX, float startY, float endY);
        void AddChest(float x, float y);
        void AddCheckpoint(float x, float y);
        void AddTeleportPad(float fromX, float fromY, float toX, float toY);
    };
}
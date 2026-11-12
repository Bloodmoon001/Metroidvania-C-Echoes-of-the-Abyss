#include "entities/Level.h"
#include <cstdlib>
#include <cmath>

namespace game {
    Level::Level(sf::Texture& texCaves, sf::Texture& texForest) : tileTexCaves(texCaves), tileTexForest(texForest) {
        tileTexCaves.setRepeated(true); tileTexForest.setRepeated(true);

        sf::Image moonImg({ 32, 32 }, sf::Color(130, 130, 140));
        for (int i = 0; i < 120; ++i) { int x = rand() % 32; int y = rand() % 32; moonImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(90, 90, 100)); }
        for (int i = 0; i < 10; ++i) { int cx = rand() % 32; int cy = rand() % 32; for (int x = -2; x <= 2; ++x) for (int y = -2; y <= 2; ++y) { if (cx + x >= 0 && cx + x < 32 && cy + y >= 0 && cy + y < 32) moonImg.setPixel({ (unsigned)(cx + x), (unsigned)(cy + y) }, sf::Color(70, 70, 80)); } }
        moonTex.loadFromImage(moonImg); moonTex.setRepeated(true);

        sf::Image spikeImg({ 32, 32 }, sf::Color::Transparent);
        for (int y = 0; y < 32; ++y) { int halfWidth = (y * 16) / 31; for (int x = 0; x < 32; ++x) { int dist = std::abs(x - 16); if (dist <= halfWidth) { if (dist >= halfWidth - 2 && halfWidth > 2) spikeImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(100, 100, 110)); else spikeImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(180, 180, 190)); } } }
        spikeTex.loadFromImage(spikeImg); spikeTex.setRepeated(true);

        sf::Image springImg({ 64, 64 }, sf::Color::Transparent);
        for (int x = 4; x < 60; ++x) { for (int y = 4; y < 40; ++y) { if ((x < 10 || x > 54) && (y < 10 || y > 34)) continue; springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(30, 30, 30)); } }
        for (int x = 6; x < 58; ++x) { for (int y = 6; y < 38; ++y) { if ((x < 10 || x > 54) && (y < 10 || y > 34)) continue; springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(0, 150, 255)); } }
        for (int x = 16; x < 48; ++x) { for (int y = 14; y < 30; ++y) { if ((x + y) % 4 == 0 || (x - y) % 4 == 0) springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(40, 40, 40)); } }
        for (int y = 38; y < 62; ++y) { for (int x = 10; x < 18; ++x) springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(30, 30, 30)); for (int x = 12; x < 16; ++x) springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(150, 150, 150)); for (int x = 46; x < 54; ++x) springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(30, 30, 30)); for (int x = 48; x < 52; ++x) springImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(150, 150, 150)); }
        springTex.loadFromImage(springImg); springTex.setRepeated(true);

        sf::Image iceImg({ 32, 32 }, sf::Color(20, 50, 120));
        for (int x = 0; x < 32; ++x) { iceImg.setPixel({ (unsigned)x, 0 }, sf::Color(255, 255, 255)); iceImg.setPixel({ (unsigned)x, 1 }, sf::Color(230, 245, 255)); int snowDepth = 3 + (rand() % 6); for (int y = 2; y < snowDepth; ++y) iceImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(200, 230, 255)); }
        for (int i = 0; i < 15; ++i) { int startX = rand() % 32; int startY = 8 + (rand() % 24); int length = 2 + (rand() % 4); for (int j = 0; j < length; ++j) { if (startX + j < 32) iceImg.setPixel({ (unsigned)(startX + j), (unsigned)startY }, sf::Color(100, 200, 255)); } }
        for (int i = 0; i < 5; ++i) { int cx = rand() % 28; int cy = 10 + (rand() % 18); for (int x = 0; x < 3; ++x) for (int y = 0; y < 3; ++y) iceImg.setPixel({ (unsigned)(cx + x), (unsigned)(cy + y) }, sf::Color(0, 255, 255)); iceImg.setPixel({ (unsigned)cx, (unsigned)cy }, sf::Color(255, 255, 255)); }
        iceTex.loadFromImage(iceImg); iceTex.setRepeated(true);

        sf::Image voidImg({ 32, 32 }, sf::Color(25, 5, 40));
        for (int i = 0; i < 200; ++i) { int x = rand() % 32; int y = rand() % 32; voidImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(15, 0, 25)); }
        for (int i = 0; i < 15; ++i) {
            int x = rand() % 32; int y = rand() % 32; int len = 3 + rand() % 8;
            bool horizontal = rand() % 2 == 0;
            for (int j = 0; j < len; ++j) {
                int px = horizontal ? (x + j) : x;
                int py = horizontal ? y : (y + j);
                if (px >= 0 && px < 32 && py >= 0 && py < 32)
                    voidImg.setPixel({ (unsigned)px, (unsigned)py }, sf::Color(100, 20, 160));
            }
        }
        for (int i = 0; i < 8; ++i) {
            int x = 3 + rand() % 26; int y = 3 + rand() % 26;
            voidImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(200, 100, 255));
            voidImg.setPixel({ (unsigned)(x - 1), (unsigned)y }, sf::Color(150, 50, 200));
            voidImg.setPixel({ (unsigned)(x + 1), (unsigned)y }, sf::Color(150, 50, 200));
            voidImg.setPixel({ (unsigned)x, (unsigned)(y - 1) }, sf::Color(150, 50, 200));
            voidImg.setPixel({ (unsigned)x, (unsigned)(y + 1) }, sf::Color(150, 50, 200));
        }
        voidTex.loadFromImage(voidImg); voidTex.setRepeated(true);

        LoadLevel(LevelType::Caves);
    }

    void Level::Update(float dt, const Vector2& playerPos) {
        for (auto& fs : fallingSpikes) {
            if (!fs.isFalling && !fs.isBroken) {
                if (fs.trigger.contains({ playerPos.x + 18.0f, playerPos.y + 18.0f })) { fs.isFalling = true; }
            }
            if (fs.isFalling && !fs.isBroken) {
                fs.bounds.position.y += fs.speed * dt;
                for (const auto& col : colliders) { if (fs.bounds.findIntersection(col)) { fs.isBroken = true; break; } }
                if (fs.bounds.position.y > 4160.0f) { fs.isBroken = true; }
            }
        }
    }

    void Level::BreakFallingSpike(int index) {
        if (index >= 0 && index < fallingSpikes.size()) fallingSpikes[index].isBroken = true;
    }

    void Level::LoadLevel(LevelType type) {
        currentType = type; colliders.clear(); hazards.clear(); springs.clear(); spikes.clear(); fallingSpikes.clear(); teleportPads.clear(); chests.clear(); checkpoints.clear(); shapes.clear(); hazardShapes.clear(); springShapes.clear(); spikeShapes.clear(); rooms.clear();
        portalBounds = sf::FloatRect({ 0,0 }, { 0,0 }); moonPortalBounds = sf::FloatRect({ 0,0 }, { 0,0 }); icePortalBounds = sf::FloatRect({ 0,0 }, { 0,0 }); voidPortalBounds = sf::FloatRect({ 0,0 }, { 0,0 });

        if (type == LevelType::IceCaves) {
            for (int y = 0; y < 2; ++y) { for (int x = 0; x < 4; ++x) { Room r; r.bounds = sf::FloatRect({ (float)(x * 3840), (float)(y * 2160) }, { 3840.f, 2160.f }); rooms.push_back(r); } }
            float worldW = 3840.f * 4.f; float worldH = 2160.f * 2.f;
            AddPlatform(-50, 0, 50, worldH); AddPlatform(worldW, 0, 50, worldH); AddPlatform(0, -50, worldW, 50); AddPlatform(0, worldH, worldW, 50);

            AddPlatform(0, 2000, 1200, 160);
            AddPortal(200, 1872); // Возврат в Пещеры
            AddCheckpoint(600, 2000);
            AddStairs(1250, 2000, 4160);
            AddPlatform(1600, 2000, 2240, 160);

            AddPlatform(1800, 1850, 200, 30);
            AddPlatform(2100, 1700, 200, 30);
            AddPlatform(2400, 1550, 300, 30);
            AddChest(2500, 1500);

            AddFallingSpike(1900, 1880);
            AddFallingSpike(2200, 1730);
            AddFallingSpike(2550, 1580);

            AddPlatform(3840, 2000, 2000, 160);
            AddCheckpoint(4200, 2000);
            AddStairs(5900, 2000, 4160);
            AddPlatform(6200, 2000, 1480, 160);

            AddPlatform(4200, 1850, 200, 30);
            AddPlatform(4500, 1700, 200, 30);
            AddPlatform(4900, 1550, 200, 30);
            AddPlatform(5300, 1700, 200, 30);
            AddPlatform(5600, 1850, 200, 30);
            AddChest(4950, 1500);

            AddFallingSpike(4300, 1880);
            AddFallingSpike(4600, 1730);
            AddFallingSpike(5000, 1580);
            AddFallingSpike(5400, 1730);

            AddPlatform(7680, 2000, 3840, 160);
            AddPlatform(8200, 1850, 200, 30);
            AddPlatform(8500, 1700, 200, 30);
            AddPlatform(8900, 1550, 200, 30);
            AddPlatform(9300, 1400, 200, 30);
            AddChest(9400, 1350);

            AddFallingSpike(8300, 1880);
            AddFallingSpike(8600, 1730);
            AddFallingSpike(9000, 1580);

            AddPlatform(11520, 2000, 3840, 160);
            AddCheckpoint(11800, 2000);
            AddPlatform(12400, 1800, 200, 30);
            AddFallingSpike(12500, 1830);

            AddCheckpoint(14500, 2000);
            AddVoidPortal(14900, 1872); // Портал в Бездну

            AddPlatform(0, 4160, 15360, 160);
            AddCheckpoint(600, 4160);
            AddHazard(4000, 4160, 800, 160);
            AddHazard(10000, 4160, 1000, 160);

            AddPlatform(4200, 4000, 400, 30);
            AddPlatform(10200, 4000, 500, 30);

            AddFallingSpike(4400, 4030);
            AddFallingSpike(10500, 4030);

            AddChest(2000, 4110);
            AddChest(8000, 4110);
            AddCheckpoint(9000, 4160);
            AddChest(13000, 4110);
        }
        else if (type == LevelType::Caves) {
            for (int y = 0; y < 3; ++y) { for (int x = 0; x < 4; ++x) { Room r; r.bounds = sf::FloatRect({ (float)(x * 3840), (float)(y * 2160) }, { 3840.f, 2160.f }); rooms.push_back(r); } }
            float worldW = 3840.f * 4.f; float worldH = 2160.f * 3.f;
            AddPlatform(-50, 0, 50, worldH); AddPlatform(worldW, 0, 50, worldH); AddPlatform(0, -50, worldW, 50); AddPlatform(0, worldH, worldW, 50);

            AddMoonPortal(200, 1872); // Портал в Лунную локацию
            AddPlatform(0, 2000, 1800, 160); AddPlatform(2100, 2000, 1740, 160); AddStairs(1850, 2000, 4160); AddSpring(500, 1950, 60, 50); AddSpikes(800, 1970, 100, 30);
            AddChest(1200, 1950); AddChest(8000, 1950); AddChest(12500, 1950); AddCheckpoint(400, 2000);
            AddPlatform(3840, 2000, 660, 160); AddPlatform(5100, 2000, 2580, 160); AddPlatform(4500, 2060, 600, 100); AddHazard(4500, 2000, 600, 60); AddStairs(5850, 2000, 4160);
            AddChest(4000, 1950); AddChest(10000, 1950); AddChest(5000, 4110); AddChest(12000, 4110);
            AddPlatform(7680, 2000, 2120, 160); AddPlatform(10100, 2000, 1420, 160); AddStairs(9850, 2000, 4160); AddSpring(8500, 1950, 60, 50);
            AddPlatform(11520, 2000, 2280, 160); AddPlatform(14100, 2000, 1260, 160); AddStairs(13850, 2000, 4160); AddPortal(14200, 1872); // Портал в Лес в конце
            AddPlatform(0, 4160, 1800, 160); AddPlatform(2100, 4160, 1740, 160); AddStairs(1850, 4160, 6320); AddSpikes(500, 4130, 100, 30);
            AddPlatform(3840, 4160, 1960, 160); AddPlatform(6100, 4160, 1580, 160); AddStairs(5850, 4160, 6320); AddSpring(4200, 4110, 60, 50);
            AddPlatform(7680, 4160, 820, 160); AddPlatform(9000, 4160, 2520, 160); AddPlatform(8500, 4220, 500, 100); AddHazard(8500, 4160, 500, 60); AddStairs(9850, 4160, 6320);
            AddPlatform(11520, 4160, 2280, 160); AddPlatform(14100, 4160, 1260, 160); AddStairs(13850, 4160, 6320); AddSpikes(12000, 4130, 100, 30);
            AddPlatform(0, 6320, 15360, 160); AddSpring(3000, 6270, 60, 50); AddSpikes(6000, 6290, 800, 30); AddSpring(10000, 6270, 60, 50); AddSpikes(13000, 6290, 400, 30);
        }
        else if (type == LevelType::Forest) {
            // ЭТОТ БЛОК БЫЛ ПОТЕРЯН! Теперь он на месте.
            for (int y = 0; y < 2; ++y) { for (int x = 0; x < 5; ++x) { Room r; r.bounds = sf::FloatRect({ (float)(x * 3840), (float)(y * 2160) }, { 3840.f, 2160.f }); rooms.push_back(r); } }
            float worldW = 3840.f * 5.f; float worldH = 2160.f * 2.f;
            AddPlatform(-50, 0, 50, worldH); AddPlatform(worldW, 0, 50, worldH); AddPlatform(0, -50, worldW, 50); AddPlatform(0, worldH, worldW, 50);

            AddPlatform(0, 2000, 3800, 160); AddPlatform(4100, 2000, 3500, 160); AddStairs(3850, 2000, 4160); AddPortal(200, 1872); AddSpikes(1000, 1970, 100, 30); AddSpring(2000, 1950, 60, 50);
            AddChest(1500, 1950); AddChest(5000, 1950); AddChest(12000, 1950); AddChest(16000, 1950); AddChest(5000, 4110); AddCheckpoint(400, 2000);
            AddPlatform(7900, 2000, 600, 160); AddPlatform(9000, 2000, 2400, 160); AddPlatform(8500, 2060, 500, 100); AddHazard(8500, 2000, 500, 60); AddStairs(7650, 2000, 4160);
            AddPlatform(11700, 2000, 3500, 160); AddStairs(11450, 2000, 4160); AddSpikes(12000, 1970, 200, 30);
            AddPlatform(15500, 2000, 3700, 160); AddStairs(15250, 2000, 4160); AddSpring(16000, 1950, 60, 50);

            AddCheckpoint(18000, 2000);
            AddIcePortal(18700, 1872); // Портал в Ледяные пещеры

            AddPlatform(0, 4160, 19200, 160); AddHazard(3000, 4160, 800, 160); AddHazard(10000, 4160, 1000, 160); AddSpikes(6000, 4130, 300, 30); AddSpring(15000, 4110, 60, 50);
        }
        else if (type == LevelType::Moon) {
            for (int y = 0; y < 3; ++y) { for (int x = 0; x < 3; ++x) { Room r; r.bounds = sf::FloatRect({ (float)(x * 3840), (float)(y * 2160) }, { 3840.f, 2160.f }); rooms.push_back(r); } }
            float worldW = 3840.f * 3.f; float worldH = 2160.f * 3.f;
            AddPlatform(-50, 0, 50, worldH); AddPlatform(worldW, 0, 50, worldH); AddPlatform(0, -50, worldW, 50); AddPlatform(0, worldH, worldW, 50);
            AddPlatform(0, 2000, 1500, 160); AddPlatform(1800, 2000, 2040, 160); AddStairs(1550, 2000, 4160); AddPortal(200, 1872); AddPlatform(400, 1600, 600, 40);
            AddChest(1000, 1950); AddSpikes(2500, 1970, 100, 30); AddCheckpoint(600, 2000);
            AddPlatform(3840, 2000, 2000, 160); AddPlatform(6140, 2000, 1540, 160); AddStairs(5900, 2000, 4160); AddChest(4500, 1950); AddSpikes(7000, 1970, 150, 30);
            AddPlatform(7680, 2000, 1500, 160); AddPlatform(9480, 2000, 2040, 160); AddStairs(9200, 2000, 4160); AddChest(8500, 1950);
            AddPlatform(0, 4160, 2000, 160); AddPlatform(2300, 4160, 1540, 160); AddStairs(2050, 4160, 6320); AddChest(1500, 4110); AddSpikes(3000, 4130, 100, 30);
            AddPlatform(3840, 4160, 1500, 160); AddPlatform(5640, 4160, 2040, 160); AddStairs(5400, 4160, 6320); AddChest(6000, 4110); AddSpikes(7000, 4130, 100, 30);
            AddPlatform(7680, 4160, 2000, 160); AddPlatform(9980, 4160, 1540, 160); AddStairs(9700, 4160, 6320); AddChest(8500, 4110);
            AddPlatform(0, 6320, 11520, 160); AddChest(2000, 6270); AddChest(8000, 6270); AddSpikes(4000, 6290, 200, 30); AddSpikes(9000, 6290, 150, 30);
            AddPlatform(1500, 5800, 400, 30); AddPlatform(6000, 5800, 400, 30); AddPlatform(10000, 5800, 400, 30);
        }
        else if (type == LevelType::Void) {
            for (int y = 0; y < 2; ++y) { for (int x = 0; x < 4; ++x) { Room r; r.bounds = sf::FloatRect({ (float)(x * 3840), (float)(y * 2160) }, { 3840.f, 2160.f }); rooms.push_back(r); } }
            float worldW = 3840.f * 4.f; float worldH = 2160.f * 2.f;
            AddPlatform(-50, 0, 50, worldH); AddPlatform(worldW, 0, 50, worldH); AddPlatform(0, -50, worldW, 50); AddPlatform(0, worldH, worldW, 50);

            // ===== ЭТАЖ 1 (y=2000) =====
            AddPlatform(0, 2000, 1500, 160);
            AddVoidPortal(200, 1872);
            AddCheckpoint(600, 2000);

            AddStairs(1250, 2000, 4160);

            AddPlatform(1600, 2000, 2240, 160);
            AddPlatform(1800, 1700, 200, 30);
            AddPlatform(2100, 1500, 200, 30);
            AddPlatform(2400, 1300, 300, 30);
            AddChest(2500, 1250);
            AddTeleportPad(3400, 1970, 1850, 1450);

            AddPlatform(3840, 2000, 660, 160);
            AddCheckpoint(4200, 2000);
            AddPlatform(4500, 2060, 600, 100);
            AddHazard(4500, 2000, 600, 60);
            AddPlatform(5100, 2000, 2580, 160);

            AddPlatform(5400, 1850, 200, 30);
            AddPlatform(5800, 1700, 200, 30);
            AddPlatform(6200, 1550, 200, 30);
            AddChest(6300, 1500);

            AddTeleportPad(4000, 1970, 5200, 1950);

            AddPlatform(7680, 2000, 3840, 160);
            AddCheckpoint(8000, 2000);

            AddPlatform(8200, 1850, 200, 30);
            AddPlatform(8600, 1700, 200, 30);
            AddPlatform(9000, 1550, 200, 30);
            AddPlatform(9400, 1400, 200, 30);
            AddChest(9500, 1350);

            AddPlatform(11520, 2000, 3840, 160);
            AddCheckpoint(11800, 2000);

            AddTeleportPad(12500, 1970, 13000, 1500);
            AddPlatform(12800, 1500, 300, 30);
            AddChest(12900, 1450);

            AddStairs(14700, 2000, 4160);

            // ===== ЭТАЖ 2 (y=4160) =====
            AddCheckpoint(600, 4160);

            AddPlatform(0, 4160, 2000, 160);
            AddPlatform(2000, 4220, 1000, 100);
            AddPlatform(3000, 4160, 3000, 160);
            AddPlatform(6000, 4220, 800, 100);
            AddPlatform(6800, 4160, 3700, 160);
            AddPlatform(10500, 4220, 1000, 100);
            AddPlatform(11500, 4160, 3860, 160);

            AddHazard(2000, 4160, 1000, 60);
            AddHazard(6000, 4160, 800, 60);
            AddHazard(10500, 4160, 1000, 60);

            AddPlatform(2200, 4000, 400, 30);
            AddPlatform(6200, 4000, 400, 30);
            AddPlatform(10800, 4000, 500, 30);

            AddChest(1500, 4110);
            AddCheckpoint(5000, 4160);
            AddChest(8000, 4110);
            AddCheckpoint(9000, 4160);
            AddChest(13000, 4110);

            AddTeleportPad(1800, 4130, 3300, 4100);
            AddTeleportPad(5800, 4130, 7000, 4100);
            AddTeleportPad(10300, 4130, 11700, 4100);
            AddTeleportPad(300, 4130, 1400, 1850);
        }
    }

    void Level::AddCheckpoint(float x, float y) {
        Checkpoint cp;
        cp.bounds = sf::FloatRect({ x - 30.0f, y - 120.0f }, { 60.0f, 120.0f });
        cp.pillar.setSize({ 8.0f, 100.0f }); cp.pillar.setPosition({ x - 4.0f, y - 100.0f }); cp.pillar.setFillColor(sf::Color(70, 70, 80)); cp.pillar.setOutlineColor(sf::Color(40, 40, 40)); cp.pillar.setOutlineThickness(2.0f);
        cp.crystal.setPointCount(4); cp.crystal.setPoint(0, { 0.0f, -15.0f }); cp.crystal.setPoint(1, { 15.0f, 0.0f }); cp.crystal.setPoint(2, { 0.0f, 15.0f }); cp.crystal.setPoint(3, { -15.0f, 0.0f }); cp.crystal.setPosition({ x, y - 110.0f }); cp.crystal.setFillColor(sf::Color(120, 120, 130));
        cp.glow.setRadius(25.0f); cp.glow.setOrigin({ 25.0f, 25.0f }); cp.glow.setPosition({ x, y - 110.0f }); cp.glow.setFillColor(sf::Color(200, 50, 255, 0));
        checkpoints.push_back(cp);
    }

    void Level::AddChest(float x, float y) {
        Chest c; c.bounds = sf::FloatRect({ x, y }, { 48.f, 48.f });
        c.shape.setSize({ 48.f, 48.f }); c.shape.setPosition({ x, y }); c.shape.setFillColor(sf::Color(139, 69, 19)); c.shape.setOutlineColor(sf::Color::Yellow); c.shape.setOutlineThickness(2.0f);
        chests.push_back(c);
    }

    void Level::AddStairs(float startX, float startY, float endY) {
        float currentY = startY + 100; float currentX = startX; bool flip = false;
        while (currentY < endY - 100) { AddPlatform(currentX, currentY, 150, 30); currentY += 110; if (flip) currentX -= 100; else currentX += 100; flip = !flip; }
    }

    void Level::AddTeleportPad(float fromX, float fromY, float toX, float toY) {
        TeleportPad pad;
        pad.trigger = sf::FloatRect({ fromX - 30.0f, fromY - 20.0f }, { 60.0f, 20.0f });
        pad.destination = { toX, toY };
        pad.shape.setSize({ 60.0f, 20.0f });
        pad.shape.setPosition({ fromX - 30.0f, fromY - 20.0f });
        pad.shape.setFillColor(sf::Color(150, 50, 220, 210));
        pad.shape.setOutlineColor(sf::Color(230, 180, 255));
        pad.shape.setOutlineThickness(3.0f);
        teleportPads.push_back(pad);
    }

    void Level::AddPlatform(float x, float y, float w, float h) {
        colliders.push_back(sf::FloatRect({ x, y }, { w, h }));
        sf::RectangleShape shape({ w, h }); shape.setPosition({ x, y });
        if (currentType == LevelType::IceCaves) { shape.setTexture(&iceTex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); }
        else if (currentType == LevelType::Moon) { shape.setTexture(&moonTex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); }
        else if (currentType == LevelType::Void) { shape.setTexture(&voidTex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); }
        else { sf::Texture& tex = (currentType == LevelType::Caves) ? tileTexCaves : tileTexForest; shape.setTexture(&tex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); }
        shapes.push_back(shape);
    }

    void Level::AddHazard(float x, float y, float w, float h) {
        hazards.push_back(sf::FloatRect({ x, y }, { w, h }));
        sf::RectangleShape shape({ w, h }); shape.setPosition({ x, y });
        if (currentType == LevelType::Void) shape.setFillColor(sf::Color(180, 50, 255, 220));
        else shape.setFillColor(sf::Color(255, 50, 0, 200));
        hazardShapes.push_back(shape);
    }
    void Level::AddSpring(float x, float y, float w, float h) { springs.push_back(sf::FloatRect({ x, y }, { w, h })); sf::RectangleShape shape({ w, h }); shape.setPosition({ x, y }); shape.setTexture(&springTex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); springShapes.push_back(shape); }
    void Level::AddSpikes(float x, float y, float w, float h) { spikes.push_back(sf::FloatRect({ x, y }, { w, h })); sf::RectangleShape shape({ w, h }); shape.setPosition({ x, y }); shape.setTexture(&spikeTex); shape.setTextureRect(sf::IntRect({ 0, 0 }, { (int)w, (int)h })); spikeShapes.push_back(shape); }

    void Level::AddFallingSpike(float x, float y) {
        FallingSpike fs;
        fs.bounds = sf::FloatRect({ x - 15.0f, y }, { 30.0f, 40.0f });
        fs.trigger = sf::FloatRect({ x - 40.0f, y + 40.0f }, { 80.0f, 400.0f });
        fallingSpikes.push_back(fs);
    }

    void Level::AddPortal(float x, float y) { portalBounds = sf::FloatRect({ x, y }, { 64.f, 128.f }); portalShape.setSize({ 64.f, 128.f }); portalShape.setPosition({ x, y }); portalShape.setFillColor(sf::Color(150, 0, 255, 200)); portalShape.setOutlineColor(sf::Color::White); portalShape.setOutlineThickness(3.0f); }
    void Level::AddMoonPortal(float x, float y) { moonPortalBounds = sf::FloatRect({ x, y }, { 64.f, 128.f }); moonPortalShape.setSize({ 64.f, 128.f }); moonPortalShape.setPosition({ x, y }); moonPortalShape.setFillColor(sf::Color(0, 255, 255, 200)); moonPortalShape.setOutlineColor(sf::Color::White); moonPortalShape.setOutlineThickness(3.0f); }
    void Level::AddIcePortal(float x, float y) { icePortalBounds = sf::FloatRect({ x, y }, { 64.f, 128.f }); icePortalShape.setSize({ 64.f, 128.f }); icePortalShape.setPosition({ x, y }); icePortalShape.setFillColor(sf::Color(150, 200, 255, 200)); icePortalShape.setOutlineColor(sf::Color::White); icePortalShape.setOutlineThickness(3.0f); }
    void Level::AddVoidPortal(float x, float y) { voidPortalBounds = sf::FloatRect({ x, y }, { 64.f, 128.f }); voidPortalShape.setSize({ 64.f, 128.f }); voidPortalShape.setPosition({ x, y }); voidPortalShape.setFillColor(sf::Color(200, 0, 255, 210)); voidPortalShape.setOutlineColor(sf::Color(255, 200, 255)); voidPortalShape.setOutlineThickness(3.0f); }

    void Level::Draw(sf::RenderWindow& window) {
        for (const auto& shape : shapes) window.draw(shape);
        for (const auto& hazard : hazardShapes) window.draw(hazard);
        for (const auto& spring : springShapes) window.draw(spring);
        for (const auto& spike : spikeShapes) window.draw(spike);
        for (const auto& chest : chests) window.draw(chest.shape);
        for (const auto& cp : checkpoints) { window.draw(cp.glow); window.draw(cp.pillar); window.draw(cp.crystal); }
        if (portalBounds.size.x > 0) window.draw(portalShape);
        if (moonPortalBounds.size.x > 0) window.draw(moonPortalShape);
        if (icePortalBounds.size.x > 0) window.draw(icePortalShape);
        if (voidPortalBounds.size.x > 0) window.draw(voidPortalShape);

        for (const auto& pad : teleportPads) window.draw(pad.shape);

        for (const auto& fs : fallingSpikes) {
            if (!fs.isBroken) {
                sf::ConvexShape triangle;
                triangle.setPointCount(3);
                triangle.setPoint(0, { fs.bounds.position.x, fs.bounds.position.y });
                triangle.setPoint(1, { fs.bounds.position.x + fs.bounds.size.x, fs.bounds.position.y });
                triangle.setPoint(2, { fs.bounds.position.x + fs.bounds.size.x / 2.0f, fs.bounds.position.y + fs.bounds.size.y });
                triangle.setFillColor(sf::Color(150, 220, 255));
                triangle.setOutlineColor(sf::Color(255, 255, 255));
                triangle.setOutlineThickness(1.0f);
                window.draw(triangle);
            }
        }
    }
}
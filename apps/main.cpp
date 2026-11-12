#include "core/Game.h"
#include <iostream>
#include <cstdlib>

int main() {
    sf::Texture playerTex, enemyTex, caveTex, forestTex;

    if (!playerTex.loadFromFile("assets/player_sheet.png")) {
        std::cerr << "Error: player_sheet.png not found!" << std::endl;
        return 1;
    }

    // Генерация камня
    sf::Image caveImg({ 32, 32 }, sf::Color(80, 80, 90));
    for (int i = 0; i < 150; ++i) {
        int x = rand() % 32;
        int y = rand() % 32;
        caveImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(60, 60, 70));
    }
    caveTex.loadFromImage(caveImg);

    // Генерация травы
    sf::Image grassImg({ 32, 32 }, sf::Color(120, 80, 50));
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 32; ++x) {
            grassImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(50, 160, 50));
        }
    }
    for (int i = 0; i < 200; ++i) {
        int x = rand() % 32;
        int y = rand() % 32;
        if (y < 8) grassImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(40, 130, 40));
        else grassImg.setPixel({ (unsigned)x, (unsigned)y }, sf::Color(100, 60, 30));
    }
    forestTex.loadFromImage(grassImg);

    game::Game game(playerTex, playerTex, playerTex, playerTex, playerTex, caveTex, forestTex);
    game.Run();
    return 0;
}
#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
namespace game {
    class Input {
    public:
        static bool IsLeft() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left); }
        static bool IsRight() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right); }
        static bool IsJump() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W); }
        static bool IsAttack() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); }
        static bool IsDash() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift); }
        static bool IsInteract() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E); }
        
        static bool jumpJustPressed;
        static bool dashJustPressed;
        static bool interactJustPressed; // Для открытия сундуков
        
        static void ProcessEvent(const sf::Event& event) {
            if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Space || key->code == sf::Keyboard::Key::W) jumpJustPressed = true;
                if (key->code == sf::Keyboard::Key::LShift || key->code == sf::Keyboard::Key::RShift) dashJustPressed = true;
                if (key->code == sf::Keyboard::Key::E) interactJustPressed = true;
            }
        }
        static void Reset() { jumpJustPressed = false; dashJustPressed = false; interactJustPressed = false; }
    };
}

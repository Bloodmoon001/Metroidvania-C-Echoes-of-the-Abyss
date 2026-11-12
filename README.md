<div align="center">



\# 🎮 Metroidvania C++: Echoes of the Abyss



\[!\[C++](https://img.shields.io/badge/C++-17-blue.svg?style=for-the-badge\&logo=c%2B%2B)](https://isocpp.org/)

\[!\[SFML](https://img.shields.io/badge/SFML-2.6-green.svg?style=for-the-badge)](https://www.sfml-dev.org/)

\[!\[CMake](https://img.shields.io/badge/CMake-3.20+-brightgreen.svg?style=for-the-badge\&logo=cmake)](https://cmake.org/)

\[!\[Visual Studio](https://img.shields.io/badge/Visual\_Studio-2022-purple.svg?style=for-the-badge\&logo=visual-studio)](https://visualstudio.microsoft.com/)



\*\*A feature-rich 2D Metroidvania platformer built from scratch in C++ with SFML.\*\*



\[English](#english) • \[Русский](#russian)



</div>



\---



<a name="english"></a>

\## 🇬🇧 English



\### 📖 About the Project

\*\*Metroidvania C++\*\* is a complete 2D platformer with Metroidvania elements, developed entirely from scratch. This project was created to demonstrate advanced C++ skills, game engine architecture, procedural generation, and Object-Oriented Programming (OOP).



\### 📸 Screenshots \& Gameplay



> \*(Replace these placeholders with your actual images and GIFs)\*



| Exploring the Caves | Boss Fight in the Void |

|:---:|:---:|

| !\[Caves](assets/screenshots/caves.jpg) | !\[Void](assets/screenshots/void.jpg) |



| Dash Mechanic | Ice Physics |

|:---:|:---:|

| !\[Dash](assets/gifs/dash.gif) | !\[Ice](assets/gifs/ice.gif) |



\### ✨ Key Features

\*   \*\*Custom Physics \& Collisions:\*\* AABB collision detection, double jump, wall-sliding, and dashing with cooldown mechanics.

\*   \*\*5 Unique Biomes:\*\* 

&#x20;   \*   🦇 \*Sinister Caves\* (Core mechanics)

&#x20;   \*   🌲 \*Green Glade\* (Platforming \& kamikaze enemies)

&#x20;   \*   🌕 \*Moonlight\* (Altered low-gravity physics)

&#x20;   \*   ❄️ \*Frozen Caves\* (Ice sliding, falling spikes)

&#x20;   \*   🌌 \*Distorted Abyss\* (Teleportation pads, acid pits, unique bosses)

\*   \*\*Advanced Enemy AI:\*\* Shooters, flying bats, jumping slimes, laser turrets, ice mages, and a \*\*Three-Headed Horror\*\* (featuring a "Leash" mechanic to return to spawn points).

\*   \*\*Procedural Graphics:\*\* All custom textures (coins, mages, the Void Horror, environmental tiles) are generated in RAM using `sf::Image` at runtime without external assets.

\*   \*\*RPG \& Inventory System:\*\* Collect resources (coins, herbs, ore), craft (upgrade sword with ore), heal (potions), and a checkpoint system.



\### 🛠️ Technical Architecture

The project follows a clean Separation of Concerns:

\*   `src/core` — Game Loop, Input handling, Math (`Vector2`).

\*   `src/entities` — Game objects (Player, Enemy, Level, Collectible, Pickup).

\*   `include/` — Header files, interfaces, and data structures.



\*\*Highlighted Technical Solutions:\*\*

1\.  \*\*Render Optimization:\*\* Utilized `sf::View` for a smooth camera and frustum culling.

2\.  \*\*Memory Management:\*\* Used `std::vector` with iterators for safe object deletion (bullets, enemies) during the game loop without memory leaks.

3\.  \*\*Texture Management:\*\* Static methods in `Collectible` and `Enemy` guarantee that heavy textures are loaded into memory exactly once (Singleton-like approach).

4\.  \*\*Build System:\*\* Fully cross-platform build pipeline using CMake and vcpkg.



\### 🚀 How to Build \& Run

\*\*Requirements:\*\*

\*   OS: Windows / Linux / macOS

\*   C++17 Compiler (MSVC, GCC, Clang)

\*   \[CMake](https://cmake.org/download/) (3.20+)

\*   \[vcpkg](https://github.com/microsoft/vcpkg)



\*\*Step-by-step (Windows + Visual Studio):\*\*

1\. Clone the repository:

&#x20;  ```bash

&#x20;  git clone https://github.com/YOUR\_USERNAME/metroidvania-cpp.git

&#x20;  cd metroidvania-cpp

&#x20;  ```

2\. Install dependencies via vcpkg (Ensure `VCPKG\_ROOT` environment variable is set):

&#x20;  ```bash

&#x20;  vcpkg install sfml gtest

&#x20;  ```

3\. Build using CMake (or open the folder directly in Visual Studio):

&#x20;  ```bash

&#x20;  cmake -B build -S . -DCMAKE\_TOOLCHAIN\_FILE=\[path\_to\_vcpkg]/scripts/buildsystems/vcpkg.cmake

&#x20;  cmake --build build --config Release

&#x20;  ```

4\. \*\*Run:\*\* Launch `app.exe` from the `bin/` folder. \*(Assets are automatically copied via POST\_BUILD CMake command).\*



\### 🎮 Controls

| Action | Key |

| :--- | :--- |

| \*\*Move\*\* | `A` / `D` or `←` / `→` |

| \*\*Jump\*\* | `Space` or `W` |

| \*\*Attack\*\* | `J` or `LMB` |

| \*\*Dash\*\* | `LShift` / `RShift` |

| \*\*Interact\*\* | `E` (Chests, Checkpoints) |

| \*\*Inventory\*\* | `I` |

| \*\*World Map\*\* | `M` or `Tab` |

| \*\*Heal (Use Herb)\*\* | `H` (in Inventory) |

| \*\*Upgrade Weapon\*\* | `U` (Costs 3 Ore) |



\---



<a name="russian"></a>

\## 🇷🇺 Русский



\### 📖 О проекте

\*\*Metroidvania C++\*\* — это полноценный 2D-платформер с элементами метроидвании, написанный с нуля. Проект создан для демонстрации навыков объектно-ориентированного программирования (ООП), разработки игровых движков, процедурной генерации графики и архитектуры игровых систем.



\### 📸 Скриншоты и Геймплей

> \*(Замени эти заглушки на свои реальные изображения и GIF-файлы)\*



| Исследование пещер | Битва в Бездне |

|:---:|:---:|

| !\[Caves](assets/screenshots/caves.jpg) | !\[Void](assets/screenshots/void.jpg) |



| Механика Рывка | Физика льда |

|:---:|:---:|

| !\[Dash](assets/gifs/dash.gif) | !\[Ice](assets/gifs/ice.gif) |



\### ✨ Ключевые особенности

\*   \*\*Собственная физика и коллизии:\*\* AABB-коллизии, двойной прыжок, скольжение по стенам (Wall-Slide), рывок (Dash) с кулдауном.

\*   \*\*5 уникальных биомов:\*\* 

&#x20;   \*   🦇 \*Sinister Caves\* (Базовые механики)

&#x20;   \*   🌲 \*Green Glade\* (Платформинг и враги-камикадзе)

&#x20;   \*   🌕 \*Moonlight\* (Изменённая гравитация)

&#x20;   \*   ❄️ \*Frozen Caves\* (Скольжение по льду, падающие сосульки)

&#x20;   \*   🌌 \*Distorted Abyss\* (Телепорты, кислотные ямы, уникальные враги)

\*   \*\*Продвинутый ИИ врагов:\*\* Стрелки, летающие мыши, прыгающие слаймы, лазерные турели, ледяные маги и \*\*Трехглавый Ужас\*\* (с механикой "Leash" — возвращение на точку спавна).

\*   \*\*Процедурная графика:\*\* Все уникальные текстуры (монеты, маги, Ужас Бездны) генерируются в оперативной памяти с помощью `sf::Image` при старте игры, не требуя внешних ассетов.

\*   \*\*Инвентарь и RPG-элементы:\*\* Сбор ресурсов (монеты, травы, руда), крафт (улучшение меча), лечение, система чекпоинтов.



\### 🛠️ Техническая архитектура

Проект имеет четкое разделение на слои (Separation of Concerns):

\*   `src/core` — Игровой цикл (Game Loop), ввод, математика.

\*   `src/entities` — Игровые сущности (Player, Enemy, Level, Collectible).

\*   `include/` — Заголовочные файлы и интерфейсы.



\*\*Интересные технические решения:\*\*

1\.  \*\*Оптимизация рендера:\*\* Использование `sf::View` для плавной камеры и отрисовки только видимой области.

2\.  \*\*Управление памятью:\*\* Использование `std::vector` с итераторами для безопасного удаления объектов (пули, враги) во время игрового цикла без утечек памяти.

3\.  \*\*Иммутабельность текстур:\*\* Статические методы гарантируют, что тяжелые текстуры загружаются в память ровно один раз.

4\.  \*\*Сборка:\*\* Проект использует CMake и vcpkg для кроссплатформенной сборки.



\### 🚀 Как собрать и запустить

\*\*Требования:\*\*

\*   ОС: Windows / Linux / macOS

\*   Компилятор с поддержкой C++17 (MSVC, GCC, Clang)

\*   \[CMake](https://cmake.org/download/) (версия 3.20+)

\*   \[vcpkg](https://github.com/microsoft/vcpkg) 



\*\*Пошаговая инструкция (Windows + Visual Studio):\*\*

1\. Клонируйте репозиторий:

&#x20;  ```bash

&#x20;  git clone https://github.com/ТВОЙ\_НИКНЕЙМ/metroidvania-cpp.git

&#x20;  cd metroidvania-cpp

&#x20;  ```

2\. Установите зависимости через vcpkg (Убедитесь, что `VCPKG\_ROOT` добавлен в PATH):

&#x20;  ```bash

&#x20;  vcpkg install sfml gtest

&#x20;  ```

3\. Соберите через CMake (или просто откройте папку в Visual Studio):

&#x20;  ```bash

&#x20;  cmake -B build -S . -DCMAKE\_TOOLCHAIN\_FILE=\[путь\_до\_vcpkg]/scripts/buildsystems/vcpkg.cmake

&#x20;  cmake --build build --config Release

&#x20;  ```

4\. \*\*Запуск:\*\* Исполняемый файл `app.exe` появится в папке `bin/`. \*(Ассеты копируются автоматически благодаря POST\_BUILD в CMake).\*



\### 🎮 Управление

| Действие | Клавиша |

| :--- | :--- |

| \*\*Движение\*\* | `A` / `D` или `←` / `→` |

| \*\*Прыжок\*\* | `Space` или `W` |

| \*\*Атака\*\* | `J` или `ЛКМ` |

| \*\*Рывок (Dash)\*\* | `LShift` / `RShift` |

| \*\*Взаимодействие\*\* | `E` (сундуки, чекпоинты) |

| \*\*Инвентарь\*\* | `I` |

| \*\*Карта мира\*\* | `M` или `Tab` |

| \*\*Лечение (Трава)\*\* | `H` (в инвентаре) |

| \*\*Улучшение меча\*\* | `U` (нужно 3 руды) |



\---



\## 👨‍💻 Author / Автор



\*\*\[Bloodmoon001]\*\*

\*   GitHub: \[@Bloodmoon001](https://github.com/Bloodmoon001)

\---

\*This project is for educational and portfolio purposes. All source code is open.\*

\*Проект написан в учебных и портфолио-целях. Все исходники открыты.\*


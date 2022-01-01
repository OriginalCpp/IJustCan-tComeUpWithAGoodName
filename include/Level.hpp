/**
 * @file Level.hpp
 * @brief The Level class.
 * @version 1.0
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Camera.hpp"
#include "DynamicGameObject.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include <vector>

class Level
{
public:

    Level(RenderWindow& p_window);

    ~Level();

    void setUpLevel(int p_level);

    void setUpLevel1();

    void renderLevel();
    void clearLevel();

    Player& getPlayer();

    Camera& getCamera();

    std::vector<std::vector<Tile*>>& getMap();

    std::vector<DynamicGameObject*>& getEnemies();

private:

    Camera* m_camera {nullptr};

    Player* m_player {nullptr};

    std::vector<std::vector<Tile*>>* m_map {nullptr};

    std::vector<DynamicGameObject*>* m_enemies {nullptr};

    SDL_Texture* m_background;

    RenderWindow& m_windowToRenderTo;
};

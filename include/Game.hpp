/**
 * @file Game.hpp
 * @brief The "Game" namespace.
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "GameState.hpp"
#include "Level.hpp"
#include "Player.hpp"

namespace Game
{
    /* Checks for input and other events */
    void handleInput(Player& p_player, GameState& p_gameState);

    void update(Level& p_level, float p_elapsedTimeInSeconds, GameState& p_gameState);
}
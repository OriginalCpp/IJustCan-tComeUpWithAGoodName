/**
 * @file Constants.hpp
 * @brief The constants used by the game.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

namespace constants
{
    namespace playerSprite
    {
        constexpr int w {16};
        constexpr int h {23}; 
    }

    namespace tileSprite
    {
        constexpr int w {16};
        constexpr int h {16};
    }

    namespace window
    {
        constexpr int w {1920};
        constexpr int h {1280};
    }

    namespace camera
    {
        constexpr int w {256};
        constexpr int h {256};
    }

    constexpr int maxAmountOfJumps {1};

    constexpr int scale {4};

    constexpr int normalPlayerSpeed {400};

    /* The player can jump 3 tiles high and 4 tiles wide*/
    constexpr int normalJumpHeight {3*tileSprite::h*scale};
    constexpr int normalJumpWidth {4*tileSprite::w*scale}; 

    /* Formula: 2h(xVelocity)² / (w²/4) */
    constexpr int gravity{2*normalJumpHeight*normalPlayerSpeed*normalPlayerSpeed/(normalJumpWidth*normalJumpWidth/4)};
}
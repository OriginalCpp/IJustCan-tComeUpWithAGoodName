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
    constexpr int scale {4};

    namespace playerSprite
    {
        constexpr int w {17};
        constexpr int wScaled{w*scale};
        constexpr int h {31}; 
        constexpr int hScaled{h*scale};
    }

    namespace tileSprite
    {
        constexpr int w {16};
        constexpr int wScaled {w*scale};
        constexpr int h {16};
        constexpr int hScaled {h*scale};
    }

    namespace slimeSprite
    {
        constexpr int w {16};
        constexpr int wScaled {w*scale};
        constexpr int h {16};
        constexpr int hScaled {h*scale};
    }

    namespace window
    {
        constexpr int w {1920};
        constexpr int h {1280};
    }

    namespace cameraMargin
    {
        constexpr int w {256};
        constexpr int h {256};
    }

    /* The size of the biggest sprite in the game, excluding the player. */
    constexpr int largestSpriteWidth {tileSprite::w*scale};
    constexpr int largestSpriteHeight {tileSprite::h*scale};

    constexpr int maxAmountOfJumps {1};
    constexpr int defaultPlayerSpeed {400};

    /* The player can jump 3 tiles high and 4 tiles wide*/
    constexpr int normalJumpHeight {3*tileSprite::h*scale};
    constexpr int normalJumpWidth {4*tileSprite::w*scale}; 

    /*
     Formula: 2*h*xVelocity² / (w²/4) 
    */
    constexpr int gravity{2*normalJumpHeight*defaultPlayerSpeed*defaultPlayerSpeed/(normalJumpWidth*normalJumpWidth/4)};
}
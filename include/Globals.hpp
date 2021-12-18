#pragma once

namespace constants
{
    constexpr int maxAmountOfJumps {1};
    constexpr int scale {4};
    constexpr int gravity{3500};

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
}
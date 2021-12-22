#include "Tests.hpp"
#include "utils.hpp"
#include "GameObject.hpp"
#include <SDL.h>
#include <iostream>

void Test::utils_collision_PointVsRect()
{
    std::cout << "Test::utils_collision_PointVsRect(): \n";
    std::string testResult = "";

    SDL_FPoint test1Point = {1, 1};
    SDL_FRect test1Rect = {0, 0, 2, 2};
    testResult = (utils::collision_PointVsRect(&test1Point, &test1Rect)) ? ("  Test 1 completed\n") : ("  Test 1 failed\n");
    std::cout << testResult;
    
    SDL_FPoint test2Point = {3, 3};
    SDL_FRect test2Rect = {1, 1, 2, 2};
    testResult = (utils::collision_PointVsRect(&test2Point, &test2Rect)) ? ("  Test 2 failed\n") : ("  Test 2 completed\n");
    std::cout << testResult;

    SDL_FPoint test3Point = {1, 2};
    SDL_FRect test3Rect = {0, 0, 1, 1};
    testResult = (utils::collision_PointVsRect(&test3Point, &test3Rect)) ? ("  Test 3 failed\n") : ("  Test 3 completed\n");
    std::cout << testResult;
}

/**
 * @sa Tests.hpp
 */
void Test::GameObject_Constructor(SDL_Renderer* p_renderer)
{
    std::cout << "Test::GameObject_Constructor():\n";
    std::string testResult = "";

    SDL_Texture* testTexture = utils::loadTexture("../res/enemies/greenslime.png", p_renderer);
    SDL_Rect testSrcRect {0, 0, 16, 16};

    SDL_Rect test1DstRect {1, 2, 3, 4};
    SDL_FRect test1CollisionRect {16, 14, 0, 0};
    GameObject test1(testTexture, testSrcRect, test1DstRect, test1CollisionRect);

    std::cout << "Before the test: " << test1.getX() << ", " << test1.getY() << ", " << test1.getW() << ", " << test1.getH() << '\n';

    testResult = ((test1.getX() == 1) && (test1.getY() == 2) && (test1.getW() == 3) && (test1.getH() == 4)) 
                    ? ("  Test 1 completed\n") : ("  Test 1 failed\n");

    std::cout << testResult;


    SDL_Rect test2DstRect {4, 4, 4, 4};
    SDL_FRect test2CollisionRect {0, 0, 2, 2};
    GameObject test2(testTexture, testSrcRect, test2DstRect, test2CollisionRect);

    std::cout << "Before the test: " << test2.getX() << ", " << test2.getY() << ", " << test2.getW() << ", " << test2.getH() << '\n';

    testResult = ((test2.getX() == 4) && (test2.getY() == 6) && (test2.getW() == 2) && (test2.getH() == 2)) 
                    ? ("  Test 2 completed\n") : ("  Test 2 failed\n");
    
    std::cout << testResult;
}

/**
 * @sa Tests.hpp
 */
void Test::GameObject_setXgetX(SDL_Renderer* p_renderer)
{
    std::cout << "Test::GameObject_setX():\n";
    std::string testResult = "";

    SDL_Texture* testTexture = utils::loadTexture("../res/enemies/greenslime.png", p_renderer);
    SDL_Rect testSrcRect {0, 0, 16, 16};
    SDL_Rect testDstRect {4, 4, 4, 4};
    SDL_FRect testCollisionRect {0, 0, 2, 2};

    GameObject test(testTexture, testSrcRect, testDstRect, testCollisionRect);

    test.setX(4);

    testResult = (test.getX() == 4) ? ("  Test 1 completed\n") : ("  Test 1 failed\n");
    std::cout << testResult;

    test.setX(5023);
    
    testResult = (test.getX() == 5023) ? ("  Test 2 completed\n") : ("  Test 2 failed\n");
    std::cout << testResult;

}
/**
 * @file tests.cpp
 * @brief Definitions of all functions in the namespace "test".
 * @sa Tests.hpp for function documentation.
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Tests.hpp"

#include "GameObject.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>
#include <SDL.h>
#include <vector>

void test::utils_collision_PointVsRect()
{
    std::cout << "\nTest::utils_collision_PointVsRect():\n";
    std::string testResult{""};

    //TEST 1
    SDL_FPoint test1Point = {1, 1};
    SDL_FRect test1Rect = {0, 0, 2, 2};
    testResult = (utils::collision_PointVsRect(&test1Point, &test1Rect)) ? ("  Test 1 completed\n") : ("  Test 1 failed\n");
    std::cout << testResult;
    
    //TEST 2
    SDL_FPoint test2Point = {3, 3};
    SDL_FRect test2Rect = {1, 1, 2, 2};
    testResult = (utils::collision_PointVsRect(&test2Point, &test2Rect)) ? ("  Test 2 failed\n") : ("  Test 2 completed\n");
    std::cout << testResult;

    //TEST 3
    SDL_FPoint test3Point = {1, 2};
    SDL_FRect test3Rect = {0, 0, 1, 1};
    testResult = (utils::collision_PointVsRect(&test3Point, &test3Rect)) ? ("  Test 3 failed\n") : ("  Test 3 completed\n");
    std::cout << testResult;
}



void test::utils_getIntersectionCornerFPoints()
{
    std::cout << "\nTest::utils_getIntersectionCornerFPoints():\n";
    std::string testResult {""};

    //TEST 1
    SDL_FRect test1Rect1 {0, 0, 6, 6};
    SDL_FRect test1Rect2 {1, 1, 3, 3};
    SDL_FPoint test1Points[4]{{1, 1},
                             {4, 1},
                             {4, 4},
                             {1, 4}};

    auto resultPoints = utils::getIntersectionCornerFPoints(&test1Rect1, &test1Rect2);

    int i{0};
    for(const SDL_FPoint& point : test1Points)
    {
        if((point.x == resultPoints->at(i).x) && (point.y == resultPoints->at(i).y))
            testResult = "  Test 1 completed\n";
        else
        {
            testResult = "  Test 1 failed\n";
            break;
        }   
        ++i;
    }
    
    std::cout << testResult;

    //TEST 2
    SDL_FRect test2Rect1 {1, 1, 3, 3.5};
    SDL_FRect test2Rect2 {2, 3.45, 3, 3};
    SDL_FPoint test2Points[2]{{4, 4.5},
                              {2, 3.45}};

    resultPoints = utils::getIntersectionCornerFPoints(&test2Rect1, &test2Rect2);

    i = 0;
    for(const SDL_FPoint& point : test2Points)
    {
        if((point.x == resultPoints->at(i).x) && (point.y == resultPoints->at(i).y))
            testResult = "  Test 2 completed\n";
        else
        {
            testResult = "  Test 2 failed\n";
            break;
        }   
        ++i;
    }

    std::cout << testResult;

    //TEST 3
    SDL_FRect test3Rect1 {1, 1, 1, 1};
    SDL_FRect test3Rect2 {9, 9, 1, 1};

    testResult = (!utils::getIntersectionCornerFPoints(&test3Rect1, &test3Rect2)) ? "  Test 3 completed\n" : "  Test 3 failed\n";
    
    std::cout << testResult;
}



void test::GameObject_Constructor(SDL_Renderer* p_renderer)
{
    std::cout << "\nTest::GameObject_Constructor():\n";
    std::string testResult {""};

    SDL_Texture* testTexture = utils::loadTexture("../res/enemies/greenslime.png", p_renderer);
    SDL_Rect testSrcRect {0, 0, 16, 16};

    SDL_Rect test1DstRect {1, 2, 3, 4};
    SDL_FRect test1CollisionRect {16, 14, 0, 0};
    GameObject test1(testTexture, testSrcRect, test1DstRect, test1CollisionRect);

    testResult = ((test1.getX() == 1) && (test1.getY() == 2) && (test1.getW() == 3) && (test1.getH() == 4)) 
                    ? ("  Test 1 completed\n") : ("  Test 1 failed\n");

    std::cout << testResult;


    SDL_Rect test2DstRect {4, 4, 4, 4};
    SDL_FRect test2CollisionRect {0, 0, 2, 2};
    GameObject test2(testTexture, testSrcRect, test2DstRect, test2CollisionRect);


    testResult = ((test2.getX() == 4) && (test2.getY() == 6) && (test2.getW() == 2) && (test2.getH() == 2)) 
                    ? ("  Test 2 completed\n") : ("  Test 2 failed\n");
    
    std::cout << testResult;
}



void test::GameObject_setXgetX(SDL_Renderer* p_renderer)
{
    std::cout << "\nTest::GameObject_setX():\n";
    std::string testResult {""};

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
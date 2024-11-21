#include "gamelogic.h"
#include <gtest/gtest.h>

class GameLogicTest : public ::testing::Test
{
protected:
    GameLogic gameLogic;

    // void SetUp() override {

    // }
};

TEST_F(GameLogicTest, TestMakeMoveDecrementAllowed)
{
    // Call function
    gameLogic.makeMove({0, 1}, -1);
    // Add assertions to check the expected state of the board
    EXPECT_EQ(gameLogic.getBoardValue({0, 0}), 8);
    EXPECT_EQ(gameLogic.getBoardValue({0, 1}), 8);
    EXPECT_EQ(gameLogic.getBoardValue({0, 2}), 8);
    EXPECT_EQ(gameLogic.getBoardValue({1, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({1, 1}), 8);
    EXPECT_EQ(gameLogic.getBoardValue({1, 2}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 1}), 8);
    EXPECT_EQ(gameLogic.getBoardValue({2, 2}), 9);
}

TEST_F(GameLogicTest, TestMakeMoveDecrementCycle)
{
    // Call function
    for (int i = 0; i < 9; ++i)
    {
        gameLogic.makeMove({0, 1}, -1);
    }

    // Add assertions to check the expected state of the board
    EXPECT_EQ(gameLogic.getBoardValue({0, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({0, 1}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({0, 2}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({1, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({1, 1}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({1, 2}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 1}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 2}), 9);
}

TEST_F(GameLogicTest, TestMakeMoveDecrementOverflow)
{
    // Add assertions to check that function throws error correctly
    EXPECT_THROW(gameLogic.makeMove({2, 3}, -1), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({3, 2}, -1), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({5, 10}, -1), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({0, -10}, -1), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({-1, -10}, -1), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({-1, 1}, -1), std::out_of_range);
}
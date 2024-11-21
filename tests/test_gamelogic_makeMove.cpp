#include "gamelogic.h"
#include <gtest/gtest.h>

class GameLogicTest : public ::testing::Test
{
protected:
    GameLogic gameLogic;

    // void SetUp() override {

    // }
};

TEST_F(GameLogicTest, TestMakeMoveAllowed)
{
    // Call function
    gameLogic.makeMove({0, 1});
    // Add assertions to check the expected state of the board
    EXPECT_EQ(gameLogic.getBoardValue({0, 0}), 1);
    EXPECT_EQ(gameLogic.getBoardValue({0, 1}), 1);
    EXPECT_EQ(gameLogic.getBoardValue({0, 2}), 1);
    EXPECT_EQ(gameLogic.getBoardValue({1, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({1, 1}), 1);
    EXPECT_EQ(gameLogic.getBoardValue({1, 2}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 0}), 9);
    EXPECT_EQ(gameLogic.getBoardValue({2, 1}), 1);
    EXPECT_EQ(gameLogic.getBoardValue({2, 2}), 9);
}

TEST_F(GameLogicTest, TestMakeMoveOverflow)
{
    // Add assertions to check that function throws error correctly
    EXPECT_THROW(gameLogic.makeMove({2, 3}), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({3, 2}), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({5, 10}), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({0, -10}), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({-1, -10}), std::out_of_range);
    EXPECT_THROW(gameLogic.makeMove({-1, 1}), std::out_of_range);
}
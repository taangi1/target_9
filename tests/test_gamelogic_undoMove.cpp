#include "gamelogic.hpp"
#include <gtest/gtest.h>

class GameLogicTest : public ::testing::Test
{
protected:
    GameLogic gameLogic;
};

TEST_F(GameLogicTest, TestUndoMoveAllowed)
{
    // Call function
    gameLogic.makeMove({0, 1});
    gameLogic.undoMove();
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

TEST_F(GameLogicTest, TestUndoMoveCycle)
{
    // Call function
    for (int i = 0; i < 9; ++i)
    {
        gameLogic.makeMove({0, 1});
    }

    for (int i = 0; i < 9; ++i)
    {
        gameLogic.undoMove();
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

TEST_F(GameLogicTest, TestUndoMoveUnderflow)
{
    // Add assertions to check that function throws error correctly
    EXPECT_THROW(gameLogic.undoMove(), std::runtime_error);
}
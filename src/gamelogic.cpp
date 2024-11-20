/**
 * @file gamelogic.cpp
 * @brief Implementation of GameLogic class methods.
 * @author Ignat Romanov
 * @version 0.1
 * @date 20.11.2024
 */
#include "gamelogic.h"

#include <stdexcept>

GameLogic::GameLogic()
{
    for (auto &row : board)
    {
        for (auto &value : row)
        {
            value = 9;
        }
    }
}

GameLogic::~GameLogic()
{
}

bool GameLogic::isWin() const
{
    for (const auto &row : board)
    {
        for (const auto &value : row) // Get value from all rows.
        {
            if (value != 9)
                return false; // False if any value not equal to 9.
        }
    }
    return true; // All values are 9.
}

void GameLogic::makeMove(Move move)
{
    if (move.row >= MAX_SIZE || move.col >= MAX_SIZE)
    {
        throw std::overflow_error("Cannot play move at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
    }
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        board[move.row][i] >= 9 ? board[move.row][i] = 1 : ++board[move.row][i]; // If value in selected row and column i is greater or equal to 9 set it to 1; increment by 1 otherwise.
        board[i][move.col] >= 9 ? board[i][move.col] = 1 : ++board[i][move.col]; // If value in selected col and row i is greater or equal to 9 set it to 1; increment by 1 otherwise.
    }
    board[move.row][move.col] <= 1 ? board[move.row][move.col] = 9 : --board[move.row][move.col]; // Handle increment of board[row][col] twice during the loop.
}

int GameLogic::getBoardValue(Move move)
{
    return board[move.row][move.col]; // Return board value in a given row and column.
}

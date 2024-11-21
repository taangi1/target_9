/**
 * @file gamelogic.cpp
 * @brief Implementation of GameLogic class methods.
 * @author Ignat Romanov
 * @version 0.1
 * @date 20.11.2024
 */
#include "gamelogic.h"

#include <stdexcept>
#include <random>

GameLogic::GameLogic()
{
    current_difficulty = 1;
    num_moves = 0;
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
    if (move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0)
    {
        throw std::out_of_range("Cannot play move at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
    }
    ++num_moves;
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        board[move.row][i] = (board[move.row][i] % 9) + 1; // If value in selected row and column i is greater or equal to 9 set it to 1; increment by 1 otherwise.
        board[i][move.col] = (board[i][move.col] % 9) + 1; // If value in selected col and row i is greater or equal to 9 set it to 1; increment by 1 otherwise.
    }
    board[move.row][move.col] <= 1 ? board[move.row][move.col] = 9 : --board[move.row][move.col]; // Handle increment of board[row][col] twice during the loop.
    historyMoves.push(move);
}

void GameLogic::makeMove(Move move, bool decrement)
{
    if (move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0)
    {
        throw std::out_of_range("Cannot play move at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
    }
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        board[move.row][i] <= 1 ? board[move.row][i] = 9 : --board[move.row][i]; // If value in selected row and column i is greater or less or equal to 1 set it to 9; decrement by 1 otherwise.
        board[i][move.col] <= 1 ? board[i][move.col] = 9 : --board[i][move.col]; // If value in selected col and row i is greater or less or equal to 1 set it to 9; decrement by 1 otherwise.
    }
    board[move.row][move.col] >= 9 ? board[move.row][move.col] = 1 : ++board[move.row][move.col]; // Handle decrement of board[row][col] twice during the loop.
    --num_moves;
}

int GameLogic::getBoardValue(Move move) const
{
    return board[move.row][move.col]; // Return board value in a given row and column.
}

void GameLogic::init()
{
    GameLogic();
    if (current_difficulty > MAX_SIZE * MAX_SIZE)
    {
        throw std::out_of_range("Cannot initialize game with difficulty " + std::to_string(current_difficulty));
    }
    for (auto &row : board)
    {
        for (auto &value : row)
        {
            value = 9; // Set all values of board to 9.
        }
    }
    solution.~Stack();
    historyMoves.~Stack();
    // Create a random device and a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define the range for the random numbers
    std::uniform_int_distribution<> distrib(0, MAX_SIZE-1); // Define the range [0,2] for rows and cols
    for (int i = 0; i < current_difficulty; ++i)
    {
        Move move = {distrib(gen), distrib(gen)};
        makeMove(move, -1); // Decrement random rows and cols by one.
        solution.push(move);
    }
    num_moves = 0;
}

void GameLogic::setDifficulty(int difficulty)
{
    if (difficulty>MAX_SIZE*MAX_SIZE)
    {
        throw std::out_of_range("Cannot set the difficulty " + std::to_string(difficulty));
    }
    current_difficulty = difficulty;
}

int GameLogic::getDifficulty() const
{
    return current_difficulty;
}

void GameLogic::undoMove()
{
    if (num_moves<=0)
    {
        throw std::runtime_error("Cannot undo move with number of moves " + std::to_string(num_moves));
    }
    makeMove(historyMoves.pop(), -1);
}

void GameLogic::redoMove()
{
    if (num_moves<=0)
    {
        throw std::runtime_error("Cannot redo move with number of moves " + std::to_string(num_moves));
    }
    makeMove(historyMoves.top());
}

int GameLogic::getNumMoves() const
{
    return num_moves;
}

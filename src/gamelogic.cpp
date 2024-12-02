/**
 * @file gamelogic.cpp
 * @brief Implementation of GameLogic class methods.
 * @author Ignat Romanov
 * @version 0.1
 * @date 20.11.2024
 */
#include "gamelogic.hpp"

#include <stdexcept>
#include <random>

GameLogic::GameLogic()
{
    for (auto &row : board)
    {
        for (auto &value : row)
        {
            value = 9; // Set all values of board to 9.
        }
    }
    current_difficulty = 1;
    num_moves = 0;
    canHint = false;
    canRedo = false;
    canUndo = false;
    historyMoves = new Stack<Move>;
    undoHistory = new Stack<Move>;
}

GameLogic::~GameLogic()
{
    delete historyMoves;
    delete undoHistory;
}

bool GameLogic::isWin()
{
    for (const auto &row : board)
    {
        for (const auto &value : row) // Get value from all rows.
        {
            if (value != 9)
                return false; // False if any value not equal to 9.
        }
    }
    canRedo = false;
    canHint = false;
    canUndo = false;
    return true; // All values are 9.
}

void GameLogic::makeMove(Move move)
{
    if (move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0)
    {
        throw std::out_of_range("Cannot play move at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
    }
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        board[move.row][i] = (board[move.row][i] % 9) + 1; // If value in selected row and column i is greater or equal to 9 set it to 1; increment by 1 otherwise.
        board[i][move.col] = (board[i][move.col] % 9) + 1; // If value in selected col and row i is greater or equal to 9 set it to 1; increment by 1 otherwise.
    }
    ++num_moves;
    board[move.row][move.col] <= 1 ? board[move.row][move.col] = 9 : --board[move.row][move.col]; // Handle increment of board[row][col] twice during the loop.
    historyMoves->push(move);
    canUndo = true;
    canRedo = false;
    delete undoHistory;
    undoHistory = new Stack<Move>;
}

void GameLogic::reverseMove(Move move)
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

void GameLogic::redoMakeMove(Move move)
{
    if (move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0)
    {
        throw std::out_of_range("Cannot play move at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
    }
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        board[move.row][i] = (board[move.row][i] % 9) + 1; // If value in selected row and column i is greater or equal to 9 set it to 1; increment by 1 otherwise.
        board[i][move.col] = (board[i][move.col] % 9) + 1; // If value in selected col and row i is greater or equal to 9 set it to 1; increment by 1 otherwise.
    }
    ++num_moves;
    board[move.row][move.col] <= 1 ? board[move.row][move.col] = 9 : --board[move.row][move.col]; // Handle increment of board[row][col] twice during the loop.
    historyMoves->push(move);
    canUndo = true;
}

int GameLogic::getBoardValue(Move move) const
{
    if (!(move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0))
    {
        return board[move.row][move.col]; // Return board value in a given row and column.
    }
    throw std::out_of_range("Cannot get value at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
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
    // Create a random device and a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define the range for the random numbers
    std::uniform_int_distribution<> distrib(0, MAX_SIZE - 1); // Define the range [0,2] for rows and cols
    for (int i = 0; i < current_difficulty; ++i)
    {
        Move move = {distrib(gen), distrib(gen)};
        reverseMove(move); // Decrement random rows and cols by one.
    }

    delete historyMoves;
    delete undoHistory;
    historyMoves = new Stack<Move>;
    undoHistory = new Stack<Move>;

    canHint = true;
    canRedo = false;
    canUndo = false;
    num_moves = 0;
}

void GameLogic::setDifficulty(int difficulty)
{
    if (difficulty > MAX_SIZE * MAX_SIZE)
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
    if (num_moves <= 0)
    {
        throw std::runtime_error("Cannot undo move with number of moves " + std::to_string(num_moves));
    }
    if (canUndo)
    {
        undoHistory->push(historyMoves->top());
        reverseMove(historyMoves->pop());
        canRedo = true;
        canUndo = num_moves != 0;
    }
    else
    {
        canUndo = false;
        throw std::runtime_error("GameLogic::undoMove() should not come to this line");
    }
}

void GameLogic::redoMove()
{
    if (undoHistory->isEmpty())
    {
        throw std::runtime_error("Cannot undo from empty stack.");
    }
    if (canRedo)
    {
        redoMakeMove(undoHistory->pop());
        canRedo = !undoHistory->isEmpty();
    }
    else
    {
        canRedo = false;
        throw std::runtime_error("GameLogic::redoMove() should not come to this line");
    }
}

int GameLogic::getNumMoves() const
{
    return num_moves;
}

bool GameLogic::isCanRedo() const
{
    return canRedo;
}

bool GameLogic::isCanUndo() const
{
    return canUndo;
}

bool GameLogic::isCanHint() const
{
    return canHint;
}

GameLogic::Move GameLogic::hintNextMove() const
{
    int minMoves = -1;
    Move bestMove = {-1, -1};
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
        {
            int currentMoves = 0;

            for (int k = 0; k < MAX_SIZE; ++k)
                currentMoves += (9 - board[i][k]);
            for (int k = 0; k < MAX_SIZE; ++k)
                currentMoves += (9 - board[k][j]);
            currentMoves -= (9 - board[i][j]);

            if (currentMoves > minMoves)
            {
                minMoves = currentMoves;
                bestMove = {i, j};
            }
        }
    }

    return bestMove;
}
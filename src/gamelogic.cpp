/**
 * @file gamelogic.cpp
 * @brief Implementation of GameLogic class methods.
 *
 * This file contains the implementation of the GameLogic class, which manages
 * the core mechanics of the game. It handles the game board, player moves,
 * and game state, including win conditions and move history. The GameLogic
 * class provides methods for making moves, undoing and redoing moves,
 * checking win conditions, and providing hints for the next move.
 *
 * @author Ignat Romanov
 * @version 1.1
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
            value = 9; // Set all values of board to 9 for testing purposes.
        }
    }

    current_difficulty = 1; // Set difficulty to 1
    num_moves = 0;          // Set number of moves to 0

    // Set all booleans for actions to false; during GameLogic::init() canHint will be set to true
    canHint = false;
    canRedo = false;
    canUndo = false;
}

GameLogic::~GameLogic()
{
}

// Check if game is won, i.e. all values are 9
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
    // If game is won set actions to false.
    canRedo = false;
    canHint = false;
    canUndo = false;
    return true; // All values are 9.
}

// Normal move in game which increments by one elements in the same column and row. Changes game state.
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
    ++num_moves;                                                                                  // Increment moves count
    board[move.row][move.col] <= 1 ? board[move.row][move.col] = 9 : --board[move.row][move.col]; // Handle increment of board[row][col] twice during the loop.
    historyMoves.push(move);                                                                      // Push current move in undo stack.
    canUndo = true;                                                                               // After move player can undo.
    canRedo = false;                                                                              // After move player cannot redo.

    // Clear redo stack after each normal move.
    while (!undoHistory.isEmpty())
    {
        undoHistory.pop();
    }
}

// Decremental move to init and to undo moves.
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
    --num_moves;                                                                                  // Decrement moves count by one.
}

// Function for redo action. Uses the same logic as normal move but does not clear the redo stack.
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
    historyMoves.push(move);                                                                      // Push move in undo stack.
    canUndo = true;
}

// Getter function for gui
int GameLogic::getBoardValue(Move move) const
{
    if (!(move.row >= MAX_SIZE || move.col >= MAX_SIZE || move.row < 0 || move.col < 0))
    {
        return board[move.row][move.col]; // Return board value in a given row and column.
    }
    throw std::out_of_range("Cannot get value at row " + std::to_string(move.row) + ", column " + std::to_string(move.col));
}

// Initialize game with random moves with set difficulty.
void GameLogic::init()
{
    if (current_difficulty > MAX_SIZE * MAX_SIZE)
    {
        current_difficulty = 1;
        throw std::out_of_range("Cannot initialize game with difficulty " + std::to_string(current_difficulty));
    }
    for (auto &row : board)
    {
        for (auto &value : row)
        {
            value = 9; // Set all values of board to 9.
        }
    }

    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define the range for the random numbers
    std::uniform_int_distribution<> distrib(0, MAX_SIZE - 1); // Define the range [0,2] for rows and cols in uniform distribution.
    for (int i = 0; i < current_difficulty; ++i)
    {
        Move move = {distrib(gen), distrib(gen)};
        reverseMove(move); // Decrement random rows and cols by one.
    }

    // Clear redo stack at the start of new game.
    while (!undoHistory.isEmpty())
    {
        undoHistory.pop();
    }

    // Clear undo stack at the start of new game.
    while (!historyMoves.isEmpty())
    {
        historyMoves.pop();
    }

    canHint = true; // At new game can hint.
    canRedo = false;
    canUndo = false;
    num_moves = 0;
}

// Setter function to set the difficulty.
void GameLogic::setDifficulty(int difficulty)
{
    if (difficulty > MAX_SIZE * MAX_SIZE || difficulty <= 0)
    {
        throw std::out_of_range("Cannot set the difficulty " + std::to_string(difficulty));
    }
    current_difficulty = difficulty;
}

// Getter function to get difficulty.
int GameLogic::getDifficulty() const
{
    return current_difficulty;
}

// Function to undo move.
void GameLogic::undoMove()
{
    if (num_moves <= 0) // Check if the number of moves is not less or equal to zero, i.e. there was at least one move.
    {
        canUndo = false;
        throw std::runtime_error("Cannot undo move with number of moves " + std::to_string(num_moves));
    }
    if (canUndo) // Check that canUndo is true.
    {
        undoHistory.push(historyMoves.top()); // Push in redo stack.
        reverseMove(historyMoves.pop());      // Decrement values in last move.
        canRedo = true;                       // After undo user can redo.
        canUndo = num_moves != 0;             // If number of moves is zero then it is not possible to undo anymore.
    }
    else
    {
        canUndo = false;
        throw std::runtime_error("GameLogic::undoMove() called when canUndo is false. Ensure that a move can be undone before calling this function.");
    }
}

// Function to redo move.
void GameLogic::redoMove()
{
    if (undoHistory.isEmpty()) // If redo stack is empty throw exception.
    {
        canRedo = false;
        throw std::runtime_error("Cannot redo moves from empty stack.");
    }
    if (canRedo) // Check if possible to redo.
    {
        redoMakeMove(undoHistory.pop());  // Call redo move function with last undo move.
        canRedo = !undoHistory.isEmpty(); // If redo stack is empty set canRedo to false.
    }
    else
    {
        canRedo = false;
        throw std::runtime_error("GameLogic::redoMove() called when canRedo is false. Ensure that a move can be redone before calling this function.");
    }
}

// Getter functions...
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

// Function to hint. Returns a move.
GameLogic::Move GameLogic::hintNextMove() const
{
    if (!canHint) // Check if can hint.
    {
        throw std::runtime_error("Hinting is not allowed at this time. Please check the game state.");
    }
    int minMoves = 100; // Theoretical maximum is 9*9=81.
    Move bestMove = {-1, -1};
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j) // Iterate over board.
        {
            int currentMoves = 0;

            // Make move.
            for (int k = 0; k < MAX_SIZE; ++k)
                currentMoves += (board[i][k]);
            for (int k = 0; k < MAX_SIZE; ++k)
                currentMoves += (board[k][j]);
            currentMoves -= (board[i][j]);

            // Check if this iteration is better than the last one.
            if (currentMoves < minMoves)
            {
                minMoves = currentMoves;
                bestMove = {i, j};
            }
        }
    }

    return bestMove;
}
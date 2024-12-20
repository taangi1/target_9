/**
 * @file gamelogic.h
 * @brief Header file for the GameLogic class.
 *
 * This file contains the declaration of the GameLogic class, which is responsible
 * for managing the core game mechanics, including game state, player actions,
 * and interactions between game entities. The GameLogic class serves as the
 * central hub for game rules and logic, ensuring that the game operates
 * according to the defined rules and provides a seamless experience for players.
 *
 * @author Ignat Romanov
 * @version 1.1
 * @date 20.11.2024
 */

#include "stack.hpp"

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#define MAX_SIZE 3 // Max size of board.

/**
 * @brief Provides the functionality for target 9 game.
 */
class GameLogic
{
public:
    struct Move
    {
        int row;
        int col;
    };

    /**
     * @brief Constructor for the class. Initializes board to default board size (3x3).
     */
    GameLogic();

    /**
     * @brief Default destructor.
     */
    ~GameLogic();

    /**
     * @brief Check if the player won.
     * @return  True if the player won. False otherwise.
     */
    bool isWin();

    /**
     * @brief Make a move in the game. Increments all values in given row and column by one. If value in board was 9, sets it to 1.
     * @param move move of struct Move containing row and col members. {row, col}.
     * @param value Value by which to make move. Default value is one.
     * @throw std::out_of_range if the move is bigger than dimensions of a square array defined by MAX_SIZE.
     */
    void makeMove(Move move);

    /**
     * @brief Getter function to get a value from the board.
     * @param move move of struct Move containing row and col members. {row, col}.
     * @return Value in a given row and column.
     * @throw std::out_of_range
     */
    int getBoardValue(Move move) const;

    /**
     * @brief Initializes game with the set difficulty. Substracts 1 from random rows and columns.
     * @throw std::out_of_range if difficulty is bigger than MAX_SIZE*MAX_SIZE
     */
    void init();

    /**
     * @brief Sets difficulty to specified value.
     * @param difficulty difficulty to set.
     * @throw std::out_of_range if new difficulty is larger than MAX_SIZE*MAX_SIZE or difficulty is less than or equal to zero.
     */
    void setDifficulty(int difficulty);

    /**
     * @brief Get difficulty level from current_difficulty.
     * @return Returns difficulty level.
     */
    int getDifficulty() const;

    /**
     * @brief Undo function to cancel last move and decrement number of moves by one.
     * @throw std::runtime_error if cannot undo move.
     */
    void undoMove();

    /**
     * @brief Redo function to play last move again and increment number of moves by one.
     * @throw std::runtime_error if cannot redo move.
     */
    void redoMove();

    /**
     * @brief Get number of moves from num_moves.
     * @return Number of moves.
     */
    int getNumMoves() const;

    /**
     * @brief Get value of canRedo boolean if it is possible to use GameLogic::redoMove(). Should be used before calling GameLogic::redoMove().
     * @return Value of canRedo.
     */
    bool isCanRedo() const;

    /**
     * @brief Get value of canUndo boolean if it is possible to use GameLogic::undoMove(). Should be used before calling GameLogic::undoMove().
     * @return Value of canUndo.
     */
    bool isCanUndo() const;

    /**
     * @brief Get value of canHint boolean if it is possible to use GameLogic::hintNextMove(). Should be used before calling GameLogic::hintNextMove().
     * @return Value of canHint.
     */
    bool isCanHint() const;

    /**
     * @brief Determine the best next move and return it.
     * @return Best next move of struct GameLogic::Move.
     * @throw std::runtime_error if cannot hint a move, e.g. when game is finished or not initialized.
     */
    Move hintNextMove() const;

private:
    int board[MAX_SIZE][MAX_SIZE];
    int num_moves;
    int current_difficulty;
    bool canRedo;
    bool canUndo;
    bool canHint;

    /**
     * @brief Overloaded makeMove(Move move). Make a move by decrementing values by one. Used in init method.
     * @param move move of struct Move containing row and col members. {row, col}.
     * @param decrement If specified, function is overloaded and decrements by one.
     * @throw std::out_of_range
     */
    void reverseMove(Move move);

    /**
     * @brief Make move function redesigned for redo function to destinguish moves by player and GameLogic::redoMove().
     * @param move Move to redo.
     * @throw std::out_of_range
     */
    void redoMakeMove(Move move);

    Stack<Move> historyMoves; // Undo stack
    Stack<Move> undoHistory;  // Redo stack
};

#endif // GAMELOGIC_HPP

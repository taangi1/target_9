/**
 * @file gamelogic.h
 * @brief Program
 * @author Ignat Romanov
 * @version 0.1
 * @date 20.11.2024
 */

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#define MAX_SIZE 3 // Max size of board.

#include "stack.h"

/**
 * @brief Provides the functionality for target 9 game.
 */
class GameLogic
{
private:
    int board[MAX_SIZE][MAX_SIZE];
    int num_moves;

    struct Move
    {
        int row;
        int col;
    };

    Stack<Move> moves;
    Stack<Move> solution;

public:
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
    bool isWin() const;

    /**
     * @brief Make a move in the game. Increments all values in given row and column by one. If value in board was 9, sets it to 1.
     * @param move move of struct Move containing row and col members. {row, col}.
     */
    void makeMove(Move move);

    /**
     * @brief Getter function to get a value from the board.
     * @param move move of struct Move containing row and col members. {row, col}.
     * @return Value in a given row and column.
     */
    int getBoardValue(Move move);
};

#endif // GAMELOGIC_H

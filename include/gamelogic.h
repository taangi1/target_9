#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#define MAX_SIZE 3

#include "stack.h"

class GameLogic
{
public:
    GameLogic();
private:
    int board[MAX_SIZE][MAX_SIZE];
    Stack<int> moves;
    
};

#endif // GAMELOGIC_H

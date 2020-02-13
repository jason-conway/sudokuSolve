#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define boardSize 9
#define boxSize 3

uint16_t blankCellRow;
uint16_t blankCellColumn;
int attempts = 0;

bool getBlankCells(uint16_t board[boardSize][boardSize]);

bool valuePossible(uint16_t board[boardSize][boardSize], uint16_t row, uint16_t column, uint16_t value);

bool solveBoard(uint16_t board[boardSize][boardSize]) 
{   
    attempts += 1;
    if (!getBlankCells(board))
    {
        return true;
    }

    uint16_t row = blankCellRow;
    uint16_t column = blankCellColumn;

    for (uint16_t value = 1; value <= 9; value++) 
    { 
        if (valuePossible(board, row, column, value)) 
        { 
            board[row][column] = value;
  
            if (solveBoard(board))
            {
                return true; 
            }
            board[row][column] = 0;
        } 
    } 
    return false; 
} 

bool getBlankCells(uint16_t board[boardSize][boardSize])
{
    for (uint16_t i = 0; i < boardSize; i++)
    {
        for (uint16_t j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 0)
            {   
                blankCellRow = i;
                blankCellColumn = j;
                return true;
            }
        }
    }
    return false;
}

bool valueInRow(uint16_t board[boardSize][boardSize], uint16_t row, uint16_t value)
{
    for (uint16_t i = 0; i < boardSize; i++)
    {
        if (board[row][i] == value)
        {
            return true;
        }
    }
    return false;
    
}

bool valueInColumn(uint16_t board[boardSize][boardSize], uint16_t column, uint16_t value)
{
    for (size_t i = 0; i < boardSize; i++)
    {
        if (board[i][column] == value)
        {
            return true;
        }
    }
    return false;
}

bool valueInBox(uint16_t board[boardSize][boardSize], uint16_t row, uint16_t column, uint16_t value)
{
    for (size_t i = 0; i < boxSize; i++)
    {
        for (size_t j = 0; j < boxSize; j++)
        {
            if (board[i + row][j + column] == value)
            {
                return true;
            }
        }
    }
    return false;
}

bool valuePossible(uint16_t board[boardSize][boardSize], uint16_t row, uint16_t column, uint16_t value)
{
    return board[row][column] == 0 && !valueInRow(board, row, value) && !valueInColumn(board, column, value) && !valueInBox(board, row - row % 3, column - column % 3, value);
}

void stdOutBoard(uint16_t board[boardSize][boardSize])
{
    for (size_t i = 0; i < boardSize; i++)
    {
        for (size_t j = 0; j < boardSize; j++)
        {
            printf("%2d", board[i][j]);
        }

        printf("\n");
    }
}

int main(void)
{
    uint16_t board[9][9] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 3, 6, 0, 0, 0, 0, 0},
                            {0, 7, 0, 0, 9, 0, 2, 0, 0},
                            {0, 5, 0, 0, 0, 7, 0, 0, 0},
                            {0, 0, 0, 0, 4, 5, 7, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0, 3, 0},
                            {0, 0, 1, 0, 0, 0, 0, 6, 8},
                            {0, 0, 8, 5, 0, 0, 0, 1, 0},
                            {0, 9, 0, 0, 0, 0, 4, 0, 0}};

    clock_t timeBegin = clock();

    if (solveBoard(board) == true)
    {
        stdOutBoard(board);
    }
    else
    {
        printf("No Solution\n"); 
    }
         
    clock_t timeEnd = clock();
    double execTime = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;
    
    printf("Time to solve: %f\n", execTime);
    printf("Took %d attemps\n", attempts);

    return 0;
}
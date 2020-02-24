#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define boardSize 9
#define boxSize 3

uint16_t blankCellRow;
uint16_t blankCellColumn;

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
    uint16_t board[9][9];
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            printf("Enter element [%lu, %lu] : ",i+1,j+1);
            scanf("%hu",&board[i][j]);
        }
    }

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
    
    printf("\nTime to solve: %f\n", execTime);

    return 0;
}
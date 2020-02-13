#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define numRows 9
#define numColumns 9 

struct sodukuBoard
{
    /* data */
};

struct sudokuCell
{
    /* data */
};

uint16_t potentialValues[9];


bool valuePossible(u_int16_t row, u_int16_t column, uint16_t value)
{
    bool possibility = false;


    return possibility;
}

bool valueInRow(uint16_t row, uint16_t value)
{
    for (size_t i = 0; i <= numRows; i++)
    {
        /* code */
    }
    
}

bool valueInColumn(uint16_t column, uint16_t value)
{
    for (size_t i = 0; i <= numColumns; i++)
    {
        /* code */
    }
}
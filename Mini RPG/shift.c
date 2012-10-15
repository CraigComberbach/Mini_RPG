#include <stdio.h>
#include <stdlib.h>
#include "gridDimension.h"
#include "shift.h"

char barrierCheck(char grid[width][height], char userInput)
{
    int     middleRow, middleColumn;

    //Determines middle element
    middleRow = (height - 1) / 2;
    middleColumn = (width - 1) / 2;

    switch(userInput)
    {
     case 'K':
        if(grid[middleColumn-1][middleRow] == ' ')
            break;
        else
            return barrierFound;
     case 'P':
        if(grid[middleColumn][middleRow+1] == ' ')
            break;
        else
            return barrierFound;
        break;
     case 'M':
        if(grid[middleColumn+1][middleRow] == ' ')
            break;
        else
            return barrierFound;
        break;
     case 'H':
        if(grid[middleColumn][middleRow-1] == ' ')
            break;
        else
            return barrierFound;
        break;
    }

    return userInput;
}

void shiftRight(char grid[width][height])
{
    int     buffer[height];
    int     x, y;

    //Stores the right hand side in the buffer variable
    for(y = 0; y < height; y++)
            buffer[y] = grid[width-1][y];

    //Shifts the remaining values
    for(y = 0; y < height; y++)
        for(x = width; x > 0; x--)
            grid[x][y] = grid[x-1][y];

    //Places the buffered values on the left side
    for(y = 0; y < height; y++)
        grid[0][y] = buffer[y];

    return;
}

void shiftLeft(char grid[width][height])
{
    int     buffer[height];
    int     x, y;

    //Stores the left hand side in the buffer variable
    for(y = 0; y < height; y++)
            buffer[y] = grid[0][y];

    //Shifts the remaining values
    for(y = 0; y < height; y++)
        for(x = 0; x < (width - 1); x++)
            grid[x][y] = grid[x+1][y];

    //Places the buffered values on the right side
    for(y = 0; y < height; y++)
        grid[width-1][y] = buffer[y];

    return;
}

void shiftUp(char grid[width][height])
{
    int     buffer[width];
    int     x, y;

    //Stores the top in the buffer variable
    for(x = 0; x < width; x++)
            buffer[x] = grid[x][0];

    //Shifts the remaining values
    for(x = 0; x < width; x++)
        for(y = 0; y < (height-1); y++)
            grid[x][y] = grid[x][y+1];

    //Places the buffered values on bottom
    for(x = 0; x < width; x++)
        grid[x][(height-1)] = buffer[x];

    return;
}

void shiftDown(char grid[width][height])
{
    int     buffer[width];
    int     x, y;

    //Stores the bottom in the buffer variable
    for(x = 0; x < width; x++)
            buffer[x] = grid[x][height-1];

    //Shifts the remaining values
    for(x = 0; x < width; x++)
        for(y = (height-1); y > 0; y--)
            grid[x][y] = grid[x][y-1];

    //Places the buffered values on top
    for(x = 0; x < width; x++)
        grid[x][0] = buffer[x];

    return;
}

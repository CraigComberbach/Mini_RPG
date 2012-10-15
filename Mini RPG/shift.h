#include "gridDimension.h"

void shiftRight(char grid[width][height]);
void shiftLeft(char grid[width][height]);
void shiftUp(char grid[width][height]);
void shiftDown(char grid[width][height]);
char  barrierCheck(char grid[width][height], char userInput);

#define barrierFound    0x07 //ASCII beep

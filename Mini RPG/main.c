#include <stdio.h>
#include <stdlib.h>
#include "shift.h"
#include "gridDimension.h"
#include "config.h"

#define BEEP    printf("\a");

void printGrid(char grid[width][height]);
void printWindow(char grid[width][height], int windowWidth, int windowHeight);
void initializeGrid(char grid[width][height]);

int main()
{
    //Fill grid from top left down
    char    grid[width][height] = {
    {"2                   1"},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"         ABC         "},
    {"         H D         "},
    {"         G E         "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"                     "},
    {"3                   4"}
    };
        /*
        {'2',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
        {' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ','',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','A','B','C',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','G',' ','E',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'3',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','4'},
        };*/

    char    userInput = '\0';
    int     windowHeight = 5,
            windowWidth = 5;

    //Display the grid
    printGrid(grid);

    while(userInput != '5')
    {
/*        //Movement options
        printf("\nArrow keys to shift grid\n");

        //Meta Options
        printf("\n1\tReinitialize Grid"
               "\n3\tToggle Window or full screen"
               "\n5\tClose Program"
               "\n7\tChange window settings");
*/
        //Get the users keystroke, if it is a null character, read in again (Allows the detection of arrow keys)
        while((userInput = getch()) == '\0');

        //Check for barriers and shift if none found
        userInput = barrierCheck(grid, userInput);

        //Determine what to do with input
        switch(userInput)
        {
            case 'H'://Up key
                shiftDown(grid);
                break;
            case 'P'://Down key
                shiftUp(grid);
                break;
            case 'K'://Left key
                shiftRight(grid);
                break;
            case 'M'://Right key
                shiftLeft(grid);
                break;
            case '1':
                initializeGrid(grid);
                break;
            case '3':
                config ^= 0x01;
                break;
            case '7':
                system("cls");
                while(printf("Height "), scanf("%d", &windowHeight), (windowHeight > height) || (windowHeight < 3) || !(windowHeight % 2));
                while(printf("Width "), scanf("%d", &windowWidth), (windowWidth > width) || (windowWidth < 3) || !(windowWidth % 2));
                break;
            case barrierFound:
                BEEP;
                break;
//            default:
//                printf("/nEpic Fail/n");
//                printf("\n%d\t%s\n", sizeof(userInput), userInput);
//                scanf("%1c", &userInput);
        }

        //Prints the grid for all to see
        if(config & 0x01)
            printWindow(grid, windowWidth, windowHeight);
        else
            printGrid(grid);

    }
    return 0;
}

//Prints the contents of the grid onto the display
void printGrid(char grid[width][height])
{
    int     x, y,
            middleRow, middleColumn;

    //Clear screen for better formating
    system("cls");

    //Makes the top of the window space
    for(x = 0; x < (width+2); ++x)
//        printf("-");
        putchar('-');

    //Puts a new line in for formating
//    printf("\n");
    putchar('\n');

    //Determines middle element
    middleRow = (height - 1) / 2;
    middleColumn = (width - 1) / 2;

    //Prints out the new table after shifting
    for(y = 0; y < height; y++)
    {
//        printf("|");
        putchar('|');
        for(x = 0; x < width; x++)
        {
            if((x == middleColumn) && (y == middleRow))
//                printf("P");
                putchar('P');
            else
//                printf("%c", grid[x][y]);
                putchar(grid[x][y]);
        }
        printf("|\n");

    }

     //Makes the bottom of the window space
    for(x = 0; x < (width+2); ++x)
//        printf("-");
        putchar('_');

    //For formating
//    printf("\n");
    putchar('\n');

    return;
}

void initializeGrid(char grid[width][height])
{
    int     x, y;
    char    z = 'A';

    //Fill grid with numbers
    for(y = 0; y < height; y++)
        for(x = 0; x < width; x++)
            grid[x][y] = z++;

    return;
}

void printWindow(char grid[width][height], int windowWidth, int windowHeight)
{
    int     x, y,
            right, top, //Used for defining the top right corner of the grid
            middleRow, middleColumn;

    //defines the upper right window boundary
    right = (width - windowWidth) / 2;
    top = (height - windowHeight) / 2;

    //Determines middle element
    middleRow = (windowHeight - 1) / 2 + right;
    middleColumn = (windowWidth - 1) / 2 + top;

    //Clear screen for better formating
    system("cls");

    //Makes the top of the window space
    for(x = 0; x < (windowWidth + 2); ++x)
        printf("-");

    //Puts a new line in for formating
    printf("\n");

    //Prints out the new table after shifting
    for(y = top; y < (top + windowHeight); y++)
    {
        printf("|");
        for(x = right; x < (right + windowWidth); x++)
            if((x == middleColumn) && (y == middleRow))
                printf("P");
            else
                printf("%c", grid[x][y]);
        printf("|\n");
    }
    //Makes the bottom of the window space
    for(x = 0; x < (windowWidth + 2); ++x)
        printf("-");

    //For formatting
    printf("\n");

    return;

}

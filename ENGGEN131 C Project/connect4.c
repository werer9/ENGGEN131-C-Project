/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
    Name: Caelan Murch
    ID: 234790019
    Github URL: https://github.com/werer9/ENGGEN131-C-Project
 */

//Swap array element i and j around
void Swap(int *values, int i, int j)
{
    int temp;
    temp = values[i];
    values[i] = values[j];
    values[j] = temp;
}

//Iterate over array, swap array elements if in wrong order
void Bubble(int *values, int length)
{
    for (int i = 0; i < length - 1; i++) {
        if (values[i] < values[i+1]) {
            Swap(values, i, i+1);
        }
    }
}

//Function to use bubble sort to find order of values in Second Place prize

void Sort(int *values, int length)
{
    //Call bubble sort function as many times necessary to sort array in
    //order from large to small
    
    for (int i = 0; i < length; i++) {
        Bubble(values, length);
    }
}

//Multiply an integer by any exponent greater than 1
//Input: number, exponent
int power(int num, int exp)
{
    //Number to multiply by
    int numOriginal;
    numOriginal = num;
    for (int i = 1; i < exp; i++) {
        //Keep multiplying number by original number until
        //multplied to exponent, exp
        num = num * numOriginal;
    }
    
    return num;
}

int SecondPlacePrize(int prize1, int prize2, int prize3)
{
    //Put prizes into array
    int values[] = {prize1, prize2, prize3};
    //Arrange prizes from large to small
    Sort(values, 3);
    //Return value of middle element in array (2nd place)
    return values[1];
}

int FourInARow(int values[], int length)
{
    for (int i = 0; i < length-3; i++) {
        //Declare boolean to check all numbers are the same
        int check;
        check = values[i] == values[i+1] && values[i] == values[i+2] && values[i] == values[i+3];
        //If boolean is true return value of i
        if (check)
            return i;
    }
    
    //Default return value if no numbers are found to be in a row
    return -1;
}

int BinaryToDecimal(int binary)
{
    int decimal, number, remainder, i;
    number = binary;
    //Set LSF to LSB
    decimal = number % 10;
    number = number / 10;
    
    //First digit calculated before loop
    i = 1;
    while (number != 0) {
        //Find remainder divided by 10
        remainder = number % 10;
        //Divide original number by 10
        number = number / 10;
        //If remainder = 1, incease decimal by 2^i
        decimal = decimal + remainder * power(2, i);
        i++;
    }
    
    //return decimal
    return decimal;
}

double MedianAbility(double abilities[], int length)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    return (abilities[0]+length)-(abilities[0]+length);
}

void RemoveSpaces(char *name)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    name[0] = '\0';
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    board[0][0] = size-size-1;
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    *lastRow = 0;
    *lastCol = 0;
    board[0][0] = (size+side+move+player)-(size+side+move+player);
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    return (board[0][0]+size+player+row+col)-(board[0][0]+size+player+row+col);
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    board[0][0] = size-size;
    boardString[0] = '\0';
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    *side = 'N';
    *move = 0;
    board[0][0] = (size+player)-(size+player);
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
    // This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
    // referred to below.  Fix this function by *deleting this comment* and the code below, and
    // writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
    *side = 'N';
    *move = 0;
    board[0][0] = (size+player)-(size+player);
}

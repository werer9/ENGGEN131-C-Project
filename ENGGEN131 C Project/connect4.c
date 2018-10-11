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

//Swap array element i and j around for double
void SwapDouble(double *values, int i, int j)
{
    double temp;
    temp = values[i];
    values[i] = values[j];
    values[j] = temp;
}

//Iterate over array, swap array elements if in wrong order for double
void BubbleDouble(double *values, int length)
{
    for (int i = 0; i < length - 1; i++) {
        if (values[i] < values[i+1]) {
            SwapDouble(values, i, i+1);
        }
    }
}

//Function to use bubble sort to find order of values in Second Place prize for double

void SortDouble(double *values, int length)
{
    //Call bubble sort function as many times necessary to sort array in
    //order from large to small
    
    for (int i = 0; i < length; i++) {
        BubbleDouble(values, length);
    }
}

//Multiply an integer by any exponent greater than 1
//Input: number, exponent
int Power(int num, int exp)
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

int isFourInARow(int player, int board[MAX_SIZE][MAX_SIZE], int size) {
    //Think about a more efficient implementation + diagonal implementation
    
    for (int i = 0; i < size-4; i++) {
        for (int j = 0; j < size-4; j++) {
            if (board[i][j] == player && board[i + 1][j] == player &&
                board[i + 2][j] == player && board[i + 3][j] == player) {
                return 1;
            } else if (board[i][j] == player && board[i][j + 1] == player &&
                  board[i][j + 2] == player && board[i][j + 3] == player) {
                return 1;
            }
        }
    }
    return 0;
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
    //Update number
    number = number / 10;
    
    //First digit calculated before loop
    i = 1;
    while (number != 0) {
        //Find remainder divided by 10
        remainder = number % 10;
        //Divide original number by 10
        number = number / 10;
        //If remainder = 1, incease decimal by 2^i
        decimal = decimal + remainder * Power(2, i);
        i++;
    }
    
    //return decimal
    return decimal;
}

double MedianAbility(double abilities[], int length)
{
    double median;
    
    SortDouble(abilities, length);
    
    if (length % 2 == 0) {
        median = (abilities[length/2 - 1] + abilities[length/2])/2;
    } else {
        median = abilities[length/2];
    }
    
    return median;
}

void RemoveSpaces(char *name)
{
    int i;
    i = 0;
    //Iterate through entire string
    while (name[i] != '\0') {
        //If there are two spaces in a row
        if (name[i] == ' ' && name[i+1] == ' ') {
            int j;
            j = i+1;
            //Move all characters back an index
            //i.e remove a space
            while (name[j] != '\0') {
                name[j] = name[j+1];
                j++;
            }
        } else {
            //If there aren't two consecutive spaces check next character
            i++;
        }
        
    }
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
    if (size > MAX_SIZE || size < 4) {
        printf("Error, size must be between 4 and 10 inclusive!");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
    
    if (size % 2 == 0) {
        board[size/2][size/2] = 3;
        board[(size/2) - 1][size/2] = 3;
        board[size/2][(size/2) - 1] = 3;
        board[(size/2) - 1][(size/2) - 1] = 3;
    } else {
        board[size/2][size/2] = 3;
    }
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
    int isVertical, i;
    
    //Check which side the piece is being added
    //Check if peice will move vertical and which
    //index it will start from
    switch (side) {
        case 'N':
            isVertical = 1;
            i = 0;
            break;
        case 'E':
            isVertical = 0;
            i = size-1;
            break;
        case 'W':
            isVertical = 0;
            i = 0;
            break;
        case 'S':
            isVertical = 1;
            i = size-1;
            break;
        default:
            //TODO: Check what default should be...
            printf("Error, invalid direction!");
            return;
    }
    
    //If it is horizontal
    if (!isVertical) {
        if (i == 0) { //Starting from left
            board[move][i] = player;
            while (board[move][i + 1] == 0 && i < size - 1) {
                //Move piece until obstacle or end of board
                board[move][i + 1] = player;
                board[move][i] = 0;
                i++;
            }
        } else if (i == size-1) { //Starting from right
            board[move][i] = player;
            while (board[move][i - 1] == 0 && i > 0) {
                //Move piece until obstacle or end of board
                board[move][i - 1] = player;
                board[move][i] = 0;
                i--;
            }
        }
        
        //Record position the piece stops at
        *lastRow = move;
        *lastCol = i;
    } else { //If it is vertical
        if (i == 0) { //Starting from top
            board[i][move] = player;
            while (board[i + 1][move] == 0 && i < size - 1) {
                //Move piece until obstacle or end of board
                board[i + 1][move] = player;
                board[i][move] = 0;
                i++;
            }
        } else if (i == size-1) { //Starting from bottom
            board[i][move] = player;
            while (board[i - 1][move] == 0 && i > 0) {
                //Move piece until obstacle or end of board
                board[i - 1][move] = player;
                board[i][move] = 0;
                i--;
            }
        }
        
        //Record position piece stops at 
        *lastRow = i;
        *lastCol = move;
    }
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
    int zeroCount;
    zeroCount = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0)
                zeroCount++;
        }
    }
    
    if (zeroCount == 0) {
        return player;
    }
    
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

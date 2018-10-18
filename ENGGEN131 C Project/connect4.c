/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
    Name: Caelan Murch
    ID: 234790019
 */

//Helper function prototypes
void Swap(int *values, int i, int j);
void Bubble(int *values, int length);
void Sort(int *values, int length);
void SwapDouble(double *values, int i, int j);
void BubbleDouble(double *values, int length);
void SortDouble(double *values, int length);
int Power(int num, int exp);
void PickRandomSide(char *side, int *move, int size);
void ConstructBorder(int size, char *boardString);
void GetWinningMove(int board[MAX_SIZE][MAX_SIZE], int i, int j, int size, char *side, int *move);


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
	//Do nothing is size is bigger than 10
	if (size > MAX_SIZE || size < 4) {
        printf("Error, size must be between 4 and 10 inclusive!");
        return;
    }
	
	//Make the dimension sizexsize 0
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
	
	//Make center of sizexsize 3
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
            printf("Error, invalid direction!");
            return;
    }
    
    //If it is horizontal
    if (!isVertical) {
        //Do not place token if token is at edge of board
		if (board[move][i] != 0) {
			*lastRow = -1;
			*lastCol = -1;
			return;
		} else if (i == 0) { //Starting from left
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
        //Do not place token if token is at edge of board
		if (board[i][move] != 0) {
			*lastRow = -1;
			*lastCol = -1;
			return;
		} else if (i == 0) { //Starting from top
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
	//Check who made last move to fill board
    int zeroCount;
    zeroCount = 0;
    for (int i = 0; i < size; i++) {
        if (board[i][0] == 0 || board[0][i] == 0 || board[size-1][i] == 0 || board[i][size-1] == 0)
			zeroCount++;
    }
    
    if (zeroCount == 0) {
        return player;
    }
    
    //Check 4 in a row in any direction and check this is part of row and col
    //Coordinates passed in as function parameter
	
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == player) {
                //Check vertical 4 in a row
                if (i < size-2) {
                    if (board[i+1][j] == player && board[i+2][j] == player
                        && board[i+3][j] == player
                        && (i <= row <= i+3) && col == j)
                        return player;
                }
                //Check horizontal 4 in a row
                if (j < size-2) {
                    if (board[i][j+1] == player && board[i][j+2] == player
                        && board[i][j+3] == player
                        && (j <= col <= j+3) && row == i)
                        return player;
                }
                //Check diagonal 4 in a row
                if (i > 0 && j > 0 && i < size-2 && j < size-2) {
                    if (board[i-1][j-1] == player && board[i+1][j+1] == player
                        && board[i+2][j+2] == player
                        && (i-1 <= col <= i+2) && (j-1 <= row <= j+2))
                        return player;
                    if (board[i-1][j+1] == player && board[i-2][j+2] == player
                        && board[i+1][j-1] == player
                        && (i-1 <= col <= i+2) && (j-1 <= row <= j+2))
                        return player;
                    if (board[i-1][j+1] == player && board[i+1][j-1] == player
                        && board[i+2][j-2] == player
                        && (i-1 <= col <= i+2) && (j-1 <= row <= j+2))
                        return player;
                }
                
                if (i > 0 && j > 1 && i < size-2 && j < size-1) {
                    if (board[i-1][j+1] == player && board[i+1][j-1] == player
                        && board[i+2][j-2] == player
                        && (i-1 <= col <= i+2) && (j-1 <= row <= j+2))
                        return player;
                }
            }
        }
    }
    
    //return 0 if none of conditions for game win are satisfied
    return 0;
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
    ConstructBorder(size, boardString);
    
    int count;
    count = (size+5)*2 + 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 3){
                boardString[count] = '#';
            } else if (board[i][j] == 1) {
                boardString[count] = 'X';
            } else if (board[i][j] == 2) {
                boardString[count] = 'O';
            }
            count++;
        }
        count += 5;
    }
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	time_t t;
	srand((unsigned) time(&t));
	int isClear;
	
	
	//Pick a random side and move if it is not already taken
	PickRandomSide(side, move, size);
	isClear = 0;
	while (!isClear) {
		switch(*side) {
			case 'N':
				if (board[0][*move] != 0) {
					PickRandomSide(side, move, size);
					isClear = 0;
				} else {
					isClear = 1;
				}
				break;
			case 'E':
				if (board[*move][size-1] != 0) {
					PickRandomSide(side, move, size);
					isClear = 0;
				} else {
					isClear = 1;
				}
				break;
			case 'S':
				if (board[size-1][*move] != 0) {
					PickRandomSide(side, move, size);
					isClear = 0;
				} else {
					isClear = 1;
				}
				break;
			case 'W':
				if (board[*move][0] != 0) {
					PickRandomSide(side, move, size);
					isClear = 0;
				} else {
					isClear = 1;
				}
				break;
			default:
				isClear = 1;
				break;
		}
	}
	
	//Make a winning move
	for (int i = 1; i < size-1; i++) {
		for (int j = 1; j < size-1; j++) {
			//If the piece is a player piece
			if (board[i][j] == 1 || board[i][j] == 2) {
				int piece = board[i][j];
				//Touching edge closest zero = front
				int isFront = 0; int isBack = 0;
				//Check if the 3 in a row area is touching any edges
				if (i-1 == 0 || j-1 == 0) {
					isFront = 1;
				}
				
				if (i+1 == size-1 || j+1 == size-1) {
					isBack = 1;
				}
				
				//Vertical
				if (board[i-1][j] == piece && board[i+1][j] == piece) {
					if (isBack && isFront) {
					} else if (isFront) {
						GetWinningMove(board, i+2, j, size, side, move);
					} else if (isBack) {
						GetWinningMove(board, i-2, j, size, side, move);
					} else {
						GetWinningMove(board, i+2, j, size, side, move);
						GetWinningMove(board, i-2, j, size, side, move);
					}
				}
				
				if (board[i][j-1] == piece && board[i][j+1] == piece) { //Horizontal
					if (isBack && isFront) {
					} else if (isFront) {
						GetWinningMove(board, i, j+2, size, side, move);
					} else if (isBack) {
						GetWinningMove(board, i, j-2, size, side, move);
					} else {
						GetWinningMove(board, i, j+2, size, side, move);
						GetWinningMove(board, i, j-2, size, side, move);
					}
				}
				
				if (board[i-1][j-1] == piece && board[i+1][j+1] == piece) { //Diagonal 1
					if (isBack && isFront) {
					} else if (isFront) {
						GetWinningMove(board, i+2, j+2, size, side, move);
					} else if (isBack) {
						GetWinningMove(board, i-2, j-2, size, side, move);
					} else {
						GetWinningMove(board, i+2, j+2, size, side, move);
						GetWinningMove(board, i-2, j-2, size, side, move);
					}
				}
				
				if (board[i-1][j+1] == piece && board[i+1][j-1] == piece) { //Diagonal 2
					if (isBack && isFront) {
					} else if (isFront) {
						GetWinningMove(board, i-2, j+2, size, side, move);
					} else if (isBack) {
						GetWinningMove(board, i+2, j-2, size, side, move);
					} else {
						GetWinningMove(board, i-2, j+2, size, side, move);
						GetWinningMove(board, i+2, j-2, size, side, move);
					}
				}
			}
		}
	}
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//Do the same thing as move bot 1
	GetMoveBot1(board, size, player, side, move);
}

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

//Choose a random side of the board and a random move
void PickRandomSide(char *side, int *move, int size)
{
	
		//Choose a random side
		switch ((rand() % 4) + 1) {
			case 1:
				*side = 'N';
				break;
			case 2:
				*side = 'E';
				break;
			case 3:
				*side = 'S';
				break;
			case 4:
				*side = 'W';
				break;
			default:
				*side = 'N';
				break;
		}
	
		//Choose a random move
		*move = rand() % size;
}

//Create border with infromation on sides and moves
void ConstructBorder(int size, char *boardString) {
	int count;
	count = 0;
	for (int i = 0; i < size + 4; i++) {
		for (int j = 0; j < size + 5; j++) {
			if (j == size + 4) { // North of south side
				boardString[count] = '\n';
			} else if (i == 0 || i == size + 3) {
				if (j < 2 || j > size + 1) {
					boardString[count] = '-';
				} else {
					boardString[count] = (i == 0) ? 'N' : 'S';
				}
			} else if (i == 1 || i == size + 2) {
				if (j < 2 || j > size + 1) {
					boardString[count] = '-';
				} else {
					boardString[count] = '0' + (j - 2);
				}
			} else {
				if (j == 0) { //West side
					boardString[count] = 'W';
					boardString[count + 1] = '0' + (i - 2);
					count++;
					j++;
				} else if (j == size + 2) { // East side
					boardString[count] = '0' + (i - 2);
					boardString[count + 1] = 'E';
					count++;
					j++;
				} else {
					boardString[count] = '.';
				}
			}
			count++;
		}
	}
	boardString[count] = '\0';
}


//Find if there is a pathway for a piece to a certain position
void GetWinningMove(int board[MAX_SIZE][MAX_SIZE], int i, int j, int size ,char *side, int *move) {
	int nonZero = 0;
	for (int k = i; k < size; k++) { //Check down is clear
		if (board[k][j] != 0) {
			nonZero++;
			break;
		}
	}
	
	if (nonZero == 0) {
		*side = 'S';
		*move = j;
		return;
	} else {
		nonZero = 0;
	}
	
	for (int k = i; k >= 0; k--) { //Check up is clear
		if (board[k][j] != 0) {
			nonZero++;
			break;
		}
	}
	
	if (nonZero == 0) {
		*side = 'N';
		*move = j;
		return;
	} else {
		nonZero = 0;
	}
	
	for (int k = j; k >= 0; k--) { //Check left is clear
		if (board[k][j] != 0) {
			nonZero++;
			break;
		}
	}
	
	if (nonZero == 0) {
		*side = 'W';
		*move = i;
		return;
	} else {
		nonZero = 0;
	}
	
	for (int k = j; k < size; k++) { //Check right is clear
		if (board[i][k] != 0) {
			nonZero++;
			break;
		}
	}
	
	if (nonZero == 0) {
		*side = 'E';
		*move = i;
		return;
	} else {
		nonZero = 0;
	}
	
	*side = *side;
	*move = *move;
}

/*********************************************************************
** Program name:  Predator-Prey Game (Group Project, CS 162-400, Winter 2019)
** Author:        Group 16
** Date:          February 2, 2019
** Description:   Board.cpp, Board Class Implementation
**********************************************************************/

#include <iostream>   //Console input and output
#include <iomanip>    //Console output formatting
#include "Board.hpp"
#include "Critter.hpp"
#include "Doodlebug.hpp"
#include "Ant.hpp"

using std::cout;
using std::endl;


//Constructors and Deconstructor
Board::Board()
{

    //instantiate the game board
    gameBoard = new Critter**[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; i++)
    {
        gameBoard[i] = new Critter*[MAX_COLS];
    }

    //initialize board to null pointers;
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLS; j++)
        {
            gameBoard[i][j] = nullptr;
        }
    }

    //randomly place all the starting doodlebugs
    for (int counter = 0; counter < STARTING_DOODLEBUGS; counter++)
    {
        while (!addDoodlebug(rand() % 20, rand() % 20));  //picks random row/col, attempts to make Doodlebug
                                                          //if unsuccessful pick two more random row/col until success
    }

    //randomly place the all the starting ants
    for (int counter = 0; counter < STARTING_ANTS; counter++)
    {
        while (!addAnt(rand() % 20, rand() % 20));  //picks random row/col, attempts to make Ant
                                                    //if unsuccessful pick two more random row/col until success
    }
    printBoard();

}
//Extra Credit Constructor 
Board::Board(int rows, int cols, int numAnts, int numDoodles) {
    numRows = rows;
    numCols = cols;
    this->numAnts = numAnts;
    this->numDoodles = numDoodles;
    gameBoard = new Critter**[numRows];
    for (int i = 0; i < this->numRows; i++)
    {
        gameBoard[i] = new Critter*[numCols];
    }

    //initialize board to null pointers;
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            gameBoard[i][j] = nullptr;
        }
    }

    //randomly place all the starting doodlebugs
    for (int counter = 0; counter < this->numDoodles; counter++)
    {
        while (!addDoodlebug(rand() % numRows, rand() % numCols));  //picks random row/col, attempts to make Doodlebug
                                                          //if unsuccessful pick two more random row/col until success
    }

    //randomly place the all the starting ants
    for (int counter = 0; counter < this->numAnts; counter++)
    {
        while (!addAnt(rand() % numRows, rand() % numCols));  //picks random row/col, attempts to make Ant
                                                    //if unsuccessful pick two more random row/col until success
    }
    printBoard();
}; 

 //AW: constructor for extra credit, blank for now



/*********************************************************************
** Deconstructor EXTRA CREDIT
** Deconstructor deletes all dynamically created objects in the gameBoard Array.
** Tested with Valgrind 2/2/2019 7:49PM
*********************************************************************/
/*
Board::~Board()
{
    //Deallocate memory for the dynamic arrow.
    for (int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete gameBoard[i][j];
        }
        delete [] gameBoard[i];
    }
    delete [] gameBoard;
    gameBoard = nullptr;
}
*/
/*********************************************************************
** Deconstructor
** Deconstructor deletes all dynamically created objects in the gameBoard Array.
** Tested with Valgrind 2/2/2019 7:49PM
*********************************************************************/  

Board::~Board()
{
    //Deallocate memory for the dynamic arrow.
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLS; j++)
        {
            delete gameBoard[i][j];
        }
        delete [] gameBoard[i];
    }
    delete [] gameBoard;
    gameBoard = nullptr;
} 

//Functions
/*********************************************************************
** runGame() EXTRA CREDIT
** 
*********************************************************************/
/*
void Board::runGame(int numSteps)
{
    while(numSteps > 0)
    {
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)  //each move, iterate through the board
            {
                if(gameBoard[i][j] == nullptr) //we need to keep this test, because if we don't skip the nullptrs we try to deference them and that's bad
                {
                    cout << "Nothing here" << endl;  //for testing, remove later
                }
                else if(gameBoard[i][j]->getIsAnt())
                {
                    cout << "This is an ant" << endl;  //for testing, remove later
                    gameBoard[i][j]->move(gameBoard);
                }
            }
            cout << "Finished row " << i << endl;
            printBoard();
        }
        printBoard();
        numSteps--;  
    }
}
*/
/*********************************************************************
** runGame()
**ORIGINAL
*********************************************************************/
void Board::runGame(int numSteps)
{
    while(numSteps > 0)
    {
        /*************************************************************************
        ** The for loops are separated because ->move() affects the location
        ** of a Doodlebug which would give a seg fault for calling ->breed()
        ** directly after. (Robert)
        **********************************************************************/
        for(int i = 0; i < MAX_ROWS; i++){//doodlebugs move first
            for(int j = 0; j < MAX_COLS; j++)  {//each move, iterate through the board
                //if(gameBoard[i][j] == nullptr) //we need to keep this test, because if we don't skip the nullptrs we try to deference them and that's bad
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())  //These can be combined since the left-hand side will be evaluated first.
                {
                    //cout << "This is a doodlebug [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->incrementCounters();
                }
            }
        }
        for(int i = 0; i < MAX_ROWS; i++){//doodlebugs move first
            for(int j = 0; j < MAX_COLS; j++)  {//each move, iterate through the board
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    cout << "Trying to move [" << i << "][" << j << "]"  << endl;
                    gameBoard[i][j]->move(gameBoard);
                }
            }
        }
        for(int i = 0; i < MAX_ROWS; i++){//doodlebugs move first
            for(int j = 0; j < MAX_COLS; j++)  {//each move, iterate through the board
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    cout << "Trying to breed [" << i << "][" << j << "]"  << endl;
                    gameBoard[i][j]->breed(gameBoard);
                }
            }
        }
        for(int i = 0; i < MAX_ROWS; i++){//doodlebugs move first
            for(int j = 0; j < MAX_COLS; j++)  {//each move, iterate through the board
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    cout << "Trying to starve [" << i << "][" << j << "]"  << endl;
                    if (gameBoard[i][j]->starve())
                    {
                        delete gameBoard[i][j];
                        gameBoard[i][j] = nullptr;
                    }
                }
            }
        }
        cout << "Finished doodlebug move" << endl;
        printBoard();
        for(int i = 0; i < MAX_ROWS; i++) //ants move second
        {
            for(int j = 0; j < MAX_COLS; j++)  //each move, iterate through the board
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt()) //These can be combined since the left-hand side will be evaluated first.
                {
                    gameBoard[i][j]->incrementCounters(); //Consider moving this to separate for loop.
                }
            }
        }
        for(int i = 0; i < MAX_ROWS; i++) //ants move second
        {
            for(int j = 0; j < MAX_COLS; j++)  //each move, iterate through the board
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt()) //These can be combined since the left-hand side will be evaluated first.
                {
                    cout << "Ant trying to moved from [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->move(gameBoard);
                }
            }
        }
        for(int i = 0; i < MAX_ROWS; i++) //ants move second
        {
            for(int j = 0; j < MAX_COLS; j++)  //each move, iterate through the board
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt())
                {
                    cout << "Ant trying to breed from [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->breed(gameBoard);
                }
            }
        }
        printBoard();
        numSteps--;
    }
}

/*********************************************************************
** printBoard() EXTRA CREDIT
** This function prints the board to the console. 
*********************************************************************/
/*
void Board::printBoard()
{
    //Top border
    cout.width(numCols + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');

    for(int i = 0; i < numRows; i++)
    {
        cout << "|";
        for(int j = 0; j < numCols; j++)
        {
            if (gameBoard[i][j] == nullptr)
            { //it's empty
                cout << " ";
            }
            else if (gameBoard[i][j]->getIsDoodlebug())
            { //Is a doodlebug object.
                cout << "X";
            }
            else
            { //Is an ant.
                cout << "O";
            }
        }
        cout << "|\n";
    }
    //Bottom border
    cout.width(numCols + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');
}
*/
/*********************************************************************
** printBoard() ORIGINAL
** This function prints the board to the console.
*********************************************************************/

void Board::printBoard()
{
    //Top border
    cout.width(MAX_COLS + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');

    for(int i = 0; i < MAX_ROWS; i++)
    {
        cout << "|";
        for(int j = 0; j < MAX_COLS; j++)
        {
            if (gameBoard[i][j] == nullptr)
            { //it's empty
                cout << " ";
            }
            else if (gameBoard[i][j]->getIsDoodlebug())
            { //Is a doodlebug object.
                cout << "X";
            }
            else
            { //Is an ant.
                cout << "O";
            }
        }
        cout << "|\n";
    }
    //Bottom border
    cout.width(MAX_COLS + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');
}

/*********************************************************************
** addAnt(int, int)
** This function instantiates an Ant object to the gameBoard array.
** First it tests whether the space is empty (nullptr). If it is empty
** it continues and returns true. If the space is not empty, then the
** function returns false without adding anything to the space.
*********************************************************************/
bool Board::addAnt(int row, int col)
{
    if (gameBoard[row][col] == nullptr)  //if the board spot is unoccupied, make an Ant
    {
        gameBoard[row][col] = new Ant(row, col);   //AW: added (row, col) to Ant constructor call
        return true;
    }
    else  //if the board spot was occupied, return false
    {
        return false;
    }
}

bool Board::addDoodlebug(int row, int col)  //if the board spot is unoccupied, make a Doodlebug
{
    if (gameBoard[row][col] == nullptr)
    {
        gameBoard[row][col] = new Doodlebug(row, col); //AW: added (row, col) to Doodlebug constructor call
        return true;
    }
    else  //if the board spot was occupied, return false
    {
        return false;
    }
}

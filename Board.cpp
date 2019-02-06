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
Board::Board(int rows, int cols) {}; //AW: constructor for extra credit, blank for now

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
** runGame()
**
*********************************************************************/
void Board::runGame(int numSteps)
{
    while(numSteps > 0)
    {
        for(int i = 0; i < MAX_ROWS; i++){//doodlebugs move first
            for(int j = 0; j < MAX_COLS; j++)  {//each move, iterate through the board
                if(gameBoard[i][j] == nullptr) //we need to keep this test, because if we don't skip the nullptrs we try to deference them and that's bad
                {
                    cout << "Nothing here" << endl;  //for testing, remove later
                }
                else if(gameBoard[i][j]->getIsDoodlebug())
                {
                    cout << "This is a doodlebug" << endl;  //for testing, remove later
                    gameBoard[i][j]->incrementCounters();
                    cout << "Trying to move" << endl;
                    gameBoard[i][j]->move(gameBoard);
                    cout << "Trying to breed" << endl;
                    gameBoard[i][j]->breed(gameBoard);
                    cout << "Trying to starve" << endl;
                    gameBoard[i][j]->starve(gameBoard);
                }
            }
        }
        cout << "Finished doodlebug move" << endl;
        printBoard();

        for(int i = 0; i < MAX_ROWS; i++) //ants move second
        {
            for(int j = 0; j < MAX_COLS; j++)  //each move, iterate through the board
            {
                if(gameBoard[i][j] == nullptr) //we need to keep this test, because if we don't skip the nullptrs we try to deference them and that's bad
                {
                    cout << "Nothing here" << endl;  //for testing, remove later
                }
                else if(gameBoard[i][j]->getIsAnt())
                {
                    cout << "This is an ant" << endl;  //for testing, remove later
                    gameBoard[i][j]->incrementCounters();
                    gameBoard[i][j]->move(gameBoard);
                    //need to implement breed here
                }

            }
            cout << "Finished row " << i << endl;
            printBoard();
        }
        printBoard();
        numSteps--;  
    }
}

/*********************************************************************
** printBoard()
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

void Board::increaseAge()
{

}

void Board::critterAttach()
{

}

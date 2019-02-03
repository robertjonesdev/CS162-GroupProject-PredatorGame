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
    srand(time(NULL));
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
        while (!addDoodlebug(rand() % 20, rand() % 20)) { }
    }

    //ranomdly place the all the starting ants
    for (int counter = 0; counter < STARTING_ANTS; counter++)
    {
        while (!addAnt(rand() % 20, rand() % 20)) { }
    }
}

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
void Board::runGame()
{

}

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
            if (dynamic_cast<Ant*>(gameBoard[i][j]) != nullptr)
            { //Is an Ant object.
                cout << "O";
            }
            else if (dynamic_cast<Doodlebug*>(gameBoard[i][j]) != nullptr)
            { //Is a doodlebug object.
                cout << "X";
            }
            else
            { //Is empty.
                cout << " ";
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

bool Board::addAnt(int row, int col)
{
  if (gameBoard[row][col] == nullptr)
  {
      gameBoard[row][col] = new Ant;
      return true;
  }
  else
  {
      return false;
  }
}

bool Board::addDoodlebug(int row, int col)
{
    if (gameBoard[row][col] == nullptr)
    {
        gameBoard[row][col] = new Doodlebug;
        return true;
    }
    else
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

/***************************************************************
** Program name: Ant.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Ant class implementation file.
**               Ant is derived from the Critter class
** Methods:      Constructor, deconstructor
**               incrementCounters: void
**               breed(Critter, const int&, const int&):void
**               move(Critter, const int&, const int&):void
**               getIsAnt:bool
**               getIsDoodlebug:bool
**               getTotalAnts:static int
**               getNewAnts:static int
**               getDeadAnts:static int
**               resetStaticCounters:void
***************************************************************/
#include <cstdlib>      //Randon number generation
#include <iostream>     //Console output
#include "Ant.hpp"
#include "Board.hpp"

//Static variable initialization
int Ant::newAnts = 0;
int Ant::deadAnts = 0;
int Ant::totalAnts = 0;

/***************************************************************************
** Ant constructor
** Takes an int for the x axis and an int for the y axis
****************************************************************************/
Ant::Ant(int row, int col): Critter(row, col)
{
    this->row = row;
    this->col = col;
    //Increases the static member variable of total Ants in existence.
    Ant::totalAnts++;
    //Increase the static member variable counter of Ants created in a step.
    Ant::newAnts++;
}

/***************************************************************************
** Ant deconstrucotr
** Decreases the static variable for total number of ant objects.
****************************************************************************/
Ant::~Ant()
{
    //Decreases the static member variable of total Ants in existence.
    Ant::totalAnts--;
    //Increase the static member variable counter of Ants dying in a step.
    Ant::deadAnts++;
}

/***************************************************************************
** Ant::move functions
** Checks that breedingCounter is >= 3 and that there is an empty ajacent space. If so, creates new Ant
*****************************************************************************/
//Checks that breedingCounter is >= 3 and that there is an empty ajacent space. If so, creates new Ant
void Ant::breed(Critter*** gameBoard, const int& numRows, const int& numCols)
{
    if (this->breedingCounter >= 3) //change this to 0 to test breeding function
    {
        bool bred = false;
        while (!bred)  //loop until bred
        {
            bool upCheck, leftCheck, downCheck, rightCheck;  //bools to track whether all adjacent spaces have been checked.
            upCheck = leftCheck = downCheck = rightCheck = false;  //false = not checked, true = checked
            while (!(upCheck == true && downCheck == true && leftCheck == true && rightCheck == true))  //loop until all are true (i.e. all have been checked);
            {
                int breedDirection = rand() % 4;
                switch (breedDirection)
                {
                    case UP:
                    {
                        upCheck = true;
                        //Edge guard: if we're in the top row, do nothing.
                        if (this->row != 0)
                        {
                            //If the space is unoccupied then breed
                            if (gameBoard[this->row - 1][this->col] == nullptr)
                            {
                                gameBoard[this->row - 1][this->col] = new Ant(this->row - 1, this->col);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            }
                        }
                        break;
                    }
                    case RIGHT:
                    {
                        rightCheck = true;
                        //Edge guard: if we're in the right column, do nothing.
                        if (this->col != numCols - 1)
                        {
                            //If the space is unoccupied then breed
                            if (gameBoard[this->row][this->col + 1] == nullptr)
                            {
                                gameBoard[this->row][this->col + 1] = new Ant(this->row, this->col + 1);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            }
                        }
                        break;
                    }
                    case DOWN:
                    {
                        downCheck = true;
                        //Edge guard: f we're in the bottom row, do nothing.
                        if (this->row != numRows - 1)
                        {
                            //if the space is unoccupied breed
                            if (gameBoard[this->row + 1][this->col] == nullptr)
                            {
                                gameBoard[this->row + 1][this->col] = new Ant(this->row + 1, this->col);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            }
                        }
                        break;
                    }
                    case LEFT:
                    {
                        leftCheck = true;
                        //Edge guard: if we're in the left column, do nothing.
                        if (this->col != 0)
                        {
                            //if the space is unoccupied then breed
                            if (gameBoard[this->row][this->col - 1] == nullptr)
                            {
                                gameBoard[this->row][this->col - 1] = new Ant(this->row, this->col - 1);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            }
                        }
                        break;
                    }
                }
            }
            if (!bred) //if doodlebug hasn't bred after checking all 4 adjacent squares
            {
                bred = true; //break out of loop, but don't reset BreedingCounter.
            }
        }
    }
}

/***************************************************************************
** Ant::incrementCounters functions
** Increments breeding counter by 1
** Resets the internal flag whether the Ant has moved within the turn.
****************************************************************************/
void Ant::incrementCounters()
{
    ++this->breedingCounter;
    this->hasMovedToday = false;
}


/***************************************************************************
** Ant::move functions
** Moves to an empty adjacent space. If the first move fails, the Ant does not move
*****************************************************************************/
void Ant::move(Critter*** gameBoard, const int& numRows, const int& numCols)
{
    if (!this->hasMovedToday)
    {
      //AW: For reference: enum Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3}
      int moveDirection = rand() % 4;  //0, 1, 2, or 3.

      switch(moveDirection)
      {
        case UP:
        {
            //Edge guard: if we're in the top row, do nothing.
            if (this->row != 0)
            {
                //if the space is unoccupied, move there
                if (gameBoard[this->row - 1][this->col] == nullptr)
                {
                    gameBoard[this->row - 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row--;
                }
            }
            break;
        }
        case RIGHT:
        {
            //Edge guard: if we're in the right column, do nothing.
            if (this->col != numCols - 1)
            {
                //if the space is unoccupied, move there
                if(gameBoard[this->row][this->col + 1] == nullptr)
                {
                    gameBoard[this->row][this->col + 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col++;
                }
            }
            break;
        }
        case DOWN:
        {
            //Edge guard: If we're in the bottom row, do nothing.
            if (this->row != numRows - 1)
            {
                //If the space is unoccupied, move there
                if (gameBoard[this->row + 1][this->col] == nullptr)
                {
                    gameBoard[this->row + 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row++;
                }
            }
            break;
        }
        case LEFT:
        {
            //Edge guard: If we're in the left column, do nothing.
            if (this->col != 0)
            {
                //If the space is unoccupied, move there
                if (gameBoard[this->row][this->col - 1] == nullptr)
                {
                    gameBoard[this->row][this->col - 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col--;
                }
            }
            break;
        }
      }
      //Set the flag for the Ant that it is has moved already during the turn.
      //In the case the ant moves to the right or down, then the Board iteration
      //will not move it again.
      this->hasMovedToday = true;
  }
}

/***************************************************************************
** Accessor functions to determine if the called object is an Ant or Doodlebug.
** getIsAnt(): bool
** getIsDoodlebug(): bool
*****************************************************************************/
bool Ant::getIsAnt()
{
    return true;
}

bool Ant::getIsDoodlebug()
{
    return false;
}

/***************************************************************************
** Accessor functions for static variables
** getTotalAnts(): int
** getNewAnts(): int
** getDeadAnts(): int
*****************************************************************************/
int Ant::getTotalAnts()
{
    return Ant::totalAnts;
}

int Ant::getNewAnts()
{
    return Ant::newAnts;
}

int Ant::getDeadAnts()
{
    return Ant::deadAnts;
}

/***************************************************************************
** Modifier functions for static variables
** resetStaticCounters(): int
*****************************************************************************/
void Ant::resetStaticCounters()
{
    Ant::newAnts = 0;
    Ant::deadAnts = 0;
}

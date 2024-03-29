/***************************************************************
** Program name: Doodlebug.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Doodlebug class implementation file.
**               Doodlebug is derived from the Critter class
** Methods:      Constructor, deconstructor
**               incrementCounters: void
**               breed(Critter, const int&, const int&):void
**               move(Critter, const int&, const int&):void
**               starve:bool
**               getIsAnt:bool
**               getIsDoodlebug:bool
**               getTotalDoodlebugs:static int
**               getNewDoodlebugs:static int
**               getDeadDoodlebugs:static int
**               resetStaticCounters:void
***************************************************************/
#include <cstdlib>     		//Randon number generation
#include <iostream>         //Console output
#include "Doodlebug.hpp"
#include "Board.hpp"

//For reference: enum class Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3}

//Static variable initialization
int Doodlebug::newDoodlebugs = 0;
int Doodlebug::deadDoodlebugs = 0;
int Doodlebug::totalDoodlebugs = 0;

/***************************************************************************
** Doodlebug constructor
** Takes an int for the x axis and an int for the y axis
****************************************************************************/
Doodlebug::Doodlebug(int row, int col): Critter(row, col)
{
	this->row = row;
	this->col = col;
	this->starvingCounter = 0;
    //Increases the static member variable of total Doodlebugs in existence.
    Doodlebug::totalDoodlebugs++;
    //Increase the static member variable counter of Doodlebugs created in a step.
    Doodlebug::newDoodlebugs++;
}

/***************************************************************************
** Doodlebug deconstructor
** Decreases the static variable for total number of Doodlebug objects.
****************************************************************************/
Doodlebug::~Doodlebug()
{
    //Decreases the static member variable of total Doodlebugs in existence.
    Doodlebug::totalDoodlebugs--;
    //Increase the static member variable counter of Doodlebugs dying in a step.
    Doodlebug::deadDoodlebugs++;
}

/***************************************************************************
** Ant::incrementCounters functions
** Increments breeding counter and starving counter by 1
** Resets the internal flag whether the Doodlebug has moved within the turn.
****************************************************************************/
void Doodlebug::incrementCounters()
{
	++this->breedingCounter;
	++this->starvingCounter;
	this->hasMovedToday = false;
}

/***************************************************************************
** Doodlebug::starve():bool
** Removes Doodlebug if starvingCounter >= 3 and returns True to the
** Board class. Board class will delete the object.
****************************************************************************/
bool Doodlebug::starve()
{
	if(this->starvingCounter >= 3)
	{
        //Doodlebug is dead. Return true for the Board to delete.
		return true;
	}
    //Doodlebug is not dead. Remains alive and on the board.
	return false;
}

/***************************************************************************
** Doodlebug::breed()
** This function will breed the doodlebug in to more doodlebugs.
** Checks that breedingCounter is >= 8 and that there is an empty adjacent space.
**  If so, creates new Doodlebug
****************************************************************************/
void Doodlebug::breed(Critter*** gameBoard, const int& numRows, const int& numCols)
{
	if (this->breedingCounter >= 8)
	{
		bool bred = false;

		while (!bred)  //Continue looping until the Doodlebug breeds
		{
			bool upCheck, leftCheck, downCheck, rightCheck;  //bools to track whether all adjacent spaces have been checked.
			upCheck = leftCheck = downCheck = rightCheck = false;  //false = not checked, true = checked

			while(!(upCheck == true && downCheck == true && leftCheck == true && rightCheck == true))  //loop until all are true (i.e. all have been checked);
			{
				int breedDirection = rand() % 4;

				switch (breedDirection)
				{
					case UP:
                    {
					    upCheck = true;
						if (this->row != 0)
                        {  //if we're in the top row, do nothing.
							if (gameBoard[this->row - 1][this->col] == nullptr)
                            {  //if the space is unoccupied breed
							    gameBoard[this->row - 1][this->col] = new Doodlebug(this->row - 1, this->col);  //make a new doodlebug there
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
						if (this->col != numCols - 1)
                        {  //if we're in the right column, do nothing.
    						if (gameBoard[this->row][this->col + 1] == nullptr)
                            {  //if the space is unoccupied breed
        						gameBoard[this->row][this->col + 1] = new Doodlebug(this->row, this->col + 1);  //make a new doodlebug there
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
						if (this->row != numRows - 1)
                        {  //if we're in the bottom row, do nothing.
    						if(gameBoard[this->row + 1][this->col] == nullptr)
                            {  //if the space is unoccupied breed
        						gameBoard[this->row + 1][this->col] = new Doodlebug(this->row + 1, this->col);  //make a new doodlebug there
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
						if (this->col != 0)
                        {  //if we're in the left column, do nothing.
    						if (gameBoard[this->row][this->col - 1] == nullptr)
                            {  //if the space is unoccupied breed
        						gameBoard[this->row][this->col - 1] = new Doodlebug(this->row, this->col - 1);  //make a new doodlebug there
        						this->breedingCounter = 0;  //reset breeding counter
        						bred = true;  //exit outer loop condition
        						upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
    						}
                        }
                        break;
                    }
				}
			}
			if(!bred) //if doodlebug hasn't bred after checking all 4 adjacent squares
			{
				bred = true; //break out of loop, but don't reset BreedingCounter.
			}
		}
	}
}

/***************************************************************************
** Doodlebug::move()
** This function will move the Doodlebug. It moves to an adjacent space with an
** Ant if possible. If not, moves to an empty adjacent space. If surrounded by
** Doodlebugs, the Doodlebug does not move.
****************************************************************************/
void Doodlebug::move(Critter*** gameBoard, const int& numRows, const int& numCols)
{
    if (!this->hasMovedToday)
    {
    	bool hasEaten = false;

    	if((this->row != 0) && hasEaten == false)  //if we're in the top row, do nothing.
    	{
    		if (gameBoard[this->row - 1][this->col] != nullptr && gameBoard[this->row - 1][this->col]->getIsAnt()) //if there is an ant above,
    		{
    			delete gameBoard[this->row - 1][this->col];  //delete the ant
    			gameBoard[this->row - 1][this->col] = this;  //move into its space
    			gameBoard[this->row][this->col] = nullptr;   //set old space to nullptr
    			this->row--;  							     //update critter row
    			hasEaten = true;
                starvingCounter = 0;
    		}
    	}
    	if((this->row != numRows - 1) && hasEaten == false)  //if we're in the bottom row or we've already eaten, do nothing.
    	{
    		if (gameBoard[this->row + 1][this->col] != nullptr && gameBoard[this->row + 1][this->col]->getIsAnt()) //if there is an ant below,
    		{
    			delete gameBoard[this->row + 1][this->col];
    			gameBoard[this->row + 1][this->col] = this;
    			gameBoard[this->row][this->col] = nullptr;
    			this->row++;
    			hasEaten = true;
                starvingCounter = 0;
    		}
    	}
    	if((this->col != 0) && hasEaten == false)  //if we're in the left column or we've already eaten, do nothing.
    	{
    		if (gameBoard[this->row][this->col - 1] != nullptr && gameBoard[this->row][this->col - 1]->getIsAnt())
    		{
				delete gameBoard[this->row][this->col - 1];
				gameBoard[this->row][this->col - 1] = this;
				gameBoard[this->row][this->col] = nullptr;
				this->col--;
				hasEaten = true;
				starvingCounter = 0;
			}
		}
		if((this->col != numCols - 1) && hasEaten == false)  //if we're in the right column or we've already eaten, do nothing.
		{
			if (gameBoard[this->row][this->col + 1] != nullptr && gameBoard[this->row][this->col + 1]->getIsAnt())
			{
				delete gameBoard[this->row][this->col + 1];
				gameBoard[this->row][this->col + 1] = this;
				gameBoard[this->row][this->col] = nullptr;
				this->col++;
				hasEaten = true;
				starvingCounter = 0;
			}
		}
		if(hasEaten == false) //if we haven't eaten anything after checking all directions, then just move
		{
			int moveDirection = rand() % 4; //spot to move if no ants in adjacent cells

			switch (moveDirection)
			{
				case UP:
				{
					if (this->row != 0)
					{  //if we're in the top row, do nothing.
            			if (gameBoard[this->row - 1][this->col] == nullptr)
						{  //if the space is unoccupied, move
							gameBoard[this->row - 1][this->col] = this;
							gameBoard[this->row][this->col] = nullptr;
							this->row--;
						}
					}
					break;
				}
				case RIGHT:
				{
					if (this->col != numCols - 1)
					{  //if we're in the right column, do nothing.
						if (gameBoard[this->row][this->col + 1] == nullptr)
						{  //if the space is unoccupied, move
							gameBoard[this->row][this->col + 1] = this;
							gameBoard[this->row][this->col] = nullptr;
							this->col++;
						}
					}
					break;
				}
				case DOWN:
				{
					if (this->row != numRows - 1)
					{  //if we're in the bottom row, do nothing.
						if (gameBoard[this->row + 1][this->col] == nullptr)
						{  //if the space is unoccupied, move
							gameBoard[this->row + 1][this->col] = this;
							gameBoard[this->row][this->col] = nullptr;
							this->row++;
						}
					}
					break;
				}
				case LEFT:
				{
					if (this->col != 0)
					{  //if we're in the left column, do nothing.
						if (gameBoard[this->row][this->col - 1] == nullptr)
						{  //if the space is unoccupied, move
							gameBoard[this->row][this->col - 1] = this;
							gameBoard[this->row][this->col] = nullptr;
							this->col--;
						}
					}
					break;
				}
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
bool Doodlebug::getIsAnt()
{
	return false;
}

//Returns true if Doodlebug, otherwise false
bool Doodlebug::getIsDoodlebug()
{
	return true;
}

/***************************************************************************
** Accessor functions for static variables
** getTotalAnts(): int
** getNewAnts(): int
** getDeadAnts(): int
*****************************************************************************/
int Doodlebug::getTotalDoodlebugs()
{
    return Doodlebug::totalDoodlebugs;
}

int Doodlebug::getNewDoodlebugs()
{
    return Doodlebug::newDoodlebugs;
}

int Doodlebug::getDeadDoodlebugs()
{
    return Doodlebug::deadDoodlebugs;
}

/***************************************************************************
** Modifier functions for static variables
** resetStaticCounters(): int
*****************************************************************************/
void Doodlebug::resetStaticCounters()
{
    Doodlebug::newDoodlebugs = 0;
    Doodlebug::deadDoodlebugs = 0;
}

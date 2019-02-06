/***************************************************************
** Program name: Doodlebug.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Doodlebug class implementation file.
**               Doodlebug is derived from the Critter class.
***************************************************************/
#include "Doodlebug.hpp"
#include "Board.hpp"
#include <iostream>

//For reference: enum class Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3}


//Doodlebug constructor. Takes an int for the row and an int for the column
Doodlebug::Doodlebug(int row, int col): Critter(row, col) {
  this->row = row;
  this->col = col;
  starvingCounter = 0;
  isDoodlebug = true;
  isAnt = false;
}

//Increments breeding counter by 1
void Doodlebug::incrementCounters() {
  ++breedingCounter;
  ++starvingCounter;
  hasMovedToday = false;
}

//Removes doodlebug if starvingCounter >= 3
bool Doodlebug::starve()
{
	if(this->starvingCounter >= 3)
	{
        std::cout << "starving" << this->row << " " << this->col << std::endl;
		//gameBoard[this->row][this->col] == nullptr; //AW: I think this will work? Maybe it breaks everything, need to test
		return true;
	}
    return false;
}

//Checks that breedingCounter is >= 8 and that there is an empty adjacent space. If so, creates new Doodlebug
void Doodlebug::breed(Critter*** gameBoard) {
    std::cout << "inside breed" << std::endl;
	if (this->breedingCounter >= 8) //change this to 0 to test breeding function
	{
        std::cout << "inside if1" << std::endl;
		bool bred = false;

		while (!bred)  //loop until bred
		{
            std::cout << "inside while loop" << std::endl;
			bool upCheck, leftCheck, downCheck, rightCheck;  //bools to track whether all adjacent spaces have been checked.
			upCheck = leftCheck = downCheck = rightCheck = false;  //false = not checked, true = checked

			while(!(upCheck == true && downCheck == true && leftCheck == true && rightCheck == true))  //loop until all are true (i.e. all have been checked);
			{
				int breedDirection = rand() % 4;

				switch (breedDirection)
				{
					case UP:    std::cout << "Trying to breed up!" << std::endl;  //for testing, remove later
								upCheck = true;
								if (this->row != 0) {  //if we're in the top row, do nothing.
									if (gameBoard[this->row - 1][this->col] == nullptr) {  //if the space is unoccupied breed
										gameBoard[this->row - 1][this->col] = new Doodlebug(this->row - 1, this->col);  //make a new doodlebug there
										this->breedingCounter = 0;  //reset breeding counter
										bred = true;  //exit outer loop condition
										upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
									}
								} break;

					case RIGHT: std::cout << "Trying to breed right!" << std::endl;  //for testing, remove later
								rightCheck = true;
								if (this->col != MAX_COLS - 1) {  //if we're in the right column, do nothing.
									if (gameBoard[this->row][this->col + 1] == nullptr) {  //if the space is unoccupied breed
										gameBoard[this->row][this->col + 1] = new Doodlebug(this->row, this->col + 1);  //make a new doodlebug there
										this->breedingCounter = 0;  //reset breeding counter
										bred = true;  //exit outer loop condition
										upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
									}
								} break;

					case DOWN:  std::cout << "Trying to breed down!" << std::endl;  //for testing, remove later
								downCheck = true;
								if (this->row != MAX_ROWS - 1) {  //if we're in the bottom row, do nothing.
									if(gameBoard[this->row + 1][this->col] == nullptr) {  //if the space is unoccupied breed
										gameBoard[this->row + 1][this->col] = new Doodlebug(this->row + 1, this->col);  //make a new doodlebug there
										this->breedingCounter = 0;  //reset breeding counter
										bred = true;  //exit outer loop condition
										upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
									}
								} break;

					case LEFT:  std::cout << "Trying to breed left!" << std::endl;  //for testing, remove later
								leftCheck = true;
								if (this->col != 0) {  //if we're in the left column, do nothing.
									if (gameBoard[this->row][this->col - 1] == nullptr) {  //if the space is unoccupied breed
										gameBoard[this->row][this->col - 1] = new Doodlebug(this->row, this->col - 1);  //make a new doodlebug there
										this->breedingCounter = 0;  //reset breeding counter
										bred = true;  //exit outer loop condition
										upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
									}
								}
				}
			}
			if(!bred) //if doodlebug hasn't bred after checking all 4 adjacent squares
			{
				std::cout << "No space to breed :(" << std::endl;
				bred = true; //break out of loop, but don't reset BreedingCounter.
			}
		}
	}
}

//Moves to an adjacent space with an Ant if possible. If not, moves to an empty adjacent space
//If surrounded by Doodlebugs, the Doodlebug does not move
void Doodlebug::move(Critter*** gameBoard) {
    if (!hasMovedToday)
    {
    	bool hasEaten = false;
    	std::cout << "Checking for ants to eat." << std::endl;
    	std::cout << "Row: " << this->row << " Col: " << this->col << std::endl;

    	if((this->row != 0) && hasEaten == false)  //if we're in the top row, do nothing.
    	{
    		if (gameBoard[this->row - 1][this->col] != nullptr && gameBoard[this->row - 1][this->col]->getIsAnt()) //if there is an ant above,
    		{
    			std::cout << "Ant above" << std::endl;
    			delete gameBoard[this->row - 1][this->col];  //delete the ant
    			gameBoard[this->row - 1][this->col] = this;  //move into its space
    			gameBoard[this->row][this->col] = nullptr;   //set old space to nullptr
    			this->row--;  //update critter row
    			hasEaten = true;
    			std::cout << "Ate an ant" << std::endl;
    		}
    	}
    	std::cout << "Checking for ants to eat.." << std::endl;
    	if((this->row != MAX_ROWS - 1) && hasEaten == false)  //if we're in the bottom row or we've already eaten, do nothing.
    	{
    		if (gameBoard[this->row + 1][this->col] != nullptr && gameBoard[this->row + 1][this->col]->getIsAnt()) //if there is an ant below,
    		{
    			std::cout << "Ant below" << std::endl;
    			delete gameBoard[this->row + 1][this->col];
    			gameBoard[this->row + 1][this->col] = this;
    			gameBoard[this->row][this->col] = nullptr;
    			this->row++;
    			hasEaten = true;
    			std::cout << "Ate an ant" << std::endl;
    		}
    	}
    	std::cout << "Checking for ants to eat..." << std::endl;
    	if((this->col != 0) && hasEaten == false)  //if we're in the left column or we've already eaten, do nothing.
    	{
    		if (gameBoard[this->row][this->col - 1] != nullptr && gameBoard[this->row][this->col - 1]->getIsAnt())
    		{
    			std::cout << "Ant left" << std::endl;
    			delete gameBoard[this->row][this->col - 1];
    			gameBoard[this->row][this->col - 1] = this;
    			gameBoard[this->row][this->col] = nullptr;
    			this->col--;
    			hasEaten = true;
    			std::cout << "Ate an ant" << std::endl;
    		}
    	}
    	std::cout << "Checking for ants to eat...." << std::endl;
    	if((this->col != MAX_COLS - 1) && hasEaten == false)  //if we're in the right column or we've already eaten, do nothing.
    	{
    		if (gameBoard[this->row][this->col + 1] != nullptr && gameBoard[this->row][this->col + 1]->getIsAnt())
    		{
    			std::cout << "Ant right" << std::endl;
    			delete gameBoard[this->row][this->col + 1];
    			gameBoard[this->row][this->col + 1] = this;
    			gameBoard[this->row][this->col] = nullptr;
    			this->col++;
    			hasEaten = true;
    			std::cout << "Ate an ant" << std::endl;
    		}
    	}
    	std::cout << "No ants to eat :(" << std::endl;
    	if(hasEaten == false) //if we haven't eaten anything after checking all directions, then just move
    	{
    		std::cout << "No ants to eat :(" << std::endl;
    		int moveDirection = rand() % 4; //spot to move if no ants in adjacent cells

    		switch (moveDirection)
    		{
    		case UP:    std::cout << "Trying to move up!" << std::endl;  //for testing, remove later
    					if (this->row != 0) {  //if we're in the top row, do nothing.
    						if (gameBoard[this->row - 1][this->col] == nullptr) {  //if the space is unoccupied, move
    							gameBoard[this->row - 1][this->col] = this;
    							gameBoard[this->row][this->col] = nullptr;
    							this->row--;
    						}
    					} break;

    		case RIGHT: std::cout << "Trying to move right!" << std::endl;  //for testing, remove later
    					if (this->col != MAX_COLS - 1) {  //if we're in the right column, do nothing.
    						if (gameBoard[this->row][this->col + 1] == nullptr) {  //if the space is unoccupied, move
    							gameBoard[this->row][this->col + 1] = this;
    							gameBoard[this->row][this->col] = nullptr;
    							this->col++;
    						}
    					} break;

    		case DOWN:  std::cout << "Trying to move down!" << std::endl;  //for testing, remove later
    					if (this->row != MAX_ROWS - 1) {  //if we're in the bottom row, do nothing.
    						if (gameBoard[this->row + 1][this->col] == nullptr) {  //if the space is unoccupied, move
    							gameBoard[this->row + 1][this->col] = this;
    							gameBoard[this->row][this->col] = nullptr;
    							this->row++;
    						}
    					} break;

    		case LEFT:  std::cout << "Trying to move left!" << std::endl;  //for testing, remove later
    					if (this->col != 0) {  //if we're in the left column, do nothing.
    						if (gameBoard[this->row][this->col - 1] == nullptr) {  //if the space is unoccupied, move
    							gameBoard[this->row][this->col - 1] = this;
    							gameBoard[this->row][this->col] = nullptr;
    							this->col--;
    						}
    					}
    		}
    	}
        this->hasMovedToday = true;
    }
}

//Returns true if ant, otherwise false
bool Doodlebug::getIsAnt() {
  return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Doodlebug::getIsDoodlebug() {
  return isDoodlebug;
}

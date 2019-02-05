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


//Doodlebug constructor. Takes an int for the x axis and an int for the y axis
Doodlebug::Doodlebug(int x, int y): Critter(row, col) {
  starvingCounter = 0;
  isDoodlebug = true;
  isAnt = false;
}

//Returns the starving counter
int Doodlebug::getStarvingCounter() {
  return starvingCounter;
}

//Takes an int to set the starving counter (used to increment and reset counter)
void Doodlebug::setStarvingCounter(int newCounter) {
  starvingCounter = newCounter;
}

//Checks that breedingCounter is >= 8 and that there is an empty ajacent space. If so, creates new Doodlebug
void Doodlebug::breed(Critter*** gameBoard) {
	
	if (getBreedingCounter() >= 8) {
		int loopEnd = 0;//makes sure each option is tested before exiting
		while (loopEnd != 5) { //loop that cycles through untill an empty space is found
			int moveDirection = rand() % 4;
			switch (moveDirection)
			{
			case UP:    std::cout << "Trying to move up!" << std::endl;  //for testing, remove later
				        if (this->row != 0) {  //if we're in the top row, do nothing.
					        if (gameBoard[this->row - 1][this->col] == nullptr) {  //if the space is unoccupied breed
						        gameBoard[this->row - 1][this->col] = this;
						        gameBoard[this->row][this->col] = nullptr;
						        this->row--;
						        loopEnd = 5; //end the loop
					        }
				        }
				        break;

			case RIGHT: std::cout << "Trying to move right!" << std::endl;  //for testing, remove later
        				if (this->col != MAX_COLS - 1) {  //if we're in the right column, do nothing.
        					if (gameBoard[this->row][this->col + 1] == nullptr) {  //if the space is unoccupied breed
        						gameBoard[this->row][this->col + 1] = this;
        						gameBoard[this->row][this->col] = nullptr;
        						this->col++;
        						loopEnd = 5; // end loop
        					}
        				}
        				break;

			case DOWN:  std::cout << "Trying to move down!" << std::endl;  //for testing, remove later
        				if (this->row != MAX_ROWS - 1) {  //if we're in the bottom row, do nothing.
        					if (gameBoard[this->row + 1][this->col] == nullptr) {  //if the space is unoccupied breed
        						gameBoard[this->row + 1][this->col] = this;
        						gameBoard[this->row][this->col] = nullptr;
        						this->row++;
        						loopEnd = 5; //endloop
        					}
        				}
        				break;

			case LEFT:  std::cout << "Trying to move left!" << std::endl;  //for testing, remove later
				if (this->col != 0) {  //if we're in the left column, do nothing.
					if (gameBoard[this->row][this->col - 1] == nullptr) {  //if the space is unoccupied breed
						gameBoard[this->row][this->col - 1] = this;
						gameBoard[this->row][this->col] = nullptr;
						this->col--;
						loopEnd = 5; //end loop
					}
				}
					break;
				
				
			}
		}
	}
}

//Moves to an adjacent space with an Ant if possible. If not, moves to an empty adjacent space
//If surrounded by Doodlebugs, the Doodlebug does not move
void Doodlebug::move(Critter*** gameBoard) {
    int moveDirection = 0;
	//Check for ants in adjacent cells
	//If ants in adjacent cells move there. 

	if (gameBoard[this->row - 1][this->col]->getIsAnt()) {
		gameBoard[this->row - 1][this->col] = this;
		gameBoard[this->row][this->col] = nullptr;
	}
	else if (gameBoard[this->row + 1][this->col]->getIsAnt()) {
		gameBoard[this->row + 1][this->col] = this;
		gameBoard[this->row][this->col] = nullptr;
	}
	else if (gameBoard[this->row][this->col - 1]->getIsAnt()) {
		gameBoard[this->row][this->col - 1] = this;
		gameBoard[this->row][this->col] = nullptr;
	}
	else if (gameBoard[this->row][this->col + 1]->getIsAnt()) {
		gameBoard[this->row][this->col + 1] = this;
		gameBoard[this->row][this->col] = nullptr;
	}
	else {
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
}

//Returns true if ant, otherwise false
bool Doodlebug::getIsAnt() {
  return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Doodlebug::getIsDoodlebug() {
  return isDoodlebug;
}

/***************************************************************
** Program name: Ant.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Ant class implementation file.
**               Ant is derived from the Critter class.
***************************************************************/
#include <stdlib.h> //rand
#include <iostream>
#include "Ant.hpp"
#include "Board.hpp"


//Ant constructor. Takes an int for the x axis and an int for the y axis
Ant::Ant(int row, int col): Critter(row, col) {
  this->row = row;
  this->col = col;
  isAnt = true;
  isDoodlebug = false;
}

//Checks that breedingCounter is >= 3 and that there is an empty ajacent space. If so, creates new Ant
void Ant::breed(Critter*** gameBoard) {
    std::cout << "inside breed" << std::endl;
    if (this->breedingCounter >= 3) //change this to 0 to test breeding function
    {
        std::cout << "inside if1" << std::endl;
        bool bred = false;
        while (!bred)  //loop until bred
        {
            std::cout << "inside while loop" << std::endl;
            bool upCheck, leftCheck, downCheck, rightCheck;  //bools to track whether all adjacent spaces have been checked.
            upCheck = leftCheck = downCheck = rightCheck = false;  //false = not checked, true = checked
            while (!(upCheck == true && downCheck == true && leftCheck == true && rightCheck == true))  //loop until all are true (i.e. all have been checked);
            {
                int breedDirection = rand() % 4;
                switch (breedDirection)
                {
                case UP:    std::cout << "Trying to breed up!" << std::endl;  //for testing, remove later
                    upCheck = true;
                    if (this->row != 0) {  //if we're in the top row, do nothing.
                        if (gameBoard[this->row - 1][this->col] == nullptr) {  //if the space is unoccupied breed
                            gameBoard[this->row - 1][this->col] = new Ant(this->row - 1, this->col);  //make a new doodlebug there
                            this->breedingCounter = 0;  //reset breeding counter
                            bred = true;  //exit outer loop condition
                            upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            std::cout << "successful breeding up!" << std::endl;
                        }
                    } break;
                case RIGHT: std::cout << "Trying to breed right!" << std::endl;  //for testing, remove later
                    rightCheck = true;
                    if (this->col != MAX_COLS - 1) {  //if we're in the right column, do nothing.
                        if (gameBoard[this->row][this->col + 1] == nullptr) {  //if the space is unoccupied breed
                            gameBoard[this->row][this->col + 1] = new Ant(this->row, this->col + 1);  //make a new doodlebug there
                            this->breedingCounter = 0;  //reset breeding counter
                            bred = true;  //exit outer loop condition
                            upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            std::cout << "successful breeding right!" << std::endl;
                        }
                    } break;
                case DOWN:  std::cout << "Trying to breed down!" << std::endl;  //for testing, remove later
                    downCheck = true;
                    if (this->row != MAX_ROWS - 1) {  //if we're in the bottom row, do nothing.
                        if (gameBoard[this->row + 1][this->col] == nullptr) {  //if the space is unoccupied breed
                            gameBoard[this->row + 1][this->col] = new Ant(this->row + 1, this->col);  //make a new doodlebug there
                            this->breedingCounter = 0;  //reset breeding counter
                            bred = true;  //exit outer loop condition
                            upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            std::cout << "successful breeding down!" << std::endl;
                        }
                    } break;
                case LEFT:  std::cout << "Trying to breed left!" << std::endl;  //for testing, remove later
                    leftCheck = true;
                    if (this->col != 0) {  //if we're in the left column, do nothing.
                        if (gameBoard[this->row][this->col - 1] == nullptr) {  //if the space is unoccupied breed
                            gameBoard[this->row][this->col - 1] = new Ant(this->row, this->col - 1);  //make a new doodlebug there
                            this->breedingCounter = 0;  //reset breeding counter
                            bred = true;  //exit outer loop condition
                            upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                            std::cout << "successful breeding left!" << std::endl;
                        }
                    }
                }
            }
            if (!bred) //if doodlebug hasn't bred after checking all 4 adjacent squares
            {
                std::cout << "No space to breed :(" << std::endl;
                bred = true; //break out of loop, but don't reset BreedingCounter.
            }
        }
    }
}

//Increments breeding counter by 1
void Ant::incrementCounters() {
  ++breedingCounter;
}


//Moves to an empty adjacent space. If the first move fails, the Ant does not move
void Ant::move(Critter*** gameBoard) {

  //AW: For reference: enum Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3}
  int moveDirection = rand() % 4;  //0, 1, 2, or 3.

  switch(moveDirection)
  {
    case UP:    std::cout << "Trying to move up!" << std::endl;  //for testing, remove later
                if(this->row != 0){  //if we're in the top row, do nothing.
                  if(gameBoard[this->row - 1][this->col] == nullptr){  //if the space is unoccupied, move
                    gameBoard[this->row - 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row--;
                  }
                } break;

    case RIGHT: std::cout << "Trying to move right!" << std::endl;  //for testing, remove later
                if(this->col != MAX_COLS - 1){  //if we're in the right column, do nothing.
                  if(gameBoard[this->row][this->col + 1] == nullptr){  //if the space is unoccupied, move
                    gameBoard[this->row][this->col + 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col++;
                  }
                } break;

    case DOWN:  std::cout << "Trying to move down!" << std::endl;  //for testing, remove later
                if(this->row != MAX_ROWS - 1){  //if we're in the bottom row, do nothing.
                  if(gameBoard[this->row + 1][this->col] == nullptr){  //if the space is unoccupied, move
                    gameBoard[this->row + 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row++;
                  }
                } break;

    case LEFT:  std::cout << "Trying to move left!" << std::endl;  //for testing, remove later
                if(this->col != 0){  //if we're in the left column, do nothing.
                  if(gameBoard[this->row][this->col - 1] == nullptr){  //if the space is unoccupied, move
                    gameBoard[this->row][this->col - 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col--;
                  }
                }
  }
}

//Returns true if ant, otherwise false
bool Ant::getIsAnt() {
  return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Ant::getIsDoodlebug() {
  return isDoodlebug;
}

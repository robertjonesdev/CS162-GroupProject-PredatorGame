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
    this->isAnt = true;
    this->isDoodlebug = false;
    this->newAnts = 0;
}

//Checks that breedingCounter is >= 3 and that there is an empty ajacent space. If so, creates new Ant
void Ant::breed(Critter*** gameBoard, const int& numRows, const int& numCols) {
    newAnts = 0;
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
                        //std::cout << "Trying to breed up!" << std::endl;  //for testing, remove later
                        upCheck = true;
                        if (this->row != 0) {  //if we're in the top row, do nothing.
                            if (gameBoard[this->row - 1][this->col] == nullptr) {  //if the space is unoccupied breed
                                gameBoard[this->row - 1][this->col] = new Ant(this->row - 1, this->col);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                                std::cout << "[" << this->row << "][" << this->col << "] successful breeding up!" << std::endl;
                                newAnts++;
                            }
                        }
                        break;
                    }
                    case RIGHT:
                    {
                        //std::cout << "Trying to breed right!" << std::endl;  //for testing, remove later
                        rightCheck = true;
                        if (this->col != numCols - 1) {  //if we're in the right column, do nothing.
                            if (gameBoard[this->row][this->col + 1] == nullptr) {  //if the space is unoccupied breed
                                gameBoard[this->row][this->col + 1] = new Ant(this->row, this->col + 1);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                                std::cout << "[" << this->row << "][" << this->col << "] successful breeding right!" << std::endl;
                                newAnts++;
                            }
                        }
                        break;
                    }
                    case DOWN:
                    {
                        //std::cout << "Trying to breed down!" << std::endl;  //for testing, remove later
                        downCheck = true;
                        if (this->row != numRows - 1) {  //if we're in the bottom row, do nothing.
                            if (gameBoard[this->row + 1][this->col] == nullptr) {  //if the space is unoccupied breed
                                gameBoard[this->row + 1][this->col] = new Ant(this->row + 1, this->col);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                                std::cout << "[" << this->row << "][" << this->col << "] successful breeding down!" << std::endl;
                                newAnts++;
                            }
                        }
                        break;
                    }
                    case LEFT:
                    {
                        //std::cout << "Trying to breed left!" << std::endl;  //for testing, remove later
                        leftCheck = true;
                        if (this->col != 0) {  //if we're in the left column, do nothing.
                            if (gameBoard[this->row][this->col - 1] == nullptr) {  //if the space is unoccupied breed
                                gameBoard[this->row][this->col - 1] = new Ant(this->row, this->col - 1);  //make a new doodlebug there
                                this->breedingCounter = 0;  //reset breeding counter
                                bred = true;  //exit outer loop condition
                                upCheck = leftCheck = downCheck = rightCheck = true; //force exit of inner loop
                                std::cout << "[" << this->row << "][" << this->col << "] successful breeding left!" << std::endl;
                                newAnts++;
                            }
                        }
                        break;
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
    ++this->breedingCounter;
    this->hasMovedToday = false;
}


//Moves to an empty adjacent space. If the first move fails, the Ant does not move
void Ant::move(Critter*** gameBoard, const int& numRows, const int& numCols) {
    if (!this->hasMovedToday)
    {
      //AW: For reference: enum Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3}
      int moveDirection = rand() % 4;  //0, 1, 2, or 3.

      switch(moveDirection)
      {
        case UP:
        {
            //std::cout << "Trying to move up!" << std::endl;  //for testing, remove later
            if (this->row != 0)
            {  //if we're in the top row, do nothing.
                if (gameBoard[this->row - 1][this->col] == nullptr)
                {  //if the space is unoccupied, move
                    gameBoard[this->row - 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row--;
                    std::cout << "[" << this->row << "][" << this->col << "] Ant moved up!" << std::endl;
                }
            }
            break;
        }
        case RIGHT:
        {
            //std::cout << "Trying to move right!" << std::endl;  //for testing, remove later
            if (this->col != numCols - 1)
            {  //if we're in the right column, do nothing.
                if(gameBoard[this->row][this->col + 1] == nullptr)
                {  //if the space is unoccupied, move
                    gameBoard[this->row][this->col + 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col++;
                    std::cout << "[" << this->row << "][" << this->col << "] Ant moved right!" << std::endl;
                }
            }
            break;
        }
        case DOWN:
        {
            //std::cout << "Trying to move down!" << std::endl;  //for testing, remove later
            if (this->row != numRows - 1)
            {  //if we're in the bottom row, do nothing.
                if (gameBoard[this->row + 1][this->col] == nullptr)
                {  //if the space is unoccupied, move
                    gameBoard[this->row + 1][this->col] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->row++;
                    std::cout << "[" << this->row << "][" << this->col << "] Ant moved down!" << std::endl;
                }
            }
            break;
        }
        case LEFT:
        {
            //std::cout << "Trying to move left!" << std::endl;  //for testing, remove later
            if (this->col != 0)
            {  //if we're in the left column, do nothing.
                if (gameBoard[this->row][this->col - 1] == nullptr)
                {  //if the space is unoccupied, move
                    gameBoard[this->row][this->col - 1] = this;
                    gameBoard[this->row][this->col] = nullptr;
                    this->col--;
                    std::cout << "[" << this->row << "][" << this->col << "] Ant moved left!" << std::endl;
                }
            }
            break;
        }
      }
      this->hasMovedToday = true;
  }
}

//Returns true if ant, otherwise false
bool Ant::getIsAnt() {
    return this->isAnt;
}

//Returns true if doodlebug, otherwise false
bool Ant::getIsDoodlebug() {
    return this->isDoodlebug;
}

int Ant::getDeadAnts() {
    return 0;
}

int Ant::getNewDoodles() {
    return 0;
}

int Ant::getNewAnts() {
    return newAnts;
}
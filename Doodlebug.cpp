/***************************************************************
** Program name: Doodlebug.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Doodlebug class implementation file.
**               Doodlebug is derived from the Critter class.
***************************************************************/
#include "Doodlebug.hpp"

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
void Doodlebug::breed() {
  if (getBreedingCounter() >= 8) {
    //Need to add function/steps to check for empty adjacent space and if so, add a new Doodlebug
  }
}

//Moves to an adjacent space with an Ant if possible. If not, moves to an empty adjacent space
//If surrounded by Doodlebugs, the Doodlebug does not move
void Doodlebug::move(Critter*** gameBoard) {
  //Need to add function/steps to check if any adjacent spaces have Ants and if so, move there
  //Need to add function/steps to check if any adjacent spaces are empty and if so, move there
}

//Returns true if ant, otherwise false
bool Doodlebug::getIsAnt() {
  return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Doodlebug::getIsDoodlebug() {
  return isDoodlebug;
}
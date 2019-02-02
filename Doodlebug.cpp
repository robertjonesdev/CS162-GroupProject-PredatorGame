/***************************************************************
** Program name: Doodlebug.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Doodlebug class implementation file.
**               Doodlebug is derived from the Critter class.
***************************************************************/
#include "Doodlebug.hpp"

//Doodlebug constructor. Takes an int for the x axis and an int for the y axis
Doodlebug::Doodlebug(int x, int y): Critter(locationX, locationY) {
  starvingCounter = 0;
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
void Doodlebug::move() {
  //Need to add function/steps to check if any adjacent spaces have Ants and if so, move there
  //Need to add function/steps to check if any adjacent spaces are empty and if so, move there
}
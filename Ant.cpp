/***************************************************************
** Program name: Ant.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Ant class implementation file.
**               Ant is derived from the Critter class.
***************************************************************/
#include "Ant.hpp"

//Ant constructor. Takes an int for the x axis and an int for the y axis
Ant::Ant(int x, int y): Critter(locationX, locationY) {
}

//Checks that breedingCounter is >= 3 and that there is an empty ajacent space. If so, creates new Ant
void Ant::breed() {
  if (getBreedingCounter() >= 3) {
    //Need to add function/steps to check for empty adjacent space and if so, add a new Ant
  }
}

//Moves to an empty adjacent space. If surrounded, the Ant does not move
void Ant::move() {
  //Need to add function/steps to check if any adjacent spaces are empty and if so, move there
}
/***************************************************************
** Program name: Critter.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Critter class implementation file.
**               Doodlebug and Ant inherit from Critter.
***************************************************************/

#include "Critter.hpp"

//Critter constructor. Takes an int for the x axis and an int for the y axis
//and sets breedingCounter to zero to start.
Critter::Critter(int x, int y) {
  locationX = x;
  locationY = y;
  breedingCounter = 0;
}

//Returns x-axis location
int Critter::getX() {
  return locationX;
}

//Returns y-axis location
int Critter::getY() {
  return locationY;
}

//Returns breeding counter
int getBreedingCounter() {
  return breedingCounter;
}

//Takes an int to set the breeding counter (used to increment and reset counter)
void setBreedingCounter(int newCounter) {
  breedingCounter = newCounter;
}
/***************************************************************
** Program name: Critter.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Critter class implementation file.
**               Doodlebug and Ant inherit from Critter.
***************************************************************/

#include "Critter.hpp"
#include "Board.hpp"

//AW: default constructor
Critter::Critter()
{
    breedingCounter = 0;
    isAnt = false;
    isDoodlebug = false;
};

//Critter constructor. Takes an int for the x axis and an int for the y axis
//and sets breedingCounter to zero to start.
Critter::Critter(int row, int col) {
    this->row = row;
    this->col = col;
    breedingCounter = 0;
    isAnt = false;
    isDoodlebug = false;
}

//Returns x-axis location
int Critter::getRow() {
    return row;
}

//Returns y-axis location
int Critter::getCol() {
    return col;
}

//Returns breeding counter
int Critter::getBreedingCounter() {
    return breedingCounter;
}

//Takes an int to set the breeding counter (used to increment and reset counter)
void Critter::setBreedingCounter(int newCounter) {
    breedingCounter = newCounter;
}

//Returns true if ant, otherwise false
bool Critter::getIsAnt() {
    return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Critter::getIsDoodlebug() {
    return isDoodlebug;
}

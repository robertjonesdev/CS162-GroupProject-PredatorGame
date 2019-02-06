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

//Critter constructor. Takes an int for the row and an int for the column, 
//set breedingCounter to zero, and sets isAnt and isDoodlebug to false.
Critter::Critter(int row, int col) {
  this->row = row;
  this->col = col;
  breedingCounter = 0;
  isAnt = false;
  isDoodlebug = false;
}

//Returns Critter's row on the board
int Critter::getRow() {
  return row;
}

//Returns Critter's column on the board
int Critter::getCol() {
  return col;
}

//Returns true if ant, otherwise false
bool Critter::getIsAnt() {
  return isAnt;
}

//Returns true if doodlebug, otherwise false
bool Critter::getIsDoodlebug() {
  return isDoodlebug;
}

bool Critter::starve() {
  return false;
}
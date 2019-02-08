/***************************************************************
** Program name: Critter.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Critter class implementation file.
**               Doodlebug and Ant inherit from Critter.
***************************************************************/

#include "Critter.hpp"
#include "Board.hpp"

//Critter constructor. Takes an int for the row axis and an int for the column axis
//and sets breedingCounter to zero to start.
Critter::Critter(int row, int col) 
{
    this->row = row;
    this->col = col;
    this->breedingCounter = 0;
    this->isAnt = false;
    this->isDoodlebug = false;
}

//Returns true if ant, otherwise false
bool Critter::getIsAnt() 
{
    return this->isAnt;
}

//Returns true if doodlebug, otherwise false
bool Critter::getIsDoodlebug() 
{
    return this->isDoodlebug;
}

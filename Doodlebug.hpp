/***************************************************************
** Program name: Doodlebug.hpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Doodlebug class specification file.
**               It is derived from the Critter class.
***************************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP
#include "Critter.hpp"

class Doodlebug: public Critter {
  private:
    int starvingCounter;

  public:
    Doodlebug(int, int);
    int getStarvingCounter();
    void setStarvingCounter(int);
    void breed();
    void move(Critter*** gameBoard);
    bool getIsDoodlebug();
    bool getIsAnt();
};

#endif
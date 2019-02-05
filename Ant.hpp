/***************************************************************
** Program name: Ant.hpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Ant class specification file.
**               It is derived from the Critter class.
***************************************************************/

#ifndef ANT_HPP
#define ANT_HPP
#include "Critter.hpp"

class Ant: public Critter {
  private:

  public:
    Ant(int, int);
    void breed(Critter*** gameBoard);
    void move(Critter*** gameBoard);  //takes the board as a parameter so it can check spaces
    bool getIsDoodlebug();
    bool getIsAnt();
};

#endif
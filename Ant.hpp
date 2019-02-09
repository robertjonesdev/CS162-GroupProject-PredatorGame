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

class Ant: public Critter
{
    private:
      static int newAnts,   //Will track all new ants from 1 round.
                 deadAnts,  //Will track all Ant deaths from 1 round.
                 totalAnts; //Will track total number of Ants on the boar.

    public:
      Ant(int, int);
      ~Ant();
      void incrementCounters();
      void breed(Critter*** gameBoard, const int& numRows, const int& numCols);
      void move(Critter*** gameBoard, const int& numRows, const int& numCols);

      //Accessors
      bool getIsAnt();
      bool getIsDoodlebug();
      static int getTotalAnts();
      static int getNewAnts();
      static int getDeadAnts();

      //Modifier
      static void resetStaticCounters();
};

#endif

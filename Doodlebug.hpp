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

class Doodlebug: public Critter
{
	private:
		int starvingCounter;

        static int newDoodlebugs,   //Will track all new Doodlebugs from 1 round.
                   deadDoodlebugs,  //Will track all Doodlebug deaths from 1 round.
                   totalDoodlebugs; //Will track totle number of Doodlebugs on the board.

	public:
		Doodlebug(int, int);
        ~Doodlebug();
		void incrementCounters();
		void breed(Critter*** gameBoard, const int& numRows, const int& numCols);
		void move(Critter*** gameBoard, const int& numRows, const int& numCols);
		bool starve();

        //Accessors
		bool getIsAnt();
		bool getIsDoodlebug();
        static int getTotalDoodlebugs();
        static int getNewDoodlebugs();
        static int getDeadDoodlebugs();

        //Modifier
        static void resetStaticCounters();
};

#endif

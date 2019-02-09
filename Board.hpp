/*********************************************************************
** Program name:  Predator-Prey Game (Group Project, CS 162-400, Winter 2019)
** Author:        Group 16 (LB, LB, RJ, DS, AW)
** Date:          February 2, 2019
** Description:   Board.hpp, Board Class Definition
**********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Critter.hpp"

class Board
{
    private:
        Critter*** gameBoard;
        int numRows,
            numCols,
            stepNumber;

    public:
        //Constructors and Deconstructor
        Board(int rows, int cols, int ants, int doodlebugs);
        virtual ~Board();

        //Functions
        void runGame(int); //Takes an int to set number of steps
        void printBoard();
        bool addAnt(int, int);
        bool addDoodlebug(int, int);
        void printGameInfo();
};
#endif

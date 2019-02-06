/*********************************************************************
** Program name:  Predator-Prey Game (Group Project, CS 162-400, Winter 2019)
** Author:        Group 16
** Date:          February 2, 2019
** Description:   Board.hpp, Board Class Definition
**********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Critter.hpp"

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
const int STARTING_ANTS = 100;
const int STARTING_DOODLEBUGS = 5;

class Board
{
    private:
        Critter*** gameBoard;

    public:
        //Constructors and Deconstructor
        Board();
        Board(int rows, int cols);  //AW: constructor for extra credit, blank for now
        virtual ~Board();

        //Functions
        void runGame(int); //Takes an int to set number of steps
        void printBoard();
        bool addAnt(int, int);
        bool addDoodlebug(int, int);
};
#endif

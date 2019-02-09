/*********************************************************************
** Program name:  Predator-Prey Game (Group Project, CS 162-400, Winter 2019)
** Author:        Group 16
** Date:          February 2, 2019
** Description:   Board.cpp, Board Class Implementation
**********************************************************************/

#include <iostream>   //Console input and output
#include <iomanip>
#include "Board.hpp"
#include "Critter.hpp"
#include "Doodlebug.hpp"
#include "Ant.hpp"

using std::cout;
using std::endl;

//Extra Credit Constructor
Board::Board(int rows, int cols, int numAnts, int numDoodlebugs)
{
    this->stepNumber = 1;
    this->numRows = rows;
    this->numCols = cols;
    gameBoard = new Critter**[this->numRows];

    for (int i = 0; i < this->numRows; i++)
    {
        gameBoard[i] = new Critter*[this->numCols];
    }

    //initialize board to null pointers;
    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            gameBoard[i][j] = nullptr;
        }
    }

    //randomly place all the starting doodlebugs
    for (int i = 0; i < numDoodlebugs; i++)
    {
        //The While-loop picks a random row/col, attempts to make a Doodlebug
        //if unsuccessful pick two more random row/col until success
        //The input validation from the menu ensures there is sufficient spots.
        while (!addDoodlebug(rand() % this->numRows, rand() % this->numCols));
    }

    //randomly place the all the starting ants
    for (int i = 0; i < numAnts; i++)
    {
        //The While-loop picks a random row/col, attempts to make an Ant
        //if unsuccessful pick two more random row/col until success
        //The input validation from the menu ensures there is sufficient spots.
        while (!addAnt(rand() % this->numRows, rand() % this->numCols));
    }

    //print the starting board and information about the board
    cout << '\n' << endl;
    cout << "Created " << numRows << "x" << numCols << " board with " << numAnts << " Ants and " << numDoodlebugs << " Doodlebugs!" << endl;
    cout << "*****Starting Board*****" << endl;
    printBoard();
};

/*********************************************************************
** Deconstructor capable of handling extra credit.
** Deconstructor deletes all dynamically created objects in the gameBoard Array.
** Tested with Valgrind 2/2/2019 7:49PM
*********************************************************************/
Board::~Board()
{
    //Deallocate memory for the dynamic arrow.
    for (int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete gameBoard[i][j];
        }
        delete [] gameBoard[i];
    }
    delete [] gameBoard;
    gameBoard = nullptr;
}

//Functions
/*********************************************************************
** runGame() capable of handling extra credit.
**
*********************************************************************/
void Board::runGame(int numSteps)
{
    while(numSteps > 0)
    {
        //Function calls to reset the step counters of new/dead Ants and Doodlebugs.
        Ant::resetStaticCounters();
        Doodlebug::resetStaticCounters();
        /*************************************************************************
        ** The for loops are separated because ->move() affects the location
        ** of a Doodlebug which would give a seg fault for calling ->breed()
        ** directly after. (Robert)
        **********************************************************************/

        //**** Doodlebugs move first ****

        //Iterate through the board and if the space is a Doodlebug object, reset or increment daily counters.
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    //cout << "This is a doodlebug [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->incrementCounters();
                }
            }
        }

        //Iterate through the board and if the space is a Doodlebug object, call it's move function.
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    //cout << "Trying to move [" << i << "][" << j << "]"  << endl;
                    gameBoard[i][j]->move(gameBoard, numRows, numCols);
                }
            }
        }

        //Iterate through the board and if the space is a Doodlebug object, call it's breed function.
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    //cout << "Trying to breed [" << i << "][" << j << "]"  << endl;
                    gameBoard[i][j]->breed(gameBoard, numRows, numCols);
                }
            }
        }

        //Iterate through the board and if the space is a Doodlebug object, call it's starve function.
        //Starve function returns a boolean. If true, the board needs to delete the object and set to nullptr.
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsDoodlebug())
                {
                    //cout << "Trying to starve [" << i << "][" << j << "]"  << endl;

                    //if Starve() returns true, the Ant shall die. The board will delete the object.
                    if (gameBoard[i][j]->starve())
                    {
                        delete gameBoard[i][j];
                        gameBoard[i][j] = nullptr;
                    }
                }
            }
        }
        //cout << "\nFinished Doodlebug move. Ants will move starting from this board:" << endl;
        //printBoard();
        //cout << "\n";

        //*** Ants move second, after all Doodlebugs. ****

        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                //This If Statement can be combined, but order matters, since the left-hand side will be evaluated first.
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt())
                {
                    gameBoard[i][j]->incrementCounters(); //Consider moving this to separate for loop.
                }
            }
        }
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt())
                {
                    //cout << "Ant trying to moved from [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->move(gameBoard, numRows, numCols);
                }
            }
        }
        for(int i = 0; i < numRows; i++)
        {
            for(int j = 0; j < numCols; j++)
            {
                if(gameBoard[i][j] != nullptr && gameBoard[i][j]->getIsAnt())
                {
                    //cout << "Ant trying to breed from [" << i << "][" << j << "]" << endl;  //for testing, remove later
                    gameBoard[i][j]->breed(gameBoard, numRows, numCols);
                }
            }
        }
        cout << "\n*****Step " << this->stepNumber << " completed!***** Here is the current board:" << endl;
        printBoard();
        printGameInfo();
        cout << "\n";
        numSteps--;
    }
}

/*********************************************************************
** printBoard()
** This function prints the board to the console.
*********************************************************************/
void Board::printBoard()
{

    /**
    cout << "  ";
    for (int i = 0; i < numCols; i++)
    {
        cout << i;
    }
    cout << endl;
    cout << " "; **/

    //Top border
    cout.width(numCols + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');

    for(int i = 0; i < numRows; i++)
    {
        cout << "|";
        for(int j = 0; j < numCols; j++)
        {
            if (gameBoard[i][j] == nullptr)
            {   //Array element is empty
                cout << " ";
            }
            else if (gameBoard[i][j]->getIsDoodlebug())
            {   //Is a doodlebug object.
                cout << "X";
            }
            else
            {   //Is an ant.
                cout << "O";
            }
        }
        cout << "|\n";
    }
    //Bottom border
    cout << " ";
    cout.width(numCols + 2);
    cout.fill('-');
    cout << '-' << endl;
    cout.fill(' ');
}

/*********************************************************************
** addAnt(int, int) / addDoodlebug(int, int)
** This function instantiates an Ant / Doodlebug object to the gameBoard array.
** First it tests whether the space is empty (nullptr). If it is empty
** it continues and returns true. If the space is not empty, then the
** function returns false without adding anything to the space.
*********************************************************************/
bool Board::addAnt(int row, int col)
{
    if (gameBoard[row][col] == nullptr)  //if the board spot is unoccupied, make an Ant
    {
        gameBoard[row][col] = new Ant(row, col);   //AW: added (row, col) to Ant constructor call
        return true;
    }
    else  //if the board spot was occupied, return false
    {
        return false;
    }
}

bool Board::addDoodlebug(int row, int col)  //if the board spot is unoccupied, make a Doodlebug
{
    if (gameBoard[row][col] == nullptr)
    {
        gameBoard[row][col] = new Doodlebug(row, col); //AW: added (row, col) to Doodlebug constructor call
        return true;
    }
    else  //if the board spot was occupied, return false
    {
        return false;
    }
}

/*********************************************************************
** printGameInfo()
** This function prints "end of round" information to the console.
**     # of new ants created in the round.
**     # of ants that died im the round.
**     # of new Doodlebugs created in the round.
**     # of Doodlebugs that died in the round.
**     Current # of ants on the board.
**     Current # of Doodlebugs on the board.
*********************************************************************/
void Board::printGameInfo()
{
    //numDoodlebugs += newDoodles - deadDoodles;
    //numAnts += newAnts - deadAnts;

    cout << "After step #" << this->stepNumber << "\n"
         << Ant::getNewAnts() << " new ants were born this turn" << "\n"
         << Ant::getDeadAnts() << " ants were eaten by doodlebugs this turn" << "\n"
         << Doodlebug::getNewDoodlebugs() << " new doodlebugs were born this turn" << "\n"
         << Doodlebug::getDeadDoodlebugs() << " doodlebugs starved to death this turn" << "\n\n"
         << "There are currently " << Ant::getTotalAnts() << " ants on the board" << "\n"
         << "There are currently " << Doodlebug::getTotalDoodlebugs() << " doodlebugs on the board" << endl;

    //this->deadDoodles = this->deadAnts = this->newAnts = this->newDoodles = 0;
    this->stepNumber++;
}

/***************************************************************
** Program name: main.cpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 6, 2019
** Description:  This is the main file that prompts the user to
**               create a Board object and runs the simulation.
**			     The simulation is cellular automata in a 2D predator–prey game.
**				 The preys are ants and the predators are doodlebugs. The
**				 ants and doodlebugs move about a regular grid. Ants will breed
**			     and Doodlebugs will breed, eat Ants, and/or starve.
**			     The user will see each resulting "time step" or "round" displayed
**				 to the computer console at the conclusion of each time step.
**				 The user will specify the size of the board, number of starting
**				 Doodlebugs and Ants, and the number of simulation time steps.
**				 At the conclusion the user will have the options to quit or
**				 continue for another user-specified amount of steps.
***************************************************************/
#include <iostream>	    //Console input and output
#include <cstdlib> 		//seeding random function
#include <ctime> 		//time() used in seeding the random function
#include "Board.hpp"
#include "validation.hpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	int numSteps,
		numRows,
		numCols,
		numAnts,
		numDoodlebugs;
	int choice = 0;

	srand(time(NULL));

	//Greet the user and note that we implemented the extra credit
	cout << "\n\tWELCOME TO THE PREDATOR/PREY SIMULATION"
		 << "\n\t---------------------------------------"
		 << "\n\nExtra credit is implemented.\n" << endl;

	//Get the number of rows from the user
	cout << "Please enter the number of number of rows on the board (1-100): ";
	cin >> numRows;
	validateInt(numRows, 1, 100);

	//Get the number of columns from the user
	cout << "Please enter the number of columns on the board (1-100): ";
	cin >> numCols;
	validateInt(numCols, 1, 100);

	//Get the number of Ants from the user (must be less than number of rows * number of columns)
	cout << "Please enter the number of Ants you'd like to start the game with (0-" << (numRows * numCols) << "): ";
	cin >> numAnts;
	validateInt(numAnts, 0, (numRows * numCols));

	//Get the number of Doodlebugs from the user (must be less than (number of rows * number of columns) - number of Ants)
	cout << "Please enter the number of Doodlebugs you'd like to start the game with: (0-" << (numRows * numCols - numAnts) << "): ";
	cin >> numDoodlebugs;
	validateInt(numDoodlebugs, 0, (numRows * numCols - numAnts));

	//Get the number of teps to run the simulation from the user
	cout << "Please enter the number of steps to run the simulation (1-5000): ";
	cin >> numSteps;
	validateInt(numSteps, 1, 5000);

	//Create the game.
	Board myGame(numRows, numCols, numAnts, numDoodlebugs);
	myGame.runGame(numSteps);

	//After the initial simulation is complete, ask the user if they want to continue (while maintaining board state)
	do
	{
		cout << numSteps << " steps completed! Would you like to continue running the simulation?\n"
		<< "1. Yes\n"
		<< "2. No\n"
		<< "Enter choice: ";
		cin >> choice;
		validateInt(choice, 1, 2);

		if (choice == 1)
		{
			numSteps = 0;

			cout << "Please enter the number of steps to run to continue the simulation (1-5000): ";
			cin >> numSteps;
			validateInt(numSteps, 1, 5000);

			myGame.runGame(numSteps);
		}

	} while (choice != 2);

	return 0;
}

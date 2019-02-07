#include <iostream>
#include <stdlib.h> //rand
#include <time.h>  //time
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
		numDoodles;
	int choice = 0;

	srand(time(NULL));

	//AW: greet and prompt the user for number of steps.
	//AW: we can make this into a separate function if we want to keep main nice and tidy
    cout << "\n\tWELCOME TO THE PREDATOR/PREY SIMULATION"
	 	 << "\n\t---------------------------------------"
	 	 << "\n\nExtra credit is implemented.\n" << endl;

	cout << "Please enter the number of number of rows on the board (1-100): ";
	cin >> numRows;
	validateInt(numRows, 1, 100);

	cout << "Please enter the number of columns on the board (1-100): ";
	cin >> numCols;
	validateInt(numCols, 1, 100);

	cout << "Please enter the number of Ants you'd like to start the game with (0-" << (numRows * numCols) << "): ";
	cin >> numAnts;
	validateInt(numAnts, 0, (numRows * numCols));

	cout << "Please enter the number of Doodlebugs you'd like to start the game with: (0-" << (numRows * numCols - numAnts) << "): ";
	cin >> numDoodles;
	validateInt(numDoodles, 0, (numRows * numCols - numAnts));

	//AW: 5000 is a completely arbitrary limit, we can change it
    cout << "Please enter the number of steps to run the simulation (1-5000): ";
	cin >> numSteps;
	validateInt(numSteps, 1, 5000);

	//Create the game.
	Board myGame(numRows, numCols, numAnts, numDoodles);
	myGame.runGame(numSteps);
	myGame.printBoard();

    //LB: After the initial simulation is complete, ask the user if they want to continue (while maintaining board state)
    do {
	  cout << numSteps << " steps completed! Would you like to continue running the simulation?\n"
	       << "1. Yes\n"
	       << "2. No\n"
		   << "Enter choice: ";
	  cin >> choice;
	  validateInt(choice, 1, 2);

	  if (choice == 1) {
	  	numSteps = 0;

	  	cout << "Please enter the number of steps to run to continue the simulation (1-5000): ";
	  	cin >> numSteps;
	  	validateInt(numSteps, 1, 5000);

	    myGame.runGame(numSteps);
	    myGame.printBoard();
	  }

    } while (choice !=2);

	return 0;
}

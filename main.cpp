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
    cout << "WELCOME TO THE PREDATOR/PREY SIMULATION" << endl << endl;
	/* EXTRACREDIT
	cout << "Please enter the number of number of rows on the board (1-100)" << endl;
	cin >> numRows;
	validateInt(numRows, 1, 100);
	cout << "Please enter the number of columns on the board (1-100)" << endl;
	cin >> numCols;
	validateInt(numCols, 1, 100);
	cout << "Please enter the number of Ants you'd like to start the game with" << endl;
	cin >> numAnts;
	validateInt(numAnts, 1, (numRows * numCols - 1));
	cout << "Please enter the number of Doodlebugs you'd like to start the game with" << endl;
	cin >> numDoodles;
	validateInt(numDoodles, 1, (numRows * numCols - numAnts));
	*/
	//AW: 5000 is a completely arbitrary limit, we can change it
    cout << "Please enter the number of steps to run the simulation (1-5000): " << endl << endl;
	cin >> numSteps;
	validateInt(numSteps, 1, 5000);


	//EXTRA CREDIT CONSTRUCTOR
	//Board myGame(numRows, numCols, numAnts, numDoodles);
	Board myGame;
	myGame.runGame(numSteps);
	myGame.printBoard();

    //LB: After the initial simulation is complete, ask the user if they want to continue (while maintaining board state)
    do {
	  cout << numSteps << " steps completed. Would you like to continue running the simulation?" << endl;
	  cout << "1. Yes" << endl;
	  cout << "2. No" << endl << endl;
	  cin >> choice;
	  validateInt(choice, 1, 2);

	  if (choice == 1) {
	  	numSteps = 0;

	  	cout << "Please enter the number of steps to run to continue the simulation (1-5000): " << endl << endl;
	  	cin >> numSteps;
	  	validateInt(numSteps, 1, 5000);

	    myGame.runGame(numSteps);
	    myGame.printBoard();
	  }

    } while (choice !=2);

	return 0;
}
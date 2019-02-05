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
	int numSteps = 0;
	int choice = 0;

	srand(time(NULL));

	//AW: greet and prompt the user for number of steps.
	//AW: we can make this into a separate function if we want to keep main nice and tidy
    cout << "WELCOME TO THE PREDATOR/PREY SIMULATION" << endl << endl;

	//AW: 5000 is a completely arbitrary limit, we can change it
    cout << "Please enter the number of steps to run the simulation (1-5000): " << endl << endl;
	cin >> numSteps;
	validateInt(numSteps, 1, 5000);

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
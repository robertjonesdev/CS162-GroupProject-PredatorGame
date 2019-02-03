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

	srand(time(NULL));

	//AW: greet and prompt the user for number of steps.
	//AW: we can make this into a separate function if we want to keep main nice and tidy
    cout << "WELCOME TO THE PREDATOR/PREY SIMULATION" << endl << endl;

	//AW: 5000 is a completely arbitrary limit, we can change it
    cout << "Please enter the number of steps to run the simulation (1-5000): " << endl << endl;
	cin >> numSteps;
	validateInt(numSteps, 1, 5000);

	Board myGame(numSteps);
	myGame.printBoard();

	return 0;
}
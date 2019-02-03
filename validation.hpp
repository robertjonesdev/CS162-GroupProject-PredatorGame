/*********************************************************************
** Author: Andrew Wilson
** Date: Jan 12, 2019
** Description: Functions for input validation.
*********************************************************************/

#ifndef VALIDATION_HPP
#define VALIDATION_HPP

void validateInt(int &input);  //reprompts if input is not an integer
void validateInt(int &input, int min, int max);  //reprompts if input is not an integer or between min and max
void validateDouble(double &input);  //reprompts if input is not a decimal/integer
void validateDouble(double &input, double min, double max);  //reprompts if input is not a decimal/integer or between min and max
void validateMenuChoice(int &menuChoice, int menuLength);   //reprompts if input is not an integer between 1 and menuLength
void clearScreen();  //clears the screen
void systemPause();  //Pauses until user presses a key

#endif
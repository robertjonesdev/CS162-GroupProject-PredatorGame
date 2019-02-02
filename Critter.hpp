/***************************************************************
** Program name: Critter.hpp (part of CS162 Group Project)
** Author:       Group 16 (LB, LB, RJ, DS, AW)
** Date:         February 2, 2019
** Description:  This is the Critter class specification file.
**               Doodlebug and Ant inherit from Critter.
***************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

class Critter {
  private:

  protected:
    int locationX;
    int locationY;
    int breedingCounter;

  public:
    Critter(int, int);
    int getX();
    int getY();
    int getBreedingCounter();
    void setBreedingCounter(int);
    virtual void breed() = 0; //pure virtual function which will be overridden in child classes
    virtual void move() = 0; //pure virtual function which will be overridden in child classes
};

#endif
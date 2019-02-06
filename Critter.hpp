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
  protected:
    int row;
    int col;
    int breedingCounter;
    enum Direction {UP, RIGHT, DOWN, LEFT};  //AW: used for movement
    bool isAnt;
    bool isDoodlebug;

  public:
    Critter();  //AW: default constructor, probably unused.
    Critter(int, int);
    int getRow();
    int getCol();
    int getBreedingCounter();
    void setBreedingCounter(int);
    virtual bool getIsDoodlebug();
    virtual bool getIsAnt();
    virtual void starve(Critter*** gameBoard) {};  //for doodlebug starving
    virtual void incrementCounters() = 0;  //adds 1 to the breeding counter, and also 1 to the starving counter for Doodlebugs
    virtual void breed(Critter*** gameBoard) = 0; //pure virtual function which will be overridden in child classes
    virtual void move(Critter*** gameBoard) = 0; //pure virtual function which will be overridden in child classes
};

#endif

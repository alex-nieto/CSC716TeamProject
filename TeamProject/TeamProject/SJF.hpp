//
//  SJF.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#ifndef SJF_hpp
#define SJF_hpp

#include <stdio.h>
#include "Algorithm.hpp"

using namespace std;

//sjf class will implement the Shortest Job First and Shortest Remaining Time Next algorithms
class SJF : public Algorithm{
    
private:
    //private data members
    bool pre_emptive; //whether the algorithm is pre-emptive or not (Shortest Job First or Shortest Remaining Time Next)
    
public:
    //public methods
    //default constructor
    SJF();
    //constructor initializers
    SJF(int numOfProcesses, Process processes[]);
    SJF(bool pre_emptive, int numOfProcesses, Process processes[]);
    //implementation of algorithm method (override from parent class)
    void implementAlg() override; //will actually implement the algorithm
};
#endif /* SJF_hpp */

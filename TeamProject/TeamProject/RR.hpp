//
//  RR.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef RR_hpp
#define RR_hpp

#include <stdio.h>
#include "Algorithm.hpp"

//class to implement "Round Robin" algorithm given a quantum
class RR : public Algorithm{
    
private:
    //private data member
    int quantum;
    
public:
    //default constructor
    RR();
    //constructor initializer
    RR(int quantum, int numOfProcesses, vector<Process> processes, int switchTime);
    //implementation of algorithm method (override from parent class)
    void implementAlg() override;
};

#endif /* RR_hpp */

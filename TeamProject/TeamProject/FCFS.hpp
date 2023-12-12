//
//  FCFS.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef FCFS_hpp
#define FCFS_hpp

#include <stdio.h>
#include "Algorithm.hpp"

//class to implement "First Come First Serve" algorithm
class FCFS : public Algorithm{
    
private:
    //private data members
    int clockTime;
    list<Process> readyQueue;
    
public:
    //constructor initializer
    FCFS(int numOfProcesses, Process processes[], int switchTime);
    //implementation of algorithm method (override from parent class)
    void implementAlg() override;
};

#endif /* FCFS_hpp */

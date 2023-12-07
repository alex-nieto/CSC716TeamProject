//
//  Algorithm.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <stdio.h>
#include <list>
#include "Event.hpp"

//algorithm class is an abstract class that hold the methods and data needed for an algorithm and will be inherited by all algorithm classes
class Algorithm{
    
protected:
    //protected data members (accessible by child classes)
    string name; //name of the algorithm to be implemented
    int numOfProcesses; //number of processes to run the implementation on
    Process* processes; //pointer to the list of processes to be executed in the algorithm (job queue)
    list<Event> events; //events for the algorithm
    int idleTime; //time the cpu not busy (to be updated by the child class - will be dependent on input and alg used)
    
public:
    //default constructor
    Algorithm();
    //constructor initializer
    Algorithm(string name, int numOfProcesses, Process processes[]);
    //virtual implementAlg method which will be implemented by child classes
    virtual void implementAlg() = 0;
    //calculation methods
    int calculateTotalTimeExecution(); //calculates the total time execution for the algorithm
    int calculateCPUutilization(); //calculates the cpu utilization for the algorithm
    //print methods
    void printAlgorithmInfo(); //outputs the algorithm info
    void printProcessInfo(); //outputs the info for each process in the algorithm
    void printProcessEvents(); //outputs the events of each process (At time X: Process {id} moves from {state} to {state})
};

#endif /* Algorithm_hpp */

//
//  Process.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/1/23.
//

#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

//process class holds the information for 1 inputed process
class Process{
    
private:
    //private data members
    int arrivalTime; //arrival time of the process
    int serviceTime; //how long the process will execute for
    int priority; //the priority of the process against other processes
    int startTime; //the time at which the process starts to execute
    
public:
    //public methods
    //default constructor
    Process();
    //constructor initializers
    Process(int serviceTime);
    Process(int arrivalTime, int serviceTime);
    Process(int arrivalTime, int serviceTime, int priority);
    Process(int arrivalTime, int serviceTime, int priority, int startTime);
    //set methods
    void setArrivalTime(int arrivalTime);
    void setServiceTime(int serviceTime);
    void setPriority(int priority);
    void setStartTime(int startTime);
    //get methods
    int getArrivalTime();
    int getServiceTime();
    int getPriority();
    int getStartTime();
    //calculation methods
    int calculateFinishTime(); //calculates the time the processes finishes executing
    int calculateTurnAroundTime(); //calculates the turn around time for the process
    int calculateNormalizedTAT(); //calculates the normaized turn around time for the process
    int calculateWaitTime(); //calculates the wait time for the process
    //print method
    void printProcessInfo(); //outputs the process information
    //overloaded operator methods
    void operator=(const Process &p); //assign process to process (= operator)
//    bool operator<(Process &p);
//    bool operator>(Process &p);
//    bool operator<=(Process &p);
//    bool operator>=(Process &p);
//    bool operator==(Process &p);
};

#endif /* Process_hpp */

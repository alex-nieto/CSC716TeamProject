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
    int processId; //process Id
    int arrivalTime; //arrival time of the process
    int serviceTime; //how long the process will execute for
    int ioTime; //how long the process will use io device
    int priority; //the priority of the process against other processes
    int startTime; //the time at which the process starts to execute
    int finishTime; //the time at which the process finishes executing
    list<int>processingTime; //this will hold all the time switches that occur (CPU time, IO time, ... CPU time)
    
public:
    //public methods
    //default constructor
    Process();
    //constructor initializers
    Process(int processId, int serviceTime);
    Process(int processId, int arrivalTime, int serviceTime, int ioTime);
    Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority);
    Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority, int startTime);
    Process(int processId, int arrivalTime, list<int>processingTime);
    //set methods
    void setProcessId(int processId);
    void setArrivalTime(int arrivalTime);
    void setServiceTime(int serviceTime);
    void setIOtime(int ioTime);
    void setPriority(int priority);
    void setStartTime(int startTime);
    void setFinishTime(int finishTime);
    void setProcessingTime(list<int>processingTime);
    //get methods
    int getProcessId();
    int getArrivalTime();
    int getServiceTime();
    int getIOtime();
    int getPriority();
    int getStartTime();
    int getFinishTime();
    list<int> getProcessingTime();
    //calculation methods
    int calculateFinishTime(); //calculates the time the processes finishes executing (straight through execution from start time)
    int calculateTurnAroundTime(); //calculates the turn around time for the process (total time spent in the system)
    int calculateNormalizedTAT(); //calculates the normaized turn around time for the process
    int calculateWaitTime(); //calculates the wait time for the process
    //print method
    void printProcessInfo(); //outputs the process information
    //overloaded operator methods
    Process& operator=(const Process &p); //assign process to process (= operator)
    bool operator==(const Process &p) const; //check if process is equal to another process
};

#endif /* Process_hpp */

//
//  Simulation.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#ifndef Simulation_hpp
#define Simulation_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <queue>
#include "FCFS.hpp"
#include "SJF.hpp"
#include "RR.hpp"

//Simulation class is for analyzing and executing input
class Simulation{
    
private:
    //private Simulation members
    string input; //input string from the console
    bool detail; //indicate whether they included -d parameter (only used and accessed by the Simulation class)
    bool verbose; //indicate whether they included -v parameter (only used and accessed by the Simulation class)
    string algToImplement; //will hold the algorithm abreviation chosen if any (FCFS, SJF, SRTN, RR10, RR50, RR100)
    int numOfProcesses; //number of processes indicated by the file
    int switchTime;
    list<Process> processList; //processes created from file information
    //private methods
    bool readFile(); //reads file information and create the process list
    bool readParameterInput(); //reads which parameters were included and updates related Simulation members
    void runAlgorithm(Algorithm** algorithToRun, int size); //implements a list of algorithms and outputs/prints results
    void runSelectAlgorithm(); //runs the selected algorithm and outputs/prints results
    Process* copyProcessListToArr(); //copies list of processes into an array
    
public:
    //public methods
    //default constructor
    Simulation();
    //constructor initializers
    Simulation(string input);
    //set method - only need this one because all other Simulation members are controlled exclusively by the class
    void setInput(string input);
    //get methods - mostly can be used for debug in this case
    string getInput();
    bool getDetail();
    bool getVerbose();
    string getAlgToImpl();
    int getNumOfProcesses();
    Process* getProcesses();
    //execute method
    bool execute(); //executes the input (runs algorithm selected or all and corresponding input parameters
};

#endif /* Simulation_hpp */

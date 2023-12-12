//
//  main.cpp
//  CSC 716 TeamProject
//
//  Created by Alex C Nieto on 11/27/23.
//

#include <iostream>
#include "Simulation.hpp"
#include "SJF.hpp"

const string SJFname = "Shortest Job First";
const string SRTNname = "Shortest Remaining Time Next";

int main() {
//    Simulation* simulation; //simulation class pointer created
//    string input = ""; //string for input
//    do{
//        //asking for user input
//        cout << "$ ";
//        getline(cin,input);
//        Simulation data(input); //creating new simulation object and passing input into constructor
//        simulation = &data; //updating the pointer to access new simulation object
//    }while(simulation->execute()); //execute simulation
    
    int numOfProcesses = 5;
    Process processes [numOfProcesses];
    Process processes2 [numOfProcesses];
    
    Process p1(1, 2, 1, 0);
    Process p2(2, 1, 5, 0);
    Process p3(3, 4, 1, 0);
    Process p4(4, 0, 6, 0);
    Process p5(5, 2, 3, 0);
    
    processes[0] = p1;
    processes[1] = p2;
    processes[2] = p3;
    processes[3] = p4;
    processes[4] = p5;
    
    processes2[0] = p1;
    processes2[1] = p2;
    processes2[2] = p3;
    processes2[3] = p4;
    processes2[4] = p5;

    
    Algorithm* alg1 = new RR(true,numOfProcesses,processes);
    
    alg1->implementAlg();
    alg1->printAlgorithmInfo(); cout << endl;
    alg1->printProcessInfo(); cout << endl;
    alg1->printProcessEvents(); cout << endl;
    return 0;
}
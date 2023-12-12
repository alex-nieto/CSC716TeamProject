//
//  RR.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#include "RR.hpp"

const string RRname = "Round Robin - Quantum = ";

RR :: RR() : Algorithm(){
    quantum = 0;
}
RR :: RR(int quantum, int numOfProcesses, Process processes[], int switchTime) : Algorithm(RRname + to_string(quantum), numOfProcesses, processes, switchTime){
    this->quantum = quantum;
}
void RR :: implementAlg(){
    
}

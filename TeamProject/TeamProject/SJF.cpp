//
//  SJF.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#include "SJF.hpp"

const string SJFname = "Shortest Job First";
const string SRTNname = "Shortest Remaining Time Next";

SJF :: SJF() : Algorithm(){
    pre_emptive = 0;
}
SJF :: SJF(int numOfProcesses, Process processes[]) : Algorithm(SJFname, numOfProcesses, processes){
    this->pre_emptive = 0;
}
SJF :: SJF(bool pre_emptive, int numOfProcesses, Process processes[]) : Algorithm(pre_emptive ? SRTNname : SJFname, numOfProcesses, processes){
    this->pre_emptive = pre_emptive;
}
void SJF :: implementAlg(){
    if(!pre_emptive){
        preEmptiveImplementation();
    }else{
        nonPreEmptiveImplememtation();
    }
}
void SJF :: preEmptiveImplementation(){
    int serviceTime = 0;
    //Process * orderedProcesses = new Process[numOfProcesses];
    for(int i = 0; i < numOfProcesses; i++){
        serviceTime = processes[i].getServiceTime();
        
    }
}
void SJF :: nonPreEmptiveImplememtation(){
    
}

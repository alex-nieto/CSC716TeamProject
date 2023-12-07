//
//  Algorithm.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#include "Algorithm.hpp"

Algorithm :: Algorithm(){
    name = "";
    numOfProcesses = 0;
    processes = NULL;
}
Algorithm :: Algorithm(string name, int numOfProcesses, Process processes[]){
    this->name = name;
    this->numOfProcesses = numOfProcesses;
    this->processes = processes;
    sortByArrivalTime();
}
void Algorithm :: sortByArrivalTime(){
//    int tempTime = 0;
//    for(int i = 0; i < numOfProcesses; i++){
//        if(processes[i].getArrivalTime() > tempTime){
//            tempTime = processes[i].getArrivalTime();
//        }
//    }
}
int Algorithm :: calculateTotalTimeExecution(){
    //looping through all processes to find the latest finish time
    int totalExecuteTime = 0;
    if(processes != NULL){
        for(int i = 0; i < numOfProcesses; i++){
            if(processes[i].calculateFinishTime() > totalExecuteTime)
                totalExecuteTime = processes[i].calculateFinishTime();
        }
    }
    return totalExecuteTime;
}
int Algorithm :: calculateCPUutilization(){
    return 0;
}
void Algorithm :: printAlgorithmInfo(){
    cout << name << ": " << endl;
    cout << "Total Time required is " << calculateTotalTimeExecution() << " time units" << endl;
    cout << "CPU Utilization is " << calculateCPUutilization() << "%" << endl;
}
void Algorithm :: printProcessInfo(){
    //loop through all the processes and print details
    for(int i = 0; i < numOfProcesses; i++){
        cout << "Process " << i << ": " << endl;
        processes[i].printProcessInfo();
    }
}
void Algorithm :: printProcessEvents(){
    //At time X: Process {id} moves from {state} to {state}
    //new, ready, running, blocked, or terminated
}

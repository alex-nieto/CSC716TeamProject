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
    idleTime = 0;
}
Algorithm :: Algorithm(string name, int numOfProcesses, Process processes[]){
    this->name = name;
    this->numOfProcesses = numOfProcesses;
    this->processes = processes;
    idleTime = 0;
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
    //busy time/total time
    int totalTime = calculateTotalTimeExecution();
    return (totalTime - idleTime) / totalTime;
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
    events.sort();
    for(Event event : events){
        event.printEventInfo();
    }
}

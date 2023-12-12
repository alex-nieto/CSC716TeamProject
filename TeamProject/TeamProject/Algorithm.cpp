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
    switchTime = 0;
    idleTime = 0;
}
Algorithm :: Algorithm(string name, int numOfProcesses, Process processes[]){
    this->name = name;
    this->numOfProcesses = numOfProcesses;
    this->processes = processes;
    this->switchTime = 1;
    idleTime = 0;
}
Algorithm :: Algorithm(string name, int numOfProcesses, Process processes[], int switchTime){
    this->name = name;
    this->numOfProcesses = numOfProcesses;
    this->processes = processes;
    this->switchTime = switchTime;
    idleTime = 0;
}
list<Process> Algorithm :: createReadyQueue(){
    list<Process> readyQueue;
    
    //create ready events
    for(int i = 0; i < numOfProcesses; i++){
        Event arrivalEvent(processes[i].getArrivalTime(), processes[i], "ready", "new");
        events.push_back(arrivalEvent);
    }
    //sort ready events (events sort by event time - here will be arrival times since only ready events exist so far)
    events.sort();
    
    //add all processes to ready queue
    for(Event event: events){
        readyQueue.push_back(event.getProcess());
    }
    
    //return ready queue
    return readyQueue;
}
int Algorithm :: calculateTotalTimeExecution(){
    //looping through all processes to find the latest finish time
    int totalExecuteTime = 0;
    if(processes != NULL){
        for(int i = 0; i < numOfProcesses; i++){
            if(processes[i].getFinishTime() > totalExecuteTime)
                totalExecuteTime = processes[i].getFinishTime();
        }
    }
    return totalExecuteTime;
}
int Algorithm :: calculateCPUutilization(){
    //busy time/total time
    int totalTime = calculateTotalTimeExecution();
    return totalTime != 0 ? ((totalTime - idleTime) / totalTime)*100 : 0;
}
void Algorithm :: printAlgorithmInfo(){
    cout << name << ": " << endl;
    cout << "Total Time required is " << calculateTotalTimeExecution() << " time units" << endl;
    cout << "CPU Utilization is " << calculateCPUutilization() << "%" << endl;
}
void Algorithm :: printProcessInfo(){
    //loop through all the processes and print details
    for(int i = 0; i < numOfProcesses; i++){
        cout << "Process " << i+1 << ": " << endl;
        processes[i].printProcessInfo();
        cout << endl;
    }
}
void Algorithm :: printProcessEvents(){
    events.sort();
    for(Event event : events){
        event.printEventInfo();
    }
}

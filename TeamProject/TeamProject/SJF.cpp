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
SJF :: SJF(int numOfProcesses, Process processes[], int switchTime) : Algorithm(SJFname, numOfProcesses, processes, switchTime){
    this->pre_emptive = 0;
}
SJF :: SJF(bool pre_emptive, int numOfProcesses, Process processes[], int switchTime) : Algorithm(pre_emptive ? SRTNname : SJFname, numOfProcesses, processes, switchTime){
    this->pre_emptive = pre_emptive;
}
void SJF :: implementAlg(){
    
    //set clock start time
    int clockTime = 0;
    
    //ready and wait queues
    list<Process> readyQueue;
    list<Event> waitingQueue;
    //the processes that have arrived at a given time
    list<Process> allProcessesArrived;
    
    //create ready events + ready queue with ready processes
    readyQueue = createReadyQueue();
    
    //new state of clock is arrival time of the first ready process (earliest arrival time)
    clockTime = readyQueue.front().getArrivalTime();
    //set idle time to clockTime as so far this is the only wait time
    idleTime = clockTime;
    
    //create temporary event and process to hold current event and next ready process
    Event currentEvent;
    Process nextReadyProcess;
    
    do{
        //loop through ready queue
        for(Process process : readyQueue){
            //getting all events arrived at that time
            if(clockTime >= process.getArrivalTime()){
                allProcessesArrived.push_back(process);
            }
        }
        //if no processes available at next time
        if(allProcessesArrived.empty()){
            //calculate idle time
            idleTime = idleTime + readyQueue.front().getArrivalTime() - clockTime;
            clockTime = readyQueue.front().getArrivalTime();
        }else{
            //sort processes by service/burst time
            allProcessesArrived.sort([](Process &a, Process &b) { return a.getServiceTime() < b.getServiceTime(); });
            //sets next process to execute
            nextReadyProcess = allProcessesArrived.front();
            for(int i = 0; i < numOfProcesses; i++){
                if(nextReadyProcess.getProcessId() == processes[i].getProcessId()){
                    processes[i].setStartTime(clockTime);
//                    cout << "DEBUG: after we set start time: " << endl;
//                    printProcessInfo();
                    cout << endl;
                }
            }
            //clear list for next round
            allProcessesArrived.clear();
        }
        //create running event from next ready process
        currentEvent.setEvent(clockTime, nextReadyProcess, "running", "ready");
        //adding event to events (all events that occur in algorithm)
        events.push_back(currentEvent);
        //set clock to finished process time
        clockTime = readyQueue.front().calculateFinishTime() + switchTime;
        //create terminated event
        currentEvent.setEvent(clockTime, nextReadyProcess, "terminated", "running");
        //adding event to events (all events that occure in algorithm)
        events.push_back(currentEvent);
        //removing process from ready queue
        readyQueue.remove(nextReadyProcess);
        
    }while(!readyQueue.empty()); //while ready queue is not empty
}

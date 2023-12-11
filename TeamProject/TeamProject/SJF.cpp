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
void SJF :: sortByServiceTime(list<Process> &processesArrived){
    map<int,int> temp;
    list<Process> tempList = processesArrived;
    tempList.reverse();
    for(Process process : processesArrived){
        for(Process tempProcess : tempList){
            if(process.getServiceTime() < tempProcess.getServiceTime()){
                
            }
        }
        temp[process.getProcessId()] = process.getServiceTime();
    }
}
void SJF :: implementAlg(){
//    if(!pre_emptive){
//        preEmptiveImplementation();
//    }else{
//        nonPreEmptiveImplememtation();
//    }
    
    //set clock start time
    int clockTime = 0;
    //ready and wait queues
    list<Event> readyQueue;
    list<Event> waitingQueue;
    //the processes that arrived at a certain time
    list<Process> allProcessesArrived;
    //bool cpuBusy = false;
    
    //create ready events
    readyQueue = createReadyEvents();
    
    //new state of clock is arrival time of the first process actually running
    clockTime = readyQueue.front().getProcess()->getArrivalTime();
    idleTime = clockTime;
    Event execProcessEvent;
    Process nextReadyProcess;
    
    do{
        //loop through ready queue
        for(Event event : readyQueue){
            //getting all events arrived at that time
            if(clockTime >= event.getProcess()->getArrivalTime()){
                allProcessesArrived.push_back(*event.getProcess());
            }
        }
        //if no processes available at next time
        if(allProcessesArrived.empty()){
            //calculate idle time
            idleTime = idleTime + readyQueue.front().getProcess()->getArrivalTime() - clockTime;
            clockTime = readyQueue.front().getProcess()->getArrivalTime();
        }else{
            //sort processes by service/burst time
            allProcessesArrived.sort([](Event &a, Event &b) { return a.getProcess()->getServiceTime() < b.getProcess()->getServiceTime(); });
            //sets next process to execute
            nextReadyProcess = allProcessesArrived.front();
            nextReadyProcess.setStartTime(clockTime);
            //clear list for next round
            allProcessesArrived.clear();
        }
        //create running event from first in ready queue
        execProcessEvent.setEvent(clockTime, nextReadyProcess, "running", "ready");
        //adding event to events (all events that occur in algorithm)
        events.push_back(execProcessEvent);
        //set clock to finished process time
        clockTime = readyQueue.front().getProcess()->calculateFinishTime();
        //create terminated event
        execProcessEvent.setEvent(clockTime, nextReadyProcess, "terminated", "running");
        //adding event to events (all events that occure in algorithm)
        events.push_back(execProcessEvent);
        //removing event from ready queue
        readyQueue.pop_front();
        
    }while(!readyQueue.empty()); //while ready queue is not empty
}

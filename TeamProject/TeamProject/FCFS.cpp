//
//  FCFS.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#include "FCFS.hpp"

const string FCFSname = "First Come First Serve";

FCFS :: FCFS() : Algorithm(){}

FCFS :: FCFS(int numOfProcesses, Process processes[], int switchTime) : Algorithm(FCFSname, numOfProcesses, processes, switchTime){
    //set clock start time at 0
    clockTime = 0;
    //create ready events + ready queue with "ready" processes
    readyQueue = createReadyQueue();
}
void FCFS :: implementAlg(){

    //new state of clock is arrival time of the first ready process (sorted by earliest arrival time)
    clockTime = readyQueue.front().getArrivalTime();
    //set idle time to clockTime as so far this is the only wait time
    idleTime = clockTime;
    
    //create temporary event and process to hold current event and next ready process
    Event currentEvent;
    Process nextReadyProcess;
    
    do{
        //sets next process to execute
        nextReadyProcess = readyQueue.front();
        //set next process start time (this is the next/latest start time if process switch happened)
        nextReadyProcess.setStartTime(clockTime);
        //save start time info to main process array data member - "master" process list
        for(int i = 0; i < numOfProcesses; i++){
            //check if ids match and if we have not already set initial start time (which will be used to calculate other values)
            if(nextReadyProcess == processes[i] && processes[i].getStartTime() < 0){
                //set process start time for processes stored in process array
                processes[i].setStartTime(clockTime);
            }
        }
        //create running event from next ready process
        currentEvent.setEvent(clockTime, nextReadyProcess, "running", "ready");
        //adding event to events (all events that occur in algorithm)
        events.push_back(currentEvent);
        //removing process from ready queue
        readyQueue.remove(nextReadyProcess);
        //set clock to finished process time
        clockTime = nextReadyProcess.calculateFinishTime();
        //create terminated event
        currentEvent.setEvent(clockTime, nextReadyProcess, "terminated", "running");
        //adding event to events (all events that occure in algorithm)
        events.push_back(currentEvent);
        //save the finish time to main process list
        for(int i = 0; i < numOfProcesses; i++){
            if(nextReadyProcess == processes[i]){
                //set process start time for processes stored in process array
                processes[i].setFinishTime(clockTime);
            }
        }
        //account for process switch time
        clockTime+=switchTime;
    }while(!readyQueue.empty()); //while ready queue is not empty
}

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
    pre_emptive = false;
}
SJF :: SJF(int numOfProcesses, Process processes[], int switchTime) : Algorithm(SJFname, numOfProcesses, processes, switchTime){
    this->pre_emptive = false;
}
SJF :: SJF(bool pre_emptive, int numOfProcesses, Process processes[], int switchTime) : Algorithm(pre_emptive ? SRTNname : SJFname, numOfProcesses, processes, switchTime){
    this->pre_emptive = pre_emptive;
}
void SJF :: implementAlg(){
    
    //set clock start time at 0
    int clockTime = 0;
    
    //flag for indicating if process switch will happen for pre-emptive algorithm
    bool swapProcess = false;
    
    //create ready events + ready queue with "ready" processes
    list<Process> readyQueue = createReadyQueue();
    
    //new state of clock is arrival time of the first ready process (sorted by earliest arrival time)
    clockTime = readyQueue.front().getArrivalTime();
    //set idle time to clockTime as so far this is the only wait time
    idleTime = clockTime;
    
    //create temporary event and process to hold current event and next ready process
    Event currentEvent;
    Process nextReadyProcess;
    
    //the processes that have arrived at a given time
    list<Process> allProcessesArrived;
    
    do{
        if(!swapProcess){
            //loop through ready queue
            for(Process process : readyQueue){
                //getting all events arrived at that time
                if(clockTime >= process.getArrivalTime()){
                    allProcessesArrived.push_back(process);
                }
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
            //if process swapping occurs due to pre-emption
            if(swapProcess){
                //save last clock time
                int oldClock = clockTime;
                //set clock time to next process's arrival time
                clockTime = allProcessesArrived.front().getArrivalTime();
                //save "new" service time (what is left for process) to existing process
                nextReadyProcess.setServiceTime(nextReadyProcess.getServiceTime() - (clockTime - oldClock));
                //create "swap" event -> return process to ready
                currentEvent.setEvent(clockTime, nextReadyProcess, "ready", "running");
                //adding event to events (all events that occur in algorithm)
                events.push_back(currentEvent);
                //return process to ready queue
                readyQueue.push_back(nextReadyProcess);
                //Update clock with switch time accounted for
                clockTime+=switchTime;
            }
            //sets next process to execute
            nextReadyProcess = allProcessesArrived.front();
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
            //reset allProcessesArrived list and swap process flag
            allProcessesArrived.clear();
            swapProcess = false;
            if(pre_emptive){
                //if pre-emptive loop through the clock from the start time of the executing process (or current start time) until possible finish time (start time + service time)
                for(int currentTime = clockTime; currentTime < nextReadyProcess.calculateFinishTime(); currentTime++){
                    //temp count for current time passage
                    int timeUnitCount = 1;
                    //loop through ready queue
                    for(Process process : readyQueue){
                        //getting all events arrived at "current" time with less service time than what is left for current process running
                        if(currentTime >= process.getArrivalTime() && process.getServiceTime() < nextReadyProcess.getServiceTime() - timeUnitCount){
                            //add that to allProcessesArrived and set swap flag to true
                            allProcessesArrived.push_back(process);
                            swapProcess = true;
                        }
                    }
                    //if at any time there is a new process that has arrived that can be swapped, break out of loop
                    if(swapProcess){
                        //sorting the process arrived list by process id so if later two processes are equal, will go by process id
                        allProcessesArrived.sort([](Process &a, Process &b) { return a.getProcessId() < b.getProcessId(); });
                        break;
                    }
                    //incrementing time passage by 1 time unit
                    timeUnitCount++;
                }
            }
            //if no swap is necessary, then we can move the process to terminated
            if(!swapProcess){
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
            }
        }
    }while(!readyQueue.empty()); //while ready queue is not empty
}

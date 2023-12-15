// RR.cpp

#include "RR.hpp"
#include "queue"
#include <algorithm>

const string RRname = "Round Robin - Quantum = ";

RR :: RR() : Algorithm(){
    quantum = 1;
}

RR :: RR(int quantum, int numOfProcesses, vector<Process> processes, int switchTime) : Algorithm(RRname + to_string(quantum), numOfProcesses, processes, switchTime){
    this->quantum = quantum;
}

void RR::implementAlg()
{
    //set clock start time at 0
    int clockTime = 0;
    
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
            //if process swapping occurs due to pre-emption
            clockTime+=quantum;
            if(nextReadyProcess.getServiceTime() <= quantum){
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
            }else{
                //save "new" service time (what is left for process) to existing process
                nextReadyProcess.setServiceTime(nextReadyProcess.getServiceTime() - quantum);
                //save "new" service time (what is left for process) to existing process
                nextReadyProcess.setArrivalTime(clockTime);
                //create "swap" event -> return process to ready
                currentEvent.setEvent(clockTime, nextReadyProcess, "ready", "running");
                //adding event to events (all events that occur in algorithm)
                events.push_back(currentEvent);
                //return process to ready queue
                readyQueue.push_back(nextReadyProcess);
                readyQueue.sort([](Process &a, Process &b) { return a.getProcessId() < b.getProcessId(); });
            }
            //Update clock with switch time accounted for
            clockTime+=switchTime;
            //reset allProcessesArrived list and swap process flag
            allProcessesArrived.clear();
        }
    }while(!readyQueue.empty()); //while ready queue is not empty
}

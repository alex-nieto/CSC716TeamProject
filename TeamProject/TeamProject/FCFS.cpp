//
//  FCFS.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#include "FCFS.hpp"

const string FCFSname = "First Come First Serve";

FCFS :: FCFS(){
    
}
FCFS :: FCFS(int numOfProcesses, Process processes[]) : Algorithm(FCFSname, numOfProcesses, processes){
    
}
void FCFS :: implementAlg(){

    //
//  FCFS.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#include "FCFS.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


const string FCFSname = "First Come First Serve";

FCFS::FCFS() {
    class EventQueue {
    private:
        std::priority_queue<Event> queue;

    public:
        void addEvent(const Event& event) {
            queue.push(event);
        }

        Event getNextEvent() {
            if (!queue.empty()) {
                Event nextEvent = queue.top();
                queue.pop();
                return nextEvent;
            }
            // Return a default event or handle the empty queue case
        }

        bool isEmpty() const {
            return queue.empty();
        }
    };

    class FCFS : public Algorithm {
    private:
        int numOfProcesses;
        Process* processes;

    }
    FCFS::FCFS(int numOfProcesses, Process processes[]) : Algorithm(FCFSname, numOfProcesses, processes) {

    }
    void FCFS::implementAlg() {
        std::vector<Process> processQueue(processes, processes + numOfProcesses);

        // Sorting processes based on arrival time
        std::sort(processQueue.begin(), processQueue.end(),
            [](const Process& a, const Process& b) {
                return a.arrivalTime < b.arrivalTime;
            });

        int currentTime = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        EventQueue eventQueue;

        for (Process& process : processQueue) {
            if (currentTime < process.arrivalTime) {
                currentTime = process.arrivalTime;
            }

            process.startTime = currentTime;
            process.finishTime = currentTime + process.burstTime;
            currentTime = process.finishTime;

            process.waitingTime = process.startTime - process.arrivalTime;
            process.turnaroundTime = process.finishTime - process.arrivalTime;

            totalWaitingTime += process.waitingTime;
            totalTurnaroundTime += process.turnaroundTime;

            Event startEvent(currentTime, process, "running", "ready");
            eventQueue.addEvent(startEvent);

            Event finishEvent(currentTime, process, "terminated", "running");
            eventQueue.addEvent(finishEvent);
        }

        // Outputting the results
        std::cout << "Process\tArrival Time\tBurst Time\tStart Time\tFinish Time\tWaiting Time\tTurnaround Time\n";
        for (const Process& process : processQueue) {
            std::cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
                << process.startTime << "\t\t" << process.finishTime << "\t\t" << process.waitingTime << "\t\t"
                << process.turnaroundTime << "\n";
        }

        std::cout << "Average waiting time = "
            << static_cast<double>(totalWaitingTime) / processQueue.size() << "\n";
        std::cout << "Average turnaround time = "
            << static_cast<double>(totalTurnaroundTime) / processQueue.size() << "\n";

        // Processing events from the event queue
        while (!eventQueue.isEmpty()) {
            Event currentEvent = eventQueue.getNextEvent();
            // Process the current event
            // This could involve changing the state of a process, adjusting the scheduler, etc.
        }
    }
}

    
}

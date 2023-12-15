//
//  RR.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef RR_hpp
#define RR_hpp

#include <stdio.h>
#include "Algorithm.hpp"
#include "queue"
#include "Event.hpp"

class RR : public Algorithm
{

private:
    //private data member
    int quantum;
    int remaingTime;
    std::deque<Event> watingQueue;
    std::deque<Event> IOQueue;
    std::deque<Event> CompletedQueue;
    int currentTime;
    int timeQuantam;

public:
    //default constructor
    RR();
    //constructor initializer
    RR(int quantum, int numOfProcesses, vector<Process> processes, int switchTime);
    //implementation of algorithm method (override from parent class)
    void implementAlg() override;
    void printProcessInfo() override;
    void initializeEventQueue();
    void handleArrivalEvent(Event event);
    void handleCompleted(Event event);
    void handleIo(Event event);
    bool compareEvent(Event obj1, Event obj2);
    void updateProcesses();
};

#endif /* RR_hpp */

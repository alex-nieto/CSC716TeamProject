// RR.cpp

#include "RR.hpp"
#include "queue"
#include "Event.hpp"
#include <algorithm>

const std::string RRname = "Round Robin - Quantum = ";

RR::RR()
{
}

RR::RR(int quantum, int numOfProcesses, Process processes[], int switchTime) : Algorithm(RRname + std::to_string(quantum), numOfProcesses, processes)
{

    deque<Event> watingQueue;
    deque<Event> IOQueue;
    queue<Event> CompletedQueue;
    this->processes = processes;
    this->numOfProcesses = numOfProcesses;
    this->currentTime = 0;
    this->timeQuantam = 50;
    this->quantum = 50;
    this->switchTime = switchTime;
}

bool RR::compareEvent(Event obj1, Event obj2)
{
    return obj1.getProcess().getArrivalTime() < obj2.getProcess().getArrivalTime();
}

void RR::initializeEventQueue()
{
    cout << this->numOfProcesses;
    for (int i = 0; i <= this->numOfProcesses; i++)
    {
        Event temp = Event(this->processes[i].getArrivalTime(), processes[i], "ready", "new", processes[i].getServiceTime(), EventType::arrival);
        this->watingQueue.push_back(temp);
    }
    std::sort(this->watingQueue.begin(), this->watingQueue.end(), [this](const Event &event1, const Event &event2)
              { return this->compareEvent(event1, event2); });
}

void RR::implementAlg()
{
    // // initlize the event que
    this->initializeEventQueue();

    // run untill the event que is empty
    while (!this->watingQueue.empty())
    {
        // give the latest recent event
        Event currentEvent = this->watingQueue.front();
        this->watingQueue.pop_front();
        this->currentTime = std::max(currentEvent.getProcess().getArrivalTime(), this->currentTime);

        if (currentEvent.getEventType() == EventType::arrival)
        {
            this->handleArrivalEvent(currentEvent);
        }
        else if (currentEvent.getEventType() == EventType::processIo)
        {
            this->handleIo(currentEvent);
        }
        else if (currentEvent.getEventType() == EventType::completed)
        {
            this->handleCompleted(currentEvent);
        }
    }
    this->updateProcesses();
}

void RR::handleArrivalEvent(Event event)
{
    if (this->currentTime < event.getRemaningTime() < this->timeQuantam)
    {
        cout << "event arrived " << this->currentTime << " " << event.getProcess().getServiceTime() << "\n";
        event.getProcess().setStartTime(this->currentTime);
        this->currentTime = this->currentTime + event.getProcess().getServiceTime();
        cout << "start time" << event.getProcess().getStartTime() << "\n";
        event.setEventType(EventType::processIo);
        event.getProcess().setFinishTime(this->currentTime);
        this->watingQueue.push_front(event);
    }
}

void RR::updateProcesses(){
    for (int i = 0; i < this->numOfProcesses; i++)
    {
        this->processes[i] = this->CompletedQueue[i].getProcess();
    }
}

void RR::handleIo(Event event)
{
    this->IOQueue.push_back(event);
    cout << event.getProcess().getProcessId() << "pushed to io"
         << "\n";
    event.setEventType(EventType::completed);
    this->watingQueue.push_front(event);
}

void RR::handleCompleted(Event event)
{
    event.setEventType(EventType::completed);
    this->CompletedQueue.push_back(event);
    cout << "event completed completed" << event.getProcess().getProcessId() << "\n";
}

void RR ::printProcessInfo()
{
    // just overwting it for now.
    for (int i = 0; i < numOfProcesses; i++)
    {
        cout << "Process " << i + 1 << ": " << endl;
        this->CompletedQueue[i].getProcess().printProcessInfo();

        cout << endl;
    }
}